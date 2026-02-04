/* A ghost. Mortricia 921001 */
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
#include "haunt.h"

#define BS(xxx)         break_string(xxx, 70)
#define BSN(xxx)        break_string(xxx + "\n", 70)
#define TP              this_player()
#define TO              this_object()
#define CAMP_DIR        MORTRICIADIR + "camp/"
#define HAUN_DIR        CAMP_DIR + "house/"
#define EQUIP_DIR       HAUN_DIR + "equip/"
#define H_CLONE(xxx)    clone_object(EQUIP_DIR + xxx) -> move(TO)

#define ADJS            ({"mighty", "powerful", "potent"})
#define ALIGN           150

void
create_monster()
{
    string adj;

    if (!IS_CLONE)
        return;

    set_name("ghost");
    adj = ADJS[random(sizeof(ADJS))];
    set_adj(adj);
    set_short(adj+" ghost");
    set_long(BSN(
        "It's a "+adj+" ghost. Once this poor soul was a proud " +
        "human soldier."
        ));
    set_race_name("soul");
    set_gender(0);

    set_stats(({50,50,50,45,45,45}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(random(ALIGN)-ALIGN/2);

    set_skill(SS_2H_COMBAT, 55);
    set_skill(SS_WEP_KNIFE, 45);
    set_skill(SS_WEP_AXE,   55);
    set_skill(SS_DEFENCE,   45);
    set_skill(SS_PARRY,     45);
    set_skill(SS_AWARENESS, 45);

    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_UNDEAD, 20);

    seq_new("do_first");
    seq_addfirst("do_first", "@@dress_me");
}

dress_me()
{
    int i;

    seteuid(getuid(TO));
    H_CLONE("axe_g");
    H_CLONE("knife_g");
    H_CLONE("mail_g");

    i = random(3);
    if (i == 0) {
        H_CLONE("cloak_g");
    }
    if (i == 1) {
        H_CLONE("helmet_g");
    }
    if (i == 2) {
        H_CLONE("leggings_g");
    }
    command("wear all");
    command("wield all");
}
