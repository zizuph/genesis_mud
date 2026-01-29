/*
 * Infection utilizing poison_effect code to inflict an
 * infectious debilitation from rust and bio-grime.  Delivered
 * by Aysha's (Brix ganger in Palanthas) knife.  Changed some
 * default messages to make it look like an infection rather
 * than a poison.
 *
 * Mortis 05.2006
 *
 */

#include "../../local.h"
#include <poison_types.h>
#include <ss_types.h>
#include <files.h>
#include <macros.h>
 
inherit "/std/poison_effect";

create_poison_effect()
{
	set_time(900 + random(120));
	set_interval(34 + random(5));
	set_strength(51 + random(5));
	set_damage(({POISON_HP, 100, POISON_FATIGUE, 25, POISON_STAT, SS_CON}));
	set_poison_type("grime and rust infection");
}

public void
timeout()
{
	if (silent < 2)
	{
		tell_object(poisonee, "You feel as if the infection has finally "
		+ "passed.\n");
	}

	remove_alarm(a_dam);
	remove_object();
}

public void
kill_player()
{
	if (a_time)
		remove_alarm(a_time);

	a_time = 0;

	say(QCTNAME(poisonee) + " collapses in a heap upon the ground, blackish "
	+ "goo oozing from " + HIS(poisonee) + " many orifaces as " + HE(poisonee)
	+ " gurgles " + HIS(poisonee) + " last.\n", poisonee);
    tell_object(poisonee, "You have died oozing.\n");
	poisonee->do_die(TO);

	remove_object();
}

public varargs void
start_poison(object poisoner)
{
    object previous_ob = previous_object();

    poisonee = environment(this_object());

    /* Find out who owns us */
    if (!living(poisonee))
    {
         /* If they aren't living, we punt. */
         remove_object();
         return;
    }

    if (!recovery)
    {
        /* Register who poisoned us. */
        responsible_object = file_name(previous_ob);
        responsible_living = "";
        /* If not given, let's try to find out. Could be a weapon. */
        if (!objectp(poisoner) && IS_WEAPON_OBJECT(previous_ob))
        {
            poisoner = previous_ob->query_wielded();
        }
        if (objectp(poisoner))
        {
            poisoner = this_player();
            responsible_living = "TP: ";
        }
        if (objectp(poisoner))
        {
            if (interactive(poisoner))
            {
                responsible_living += poisoner->query_name() + "; " +
                    file_name(poisoner);
            }
            else
            {
                responsible_living += file_name(poisoner);
            }
        }
        else
        {
            responsible_living = "unspecified";
        }
    }

    if (silent < 2)
    {
        tell_object(poisonee, "You have been infected!\n");
    }

    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    if (interval)
    {
        a_dam = set_alarm((interval / 2.0) + (rnd() * interval), 0.0,
            damage_player);
    }

    a_time = set_alarm(p_time, 0.0, timeout);
}
