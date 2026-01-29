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

int gDuration = 100;
object gAdvancer = find_living("gwyneth");
object gRoom = find_object("/w/morrigan/workroom");

public void set_duration(int i) { gDuration = i; }
public void set_advancer(object ob) { gAdvancer = ob; }
public void set_advance_room(object ob) { gRoom = ob; }
public int query_duration() { return gDuration; }
public object query_advancer() { return gAdvancer; }
public object query_advance_room() { return gRoom; }

public void duration_exceeded()
{
    object me = environment(this_object());

    if (query_advancer()->query_prop(MERC_O_ADVANCING))
        me->catch_tell(query_advancer()->query_The_name(me) + " falls "+
	"out of position, preventing your retreat.\n");
    remove_object();
}

public int do_retreat(string str)
{
    object *enemies, *gag;
    int i;
    object *ob;
 
    enemies = TP->query_enemy(-1);

    if (!sizeof(enemies))
    {
	write("You are no longer under attack, and have no need to retreat.\n");
	return remove_object();
    }

    if (!parse_command(str, E(TP), "[behind] [the] %l", ob) || 
	!sizeof(ob = NORMAL_ACCESS(ob, 0, 0)))
    {
        write("Retreat behind whom?\n");
        return 1;
    }

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

    for (i = 0; i < sizeof(enemies); i++)
    {
        enemies[i]->attack_object(query_advancer());
        enemies[i]->catch_tell("As "+TP->query_the_name(enemies[i])+" falls "+
	    "back several steps, "+query_advancer()->query_the_name(enemies[i])+
	    " steps between the two of you, cutting off your attacks.\n");
    }

    if (!query_advancer()->query_attack())
        query_advancer()->attack_object(enemies[0]);

    query_advancer()->remove_prop(MERC_O_ADVANCING);

    write("As you fall back several steps, "+query_advancer()->query_the_name(TP)+
	" immediately rushes forward, getting between you and "+
	COMPOSITE_LIVE(enemies)+".\n");
    query_advancer()->catch_tell("As "+TP->query_the_name(query_advancer())+
	" falls back several steps, you immediately rush forward, getting "+
	"between "+OBJECTIVE(TP)+" and "+COMPOSITE_LIVE(enemies)+".\n");

    gag = enemies + ({ TP, query_advancer() });

    tell_room(E(TP), "As "+QTNAME(TP)+" falls back several steps, "+
	QTNAME(query_advancer())+" immediately rushes forward, getting between "+
	OBJECTIVE(TP)+" and "+COMPOSITE_LIVE(enemies)+".\n",
	enemies + ({ TP, query_advancer() }) );
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

public void init()
{
    ::init();

    set_alarm(itof(query_duration()), 0.0, &duration_exceeded());

    add_action("do_retreat", "retreat");
}
