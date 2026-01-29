// file name:    n1
// creator(s):   Cirion, April 1996
// last update:  Lilith 21 Feb 2014: Got merchant to load
// purpose:      Tunnel for the newbie area that has
//               bugs and other nasty creatures.
// note:         
// bug(s):
// to-do: 
#pragma strict_types

inherit "/std/room";
#include "outpath.h"
#include <money.h>

int      bugs, torch, money;
static object   merch;

void reset_room()
{
    bugs = 3;
    torch = 1;
    money = 1;
	if (!merch)
	{
		merch = clone_object( MON + "merchant");
		merch->move_living("M", this_object());
    }
}

void create_room()
{
    set_short("southern tunnel");
    set_long("This dark tunnel extends north into darkness, and "
      +"back south, where you can see the white mist of "
      +"the port. A furious wind is blowing from the south, "
      +"making eerie noises against the jagged and "
      +"uneven rock walls of the tunnel. There is a "
      +"small dark hole on the west side of the tunnel.\n");

    add_item(({"wall","walls","rock"}),"The rock walls of this "
      +"tunnel are craggy and rough-hewn, their cold surface "
      +"glistening with moisture and lattices with numerous "
      +"shadows. There is a small hole in the western wall of "
      +"the tunnel.\n");
    add_item(({"floor","ground"}),"The ground is cold and "
      +"rough, making your footing treacherous.\n");
    add_item(({"ceiling","roof"}),"The ceiling of the tunnel "
      +"is hidden in shadows.\n");
    add_item(({"shadow","shadows","darkness"}),"The shadows are "
      +"everywhere.\n");
    add_item(({"mist","south"}),"To the south, the tunnel "
      +"seems to open out into a bright white mist, from "
      +"where the sounds of water can be heard.\n");
    add_item(({"north","tunnel"}),"It leads into darkness and "
      +"gloom.\n");
    add_item("hole", "It is pitch dark, and a tiny bit larger "
      +"than your hand.\n");

    IN;
    IN_IN;

    add_prop(OBJ_S_SEARCH_FUN, "search_hole");
    add_prop(OBJ_I_SEARCH_TIME, 1);

    add_exit(PORT+"port12", "south");
    add_exit(OUTPATH+"n2", "north");

    reset_room();
}

void init()
{
    ::init();
    add_action("reach", "reach");
    add_action("reach", "feel");
}

int reach(string str)
{
    if (!strlen(str))
	return NF("Reach what?\n");

    if (!parse_command(str, ({}), "[my] [hand] 'into' [the] 'hole'"))
	return NF("Reach into what?\n");

    if (TP->query_attack())
    {
	write("You are too busy fighting!\n");
	return 1;
    }

    write("You reach your hand into the dark hole and feel around "
      +"it.\n");
    say(QCTNAME(TP)+" reaches "+TP->query_possessive()+" into the "
      +"dark hole.\n");
    search_object("hole");
    return 1;
}

mixed search_hole()
{
    object    mil;

    seteuid(getuid());

    if (!bugs)
    {
	if (!torch)
	{
	    if (!money)
		return;

	    say(QCTNAME(TP)+" pulls something out of the hole.\n");
	    MONEY_MAKE_SC(2)->move(TP, 1);
	    money = 0;
	    return "You feel around the hole, and find a couple of "
	    +"moldy silver coins!\n";
	}

	say(QCTNAME(TP)+" pulls something out of the hole.\n");
	clone_object(OBJ+"torch")->move(TP, 1);
	torch = 0;
	return "You feel around the hole, and find a wooden stick "
	+"which you pull out.\n";
    }

    bugs--;

    write("As you feel around the hole, something crawls "
      +"across your hand and starts biting you!\n");
    say(QCTNAME(TP)+" quickly pulls "+TP->query_possessive()
      +" hand out of the hole.\n");
    /*
       if (TP->query_gender() == G_FEMALE && TP->query_stat(SS_DIS) < 55)
	 set_alarm(0.0, 0.0, &TP->command("$scream"));
     */

    mil = clone_object(MON+"millipede");
    mil->move(TO);
    mil->attack_object(TP);

    return "The millipede crawls down to the floor.\n";
}
