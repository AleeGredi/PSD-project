#include "main_functions.h"

/* 1. Print all available courses */
void action_print_all_courses(array_ptr array) {
    printf("\n--- Available Courses ---\n");
    array_print(array, stdout, print_course_callback);
}

/* 2. Show my booked courses */
void action_show_booked_courses(linked_list_ptr booked_list) {
    printf("\n--- Booked Courses ---\n");
    ll_print(booked_list, stdout, print_course_callback);
}

/* 3. Show course history */
void action_show_history(linked_list_ptr history_list) {
    printf("\n--- Course History ---\n");
    ll_print(history_list, stdout, print_frequentation_callback);
}

/* 4. Book a course */
void action_book_course(int course_id, 
                        linked_list_ptr booked_list,
                        linked_list_ptr history_list,
                        hash_map_ptr hash_map,
                        user_ptr user)
{
    if (compare_datetime(get_datetime(),
        get_subscription_end_date(get_user_subscription(user))) == 1)
    {
        printf("Subscription has expired.\n");
        return;
    }

    course_ptr course = get_course(hash_map, course_id);
    if (!course) {
        printf("Course ID not found.\n");
        return;
    }

    /* Check duplicate booking */
    course_ptr tmp = create_course(course_id, "", NULL, 0, 0);
    if (ll_search(booked_list, tmp, compare_course_id) != -1) {
        printf("You have already booked this course.\n");
        delete_course(tmp);
        return;
    }
    delete_course(tmp);

    /* Check availability */
    if (get_course_seats_booked(course) >= get_course_seats_total(course)) {
        printf("No available seats for this course.\n");
        return;
    }

    /* Book it */
    ll_add(booked_list, course);
    set_course_seats_booked(course,
        get_course_seats_booked(course) + 1);

    /* Update history */
    int idx = ll_search(history_list, course, compare_course_id);
    if (idx == -1) {
        frequentation_ptr f = create_frequentation(
            get_course_id(course),
            get_course_name(course),
            1
        );
        ll_add(history_list, f);
    } else {
        frequentation_ptr *fp =
            (frequentation_ptr*)ll_get_at(history_list, idx);
        set_frequentation_times_booked(
           *fp,
           get_frequentation_times_booked(*fp) + 1
        );
    }

    printf("Course booked successfully.\n");
}

/* 5. Cancel a booked course */
void action_cancel_course(linked_list_ptr booked_list,
                          linked_list_ptr history_list)
{
    uint16_t course_id;
    printf("Enter course ID to cancel: ");
    if (scanf("%hu", &course_id) != 1) { getchar(); return; }
    getchar();

    int idx = ll_search(booked_list, &course_id, compare_course_id);
    if (idx == -1) {
        printf("You have not booked this course.\n");
        return;
    }

    course_ptr course = *(course_ptr*)ll_get_at(booked_list, idx);
    ll_delete_at(booked_list, idx, NULL);
    set_course_seats_booked(course,
        get_course_seats_booked(course) - 1);

    int hidx = ll_search(history_list, course, compare_course_id);
    if (hidx != -1) {
        frequentation_ptr freq =
            *(frequentation_ptr*)ll_get_at(history_list, hidx);
        int times = get_frequentation_times_booked(freq) - 1;
        set_frequentation_times_booked(freq, times);
        if (times <= 0) {
            ll_delete_at(history_list, hidx, delete_frequentation);
        }
    }

    printf("Course cancellation successful.\n");
}

/* 6. Check subscription and optionally renew */
void action_check_subscription(user_ptr user) {
    if (compare_datetime(get_datetime(),
                         get_subscription_end_date(get_user_subscription(user)))
        < 1)
    {
        printf("Subscription is valid.\n");
    } else {
        printf("Subscription has expired.\n");
        datetime_ptr now = get_datetime();
        datetime_ptr start = create_datetime(
            00,
            00,
            get_datetime_field(now, "day"),
            get_datetime_field(now,"month"),
            get_datetime_field(now,"year")
        );
        datetime_ptr end = create_datetime(
            59,
            23,
            1,
            (get_datetime_field(now,"month")+1)%12,
            get_datetime_field(now,"year")
        );
        set_subscription_renew(
            get_user_subscription(user),
            start, end
        );
        printf("Subscription renewed.\n");
    }
}

/* 7. Show last report */
void action_show_last_report(user_ptr user) {
    char path[192];
    snprintf(path, sizeof(path), "%s%s_report.txt",
             REPORT_PATH, get_user_username(user));
    FILE *fp = fopen(path, "rb");
    if (!fp) {
        printf("Wait next month for the report to be generated\n");
        return;
    }
    fseek(fp, 0, SEEK_END);
    long sz = ftell(fp);
    rewind(fp);
    char *buf = malloc(sz+1);
    if (!buf) { fclose(fp); return; }
    fread(buf, 1, sz, fp);
    buf[sz] = '\0';
    fclose(fp);

    printf("Here is your monthly report:\n%s\n", buf);
    free(buf);
}

/* 0. Exit: saving is easiest from main still */
void action_exit_and_save(hash_map_ptr map,
                          array_ptr array,
                          linked_list_ptr booked,
                          linked_list_ptr history,
                          user_ptr user)
{
    char user_filepath[192] = {0};
    snprintf(user_filepath, sizeof(user_filepath), "assets/users/%s.txt", get_user_username(user));

    char report_filepath[256] = {0};
    snprintf(report_filepath, sizeof(report_filepath), "assets/report/%s_report.txt", get_user_username(user));

    report(report_filepath, user, history);
    save_user(user_filepath, booked, history, user);
    save_course(COURSE_PATH, array);
    array_delete(array, NULL);
    ll_delete_list(booked, NULL);
    ll_delete_list(history, NULL);
    delete_hash_map(map, true);
    printf("Exiting program and saving courses.\n");
}


char *login_user(void) {
    char input_buf[256];
    char *username = NULL;
    char password[MAX_INPUT_USER];
    char stored_password[MAX_INPUT_USER];
    char filepath[512];
    FILE *file;
    char linebuf[1024];

    printf("=== User Login ===\n");

    // Read username
    printf("Enter username: ");
    if (fgets(input_buf, sizeof(input_buf), stdin) == NULL) {
        fprintf(stderr, "Failed to read username.\n");
        return NULL;
    }
    // Strip newline
    input_buf[strcspn(input_buf, "\n")] = '\0';

    // Allocate and copy username
    username = malloc(strlen(input_buf) + 1);
    if (!username) {
        perror("malloc");
        return NULL;
    }
    strcpy(username, input_buf);

    // Read password
    printf("Enter password: ");
    if (fgets(password, sizeof(password), stdin) == NULL) {
        fprintf(stderr, "Failed to read password.\n");
        free(username);
        return NULL;
    }
    password[strcspn(password, "\n")] = '\0';

    // Build path to user file
    snprintf(filepath, sizeof(filepath),
             "assets/users/%s.txt", username);

    file = fopen(filepath, "r");
    if (!file) {
        fprintf(stderr, "User '%s' not found.\n", username);
        free(username);
        return NULL;
    }

    // Skip the first line (e.g. header)
    if (fgets(linebuf, sizeof(linebuf), file) == NULL) {
        fprintf(stderr, "Error reading user file.\n");
        fclose(file);
        free(username);
        return NULL;
    }

    // Read the second line, which contains the comma‐separated fields
    if (fgets(linebuf, sizeof(linebuf), file) == NULL) {
        fprintf(stderr, "Error reading user file.\n");
        fclose(file);
        free(username);
        return NULL;
    }
    fclose(file);

    // Extract the 5th field (index 4) as the stored password
    {
        int field = 0;
        char *token = strtok(linebuf, ",");
        while (token && field < 4) {
            token = strtok(NULL, ",");
            field++;
        }
        if (!token) {
            fprintf(stderr, "Malformed user file.\n");
            free(username);
            return NULL;
        }
        // Copy and strip newline
        strncpy(stored_password, token, MAX_INPUT_USER - 1);
        stored_password[MAX_INPUT_USER - 1] = '\0';
        stored_password[strcspn(stored_password, "\n")] = '\0';
    }

    // Verify password
    if (strcmp(password, stored_password) != 0) {
        fprintf(stderr, "Incorrect password.\n");
        free(username);
        return NULL;
    }

    // Success!
    return username;
}

void load_courses(const char *filepath, array_ptr *array, hash_map_ptr *hash_map){
    FILE *fp = fopen(filepath, "r");
    CHECK_NULL(fp);

    // Read number of courses
    uint16_t num_of_courses;
    if (fscanf(fp, "%hu\n", &num_of_courses) != 1){
        fprintf(stderr, "Failed to read course count\n");
        fclose(fp);
        exit(1);
    }

    *array = array_create(num_of_courses);
    *hash_map = create_hash_map(num_of_courses);

    char line[LINE_READ_BUFFER];

    for (uint16_t i = 0; i < num_of_courses; i++){
        if (!fgets(line, sizeof line, fp)){
            fprintf(stderr, "Unexpected EOF at line %u\n", i + 2);
            break;
        }

        // Split CSV: id,name,HH:MM DD/MM/YY,seats_total,seats_booked
        char *p = line;
        char *id_str = str_sep(&p, ",");
        char *name_str = str_sep(&p, ",");
        char *dt_str = str_sep(&p, ",");
        char *total_str = str_sep(&p, ",");
        char *booked_str = str_sep(&p, ",;\n");

        // convert fields
        uint16_t id = (uint16_t)atoi(id_str);
        uint16_t seats_total = (uint16_t)atoi(total_str);
        uint16_t seats_booked = (uint16_t)atoi(booked_str);

        datetime_ptr datetime;
        // Parse datetime "HH:MM DD/MM/YYYY"
        int hh, mm, dd, mo, yyyy;
        if (sscanf(dt_str, "%2d:%2d %2d/%2d/%4d", &hh, &mm, &dd, &mo, &yyyy) == 5){
            datetime = create_datetime(mm, hh, dd, mo, yyyy);
        }
        else{
            fprintf(stderr, "Bad datetime format on line: %u\n", i + 2);
            exit(1);
        }

        // Allocate course
        course_ptr course = create_course(
            id,
            str_dup(name_str),
            datetime,
            seats_total,
            seats_booked);
        // add course to array (already sorted in file);
        array_add(*array, course);
        // add course to hash map
        insert_course(*hash_map, get_course_id(course), course);
    }

    fclose(fp);
}

user_ptr load_user(const char *filepath, linked_list_ptr *booked_list, linked_list_ptr *history_list, hash_map_ptr *hash_map){
    FILE *fp = fopen(filepath, "r");
    CHECK_NULL(fp);

    char line[LINE_READ_BUFFER];

    // 1) Read last report date
    if (!fgets(line, sizeof(line), fp)){
        fprintf(stderr, "Failed to read report date\n");
        fclose(fp);
        exit(1);
    }
    int hh, mm, dd, mo, yyyy;
    if (sscanf(line, "%2d:%2d %2d/%2d/%4d", &hh, &mm, &dd, &mo, &yyyy) != 5){
        fprintf(stderr, "Invalid datetime format\n");
        fclose(fp);
        exit(1);
    }
    datetime_ptr last_report_date = create_datetime(mm, hh, dd, mo, yyyy);

    // 2) Read user data
    if (!fgets(line, sizeof(line), fp)){
        fprintf(stderr, "Failed to read user data\n");
        fclose(fp);
        exit(1);
    }
    char *p = line;
    char *cf_str = str_sep(&p, ",");
    char *first_name_str = str_sep(&p, ",");
    char *last_name_str = str_sep(&p, ",");
    char *username_str = str_sep(&p, ",");
    char *password_str = str_sep(&p, ",");
    char *sub_start = str_sep(&p, ",");
    char *sub_end = str_sep(&p, ",;\n");

    sscanf(sub_start, "%2d:%2d %2d/%2d/%4d", &hh, &mm, &dd, &mo, &yyyy);
    datetime_ptr sub_start_date = create_datetime(mm, hh, dd, mo, yyyy);
    sscanf(sub_end, "%2d:%2d %2d/%2d/%4d", &hh, &mm, &dd, &mo, &yyyy);
    datetime_ptr sub_end_date = create_datetime(mm, hh, dd, mo, yyyy);

    subscription_ptr subscription = create_subscription(sub_start_date, sub_end_date);

    // inizializza le liste
    *booked_list = ll_create();
    *history_list = ll_create();

    user_ptr user = create_user(
        str_dup(cf_str),
        str_dup(first_name_str),
        str_dup(last_name_str),
        str_dup(username_str),
        str_dup(password_str),
        subscription,
        last_report_date);

    // 3) Read booked course IDs
    if (!fgets(line, sizeof(line), fp)){
        fprintf(stderr, "Failed to read booked courses\n");
        fclose(fp);
        exit(1);
    }
    p = line;
    while (p && *p){
        char *course_id = str_sep(&p, ",;\n");
        course_ptr course_reference = get_course(*hash_map, (uint16_t)atoi(course_id));

        if (course_reference)
        {
            ll_add(*booked_list, course_reference);
        }
    }

    // 4) Read history as flat CSV: every 3 elementi -> (id, name, times)
    if (!fgets(line, sizeof(line), fp)){
        fprintf(stderr, "Failed to read history\n");
        fclose(fp);
        exit(1);
    }
    p = line;
    while (p && *p){
        char *id_hist = str_sep(&p, ",");
        if (!id_hist || !*id_hist)
            exit(1);
        uint16_t course_id = (uint16_t)atoi(id_hist);

        char *name_hist = str_sep(&p, ",");
        if (!name_hist)
            exit(1);

        // leggo times
        char *times_hist = str_sep(&p, ",;\n");
        if (!times_hist)
            exit(1);
        uint16_t times_booked = (uint16_t)atoi(times_hist);

        frequentation_ptr frequentation = create_frequentation(course_id, str_dup(name_hist), times_booked);

        ll_add(*history_list, frequentation);
    }

    fclose(fp);
    return user;
}

void save_user(char* filepath, linked_list_ptr booked_list, linked_list_ptr history_list, user_ptr user){
    FILE *file = fopen(filepath, "w");
    CHECK_NULL(file);

    // 1) Last report date
    print_datetime(file, get_user_last_report_date(user));
    fprintf(file, "\n");

    // 2) User data
    fprintf(file, "%s,%s,%s,%s,%s,",
        get_user_CF(user),
        get_user_first_name(user),
        get_user_last_name(user),
        get_user_username(user),
        get_user_password(user));
    print_datetime(file, get_subscription_start_date(get_user_subscription(user)));
    fprintf(file, ",");
    print_datetime(file, get_subscription_end_date(get_user_subscription(user)));
    fprintf(file, "\n");

    // 3) Booked courses (if the user is being created write 0,)
    if (ll_get_element_count(booked_list) == 0) {
        fprintf(file, "0,");
    } else {
        ll_print(booked_list, file, save_booking_callback);
    }
    fprintf(file, "\n");

    // 4) Booked history (if the user is being created write "0,,0,")
    if (ll_get_element_count(history_list) == 0) {
        fprintf(file, "0,"",0,");
    } else {
        ll_print(history_list, file, save_frequentation_callback);
    }

    fclose(file);
}

void save_course(char* filepath, array_ptr array){    
    FILE *file = fopen(filepath, "w");
    CHECK_NULL(file);

    fprintf(file, "%d\n", get_size(array));

    array_print(array, file, print_course_file_callback);

    fclose(file);
}

void registration_user() {
    char cf[MAX_INPUT_USER];
    char first_name[MAX_INPUT_USER];
    char last_name[MAX_INPUT_USER];
    char username[MAX_INPUT_USER];
    char password[MAX_INPUT_USER];
    char filepath[192];
    FILE *file;

    printf("=== New User Registration ===\n");

    // Read CF
    printf("Enter CF: ");
    if (fgets(cf, sizeof(cf), stdin) == NULL) {
        fprintf(stderr, "Failed to read CF.\n");
        return;
    }
    cf[strcspn(cf, "\n")] = '\0';

    // Read first name
    printf("Enter first name: ");
    if (fgets(first_name, sizeof(first_name), stdin) == NULL) {
        fprintf(stderr, "Failed to read first name.\n");
        return;
    }
    first_name[strcspn(first_name, "\n")] = '\0';

    // Read last name
    printf("Enter last name: ");
    if (fgets(last_name, sizeof(last_name), stdin) == NULL) {
        fprintf(stderr, "Failed to read last name.\n");
        return;
    }
    last_name[strcspn(last_name, "\n")] = '\0';

    // Choose username
    printf("Choose a username: ");
    if (fgets(username, sizeof(username), stdin) == NULL) {
        fprintf(stderr, "Failed to read username.\n");
        return;
    }
    username[strcspn(username, "\n")] = '\0';

    // Check if username already exists
    snprintf(filepath, sizeof(filepath), "%s%s.txt", USERS_PATH, username);
    file = fopen(filepath, "r");
    if (file) {
        fclose(file);
        fprintf(stderr, "Error: Username '%s' already exists.\n", username);
        return;
    }

    // Read password
    printf("Choose a password: ");
    if (fgets(password, sizeof(password), stdin) == NULL) {
        fprintf(stderr, "Failed to read password.\n");
        return;
    }
    password[strcspn(password, "\n")] = '\0';

    // Prepare subscription dates
    datetime_ptr now = get_datetime();
    datetime_ptr start = create_datetime(
            00,
            00,
            get_datetime_field(now, "day"),
            get_datetime_field(now,"month"),
            get_datetime_field(now,"year")
        );
    // Set subscription end date to day 1st of next month
    datetime_ptr end = create_datetime(
        59,
        23,
        1,
        (get_datetime_field(now, "month") + 1) % 12,
        get_datetime_field(now, "year")
    );
    subscription_ptr sub = create_subscription(start, end);

    // Create user struct
    user_ptr new_user = create_user(
        str_dup(cf),
        str_dup(first_name),
        str_dup(last_name),
        str_dup(username),
        str_dup(password),
        sub,
        now
    );

    // Initialize empty lists
    linked_list_ptr booked_list = ll_create();
    linked_list_ptr history_list = ll_create();
    
    char user_filepath[192] = {0};
    snprintf(user_filepath, sizeof(user_filepath), "assets/users/%s.txt", get_user_username(new_user));
    // Save to file
    save_user(user_filepath, booked_list, history_list, new_user);

    printf("Registration successful. User '%s' created.\n", username);
    
    delete_user(new_user);
    ll_delete_list(booked_list, NULL);
    ll_delete_list(history_list, NULL);
}

void report(char* filepath, user_ptr user, linked_list_ptr frequentation_linked_list) {
    datetime_ptr last_report_datetime = get_user_last_report_date(user);
    datetime_ptr now = get_datetime();
    datetime_ptr current_datetime = create_datetime(
            00,
            00,
            get_datetime_field(now, "day"),
            get_datetime_field(now,"month"),
            get_datetime_field(now,"year")
        );
    
    int flag_year = get_datetime_field(last_report_datetime, "year") 
        <= 
        get_datetime_field(current_datetime, "year");
    int flag_month = get_datetime_field(last_report_datetime, "month") 
        <
        get_datetime_field(current_datetime, "month");
    
    if (!flag_year || !flag_month) return;
    
    // create flag
    FILE* file = fopen(filepath, "w");
    CHECK_NULL(file);

    int array_size = ll_get_element_count(frequentation_linked_list);
    array_ptr temp_array = array_create(array_size);
    ll_copy_list_to_array(frequentation_linked_list, temp_array);
    
    for (int i = 0; i < array_size - 1; i++) {
        // After each full pass, the largest element among the first (n-i) is at position n-i-1
        for (int j = 0; j < array_size - i - 1; j++) {
            frequentation_ptr* element1 = (frequentation_ptr*)get_at(temp_array, j);
            frequentation_ptr* element2 = (frequentation_ptr*)get_at(temp_array, j + 1);
            if (get_frequentation_times_booked(*element1) < get_frequentation_times_booked(*element2)) {
                ptr_swap((void**)element1, (void**)element2);
            }
        }
    }

    // set new last report datetime
    set_user_last_report_date(user, current_datetime);

    // print datetime for this report
    print_datetime(file, current_datetime);
    fprintf(file, "\n");

    int i = 0;
    frequentation_ptr* fr;
    fprintf(file, "Top tree courses followed:\n");
    while(i < array_size && i < 3) {
        fr = (frequentation_ptr*)get_at(temp_array, i);
        print_frequentation_callback(file, *fr);
        i++;
    }
    fprintf(file, "Other courses:\n");
    while(i < array_size) {
        fr = (frequentation_ptr*)get_at(temp_array, i);
        print_frequentation_callback(file, *fr);
        i++;
    }

    array_delete(temp_array, NULL);
    fclose(file);
}