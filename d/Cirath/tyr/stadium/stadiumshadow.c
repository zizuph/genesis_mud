/* This shadow is a Ged Production (tm) */

inherit "/std/shadow";

#include "defs.h"
#include <std.h>
#include <macros.h>
#include <filepath.h>
#include <language.h>

#define ARENA TYR_STADIUM+"stadium"

nomask do_die(object killer)
{
    string str;
    object me,*elist;
    int i;

    me =query_shadow_who();
    if (me->query_hp() > 0) return;

    if(!living(killer)) 
    { 
	log_file("arena_kills", ctime(time()) + " " + me->query_real_name() + 
	  " by " + killer->query_short() + "\n");
	me->do_die(killer);
	remove_shadow();
	return;  /* Not reached -- Modifid by Lucius. 1-13-2001 */
    }

    elist =(me->query_enemy(-1) & all_inventory(environment(me)) );
    for(i=0 ; i < sizeof(elist) ; i++)
    {
	elist[i]->stop_fight(me);
	me->stop_fight(elist[i]);
    }


    str=QCTNAME(killer)+" did a devastating attack on "+QCTNAME(me)+" and "+
    "a magic force stops the fight.\n";
    tell_room(ARENA,str,({me,killer}));
    me->catch_msg("You lost the fight and "+QCTNAME(killer)+" won.\n");
    killer->catch_msg("You won over "+QCTNAME(me)+".\n");
    log_file("deaths", ctime(time()) + " " + me->query_real_name() + 
      " by " + killer->query_real_name() + "\n");
    me->set_hp(1);
    me->command("seats");
}    

nomask
add_panic(int x){}

nomask 
run_away(){}

geds_special_func()
{
    remove_shadow();
}

return_unkillable()
{
    return 1;
}
