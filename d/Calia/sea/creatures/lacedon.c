/*   lacedon.c
 *
 *  A marine form of the ghoul, can be found
 *  in the shipwreck.
 *
 * Baldacin@Genesis, Aug 2003
 */

inherit "/d/Calia/std/sea_creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/asking";
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <poison_types.h>
#include "defs.h"

#define A_CLAWS 0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1
#define H_ARMS 2
#define H_LEGS 3


#define SPEC_PEN 350 /* Pen for the special attack */

create_creature()
{
    set_name("shipwreck_lacedon");
    set_race_name("lacedon");
    set_adj(({"shadowy","rotting"}));
    set_short("shadowy rotting lacedon");
    
    set_long("This shadowy rotting creature must be a marine "+
      "form of the horrifying land-roaming ghoul. It seems to "+
      "be a strong opponent, you better stay away from it.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_UNDEAD, 45);
    set_alignment(-350);
    set_gender(G_NEUTER);

    set_stats(({105 + random(5),     
                105 + random(5),     
                105 + random(5),     
                 95 + random(5),     
                 95 + random(5),     
                100 + random(5)}));  

    set_skill(SS_UNARM_COMBAT, 85 + random(15));
    set_skill(SS_BLIND_COMBAT, 85 + random(15));
    set_skill(SS_DEFENCE,      90 + random(10));
    set_skill(SS_AWARENESS,    60);

    set_attack_unarmed(A_CLAWS, 35, 40, W_SLASH, 30, "claws");
    set_attack_unarmed(A_LCLAW, 25, 25, W_SLASH, 35, "left claw");
    set_attack_unarmed(A_RCLAW, 25, 25, W_SLASH, 35, "right claw");
    
    set_hitloc_unarmed(H_HEAD, ({2,2,2,2}), 20, "head");
    set_hitloc_unarmed(H_BODY, ({7,7,7,7}), 40, "body");
    set_hitloc_unarmed(H_ARMS, ({3,3,3,3}), 20, "arms");
    set_hitloc_unarmed(H_LEGS, ({4,4,4,4}), 20, "legs");
        
    add_act("emote scans the area cautiously.");
    add_act("emote grinds its teeth.");
    add_act("@@do_gnaw");
    add_act("emote hisses in anger.");
    
    set_default_answer(VBFC_ME("do_answer"));
    
    clone_object(WATER + "shipwreck/objects/wheel.c")->move(TO);
}

string
do_answer()
{
    command("glare "+TP->query_name());
    return "";
}

string
do_gnaw()
{
    if (present("shipwreck_wheel_", TO))
        return "emote gnaws on an old steering wheel.";
    return "emote gnaws on a fleshy bone.";
}

int
special_attack(object enemy)
{
   mixed* hitres;
   string how;
   object pois;

   if(random(4)) return 0;   

   hitres = enemy->hit_me(SPEC_PEN, W_SLASH, TO, -1);
   how = "completely misses";

   if (hitres[0] >  0) how = "barely hits";
   if (hitres[0] > 15) how = "lightly hit";
   if (hitres[0] > 30) how = "barely scratch";
   if (hitres[0] > 50) how = "wounds";
   if (hitres[0] > 75) how = "heavily wounds";

   enemy->catch_msg(QCTNAME(TO)+" tries to slash you with its "+
     "razor-sharp claws!\n");
   enemy->catch_msg(QCTPNAME(TO)+" attack "+how+" you.\n");
   
   enemy->tell_watcher(QCTNAME(TO) +" tries to slash "+QTNAME(enemy)+
     " with its razor-sharp claws!\n");
   enemy->tell_watcher(QCTPNAME(TO)+" attack "+how+" "+QTNAME(enemy)+".\n");

   if (hitres[0] > 70)
   {   
      pois = clone_object("/std/poison_effect");
      if(pois)
      {       
           pois->set_time(150);
           pois->set_interval(25);
           pois->set_strength(50);
           pois->set_damage(({POISON_HP, 70, POISON_FATIGUE, 70}));
           pois->move(enemy);
           pois->start_poison();
       }
   }
   if(enemy->query_hp() <= 0)
   enemy->do_die(TO);
   return 1;
}
