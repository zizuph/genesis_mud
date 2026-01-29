// file name: bicornb.c
// creator(s): Farlong, Ilyian (8 March, 1995)
// last update:
// purpose: Adult female bicorn for park area
// note: random adjectives taken from
//       Kazz's /d/Avenir/common/outpost/mon/guard.c
//       Various valuable horns are included as leftovers in the corpse
// bug(s):
// to-do:


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

#define SHU set_hitloc_unarmed

/* defines for attacks */
#define A_HORN 0
#define A_RHOOF 1
#define A_LHOOF 2
#define A_BITE 3

/* defines for hitlocs */
#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_HORN 3

string *randadj;

void
create_creature()
{
        randadj = ({"gentle","white-coated","nimble","lithe",
                    "beautiful","lovely","soft"});
        set_name("female_bicorn");
        set_race_name("bicorn");
        set_gender(G_FEMALE);
        set_adj(randadj[random(sizeof(randadj))]);
        set_long("This is a large adult creature that seems to bear "
                +"some distant relation to a unicorn, beautiful in "
                +"its grace and stature. It has two ivory-white horns "
                +"protruding from its head, and its coat is silky white, "
                +"which seems to shimmer in the light.\n");

        set_alarm(1.0,0.0,"set_m_in","walks in");
        set_alarm(1.0,0.0,"set_m_out","walks");
        set_alignment(0);

        set_skill(SS_HERBALISM, 35);

        set_stats(({110,100,105,70,70,100}));
        set_hp(query_max_hp());
        set_restrain_path(PK);

        set_random_move(1,0);

        set_attack_unarmed(A_HORN,40,40,W_IMPALE,50,"horns");
        set_attack_unarmed(A_RHOOF,15,13,W_BLUDGEON,20,"right hoof");
        set_attack_unarmed(A_LHOOF,15,13,W_BLUDGEON,20,"left hoof");
        set_attack_unarmed(A_BITE,10,15,W_BLUDGEON,10,"teeth");

        SHU(H_HEAD, ({7,7,7,15}),25,"head");
        SHU(H_BODY,({7,7,7,15}),25,"body");
        SHU(H_LEGS,({7,7,7,15}),25,"legs");
        SHU(H_HORN,({10,10,10,50}),25,"horns");

        set_cact_time(10);
         add_cact("emote throws her head back and lets out "
                 +"a piercing scream.");
         add_cact("emote sways her head back and forth, her sharp "
                 +"horns shimmering.");
         add_cact("emote becomes tense for a moment.");

        set_act_time(10);
         add_act("emote raises her head suddenly and sniffs the air.");
         add_act("emote shuffles around nervously.");
         add_act("glare softly all");
         add_act("sniff .");
         add_act("search weeds for herbs");

       trig_new("%s 'find' %s", "eat_herb");

       add_leftover(PK+"obj/white_horn","horn",2,0,0,0);

}

eat_herb(string str1, string str2)
{
      set_alarm(itof(random(6)),0.0,"command","eat herb");
      return 1;
}

