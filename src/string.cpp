#include "string.hpp"
#include <iostream>
#include <utility>

char *String::strncpy(char *dest, const char *src, int n){
    int i = 0;
    for (; i < n && src[i] != '\0'; i++){
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}

char *String::strcpy(char *dest, const char *src)
{
    int i = 0;

    for (; src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }

    dest[i] = '\0';
    return dest;
}

int String::strlen(const char *s)
{
    int length = 0;
    for (int i = 0; s[i] != '\0'; i++){
        length += 1;
    }
    return length;

}

char *String::strdup(const char *src)
{
    int length = strlen(src);
    char *copy = new char[length + 1];
    strcpy(copy, src);
    return copy;
}

//Constructor 
String::String(const char *s)
{
    buf = strdup(s);
}

String::String(const String &s)
{
    buf = strdup(s.buf);
}

String::String(int length)
{
    buf = new char[length + 1];
}

String::String(String &&s)
{
    buf = s.buf;
    s.buf = nullptr;
}

//Destructor
String::~String()
{
    delete[] buf;
}

void String::swap(String &s)
{
    std::swap(buf, s.buf);
}

int String::size() const
{
    return strlen(buf);
}

void String::print(std::ostream &out) const
{
    out << buf;
}

std::ostream &operator<<(std::ostream &out, const String &s)
{
    s.print(out);
    return out;
}

char *String::strcat(char *dest, const char *src)
{
    int i = strlen(dest);
    int j = 0;

    for (; src[j] != '\0'; j++)
    {
        dest[i + j] = src[j];
    }

    dest[i + j] = '\0';

    return dest;
}

char *String::strncat(char *dest, const char *src, int n)
{
    int i = strlen(dest);
    int j = 0;

    for (; j < n && src[j] != '\0'; j++)
    {
        dest[i + j] = src[j];
    }

    dest[i + j] = '\0';
    return dest;
}

String &String::operator=(String s)
{
    swap(s);
    return *this;
}

int String::strcmp(const char *left, const char *right)
{
    int i = 0;

    while (left[i] != '\0' && right[i] != '\0')
    {
        if (left[i] != right[i])
        {
            return left[i] - right[i];
        }

        i++;
    }

    return left[i] - right[i];
}

int String::strncmp(const char *left, const char *right,int n)
{
    int i = 0;

    while (i < n && left[i] != '\0' && right[i] != '\0')
    {
        if (left[i] != right[i])
        {
            return left[i] - right[i];
        }

        i++;
    }

    if (i == n)
    {
        return 0;
    }

    return left[i] - right[i];
}

// Comparison Operators
bool String::operator==(const String &s) const
{
    return strcmp(buf, s.buf) == 0;
}

bool String::operator!=(const String &s) const
{
    return strcmp(buf, s.buf) != 0;
}

bool String::operator<=(const String &s) const
{
    return strcmp(buf, s.buf) <= 0;
}

bool String::operator>=(const String &s) const
{
    return strcmp(buf, s.buf) >= 0;
}

bool String::operator<(const String &s) const
{
    return strcmp(buf, s.buf) < 0;
}

bool String::operator>(const String &s) const
{
    return strcmp(buf, s.buf) > 0;
}

void String::reverse_cpy(char *dest, const char *src)
{
    int src_len = strlen(src);
    int src_index = src_len - 1;
    int dest_index = 0;
    for (;dest_index < src_len; dest_index++, src_index--){
        dest[dest_index] = src[src_index];
    }
    dest[dest_index] = '\0';
}

String String::reverse() const
{
    String result(strlen(buf));

    reverse_cpy(result.buf, buf);

    return result;
}

const char *String::strchr(const char *str, char c)
{
    int i = 0;

    while (str[i] != '\0')
    {
        if (str[i] == c)
        {
            return &str[i];
        }

        i++;
    }

    if (c == '\0')
    {
        return &str[i];
    }

    return nullptr;
}

int String::indexOf(char c) const
{
    const char *found = strchr(buf, c);

    if (found == nullptr)
    {
        return -1;
    }

    return found - buf;
}

const char *String::strstr(const char *haystack, const char *needle)
{
    if (needle[0] == '\0')
    {
        return haystack;
    }

    int len = strlen(needle);

    for (const char *p = haystack; (p = strchr(p, needle[0])); ++p)
    {
        if (strncmp(p, needle, len) == 0)
        {
            return p;
        }
    }

    return nullptr;
}

int String::indexOf(const String &s) const
{
    const char *found = strstr(buf, s.buf);

    if (found == nullptr)
    {
        return -1;
    }

    return found - buf;
}

char &String::operator[](int index)
{
    if (!in_bounds(index))
    {
        std::cerr << "ERROR: Index Out Of Bounds\n";
        return buf[0];
    }

    return buf[index];
}

const char &String::operator[](int index) const
{
    if (!in_bounds(index))
    {
        std::cerr << "ERROR: Index Out Of Bounds\n";
        return buf[0];
    }

    return buf[index];
}

String &String::operator+=(const String &s)
{
    int current_len = strlen(buf);
    int added_len = strlen(s.buf);

    char *newBuf = new char[current_len + added_len + 1];

    strcpy(newBuf, buf);
    strcat(newBuf, s.buf);

    delete[] buf;
    buf = newBuf;

    return *this;
}

String String::operator+(const String &s) const
{
    int total_len = strlen(buf) + strlen(s.buf);

    String result(total_len);

    strcpy(result.buf, buf);
    strcat(result.buf, s.buf);

    return result;
}

void String::read(std::istream &in)
{
    char temp[1024];

    in.width(1024);
    if (in >> temp)
    {
        char *newBuf = strdup(temp);

        delete[] buf;
        buf = newBuf;
    }
}

std::istream &operator>>(std::istream &in, String &s)
{
    s.read(in);
    return in;
}