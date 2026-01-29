inherit "/std/container";

#include <stdproperties.h>

private static int table_size;

void
create_container()
{
    set_name("table");
    add_adj("dining-room");

    set_long("This is a dining room table.\n");

    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_MAX_VOLUME, 400000);
    add_prop(CONT_I_MAX_WEIGHT, 300000);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 200000);
}

public void
set_table_size(int size)
{
    table_size = size;
}

public int
query_table_size()
{
    return table_size;
}

public string *
query_diners()
{
    return query_sublocs();
}

public int
add_diner(object diner)
{
    string *diners = query_diners();
    string name = diner->query_real_name();

    if (member_array(name, diners) < 0)
    {
        if (sizeof(diners) >= table_size)
        {
	    return 0;
	}

	add_subloc(name, this_object());
	return 1;
    }

    // Diner was previously added
    return 1;
}

public void
remove_diner(object diner)
{
    remove_subloc(diner->query_real_name());
}

