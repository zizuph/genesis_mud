// Underwater room   (/d/Avenir/common/port/uw3a.c)
// creator(s):       Glinda may -95
// last update:
// 		Lucius, Jan 2009: Re-written for new water code.
// purpose:
//
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/water";
#include "/d/Avenir/common/common.h"


public string
hook_no_swim(string str)
{
    if ((str == "east") || (str == "south"))
    {
	return "You decide that isn't a good idea, since the currents "+
	    "seem dangerous in that direction.\n";
    }
    else if (str == "north")
    {
	return "The cliff blocks your way.\n";
    }
    else if (str == "down")
    {
	TP->add_fatigue(-(calc_fat(TP) / 2));
	return "You dive further down, but the pressure is so " +
	    "strong you instantly return.\n";
    }

    return "";
}

public void
create_room(void)
{
    underwater_room();

    set_short("Underwater in the dark lake");
    set_long("You are swimming in dark, murky water. Powerful " +
      "currents are pulling you in various directions. Far above you, the " +
      "surface of the lake is a faint glowing light. Below you is only " +
      "darkness. You cannot make out the details of the cliff surface to "+
      "the north but it is there, the only steady point in your "+
      "environment.\n");
    add_item(({"water","currents"}),
      "The dark water envelops you completely. Luckily the currents here " +
      "are moving you towards the cliff, rather than away from it. You " +
      "don't know what could happend if you got caught in the currents.\n");
    add_item(({"cliff","rock"}),
      "The dark rock of the cliff appears only as a darker shade in the " +
      "darkness surrounding you. There seems to be a narrow rock shelf "+
      "jutting out from it.\n");
    add_item("shelf", "You can barely make it out in the gloom and inky "+
	"blackness.\n");
    add_item(({"surface"}),
      "A faint glow above your head indicates that the surface is somewhere " +
      "above you. It looks like your best option.");

    add_prop(OBJ_S_SEARCH_FUN, "search_me");

    add_exit(PORT + "uw2a", "up");
    add_exit(PORT + "uw3", "west");
}

#include "/d/Avenir/union/lib/bits.h"
#define LIST ("/d/Avenir/union/list")

public string
search_me(object player, string str)
{
    if (player->query_prop("found_it_yet") ||
	player->test_bit("Avenir", GUILD_GROUP, QUEST_BIT) ||
	!LIST->query_accepted(player->query_real_name()))
    {
	return "";
    }

    if (!parse_command(str, ({ }),
	"[the] 'cliff' / 'shelf' / 'rock'"))
    {
	return "";
    }

    player->add_prop("found_it_yet", 1);
    object ob = clone_object(UNION+"obj/quest/stone");
    ob->move(player, 1);

    return "You find "+ LANG_ASHORT(ob) +
	" lying on the narrow rock shelf.\n";
}
