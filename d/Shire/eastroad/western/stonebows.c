#pragma save_binary
#pragma strict_types

#include "local.h"
#include H_MAKER

inherit EAST_ROAD;
#define IS_ELF_GR_TRAVELLER "/d/Shire/std/elf_gr_patrol.c"
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "w";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

int do_climb(string str);

object hobbit;
int rockmax = 2 + random(4); /* 2-5 rocks here */

void
create_er_room()
{
    area = "standing on";
    areaname = "the Brandywine Bridge";
    land = "the Shire";
    areatype = 8;
    areadesc = "ancient stone bridge";
    grass = "green";

    extraline = "The Bridge of Stonebows, the border of "+
    "The Shire and Bree-land is ancient beyond the knowledge "+
    "of hobbits.  The mighty boulders and well-crafted stones "+
    "show no signs of wear from age or water.  An inn is stationed "+
    "at the western end of the Bridge, while towards the east, the "+
    "Bridge again meets the East Road, headed towards Bree.";

    add_item(({"boulder","boulders","mighty boulders"}),
      "The boulders are all bigger than any ox you have seen, but "+
      "no crack is visible between them.\n");

    add_item(({"stone","stones","well-crafted stones","well-crafted stone"}),
      "The well-crafted stones are much smaller than the boulders, "+
      "about the size of a large keg of ale.\n");

    add_item(({"inn","stonebows","stonebows inn"}),
      "The Inn itself is very small, built on a platform extending "+
      "from the bridge- it is in neither the Shire nor Bree-land.\n");

    add_item(({"river","baranduin river","brandywine river"}),
      "Below you to the north and south you can see the river "+
      "flowing under the bridge, at a rather slow but steady pace.\n");
    add_item(({"bridge","baranduin bridge","brandywine bridge","bridge of stonebows"}),
      "You stand on the Bridge of Stonebows, that crosses the Baranduin "+
    "river between Bree and Frogmorton. It is an ancient bridge, "+
      "built of stones and good masonry that has lasted for many ages of "+
      "the world.\n");

    add_exit(EAST_R_DIR + "er21e","west");
    add_exit(EAST_R_DIR + "er22","east", "@@leave_shire@@");
    add_exit(EAST_R_DIR + "stone_inn","inn");

    reset_shire_room();
}


public void
enter_inv(object ob, object from)
{
	string *names;
	::enter_inv(ob, from);
	names = ob->query_names();
	if(ob->id(npc_name))
	{
		if (!move_alarm || !sizeof(get_alarm(move_alarm)))
		{
			move_alarm = set_alarm(50.0 + rnd() * 20.0, 0.0, &move_patrol(ob));
		}
	return;
	}
}

void
reset_shire_room()
{
    object rock = present("rock");
    
    if (!objectp(rock) || rock->num_heap() < rockmax)
    {
        clone_object(ROCK_DIR + "rock")->move(TO);
    }

    if (!hobbit)
    {
	hobbit = clone_object(HOBBITMAKER);
	hobbit->set_type(CITIZEN);
	hobbit->set_power(100);
	hobbit->set_restrain_path("/d/Shire/eastroad/western");
	hobbit->set_random_move(3);
	hobbit->set_monster_home("/d/Shire/eastroad/western/stonebows");
	hobbit->move(TO);
    }
}

void
init()
{
    ::init();
    add_action("do_climb","climb");
}

int
do_climb(string str)
{
    if (!str)
    {
	write("Climb what?\n");
	return 1;
    }
    if ((str != "bridge") && (str != "from bridge") && (str != "down bridge"))
    {
	write("Climb where?\n");
	return 1;
    }
    write("You climb, with great effort, down the side of the slick stone "+
      "bridge.\n");
    SAYBB(" climbs carefully down the side of the bridge.");
    TP->move_living("M",GIRDLEY_DIR + "girpath1",1,0);
    SAYBB(" arrives climbing down from the bridge.");
    return 1;
}




void leave_shire()
{
    write("You cross the East Farthing border and leave the Shire.\n");
}