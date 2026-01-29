inherit "/std/object";
#include "/d/Kalad/defs.h"
#include <macros.h>
/* by Antharanos */
create_object()
{
    set_name("net");
    set_adj("large");
    add_adj("fishing");
    set_long("A fine-mesh net used for catching fish.\n");
    add_prop(OBJ_I_VALUE,60);
    add_prop(OBJ_I_WEIGHT,750);
    add_prop(OBJ_I_VOLUME,750);
}
init()
{
    ::init();
    add_action("fish","fish");
}
int
fish()
{
    write("You try and catch a fish...\n");
    say(QCTNAME(TP) + " tries to catch a fish...\n");
    set_alarm(2.0,0.0,"fish_catch");
    return 1;
}
void
fish_catch()
{
    write("For some reason, you failed to catch one.\n");
    say("For some reason, " + QCTNAME(TP) + " fails to catch anything.\n");
}
