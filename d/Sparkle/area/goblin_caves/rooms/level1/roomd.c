/*
 * Storage room
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
    set_short("Storage room");
    set_long("This part of the cave is used for storing different items. " +
             "You can see racks, shelves, sacks and crates all over. " +
             "\n\n");

    add_item(({"racks", "rack"}),
             "The racks are full of equipment but stealing it " +
             "will be punished severely.\n");
    add_item(({"shelves", "shelf"}),
             "There are a lot of jars on the shelves.\n");
    add_item(({"sacks", "sack", "food supplies", "food supply"}),
             "The sacks contain some food supplies for long expeditions.\n");
	add_item(({"crates", "crate"}), "@@get_crates_desc");
    add_item(({"jars", "jar"}),
             "Some of them empty, some of them full. But you " +
             "cannot find anything you can use.\n");
    add_item(({"tools", "useless tools"}),
             "You cannot find anything useful.\n");
    add_exit ("roome","east");

    add_npc(NPCS_DIR + "goblin1_1", 2, &->arm_me());
} /* create_room */

/*
 * Function name:		get_crates_desc
 * Description  :		returns crates desc according to quest prop
 */
string
get_crates_desc()
{
	if((!this_player()->query_prop(GCL1_QUEST_PROP))
	|| (this_player()->query_prop(GCL1_QUEST_PROP) != 2))
		return "You search the crates but cannot find anything but " +
                       "useless tools.\n";

	quest_armour = clone_object(EQUIP_DIR + "quest_goblin_armour");
	this_player()->add_prop(GCL1_QUEST_PROP, 99);
	if(!quest_armour->move(this_player()))
	{
		return "You find goblin armour inside crates.\n";
	}
	else
	{
		quest_armour->move(this_object());
		return "You find goblin armour inside crates but unable to hold " +
		       "it. It falls on the floor.\n";
	}
} /* get_crates_desc */

