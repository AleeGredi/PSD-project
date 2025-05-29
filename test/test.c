#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "main_functions.h"

#define MAX_LINE_LEN 1024

int compare_files(const char *path1, const char *path2);
void booking_test(int test_case_type, int id);
void subscription_test(int test_case_type, int id);
void report_test(int test_case_type, int id);

int main(int argc, char* argv[]) {
    FILE *test_suite;
    int test_case_type;
    int id;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <test-suite-file>\n", argv[0]);
        exit(1);
    }

    test_suite = fopen(argv[1], "r");
    CHECK_NULL(test_suite);

    // Read the first integer as the type
    if (fscanf(test_suite, "%d", &test_case_type) != 1) {
        fprintf(stderr, "Failed to read test_case_type\n");
        fclose(test_suite);
        exit(1);
    }
    // printf("Test case type: %d\n", test_case_type);
    
    char result_filepath[256];
    sprintf(result_filepath, "test/%d/%d_test_result.txt", test_case_type, test_case_type);
    FILE* result_file = fopen(result_filepath, "w");
    CHECK_NULL(result_file);
    fclose(result_file);

    // Then read all subsequent values as IDs
    while (fscanf(test_suite, "%d", &id) == 1) {
        printf("Test case ID: %d\n", id);
        switch (test_case_type) {
            case 1:
                booking_test(test_case_type, id);
                break;
            case 2:
                subscription_test(test_case_type, id);
                break;
            case 3:
                report_test(test_case_type, id);
                break;
            default:
                break;
        }
    }

    fclose(test_suite);
    return 0;
}

int compare_files(const char *path1, const char *path2) {
    FILE *f1 = fopen(path1, "r");
    FILE *f2 = fopen(path2, "r");
    CHECK_NULL(f1);
    CHECK_NULL(f2);

    char line1[MAX_LINE_LEN];
    char line2[MAX_LINE_LEN];
    int line_num = 1;

    while (fgets(line1, sizeof(line1), f1) && fgets(line2, sizeof(line2), f2)) {
        if (strcmp(line1, line2) != 0) {
            // Files differ
            fclose(f1);
            fclose(f2);
            return 1;
        }
        line_num++;
    }

    // Check if one file has extra lines
    if (fgets(line1, sizeof(line1), f1) || fgets(line2, sizeof(line2), f2)) {
        // Files differ in length (one has extra lines).
        fclose(f1);
        fclose(f2);
        return 1;
    }

    fclose(f1);
    fclose(f2);
    // Files are identical
    return 0;
}

void booking_test(int test_case_type, int id) {
    hash_map_ptr hash_map = NULL;
    array_ptr array = NULL;
    user_ptr user = NULL;
    linked_list_ptr booked_list = NULL;
    linked_list_ptr history_list = NULL;

    char course_filepath[256];
    sprintf(course_filepath, "test/%d/%d-%d_course.txt",test_case_type, test_case_type, id);
    char user_filepath[256];
    sprintf(user_filepath, "test/%d/%d-%d_user.txt",test_case_type, test_case_type, id);

    load_courses(course_filepath, &array, &hash_map);
    user = load_user(user_filepath, &booked_list, &history_list, &hash_map);

    char course_oracle_filepath[256];
    sprintf(course_oracle_filepath, "test/%d/%d-%d_course_oracle.txt",test_case_type, test_case_type, id);
    char user_oracle_filepath[256];
    sprintf(user_oracle_filepath, "test/%d/%d-%d_user_oracle.txt",test_case_type, test_case_type, id);

    // the course id is the same id of the test case
    action_book_course(id, booked_list, history_list, hash_map, user);
    
    char course_output_filepath[256];
    sprintf(course_output_filepath, "test/%d/%d-%d_course_output.txt",test_case_type, test_case_type, id);
    char user_output_filepath[256];
    sprintf(user_output_filepath, "test/%d/%d-%d_user_output.txt",test_case_type, test_case_type, id);
    
    save_user(user_output_filepath, booked_list, history_list, user);
    save_course(course_output_filepath, array);
    array_delete(array, NULL);
    ll_delete_list(booked_list, NULL);
    ll_delete_list(history_list, NULL);
    delete_hash_map(hash_map, true);
    
    // check if output equal oracle
    int course_test = !compare_files(course_output_filepath, course_oracle_filepath);
    int user_test = !compare_files(user_output_filepath, user_oracle_filepath);

    char result_filepath[256];
    sprintf(result_filepath, "test/%d/%d_test_result.txt", test_case_type, test_case_type);
    FILE* result_file = fopen(result_filepath, "a");
    CHECK_NULL(result_file);
    fprintf(result_file, "test:%d = %s\n", id, course_test && user_test ? "PASS" : "NOT PASS");

    fclose(result_file);
}

void subscription_test(int test_case_type, int id) {
    hash_map_ptr hash_map = NULL;
    array_ptr array = NULL;
    user_ptr user = NULL;
    linked_list_ptr booked_list = NULL;
    linked_list_ptr history_list = NULL;

    char course_filepath[256];
    sprintf(course_filepath, "test/%d/%d-%d_course.txt",test_case_type, test_case_type, id);
    load_courses(course_filepath, &array, &hash_map);

    char user_filepath[256];
    sprintf(user_filepath, "test/%d/%d-%d_user.txt", test_case_type, test_case_type, id);
    user = load_user(user_filepath, &booked_list, &history_list, &hash_map);

    char user_oracle_filepath[256];
    sprintf(user_oracle_filepath, "test/%d/%d-%d_user_oracle.txt", test_case_type, test_case_type, id);

    char user_output_filepath[256];
    sprintf(user_output_filepath, "test/%d/%d-%d_user_output.txt", test_case_type, test_case_type, id);

    action_check_subscription(user);

    save_user(user_output_filepath, booked_list, history_list, user);

    ll_delete_list(booked_list, NULL);
    ll_delete_list(history_list, NULL);
    delete_hash_map(hash_map, true);

    // Compare output to oracle
    int subscription_test = !compare_files(user_oracle_filepath, user_output_filepath);

    char result_filepath[256];
    sprintf(result_filepath, "test/%d/%d_test_result.txt", test_case_type, test_case_type);
    FILE* result_file = fopen(result_filepath, "a");
    CHECK_NULL(result_file);
    fprintf(result_file, "test:%d = %s\n", id, subscription_test ? "PASS" : "NOT PASS");
    
    fclose(result_file);
    
}

void report_test(int test_case_type, int id) {
    hash_map_ptr hash_map = NULL;
    array_ptr array = NULL;
    user_ptr user = NULL;
    linked_list_ptr booked_list = NULL;
    linked_list_ptr history_list = NULL;

    char course_filepath[256];
    sprintf(course_filepath, "test/%d/%d-%d_course.txt",test_case_type, test_case_type, id);
    load_courses(course_filepath, &array, &hash_map);

    char user_filepath[256];
    sprintf(user_filepath, "test/%d/%d-%d_user.txt", test_case_type, test_case_type, id);
    user = load_user(user_filepath, &booked_list, &history_list, &hash_map);

    char user_oracle_filepath[256];
    sprintf(user_oracle_filepath, "test/%d/%d-%d_user_oracle.txt", test_case_type, test_case_type, id);

    char user_output_filepath[256];
    sprintf(user_output_filepath, "test/%d/%d-%d_user_output.txt", test_case_type, test_case_type, id);

    char report_oracle_filepath[256];
    sprintf(report_oracle_filepath, "test/%d/%d-%d_report_oracle.txt", test_case_type, test_case_type, id);

    char report_output_filepath[256];
    sprintf(report_output_filepath, "test/%d/%d-%d_report_output.txt", test_case_type, test_case_type, id);

    report(report_output_filepath, user, history_list);
    save_user(user_output_filepath, booked_list, history_list, user);

    ll_delete_list(booked_list, NULL);
    ll_delete_list(history_list, NULL);
    delete_hash_map(hash_map, true);

    // Compare output to oracle
    int report_test = !compare_files(report_oracle_filepath, report_output_filepath);
    int user_test = !compare_files(user_oracle_filepath, user_output_filepath);
    
    char result_filepath[256];
    sprintf(result_filepath, "test/%d/%d_test_result.txt", test_case_type, test_case_type);
    FILE* result_file = fopen(result_filepath, "a");
    CHECK_NULL(result_file);
    fprintf(result_file, "test:%d = %s\n", id, report_test && user_test ? "PASS" : "NOT PASS");
    fclose(result_file);
    
}