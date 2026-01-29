/*
 * Standard Karg class for kargs on Karg island
 * by Ged 8/10/2001
*/

inherit "/std/monster";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

#include "defs.h"

int helps=0;
int auto_reteam=0;
int hide_hp=500;

void create_karg()
{
}

void create_monster()
{
 create_karg();
 set_name("karg");
 add_prop(LIVE_I_NEVERKNOWN,1);
}

void notify_team_attacked(object ob)
{
 if(member_array(ob,query_enemy(-1))!=-1) return;
 
 command("shout For the Glory of Karg Empire!");
 command("assist");
}

void leader_notify_attack(object ob)
{
 int i;
 object *team;

 team=query_team();
 for(i=0;i<sizeof(team);i++) team[i]->notify_team_attacked(ob);
 notify_team_attacked(ob);
}

public void attacked_by(object ob)
{
 int i;
 object leader;

 ::attacked_by(ob);

 leader=query_leader();
 if(!leader) leader_notify_attack(ob);
 else leader->leader_notify_attack(ob);

}

object *get_all_team()
{
 object *tm;

 if(query_leader()) 
  {
   tm=query_leader()->query_team();
   tm+=({query_leader()});
  }
 else tm=query_team();

 return tm-({TO});
}

int can_help()
{
 return (query_hp()>hide_hp ? 1 : 0);
}

varargs mixed
hit_me(int wcpen, int dt, object enemy, int
       attack_id, int target_hitloc)
{
  mixed output;
  object* help,helper;
  int max_ind,max_hp,i;

  output = ::hit_me(wcpen, dt, enemy, attack_id, target_hitloc);
  if(!helps) return output;

  if (this_object()->query_hp() < hide_hp)
   {
    help=get_all_team();
    max_hp=0;max_ind=-1;
    for(i=0;i<sizeof(help);i++)
     {
      if(help[i]->query_hp()>max_hp && ENV(help[i])==ENV(TO) && 
      help[i]->can_help())
       {max_hp=help[i]->query_hp(); max_ind=i;};
     }
    if(max_ind==-1) return output;

    helper=help[max_ind];

    if(DIS(helper)+DEX(helper)+random(WIS(helper)/2)>
       DIS(enemy)+DEX(enemy))
     {
      enemy->catch_msg("\n"+QCTNAME(helper)+" steps in between you "+
        "and "+QTNAME(TO)+", drawing your attention at "+
        OBJ(helper)+".\n\n");
      tell_room(ENV(TO),"\n"+QCTNAME(helper)+" steps in between "+
        QTNAME(enemy)+" and "+QTNAME(TO)+" drawing "+POS(enemy)+
        " attention at "+OBJ(helper)+".\n\n",enemy);
      enemy->attack_object(helper);
     }
    else
     {
      enemy->catch_msg("\n"+QCTNAME(helper)+" tries to step between "+
        "you and "+QTNAME(TO)+", but you notice "+POS(helper)+
        " maneuver and make a falce attack towards "+OBJ(helper)+
        " to prevent it.\n\n");
      tell_room(ENV(TO),"\n"+QCTNAME(helper)+" tries to step between "+
        QTNAME(enemy)+" and "+QTNAME(TO)+", but "+POS(helper)+
        " maneuver was too obvious for "+QTNAME(enemy)+", who "+
        "prevents it easily.\n\n",enemy);
     }
   }

  return output;
}

void set_help(int h) {helps=h;}

void set_auto_reteam(int a) {auto_reteam=a;}

public void do_die(object killer)
{
 object *team;
 int i;

 team=query_team();
 if(auto_reteam && team)
  {
   for(i=0;i<sizeof(team);i++)
     team_leave(team[i]);
   for(i=1;i<sizeof(team);i++)
     team[0]->team_join(team[i]);
  }

 ::do_die(killer);
}

void set_hide_hp(int hp) {hide_hp=hp;}

int query_hide_hp() {return hide_hp;}

