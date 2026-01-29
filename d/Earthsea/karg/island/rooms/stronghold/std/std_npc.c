#include <wa_types.h>

#include "defs.h"

inherit ISLAND_STD+"karg";

#define DEBUG(x) find_player("ged")->catch_msg(x+"\n")

int level=0;
int stil=0;
int calm=0;

void set_level(int lv) {level=lv;}
int query_level() {return level;}

void create_stronghold_karg()
{
}

void create_karg()
{
 create_stronghold_karg();
}

int special_attack(object enemy)
{
 int dmg;
 mixed *hitresult;
 string how,wep_desc;
 string *wep;
 int i;
 object *subinv;

 if(!level) return 0;
 if(random(6-level)) return 0;

 wep=TO->query_weapon(-1);
 if(!sizeof(wep)) return 0;

 wep_desc="";
 for(i=0;i<sizeof(wep);i++) 
  {
   wep_desc+=wep[i]->short();
   if(i!=sizeof(wep)-1) wep_desc+=" and ";
  }
 
 dmg=(100+random(50))*level;
 enemy->catch_msg(QTN(TO,enemy)+" jumps at you , breaking you defence, "+
   "swinging "+POS(TO)+" "+wep_desc+" wildly.\n");
 subinv=ENV(TO)->subinventory();
 for(i=0;i<sizeof(subinv);i++)
   if(interactive(subinv[i]) && !subinv[i]->query_options(5) &&
   subinv[i]!=enemy)
     subinv[i]->catch_msg(QTN(TO,subinv[i])+" jumps at "+
       QtN(enemy,subinv[i])+", swinging "+POS(TO)+" "+wep_desc+
       " wildly.\n");
 
 hitresult=enemy->hit_me(dmg,W_SLASH,TO,-1);

 how = "You avoid the attack easily, getting only a tiny scratch.\n";

 if(hitresult[0] > 5)
   how = "You are barely scratched by "+POS(TO)+" attack.\n";
 if(hitresult[0] > 10)
   how = "You are lightly wounded by "+POS(TO)+" attack.\n";
 if(hitresult[0] > 15)
   how = "You are rather wounded by "+POS(TO)+" attack.\n";
 if(hitresult[0] > 20)
   how = "You are hit hard from "+POS(TO)+" attack.\n";
 if(hitresult[0] > 25)
   how = "You are brutally wounded by "+POS(TO)+" attack.\n";
 if(hitresult[0] > 30)
   how = "Your bones crash as you are devastated by "+POS(TO)+
     " attack.\n";

 enemy->catch_msg(how);

 if(enemy->query_hp()<0) enemy->do_die(TO);

 return 0;
}

void attack_enemy(object enemy)
{
 command("shout Die enemy of Karg Empire! DIE !!!");
 command("kill "+enemy->query_real_name());
}

void notify_enemy_arrival(object enemy)
{
 set_alarm(0.1,0.0,&attack_enemy(enemy));
}

void attacked_by(object enemy)
{
 (SERVER)->add_enemy(enemy->query_real_name());
 ::attacked_by(enemy);
}

void set_stil(int st) {stil=st;}

varargs int move_living(string how, mixed to_dest, int dont_follow,
int no_glance)
{
 if(stil) return 3;

 return ::move_living(how,to_dest,dont_follow,no_glance);
}

void set_calm(int cl) {calm=cl;}

void attack_object(object ob)
{
 if(calm && ob->query_real_name()=="karg") return;

 ::attack_object(ob);
}

int query_calm() {return calm;}
int query_stil() {return stil;}
