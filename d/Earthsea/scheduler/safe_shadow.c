inherit "/std/shadow";

#include <macros.h>
#include <std.h>

#include "defs.h"
#include "event_defs.h"
#include "func.h"

#define SW shadow_who

object handler;

int has_safe_shadow() {return 1;}

void set_handler(object h) {handler=h;}
object query_handler() {return handler;}

void remove_safe_shadow() {remove_shadow();}

varargs int shadow_me(mixed to_shadow)
{
 string *ev;

 ev=(SCHEDULER)->filter_events(({P_TYPE,P_STATUS}),
   ({"Invasion",ST_RUNNING}));

 if(!sizeof(ev)) return 0;

 return ::shadow_me(to_shadow);
}

void do_die(object killer)
{
 string *ev,*mon;
 object *enm;
 int i;

 ev=(SCHEDULER)->filter_events(({P_TYPE,P_STATUS}),
   ({"Invasion",ST_RUNNING}));

 if(!sizeof(ev))
  {
   SW->do_die(killer);
   remove_shadow();
  }

 mon=(SCHEDULER)->query_prop_value(ev[0],"monsters");
 if(member_array(fix_file(MASTER_OB(killer)),mon)==-1)
  {
   SW->do_die(killer);
   remove_shadow();
  }

 SW->catch_msg("You have been defeated by invaders and sent "+
   "back to your start location!\n");
 enm=SW->query_enemy(-1);
 SW->stop_fight(enm);
 for(i=0;i<sizeof(enm);i++) enm->stop_fight(SW);
 SW->move_living("X",SW->query_default_start_location());
 handler->notify_player_defeated(SW,killer);
 remove_shadow();
}

void attacked_by(object ob)
{
 string *ev,*mon;

 SW->attacked_by(ob);

 ev=(SCHEDULER)->filter_events(({P_TYPE,P_STATUS}),
   ({"Invasion",ST_RUNNING}));

 if(!sizeof(ev)) remove_shadow();
}

void attack_object(object ob)
{
 string *ev,*mon;

 SW->attack_object(ob);

 ev=(SCHEDULER)->filter_events(({P_TYPE,P_STATUS}),
   ({"Invasion",ST_RUNNING}));

 if(!sizeof(ev)) remove_shadow();
}

