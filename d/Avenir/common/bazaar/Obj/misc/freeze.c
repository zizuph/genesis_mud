/*
 * Clone and move this object to a player if you want to make the
 * player to be locked for a while.
 *
 * Made by Mortricia for Avenir Dec. 1994 using Nick's /std/paralyze.c
 * Revisions: Manat, 16 Sept 2000 : add a leave_end that removes the prop.
 */

inherit "/std/paralyze";

#include <macros.h>
#include <stdproperties.h>

/* Some commands may always be issued. */
#define ALLOWED ({ "bug", "commune", "help", "idea", "praise", "quit", \
    "reply", "sysbug", "typo", "groan", "scream", "cry", "look"})
#define SUBLOC        "_freeze_obj_subloc"
#define STD_TIME      90               /* Default duration */

/*
 * Variables
 */
int    fastened;      /* Indicates fastned in stockade           */

/*
 * Prototypes
 */
void set_fastened(object i);

/*
 * Function name: create_object
 * Description:   The standard create routine.
 */
void
create_paralyze() 
{
    set_name("_baz_pillory_freeze");
    set_stop_verb("");
    set_stop_object(0);
    set_stop_message("You can move again.\n");
    set_fail_message("You are bound and gagged. You cannot do that right now.\n");
    set_remove_time(STD_TIME);
}

void set_fastened(int i) { fastened = i; }

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    
    if (to && living(to)) {
        to->add_subloc(SUBLOC, this_object());
	to->add_prop(OBJ_M_NO_ATTACK, "A guard blocks the way!\n");
    }
}

public void
leave_env(object inv, object to)
{
    ::leave_env(inv, to);

    inv->remove_prop(OBJ_M_NO_ATTACK);
}

public string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";
        
    if (for_obj == carrier) {
        if (fastened)
            str = "You are gagged and locked in the pillory.\n";
        else
            str = "You are gagged and held by a guard.\n";
    } else {
        if (fastened) 
            str = capitalize(carrier->query_pronoun()) +
                  " is gagged and locked in the pillory.\n";
        else
            str = capitalize(carrier->query_pronoun()) +
                  " is gagged and held by a guard.\n";
    }
    
    return str;
}
