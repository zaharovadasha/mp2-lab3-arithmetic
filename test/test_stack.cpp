// тесты для стека

#include "stack.h"
#include <gtest.h>
	class TestStacks : public ::testing::Test {
 protected:
 	Stack<int> stk;
 public:
 	TestStacks() : stk(10) {
 		for (int i = 0; i < stk.getSize(); i++)
 			stk.push(i);	
 	}
 	~TestStacks() {}
 };
 
 
 TEST(Stack, can_create_stack_with_positive_lenght)
 {
 	ASSERT_NO_THROW(Stack<int> st(5));
 }
 
TEST(Stack, can_create_stack_with_lenght_more_max)
 {
 ASSERT_ANY_THROW(Stack<int> st(60000));
 }
 
 TEST(Stack, can_create_stack_with_negative_lenght)
 {
 	ASSERT_ANY_THROW(Stack<int> st(-5));
 }
 
TEST(Stack, can_not_delete_if_stack_is_empty)
 {
 	Stack<int> st;
 	ASSERT_ANY_THROW(st.pop());
 }
 
 TEST_F(TestStacks, can_get_quantity)
 {
 	EXPECT_EQ(10, stk.getSize());
 }
 
 TEST_F(TestStacks, can_push_element_and_view_top)
 {
 	stk.push(0);
	EXPECT_EQ(11, stk.getTop());
 	EXPECT_EQ(0, stk.view());
 }
 
 TEST_F(TestStacks, can_pop_element)
 {
 	int s = stk.pop();
 	EXPECT_EQ(9, s);
	EXPECT_EQ(9, stk.getTop()); 

 }
 TEST(Stack, can_push_element_with_too_large_index)
{
Stack <int> st(1);
st.push(2);
ASSERT_NO_THROW(st.push(3));
}

TEST(Stack, can_pop_value)
{
Stack <int> a;
a.push(5);
EXPECT_EQ(5,a.pop());
}

 TEST_F(TestStacks, can_check_emptiness)
 {
 	EXPECT_EQ(false, stk.isempty());
 }
 
 TEST_F(TestStacks, can_clean_steck)
 {
 	stk.clear();
 	EXPECT_EQ(true, stk.isempty());
 }

 