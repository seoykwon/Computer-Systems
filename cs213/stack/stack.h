#pragma once

struct stack_element;

//struct stack_element* push(int val);

struct stack_element* push(int val);
int pop();
int get_value(struct stack_element* e);
