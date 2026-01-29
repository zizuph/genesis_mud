
#include <composite.h>
#include <language.h>

string *Save_Data = ({ "First Entry", "Second Entry", });

public string *
query_save_data()
{
    return Save_Data;
}

public void
print_data()
{
    int     i = -1;
    string *data;

    data = this_object()->query_save_data();

    while (++i < sizeof(data))
	data[i] = lower_case(data[i]);

    // data = map(data, lower_case);

    write(COMPOSITE_WORDS(data) + "\n");
}

public void
func_b(string *foo)
{
    if (sizeof(foo))
    foo[0] = "FOO";
}

public void
func_a()
{
    string *fdat = ({ "a", "b", "c", "d", });

    func_b(fdat);

    dump_array(fdat);
}

public void
func_d(int foo)
{
    foo = 5;
}

public void
func_c()
{
    int bar = 1;
    func_d(bar);
    dump_array(bar);
}
