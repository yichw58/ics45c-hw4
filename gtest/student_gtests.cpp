#include <gtest/gtest.h>
#include <string.h>

#include <algorithm>

#include "string.hpp"
#include "alloc.hpp"

TEST(StringFunction, strlen) {
    EXPECT_EQ(String::strlen(""), 0);
    EXPECT_EQ(String::strlen("foo"), 3);
}

TEST(StringFunction, strcpy) {
    char result[10];
    EXPECT_EQ(String::strcpy(result, "foo"), result);
    EXPECT_STREQ(result, "foo");

    EXPECT_EQ(String::strcpy(result, "a"), result);
    EXPECT_STREQ(result, "a");

    EXPECT_EQ(String::strcpy(result, ""), result);
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, strdup) {
    char original[] = "Hello";
    char *copy = String::strdup(original);

    EXPECT_STREQ(copy, "Hello");
    EXPECT_NE(copy, original);
    original[0] = 'Y';
    EXPECT_STREQ(copy, "Hello");

    delete[] copy;

    char *empty = String::strdup("");
    EXPECT_STREQ(empty, "");
    delete[] empty;
}

TEST(StringFunction, strncpy) {
    char result[10];

    EXPECT_EQ(String::strncpy(result, "Hello", 5), result);
    EXPECT_STREQ(result, "Hello");

    EXPECT_EQ(String::strncpy(result, "Hello", 3), result);
    EXPECT_STREQ(result, "Hel");

    EXPECT_EQ(String::strncpy(result, "Cat", 8), result);
    EXPECT_STREQ(result, "Cat");

    EXPECT_EQ(String::strncpy(result, "Apple", 0), result);
    EXPECT_STREQ(result, "");

    EXPECT_EQ(String::strncpy(result, "", 5), result);
    EXPECT_STREQ(result, "");

}

TEST(StringFunction, strcat) {
    char result[30] = "Hello";

    EXPECT_EQ(String::strcat(result, "World"), result);
    EXPECT_STREQ(result, "HelloWorld");

    EXPECT_EQ(String::strcat(result, "!"), result);
    EXPECT_STREQ(result, "HelloWorld!");

    char empty[20] = "";
    EXPECT_EQ(String::strcat(empty, "Apple"), empty);
    EXPECT_STREQ(empty, "Apple");

    char unchanged[20] = "Cat";
    EXPECT_EQ(String::strcat(unchanged, ""), unchanged);
    EXPECT_STREQ(unchanged, "Cat");

    char punctuation[20] = "a,b";
    EXPECT_EQ(String::strcat(punctuation, "!?"), punctuation);
    EXPECT_STREQ(punctuation, "a,b!?");
}


TEST(StringFunction, strncat) {
    char result[20] = "Hello";

    EXPECT_EQ(String::strncat(result, "World", 3), result);
    EXPECT_STREQ(result, "HelloWor");

    char zero[20] = "Cat";
    EXPECT_EQ(String::strncat(zero, "Dog", 0), zero);
    EXPECT_STREQ(zero, "Cat");

    char longer[20] = "Hi";
    EXPECT_EQ(String::strncat(longer, "!", 5), longer);
    EXPECT_STREQ(longer, "Hi!");

    char exact[20] = "A";
    EXPECT_EQ(String::strncat(exact, "BC", 2), exact);
    EXPECT_STREQ(exact, "ABC");

    char empty[20] = "";
    EXPECT_EQ(String::strncat(empty, "Apple", 3), empty);
    EXPECT_STREQ(empty, "App");

    char unchanged[20] = "Test";
    EXPECT_EQ(String::strncat(unchanged, "", 4), unchanged);
    EXPECT_STREQ(unchanged, "Test");
}


TEST(StringFunction, strcmp) {
    EXPECT_EQ(String::strcmp("Hello", "Hello"), 0);
    EXPECT_EQ(String::strcmp("", ""), 0);

    EXPECT_LT(String::strcmp("apple", "banana"), 0);
    EXPECT_GT(String::strcmp("cat", "car"), 0);

    EXPECT_LT(String::strcmp("cat", "cats"), 0);
    EXPECT_GT(String::strcmp("cats", "cat"), 0);

    EXPECT_LT(String::strcmp("", "a"), 0);
    EXPECT_GT(String::strcmp("a", ""), 0);

    EXPECT_LT(String::strcmp("Apple", "apple"), 0);
    EXPECT_EQ(String::strcmp("a!b", "a!b"), 0);
}

TEST(StringFunction, strncmp) {
    EXPECT_EQ(String::strncmp("Hello", "Hello", 5), 0);
    EXPECT_EQ(String::strncmp("", "", 5), 0);

    EXPECT_EQ(String::strncmp("apple", "application", 3), 0);
    EXPECT_EQ(String::strncmp("cat", "car", 2), 0);

    EXPECT_GT(String::strncmp("cat", "car", 3), 0);
    EXPECT_GT(String::strncmp("dog", "cat", 3), 0);

    EXPECT_EQ(String::strncmp("Hello", "World", 0), 0);

    EXPECT_LT(String::strncmp("cat", "cats", 4), 0);
    EXPECT_GT(String::strncmp("cats", "cat", 4), 0);

    EXPECT_LT(String::strncmp("", "abc", 3), 0);
    EXPECT_GT(String::strncmp("abc", "", 3), 0);

    EXPECT_EQ(String::strncmp("abc", "abcXYZ", 3), 0);
    EXPECT_LT(String::strncmp("apple", "banana", 5), 0);
}

TEST(StringFunction, reverse_cpy) {
    char result[30];

    String::reverse_cpy(result, "Hello");
    EXPECT_STREQ(result, "olleH");

    String::reverse_cpy(result, "abcd");
    EXPECT_STREQ(result, "dcba");

    String::reverse_cpy(result, "a");
    EXPECT_STREQ(result, "a");

    String::reverse_cpy(result, "");
    EXPECT_STREQ(result, "");

    String::reverse_cpy(result, "a!b");
    EXPECT_STREQ(result, "b!a");

    String::reverse_cpy(result, "123456");
    EXPECT_STREQ(result, "654321");

    String::reverse_cpy(result, "racecar");
    EXPECT_STREQ(result, "racecar");
}

TEST(StringFunction, strchr) {
    const char *word = "Hello";

    EXPECT_EQ(String::strchr(word, 'H'), word);
    EXPECT_EQ(String::strchr(word, 'l'), word + 2);
    EXPECT_EQ(String::strchr(word, 'o'), word + 4);

    EXPECT_EQ(String::strchr(word, 'z'), nullptr);
    EXPECT_EQ(String::strchr(word, '\0'), word + 5);

    const char *empty = "";
    EXPECT_EQ(String::strchr(empty, 'a'), nullptr);
    EXPECT_EQ(String::strchr(empty, '\0'), empty);

    const char *repeated = "banana";
    EXPECT_EQ(String::strchr(repeated, 'a'), repeated + 1);
    EXPECT_EQ(String::strchr(repeated, 'n'), repeated + 2);

    const char *symbols = "a!b?";
    EXPECT_EQ(String::strchr(symbols, '!'), symbols + 1);
}

TEST(StringFunction, strstr) {
    const char *text = "HelloWorld";

    EXPECT_EQ(String::strstr(text, "Hello"), text);
    EXPECT_EQ(String::strstr(text, "World"), text + 5);
    EXPECT_EQ(String::strstr(text, "loW"), text + 3);

    EXPECT_EQ(String::strstr(text, "XYZ"), nullptr);
    EXPECT_EQ(String::strstr(text, "HelloWorld!"), nullptr);
    EXPECT_EQ(String::strstr(text, ""), text);

    const char *empty = "";
    EXPECT_EQ(String::strstr(empty, ""), empty);
    EXPECT_EQ(String::strstr(empty, "a"), nullptr);

    const char *repeated = "banana";
    EXPECT_EQ(String::strstr(repeated, "ana"), repeated + 1);

    const char *overlap = "aaaab";
    EXPECT_EQ(String::strstr(overlap, "aab"), overlap + 2);

    EXPECT_EQ(String::strstr("abc", "abcd"), nullptr);

    const char *same = "test";
    EXPECT_EQ(String::strstr(same, "test"), same);

    const char *symbols = "hello!world";
    EXPECT_EQ(String::strstr(symbols, "!w"), symbols + 5);
}