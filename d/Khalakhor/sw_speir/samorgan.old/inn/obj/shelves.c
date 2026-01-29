/**********************************************************************
 * - shelves.c                                                      - *
 * - Simple container that players may use while in the Inn.        - *
 * - Created by Damaris@Genesis 08/2006                             - *
 **********************************************************************/
#pragma strict_types

inherit "/std/container";
#include <stdproperties.h>
#include "/d/Khalakhor/sys/basic.h"
#include "../inn.h"

string
query_sign()
{
    return("\n"+
    "          *------------------*` - - `*------------------*\n"+
    "          | ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` |\n"+
    "          | `                                         ` |\n"+
    "          | `  You may use the items on the shelves.  ` |\n"+
    "          | `                                         ` |\n"+
    "          | `  You may express your emotions freely.  ` |\n"+
    "          | `                                         ` |\n"+
    "          | `  You may <sit> in tub or on bench, or   ` |\n"+
    "          | `                                         ` |\n"+
    "          | `  on another person if they are seated.  ` |\n"+
    "          | `                                         ` |\n"+
    "          | ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` |\n"+
    "          *------------------*` - - `*------------------*\n");
}
void
create_container()
{
	seteuid(getuid(TO));
	set_name("shelves");
        add_name(({"shelf", "inn:shelves"}));
        set_short("long wooden shelves");
        add_adj(({"long", "wooden"}));
        set_long("These are long wooden shelves along the wall. There "+
        "is a highly polished brass sign with flowing script dangling "+
        "from it.\n");
        add_item(({"script", "flowing script", "sign", "small sign", "brass sign"}), query_sign);
	add_cmd_item(({"script", "flowing script", "sign", "small sign", "brass sign"}),"read", query_sign);
	set_no_show_composite(1);
	
        add_prop(CONT_I_CLOSED,0);
        add_prop(CONT_I_MAX_WEIGHT, 500000);
        add_prop(CONT_I_MAX_VOLUME, 500000);
        add_prop(CONT_I_WEIGHT, 100000);
        add_prop(CONT_I_VOLUME, 100000);
        add_prop(OBJ_I_VALUE, 8549);
        add_prop(CONT_I_RIGID, 1);
        add_prop(OBJ_M_NO_GET, "It is held firmly in place.\n");
}

