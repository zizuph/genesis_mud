/*
 * /d/Genesis/start/human/sparkle/mouse.c
 * 
 * This file will serve two purposes. The first is to provide
 * a more dynamic generation of a mouse complete with unique
 * descriptions randomly chosen at the time of cloning. The
 * second purpose is to make the mouse more realistic in size
 * and stature as compared to the brand new newbie player. A
 * mouse should be relatively easy to kill even for a newbie.
 *
 * This file was originally modified from mouse.c, created by
 * Styles for the human start area on 22-March-1992.
 *
 * Copyright (c) June 2000, by Shadow deForest (Shadowlynx)
 *
 * Revision history:
 */
#pragma save_binary
#pragma strict_types

inherit "/std/creature";         /* generate a generic creature */
inherit "/std/combat/unarmed";   /* reference to unarmed combat */
inherit "/std/act/domove";       /* random move and follow */

#include <ss_types.h>            /* reference to skill types */
#include <wa_types.h>            /* reference to weapon types */
#include <formulas.h>            /* reference to hit/pen etc */
#include <macros.h>              /* reference to names/cloning etc */
#include <const.h>               /* reference to gender */
#include <stdproperties.h>       /* reference to setting properties*/

#define A_BITE  0                /* method of attack */

#define H_HEAD 0                 /* hit locations */
#define H_BODY 1
#define H_TAIL 2

/* Prototypes */
private string *randomname = ({"mouse", "rodent"});
private string *randomadj =  ({"tiny", "small", "large", "gigantic",
  "skinny", "fat", "dirty", "hairy", "frightened", "scared", "timid",
  "confused", "bewildered", "waterlogged", "noisy", "sneaky"});
private string *randomcoloradj = ({"black", "coal-black", "jet-black",
  "gray", "soot-gray", "sable-gray", "steel-gray", "ashen-gray", "brown",
  "silvery-gray", "coppery-brown", "russet-brown", "sorrel-brown",
  "chocolate-brown", "white", "chalk-white", "snow-white"});


public void
create_creature()
{
    if (!IS_CLONE)
	return;
    set_race_name("mouse"); 
    set_name(randomname[random(sizeof(randomname))]); /* names */
    set_pname(({"mice", "rodents"})); /* plural names */
    set_adj(randomadj[random(sizeof(randomadj))]); /* adjectives */
    add_adj(randomcoloradj[random(sizeof(randomcoloradj))]); /* colors */
    /* implode will choose one word from each list and combine */
    set_short(implode(query_adj(1), " ") + " " + lower_case(query_name()));
    set_pshort(implode(query_adj(1), " ") + " " + lower_case(query_pname()));
    set_long("This "+ short() +" is a regular inhabitant among" +
      " the various warehouses situated along the harbour." +
      " On occasion these rodents can be seen scurrying up" +
      " the rough hemp ropes anchoring ships to the piers.\n");
    /* sets random gender */
    if(random(2))
	set_gender(G_MALE);
    else
	set_gender(G_FEMALE);
    set_random_move(40); /* allows npc to move around */
    set_stats(({ 1, 3, 2, 1, 1, 2})); /* str/dex/con/int/wis/dis */
    set_skill(SS_SWIM, 45);     /* native skills */

    /* properties */
    add_prop(NPC_I_NO_LOOKS, 1); /* has no defining looks */
    add_prop(LIVE_I_NEVERKNOWN, 1); /* never introduced */
    add_prop(LIVE_I_NON_REMEMBER,1); /* unable to remember npc */
    add_prop(LIVE_I_SEE_DARK, 1); /* npc can see in the dark */
    add_prop(OBJ_I_NO_INS, 1); /* npc cannt be inserted into container */
    add_prop(LIVE_I_QUICKNESS, 2); /* more attacks per combat round */
    /* npc cannot be sold */
    add_prop(OBJ_M_NO_SELL, "Set the "+ short() +" free instead.\n");
    remove_prop(OBJ_I_NO_GET); /* can pick up npc */
    remove_prop(OBJ_I_NO_DROP); /* can drop npc */
    add_prop(CONT_I_WEIGHT, 1000); /* weight = 1 kilogram */
    add_prop(CONT_I_HEIGHT, 60); /* height = 6 centimeters */
    add_prop(CONT_I_VOLUME, 220); /* volume = 220 milliliters */

    /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
    set_attack_unarmed(A_BITE,   2, 3, W_IMPALE, 80, "sharp teeth");

    /* Hit_loc, *Ac against (impale/slash/bludgeon/magic), %hit, hit_desc */
    set_hitloc_unarmed(H_HEAD, ({ 5, 7, 3, 2 }), 30, "head");
    set_hitloc_unarmed(H_BODY, ({ 2, 4, 8, 0 }), 60, "body");
    set_hitloc_unarmed(H_TAIL, ({ 3, 0, 1, 0 }), 10, "tail");
}

