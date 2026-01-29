/*
 * /d/Genesis/guilds/merc/obj/retreat_object.c, by Morrigan October, 2002
 * 
 * This object is to allow for the environment to use the 'retreat' 
 *     command, as relevant to the mercenary guild special 'advance'.
 */

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include "../merc.h"
#include <stdproperties.h>
#include <composite.h>
#include <cmdparse.h>
#include <macros.h>

#define MERC_I_RETREATING "_merc_i_retreating"

int gDuration = 5;
object gAdvancer, gRoom;

public void set_duration(int i) { gDuration = i; }
public void set_advancer(object ob) { gAdvancer = ob; }
public void set_advance_room(object ob) { gRoom = ob; }
public int query_duration() { return gDuration; }
public object query_advancer() { return gAdvancer; }
public object query_advance_room() { return gRoom; }

public void duration_exceeded()
{
    if (E(TO)->query_prop(MERC_I_RETREATING))
	return;

    remove_object();
}

public object *query_attackers()
{ 
    object me = E(TO);
    object *en = me->query_enemy(-1);
    object *ret = ({ });
    int i;

    if (!sizeof(en))
	return 0;

    for (i=0;i<sizeof(en);i++)
        if (en[i]->query_attack() == TP)
	    ret += ({ en[i] });

    return ret;
}

public int complete_retreat(object me, object advancer)
{
    object *enemies = query_attackers(), noatt;
    int i;

    me->remove_prop(MERC_I_RETREATING);

    if (!sizeof(enemies))
    {
	me->catch_tell("You are no longer under attack, and have no need to "+
	    "retreat.\n");
	return remove_object();
    }

    if (E(advancer) != E(me))
    {
        me->catch_tell(advancer->query_The_name(me)+" is no longer here for "+
	    "you to retreat behind.\n");
	return remove_object();
    }

    if (advancer->query_prop(MERC_O_ADVANCING) != me)
    {
        me->catch_tell(advancer->query_The_name(me) + " is no longer in a "+
	    "position to which you could retreat safely.\n");
	return remove_object();
    }

    for (i = 0; i < sizeof(enemies); i++)
    {
        query_advancer()->attack_object(enemies[i]);
        enemies[i]->attack_object(query_advancer());
        enemies[i]->catch_tell("As "+me->query_the_name(enemies[i])+" falls "+
	    "back several steps, "+advancer->query_the_name(enemies[i])+
	    " steps between the two of you, cutting off your attacks.\n");
    }

/*
    if (!advancer->query_attack())
        advancer->attack_object(enemies[0]);
*/

    advancer->remove_prop(MERC_O_ADVANCING);
    me->catch_tell("As you fall back several steps, "+advancer->query_the_name(me)+
	" immediately rushes forward, getting between you and "+
	COMPOSITE_LIVE(enemies)+".\n");
    advancer->catch_tell("As "+me->query_the_name(advancer)+
	" falls back several steps, you immediately rush forward, getting "+
	"between "+OBJECTIVE(me)+" and "+COMPOSITE_LIVE(enemies)+".\n");
    tell_room(E(me), "As "+QTNAME(me)+" falls back several steps, "+
	QTNAME(advancer)+" immediately rushes forward, getting between "+
	OBJECTIVE(me)+" and "+COMPOSITE_LIVE(enemies)+".\n",
	enemies + ({ me, advancer }) );

    setuid(); seteuid(getuid());

    noatt = clone_object(MOBJ+"no_attack_object");
    noatt->set_duration(query_duration());
    noatt->set_advancer(advancer);
    noatt->set_retreater(me);
    noatt->move(me, 1);

    return remove_object();
}

public int do_retreat(string str)
{
    object *enemies, *gag;
    object *ob, me;
    int my_dur;
 
    enemies = query_attackers();

    if (!str)
    {
       str = OB_NAME(query_advancer());
    }

    if (!sizeof(enemies))
    {
	write("You are no longer under attack, and have no need to retreat.\n");
	return remove_object();
    }

    if (TP->query_prop(MERC_I_RETREATING))
    {
        write("You are in the process of attempting to retreat already.\n");
	return 1;
    }

    if (!parse_command(str, E(TP), "[behind] [the] %l", ob) || 
	!sizeof(ob = NORMAL_ACCESS(ob, 0, 0)))
    {
        write("Retreat behind whom?\n");
        return 1;
    }

    NF("You are too stunned to do this.\n");
    if (TP->query_prop(LIVE_I_STUNNED))
	return 0;

    if (ob[0] != query_advancer())
	return 0;

    if (E(query_advancer()) != E(TP))
    {
        write(query_advancer()->query_The_name(TP)+" is no longer here for "+
	    "you to retreat behind.\n");
	return remove_object();
    }

    if (query_advancer()->query_prop(MERC_O_ADVANCING) != TP)
    {
        write(query_advancer()->query_The_name(TP) + " is no longer in a "+
	    "position to which you could retreat safely.\n");
	return remove_object();
    }

    if (sizeof(ob) > 1)
    {
        write("Retreat behind whom?\n");
	return 1;
    }

    if (ob[0] != query_advancer())
    {
        write("Retreat behind whom?\n");
	return 1;
    }

    me = TP;

    if (IS_MERC(me) && 
	MCREST->query_members_lord(me->query_name()) == 
	query_advancer()->query_name())
    {
        my_dur = 20 - (me->query_skill(SS_MERC_TACTICS) / 5);
        my_dur = MAX(4, my_dur);
    }
    else if (IS_MERC(me) || me->query_wiz_level())
    {
        my_dur = 20 - (me->query_skill(SS_MERC_TACTICS) / 10);
        my_dur = MAX(8, my_dur);
    }
    else
    {
        write("You attempt to retreat, but bump into "+
	query_advancer()->query_the_name(me)+" clumsily.\n");
        return 1;
    }

    me->add_prop(MERC_I_RETREATING, 1);

    write("You begin looking for an opportunity to fall back.\n");
    set_alarm(itof(my_dur), 0.0, &complete_retreat(TP, query_advancer()));
    return 1;
}

public void create_object()
{
    set_name("_merc_retreat_object_");
    set_short("_merc_retreat_object_");
    set_long("This object should not be visible.");
    add_prop(OBJ_M_NO_DROP, "The poster cannot be taken.\n");
    set_no_show();
}

public void do_tell()
{
    if (!E(TO)->query_skill(SS_MERC_AUTOCOMPLY))
	E(TO)->catch_tell("You may use the 'retreat' command to comply "+
	    "with "+query_advancer()->query_the_name(E(TO))+"'s order.\n");

    return;
}

public void init()
{
    ::init();

    set_alarm(0.5, 0.0, &do_tell());
    set_alarm(itof(query_duration()), 0.0, &duration_exceeded());

    add_action("do_retreat", "retreat");
}
