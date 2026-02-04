/*
  A drunk. Mortricia 920927
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

    set_name("human");
    set_short("drunken human");
    set_long(BSN(
        "It's a drunken human."
        ));
    set_adj("drunken");
    set_race_name("human");
    set_gender(0);

    set_stats(({15,15,15,10,10,15}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(ALIGN);
    set_intoxicated(5);

    set_skill(SS_UNARM_COMBAT, 10);

    set_all_hitloc_unarmed(5);
    set_all_attack_unarmed(10, 10);

    set_chat_time(20);
    add_chat("Gee, two bartenders!?");

    set_act_time(40);
    add_act(({"buy beer", "drink beer", "burp"}));

    MONEY_MAKE_SC(15)->move(TO);

    set_cact_time(10);
    add_cact("giggle");
}
