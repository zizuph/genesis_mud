/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * glow_worm.c
 *
 * A glow-worm. Mortricia 921017 
 * modified by Sorgum 941226
 * Modified by Shanoga, 20200921:
 *   removed max weight/volume, was preventing some imbues from working
 */

#include "/d/Terel/include/Terel.h"

inherit STDCREATURE;

inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/std/act/domove";

#include <wa_types.h>
#include <ss_types.h>

/*
 * Function name: create_creature
 * Description:   Create the creature.
 */
public void
create_creature()
{
    if (!IS_CLONE)
        return;

    ::create_creature();
    set_name("worm");
    add_name("glow-worm");
    set_short("glowing worm");
    set_long("It's a giant glow-worm. It glows with a faint light.\n");
    set_adj("glowing");
    set_race_name("worm");
    set_stats(({75, 41, 58, 2, 2, 50}));
    SET_MAX_HP;
    set_alignment(-20);
    set_gender(NEUTER);
    AGGRESSIVE;

    set_skill(SS_DEFENCE,   50 + random(5));
    set_skill(SS_AWARENESS, 50 + random(5));

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_QUICKNESS,  -50);
    
    add_prop(OBJ_I_WEIGHT,  15000);
    add_prop(OBJ_I_VOLUME,  9000);
    /*
    add_prop(CONT_I_MAX_WEIGHT, 18000);
    add_prop(CONT_I_MAX_VOLUME, 14000);
    */
    add_prop(CONT_I_LIGHT,      1);

    add_item(({"fangs"}), "The fangs are sharp.\n");
    add_item(({"legs"}), "The legs are small but countless.\n");
}

#define A_BITE  0
#define A_CLAW  1

#define H_BODY 0
#define H_LEGS 1

public void
cr_configure()
{
    add_attack(25, 20, W_IMPALE,   45, A_BITE);
    add_attack(25, 20, W_SLASH,    45, A_CLAW);
    add_attack(51, 65, W_BLUDGEON, 10, A_BODY);

    add_hitloc( ({70, 70, 70}), 75, "body", H_BODY);
    add_hitloc( ({20, 20, 20}), 25, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
     case A_BITE:return "fangs";
     case A_CLAW:return "legs";
     case A_BODY:return "body";
    }
}
