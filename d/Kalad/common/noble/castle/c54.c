// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

int key_here;

void reset_room();

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("Your feet now step upon cold, white marble. "+
    "You stand before a staircase that leads down to the lower "+
    "level of the castle of the High-Lord. To the east, you can "+
    "see the way into the second level of the castle. There is "+
    "a suit of armour standing against one of the walls here.\n");
    add_item(({"suit of armour","armour","suit"}),"A large iron "+
    "fullplate armour of antique design. You see the coat of arms of "+
    "King Vorbaar Sulantra on it.\n");
    add_item(({"floor","marble"}),"The floor is made of polished "+
    "white marble. It looks flawless, except in one corner....\n");
    add_item("corner","You see a loose flagstone there.\n");
    add_item("flagstone","The flagstone seems to be cracked, and "+
    "probably liftable.\n");

    add_exit(NOBLE + "castle/c55","east", 0, 0);
    add_exit(NOBLE + "castle/c19", "down", 0, 0);

    reset_room();
}


void
reset_room()
{
    ::reset_room();
    key_here = 1;
}

int
do_lift(string str)
{
    object key;

    NF("Lift what?\n");
    if(str != "flagstone")
        return 0;

    write("You lift up the loose flagstone.\n");
    say(QCTNAME(TP)+" lifts up a loose flagstone.\n");

    if(key_here)
    {
        key = clone_object(NOBLE + "obj/free_goblin_key");
        write("You find a "+key->short()+"!\n");
        key->move(ENV(TP));
        key_here = 0;
    }
    else
        write("You find nothing.\n");

    return 1;
}

void
init()
{
   ::init();
   add_action(do_lift, "lift");
}

