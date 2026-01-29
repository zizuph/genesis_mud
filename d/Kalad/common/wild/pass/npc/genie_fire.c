/* 
 * /d/Kalad/common/wild/pass/npc/genie_fire.c
 * Purpose    : A powerful elemental, he is used for a quest
 * Located    : /d/Kalad/common/wild/pass/desert/mount/p2
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#define A_WOFIRE 0
#define A_LAVA 1
#define H_HEAD 0
#define H_BODY 1
#define H_LARM 2
#define H_RARM 3
#define H_LEGS 4
/* by Antharanos */
void
create_monster()
{
   int i;
   set_name("efreeti");
   add_name("genie");
   set_race_name("genie");
   set_adj("guardian");
   set_short("guardian genie of Fire");
   set_long("A massive, solid creature of humanoid shape, whose body "+
      "appears to be fashioned from solid flame, or perhaps basalt or "+
      "bronze. Its large, twelve foot frame is dominated by the savage "+
      "head atop its huge shoulders. A pair of red horns protrude from "+
      "the top of its skull, while pointed ears, a flat nose and a mouth "+
      "filled with razor-sharp teeth complete the rest of its countenance.\n");
   for(i = 0; i < 3; i++)
   set_base_stat(i, 200 + random(50));
   set_base_stat(3, 100);
   set_base_stat(4, 100);
   set_base_stat(5, 150);
   set_alignment(-600);
   set_knight_prestige(1000);
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_AWARENESS,100);
   set_act_time(6);
   add_act("emote stares at you with flaming, black eyes.");
   add_act("say No mortal can defeat a genie in combat.");
   add_act("say Only the possessor of the urn of Rata may pass me.");
   set_cact_time(6);
   add_cact("emote laughs cruelly.");
   add_cact("emote smirks in contempt.");
   add_cact("say Prepare to meet T'har, foolish mortal!");
   add_cact("snarl all");
   add_speak("Only the holder of the urn of Rata may pass. Any and all "+
      "other mortals foolish enough to fight me shall perish.\n");
   set_default_answer("The guardian genie of Fire answers your query "+
      "with silence.\n");
   set_attack_unarmed(A_WOFIRE, 55, 55, W_BLUDGEON, 50, "massive right fist");
   set_attack_unarmed(A_LAVA, 45, 45, W_BLUDGEON, 50, "massive left fist");
   set_hitloc_unarmed(H_HEAD, ({ 75, 75, 75 }), 15, "grotesque face");
   set_hitloc_unarmed(H_BODY, ({ 100, 100, 100 }), 45, "muscular body");
   set_hitloc_unarmed(H_LARM, ({ 75, 75, 75 }), 10, "massive left arm");
   set_hitloc_unarmed(H_RARM, ({ 75, 75, 75 }), 10, "massive right arm");
   set_hitloc_unarmed(H_LEGS, ({ 90, 90, 90 }), 20, "enormous legs");
   add_prop(LIVE_I_SEE_DARK,100);
   add_prop(LIVE_I_SEE_INVIS,100);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   add_prop(CONT_I_WEIGHT,1000000);
   add_prop(CONT_I_VOLUME,1000000);
   add_prop(OBJ_I_RES_MAGIC,100);
   trig_new("%w 'pours' 'out' 'some' 'of' 'the' 'water' 'from' 'the' 'urn.\n' %s","react_banish");
}
 
void
banished()
{
    TO->command("scream");
    TO->command("shout Nooooooooooooooo!!!");
    say(QCTNAME(TO) + " is banished back to the elemental " +
        "plane of Fire.\n");
    TO->move_living("into the gateway to the elemental " +
        "plane of Fire",
        "/d/Kalad/common/wild/pass/desert/mount/banished1");
    return;
}
 
 
int
react_banish(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(4.0,0.0,"return_banish",who);
      return 1;
   }
}
void
return_banish(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("banished intotheelementalplaneoffireforever");
   }
}
int
special_attack(object enemy)
{
   int attacktype, i, penet;
   mixed* hitresult;
   string how;
   object me, *ob;
   me = TO;
   attacktype = random(5);
   if(attacktype == 1)
      {
      ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
      for(i = 0; i < sizeof(ob); i++)
      {
         penet = 500 + random(1000);
         penet -= penet * ob[i]->query_mag_res(MAGIC_I_RES_FIRE) / 50;
         hitresult = ob[i]->hit_me(penet, MAGIC_DT, me, -1);
         how = "only barely singed";
         if(hitresult[0] > 0)
            how == "slightly singed";
         if(hitresult[0] > 5)
            how = "singed";
         if(hitresult[0] > 10)
            how = "singed quite badly";
         if(hitresult[0] > 15)
            how = "singed very badly";
         if(hitresult[0] > 20)
            how = "burned";
         if(hitresult[0] > 25)
            how = "burned badly";
         if(hitresult[0] > 30)
            how = "burned quite badly";
         if(hitresult[0] > 35)
            how = "burned very badly";
         if(hitresult[0] > 40)
            how = "burned and disfigured horribly";
         ob[i]->catch_msg("The area is suddenly blasted with heat so intense, "+
            "it appears as if the Kaladian sun itself has struck at you!\n");
         ob[i]->catch_msg("You were " + how + " by the heat!\n");
         tell_watcher(QCTNAME(ob[i]) + " is " + how + " by the blast of heat!\n", ob[i]);
         if(ob[i]->query_hp() <= 0)
            ob[i]->do_die(me);
      }
      return 1;
   }
}
int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   if(aid == A_WOFIRE)
      {
      tell_object(enemy,"A giant wall of fire suddenly bursts forth before "+
         "you!\n");
      tell_object(enemy,"It roars towards you with unbelievable speed and "+
         "scorches you terribly with its intense heat!!\n");
      {
         enemy -> heal_hp(-750);
      }
   }
   if(aid == A_LAVA)
      {
      tell_object(enemy,"A ball of flaming lava suddenly slams into you!\n");
      tell_object(enemy,"You are both bruised and seared by the terrible "+
         "attack!!\n");
      {
         enemy -> heal_hp(-500);
      }
   }
   return 0;
}
