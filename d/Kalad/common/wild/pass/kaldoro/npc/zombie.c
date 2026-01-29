/* 
 * /d/Kalad/common/wild/pass/kaldoro/npc/zombie.c
 * Purpose    : A random descrip zombie.
 * Located    : ../rooms/<undetermined>
 * Created By : Sarr 
 * Modified By: Rico 10.Jan.97 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";

#include "/d/Kalad/defs.h"

string
adj_ran()
{
    int i;
    i = random(4);
    switch (i)
    {
    case 0:
        return "revolting";
        break;
    case 1:
        return "loathsome";
        break;
    case 2:
        return "horrible";
        break;
    default:
        return "foul";
        break;
    }
}

void
create_monster() 
{
   string ran;
   ::create_monster();
   ran = adj_ran();
   set_name("zombie");
   set_race_name("zombie");
   set_adj("large");
   add_adj(ran);
   set_short("large "+ran+" zombie");
   set_long("@@my_long@@");
   set_gender(G_NEUTER);
   set_stats(({85,50,80,1,1,100}));
   set_skill(SS_DEFENCE,70);
   set_skill(SS_UNARM_COMBAT,90);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(LIVE_I_SEE_DARK, 1);
   add_prop(OBJ_I_WEIGHT, 6500);
   add_prop(OBJ_I_VOLUME, 3500);
   add_prop(LIVE_I_UNDEAD,20);
   set_alignment(-325);
   set_knight_prestige(325);
   set_random_move(5);
   set_act_time(3);
   add_act("moan");
   add_act("emote wants to rip open your head and eat your brains.");
   set_cact_time(3);
   add_cact("emote wants to rip out your eyeballs, squish them in its "+
   "hands and drink down the bloody ooze.");
   add_cact("say I will eat your corpse when you die...");
   add_cact("say I cann smellll yourrr braaaiiinnnss...!!");
   add_cact("emote licks its chops thinking of eating your heart.");
   set_attack_unarmed(0, 40, 40, W_IMPALE, 10, "savage bite");
   set_attack_unarmed(1, 30, 35, W_SLASH, 45, "left claw");
   set_attack_unarmed(2, 30, 35, W_SLASH, 45, "right claw");
   set_hitloc_unarmed(0,20,15,"head");
   set_hitloc_unarmed(1,20,10,"left arm");
   set_hitloc_unarmed(2,20,10,"right arm");
   set_hitloc_unarmed(3,30,45,"body");
   set_hitloc_unarmed(4,20,20,"legs");
}

string
query_combat_file()
{ return "/d/Kalad/sarr/std/combat/chumanoid.c"; }

string 
*run_armour()
{
    int i;
    i = random(2);
    if(i)
    {
         switch(random(7))
         {
         case 0:
         return 
         ({RAUM(arm/rdplatemail),RAUM(arm/rfgreavs),RAUM(arm/rdcloak)});
         break;
         case 1:
         return
         ({RAUM(arm/rtchainmail),RAUM(arm/rbelt),RAUM(arm/rdcloak)});
         break;
         case 2:
         return
         ({RAUM(arm/rshelm),RAUM(arm/rbelt),RAUM(arm/rdcloak)});
         break;
         case 3:
         return
         ({RAUM(arm/rcbracers),RAUM(arm/rshelm),RAUM(arm/rdcloak)});
         break;
         case 4:
         return
         ({RAUM(arm/rfgreavs),RAUM(arm/rshelm),RAUM(arm/rdcloak)});
         break;
         case 5:
         return
         ({RAUM(arm/rcbracers),RAUM(arm/rbelt),RAUM(arm/rdcloak)});
         break;
         case 6:
         return
         ({RAUM(arm/kwboots),RAUM(arm/rbelt),RAUM(arm/rdcloak)});
         break;
         }
    }
    else
    {
         switch(random(7))
         {
             case 0:
             return
         ({RAUM(arm/kdgreavs),RAUM(arm/kbplatemail),RAUM(arm/ktcloak)});
             break;
             case 1:
             return
         ({RAUM(arm/ktgloves),RAUM(arm/kbchainmail),RAUM(arm/ktcloak)});
             break;
             case 2:
             return
         ({RAUM(arm/ktgloves),RAUM(arm/kdhelm),RAUM(arm/ktcloak)});
             break;
             case 3:
             return
         ({RAUM(arm/kbbracers),RAUM(arm/kdhelm),RAUM(arm/ktcloak)});
             break;
             case 4:
             return
         ({RAUM(arm/kdgreavs),RAUM(arm/kdhelm),RAUM(arm/ktcloak)});
             break;
             case 5:
             return
         ({RAUM(arm/kbbracers),RAUM(arm/ktgloves),RAUM(arm/ktcloak)});
             break;
             case 6:
             return
         ({RAUM(arm/ktgloves),RAUM(arm/kwboots),RAUM(arm/ktcloak)});
             break;        
         }
    }
}

void
init_living()
{
    ::init_living();
    if(interactive(TP))
        set_alarm(1.5,0.0,"my_attack", TP);
}

void
my_attack(object ob)
{
   if(ob->query_prop(LIVE_I_UNDEAD))
       return;
   else
   {
       if(ob->query_prop(OBJ_I_HIDE))
           ob->add_prop(OBJ_I_HIDE,0);
       command("kill "+lower_case(ob->query_name()));
   }
}



void
arm_me()
{
    string *sarm;
    object arm;
    sarm = run_armour();
    seteuid(getuid(TO));
    arm = clone_object(sarm[0]);
    arm->move(TO,1);
    arm = clone_object(sarm[1]);
    arm->move(TO,1);
    arm = clone_object(sarm[2]);
    arm->move(TO,1);
    command("wear all");
}

void
notify_you_killed_me(object who)
{
    command("emote hisses in satisfaction as its victim falls.");
    command("emote moans: Your corpsssee isss mineee!");
    who->add_prop(LIVE_I_NO_CORPSE,1);
    command("emote devours the corpse of "+who->query_name()+".");
}

void
do_die(object killer)
{
    command("emote falls to the ground, spewing black ooze out of its mouth.");
    command("emote moans: Yourrr tiiime will commme soooon, mortaaal.....");
    ::do_die(killer);
}

string
my_long()
{
   return
   "This foul creatures looks fresh out of the grave. His glowing eyes, "+
   "savage claws, and decaying flesh make you want to turn and run far "+
   "far away. "+
   "This one looks larger and meaner than the rest of the zombies.\n";
}

int
special_attack(object enemy)
{
    object me;
    mixed *hitresult;
    string how;
    string ohow;
    string tar;
    me = TO;
    if(random(10))
        return 0;
    hitresult = enemy->hit_me(100 + random(150), W_SLASH, me , -1);
    how = " but miss";
    ohow = " but misses";
    if(hitresult[0] >= 0)
    {
        how = " and slashes across ";
        ohow = " and slashes across ";
        tar = " chest";
    }
    if(hitresult[0] > 10)
    {
        how = " and rip across ";
        ohow = " and rips across ";
        tar = " chest";   
    }
    if(hitresult[0] > 20)
    {
        how = " and brutaly slashes across ";
        ohow = " and brutaly slashes across ";
        tar = " chest, spraying blood everywhere";
    }         
    if(hitresult[0] == -1)
    {
    me->catch_msg("You strike out at " + QCTNAME(enemy) + " with your claws,"+
    how + ".\n");
    enemy->catch_msg(QCTNAME(me) + " strikes out at you with its clawed foot,"+
    ohow + ".\n");
    tell_watcher(QCTNAME(me) + " strikes out at "+ QCTNAME(enemy) + 
    " with its clawed foot,"+ ohow + ".\n", enemy);
    return 1;
    }
    if(hitresult[0] >= 0)
    {
    me->catch_msg("You strike out at " + QCTNAME(enemy) + " with your claws,"+
    how + enemy->query_possessive() + tar +".\n");
    enemy->catch_msg(QCTNAME(me)+ " strikes out at you with its clawed foot,"+
    ohow + "your" + tar + ".\n");
    tell_watcher(QCTNAME(me)+ " strikes out at "+ QCTNAME(enemy) + " with "+
    "its clawed foot,"+ 
    ohow + enemy->query_possessive() + tar + ".\n", enemy); 
    if(enemy->query_hp() <= 0);
        enemy->do_die(me);
    return 1;
    }
}
