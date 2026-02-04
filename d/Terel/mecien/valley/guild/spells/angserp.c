/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
*  A mystic serpent. Mortricia 930310
*/

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)   break_string(message, 72)
#define TO            this_object()
#define TP            this_player()
#define ETP           environment(TP)
#define ETO           environment(TO)
#define EVIL_LIMIT    1

#define A_BITE  0

#define H_BODY  0
#define H_HEAD  1


init_living()
{
   ::init_living();
   set_alarm(2.0, -1.0, "search_evil");
}

public void
search_evil()
{
   object *ob;
   int i;

   ob = all_inventory(ETO) - ({ TO });
   for (i=0; i<sizeof(ob); i++) {
      if (living(ob[i]) && (ob[i]->query_alignment() < EVIL_LIMIT || 
                            ob[i]->query_prop(LIVE_I_UNDEAD))) {
         tell_room(ETO, QCTNAME(TO) + " hisses at " + QTNAME(ob[i]) +
                        ".\n", ob[i]);
         ob[i]->catch_msg(QCTNAME(TO) + " strikes out at you!\n");
         tell_room(ETO, QCTNAME(TO) + " strikes out at " +
                        QTNAME(ob[i]) + "!\n", ob[i]);
         TO->attack_object(ob[i]);
      }
   }
}

public void
create_creature()
{
   set_name("serpent");
   set_long(BS(
         "A ghostly serpentine creature, shining with an emerald hue, " +
         "its long body writhes about wildly. Its eyes glimmer like jewels, fangs "
         + "protruding, ready to strike. Arcane and mysterious, its form, " +
         "is overshadowed by a darkness, telling of its abyssmal origins.\n"
   ));
   set_adj(({"ghostly", "emerald"}));
   set_race_name("serpent");
   
   set_stats( ({100,145,125,30,30,45}) );
   set_learn_pref( ({10,10,10,10,10,10}) );
   set_hp(9999);
   set_alignment(250);
   set_mana(9999);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(CONT_I_WEIGHT, 200000);
   add_prop(CONT_I_VOLUME,  200000);
   add_prop(CONT_I_MAX_WEIGHT, 280000);
   add_prop(CONT_I_MAX_VOLUME, 280000);
   add_prop(LIVE_I_QUICKNESS, 80);
   set_skill(SS_DEFENCE,      90);
   set_skill(SS_PARRY,        55);
   set_skill(SS_AWARENESS,    90);
   set_skill(SS_CLIMB,        70);
   set_skill(SS_LOC_SENSE,    50);
   set_skill(SS_HUNTING,      60);
   
   set_act_time(5);
   add_act("emote coils its body upwards.");
   add_act("emote writhes about wildly.");
   add_act("emote hisses.");
   add_item(({"fangs"}),  "They are long and filled with venom.\n");
   add_item(({"scales"}), "They shine like brilliant jewels.\n");
   add_item(({"eyes"}),   "They possess an unworldy power.\n");
}

public void
cr_configure()
{
   add_attack(70, 60, W_IMPALE, 100, A_BITE);
   
   add_hitloc( ({ 50, 50, 50 }), 25, "body",  H_BODY);
   add_hitloc( ({ 70, 70, 70 }), 75, "head",  H_HEAD);
}

public string
cr_attack_desc(int aid)
{
   switch (aid) {
      case A_BITE:return "deadly fangs";
   }
}

public void
set_duration(int dur)
{
    set_alarm(itof(dur), -1.0, "fade");
}

fade()
{
   tell_room(ETO, QCTNAME(TO) + " fades away with a eerie green glow.\n");
   remove_object();
}


special_attack(object enemy)
{  
   object me;
   mixed *hitresult;
   string how;
   
   me = this_object();
   if(random(5)) return 0;
   
   hitresult = enemy->hit_me(40+random(60), W_BLUDGEON, me, -1);
   how = " fails to grasp";
   if(hitresult[0] > 0)
      how = " grasps";
   if(hitresult[0] > 25)
      how = " grips";
   if(hitresult[0] > 40)
      how = " crushes";
   
   me->catch_msg("You encircle your victim with your coils.\n");
   enemy->catch_msg(QCTNAME(me) + how + " you in " +
      me->query_possessive() + " serpentine coils.\n");
   tell_watcher(QCTNAME(me) + how + " " +QTNAME(enemy) +
      " in " + me->query_possessive() +  " serpentine coils.\n", enemy);
   
   if (enemy->query_hp() <= 0)
       enemy->do_die(me);

   return 1;
}
