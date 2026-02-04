/*
  A shop woman. Mortricia 920927
 */
inherit "/d/Terel/std/monster";
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

#define ALIGN           1000
#define CAMP_DIR        MORTRICIADIR + "camp/"

void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("tricia");
    add_name("woman");
    set_short("small gypsy woman");
    set_long(BSN(
        "It's a small gypsy woman that works in the weird shop."
        ));
    set_adj("small");
    set_gender(1);
    set_race_name("gypsy");

    set_stats(({50,50,50,99,99,99}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(ALIGN);
    enable_intro();

    set_skill(SS_UNARM_COMBAT, 80);
    set_all_hitloc_unarmed(5);
    set_all_attack_unarmed(50, 50);

    set_act_time(20),
    add_act(({"giggle"}));
}
