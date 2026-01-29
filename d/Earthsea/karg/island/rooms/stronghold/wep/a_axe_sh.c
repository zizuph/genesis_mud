inherit "/std/shadow";

#include <formulas.h>

#define SW shadow_who
#define DEBUG(x) find_player("ged")->catch_msg(x+"\n")

object axe;

void set_axe(object a) {axe=a;}

public int set_stat_extra(int stat, int val)
{
 int res;

 res=SW->set_stat_extra(stat,val);

 axe->check_still_worthy();
 return res;
}

void check_axe()
{
axe->check_still_worthy();
}

public int add_tmp_stat(int stat, int ds, int dt)
{
 if(!SW->add_tmp_stat(stat,ds,dt)) return 0;

 set_alarm(itof(dt * F_INTERVAL_BETWEEN_HP_HEALING),0.0,&check_axe());
}

void remove_a_axe_shadow()
{
 remove_shadow();
}

int has_a_axe_shadow() {return 1;}

public int set_skill(int skill, int val)
{
 int res;

 res=SW->set_skill(skill,val);

 axe->check_still_worthy();
 return res;
}

