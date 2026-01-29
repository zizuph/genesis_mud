/*
 * /d/Genesis/start/human/sparkle/orc.c
 * 
 * This file will serve two purposes. The first is to provide
 * a more dynamic generation of an orc complete with unique
 * descriptions randomly chosen at the time of cloning. The
 * second is to provide a comparible opponent for the true
 * newbie character.
 *
 * This file was originally modified from orc.c 
 * Creator: unknown
 *
 * Copyright (c) June 2000, by Shadow deForest (Shadowlynx)
 *
 * Revision history:
 */

#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#include "../defs.h"

string face();

void
create_monster()
{
    if (!IS_CLONE)
	return;

    set_race_name("orc"); 
    set_name("orc");
    set_adj(face());
    /* sets random gender */
    if(random(2))
	set_gender(G_MALE);
    else
	set_gender(G_FEMALE);
    set_long("This is probably one of the most worthless\n"+
      "creatures ever put upon this world.\n");

    /* default_config_npc(); */
    set_base_stat(SS_STR, random(5)+4);
    set_base_stat(SS_DEX, 7);
    set_base_stat(SS_CON, 6);
    set_base_stat(SS_INT, 5);
    set_base_stat(SS_WIS, 5);
    set_base_stat(SS_DIS, 6);
    set_hp(1000); /* reduced to correct level according to con. */
    set_aggressive(1);
    set_alignment(-150 + random(-50));

    add_prop(CONT_I_WEIGHT, 50000);
    add_prop(CONT_I_HEIGHT, 1600);
    add_prop(CONT_I_VOLUME, 45000);

    /*    set_attack_chance(50);  */

    set_skill(SS_WEP_KNIFE, 4);
}

string
face()
{
    string *faces;
    faces = ({"scarred", "grim", "grumpy", "young", "sturdy", "massive",
      "big", "nasty", "angry", "mean", "dirty", "ugly", "foul",
      "brutal", "dirty", "dirty", "ugly", "ugly"});
    return faces[random(sizeof(faces))];
}

void
arm_me()
{
    if (random(10)<3) {
	MONEY_MAKE(random(8) + 2,"copper")->move(TO);
	if (!random(100))
	    MONEY_MAKE(1,"silver")->move(TO);
    }

    if (random(5))
	return;

    clone_object(OBJ_DIR + "knife")->move(TO);
    command("wield all");
}
