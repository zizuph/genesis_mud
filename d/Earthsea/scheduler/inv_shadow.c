inherit "/std/shadow";

#include "defs.h"

#define SW shadow_who

float interval=0.0; // Interval between movement
int leader=0;       // 
int pts=0;
int pos=-1;
object handler;

void set_interval(float intr) {interval=intr;}

float query_interval() {return interval;}

void is_leader() {leader=1;}

int am_i_leader() {return leader;}

void set_handler(object hn) {handler=hn;}

object query_handler() {return handler;}

void set_pts(int pt) {pts=pt;}

int query_pts() {return pts;}

void set_pos(int ps) {pos=ps;}

int query_pos() {return pos;}

int is_in_fight()
{
 int i;
 object *team;

 if(SW->query_attack()) return 1;

 for(i=0;i<sizeof(team);i++)
   if(team[i]->query_attack()) return 1;

 return 0;
}

void wonder() 
{
 if(is_in_fight()) return;
 SW->command(RND(ENV(SW)->query_exit_cmds()));
}

void go()
{
 if(interval!=0.0 && leader) set_alarm(interval,interval,&wonder());
}

void remove_sh() {remove_shadow();}

void disband()
{
 object *tm;
 int i;

 tm=SW->query_team_others();
 for(i=0;i<sizeof(tm);i++) SW->team_leave(tm[i]);
}

void make_team(object *mo)
{
 int i;

 is_leader();
 for(i=0;i<sizeof(mo);i++) SW->team_join(mo[i]);
 go();
}

void notify_team_attack()
{
 int i;
 object *team;

 team=SW->query_team_others();
 for(i=0;i<sizeof(team);i++) team[i]->command("assist");
}

void do_die(object killer)
{
 object *tm;

 if(leader)
  {
   tm=SW->query_team_others();
   disband();
   if(sizeof(tm)>1)
     tm[0]->make_team(tm-({tm[0]}));
  }

 handler->notify_monster_killed(pts,killer,SW);

 SW->do_die(killer);
}

void attacked_by(object ob)
{
 object sh;

 if(interactive(ob) && !ob->has_safe_shadow())
  {
   sh=clone_object(SAFE_SHADOW);
   if(!sh->shadow_me(ob)) sh->remove_object();
   else sh->set_handler(handler);
  }

 set_alarm(0.5,0.0,&notify_team_attack());

 SW->attacked_by(ob);
}

void attack_object(object ob)
{
 object sh;

 if(interactive(ob) && !ob->has_safe_shadow())
  {
   sh=clone_object(SAFE_SHADOW);
   if(!sh->shadow_me(ob)) sh->remove_object();
   else sh->set_handler(handler);
  }

 SW->attack_object(ob);
}

