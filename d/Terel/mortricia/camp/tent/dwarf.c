/* A dwarf. Mortricia 920927 */
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
#define TENT_DIR        MORTRICIADIR + "camp/tent/"
#define ARM_DIR         TENT_DIR + "equip/"
#define WEP_DIR         TENT_DIR + "equip/"

#define G_KID           0
#define G_YOUNGSTER     1
#define G_GROWN         2
#define G_OLD           3

int g_age;

void
create_monster()
{
    int i, j, jj, align;

    if (!IS_CLONE)
        return;

    i = random(4);           /* age */
    g_age = i;
    align = 20 - 10 * i;
    j = random(2);           /* gender */
    jj = 3*j;
    set_name("dwarf");
    set_pname("dwarves");
    set_act_time(20 + 3 * i);

    if (i == G_KID) {
        set_short("small dwarf");
        set_pshort("small dwarves");
        set_long(BSN(
            "It's a small dwarf."
        ));
        set_adj("small");
        set_stats(({10-jj,10,15+jj,10,10,10}));
	add_act(({"scream"}));
    }
    if (i == G_YOUNGSTER) {
        set_short("young dwarf");
        set_pshort("young dwarves");
        set_long(BSN(
            "It's a young dwarf."
        ));
        set_adj("young");
        set_stats(({20-jj,20,20+jj,20,20,20}));
	add_act(({"whistle"}));
    }
    if (i == G_GROWN) {
        set_short("dwarf");
        set_pshort("dwarves");
        set_long(BSN(
            "It's a bored dwarf."
        ));
        set_adj("bored");
        set_stats(({30-jj,25,30+jj,30,30,30}));
	add_act(({"sigh"}));
    }
    if (i == G_OLD) {
        set_short("old dwarf");
        set_pshort("old dwarves");
        set_long(BSN(
            "It's an old dwarf."
        ));
        set_adj("old");
        set_stats(({20-jj,15,20+jj,40,40,30}));
	add_act(({"applaud"}));
    }
    set_race_name("dwarf");
    set_gender(j);

    set_hp(9999);
    set_mana(9999);
    set_alignment(align);

    add_prop(CONT_I_WEIGHT, 15000+i*25000);
    add_prop(CONT_I_VOLUME, 15000+i*25000);
    add_prop(CONT_I_MAX_WEIGHT, 20000+i*28000);
    add_prop(CONT_I_MAX_VOLUME, 20000+i*28000);

    set_all_hitloc_unarmed(2 + i * 10);
    set_all_attack_unarmed(2 + i * 10, 2 + i * 10);
    set_skill(SS_UNARM_COMBAT, 2 + i*(10-jj));
    set_skill(SS_DEFENCE, 2 + i*(10+jj));
    set_skill(SS_WEP_KNIFE, 2 + i*10);
    set_skill(SS_WEP_AXE, 2 + i*10);
    set_skill(SS_WEP_POLEARM, 2 + i*10);

    seq_new("do_first");
    seq_addfirst("do_first", "@@dress_me");
}

dress_me()
{
    seteuid(getuid(TO));
    if(g_age == G_KID) {
	clone_object(WEP_DIR + "stick") -> move(TO);
	clone_object(ARM_DIR + "jacket") -> move(TO);
    }
    if(g_age == G_YOUNGSTER) {
	clone_object(WEP_DIR + "knife") -> move(TO);
	clone_object(ARM_DIR + "jacket") -> move(TO);
    }
    if(g_age == G_GROWN) {
	clone_object(WEP_DIR + "axe") -> move(TO);
	clone_object(ARM_DIR + "mail") -> move(TO);
    }
    if(g_age == G_OLD) {
	clone_object(WEP_DIR + "axe") -> move(TO);
	clone_object(ARM_DIR + "jacket") -> move(TO);
    }
    command("wear all");
    command("wield all");
}
