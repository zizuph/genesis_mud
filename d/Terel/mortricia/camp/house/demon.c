/* A demon. Mortricia 921001 */
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

#define ADJS            ({"dreadful", "duteous", "devious"})
#define ALIGN           1200

void dress_me();

void
create_monster()
{
    string adj;

    if (!IS_CLONE)
        return;

    set_name("demon");
    adj = ADJS[random(sizeof(ADJS))];
    set_adj(adj);
    set_short(adj+" demon");
    set_long(BSN(
        "This "+adj+" demon is a lost soul. Once this poor soul was " +
        "a proud and great warrior. You wonder what evil he might " +
        "have done to achieve his present state."
        ));
    set_race_name("soul");
    set_gender(0);

    set_stats(({65,65,65,60,60,60}));
    set_hp(9999);
    set_mana(9999);
   set_alignment(-random(ALIGN));

    set_skill(SS_2H_COMBAT, 70);
    set_skill(SS_WEP_KNIFE, 60);
    set_skill(SS_WEP_AXE,   70);
    set_skill(SS_WEP_SWORD, 70);
    set_skill(SS_DEFENCE,   60);
    set_skill(SS_PARRY,     60);
    set_skill(SS_AWARENESS, 60);

    add_prop(LIVE_I_NO_CORPSE, 1);

    dress_me();
}

void
dress_me()
{
    int i;

    seteuid(getuid(TO));
    H_CLONE("sword_d");
    H_CLONE("axe_g");
    H_CLONE("mail_d");
    H_CLONE("helmet_d");

    i = random(2);
    if (i == 0) {
        H_CLONE("cloak_d");
    }
    if (i == 1) {
        H_CLONE("leggings_d");
    }
    command("wear all");
    command("wield all");
}
