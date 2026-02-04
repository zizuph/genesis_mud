/* File         : /d/Terel/silver/include/road_base.c
 * Creator      : Tomas
 * Date         : August 2000
 * Purpose      : Base file for Silver Forest.
 * Related Files:
 * Comments     : Taken from Elderwood road.c file.
 * Modifications: Modified by Pasqua April 2006 unq_no_move
 * Lucius - 2021-03
 * - Exclude 'up','down' from custom unq_no_move.
 */
#include "/d/Terel/include/Terel.h"
#include "defs.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <filter_funs.h>

inherit INCLUDE + "cold_room.c";
inherit "/d/Terel/std/room_tell.c";

#include <stdproperties.h>

#define PLAYER_I_ATTACKED_CARAVAN "_player_i_attacked_caravan"

void
init()
{
    ::init();
    add_action("do_smell",  "smell",  0);
    start_room_tells();
}


public string
smell_desc()
{
    return "The air smells of fresh evergreens.\n";
}

/*
 * Function name: do_smell
 * Description:   Handle the smell action
 * Returns:       1/0
 */
public int
do_smell(string str)
{
    NF("Smell what?\n");
    if (!strlen(str))
	return 0;

    if (str == "air" || str == "scent" || str == "strange scent")
    {
	write(smell_desc());
	return 1;
    }
    return 0;
}

public void
arrow_shot(object random_victim)
{
    tell_room(E(random_victim), "You notice sudden movement, as if something was shot "+
      "from between the trees.\n" + QCTNAME(random_victim) + " stuggers, and "+
      "collapses to the ground, with throat pierced by an arrow.\n");
    random_victim->set_hp(0);
    random_victim->do_die(TO);
}

public void
bandit_ambush(object victim)
{
    /* bandits are already here*/
    if(sizeof(filter(all_inventory(E(victim)), &->id("_silver_forest_bandit"))))
	return;

    int bandit_c = random(2) + 2;
    object bandit;
    for(int i = 0; i < bandit_c; ++i)
    {
	bandit = clone_object(NPC + "bandit");
	bandit->set_recon();
	bandit->add_prop(PLAYER_I_ATTACKED_CARAVAN, 1);
	bandit->move_living("jumping down from a tree", E(victim), 0, 0);
	bandit->command("kill " + victim->query_name());
    }
}

/* Called by caravan, it creates an ambush of bandits.*/
public void
ambush_caravan(object defender)
{
    /* All caravan objects */
    object *caravan = FILTER_LIVE(filter(all_inventory(TO), &->is_caravan()));
    mixed where;
    /* they appear on the road */
    if(!sizeof(caravan))
    {
	string *wagons = ({});
	for(int i = 0; i < sizeof(all_inventory(TO)); ++i)
        {
	    if(stringp(all_inventory(TO)[i]->query_inside()) &&
	      all_inventory(TO)[i]->query_inside()->is_manned)
		wagons += ({all_inventory(TO)[i]->query_inside()});
        }

	if(!sizeof(wagons))
	    return;
	/* caravan members there */
	caravan = FILTER_LIVE(filter(all_inventory(find_object(wagons[0])), &->is_caravan()));

    }
    if(!sizeof(caravan))
	return;
    if(!random(5))
    {
	object arrow_victim = caravan[random(sizeof(caravan))];
	set_alarm(3.0, 0.0, &arrow_shot(arrow_victim));
	caravan -= ({arrow_victim});
    }
    if(!sizeof(caravan))
	return;
    if(!random(5))
	set_alarm(1.0, 0.0, &bandit_ambush(caravan[random(sizeof(caravan))]));

}

public int
caravan_block(mixed attacker)
{
    return sizeof(filter(all_inventory(TO), &->id("_silver_forest_bandit")));
}

public void
create_room()
{
    ::create_room();
    set_short("silver forest road");
    set_long("You hear the snow crunch beneath you as you " +
      "continue to travel on the snow covered " +
      "road. Drifts of snow have built up along the " +
      "treeline along the sides of the road.\n");


    add_prop("_room_m_da_dragonsteed_no_land","The trees " +
      "have extended their branches creating " +
      "a makeshift canopy over the road. The branches " +
      "are too thick for your dragon to land safely.\n");

    add_item(({"hoof prints","horse hoof prints","prints"}),
      "The road is rutted with several hoove prints in the snow.\n");

    add_item(({"mountain","mountain range","pass"}),
      "The vast jagged mountain range extends all along the " +
      "northern horizon. You notice what looks like " +
      "a mountain pass towards the middle of the field.\n");

    add_item(({"field","snow covered field"}),
      "The field is covered in snow with the exception of some " +
      "rocky exposed areas. Clumps of tall frozen grass " +
      "grow about rocks and shallow areas of the snow drifts.\n");

    add_item(({"snow covered road","snowy road","road","dirt road"}),
      "The snow covered road leads north and southward "+
      "through a densely populated forest, which grows " +
      "on either side of the road.\n");

    add_item(({"forest","trees","undergrowth", "bushes",
	"shrubs","plants","evergreens","floor",
	"ground","shrub","plant","evergreen",
	"bush"}),
      "The evergreens loom high overhead creating a " +
      "semi-shaped canopy over the road. Dense undergrowth " +
      "covers the forest floor on either sides of the road.\n");

    add_item(({"branches","tree branches"}),"The tree branches " +
      "extend from either side entertwining over the road.\n");

    add_item(({"snow"}),"The snow covers everything, piling up along " +
      "the road and at the tree basin.\n");

    set_tell_time(300 + random(200));
    add_tell("You hear birds chirping off in the distance.\n");

    add_cmd_item(({"rocks","rock","pebble","pebbles"}),
      ({"collect","gather","get"}),"@@get_pebble");

    reset_room();
}

int
exits()
{
    if ((TP->query_skill(SS_LOC_SENSE) > 60))
    {
	return 0;
    }
    return 1;
}

public int
get_pebble()
{
    object pebble;

    seteuid(getuid(TO));
    pebble = clone_object(CALATHIN_DIR + "houses/obj/pebble");
    pebble->move(TP);
    write("You pickup a pebble from the ground.\n");
    say(QCTNAME(TP) + " reaches into the snow and picks up a pebble.\n");
    return 1;
}

public int
unq_no_move(string str)
{
    string verb = query_verb();
    if (verb == "up" || verb == "down")
        return ::unq_no_move(str);

    notify_fail("The forest is too dense to enter in that direction.\n");
    return 0;
}

