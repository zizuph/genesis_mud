inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

object obj;

void
create_room()
{
    set_short("In a hallway of the House of Paullus");
    set_long("You are now in a short hallway. There are candles on "+
    "the wall, lighting the way. A very beautiful table stands at "+
    "the corner here. A statue also stands here.\n");
  
    add_item("candles","They flicker in the slight breeze.\n");
    add_item("table","A beautiful table made of red rose-wood. On "+
    "its shiny surface, you see a mysterious rock.\n");
    add_item("statue","A sculpture of a young warrior, wearing a "+
    "toga and brandishing a dagger in his hand.\n");
    add_item(({"rock","mysterious rock"}),"It is a very strangely shaped "+
    "polished rock. It is so shiny, in fact, that you can see your "+
    "reflection on it very well. It looks like it is shaped as a "+
    "spider.\n");

    INSIDE;

    add_exit(NOBLE(paullus/m8),"east",0,-1,-1);
    add_exit(NOBLE(paullus/m6),"south",0,-1,-1);
    reset_room();
}

void
reset_room()
{
    if(!obj)
    {
        obj = clone_object(NOBLE(npc/house_guard));
        obj->set_house_name("Paullus");
        obj->set_color_name("red-gold");
        obj->arm_me();
        obj->move_living("xxx",TO);
    }
}

