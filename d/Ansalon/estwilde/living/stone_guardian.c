

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

inherit "/std/act/asking";
inherit AC_FILE

void
create_creature()
{

    set_name("guardian");
    set_adj("stone");
    set_race_name("golem");
    set_short("stone guardian");

    set_long("This squat stone statue is a tomb " +
      "guardian. Long ago, when priests were common " +
      "in the realms, this statue was blessed with the " +
      "power of Reorx, and even now it stands ready to " +
      "protect this cairn from unwelcome intruders.\n");


    set_stats(({200, 130, 200, 80, 60, 100}));
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_SEE_DARK, 1);

    set_hp(10000);
    set_alignment(0);

    set_default_answer("The stone guardian is unresponsive.\n");

    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_BLIND_COMBAT, 75);
    set_skill(SS_AWARENESS,100);

    NEVERKNOWN;

    set_attack_unarmed(1, 30, 45, W_BLUDGEON, 50, "left fist");
    set_attack_unarmed(2, 30, 45, W_BLUDGEON, 50,"right fist");

    set_hitloc_unarmed(1, 30, 90, "body");
    set_hitloc_unarmed(2, 30, 10, "head");


}
