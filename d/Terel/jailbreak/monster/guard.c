/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * guard.c
 *
 * A prison guard.
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <money.h>

#define ARM_DIR JAIL_DIR + "armour/"
#define WEP_DIR JAIL_DIR + "weapon/"


/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    set_name("guard");
    
    set_short("Prison guard");
    set_long("A guard in the Calahtin jail.\n");
    
    set_race_name("human");
    set_gender(MALE);
    set_alignment(-400);

    set_stats(({80, 75, 70, 60, 65, 65}));
    SET_MAX_HP;
    
    set_skill(SS_DEFENCE,      50 + random(11));
    set_skill(SS_UNARM_COMBAT, 55 + random(11));
    set_skill(SS_PARRY,        77 + random(11));
    set_skill(SS_WEP_SWORD,    50 + random(5));
    set_skill(SS_WEP_KNIFE,    50 + random(5));
    set_skill(SS_BLIND_COMBAT, 60);
    set_skill(SS_AWARENESS,    70);
    
    
}

