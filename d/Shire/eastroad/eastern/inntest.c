#pragma save_binary
#pragma strict_types

#include <ss_types.h>
#include <tasks.h>
#include "local.h"

inherit SHIRE_ROOM;

#define CLIMB_PROP  "_Shire_i_climb_cellar_stairs"

int do_fail_climb(object player);
int do_successful_climb(object player);


void
create_shire_room()
{
    set_short("Inside the basement cellar of the Forsaken Inn");
    set_long("Puddles form in the broken earth floor that you "+
      "struggle to find footing on, worsened by shards and pieces "+
      "of timber from various furniture and cellar items. Its hard "+
      "to make out much in the gloom down here but you can see "+
      "several wine shelves still stocked and standing. Along the "+
      "far west wall you can make out the large squat shapes of "+
      "some casks, of what they contain you can only guess at this "+
      "time. A ruined and unusable staircase occupies the east "+
      "corner, although you think with some care and skill that "+
      "you might be able to climb out of this cellar.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE, -1);

    add_item(({"water","drips","puddles"}),
      "The water that had done such a terrific job of ruining "+
      "the above two levels is somewhat less here, and of course "+
      "there is so much less here to destroy.\n");
    add_item(({"floor","earth floor","broken earth floor"}),
      "From the dim light in here you can't really make out the "+
      "details of the floor you stand on, besides that it seems "+
      "to be whats left of hard packed cellar earth after years "+
      "of water seepage, combined with the various shrapnel of "+
      "broken fixtures and furniture from above.\n");
    add_item(({"shelves","wine shelves","wine racks"}),
      "Standing in line are several wine racks of timber, "+
      "apparently protected here from the elements. Back "+
      "towards the wall you find that there are still several "+
      "bottles left in various places amongst the shelves.\n");
    add_item(({"wine","bottles","wine bottles"}),
      "Scattered amongst the several surviving wine shelves "+
      "you spot several bottles of wine, blanketed in dust "+
      "from what must have been hundreds of years, and no "+
      "doubt they're still here on the assumption that any "+
      "bottle that old would be nothing but vinegar.\n");
    add_item("casks",
      "Nestled along the far west wall beyond the wine racks "+
      "are several oaken casks, all seemingly in good "+
      "condition, though after a few hundred years who can "+
      "guess what remains inside them. You count six casks "+
      "in total.\n");
    add_item(({"stairs","staircase"}),
      "Once occupying the northeast corner of the basement, "+
      "what is left of the staircase up to a now-missing trap-"+
      "door puts up a pitiful stand against time and rot. "+
      "Much of the timber is warped and cracked, several stairs "+
      "are snapped in half or rotted away. Getting back up "+
      "these stairs to freedom will be some challenge.\n");

    reset_shire_room();
}

void init()
{
    ::init();
    add_action("climbout", "climb");
}

void
reset_shire_room()
{
    object leader, dwarf1, dwarf2;

    if (!objectp(leader = present("khaaz", TO)))
    {
	leader = clone_object(ERNPC_DIR + "khaaz");
	leader->move_living("void",TO);
    }
    if (!objectp(dwarf1 = present("dibble", TO)))
    {
	dwarf1 = clone_object(ERNPC_DIR + "dwarf_warrior");
	dwarf1->add_name("dibble");
	dwarf1->move_living("void",TO);
    }
    if (!objectp(dwarf2 = present("tribble", TO)))
    {
	dwarf2 = clone_object(ERNPC_DIR + "dwarf_warrior");
	dwarf2->add_name("tribble");
	dwarf2->move_living("void",TO);
    }
    leader->team_join(dwarf1);
    leader->team_join(dwarf2);
}

int climbout(string out)
{
    notify_fail("Climb where?\n");

    if (out!="out") return 0;
    if (TP->query_prop(CLIMB_PROP))
    {
	NF("You are already busy climbing out of the cellar.\n");
	return 0;
    }
    if (TP->resolve_task((objectp(TP->query_attack()) ? TASK_FORMIDABLE :
	  TASK_DIFFICULT), ({TS_DEX, SS_CLIMB})) <= 0)
	set_alarm(7.0, 0.0, &do_fail_climb(TP));
    else
	set_alarm(7.0, 0.0, &do_successful_climb(TP));
    write("You begin to climb out of the cellar...\n");
    TP->add_prop(CLIMB_PROP, 1);
    return 1;
}

int do_fail_climb(object player)
{
    player->remove_prop(CLIMB_PROP);
    // Don't print messages to the player if he not here
    if (!present(player,TO))
	return 0;
    player->catch_tell("You almost make it out of the cellar but fall backward just "+
      "before reaching the top.\n");
    say(QCTNAME(player)+" almost makes it out of the cellar but falls backwards "+
      "just before reaching the top.\n");
    return 1;
}

int do_successful_climb(object player)
{
    player->remove_prop(CLIMB_PROP);
    // Don't print messages or move the player if they aren't in the room.
    if (!present(player,TO))
	return 0;
    player->catch_tell("You somehow manage to haul yourself out of that cellar.\n");
    say(QCTNAME(player)+" slips up the ruined staircase and to the "+
      "ground level of the Inn like a monkey after a hand of bananas.\n");
    player->move_living("up through the hole", ERE_DIR + "inn1"); 
    return 1;
}
