/*
 * tower4.c
 *
 * Skippern 20(c)02
 *
 * 3rd floor in a magicians tower.
 *
 */
#include "../../defs.h"
inherit DOL_STD + "inside";

#include <stdproperties.h>

/* Global variables */
static int     NoGargoyls;

string gargoyl_desc();

void
create_inside()
{
    object o;

    set_short("the fourth level in a tower");
    set_long("This is the fourth level of a high tower. This circular " +
	     "chamber seems to be the workroom of a lore master. On the " +
	     "walls pointing north, south, east and west are small niches " +
	     "who servs as windows. Along round the wall, just upon the " +
	     "ceiling is a shelve containing many small boxes and jars. " +
	     "A steep staircase comes up between the southern and the " +
	     "western window. In the middle of the room a large put " +
	     "stands.\n");

    add_item( ({ "pot", "large pot" }), "In the middle of the room a " +
	      "large pot stands. The pot contains a strange looking " +
	      "green liquid substance.\n");
    add_item( ({ "pedistal", "pedistals", "gargoyl", "gargoyls" }), &gargoyl_desc());

    add_exit(DOL_HILLS + "g-11/tower3", "down", 0, 1);

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);

    o = clone_object(DOL_NPC + "g11-mage");
    o->set_tower(this_object());
    o->move(this_object());

    NoGargoyls = 4;
}

void
reset_room()
{
    ::reset_room();

    if (!present("halvgorn"))
	clone_object(DOL_NPC + "g11-mage")->move(this_object());
}

int
no_of_gargoyls()
{
    return NoGargoyls;
}

string
gargoyl_desc()
{
    string r;

    r = "Four high columns are placed in the corners of the room. These columns does not " +
      "go all the way to the ceiling, but are pedistals for some gargoyls. ";
    switch(NoGargoyls)
    {
    case 0:
	r += "All the pedistals are empty. ";
	break;
    case 1:
      r += "Only one gargoyl is left on its pedistal ";
      break;
    case 2:
      r += "Two gargoyls still sits in their places, while the two other are empty. ";
    case 3:
	r += "Some of the pedistals are empty, but one gargoyl still sits on its places. ";
	break;
    case 4:
    default:
	r += "All the pedistals are occupied by a gargoyl. ";
    }
    if (NoGargoyls != 0)
	r += "The gargoyls looks like huge winged deamons. Their skin looks like it is " +
	  "made out of clay. The gargoyls are watching you with sharp eyes. ";

    r += "\n";

    return r;
}

void
remove_g() { NoGargoyls--; }
add_g() { NoGargoyls++; }
