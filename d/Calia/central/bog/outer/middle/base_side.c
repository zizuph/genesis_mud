// ROOM:  base_side.c

    /*  Calia Domain

    HISTORY

    [99-06-09] created by Uhclem from
    [D:\CALIA\CENTRAL\BOG\OUTER\MIDDLE\BASE_SID.DOC].

    PURPOSE

    This is the base for rooms reached by climbing the wall of the Sanctimonian
    fortress, middle level.  Climbing is only possible on the flat sides, not
    on the corners, so no corner rooms are defined at this level.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/bog/baseroom";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include "defs.h"

#define DROPPED_OBJECTS "_dropped_objects"

// GLOBAL VARIABLES

string This_Location;

// FUNCTIONS

// Function:  sorry_pal()

/*

Purpose:  Tell the player he can't do whatever he just tried to do while
hanging on the wall if it isn't on the wall-approved list.  This function is
based on the function of the same name in the central forest pit baseroom.

Arguments:  none.

Returns:  0/1.

*/

int
sorry_pal()

    {

    object tp = this_player();

    if (member_array(query_verb(), query_prop("_wall_" + tp->query_name())) !=
        -1)

        {

        return 0;

        }

    write("You can't do that while you're concentrating all" +
        " your energies on clinging to the wall!\n");

    return 1;

    }

// Function:  init()

/*

Purpose:  add local commands. In actuality, it adds a property containing the
list of verbs a player can use while on the wall. The property is a big array,
so it's added to room, not the player! Basically, the player can use standard
Genesis commands; nothing from guild or other cmdsouls or from objects (other
than Calian central objects) is allowed. However, commands that mask standard
commands, like specialized "say" or "team" functions are not blocked.

Arguments:  none.

Returns: nothing.

*/

void
init()

    {

    object tp = this_player();
    mixed *command_list;
    mixed *details;
    string *soul_list;
    string *verb_list;
    string defined_by;
    string *dont_override = ({});
    int m;
    int n;

    ::init();

    if (tp->query_wiz_level()) return;  /* Don't block wizards. */

    command_list = commands(tp);
    m = sizeof(command_list);

    for (n=0; n<m; n+=1)

        {

        details = command_list[n];
        defined_by = file_name(details[2]);

        if (wildmatch("/d/Genesis*", defined_by)
            || wildmatch("/cmd/live*", defined_by)
            || wildmatch("/std*", defined_by)
            || wildmatch("/d/Calia/central*", defined_by))

            {

            dont_override += ({details[0]});

            }

        }

    soul_list = tp->query_cmdsoul_list();
    m = sizeof(soul_list);

    for (n=0; n<m; n+=1)

        {

        verb_list = m_indices(find_object(soul_list[n])->query_cmdlist());

        if (wildmatch("/d/Genesis*", soul_list[n])
            || wildmatch("/cmd/live*", soul_list[n])
            || wildmatch("/std*", soul_list[n]))

            {

            dont_override += verb_list;

            }

        }

    add_prop("_wall_" + tp->query_name(), dont_override);

    add_action(sorry_pal, "", 1);

    }

// Function:  burden_check()

/*

Purpose:  Make sure the player isn't violating the climbing rule, which might
happen if he is handed something by another player at this level or receives a
pigeon.

Arguments:  none.

Returns:  0/1.

*/

int
burden_check()

    {

    object tp = this_player();

    /*  You may wish to compare the climb and burden checks in the central
        forest.  There the key rule is that you cannot climb if your burden
        exceeds your climb skill, but the wall of the fortress is twice as easy
        to climb as a straight tree trunk.  */

    if ((tp->query_encumberance_weight() * 2) > tp->query_skill(SS_CLIMB))

        {

        write ("You are too heavily burdened to climb up.\n");
        return 1;

        }

    return 0;

    }

// Function:  drop_object()

/*

Purpose:  Make a dropped object fall; this function is called after a very
short delay when an object is dropped in the room.

Arguments:  none.

Returns:  nothing.

*/

void
drop_object()

    {

    object *loose_objects = query_prop(DROPPED_OBJECTS);

    string target_room = BOG_OUTER_GROUND + This_Location;

    if (!loose_objects) return;
    else loose_objects = FILTER_DEAD(loose_objects);

    while (sizeof(loose_objects))

        {

        /*  The following check is just to account for a nimble player who
            grabs an object after someone drops it but before it leaves the
            room. */

        if (environment(loose_objects[0]) == this_object())

            {

            loose_objects[0]->move(target_room);

            }

        loose_objects -= ({loose_objects[0]});

        }

    remove_prop(DROPPED_OBJECTS);

    }

// Function:  leave_inv()

/*

Purpose:  provide messages for non-living items falling to the ground.

Arguments:  object leaving the room, object destination.

Returns:  nothing.

*/

void
leave_inv(object ob, object dest)

    {

    ::leave_inv(ob, dest);

    if (!dest) return;  /* Covers updates and destructs by wizards. */
    if (file_name(dest) != BOG_OUTER_LOW + This_Location) return;

    if (living(ob))

        {

        remove_prop("_wall_" + ob->query_name());

        }

    else

        {

        if (ob->num_heap() > 1)

            {

            tell_room(this_object(),
                capitalize(LANG_THESHORT(ob)) + " fall to the ground.\n");

            tell_room(dest,
                capitalize(LANG_ASHORT(ob)) +
                " fall from the top of the fortress.\n");

            }

        else

            {

            tell_room(this_object(),
                capitalize(LANG_THESHORT(ob)) + " falls to the ground.\n");

            tell_room(dest,
                capitalize(LANG_ASHORT(ob)) +
                " falls from the top of the fortress.\n");

            }

        }

    }

// Function:  enter_inv(object, from_object)

/*

Purpose: cause non-living objects that enter this room to drop to ground level.

Arguments:  object entering the room, object from whence it came.

Returns:  nothing.

*/

void
enter_inv(object ob, object from)

    {

    object *loose_objects;

    ::enter_inv(ob, from);

    if (living(ob) && !ob->sanctimonian())

        {

        register_player(ob);

        }

    else if (!living(ob))

        {

        loose_objects = query_prop(DROPPED_OBJECTS);

        if (loose_objects)
            add_prop(DROPPED_OBJECTS, loose_objects + ({ob}));

        else add_prop(DROPPED_OBJECTS, ({ob}));

        set_alarm(0.2, 0.0, drop_object);

        }

    }

// Function:  create_wall(location, direction)

/*

Purpose:  Create the room description and add standard attributes.

Arguments:  string containing the filename of this room, string containing the
compass direction which the wall faces.  The same filename is assumed to be
used in other directories for rooms directly below or above this one.

Returns:  nothing.

SPECIAL NOTE:  the only possible exits from this room are up and down.  They
are added by the create_wall function, so no add_exit statements should appear
in the individual room files.

*/

void
create_wall(string location, string direction)

    {

    This_Location = location;

    set_short("On the " + direction + " side of a log fortress");

    set_long("You are hanging onto the " + direction +
        " side of a great log fortress, only a short" +
        " distance from the top.\n");

    add_item(({"side", "sides"}),
        "The sides of the fortress are constructed of" +
        " immense logs, tightly stacked and" +
        " securely joined together. You have an excellent view" +
        " of them from where you're hanging.\n");

    add_item(({"log", "logs"}),
        "The logs at this level have surfaces of rough, dry bark" +
        " that give you a good grip. The one you're hanging" +
        " onto looks like the trunk of a " +
        ({"cedar", "pine", "fir", "spruce"})[random(4)] +
        " tree.\n");

    add_item(({"fortress", "log fortress", "great log fortress"}),
        "You can't see much more than the logs directly in" +
        " front of you.\n");

    add_item("top",
        "The wall obscures your view; you can see only the" +
        " logs and the sky.\n");

    add_item(({"sky", "view"}),
        "It's such a lovely day. Wouldn't you rather be" +
        " playing fireball than climbing this wall?\n");

    add_exit(BOG_OUTER_UPPER + This_Location, "up", "@@climb_check@@", 5);
    add_exit(BOG_OUTER_LOW + This_Location, "down", 0, 0);

    /*  The following exit is a dummy to allow shouts from the top of the wall
        to be heard at all levels of the fortress exterior. */

    add_exit(BOG_OUTER_GROUND + This_Location, "d", 1, 1, 1);

    add_prop(ROOM_I_HIDE, -1);  /*  Impossible to hide. */
    add_prop(ROOM_I_LIGHT, 2);  /*  Partial shade. */

    /*  "uid" settings required for cloning objects.  */

    setuid();
    seteuid(getuid());

    /*  SPECIAL FUNCTION  */

    /*  Tell the Sanctimonian central control room that this room has been
        loaded.  Function is found in /d/Calia/central/bog/baseroom.c.  */

    register_room();

    }
