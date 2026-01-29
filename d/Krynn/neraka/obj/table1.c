/*
 * Table in sleeping inn, made by Nick
 */

inherit "/std/container";
#include "../local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>

void
create_container()
{
    set_name("table");
    set_adj("wooden");
    set_no_show_composite(1);

    set_long("@@my_long");
    add_prop(CONT_I_IN, 0);
    add_prop(OBJ_M_NO_GET, 1);
    enable_reset();

    seteuid(getuid());
    if (IS_CLONE)
      set_alarm(1.0,0.0,"reset_container");
}

void
reset_container()
{
    object *arr;
    int i;

    arr = all_inventory();
    for (i = sizeof(arr); i <= 3; i++)
	clone_object(OBJ + "lazy_beer")->move(TO, 1);
}

string
my_long()
{
    string str;
    object *arr;

    str = "The tables are covered with dust but some of the people in here " +
	"still use them to sleep against. ";
    arr = all_inventory();
    if (!sizeof(arr))
	str += "A few bottles are standing on the tables, but none close " +
	    "enough for you to reach.";
    else
	str += "There are some bottles standing on the tables that you " +
	    "might be able to reach.";

    return BS(str, SL);
}

