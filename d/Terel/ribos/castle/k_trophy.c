/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * k_trophy.c
 *
 * Vader
 * Recoded by Sorgum 950708
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit STDROOM;

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({CASTLE_DIR + "monster/stronguard",
	     CASTLE_DIR + "monster/stronguard",
	     CASTLE_DIR + "monster/stronguard"});		     
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Trophy room");
    set_long("You now look upon the treasures of a ruler.  King Bor-El, in " +
	     "days past, was quite well known as a slayer of " +
	     "monsters.  Here is where he prominently displays " +
	     "the proof of such adventures.  You see a dragon " +
	     "head, mounted on one wall, with a painting on that wall " +
	     "depicting the battle.  You also see the Kings choice " +
	     "armour and sword.  There are various other things, " +
	     "such as amulets, and furs, as well as the royal crown " +
	     "of Bindolock, from the land that the king and his " +
	     "knights defeated two decades ago.  All of the items " +
	     "in this room are protected by magic, so thieves do not " +
	     "run away with anything.\n");
    

    add_item(({"crown", "royal crown", "royal crown of bindolock"}),
	     "It was once worn by the King of Bindolock, but he is " +
	     "dead now.\n");

    add_item(({"amulets", "amulet"}),
	     "They were taken from various enemies.\n");

    add_item(({"furs"}),
	     "These come from various lions, bears, and other " +
	     "fierce creatures\nthat King Bor-El killed for sport.\n");

    add_item(({"head", "dragon head"}),
	     "A very large dragon head, probably sliced from an " +
	     "enormous body.\n");

    add_item(({"painting"}),
	     "It depicts a huge creature, with a longsword embeded " +
	     "in its chest and\nKing Bor-El driving it further within.\n");

    add_item(({"armour", "choice armour", "sword", "choice sword"}),
	     "This is a matched set of armour and sword, made of a " +
	     "strange black metal that you have never seen before.  " +
	     "It is smooth and shiny, yet it reflects no light.\n");

    INSIDE;

    add_exit(CASTLE_DIR + "m_hall1_1", "east", 0);
    reset_room();
}
