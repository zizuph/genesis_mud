/* 
 * /d/Kalad/common/wild/pass/npc/bed_camel.c
 * Purpose    : A camel in the desert of Kalad
 * Located    : /d/Kalad/common/wild/pass/dsesert/
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#define A_BITE 0
#define A_LHOOF 1
#define A_RHOOF 2
#define H_HEAD 0
#define H_BODY 1
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("camel");
   set_race_name("camel");
   set_adj("two-humped");
   add_adj("desert");
   set_long("A large camel with two great humps on its back. Because it "+
      "is so superbly adapted to life in the waste, it can go for days "+
      "on end with but one full drink of water. This quality helps make it "+
      "the mount of choice here in the desert. By the mark of the red sun "+
      "on its flank, you can tell it belongs to the Iriphawa tribe.\n");
   set_stats(({55,65,75,30,30,55}));
   set_skill(SS_DEFENCE,30);
   set_gender(G_NEUTER);
   set_act_time(9);
   add_act("spit all");
   add_act("eat all");
   add_act("emote starts making a terrible noise.");
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(OBJ_I_WEIGHT,75000);
   add_prop(OBJ_I_VOLUME,75000);
   add_prop(OBJ_I_NO_INS,1);
   add_prop(NPC_M_NO_ACCEPT_GIVE,0);
   set_attack_unarmed(A_BITE, 20, 20, W_BLUDGEON, 40, "teeth");
   set_attack_unarmed(A_LHOOF, 30, 20, W_BLUDGEON, 30, "left hoof");
   set_attack_unarmed(A_RHOOF, 30, 20, W_BLUDGEON, 30, "right hoof");
   set_hitloc_unarmed(H_HEAD, ({ 20, 15, 20 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 10, 15, 20 }), 80, "body");
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob, environment()))
      {
      command("emote snorts angrily!");
      command("kill " + (ob->query_real_name()));
   }
}
