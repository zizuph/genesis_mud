/* Sarr */
#include "defs.h"
inherit "/std/object";


void
create_object()
{
    set_name("post");
    add_name("sign");
    add_adj("sign");
    set_short("sign post");
    set_long("-----------------------------------\n"+
             "| Northwest: To the mountain pass |\n"+
             "| Northeast: To Drakmere          |\n"+
             "| Southeast: To Zhaal             |\n"+
             "-----------------------------------\n"+
             "         |              |          \n"+
             "         |              |          \n"+
             "         |              |          \n");
    add_prop(OBJ_M_NO_GET,"You don't want to do that.\n");
}

