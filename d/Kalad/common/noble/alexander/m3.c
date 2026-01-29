inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

object obj;
void reset_room();

void
create_room()
{
    set_short("In a hallway of the House of Alexander");
    set_long("You are now in a short hallway. There are candles "+
    "burning on a small table against the wall here. A painting "+
    "hangs on the wall here.\n");
  
    add_item("candles","They flicker in the slight breeze.\n");
    add_item("table","A beautiful table made of red rose-wood.\n");
    add_item("painting","The paintings is that of a black sun "+
    "rising over a red desert, in which you see a deserted, ruined "+
    "gladiator ring.\n");

    INSIDE;

    add_exit(NOBLE(alexander/m1),"north",0,-1,0);
    add_exit(NOBLE(alexander/m7),"southeast",0,-1,0);
    reset_room();
}

void
reset_room()
{
    if(!obj)
    {
        obj = clone_object(NOBLE(npc/house_guard));
        obj->set_house_name("Alexander");
        obj->set_color_name("black");
        obj->arm_me();
        obj->move_living("xxx",TO);
    }
}

