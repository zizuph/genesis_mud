#include "defs.h"

inherit STRHOLD_STD+"std_npc";

#include <stdproperties.h>
#include <ss_types.h>

#define ADMIRAL_LOG STRHOLD_LOG+"admiral"

void arm_npc()
{
 command("wear all");
 command("wield all");
 command("rub handle");
}

void create_stronghold_karg()
{
 string adj1,adj2;

 set_auto_reteam(1);
 set_alignment(-1200);
 set_hide_hp(100000); //Makes him hide right away
 set_level(3);

 set_name("admiral");
 add_name("guard");
 set_adj("stern");
 add_adj("karg");
 set_short("stern karg admiral");
 set_long("This is Admiral of Karg War Fleet. This one of the most "+
   "important officers of whole Karg Empire. He is old , but though "+
   "tough, and you guess he's in top shape and can make an excellent "+
   "opponent. He is battle-scarred , polished medals shine on his "+
   "admiral uniform.\n");

 set_stats(({200,207,200,160,160,140}));

 set_skill(SS_WEP_CLUB,100);
 set_skill(SS_WEP_AXE,100);
 set_skill(SS_SPELLCRAFT,100);
 set_skill(SS_2H_COMBAT,100);
 set_skill(SS_DEFENCE,100);
 set_skill(SS_PARRY,100);
 set_skill(SS_AWARENESS,100);
 set_skill(SS_BLIND_COMBAT,100);

 clone_object(STRHOLD_WEP+"a_axe")->move(TO);
 clone_object(STRHOLD_WEP+"sceptre")->move(TO);

 clone_object(STRHOLD_ARM+"a_plate")->move(TO);
 clone_object(STRHOLD_ARM+"a_helm")->move(TO);
 clone_object(STRHOLD_ARM+"a_cape")->move(TO);

 set_alarm(0.5,0.0,&arm_npc());
}

void do_die(object killer)
{
 string log_str,*nm;
 object *team;
 int i;

 command("ungrip sceptre");
 command("unwield all");
 command("scream");
 command("drop weapons");

 nm=({ killer->query_real_name() });

 if(killer->query_leader()) 
  {
   team=killer->query_leader()->query_team();
   team-=({killer});
   team+=({killer->query_leader()});
  }
 else if(sizeof(killer->query_team())) team=killer->query_team();
 else team=({});

 log_str="Killed by "+killer->query_name();
 if(!sizeof(team)) log_str+=" with no assistance ";
 else
  {
   nm=({});
   for(i=0;i<sizeof(team);i++)
     nm+=({ team[i]->query_name() });
   log_str+=" with assistance of "+implode(nm,",")+" on ";
  }
 log_str+=ctime(time())+"\n";

 write_file(ADMIRAL_LOG,log_str);

 ::do_die(killer);
}

