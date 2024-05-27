#pragma once

int* resize(int* vec, int old_size, int new_size);
int* removeItem(int* vec, int vec_size, int item_pos);
int* insertItem(int* vec, int vec_size, int insert_pos, int insert_value);
int* concat(int* vec_left, int left_size, int* vec_right, int right_size);
int min(int a, int b);
