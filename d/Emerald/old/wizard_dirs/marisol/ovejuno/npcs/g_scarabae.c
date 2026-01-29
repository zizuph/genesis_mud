/*Scarabae Bug for Castle's Garden
* Coded by Mccram and modified by 
* Marisol (9/12/97)
*/



#pragma save_binary

inherit "/d/Earthsea/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
#include "/d/Earthsea/sys/macros.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>      



create_earthsea_creature()
{
    int i;

    set_name("scarabae");
    set_adj("huge");
    set_race_name("scarabae");
    add_name("g_scarabae");
    set_gender(2); /*male=0, female=1, other =2 */
    set_long("This is one of the hugest bugs that you have "+
       "ever seen in your life.\n");

    set_act_time(10);
    add_act("emote scratchs the ground looking for food"); 
    add_act(({"emote finds a tasty morsel.", "emote chews noisily."}));
    

    set_appearance(50);

    set_stats(({5,5,5,8,8,9}));

    set_alignment(-10);


   set_skill(SS_DEFENCE,10);
   set_skill(SS_UNARM_COMBAT,5);


   set_attack_unarmed(0,5,5,W_SLASH,5,"left leg");
   set_attack_unarmed(1,5,5,W_SLASH,5,"right leg");
   set_attack_unarmed(2,5,5,W_SLASH,5,"jaws");     

   set_hitloc_unarmed(A_HEAD,5,20,"head");
   set_hitloc_unarmed(A_BODY,8,80,"thorax");
   set_hitloc_unarmed(A_R_ARM,9,10,"front leg");
   set_hitloc_unarmed(A_L_ARM,9,10,"middle leg");
   set_hitloc_unarmed(A_R_ARM,9,10,"hind leg");
  
   add_prop(LIVE_I_NO_CORPSE,1);
   add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
   


}                                                             

int
special_attack(object enemy)

{

    int temp;
    temp = random(15);

    switch (temp)
        {
          case 0:
                 enemy->heal_hp(-10); 
                 enemy->add_fatigue(-1);

                 command("emote spits out a sprinkle of acid.");          
                 enemy->catch_msg("You are burnt at little.\n");   

                 if (enemy->query_hp() <= 0)
                 enemy->do_die(TO);
                 return 1;               
                 break;
               
          case 2:
                 enemy->heal_hp(-30);             
                 enemy->add_fatigue(-1);

                 command("emote spits out a scorching spray of acid.");
                 enemy->catch_msg("You are burnt and it really "+
                 "hurts.\n");

                 if (enemy->query_hp() <= 0)
                 enemy->do_die(TO);
                 return 1;
                 break;

                 default:
                 break;
        }

        return 0;
                                             
}

