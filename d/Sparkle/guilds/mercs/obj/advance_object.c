/*
 * /d/Genesis/guilds/merc/obj/advance_object.c, by Morrigan October, 2002
 * 
 * This object is to allow for the environment to use the 'advance' 
 *     command, as relevant to the mercenary guild special 'retreat'.
 */

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include "../merc.h"
#include <stdproperties.h>
#include <composite.h>
#include <cmdparse.h>
#include <macros.h>

#define MERC_I_ADVANCING "_merc_i_advancing"

int gDuration = 5;
object gRetreater, gRoom;

public void set_duration(int i) { gDuration = i; }
public void set_retreater(object ob) { gRetreater = ob; }
public void set_retreat_room(object ob) { gRoom = ob; }
public int query_duration() { return gDuration; }
public object query_retreater() { return gRetreater; }
public object query_retreat_room() { return gRoom; }

public void duration_exceeded()
{
    if (E(TO)->query_prop(MERC_I_ADVANCING))
	return;

    remove_object();
}

public object *query_attackers(object ob)
{ 
    object *en = ob->query_enemy(-1);
    object *ret = ({ });
    int i;

    if (!sizeof(en))
	return 0;

    for (i=0;i<sizeof(en);i++)
        if (en[i]->query_attack() == ob)
	    ret += ({ en[i] });

    return ret;
}

public int complete_advance(object me, object retreater)
{
    object *enemies = query_attackers(retreater), noatt;
    int i;

    me->remove_prop(MERC_I_ADVANCING);

    if (!sizeof(enemies))
    {
	me->catch_tell(retreater->query_The_name(me)+" is no longer under attack, "+
	    "and does not need to retreat.\n");
	return remove_object();
    }

    if (E(retreater) != E(me))
    {
        me->catch_tell(retreater->query_The_name(me)+" is no longer here for "+
	    "you to advance before.\n");
	return remove_object();
    }

    if (retreater->query_prop(MERC_O_RETREATING) != me)
    {
        me->catch_tell(retreater->query_The_name(me) + " is no longer in a "+
	    "position before which you could advance safely.\n");
	return remove_object();
    }

    for (i = 0; i < sizeof(enemies); i++)
    {
        me->attack_object(enemies[i]);
        enemies[i]->attack_object(me);
        enemies[i]->catch_tell("As "+retreater->query_the_name(enemies[i])+
	    " falls back several steps, "+me->query_the_name(enemies[i])+
	    " steps between the two of you, cutting off your attacks.\n");
    }

/*
    if (!me->query_attack())
        me->attack_object(enemies[0]);
*/

    retreater->remove_prop(MERC_O_RETREATING);
    me->catch_tell("As "+retreater->query_the_name(me)+" falls back several "+
	"steps, "+
	"you immediately rush forward, getting between "+OBJECTIVE(retreater)+
	" and "+COMPOSITE_LIVE(enemies)+".\n");
    retreater->catch_tell("As you fall back several steps, "+
	me->query_the_name(retreater)+" you immediately rushes forward, "+
	"getting between you and "+COMPOSITE_LIVE(enemies)+".\n");
    tell_room(E(me), "As "+QTNAME(retreater)+" falls back several steps, "+
	QTNAME(me)+" immediately rushes forward, getting between "+
	OBJECTIVE(retreater)+" and "+COMPOSITE_LIVE(enemies)+".\n",
	enemies + ({ me, retreater }) );

    setuid(); seteuid(getuid());

    noatt = clone_object(MOBJ+"no_attack_object");
    noatt->set_duration(query_duration());
    noatt->set_advancer(me);
    noatt->set_retreater(retreater);
    noatt->move(retreater, 1);

    return remove_object();
}

public int do_advance(string str)
{
    object *enemies, *gag;
    object *ob, me;
    int my_dur;
 
    enemies = query_attackers(query_retreater());

    if (!str)
    {
       str = OB_NAME(query_retreater());
    }

    if (!sizeof(enemies))
    {
	write(query_retreater()->query_the_name(TP)+" is no longer under "+
	    "attack, and has no need to retreat.\n");
	return remove_object();
    }

    if (TP->query_prop(MERC_I_ADVANCING))
    {
        write("You are in the process of attempting to retreat already.\n");
	return 1;
    }

    if (!parse_command(str, E(TP), "[before] [the] %l", ob) || 
	!sizeof(ob = NORMAL_ACCESS(ob, 0, 0)))
    {
        write("Advance before whom?\n");
        return 1;
    }

    NF("You are too stunned to do this.\n");
    if (TP->query_prop(LIVE_I_STUNNED))
	return 0;

    if (ob[0] != query_retreater())
	return 0;

    if (E(query_retreater()) != E(TP))
    {
        write(query_retreater()->query_The_name(TP)+" is no longer here for "+
	    "you to advance before.\n");
	return remove_object();
    }

    if (query_retreater()->query_prop(MERC_O_RETREATING) != TP)
    {
        write(query_retreater()->query_The_name(TP) + " is no longer in a "+
	    "position before which you could advance safely.\n");
	return remove_object();
    }

    if (sizeof(ob) > 1)
    {
        write("Advance before whom?\n");
	return 1;
    }

    if (ob[0] != query_retreater())
    {
        write("Advance before whom?\n");
	return 1;
    }

    me = TP;

    if (IS_MERC(me) && 
	MCREST->query_members_lord(me->query_name()) == 
	query_retreater()->query_name())
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
        write("You attempt to advance, but bump into "+
	query_retreater()->query_the_name(me)+" clumsily.\n");
        return 1;
    }

    me->add_prop(MERC_I_ADVANCING, 1);

    write("You begin looking for an opportunity to advance.\n");
    set_alarm(itof(my_dur), 0.0, &complete_advance(me, query_retreater()));
    return 1;
}

public void create_object()
{
    set_name("_merc_advance_object_");
    set_short("_merc_advance_object_");
    set_long("This object should not be visible.");
    add_prop(OBJ_M_NO_DROP, "The poster cannot be taken.\n");
    set_no_show();
}

public void do_tell()
{
    if (!E(TO)->query_skill(SS_MERC_AUTOCOMPLY))
	E(TO)->catch_tell("You may use the 'advance' command to comply "+
	    "with "+query_retreater()->query_the_name(E(TO))+"'s order.\n");

    return;
}

public void init()
{
    ::init();

    set_alarm(0.5, 0.0, &do_tell());
    set_alarm(itof(query_duration()), 0.0, &duration_exceeded());

    add_action("do_advance", "advance");
}
