/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * eremite.c
 *
 * An eremite. Mortricia 920717
 * Modified by Sorgum 941002
 */

#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;

#define ARM_DIR SILVER_DIR + "armour/"

#include <ss_types.h>
#include <money.h>

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    set_name("Tony Bobnis");
    set_short("fat smelly human");
    set_long("A very fat, very smelly human.  He has such a big paunch " +
	     "that he has to lift up 100 pounds of shit just to get to " +
	     "his 1 inch chimp!  Grey masses of mold are on his body in " +
	     "various places, and there might even be a tuna sandwich " +
	     "hidden within the folds of fat.  He is thoroughly " +
	     "replulsive\n");
    set_adj("fat");
    set_race_name("human");
    set_gender(MALE);

    set_stats(({15, 15, 15, 15, 20, 15}));
    SET_MAX_HP;
    SET_MAX_MANA;
    set_alignment(200);
    set_skill(SS_DEFENCE, random(10) + 20);
    set_skill(SS_UNARM_COMBAT, random(5) + 10);

    set_act_time(30);
    add_act(({"fart", "cough"}));

    add_prop(LIVE_I_NEVERKNOWN, 1);
    
    set_all_hitloc_unarmed(5);
    set_all_attack_unarmed(10, 10);
}
