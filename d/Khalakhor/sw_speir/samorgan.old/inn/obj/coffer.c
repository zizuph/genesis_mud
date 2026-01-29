/**********************************************************************
 * - coffer.c                                                       - *
 * - Simple container that players may use while in the Inn.        - *
 * - Created by Damaris@Genesis 08/2006                             - *
 **********************************************************************/
#pragma strict_types

inherit "/std/container";
#include <stdproperties.h>
#include "/d/Khalakhor/sys/basic.h"
#include "../inn.h"

string
query_plaque()
{
    return("\n"+
    "          *----------------*` - - `*----------------*\n"+
    "          | ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` |\n"+
    "          | `                                     ` |\n"+
    "          | `          For General Usuage         ` |\n"+
    "          | `                                     ` |\n"+
    "          | ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` |\n"+
    "          *----------------*` - - `*----------------*\n");
}
void
create_container()
{
	seteuid(getuid(TO));
	set_name("coffer");
        add_name("inn:coffer");
        set_short("wooden coffer");
        add_adj("wooden");
        set_long("This is a small wooden coffer. It has a highly "+
        "polished brass edging that helps protect putting and taking "+
        "items in and out of it. There is a small brass plaque attached "+
        "to it as well.\n");
        add_item(({"brass", "brass edging", "edging"}),
        "The brass edging is highly polished and helps to protect the "+
        "edge of the coffer.\n");
        add_item(({"plaque", "small plaque", "brass plaque"}), query_plaque);
	add_cmd_item(({"plaque", "small plaque", "brass plaque"}),"read", query_plaque);
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

