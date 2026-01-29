/*
 *	/d/Krynn/neraka/obj/invis_object.c
 *
 *	Olorin, December 1995
 */
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/neraka/local.h"

#define INVIS_POTIONS "_live_i_invis_potions"

static int     time = 1;

void
create_object()
{
    set_name("Invisibility_Object");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    set_no_show();
}

void
set_duration(int i)
{
    time = i;
}

void
end_effect()
{
    object  ob = E(TO),
            poison;

    if (ob->query_invis())
    {
        ob->remove_prop(OBJ_I_INVIS);
        ob->catch_msg("You are now visible.\n");
        tell_room(E(ob), QCTNAME(ob) + " " + ob->query_mm_in() + "\n", ob, ob);

	if (ob->query_prop(INVIS_POTIONS) > (5 + random(10)))
	  {
	    seteuid(getuid(TO));
	    log_file("invispoison",
		     extract(ctime(time()), 4, 15) + " " + ob->query_name() + "\n",10000);
	    poison = clone_object("/std/poison_effect");
	    poison->set_interval(10);
	    poison->set_time(500);
	    poison->set_damage(({ POISON_FATIGUE, 40, POISON_HP,
				    ob->query_max_hp() / 9, POISON_STAT, SS_CON }));
	    poison->set_strength(70 + random(10));
	    if (poison->move(ob))
	      poison->move(ob, 1);
	    poison->start_poison();
	  }
	else
	  ob->add_prop(INVIS_POTIONS, ob->query_prop(INVIS_POTIONS) + 1);
	
	set_alarm(0.0, 0.0, remove_object);
    }
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(to) || !living(to))
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    if (to->query_invis())
    {
        to->catch_msg("Nothing seems to happen\n");
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    to->catch_msg("You are now invisible.\n");
    tell_room(E(to), QCTNAME(to) + " " + to->query_mm_out() + "\n", to, to);
    to->add_prop(OBJ_I_INVIS, 1);
    set_alarm(itof(time), 0.0, end_effect);
}

void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);

    end_effect();
}

