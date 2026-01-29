/* 
 * /d/Kalad/common/wild/pass/npc/lamia_queen.c
 * Purpose    : A lamia queen
 * Located    : /d/Kalad/common/wild/pass/desert/rock/l6
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#define A_RIGHT 0
#define A_LEFT 1
#define H_HEAD 0
#define H_LARM 1
#define H_RARM 2
#define H_TORSO 3
#define H_BODY 4
#define H_TAIL 5
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("aldirlana");
   add_name("queen");
   set_race_name("lamia");
   set_adj("noble");
   set_long("A strange creature whose body from waist and up is that of "+
      "the most beautiful and alluring woman you've ever had the privilege "+
      "of seeing, while her lower body is that of a giant scaled serpent.\n");
   set_gender(G_FEMALE);
   set_alignment(-600);
   set_knight_prestige(900);
   set_aggressive(1);
   set_stats(({125,125,125,125,125,125}));
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_AWARENESS,100);
   add_prop(LIVE_I_SEE_DARK,1);
   add_leftover(CPASS(obj/bed_heart),"heart",1,"",1,1);
   set_act_time(3);
   add_act("growl");
   add_act("say Ahh, more toys to play with!");
   add_act("grin mer");
   set_cact_time(3);
   add_cact("snarl all");
   add_cact("growl all");
   add_cact("say Die pitiful biped!");
   set_attack_unarmed(A_RIGHT, 40, 40, W_IMPALE, 40, "right clawed hand");
   set_attack_unarmed(A_LEFT, 40, 40, W_IMPALE, 60, "left clawed hand");
   set_hitloc_unarmed(H_HEAD, ({ 20, 20, 20 }), 10, "gorgeous blonde head");
   set_hitloc_unarmed(H_LARM, ({ 25, 25, 25 }), 5, "slender left arm");
   set_hitloc_unarmed(H_RARM, ({ 25, 25, 25 }), 5, "slender right arm");
   set_hitloc_unarmed(H_TORSO, ({ 30, 30, 30 }), 15, "beautifully voluptuous torso");
   set_hitloc_unarmed(H_BODY, ({ 35, 35, 35 }), 30, "serpent-like body");
   set_hitloc_unarmed(H_TAIL, ({ 35, 35, 35 }), 35, "long scaled tail");
   set_title("the Lamia Queen");
   MONEY_MAKE_GC(random(20))->move(TO,1);
}
int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   if(aid == A_RIGHT)
      {
      tell_object(enemy,"The noble lamia tears into your flesh with its "+
         "needle-sharp claws!!\n");
      tell_object(enemy,"You feel your mind slipping from your control.\n");
      {
         enemy -> add_mana(-100);
         if(enemy->query_mana() <= 0)
            {
            enemy -> command("$shout Death to the enemies of the Lamia!");
            enemy -> command("$kill human");
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
