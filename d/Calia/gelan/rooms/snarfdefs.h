#define BS(str) break_string(str, 75)
#define CWD dirname(explode(file_name(this_object()), "#")[0]) + "/"
#define CUR_DIR CWD

string
dirname(string path)
{
    string *a;
    string apa;

    a = explode(path, "/");
    a[sizeof(a)-1] = 0;
    apa = "/" + implode(a, "/");
    return apa;
}
