/* Created by Lucas */
/* Modified by Kieryn */
/* Further modified by Karath */
/* A merman for Coral Requiem */


inherit "/d/Emerald/std/emerald_monster";
inherit "/d/Emerald/std/aid_npc";

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include "/d/Emerald/eclipsia/edefs.h"

create_emerald_monster()
{
    set_name("mermaid");
    set_short("beautiful mermaid");
    set_adj("beautiful");
    set_race_name("merfolk");
    set_long("This lovely creature swims about the waters " +
        "with grace.  Girded in seashells, the mermaid " +
        "floats in and out of the buildings, conversing " +
        "with the other merfolk.\n");

    add_prop(LIVE_I_NEVERKNOWN,1);
    set_alignment(200);
    set_gender(1);
    set_random_move(8);
    set_act_time(10);
    add_act("say I hope you are enjoying your stay in our lovely town.");
    add_act("say Welcome to Coral Requiem.");
    add_prop(CONT_I_VOLUME, 75000);
    add_prop(CONT_I_WEIGHT, 75000);
    set_skill(SS_WEP_POLEARM, 75);
    set_skill(SS_PARRY, 50);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_SWIM, 100);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_AWARENESS, 50);

    set_stats(({(random(10)+50),(random(10)+60),(random(10)+50),
        80,80,(random(20)+40)}));

    MONEY_MAKE_CC(45)->move(this_object(), 1);
    MONEY_MAKE_SC(20)->move(this_object(), 1);
    add_equipment( ({ ECLIPSIA_OBJ + "spear", ECLIPSIA_OBJ + "bodice" }) );
}

void
attacked_by(object enemy)
{
  ::attacked_by(enemy);
  get_assistance(enemy);
}
