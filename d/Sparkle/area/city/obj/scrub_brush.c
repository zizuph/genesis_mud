/*
 *  /d/Sparkle/area/city/obj/scrub_brush.c
 *
 *  This object is given out by Carlsan Fountaine, the Town Crier
 *  as part of the Dock Tour in Sparkle.
 *
 *  Using it, players may <scrub> Genesis ShipLines signs to
 *  Quest.
 *
 *  Note: If new docks are added to Sparkle, they can be incorporated
 *        into this quest by adding the room filename (e.g. "pier1") to
 *        the global variable SRooms.
 *
 *  Created April 2011, by Cooper Sherry (Gorboth)
 */

#pragma strict_types

inherit "/std/object";

#include <filepath.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"


/* This mapping tells us the rooms in which a signs can be found. */
public string  *SRooms   = ({ 
                             "newbie-pier_1",
                             "newbie-pier_2",
                             "newbie-pier_3",
                             "newbie-pier_4",
                             "pier1",
                             "pier2",
                             "pier3",
                             "pier4",
                             "pier5",
                             "pier6",
                             "pier7",
                             "pier8",
                             "parrot",
                             "pier11",
                             "pier12",
                             "pier14",
                             "pier15",
                             "pier16"
                          });

public string  *query_rooms() { return SRooms; }

/* Prototypes */
public void     create_object();
public void     init();
public int      finished_task(object who);
public int      do_scrub(string arg);
public void     check_finished_msg(object who);



/*
 * Function name:        create_object
 * Description  :        The constructor
 */
public void
create_object()
{
    set_name("brush");
    add_name( ({ SCRUB_BRUSH, "scrub-brush", "tool" }) );
    add_adj( ({ "sturdy", "scrub" }) );

    set_short("sturdy scrub-brush");
    set_long("This is the brush the town crier gave you to use to clean"
      + " any scum that has built up on the Genesis ShipLines signs that"
      + " are placed along the piers in Sparkle. You were tasked to"
      + " <read> each sign and then <scrub> off any scum that you happen"
      + " to notice. When you are finished you are"
      + " to return to him and <show> him the brush.\n");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL, "That would not be a good idea.\n");
    add_prop(OBJ_M_NO_DROP, "You'd better hang on to that. If you have"
      + " finished your task, you can <show> it to Carlsan.\n");
    add_prop(OBJ_I_VOLUME, 2);
    add_prop(OBJ_I_WEIGHT, 1);
    
    setuid();
    seteuid(getuid());
} /* create_object */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_scrub, "scrub");
    add_action(do_scrub, "clean");
} /* init */


/*
 * Function name:        finished_task
 * Description  :        See if the player has completed the task
 * Arguments    :        object who - the player to check for
 * Returns      :        int 1 - completed
 *                       int 0 - not yet completed
 */
public int
finished_task(object who)
{
    int     finished = 1;
    string *rooms_scrubbed = this_player()->query_prop(DOCK_TOUR_PROP);

    foreach(string this_room : SRooms)
    {
        if (!IN_ARRAY(this_room, rooms_scrubbed))
        {
            finished = 0;
        }
    }

    return finished;
} /* finished_task */


/*
 * Function name:        do_scrub
 * Description  :        Allow players to scrub a sign if it is dirty
 *                       and they are in the correct room.
 * Arguments    :        string arg - what the player typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_scrub(string arg)
{
    object  sign = present(SHIPLINE_SIGN, environment(this_player()));
    string  room = FILE_NAME(file_name(environment(this_player())));
    string *rooms_scrubbed = this_player()->query_prop(DOCK_TOUR_PROP);

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [scum] [off] [of] [the] [genesis] [ship] [lines]"
      + " [shiplines] 'sign' [with]"
      + " [the] [sturdy] [scrub] [scrub-brush] [brush]"))
    {
        notify_fail("Are you trying to <scrub> a sign,"
          + " perhaps?\n");
        return 0;
    }

    if (!sign)
    {
        write("You would need to locate one of the Genesis ShipLine"
          + " signs first. There doesn't seem to be one in this"
          + " location.\n");
        return 1;
    }

    if (IN_ARRAY(room, rooms_scrubbed))
    {
        write("You've already cleaned this sign quite thoroughly. It"
          + " looks as good as new!\n");
        return 1;
    }

    if (!sizeof(rooms_scrubbed))
    {
        rooms_scrubbed = ({ "" });
    }

    this_player()->reveal_me(1);
    write("You take your scrub-brush and give the sign a very thorough"
      + " cleaning. As the minutes pass, you notice less and less"
      + " scum on the sign, until eventually you stop, satisfied with"
      + " your work.\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
      + " spends a few moments cleaning the sign with a sturdy"
      + " scrub-brush.\n", this_player());

    rooms_scrubbed += ({ room });
    this_player()->add_prop(DOCK_TOUR_PROP, rooms_scrubbed);

    set_alarm(1.0, 0.0, &check_finished_msg(this_player()));

    return 1;
} /* do_scrub */



/*
 * Function name:        check_finished_msg
 * Description  :        If the player has finished rating their form,
 *                       we print a special message.
 * Arguments    :        object who - the player
 */
public void
check_finished_msg(object who)
{
    if (finished_task(who))
    {
        who->catch_msg("\nIt looks as if you have finished scrubbing all of"
          + " the signs. You can now return to Carlsan and <show>"
          + " him the brush.\n");
    }

    return;
} /* check_finished_msg */
