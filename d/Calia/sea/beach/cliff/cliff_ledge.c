/*  description: Room on a cliff above Calian sea
 *  coder: Tigerlily
 *  date:  2002-02-02
 *  special: needs climb skill to access
 *  notes:
 */

#pragma strict_types
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"

inherit "/std/room";
inherit ROOM_TELL;


object fish;
int fish_found = 0;

void
reset_room()
{
    fish_found = 0;
}


void
create_room()
{

    set_short("Narrow ledge just below the clifftop");
    set_long("This is a narrow ledge of rock that"+
      " juts out from just below the clifftop."+
      " You notice that there is a rather bad odour"+
      " that seems to emanate from a heap"+
      " of nasty debris that encrusts the ledge.\n");
    add_item(({"debris", "nasty debris"}), "Clearly"+
      " this is a dumping ground of sorts. As you"+
      " examine the debris carefully, you are compelled"+
      " to hold your nose due to the aroma of decaying"+
      " fish leftovers and bird excrement.\n");
    add_item(({"rock", "ledge", "cliff","clifftop"}),
      "Constructed from the same basic granite that"+
      " composes the rest of the cliff, you are glad"+
      " to have this narrow ledge to stand on.\n");
    add_item("down", "Don't look down! You"+
      " get dizzy.\n");
    add_item(({"odour", "nasty odour"}), "Whatever it is,"+
      " it smells really bad.\n");
    add_item(({"leftovers", "fish leftovers"}),
      "The remainder of the osprey's dinner.\n");
    add_item(({"excrement", "bird excrement"}),
      "Quite nasty isn't it?\n");

    add_exit(CLIFF_ROOM + "cliff0_4", "down", 0,0, 1);
    set_tell_time(150);
    add_tell("Nasty bits of debris come falling down"+
      " from above.\n");
    add_tell("A fresh breeze wafts in and clears away"+
      " some of the stench.\n");
    add_prop(OBJ_S_SEARCH_FUN, "search_debris");
    add_prop(OBJ_I_SEARCH_TIME, 5);

}
string
search_debris(object player, string str)
{
    if (!str)
	return "";

    if (!parse_command(str, this_object(), " [debris] / [excrement] "))
	return "";

    if (!CAN_SEE_IN_ROOM(player))
	return "It's too dark to search anything.\n";

    if (!fish_found)
    {
	fish = clone_object(SEA_OBJECTS + "rotten_fish");
	fish->move(this_object(), 1);
	fish_found = 1;
	return "You find something unpleasant just as"+
	" you might have anticipated.\n";
    }

    return "";

}

string
hook_smelled(string str)
{
    object tp = this_player();

    if (str == "debris" || str == "excrement")
    {
	write("You cannot believe the awful stench"+
	  " from the mixture of bird excrement and decayed fish.\n");
	write("You hold your nose in disgust.\n");
	say(QCTNAME(tp) + " holds " + tp->query_possessive()+
	  " nose in disgust.\n");
	return "";
    }
    /* else more general stench */
    write("It sure stinks around here. What can it be?\n");
    return "";

}
