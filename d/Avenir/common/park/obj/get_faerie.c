
// file name: get_faerie.c
// creator(s): Ilyian (23 April, 1995)
// last update:
// purpose:
// note: This one can be held in inventory
//       She is a reward for killing [something]
//       She generates a light level of 15
// bug(s):
// to-do: Use her in some sort of rescue quest between dark -> park areas

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/domove";
inherit "/std/act/action";

#include "/d/Avenir/common/common.h"
#include <formulas.h>
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/sys/ss_types.h"
#include "/sys/macros.h"


/* defines for attacks */
#define A_WINGS 0
#define A_RHAND 1
#define A_LHAND 2
#define A_BITE 3
#define A_RFOOT 4
#define A_LFOOT 5

/* defines for hitlocs */
#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_WINGS 3

void
create_creature()

{
        set_name("astarte");
        add_name("faerie");
        set_race_name("faerie");
        set_short("shining faerie");
        set_gender(G_FEMALE);
        set_adj("shining");
        set_long("This miniscule creature looks just like a perfectly-"
                +"formed naked elven woman with silvery insect wings. She "
                +"flits around curiously, and seems to radiate a "
                +"dazzling light.\n");

        set_alarm(1.0,0.0,"set_m_in","flits in.");
        set_alarm(1.0,0.0,"set_m_out","flits");
        set_alignment(300);

        add_prop(LIVE_I_QUICKNESS, 100);
        add_prop(OBJ_I_WEIGHT,200);
        add_prop(OBJ_I_VOLUME,300);
        add_prop(CONT_I_WEIGHT,200);
        add_prop(CONT_I_VOLUME,300);

        remove_prop(OBJ_I_NO_GET);

        add_prop(OBJ_I_LIGHT, 15);

        set_stats(({2,70,30,30,90,50}));

        set_hp(query_max_hp());

        set_random_move(1,0);

        set_skill(SS_UNARM_COMBAT, 20);
        set_skill(SS_DEFENCE, 100);
        set_skill(SS_SNEAK, 60);
        set_skill(SS_HIDE, 60);
        set_skill(SS_AWARENESS, 85);
        set_skill(SS_BLIND_COMBAT, 93);

        set_attack_unarmed(A_WINGS,3,3,W_BLUDGEON,10,"wings");
        set_attack_unarmed(A_RHAND,3,3,W_BLUDGEON,10,"right hand");
        set_attack_unarmed(A_LHAND,3,3,W_BLUDGEON,10,"left hand");
        set_attack_unarmed(A_BITE,5,8,W_IMPALE,50,"bite");
        set_attack_unarmed(A_RFOOT,3,3,W_BLUDGEON,10,"right foot");
        set_attack_unarmed(A_LFOOT,3,3,W_BLUDGEON,10,"left foor");

        set_hitloc_unarmed(H_HEAD, 70, 2,"head");
        set_hitloc_unarmed(H_BODY, 95 , 60,"body");
        set_hitloc_unarmed(H_LEGS, 90 , 30,"legs");
        set_hitloc_unarmed(H_WINGS, 75 , 8,"wings");

        set_cact_time(10);
         add_cact("emote screams in a high pitched voice.");
         add_cact("glare enemy");
         add_cact("growl angr enemy");
         add_cact("emote waves her wings in irritation.");
         add_cact("whine soft");
         add_cact("fume");
         add_cact("point enemy");
         add_cact("shap enemy");
         add_cact("pout .");
         add_cact("emote utters a loud exclamation in a lost language.");


        set_act_time(5);
         add_act("giggle merrily");
         add_act("stretch");
         add_act("emote flits around your head.");
         add_act("emote stretches her wings and yawns.");
         add_act("smile cute");
         add_act("hiccup");
         add_act("laugh happily");
         add_act("emote rubs her eyes and smiles tiredly.");
         add_act("emote sings a sad song in a forgotten language.");
         add_act("emote flits around happily.");
         add_act("emote sings in a high, lilting voice.");
         add_act("emote blinks.");
         add_act("gasp");
         add_act("hide");
         add_act("twinkle");
         add_act("laugh softly");
         add_act("hide");
         add_leftover("/d/Avenir/ilyian/obj/faerie_wing","wing",2,0,0,0);

//            change this later

}

