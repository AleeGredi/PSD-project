#ifndef MAIN_FUNCTION_H
#define MAIN_FUNCTION_H

#include "array.h"
#include "linked_list.h"
#include "hash_map.h"
#include "frequentation.h"
#include "course.h"
#include "user.h"
#include "utils.h"
#include <errno.h>
#include <string.h>

#define LINE_READ_BUFFER 1024
#define MAX_INPUT_USER 128
#define USERS_PATH "assets/users/"
#define COURSE_PATH "assets/courses.txt"
#define REPORT_PATH "assets/report/"

void action_print_all_courses(array_ptr array);
void action_show_booked_courses(linked_list_ptr booked_list);
void action_show_history(linked_list_ptr history_list);
void action_book_course(int course_id, linked_list_ptr booked_list, linked_list_ptr history_list, hash_map_ptr hash_map, user_ptr user);
void action_cancel_course(linked_list_ptr booked_list, linked_list_ptr history_list);
void action_check_subscription(user_ptr user);
void action_show_last_report(user_ptr user);
void action_exit_and_save(hash_map_ptr map, array_ptr array, linked_list_ptr booked, linked_list_ptr history, user_ptr user);
char *login_user();
void load_courses(const char *filepath, array_ptr *array, hash_map_ptr *hash_map);
user_ptr load_user(const char *filepath, linked_list_ptr *booked_list, linked_list_ptr *history_list, hash_map_ptr *hash_map);
void save_user(char* filepath, linked_list_ptr booked_list, linked_list_ptr history_list, user_ptr user);
void registration_user();
void save_course(char* filepath, array_ptr array);
void report(user_ptr user, linked_list_ptr frequentation_linked_list);

#endif 
