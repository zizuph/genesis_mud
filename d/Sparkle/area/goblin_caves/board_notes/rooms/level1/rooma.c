/*
 * Sleeping room
 * Boreaulam, April 2012
 */
#include "defs.h"
#pragma strict_types

inherit L1_BASE_ROOM;

object 	quest_armour;

/*
 * Function name:		create_room
 * Description  :		creates room
 */
void
create_room()
{
    ::create_room();

    set_short("Sleeping room");
    set_long("You are in a big room with a lot of beds. "+
             "It seems to be a goblins sleeping quarter. "+
             "There are some chests between the beds.\n\n");

    add_item(({"beds", "bed"}), "The beds have some dirty pillows on them.\n");
    add_item(({"pillows", "pillow"}), "Nothing interesting. Just small dirty " +
             "pillows.\n");
    add_item(({"chests", "chest"}), "Chests are empty except one big chest " +
             "in the corner.\n");
    add_item("corner", "You see big chest there.\n");
	add_item("big chest", "@@get_chests_desc");
	add_item("useless armours", "The big chest is full with the useless " +
	         "armours.\n");
	add_item("sleeping quarter", long());
    add_exit ("roomb", "east");

    add_npc(NPCS_DIR + "goblin1_1", 2, &->arm_me());

    reset_room();
} /* create_room */

/*
 * Function name:		get_chests_desc
 * Description  :		Returns description of chest depends on quest prop
 */
string
get_chests_desc()
{
	if((!this_player()->query_prop(GCL1_QUEST_PROP))
	|| (this_player()->query_prop(GCL1_QUEST_PROP) != 1))
		return "Big chest is full of useless armours.\n";

	quest_armour = clone_object(EQUIP_DIR + "quest_goblin_armour");
	this_player()->add_prop(GCL1_QUEST_PROP, 99);
	if(!quest_armour->move(this_player()))
	{
		return "Looking inside the big chest, you find a shattered iron " +
		       "platemail which must be what the trainer was talking " +
		       "about. You decide to take it with you.\n";
	}
	else
	{
		quest_armour->move(this_object());
		return "Looking inside the big chest, you find a shattered iron " +
		       "platemail which must be what the trainer was talking " +
		       "about. Unfortunately it is too heavy and falls on the " +
		       "floor.\n";
	}
}	/* get_chests_desc */

