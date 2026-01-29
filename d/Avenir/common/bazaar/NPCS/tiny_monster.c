/*
 * A tiny test-monster. For Avenir by Mortricia Dec. 1994
 */
inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";

inherit "/d/Avenir/common/bazaar/NPCS/call_for_help";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#define TP              this_player()
#define TO              this_object()
#define ETO             environment(TO)

#define ALIGN           100

void
create_monster()
{
    if (!IS_CLONE) return;

    set_name("monster");
    set_short("small monster");
    set_long(
        "It's a small test-monster.\n"
        );
    set_adj("small");
    set_race_name("human");
    set_gender(0);

    set_stats(({5,5,5,5,5,5}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(random(2*ALIGN) - ALIGN);

    set_skill(SS_UNARM_COMBAT, 20);

    set_all_hitloc_unarmed(10);
    set_all_attack_unarmed(10, 10);
}
