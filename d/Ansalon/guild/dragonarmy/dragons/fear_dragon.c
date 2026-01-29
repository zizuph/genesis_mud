/*
 * This dragon is used in dragonfear special.
 */
#pragma strict_types
#pragma save_binary

inherit "/d/Krynn/std/dragon_base";

#include "../guild.h"

#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <ss_types.h>

static object summoner;

void
set_summoner(object ob)
{
    summoner = ob;
    set_colour(ob->query_dragonarmy_division());
}

object
query_summoner()
{
    return summoner;
}

void
remove_object()
{
    tell_room(E(TO), "The "+ ::short_desc()+" soars up into the sky and disappears.\n");
    move_living("M", TEMP_DRAGON_ROOM, 1, 1);
    ::remove_object();
}

void
set_dragonfear_time(int t)
{
    set_alarm(itof(t), 0.0, remove_object);
}

void
follow_summoner()
{
    set_alarm(itof(5+random(5)), 0.0, follow_summoner);
    if (objectp(summoner) && E(TO) != E(summoner) &&
	!E(summoner)->query_prop(ROOM_I_INSIDE))
    {
	tell_room(E(TO), "The "+ ::short_desc()+" flies away following "+
	    QTNAME(summoner)+".\n");
	tell_room(E(summoner), C(LANG_ADDART(::short_desc()))+
	    " swoops out of the clouds above with a shriek, circling over "+
	    "the battlefield with cruel interest.\n");
	move_living("M", E(summoner), 1, 1);
    }
}

void
create_dragon_npc()
{
    add_prop(LIVE_I_NEVERKNOWN, 1);
    setup_dragon();
    add_prop(OBJ_M_NO_ATTACK, "Attack flying dragon? How???\n");
    set_adj("flying");
}

string
long_desc()
{
    return "Flying above you is one of the children of " +
      "Takhisis, "+LANG_ADDART(::short_desc()) +". This " +
      "massive reptile is covered with thick scales from its " +
      "sinuous tail to its sinister head, a formidable defense " +
      "overshadowed only by its awesome destructive capability. "+
      C(HE(TO))+" circles over the battlefield with cruel interest.\n";
}

string
short_desc()
{
    return "flying " + ::short_desc();
}

public int
query_dragonarmy_dragon()
{
    return 1;
}

public object
clone_dragon_fear_object()
{
    setuid();
    seteuid(getuid());
    return clone_object(DRAGONARMY_DRAGON + "dragon_fear_obj");
}
