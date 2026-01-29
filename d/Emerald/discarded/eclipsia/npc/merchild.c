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
    setuid();
    seteuid(getuid());

    MONEY_MAKE_CC(15)->move(this_object(), 1);
}

create_emerald_monster()
{
    set_name("merchild");
    set_short("young merchild");
    set_adj("young");
    set_race_name("merfolk");
    set_long("The young merchild is quite an amazing " +
        "creature.  With the head and torso of a boy, " +
        "and the lower body of a fish, he is quite an agile " +
        "swimmer.\n");

    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop("_coral_requiem_npc_", 1);
    add_prop(MAGIC_I_BREATH_WATER,1);
    set_alignment(200);
    set_random_move(8);
    add_act("say Welcome to our beautiful town.");
    add_act("say Hello. Would you like to race me...I'm the fastest "+
	"swimmer in the city!");
    add_prop(CONT_I_VOLUME, 55000);
    add_prop(CONT_I_WEIGHT, 55000);
    set_skill(SS_UNARM_COMBAT, 45);
    set_skill(SS_PARRY, 40);
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_SWIM, 100);
    set_skill(SS_BLIND_COMBAT, 40);
    set_skill(SS_AWARENESS, 35);

    set_stats(({(random(20)+20),(random(30)+20),(random(20)+20),
        40,40,(random(20)+20)}));

    equip_me();
}

attacked_by(object enemy)
{
  ::attacked_by(enemy);
    get_assistance(enemy);
}
