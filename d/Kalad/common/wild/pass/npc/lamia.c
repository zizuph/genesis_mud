/* 
 * /d/Kalad/common/wild/pass/npc/lamia.c
 * Purpose    : A lamia creature
 * Located    : /d/Kalad/common/wild/pass/desert/rock/l*
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#define A_FORE 0
#define A_REAR 1
#define H_HEAD 0
#define H_LARM 1
#define H_RARM 2
#define H_TORSO 3
#define H_BODY 4
#define H_FLEGS 5
#define H_RLEGS 6
#define H_TAIL 7
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("lamia");
   set_race_name("lamia");
   set_adj("feline");
   set_long("A strange creature whose body from waist and up is that of "+
      "the most beautiful human woman you've ever laid eyes upon, while its "+
      "lower body is that of a powerful lioness with sleek golden fur.\n");
   set_gender(G_FEMALE);
   set_alignment(-500);
   set_knight_prestige(750);
   set_aggressive(1);
   set_stats(({100,100,100,100,100,100}));
   set_skill(SS_UNARM_COMBAT,75);
   set_skill(SS_BLIND_COMBAT,75);
   set_skill(SS_DEFENCE,75);
   set_skill(SS_AWARENESS,75);
   add_prop(LIVE_I_SEE_DARK,1);
   set_act_time(3);
   add_act("growl");
   add_act("say Intruder!");
   add_act("grin mer");
   set_cact_time(3);
   add_cact("snarl all");
   add_cact("growl all");
   add_cact("say Die pitiful biped!");
   set_attack_unarmed(A_FORE, 35, 35, W_IMPALE, 70, "front paws");
   set_attack_unarmed(A_REAR, 35, 35, W_IMPALE, 30, "rear paws");
   set_hitloc_unarmed(H_HEAD, ({ 15, 15, 15 }), 10, "beautiful blonde head");
   set_hitloc_unarmed(H_LARM, ({ 20, 20, 20 }), 5, "slender left arm");
   set_hitloc_unarmed(H_RARM, ({ 20, 20, 20 }), 5, "slender right arm");
   set_hitloc_unarmed(H_TORSO, ({ 25, 25, 25 }), 15, "voluptuous torso");
   set_hitloc_unarmed(H_BODY, ({ 30, 30, 30 }), 30, "feline body");
   set_hitloc_unarmed(H_FLEGS, ({ 25, 25, 25 }), 15, "front legs");
   set_hitloc_unarmed(H_RLEGS, ({ 25, 25, 25 }), 15, "rear legs");
   set_hitloc_unarmed(H_TAIL, ({ 10, 10, 10 }), 5, "long tail");
   MONEY_MAKE_GC(random(10))->move(TO,1);
}
int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   if(aid == A_FORE)
      {
      tell_object(enemy,"The feline lamia rakes you with its sharp claws!\n");
      tell_object(enemy,"You feel your mind slipping from your control.\n");
      {
         enemy -> add_mana(-50);
         if(enemy->query_mana() <= 0)
            {
            enemy->command("$shout Death to the enemies of the Lamia!");
            enemy->command("$kill human");
            enemy -> command("$kill elf");
            enemy -> command("$kill dwarf");
            enemy -> command("$kill gnome");
            enemy -> command("$kill hobbit");
            enemy -> command("$kill goblin");
         }
      }
   }
   return 0;
}
