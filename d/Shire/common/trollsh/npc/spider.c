/*
* Big spider.
*/

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";

#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/poison_types.h"

/* Invent some attack/hitlocation numbers, for ourselves */
#define ATT_BITE    0

#define HIT_BODY     0

create_creature()
{
   if (!IS_CLONE)
      return;
   set_name("vicious");
   set_race_name("spider");
   set_gender(G_FEMALE);
   set_long("The spider looks quite mean and is bigger than your hand.\n");
   
   set_stats(({ 20, 34, 20, 15, 15, 35 }));
   set_hp(300);
   set_skill(SS_DEFENCE, 45);
   set_attack_chance(100);                 /* should start to fight */
   set_aggressive(1);                      /* right away...         */
   set_alignment(-200);
   
   set_attack_unarmed(ATT_BITE, 29, 17,W_IMPALE, 100, "bite");
   
   set_hitloc_unarmed(HIT_BODY, 30, 100, "body");
   
   add_prop(CONT_I_WEIGHT, 500);   /* 0.5 Kg  */
   add_prop(CONT_I_VOLUME, 400);   /* 0.4 Ltr */
}

/*
* Function name: cr_did_hit
* Description:   This function is called from the combat object to give
*                appropriate messages.  We shall remain content to let 
*                the default messages be sent, but we will give poison 
*                to the hit creature.
* Arguments:     aid:   The attack id
*                hdesc: The hitlocation description.
*                phurt: The %hurt made on the enemy
*                enemy: The enemy who got hit
*                dt:    The current damagetype
*                phit:  The %success that we made with our weapon
*                       If this is negative, it indicates fail
*/

int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   object poison;
   
   /* I believe the spider poisons the player each bite. it should of course
   * be harder to poison the player again and again, Nick */
   
   if(aid == ATT_BITE && phurt > 0) {
      tell_object(enemy, "The spider's fangs bite deep!\n");
      
      poison = clone_object("/std/poison_effect");
      if(poison) {
         poison->move(enemy);
         poison->set_poison_type("spider");
         poison->set_time(200);
         poison->set_interval(50);
         poison->set_strength(50);
         poison->set_damage(({POISON_FATIGUE, 30, POISON_STAT, SS_STR }));
         poison->start_poison();
         
      }
   }
   
   return 0;
}

