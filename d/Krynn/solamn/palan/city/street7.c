/* created by Aridor 06/21/93 */

#include "../local.h"

inherit STREET_BASE

#include <macros.h>

object the_rod, the_worm;
int    can_fish;
object  already_fishing;

string
query_to_jail()
{
  return "south";
}

void
reset_palan_room()
{
    can_fish = 2;
}


create_palan_room()
{

    set_short("Eastern part of the Harbour");
    set_long(BS("This seems to be the perfect place to fish. "
         +   "You have a nice view across the harbour to the "
         +   "pier. To the north you can see the bay opening "
         +   "into the ocean, where ships go to and come from "
         +   "many a mysterious and wondersome place.",SL));
    add_item("fish",BS("They dart around in the water, heedless "
          + "of your presence.",SL));
    add_item("harbour",BS("It appears that the harbour is "
         +   "frequently used by ships and therefore a very "
         +   "busy place.",SL));
    add_item(({"water","ocean","bay"}),BS("The smells of salt "
         +   "water reaches your nostrils, the water looks "
         +   "green just like any ocean you've ever seen. "
         +   "As you look closer into the water you can see "
         +   "fish swimming in the bay.",SL));
    add_item(({"pier","lighthouse","tower"}),
	     BS("You can see a pier across the harbour to your west, with a tower, " +
		"which must be the lighthouse around here.",SL));

    add_exit(ROOM + "street11","south",0,1);
    add_exit(ROOM + "street18","southeast","@@bend_south",1);
    add_exit(ROOM + "street22","northeast",0,1);
    
    reset_room();
}


int
bend_south()
{
  write("The street bends to the south.\n");
  return 0;
}


init()
{
    ::init();
    ADA("fish");
}

fish()
{
    the_rod = present("rod", TP);
    if (the_rod)
    {   if (TP == already_fishing)
        {
            write("You can only fish with one rod at a time!\n");
            return 1;
        }
	else if (already_fishing)
	  {
	    write("There is only room for one person to fish at the same time.\n");
	    return 1;
	  }
        write("You start to fish.\n");
        already_fishing = TP;
        say(QCTNAME(TP) + " starts to fish.\n");
        set_alarm(itof(random(10) + 20),0.0,"caught_something");
        return 1;
    }
    else 
    {
        NF("Something doesn't seem to work right.\n"
        +  "Maybe you need a fishing rod to fish?\n");
        return 0;
    }
}


caught_something()
{
    seteuid(getuid(TO));
    the_worm = present("earthworm", the_rod);
    if (can_fish && (the_worm || (!the_worm && !random(5))))
    {
        write("You pull in the rod, and you caught a fish!\n");
        say(QCTNAME(TP) + " caught a fish!\n");
        can_fish--;
        clone_object(OBJ + "weedfish")->move(TP);
        the_worm->remove_object();
        return;
    }
    else
        write("You pull in the rod, but it seems you're out of luck!\n");
    already_fishing = 0;
    the_rod = 0;
    return;
}

