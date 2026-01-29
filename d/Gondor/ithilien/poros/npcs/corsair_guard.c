/*
 *   /d/Gondor/ithilien/poros/npcs/corsair_guard.c
 *
 *   This is the corsair guard who will arrive when the captain is in badly
 *   need of help. They are very dangerous in packs as they have tough 
 *   knives. They are weaker then the other corsair, just to be alittle
 *   fair to the players.
 *
 *   Copyright (C): Daniel W. Mathiasen 1996
 *
 *   Sir Boron of Mordor
 *   
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/poros/npcs/corsair";

#include <stdproperties.h>
#include <composite.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

int   query_knight_prestige();

/*
int
second_life()
{
    find_living("gaerhir")->remove_protection();
    return 0;
}
*/

public void
create_corsair()
{
    ::create_corsair();

    add_name("guard");
    default_config_npc(80+random(15));
    set_base_stat(SS_DEX, 90+random(15));
    set_base_stat(SS_DIS, 85+random(15));
    set_skill(SS_WEP_KNIFE, 90+random(10));
    set_skill(SS_DEFENSE, 70+random(15));
    set_skill(SS_PARRY, 70+random(15));
    set_skill(SS_AWARENESS, 60 + random(15));

    set_act_time(4);
    add_act("close door");
}

public void
arm_me()
{
    /* XXX we have some kind of bug here ... even tho the dagger
     * is W_ANYH, it apparently can only be wielded in the right
     * hand -- and the shield for some reason insists on being
     * worn on the right arm.  however, if we make a dummy shield
     * and wear it first, it gets the right arm slot. then wear
     * all the other stuff, remove the dummy shield, wield
     * the dagger. gnadnar 19 june 1998
     */
    object	dummy;
    dummy = clone_object(ARM_DIR+"dushield");
    dummy->move(TO);
    command("wear shield");
    clone_object(POROS_DIR + "armours/leather")->move(this_object());
    clone_object(POROS_DIR + "armours/helmet")->move(this_object());
    clone_object(POROS_DIR + "armours/shield")->move(this_object());
    command("wear all");
    command("remove painted shield");
    dummy->remove_object();

    clone_object(POROS_DIR + "weapons/guard_dagger")->move(this_object());
    command("wield all");
}


int
query_knight_prestige() {return 75;}
