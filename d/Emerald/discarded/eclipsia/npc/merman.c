/* Created by Lucas */
/* A merman for Coral Requiem */


inherit "/d/Emerald/std/emerald_monster";
inherit "/d/Emerald/std/aid_npc";

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include "/d/Emerald/eclipsia/edefs.h"

void
equip_me()
{
    object trident;
   
    setuid();
    seteuid(getuid());

    if (trident = clone_object(ECLIPSIA_OBJ + "trident"))
    {
        trident->move(this_object(), 1);
        trident->wield_me();
    }

    MONEY_MAKE_CC(25)->move(this_object(), 1);
    MONEY_MAKE_SC(15)->move(this_object(), 1);
}

create_emerald_monster()
{
    set_name("merman");
    set_short("young merman");
    set_adj("young");
    set_race_name("merfolk");
    set_long("The strapping young merman is quite an amazing " +
        "creature.  With the head and torso of a man, " +
        "and the lower body of a fish, he is quite an agile " +
        "swimmer.\n");

    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop("_coral_requiem_npc_", 1);
    add_prop(MAGIC_I_BREATH_WATER,1);
    set_alignment(200);
    set_random_move(8);
    add_act("say Welcome to our beautiful town.");
    add_act("say Isn't the water particularly warm today?");
    add_prop(CONT_I_VOLUME, 75000);
    add_prop(CONT_I_WEIGHT, 75000);
    set_skill(SS_WEP_POLEARM, 65);
    set_skill(SS_PARRY, 50);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_SWIM, 100);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_AWARENESS, 45);

    set_stats(({(random(40)+40),(random(50)+20),(random(40)+40),
        70,70,(random(40)+20)}));

    equip_me();
}

attacked_by(object enemy)
{
  ::attacked_by(enemy);
    get_assistance(enemy);
}
