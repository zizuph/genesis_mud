/*
 *  /d/Emerald/blackwall/delrimmon/npc/bird.c
 *
 *  This is one of the random animals that may be roaming around in the
 *  forests beside Del Rimmon.
 *
 *  Copyright (c) June 2001, by Cooper Sherry (Gorboth)
 *  Taken largely from Gnadnar's livestock in the Sirith Farm area
 *  in Gondor.
 */

#pragma strict_types

inherit "/std/creature.c";
inherit "/std/act/action.c";
inherit "/std/act/domove.c";
inherit "/std/combat/unarmed.c";

#include <const.h>		/* for G_FEMALE			*/
#include <ss_types.h>		/* for SS_dEFENCE, etc		*/
#include <stdproperties.h>	/* for NPC_I_NO_LOOKS, etc	*/
#include <wa_types.h>		/* for W_IMPALE, etc		*/

#include "/d/Emerald/blackwall/delrimmon/defs.h"

public void	create_creature();


/*
 * Function name:	create_creature
 * Description	:	set up the bird
 */
public void
create_creature()
{
    set_name( ({"hen", "fowl", "bird", "beast", "grouse" }) );
    set_pname( ({"hens", "chickens", "fowl", "poultry", "birds", "beasts" }) );
    set_race_name("chicken");
    set_gender(G_FEMALE);

    switch (random(3))
    {
    case 0:
	set_short("speckled forest hen");
    	set_adj( ({ "forest", "small", "speckled" }) );
    	set_long(BSN("This bird looks nearly flightless, though it"
          + " could probably use its wings in a pinch. It is mostly"
	  + " white with brown speckles around the head and neck."));
	break;
    case 1:
	set_short("plump white forest hen");
    	set_adj( ({ "forest", "white", "plump" }) );
    	set_long(BSN("This plump little bird doesn't look as if it"
          + " can fly, though its wings look sturdy enough. Its"
          + " feathers are solid white."));
	break;
    case 2:
	set_short("brown forest hen");
	set_adj( ({ "forest", "brown", "reddish-brown" }) );
	set_long(BSN("This forest hen has dark reddish brown feathers."));
	break;
    }

    set_alignment(0);
    set_stats(({ 5, 20, 5, 5, 5, 5 }));

    set_skill(SS_AWARENESS, 90);
    set_skill(SS_DEFENCE,   40);

    add_prop(CONT_I_WEIGHT, 1360);	/* 3 lbs */
    /* 15" tall by 10" long by 8" wide */
    add_prop(CONT_I_HEIGHT, 38);	/* 15 inches */
    add_prop(CONT_I_VOLUME, 19665);	/* 1200 cubic inches */

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " is not able to carry anything.\n");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_attack_unarmed(0,  5, 15, W_IMPALE,            50, "beak");
    set_attack_unarmed(1, 15, 10, W_SLASH | W_IMPALE,  75, "claws");

    set_hitloc_unarmed(0, ({ 12, 12,  5}),  40, "body");
    set_hitloc_unarmed(1, ({ 15,  5, 15}),  20, "left wing");
    set_hitloc_unarmed(2, ({ 15,  5, 15}),  20, "right wing");
    set_hitloc_unarmed(3, ({ 20, 10,  5}),  10, "head");
    set_hitloc_unarmed(4, ({ 10, 10, 20}),  10, "claws");

    set_act_time(20);
    add_act("emote cackles rapidly.");
    add_act("emote pecks at the ground.");
    add_act("emote walks slowly around, bobbing her head.");
    add_act("peer");

} /* create_creature */

