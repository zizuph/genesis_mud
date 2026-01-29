// file name: ulair_mon_c.c
// creator(s): Farlong
// last update: Ilyian (8 March, 1995)
// purpose:
// note:
// bug(s):
// to-do:

/* ulair_mon_c.c
The Underground LAIR MONster, Child, for park island
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
        set_race_name("creature");
        set_adj("young");
        set_pshort("young creatures");
        set_long("A hideous creature stands before you."
        +" It is long and flat, like a gigantic orange beetle,"
        +" and bears down on you with sharp, pincer-like jaws."
        +" Six legs jut out from its armored torso, while three"
        +" large, compound eyes dominate the head. You guess that"
        +" is, it certainly is not happy with your presence!\n");

        set_gender(G_NEUTER);
        set_stats(({40,35,30,4,4,40}));
        set_hp(1000000);
        set_alignment(-20);

        set_aggressive(1);

        set_skill(SS_UNARM_COMBAT,30);
        set_skill(SS_DEFENCE,20);

        add_prop(CONT_I_WEIGHT, 34000);
        add_prop(CONT_I_VOLUME, 1000);
        add_prop(NPC_I_NO_RUN_AWAY,1);
        add_prop(LIVE_I_SEE_DARK,1);

        set_attack_unarmed(A_BITE, 30,16,W_SLASH,80,"pincers");
        set_attack_unarmed(A_LEGS, 10,10,W_SLASH,20,"legs");

        set_hitloc_unarmed(H_HEAD,({2,5,4,0}),40,"head");
        set_hitloc_unarmed(H_BODY,({20,29,23,9}),60,"body");

}
