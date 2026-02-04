/* A ghostly grave digger. Mortricia 921027 */
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
#define WEP_DIR         MANSION + "obj/"
#define ARM_DIR         MORTRICIADIR + "armours/"
#define ALIGN           10

void
create_monster()
{
    if (!IS_CLONE) return;

    set_name("grave digger");
    add_name("digger");
    set_short("ghostly grave digger");
    set_long(BSN(
        "This ghostly figure is nothing but the grave digger. " +
        "Since there not many people living in the mansion " +
        "nowadays, there is not much for him to do. Instead " +
        "he has taken on the duty to maintain the graveyard " +
        "area here at the mansion. But, if you are not careful " +
        "he maybe has to resume his original job."
    ));
    set_adj("ghostly");
    set_race_name("human");
    set_gender(0);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_stats(({30,30,30,40,40,30}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(ALIGN);

    set_skill(SS_UNARM_COMBAT, 10);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_AWARENESS, 40);

    set_all_hitloc_unarmed(20);
    set_all_attack_unarmed(10, 10);

    seq_new("do_first");
    seq_addfirst("do_first", "@@dress_me");
}

dress_me()
{
    object shovel;

    seteuid(getuid(TO));

    shovel = clone_object(WEP_DIR + "shovel");
    shovel -> move(TO);
    command("wield shovel");
}
