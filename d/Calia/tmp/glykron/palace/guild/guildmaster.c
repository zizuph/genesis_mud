/*      the guildmaster mobile in the crystalline palace

    coder(s):   Glykron

    history:     4. 5.93    created                         Glykron
                29. 8.93    calian object inherited         Glykron

*/

inherit "/d/Calia/tmp/glykron/std/calian";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#include "defs.h"


int
no_attack_des()

{
  TP->catch_msg("Caliana will not allow anyone to " +
                                "attack her guildmaster.\n");
  return 1;
}


void
create_calian()
{
    if (!IS_CLONE)
        return;

    add_name("guildmaster");
    set_race_name("human");
    set_adj("grim-faced");
    set_title("the Guildmaster and Exalted Member of Caliana's Elite Guard");
    set_long("He is a grim-faced human dressed in blue.\n");
    set_base_stat(SS_INT, 200);
    set_base_stat(SS_WIS, 200);
    set_base_stat(SS_DIS, 200);
    set_base_stat(SS_STR, 200);
    set_base_stat(SS_DEX, 200);
    set_base_stat(SS_CON, 200);
    set_base_stat(SS_OCCUP, 200);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_DEFENCE, 100);
    set_hp(100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
    add_prop(OBJ_M_NO_ATTACK, "Caliana will not allow someone to attack her " +
                              "guildmaster.\n");
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
}


