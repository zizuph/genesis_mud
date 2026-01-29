// file name:    Spider
// creator(s):   Cirion, April 1996
// last update:
// purpose:      Newbie Monster
// note:         Uses a small poison, mostly just to give
//               newbies some experience with these things :)
// bug(s):
// to-do: 
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include "../outpath.h"
#include <poison_types.h>

#define A_TEETH      0
#define A_LEG        1

#define H_HEAD       0
#define H_THORAX     1
#define H_LEGS       2
#define H_ABDOMEN    3

void create_creature()
{
    string *adjs = ({ "huge", "fat", "black", "nasty", "ugly", "horrid" });

    set_name("spider");
    add_name("insect");
    set_race_name("spider");

    set_adj( adjs[random(sizeof(adjs))] );
    set_gender(G_NEUTER);

    set_long("It is a huge, fat spider with long jointed "
        +"legs and a set of nasty looking jaws. Along "
        +"its abdomen is a blood-red mark.\n");

    set_stats(({ 8, 10, 15, 1, 1, 20 }));

    set_skill(SS_UNARM_COMBAT,  10);
    set_skill(SS_DEFENCE,        5);
    set_skill(SS_AWARENESS,     50);

    set_alignment(0);

    set_attack_unarmed(A_TEETH, 8, 8, W_IMPALE, 40, "jaws");
    set_attack_unarmed(A_LEG, 2, 2, W_BLUDGEON, 60, "tiny legs");

    set_hitloc_unarmed(H_HEAD,   ({ 10, 10, 2 }), 5, "head");
    set_hitloc_unarmed(H_THORAX, ({ 2, 2, 8 }),   50, "thorax");
    set_hitloc_unarmed(H_LEGS,   ({ 5, 5, 5 }),   15, "legs");
    set_hitloc_unarmed(H_ABDOMEN,({ 10, 10, 10 }), 30, "tail");

    add_prop(CONT_I_WEIGHT, 5);
    add_prop(CONT_I_VOLUME, 25);
    add_prop(CONT_I_HEIGHT, 5);

    add_prop(LIVE_I_SEE_DARK,    2);
    add_prop(LIVE_I_NEVERKNOWN,  1);
    add_prop(NPC_I_NO_LOOKS,     1);

    add_leftover("/std/leftover", "leg", 8, 0, 1, 0);

    set_act_time(10);
     add_act("emote seems to watch you.");
     add_act("emote touches the web, making it vibrate "
            +"slightly.");
}

int special_attack(object enemy)
{
  object    poison;

  if(random(20))
   return 0;

  enemy->catch_msg(QCTNAME(TO)+" bites you with its teeth.\n");
  say(QCTNAME(TO)+" bites "+QTNAME(enemy)+" with its teeth.\n",
         ({ TO, enemy }) );

  seteuid(getuid());
  poison = clone_object("/std/poison_effect");
   poison->set_poison_type("spider");
   poison->set_time(200);
   poison->set_strength(3);
   poison->set_damage( ({ POISON_FATIGUE, 50, POISON_MANA, 8 }) );
   poison->move(enemy, 1);
   poison->start_poison();

  return 1;
}
