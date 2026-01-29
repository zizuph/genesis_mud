/* Sarr */
#include "/d/Raumdor/defs.h"
inherit "/std/object";

string sign_description = 
        "+---------------------------------+\n"+
        "| Northwest: To the mountain pass |\n"+
        "| Northeast: To Drakmere          |\n"+
        "| Southeast: To Zhaal             |\n"+
        "+---------------------------------+\n"+
        "         ||             ||         \n"+
        "         ||             ||         \n"+
        "         ||             ||         \n";

int
do_read()
{
    write(sign_description);
    return 1;
}


void
create_object()
{
    set_name("post");
    add_name("sign");
    add_adj("sign");
    set_short("sign post");
    set_long(sign_description);
    add_prop(OBJ_M_NO_GET,"You don't want to do that.\n");
}

void
init()
{
    ::init();
    add_action(do_read, "read");
}

