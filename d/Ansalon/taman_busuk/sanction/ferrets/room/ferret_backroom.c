
/*
 * ferret_backroom.c
 * A room within the ferret shack, has the Quest NPC.
 * 
 * Ares, 2004
 * Mirandus February 19th, 2015 - Updated strings for quest
 */
 
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <ss_types.h>
#include <money.h>
#include "/d/Ansalon/taman_busuk/sanction/ferrets/defs.h"

inherit "/d/Ansalon/taman_busuk/sanction/std/i_room_base";

object dante;
object paper;

int did_quest3;
int do_grab(string str);

void
reset_sanction_room()
{
   if(!objectp(dante))
      {
      dante = clone_object(NPC_DIR + "dante");
      dante->move(this_object(), 1);
      }
    did_quest3 = 0;
}

void
create_sanction_room()
{
    set_short("Back room of the ferret breeding shack");
    set_long("You now stand in the back room of the ferret shack. "+
    "It's a little cleaner back here, but not by much. Rusty weapons "+
    "hang from hooks on the walls, probably from the owner's past "+
    "reputation as an Officer in the Blue Dragonarmy. A large bin full "+
    "of pikes is in the corner, similar to one in the other room. "+
    "Other than the weapons, there's not much else of interest in this back "+
    "room. There are doors leading to the front of the house, the kitchen "+
    "and to the outside. \n");
    
    add_item(({"pikes"}),
    "These are rusty pikes used back in an old man's lifestyle of war. "+
    "Now, he earns a living breeding and selling ferrets. You have a feeling "+
    "that he'll part with these relics if you ask him. \n");
    
    add_item(({"bin", "bottom of bin", "bottom"}),
    "This large bin has tons of rusty pikes in it. It goes down very deep "+
    "to the bottom. Through the rusty pikes you can see a paper at the bottom "
	+"of the bin. You could likely grab it.\n");
    
    add_item(({"weapons", "hooks", "rusty weapons", "axe", "swords", "daggers"}),
    "Hanging from hooks are several different weapons. One large rusty axe, "+
    "five tarnished swords, and several daggers. A very long time ago, these "+
    "weapons gave glory to the name of the Queen of Darkness. Now, they "+
    "collect rust and rot away nearly forgotten. \n");
    
    add_item(({"door", "doors"}),
    "There are three of them. One leads back to the front of the shack, another "+
    "to the kitchen, and one leads outside to the backyard. \n");
    
     add_exit(ROOM_DIR + "ferret_breeder_room", "front");
     add_exit(ROOM_DIR + "ferret_outside", "outside");
     add_exit(ROOM_DIR + "ferret_kitchen", "kitchen");
     
     reset_sanction_room();
     
}

void
init()
{
    ::init();
    add_action(do_grab,"grab");
    
}


int
do_grab(string str)
{
    notify_fail("Grab what?\n");
    if((!str) || (!strlen(str)) || (str != "paper from bottom of bin")
		&& (str != "paper") && (str != "paper from bin"))
        return 0;

    if(did_quest3)
    {
        write("You find a blank piece of paper and discard it. \n");
        return 1;
    }

    did_quest3=1;

    write("You reach down deep into the bin, careful not to hurt yourself "+
        "on the pikes, and grab an old piece of paper. \n");
    say(QCTNAME(TP)+" reaches down into the bin and pulls out a paper.\n");

    reset_euid();

    clone_object(OBJ_DIR + "old_paper")->move(this_player(),1);

    return 1;
}




    