/*
 * Melt this ice, and a gargoyle will emerge from it. *demonical laughter*
 *
 *					Tricky, 28-2-92
 */
inherit "/std/object";

#include "defs.h"
#include "/sys/macros.h"
#include "/sys/cmdparse.h"
#include "/sys/stdproperties.h"

void
create_object()
{
    set_name(({"block", "ice"}));
    set_adj(({"block","of"}));
    set_short("block of ice");
    set_long(break_string(
	  "The block of ice is barring the stairs that lead up. Inside "
	+ "it, you can vaguely make out a hideous shape. It seems some "
	+ "powerfull mage casted a frost spell on the guardian of the "
	+ "top floor of this tower.\n", 70));

    add_prop(OBJ_I_WEIGHT, 500000);
    add_prop(OBJ_I_VOLUME, 500000);
}

void
init()
{
    ::init();
    add_action("do_melt", "melt");
}

int
do_melt(string str)
{
    object *obs, tp;
    string str1;

    if (!str)
    {
	notify_fail("Melt what?\n");
	return 0;
    }

    str = lower_case(str);

    notify_fail("Melt what with what?\n");
    if (sscanf(str, "ice with %s", str1) != 1)
	if (sscanf(str, "block with %s", str1) != 1)
	    return 0;

    tp = this_player();
    obs = FIND_STR_IN_OBJECT(str1, tp);

    if (!sizeof(obs))
    {
	notify_fail("You have no " + str1 + ".\n");
	return 0;
    }

    if (sizeof(obs) > 1)
    {
	notify_fail("Could you be more specific?\n");
	return 0;
    }

    if (obs[0]->query_prop(OBJ_I_HAS_FIRE) == 0)
    {
	notify_fail("Now if only the " + obs[0]->short() + " was on fire...\n");
	return 0;
    }


    write("You melt the block of ice with the " + obs[0]->short() + ".\n");
    say(QCTNAME(tp) + " melts the block of ice with " + tp->query_possessive()
      + obs[0]->short() + ".\n");

    clone_object(STAND_MONSTER + "tower_gargoyle")->move(environment());

    tell_room(environment(),
	"Freed from the ice, the hideous shaped creature inside awakens.\n"
      + "It shakes it head and peers quizzically around with its piercing eyes.\n"
      + "The creature sees you and starts to growl horribly at you.\n");

    remove_object();
    return 1;    
}
