/*
 * Recruiter room
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
	object door;

    set_short("Small cave room");
    set_long("This is the recruiter private cave. " +
             "There is desk with some papers on it and some chairs. " +
             "You can see a door in the western wall. " +
             "\n\n");

    add_item("desk", "@@get_desk_desc");
    add_item(({"papers", "plan", "recruitment plan"}),
             "Most of the papers are blank, but you do notice the title " +
             "'Recruitment Plan' on one of them.\n");
    add_item(({"chairs", "chair"}),
             "There are some wooden chairs around the desk.\n");
    add_item("door", "It is the only exit from this cave.\n");
    add_item(({"wall", "western wall"}),
             "There is a door in the western wall.\n");
    add_cmd_item( ({"papers", "plan", "recruitment plan"}),
                  "read",
                  "Most of the papers are blank, and the rest are written " +
                  "with terrible handwriting.\n");

    add_npc(NPCS_DIR + "recruiter", 1, &->arm_me());

    door = clone_object(DOORS_DIR + "recruiter_e");
	door->move(this_object());

	add_prop(OBJ_S_SEARCH_FUN, "do_search");


} /* create_room */


/*
 * Function name:        do_search
 * Description  :        allow the player to search things in the room
 * Arguments    :        object pl  - the player object,
 *                       string arg - what the player tried to search
 * Returns      :        int 1 - success, 0 - failure
 */
public string
do_search(object pl, string arg)
{
    if (!strlen(arg) || (member_array(arg,
        ({ "desk", "under desk"}) ) == -1))
    {
        return "Your search reveals nothing special.\n";
    }

	if((!this_player()->query_prop(GCL1_QUEST_PROP))
	|| (this_player()->query_prop(GCL1_QUEST_PROP) != 3))
		return "There is nothing under recruiter's desk.\n";

	quest_armour = clone_object(EQUIP_DIR + "quest_goblin_armour");
	this_player()->add_prop(GCL1_QUEST_PROP, 99);
	if(!quest_armour->move(this_player()))
	{
		return "You find goblin armour under the desk.\n";
	}
	else
	{
		quest_armour->move(this_object());
		return "You find goblin armour under the desk but unable to hold " +
		       "it. It falls on the floor.\n";
	}

} /* do_search */

/*
 * Function name:        get_desk_desc
 * Description  :        shows desk desc according to quest prop
 */
string
get_desk_desc()
{
	if((!this_player()->query_prop(GCL1_QUEST_PROP))
	|| (this_player()->query_prop(GCL1_QUEST_PROP) != 3))
		return "This is a small wooden desk with some papers on it.\n";
	return "This is a small wooden desk with some papers on it. But " +
           "you can see something laying under the desk.\n";

} /* get_desk_desc */