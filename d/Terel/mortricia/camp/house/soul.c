/* A lost soul. Mortricia 921001 */
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

#define ADJS            ({"lost", "lonely", "sad", "lurid", "lean"})
#define ALIGN           800

void
create_monster()
{
    string adj;

    if (!IS_CLONE)
        return;

    set_name("soul");
    adj = ADJS[random(sizeof(ADJS))];
    set_adj(adj);
    set_short(adj+" soul");
    set_long(BSN(
        "It's a "+adj+" soul. Once this poor soul was a proud " +
        "human."
        ));
    set_race_name("soul");
    set_gender(random(1));

    set_stats(({35,35,35,30,30,30}));
    set_hp(9999);
    set_mana(9999);
   set_alignment(-random(ALIGN));

    set_skill(SS_2H_COMBAT,  40);
    set_skill(SS_WEP_KNIFE,  30);
    set_skill(SS_WEP_SWORD,  40);
    set_skill(SS_DEFENCE,    30);
    set_skill(SS_PARRY,      30);
    set_skill(SS_AWARENESS,  30);

    add_prop(LIVE_I_NO_CORPSE, 1);
    seq_new("do_first");
    seq_addfirst("do_first", "@@dress_me");
}

dress_me()
{
    int i;

    seteuid(getuid(TO));
    H_CLONE("sword_s");
    H_CLONE("knife_s");
    H_CLONE("mail_s");

    i = random(3);
    if (i == 0) {
        H_CLONE("cloak_s");
    }
    if (i == 1) {
        H_CLONE("helmet_s");
    }
    if (i == 2) {
        H_CLONE("leggings_s");
    }
    command("wear all");
    command("wield all");
}
