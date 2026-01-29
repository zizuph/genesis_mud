/*
 * /d/Gondor/common/guild/obj/earthworm.c
 *
 * Component for the Ranger spell regrowth.
 *
 * Coded by Gwyneth on June 4, 2000
 */

inherit "/std/food";

#include <macros.h>
#include <math.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

void
create_food()
{
    set_name("earthworm");
    add_name("worm");
    add_name("regrowth_ingredient");
    add_prop(HEAP_S_UNIQUE_ID, "regrowth_ingredient");

    set_adj("pink");
    add_adj("squirming");

    set_short("pink earthworm");
    set_pshort("pink earthworms");

    set_long("Its pink segmented body thrashes around, trying to " +
      "find a bit of earth to burrow into.\n");

    set_amount(10);
}

public void
special_effect(int amnt)
{
    write("You slurp " + TO->short() + " up through your lips. " +
      "You feel the thrashing around of " + TO->short() +
      " in your mouth before you chomp down and swallow.\n");
    say(QCTNAME(TP) + " slurps " + TO->short() +
      " up through " + TP->query_possessive() + " lips.\n");
}

void
enter_env(object dest, object old)
{
    int ident = 38261588;
    object name;

    ::enter_env(dest, old);

    if(living(dest))
    {
	name = dest->query_real_name();

	if(dest->query_skill(SS_ANI_HANDL) < (20 +
	    NAME_TO_RANDOM(name, ident, 11)))
	{
	    set_alarm(1.0, 0.0, &dest->catch_tell("You can't seem to handle " +
		"the slippery earthworm and drop it.\n"));
	    set_alarm(1.0, 0.0, &tell_room(environment(dest),
		QCTNAME(dest) + " loses " + dest->query_possessive() +
		" grip on the slippery earthworm and drops it.\n", dest));
	    TO->move(environment(dest));
	}
    }
}
