// file name: ulair_mon_f.c
// creator(s): Farlong
// last update: Ilyian (8 March, 1995)
// purpose:
// note:
// bug(s):
// to-do:

/* ulair_mon_f.c
The Underground LAIR MONster, Female, for park island
(Holm of the Icondrite) of Shadowelves
Farlong, 1-26-94 */

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";

#include "/d/Avenir/common/common.h"
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/elessar/lib/evilkill.h"

#define A_BITE  0

#define H_HEAD 0
#define H_BODY 1

create_creature() {

    if (!IS_CLONE)
        return;
        set_name("parent");
        set_race_name("creature");
        set_adj("parent");

        set_long("This is a medium-sized and very ugly"
                +" insect-like creature. This one appears to be female,"
                +" and you surmise that it will fight visciously to"
                +" protect its young.\n");

        set_gender(G_FEMALE);
        set_stats(({80,59,61,9,9,80}));
        set_hp(1000000);
        set_alignment(-20);

        set_aggressive(1);

        set_skill(SS_UNARM_COMBAT, 78);
        set_skill(SS_DEFENCE, 62);

        add_prop(CONT_I_WEIGHT,100*1000);
        add_prop(CONT_I_VOLUME,3500);
        add_prop(NPC_I_NO_RUN_AWAY,1);
        add_prop(LIVE_I_SEE_DARK,1);

        set_attack_unarmed(A_BITE, 70,30,W_SLASH,80,"pincers");
        set_attack_unarmed(1,18,20,W_SLASH,20,"legs");

        set_hitloc_unarmed(H_HEAD,({2,5,4,0}),40,"head");
        set_hitloc_unarmed(H_BODY,({20,29,23,9}),60,"body");

}
