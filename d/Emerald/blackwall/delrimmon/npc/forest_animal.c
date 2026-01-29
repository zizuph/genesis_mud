/*
 *  /d/Emerald/blackwall/del_rimmon/npc/forest_animal.c
 *
 *  This file can be one of three random forest animals which will
 *  roam around the forests in the Del Rimmon area.
 *
 *  Copyright (c) June 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/creature.c";
inherit "/std/act/action.c";
inherit "/std/act/domove.c";
inherit "/std/combat/unarmed.c";

#include <ss_types.h>           /* for SS_DEFENCE, etc          */
#include <stdproperties.h>      /* for NPC_I_NO_LOOKS, etc      */
#include <wa_types.h>           /* for W_IMPALE, etc            */

#include "/d/Emerald/blackwall/delrimmon/defs.h"

public void     create_creature();
public void     get_pelt();


/* global variables */
public int         Type = 0;

/*
 * Function name:       create_creature
 * Description  :       set up the creature
 */
public void
create_creature()
{
    add_name( ({ "animal", "creature", "_delrimmon_forest_animal" }) );

    switch (random(3))
    {
    case 0:
        set_name( ({ "fox", "beast" }) );
        set_race_name("fox");        
        set_short("small brown fox");
        set_adj( ({ "small", "brown" }) );
        set_long("Lean and brown, this small fox has a sleek coat of fur"
          + " which gleams in the open air. It seems to be poking around,"
          + " looking for food.\n");
        add_act("emote trots along the ground, sniffing the dirt.");
        add_act("emote stops completely still, and peers around.");
        add_act("emote sits and licks its tail.");
        Type = 1;
        break;
    case 1:
        set_name( ({ "bobcat", "cat", "beast" }) );
        set_race_name("bobcat");
        set_short("grey bobcat"); 
        set_adj( ({ "grey" }) );
        set_long("Prowling around the wilderness, this bobcat seems to"
          + " be looking for his next lunch. It takes little notice of"
          + " you.\n");
        add_act("emote sits down and licks its fur.");
        add_act("emote crouches, as if ready to pounce.");
        add_act("emote yawns lazily.");
        Type = 2;
        break;
    case 2:
        set_name( ({ "badger", "beast" }) );
        set_race_name("badger");
        set_short("large black badger");
        set_adj( ({ "large", "black", "squat" }) );
        set_long("This badger looks large and squat. He is ambling around"
          + " the area sniffing the ground. Occasionally he stops, as if"
          + " listening for something.\n");
        add_act("emote ambles around the area looking for food.");
        add_act("emote pushes some dirt around with its nose and snorts.");
        add_act("emote stops and scratches behind its ear for a bit.");
        Type = 3;
        break;
    }

    set_alignment(0);
    set_stats(({ 35, 80, 45, 30, 5, 50 }));

    set_skill(SS_AWARENESS, 90);
    set_skill(SS_UNARM_COMBAT, 70);
    set_skill(SS_DEFENCE,   60);

    add_prop(CONT_I_WEIGHT, 13600);      /* 30 lbs */
    /* 15" tall by 10" long by 8" wide */
    add_prop(CONT_I_HEIGHT, 45);        /* 20 inches */
    add_prop(CONT_I_VOLUME, 39330);     /* 2400 cubic inches */

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " is not able to carry anything.\n");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_attack_unarmed(0,  5, 15, W_IMPALE,            50, "teeth");
    set_attack_unarmed(1, 15, 10, W_SLASH | W_IMPALE,  75, "claws");

    set_hitloc_unarmed(0, ({ 12, 12,  5}),  40, "body");
    set_hitloc_unarmed(1, ({ 15,  5, 15}),  20, "left paw");
    set_hitloc_unarmed(2, ({ 15,  5, 15}),  20, "right paw");
    set_hitloc_unarmed(3, ({ 20, 10,  5}),  10, "head");
    set_hitloc_unarmed(4, ({ 10, 10, 20}),  10, "tail");

    set_act_time(20);
    get_pelt();

} /* create_creature */ 


/*
 * Function name:    get_pelt
 * Description   :    give the animal a pelt
 */
public void
get_pelt()
{
    object  skin = clone_object(DELRIMMON_DIR + "obj/pelt");

    skin->set_pelt(Type);
    skin->move(this_object());
} /* get_pelt */
