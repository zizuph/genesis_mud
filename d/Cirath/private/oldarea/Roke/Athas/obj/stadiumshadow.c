/* This shadow is a Ged Production (tm) */

inherit "/std/shadow";

#include "/d/Roke/common/defs.h"
#include <std.h>
#include <macros.h>
#include <filepath.h>
#include <language.h>

#define ARENA "/d/Roke/Athas/room/tyr/stadium/stadium"

nomask do_die(object killer)
{
    string str;
    object me,*elist;
    int i;
    me =query_shadow_who();
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
    me->set_hp(1);
}    

nomask
add_panic(int x){}

nomask 
run_away(){}

geds_special_func()
{
    remove_shadow();
}
