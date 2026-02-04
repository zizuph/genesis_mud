/* A gypsy. Mortricia 920927 */
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

#define CAMP_DIR        MORTRICIADIR + "camp/"
#define WEP_DIR         CAMP_DIR + "tent/equip/"
#define ARM_DIR         CAMP_DIR + "tent/equip/"
#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()

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
    if (i == G_KID) {
	set_name("kid");
	set_pname("kids");
        set_short("small kid");
        set_pshort("small kids");
        set_long(BSN(
            "It's a small gypsy kid."
        ));
        set_adj("small");
        set_stats(({10-jj,10,15+jj,10,10,10}));
    }
    if (i == G_YOUNGSTER) {
	set_name("gypsy");
	set_pname("gypsies");
        set_short("young gypsy");
        set_pshort("young gypsies");
        set_long(BSN(
            "It's a young gypsy."
        ));
        set_adj("young");
        set_stats(({20-jj,20,20+jj,20,20,20}));
    }
    if (i == G_GROWN) {
	set_name("gypsy");
	set_pname("gypsies");
        set_short("gypsy");
        set_pshort("gypsies");
        set_long(BSN(
            "It's a suspicious gypsy."
        ));
        set_adj("suspicious");
        set_stats(({30-jj,25,30+jj,30,30,30}));
    }
    if (i == G_OLD) {
	set_name("gypsy");
	set_pname("gypsies");
        set_short("old gypsy");
        set_pshort("old gypsies");
        set_long(BSN(
            "It's an old gypsy."
        ));
        set_adj("old");
        set_stats(({20-jj,15,20+jj,40,40,30}));
    }
    set_race_name("gypsy");
    set_gender(j);

    set_hp(9999);
    set_mana(9999);
    set_alignment(align);
    set_whimpy(30);
    set_random_move(20);

    add_prop(CONT_I_WEIGHT, 15000+i*25000);
    add_prop(CONT_I_VOLUME, 15000+i*25000);
    add_prop(CONT_I_MAX_WEIGHT, 20000+i*28000);
    add_prop(CONT_I_MAX_VOLUME, 20000+i*28000);

    seq_new("do_first");
    seq_addfirst("do_first", "@@dress_me");
}

dress_me()
{
    object wep, arm;

    seteuid(getuid(TO));
    if (g_age == G_KID) {
	wep = clone_object(WEP_DIR + "stick");
	arm = clone_object(ARM_DIR + "jacket");
    }
    if (g_age == G_YOUNGSTER) {
	wep = clone_object(WEP_DIR + "knife");
	arm = clone_object(ARM_DIR + "jacket");
    }
    if (g_age == G_GROWN) {
	wep = clone_object(WEP_DIR + "dagger");
	arm = clone_object(ARM_DIR + "cloak");
    }
    if (g_age == G_OLD) {
	wep = clone_object(WEP_DIR + "knife");
	arm = clone_object(ARM_DIR + "cloak");
    }
    wep -> move(TO);
    arm -> move(TO);
    command("wield all");
    command("wear all");
}
