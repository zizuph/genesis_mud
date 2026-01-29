/*
 *	/d/Gondor/rohan/plains/b14.c
 *
 *	Coded by Olorin.
 *
 */
#pragma strict_types

inherit "/d/Gondor/rohan/plains/plain";

#include "/d/Gondor/defs.h"

#define RHARD		100
#define DID_VISIT_ROHAN "_ranger_visited_rohan"


public void
create_plain()
{
    set_geo("open");
    set_wet("damp");
    set_grass("long, thick green");
    set_land("the Eastfold");
    set_where("southeast");
    set_river_name("Mering Stream");
    set_special(5);
    set_rwhere("east");
    set_rhard(100);
    add_exit("c14", "north",     0, 5);
    add_exit("c15", "northeast", 0, 5);
/*
    add_exit("b14","east",crossing);
    add_exit("b14", "east", drown, RHARD);
*/
    add_exit(ROH_DIR + "road/er7",   "south",     0, 5);
    add_exit(ROH_DIR + "road/er6",   "west",      0, 5);
    set_extraline("It marks the border between Gondor and Rohan. "
      + "The trees growing on either side of the road to the south are "
      + "the northern parts of the Firienwood. ");

    set_drink_from( ({"mering","mering stream","stream","river"}) );
    set_npc_file(NPC_DIR + "rabbit");
    set_npc_number(1 + random(4));

    reset_room();

}

void
reset_room()
{
    ::reset_room();
    if (!present("sword", TO))
    {
	FIX_EUID;
        clone_object(WEP_DIR + "fssword")->move(TO);
    }
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (IS_RANGER(ob))
        ob->add_prop(DID_VISIT_ROHAN, 1);
}

