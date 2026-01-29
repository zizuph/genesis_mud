
// file name: bicorna.c
// creator(s): Farlong
// last update: Ilyian (8 March, 1995)
// purpose: Adult male bicorn for park area
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
inherit "/d/Avenir/inherit/hitlocs";

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
        randadj = ({"strong","massive","angry","swift","hungry",
                    "large","fast","sleek","black"});
        set_name("male_bicorn");
        set_race_name("bicorn");
        set_gender(G_MALE);
        set_adj(randadj[random(sizeof(randadj))]);
        set_long("This is a large adult creature that seems to bear "
                +"some distant relation to a unicorn, except it is "
                +"not as graceful and it has two jet black horns "
                +"protruding from its head. Its coat is shiny black, "
                +"and it seems to shimmer in the light.\n");

        set_alarm(1.0,0.0,"set_m_in","struts in");
        set_alarm(1.0,0.0,"set_m_out","struts");
        set_alignment(0);

        set_stats(({125,140,150,70,70,140}));
        set_hp(query_max_hp());
        set_restrain_path(PK);
        set_aggressive(1);
        set_random_move(1,0);

        set_attack_unarmed(A_HORN,40,60,W_IMPALE,50,"horns");
        set_attack_unarmed(A_RHOOF,15,15,W_BLUDGEON,20,"right hoof");
        set_attack_unarmed(A_LHOOF,15,15,W_BLUDGEON,20,"left hoof");
        set_attack_unarmed(A_BITE,10,17,W_BLUDGEON,10,"teeth");

        SHU(H_HEAD, ({7,7,7,15}),25,"head");
        SHU(H_BODY,({7,7,7,15}),25,"body");
        SHU(H_LEGS,({7,7,7,15}),25,"legs");
        SHU(H_HORN,({10,10,10,50}),25,"horns");

        set_cact_time(10);
         add_cact("emote throws his head back and lets out "
                 +"a furious scream.");
         add_cact("emote sways his head back and forth, his sharp "
                 +"horns gleaming blackly.");
         add_cact("emote becomes tense for a moment.");

        set_act_time(20);
         add_act("emote raises his head suddenly and sniffs the air.");
         add_act("emote shuffles around nervously.");
         add_act("glare . all");
         add_act("sniff .");
         add_act("growl softly");

       add_prop(LIVE_I_NEVERKNOWN, 1);
       add_prop(NPC_I_NO_LOOKS, 1);
       add_prop(CONT_I_VOLUME, 88000);
       add_prop(CONT_I_WEIGHT, 100000);
       add_prop(CONT_I_HEIGHT, 300);
       add_prop(LIVE_I_QUICKNESS, 95);

       add_leftover(PK+"obj/black_horn","horn",2,0,0,0);

}

int special_attack(object enemy)
{
   string    str, hitloc;
   mixed    *hitres;

   if(random(5))
     return 0;

    if(enemy->query_not_attack_me(this_object()))
     return 1;

   /* miss */
   if(query_combat_object()->cb_tohit(A_HORN, 55, enemy) <= 0)
   {
     enemy->catch_msg(QCTNAME(TO) + " tries to charge at you with "
        + "its sharp horn, but you dodge aside.\n");
     tell_watcher(QCTNAME(TO) + " tries to charge at " + QTNAME(enemy)
        + " with its sharp horn, but " + enemy->query_pronoun()
        + " dodges aside.\n", enemy);
     return 1;
   }

   hitres = enemy->hit_me(60, W_IMPALE, TO, A_HORN);

   hitloc = translate_hitloc(enemy, (string)hitres[1]);

   switch(hitres[2])
   {
     case -100 .. 0:
        enemy->catch_msg(QCTNAME(TO) + " tries to charge at you with "
           + POSSESS(TO) + " sharp horn, but you dodge aside.\n");
        tell_watcher(QCTNAME(TO) + " tries to charge at " + QTNAME(enemy)
           + " with " + POSSESS(TO) + " sharp horn, but " + enemy->query_pronoun()
           + " dodges aside.\n", enemy);
        break;
     case 1 .. 5:
        str = "grazes";
        break;
     case 6 .. 12:
        str = "bruises";
        break;
     case 13 .. 20:
        str = "hurts";
        break;
     case 21 .. 30:
        str = "stabs into";
        break;
     case 31 .. 50:
        str = "impales";
        break;
     default:
        str = "gores";
        break;
   }

   enemy->catch_msg(QCTNAME(TO) + " charges at you with " + POSSESS(TO) 
     + " long black horn and "
     + str + " your " + hitloc + "!\n");
   tell_watcher(QCTNAME(TO) + " charges at " + QTNAME(enemy)
     + " with " + POSSESS(TO) + " long black horn and "
     + str + " " + POSSESS(enemy) + " " + hitloc + ".\n", enemy);

   switch(hitres[0])
   {
     case 0 .. 10: str = "unaffected"; break;
     case 11 .. 20: str = "stunned"; break;
     case 21 .. 40: str = "dizzy"; break;
     case 41 .. 60: str = "very dizzy"; break;
     case 61 .. 80: str = "extremely stunned"; break;
     default: str = "like you can barely stand"; break;
   }

   enemy->catch_msg("You feel " + str + ".\n");
   enemy->add_attack_delay(hitres[0] / 10);

   if(!enemy->query_hp())
     enemy->do_die(TO);

   return 1;
}



