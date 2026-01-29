inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

void
create_room()
{
    set_short("In a secret passageway in the House of Paullus");
    set_long("You are in a very small and crampt passageway. It "+
    "is very dark and dusty here. You see a ladder leading down "+
    "into darkness. The hole leading out is just to your left.\n");
    add_item("ladder","An iron, rusty ladder leading down.\n");
    
    INSIDE;
    add_prop(ROOM_I_LIGHT,0);
    
    add_exit(NOBLE(paullus/hole2),"down",0,-1,-1);
}

void
init()
{
    ::init();
    AA(do_enter,enter);
}

int
do_enter(string str)
{
    NF("Enter what?\n");
    if(str != "hole")
        return 0;
    write("You squeeze back through the hole.\n");
    say(QCTNAME(TP)+" squeezes back through the hole.\n");
    TP->move_living("M",NOBLE(paullus/m12));
    return 1;
}

