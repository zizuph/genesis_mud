/*
 * /d/Gondor/private/events/obj/event_command.c
 *
 * Created by Mercade on October 5, 2000.
 *
 * This little object will add the command "event" to a player that carries
 * the item. With it, he or she may leave their comments on the event they 
 * have participated in.
 */

inherit "/std/object";

#include <files.h>
#include <macros.h>
#include <stdproperties.h>
#include "../events.h"

#define OBJECT_NAME "event_command"

/*
 * Function name: create_object
 * Description  : Constructor.
 */
void
create_object()
{
    set_name(OBJECT_NAME);

    set_long("This object defines the command \"event\".\n");
 
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_TELEPORT, 1);
    add_prop(OBJ_S_WIZINFO, "This object defines the command \"event\" for " +
        "use in the Gondorian event system.\n");

    set_no_show();

    setuid();
    seteuid(getuid());
}

/*
 * Function name: event_edited
 * Description  : This routine is called when the player is done editing.
 * Arguments    : string str - the text the player entered.
 */
void
event_edited(string str)
{
    string name;

    if (!strlen(str))
    {
        write("No thoughts or comments were entered at this time.\n");
        return;
    }

    name = capitalize(this_player()->query_real_name());
    write_file(COMMENTLOG, file_name(environment(this_player())) +
         "\n" + ctime(time()) + " by " + name + "\n" + str + "\n");
    write("\nThank you for sharing your thoughts and comments, " + name +
         ".\n   The team of Gondor.\n");
}

/*
 * Function name: event
 * Description  : The "event" command. It will display the editor to the
 *                player.
 * Arguments    : string str - the command line arugment.
 * Returns      : int 1/0 - success/failure (in this case, always success).
 */
int
event(string str)
{
    write(capitalize(this_player()->query_real_name()) + ", please share " +
        "with us your thoughts and comments about the event(s) that " +
        "you have recently participated in. They will help us improve the " +
        "realms.\n\n");

    clone_object(EDITOR_OBJECT)->edit(event_edited, str);
    return 1;
}

/*
 * Function name: init
 * Description  : Links the command "event" to a player.
 */
void
init()
{
    ::init();

    add_action(event, "event");
}

/*
 * Function name: enter_env
 * Description  : Called when this object enters another object. We do not
 *                want multiple event-command-objects in the same player.
 * Arguments    : object to - the object we enter.
 *                object from - the object we left.
 */
void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (objectp(to))
    {
        /* We do not want to be on the ground. */
        if (!living(to))
        {
            set_alarm(0.5, 0.0, remove_object);
        }

        /* Protect against identical objects in the inventory of a player. */
        if (sizeof(filter(all_inventory(to), &->id(OBJECT_NAME)) - ({ this_object() })))
        {
            set_alarm(0.5, 0.0, remove_object);
        }
    }
}
