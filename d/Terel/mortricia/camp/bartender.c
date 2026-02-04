/*
  A bartender. Mortricia 920927
 */
inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()

#define ALIGN           100

void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("bartender");
    set_short("fat bartender");
    set_long(BSN(
        "It's a fat bartender. Don't mess with him."
        ));
    set_adj("fat");
    set_race_name("gypsy");
    set_gender(0);

    set_stats(({99,99,99,99,99,99}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(ALIGN);

    set_skill(SS_UNARM_COMBAT, 100);

    set_all_hitloc_unarmed(1);
    set_all_attack_unarmed(20, 100);

    set_act_time(20);
    add_act(({"shout Last call!", "laugh", "say Just joking."}));

    set_cact_time(10);
    add_cact("grin");
}
