/*
 *	/d/Gondor/minas/npc/arrest_attacker.c
 *
 *	Olorin, June 14th, 1995
 *
 *	This file contains routines to arrest a player in Minas Tirith
 *	when he or she attacks a npc that inherits this file.
 *
 *	Usage:
 *
 *	inherit "/d/Gondor/minas/npc/arrest_attacker";
 *
 *	void
 *	attacked_by(object ob)
 *	{
 *	    ::attacked_by(ob);
 *
 *	    // this will make guards in the neighbouring rooms come to help
 *	    set_alarm(4.0, 0.0, &check_for_guards(ob));
 *
 *	    // this will make guards appear that arrest the attacker and
 *	    // put him into prison.
 *	    set_alarm(20.0 + 40.0 * rnd(), 0.0, &arrest_attacker(ob));
 *	}
 */
#include <filter_funs.h>

#include "/d/Gondor/defs.h"

static int      filter_guards(object x) { return (x->id("_gondor_guard")); }

varargs void
check_for_guards(object enemy)
{
    int     i, j;
    object *guards;
    string *rooms;

    if (!objectp(enemy))
        if (!objectp(enemy = TO->query_attack()))
            return;

    FIX_EUID
    rooms = ENV(TO)->query_exit_rooms();

    for (i = 0; i < sizeof(rooms); i++)
    {
        rooms[i]->load_me();
        guards = FILTER_LIVE(all_inventory(find_object(rooms[i])));
        guards = filter(guards, filter_guards);

        for (j = 0; j < sizeof(guards); j++)
        {
            guards[j]->move_living("running", ENV(TO));
            guards[j]->do_attack(enemy);
        }
    }
}

void
arrest_attacker(object attacker)
{
    object  officer;

    if (!objectp(attacker))
        attacker = TO->query_attack();

    if (!objectp(attacker) || !present(attacker, ENV(TO)))
        return;

    FIX_EUID
    officer = clone_object(MINAS_DIR + "npc/arrest_officer");
    officer->arm_me();
    officer->set_enemy(attacker);
    officer->move_living("from the void", ENV(TO));
}
