inherit "/std/object";
#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>

void create_object()
{
    set_name("test");
    set_short("sorter test");
    add_name("object");
    set_long("sorter object.\n");
}

void init()
{
    add_action("sort_inv", "sort");
    ::init();
}

int special_sort(object obj1, object obj2)
{
    int a = obj1->query_prop(OBJ_I_WEIGHT);
    int b = obj2->query_prop(OBJ_I_WEIGHT);

    if (a == b)
	return 0;
    else if (a < b)
	return -1;
    else if (a > b)
	return 1;
}

int sort_inv(string str)
{
    object *all = all_inventory(environment(this_object()));
    object *list;
    int i;

    NF("No inventory.\n");
    if (!sizeof(all))
	return 0;

    list = sort_array(all, "special_sort");

    for (i = 0; i < sizeof(list); i++)
	write(list[i]->short()+"\n");
    return 1;
}

