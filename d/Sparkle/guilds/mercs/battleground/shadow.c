/* 
 * This shadow is a Ged Production (tm) 
 *
 * Well its used in the Arena of the Mercernaries in Sparkle.
 * Lunatari 2006
 */
inherit "/std/shadow";

#include "../merc.h"
#include <std.h>
#include <filepath.h>

#define ARENA MBATTLE +"battlegrounds"

nomask do_die(object killer)
{
    string str;
    object me,*elist;
    object raddick;
    int i;

    me =query_shadow_who();
    if (me->query_hp() > 0) return;

    if(!living(killer)) 
    { 
        write_file(MERC_ARENA_LOG, extract(ctime(time()), 4, 15) + " " +
        me->query_name() + " killed by "+killer->query_short()+"\n");
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

    raddick = present("raddick", environment(shadow_who));

    tell_room(ARENA, QCTNAME(raddick)+" deems that "+QTNAME(me)+
	" is no longer able to fight effectively, and declares that "+
	POSSESSIVE(me)+" fight is over. "+QCTNAME(killer)+" has defeated "+
	QTNAME(me)+".\n", ({ killer,me }) );

    me->catch_msg(raddick->query_The_name(me)+" steps in and halts your fight "+
	"with "+killer->query_the_name(me)+", declaring "+OBJECTIVE(killer)+
	" the winner.\n");

    killer->catch_msg(raddick->query_The_name(killer)+" steps in and halts your "+
	"fight with "+me->query_the_name(killer)+", declaring you the "+
	"winner.\n");

    write_file(MERC_ARENA_LOG, extract(ctime(time()), 4, 15) + " " +
        me->query_name() + " (" + me->query_average_stat() + " / "+
	me->query_stat(SS_OCCUP) + ") "+
	" defeated by "+killer->query_name()+" ("+killer->query_average_stat()+
	" / "+ killer->query_stat(SS_OCCUP)+")\n");

    me->set_hp(me->query_max_hp() / 20);
}    

nomask
add_panic(int x) { }

nomask 
run_away() { }

geds_special_func()
{
    remove_shadow();
}

return_unkillable()
{
    return 1;
}
