/*
 * /d/Gondor/anorien/druedain/rangerfield.c
 * 
 * modified for new rangers: Tigerlily, Feb. 6, 2004
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"

#define OTHER_ROOM ("/d/Gondor/anorien/druedain/rangerpath3")

private void    add_stuff();
private int     enter_house();
private int     enter_portal();

static object  Ranger,
               Ranger2;

public void
create_area_room()
{
    set_areatype(2);
    set_areadesc("field");
    set_area("western");
    set_areaname("the Druedain Forest");
    set_land("Gondor");
    set_grass("soft, light green");
    set_treetype("large oaks");
    set_extraline("Before you to the west is a wooden house, built in between "+
       "two shoulders of a hill. An open doorway faces you, and you glimpse "+
       "a large hall on the inside. To the south the White Mountains dominate "+
       "the entire horizon, as this field lies almost by their feet. "+
       "To the east is the edge of the looming Druedain Forest. A path "+
       "starts here, entering the woods through what seems like a wooden portal, "+
       "consisting of two great oaks. You notice a little clearing to the north.");

    add_exit(ANO_DIR+"druedain/rangerpath3",  "east",  enter_portal, 1);
    add_exit(ANO_DIR+"druedain/rangerfield2", "north", 0);
#ifndef  NEW_RANGERS_OPEN 
    add_exit(RANGER_GON_DIR+"boardhall","west",  &enter_house(), 0);
#endif

#ifdef  NEW_RANGERS_OPEN 
    add_exit(RANGERS_DIR + "hq/boardhall", "west",  &enter_house(), 0);
#endif

    add_item("path","The path starts (or ends) here, and enters the forest through\n"+
	     "a strange tree-portal in the forests edge.\n");
    add_item("portal","The portal consists of two great oaks, and from each a large\n"+
	     "bough has grown upwards and towards the other, and then in some strange\n"+
	     "way grown together, as a giant oak with twin trunks. Through this portal\n"+
	     "a path enters the field.\n");
    add_item("house","The house is a two-story timber-latched building built half-way\n"+
	     "into the hillside. The only windows on the ground floor must be here on\n"+
	     "the front, as the lower slopes of the hill seem to be level with the\n"+
	     "second floor on the north and south end of the house, and probably also\n"+
	     "at the back. An open doorway faces you here on the east side of the house.\n");
    add_item("doorway","The doorway is invitingly open.\n");
    add_item("windows","You don't see anything through the closed, bolted windows.\n");
    add_item(({"tree", "trees"}), "They look as though they might conceal "
        + "almost anything - or anyone.\n");

    set_up_herbs(({ HERB_DIR + "lothore", HERB_DIR + "redweed", 
		     SHIRE_HERB_DIR + "huckleberry", }),
		 ({"ground","field"}), 5);
    add_item("ground", "Grass, flowers, herbs and plants grow on the ground.\n");
    add_stuff();

    clone_object("/d/Genesis/ateam/aoe/obj/ranger_tree")->move(this_object(), 1);
    clone_object("/d/Genesis/ateam/aoe/obj/ranger_tree_2008")->move(this_object(), 1);
}

private int
enter_portal()
{
    write("You pass through the strange portal, and enter the Druedain Forest.\n");
    return 0;
}

private int
enter_house()
{
    object tp = this_player();

    if (tp->query_npc()) 
	    return 1;
    tp->catch_msg("You walk through the open doorway of the house.\n");
    if (tp->query_autosneak())
    {
	tp->catch_msg("You stop being stealthy as you enter.\n");
	tp->set_autosneak(0);
	tp->add_prop("_ranger_was_stealthy", 1);
    }
    return 0;
}

private void
add_stuff()
{
    if (!objectp(Ranger))
    {
	Ranger = clone_object(NPC_DIR + "random_ranger");
    Ranger->arm_me();
	Ranger->add_prop(OBJ_I_HIDE,random(Ranger->query_skill(SS_HIDE)));
	Ranger->move_living("down", TO);
    }
    if (!objectp(Ranger2)) 
    {
	Ranger2 = clone_object(NPC_DIR + "random_ranger");
    Ranger2->arm_me();
	Ranger2->set_moving();
	Ranger2->move_living("down", TO);
    }
}

public void
reset_room()
{
    ::reset_room();
    add_stuff();
}


public void
enter_inv(object ob, object from)
{
    int	n;

    ::enter_inv(ob, from);

    FIX_EUID;

    if (!interactive(ob) ||
        ob->query_wiz_level() ||
        OTHER_ROOM->query_friend_or_foe(ob->query_real_name()) >= 0)
    {
	return;
    }

    n = ((ob->query_max_hp() * 100) / 50);
    ob->heal_hp(-n);
    if (ob->query_hp() <= 0)
    {
	ob->heal_hp(10);
    }
    n = ((ob->query_max_mana() * 100) / 50);
    ob->add_mana(-n);
    ob->set_fatigue(0);
    n = ob->query_prop(LIVE_I_SEE_DARK);
    ob->add_prop(LIVE_I_SEE_DARK, -10);
    set_alarm(120.0, 0.0, &ob->add_prop(LIVE_I_SEE_DARK, n));
    ob->catch_msg("A bolt of lightning knocks you flying! You are burnt "+
	"and blinded!\n");
    tell_room(TO, "The sky is rent by a bolt of lightning! It knocks " +
	QTNAME(ob) + " sprawling to the east.\n", ob);
    ob->move(OTHER_ROOM);
    tell_room(OTHER_ROOM, 
	QCTNAME(ob) + " stumbles in from the west.\n", ob);
}
