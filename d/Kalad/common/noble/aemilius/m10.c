inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

object ob;
void reset_room();

void
create_room()
{
    ::create_room();
    set_short("A short hall");
    INSIDE;
    set_long("You are now in a short hall. The hall continues to the "+
    "north, where the smells of cooking come from, south where you can "+
    "hear scrubbing, and east, where the hall continues. There is a "+
    "large statue here againts the wall.\n");
    add_item("statue","This is a statue of armoured warrior. In "+
    "its hands it clutches a large, giant mace. The warrior is "+
    "intricatly detailed, down to the nails in the armour. A small "+
    "inscription on the bottom reads: Calador the V, the warrior "+
    "from Athas.\n");
    add_exit(NOBLE(aemilius/m7),"east",0,-1,-1);
    add_exit(NOBLE(aemilius/m11),"north",0,-1,-1);
    add_exit(NOBLE(aemilius/m9),"south",0,-1,-1);
    reset_room();
}


void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(NOBLE(npc/house_guard));
        ob->set_house_name("Aemilius");
        ob->set_color_name("red");
        ob->arm_me();
        ob->move_living("xxx",TO);
    }
}

