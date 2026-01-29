inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

object guard;
void reset_room();

void
create_room()
{
    set_short("In the guard's room");
    set_long("You are now in the guards quarters in the house of "+
    "Aemilius. The room is huge, and stretches all the way to "+
    "the north. Cots line the walls where guards rest up. "+
    "There are tables and chairs and chests where guards keep "+
    "thier stuff.\n");
    
    add_item("chests","Old chests that are locked shut.\n");
    add_item("cots","Warm and soft cots where guards rest.\n");
    add_item("chairs","Old wooden chairs surround the tables.\n");
    add_item("tables","Various old tables dot the room.\n");

    INSIDE;

    add_exit(NOBLE(aemilius/m17),"southeast",0,-1,-1);
    add_exit(NOBLE(aemilius/m16),"east",0,-1,-1);
    add_exit(NOBLE(aemilius/m15),"northeast",0,-1,-1);
    add_exit(NOBLE(aemilius/m18),"north",0,-1,-1);
    reset_room();
}

void
reset_room()
{
    if(!guard)
    {
        guard = clone_object(NOBLE(npc/house_guard));
        guard->set_house_name("Aemilius");
        guard->set_color_name("red");
        guard->arm_me();
        guard->move_living("xxx",TO);
     }
}

