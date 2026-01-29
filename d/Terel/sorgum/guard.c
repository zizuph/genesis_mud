/*
  A camp guard. Mortricia 920927
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


#include "/secure/std.h"

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()

#define ALIGN           -100
#define ARM_DIR         MORTRICIADIR + "armours/"
#define WEP_DIR         MORTRICIADIR + "weapons/"

void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("guard");
    set_short("dark guard");
    set_long(BSN(
        "It's a guard, protecting this camp from trouble-makers."
        ));
    set_adj("dark");
    set_race_name("gypsy");
    set_gender(0);

    set_stats(({40,40,40,30,30,40}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(ALIGN);
 
    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_WEP_SWORD, 50);

    set_all_hitloc_unarmed(20);
    set_all_attack_unarmed(20, 20);

    seq_new("do_first");
    seq_addfirst("do_first", "@@dress_me");
}

dress_me()
{
    object sword, cloak;

    seteuid(getuid(TO));
    cloak = clone_object(ARM_DIR + "cloak");
    cloak -> set_short("brown cloak");
    cloak -> set_long("A brown cloak.\n");
    cloak -> set_adj("brown");
    cloak -> move(TO);
    command("wear cloak");

    sword = clone_object(WEP_DIR + "plain_sword");
    sword -> move(TO);
    command("wield sword");
}


public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id)
{
     mixed result;
     command("say Ouch! You hit me!\n");
     result = ::hit_me(wcpen, dt, attacker, attack_id);
     return result;
}
