#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/dunland/wild/dunlendings.h"
#include "/d/Gondor/bits.h"

string    quest_reward();

public void
create_area_room()
{
    set_areatype(4);
    set_areadesc("in a large open field");
    set_area("southeast");
    set_areaname("Dunland");
    set_land("Enedwaith");
    set_extraline("You find yourself in the east part of a "
      + "farming field. But the last year it cannot have been "
      + "used for farming. Small houses of wood have been built "
      + "on the field, and the ground looks like it is quite " 
      + "heavily travelled. You can spot a fence at the south "
      + "edge of the field and in the middle of the field you "
      + "can spot a plow. To your north you can enter one of "
      + "the houses. At the corner of the eastern wall of the small "
      + "house you can spot a big pile.");

    add_item(({"pile", "big pile"}), "As you investige the pile "
      + "closer, you notice it is a pile of bones, to be more "
      + "exact, horse heads. There are even some head where flies "
      + "still are having themselves a decent meal. But most "
      + "of the heads are only skulls left.");
    add_item(({"head", "horse head", "heads", "horse heads"}), "The "
      + "pile is made of several horse heads, there must be atleast "
      + "a dozen, probably a bit more. One of the heads are crawling "
      + "with flies, apparently it is the newest addition to the "
      + "pile.");
    add_item(({"house","houses","wood"}), "The houses are very "
      + "simple, they give you the impression that they have been "
      + "built to serve for a temporarely reason, perhaps while "
      + "another building is being built?");
    add_item(({"ground", "field", "farming field", }), "The ground "
      + "was obviously used to grow crops some years ago, "
      + "but now some simple wooden houses has been built and the "
      + "ground has been trampled up because of heavy travelling.");
    add_item(({"fence", "broken fence"}), "Along the southern "
      + "edge of the field runs an old fence. It does not look "
      + "to be in a good shape.");
    add_item(({"plow","middle"}), "In the middle of the field, "
      + "far to the west of here, you can see a plow, it does "
      + "not look to be recently used, but you would have to "
      + "get closer to be sure.");

    set_no_exit_msg("northeast", "You begin to walk northeast " +
      "but quickly realize that it is overgrown with bushes and " +
      "other growth.\n");
    set_no_exit_msg("north", "To the north stands a house, you " +
      "clearly see the door from here. It is basically just to " +
      "walk in, should you wish to do so.\n");

    add_exit(DUN_WILD_ROOMS + "house09", "in", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field07", "west", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field12", "southwest", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field13", "south", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field14", "southeast", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field04", "northwest", 0, 2);
    add_exit(DUN_WILD_ROOMS + "field09", "east", 0, 2);

    add_npc(DUN_WILD_NPC + "dunl_soldier", 1 + (random(2)));
}


public int
throw_head(string arg)
{
    object  obj;
    mixed   fail;

    if (!strlen(arg))
    {
	notify_fail(capitalize(query_verb()) + " what?\n");
	return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
	"%o 'in' / 'into' / [the] [large] [horse]"
	+ " 'pile' [in] [the]", obj))
    {
	notify_fail("What do you want to " + query_verb() + " where?\n");
	return 0; /* give them a bit of syntax help */
    }

    if (fail = obj->query_prop(OBJ_M_NO_DROP))
    {
	if (!stringp(fail))
	{
	    fail = "You cannot throw the " + obj->short() + " away.\n";
	}

	notify_fail(fail);
	return 0;
    }


    if (!obj->id("_mearas_head_galuk_"))
    {
	write("You throw the " + obj->short() + " into the large pile. "
	  + "However, the " + obj->short() + " just rolls back down "
	  + "from the pile again, and you decide to pick it up.\n");
	say(QCTNAME(TP) + " throws the " + obj->short() + " into the "
	  + "large pile. However the " + obj->short() + " just rolls back " 
	  + "down and " + TP->query_pronoun() + " decides to take it up again.\n");
	return 1;
    }

    write("You throw the " + obj->short() + " into the large pile. "
      + "Flies already having a feast flies up and buzz around "
      + "before they all fly down and attack their new prey.\n");
    say(QCTNAME(TP) + " throws the " + obj->short() + " into the "

      + "large pile. Flies already having a large feast flies up and buzz "
      + "around. Then they discover their new prey and begins to feast on it.\n");

    set_alarm(2.0, 0.0, &quest_reward());

    obj->remove_object();
    return 1;
} 

string
quest_reward()
{
     if (TP->test_bit("Gondor", MEARAS_HEAD_GROUP, MEARAS_HEAD_BIT))
      {
        write("You do not feel more experienced when repeating this " +
            "task.\n");
      }

     if (!TP->test_bit("Gondor", MEARAS_HEAD_GROUP, MEARAS_HEAD_BIT))
      {
        write("You feel more experienced!\n");
        TP->set_bit(MEARAS_HEAD_GROUP, MEARAS_HEAD_BIT);
        TP->add_exp_quest(MEARAS_HEAD_EXP);
        LOG_QUEST(TP, MEARAS_HEAD_EXP, "GALUK HORSE HEAD");
      }
}


void
init()
{
    ::init();

    add_action(throw_head, "throw");
}


