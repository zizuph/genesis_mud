/*
 * This is a modification of the CORPSE_OBJECT to support
 * the petrification spell used by the wand 
 * /d/Krynn/throtyl/obj/petrified_stick.c
 *
 * Arman - November 2020
 */

#pragma save_binary
#pragma strict_types

#include <composite.h>
#include <files.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>

inherit CORPSE_OBJECT;

#define DECAY_LIMIT      3    /* times DECAY_UNIT == minutes */

int crumbling;

varargs public mixed
query_leftover(string organ)
{
    // No leftovers
    return ({ });
}

void 
set_name(string n)
{
    ::set_name(n);
    add_name("statue");
    add_name("statue of " + met_name);
    add_name("remains");
    add_name("remains of " + met_name);

    if (nonmet_name)
    {
        add_name("statue of " + nonmet_name);
        add_name("remains of " + nonmet_name);
    }
}

/*
 * Function name: short_func
 * Description  : Returns the short description of this object, based on
 *                recognition of the corpse.
 * Returns      : string - the short description.
 */
string
short_func()
{
    object pob;
    string state_d;

    if(crumbling)
        state_d = "crumbled stony remains of ";
    else
        state_d = "petrified statue of ";

    pob = vbfc_caller();
    if (!pob || !query_interactive(pob) || pob == this_object())
        pob = previous_object(-1);

    if (!pob || !query_interactive(pob))
        pob = this_player();

    if (pob && pob->query_real_name() == lower_case(met_name))
        return state_d + "yourself";

    else if (pob && pob->query_met(met_name))
        return state_d + capitalize(met_name);
    else
        return state_d + LANG_ADDART(nonmet_name);

}

/*
 * Function name: pshort_func
 * Description  : Returns the plural short description of this object, based on
 *                recognition of the corpse.
 * Returns      : string - the plural short description.
 */

string
pshort_func()
{
    object pob;
    pob = vbfc_caller();
    string pstate_d;

    if(crumbling)
        pstate_d = "crumbled stony remains of ";
    else
        pstate_d = "petrified statues of ";

    if (!pob || !query_interactive(pob) || pob == this_object())
        pob = previous_object(-1);

    if (!pob || !query_interactive(pob))
        pob = this_player();

    if (pob && pob->query_real_name() == lower_case(met_name))
        return pstate_d + "yourself";

    else if (pob && pob->query_met(met_name))
        return pstate_d + capitalize(met_name);
    else
        return pstate_d + LANG_PWORD(nonmet_name);
}

/*
 * Function name: long_func
 * Description  : Returns the long description of this object, based on
 *                recognition of the corpse.
 * Returns      : string - the long description.
 */

string
long_func()
{
    object pob = vbfc_caller();
    string cause;
    string long_d;

    if(crumbling)
        long_d = "This is the crumbled stony remains of ";
    else
        long_d = "This is the petrified body of ";

    if (!pob || !query_interactive(pob) || pob == this_object())
        pob = this_player();

    /* Attach cause of death (or rather, cause of most damage). */
    cause = (strlen(cause1) ? (". " + cause1) : ".") + "\n";

    cause = ", frozen by earth magics in death as a statue.\n";

    if (pob->query_real_name() == lower_case(met_name))
        return "This is your own dead body" + cause;

    if (pob->query_met(met_name))
        return long_d + capitalize(met_name) + cause;
    else
        return long_d +LANG_ADDART(nonmet_name) + cause;
}

/*
 * Function name: decay_fun
 * Description  : First stage of decay. Decay to a heap of remains, and move
 *                all inventory into the room. Then set the alarm for the
 *                second stage.
 */
void
decay_fun()
{
    object *ob;
    string desc;
    int i;
    ob = filter(all_inventory(this_object()), move_out);

    /* fix this to get singular/plural of 'appear' */
    i = ((sizeof(ob) != 1) ? sizeof(ob) :
         ((ob[0]->query_prop(HEAP_I_IS)) ? (int)ob[0]->num_heap() : 1));

    if (strlen(desc = COMPOSITE_DEAD(ob)))
    {
        tell_room(environment(this_object()),
            "As the " + QSHORT(this_object()) + " crumbles, " +
            desc + " appear" +
            ((i == 1 || desc == "something" || desc == "nothing") ? "s" : "") +
            " from it.\n");
    }
    crumbling = 1;

    add_name("crumbled stony remains");
    add_name("stony remains");
    /* Set the short decay limit so it will remove itself. */
    set_decay(DECAY_LIMIT);
}

