/*
 *  /d/Sparkle/area/city/obj/feather_duster.c
 *
 *  This object is given out by Carlsan Fountaine, the Town Crier
 *  as part of the Orbs Tour in Sparkle.
 *
 *  Using it, players may <dust> Genesis ShipLines orbs to
 *  Quest.
 *
 *  Note: If new domains are added to Genesis, their orbs can be
 *        incorporated into this quest by adding the file path for the
 *        domain office from the tower of realms to the global variable
 *        SRooms.
 *
 *  Also: Liwitch does NOT count! We don't tempt fate.
 *
 *  Created June 2011, by Cooper Sherry (Gorboth)
 */

#pragma strict_types

inherit "/std/object";

#include <filepath.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"


/* This mapping tells us the rooms in which a orbs can be found. */
public string  *SRooms   = ({ 
                             "/d/Genesis/start/human/town/tower",
                             "/d/Ansalon/common/domain_office",
                             "/d/Gondor/domain_office",
                             "/d/Krynn/common/domain_office",
                             "/d/Terel/domain_office",
                             "/d/Shire/common/domain_office",
                             "/d/Avenir/common/domain_office",
                             "/d/Earthsea/open/domain_office",
                             "/d/Raumdor/open/projects/office",
                             "/d/Kalad/projects/tower_office",
                             "/d/Emerald/open/tower",
                             "/d/Cirath/open/projects/ctower",
                             "/d/Khalakhor/open/project/office",
                             "/d/Calia/domain_office",
                             "/d/Faerun/common/domain_office",
                          });

public string  *query_rooms() { return SRooms; }

/* Prototypes */
public void     create_object();
public void     init();
public int      finished_task(object who);
public int      do_dust(string arg);
public void     check_finished_msg(object who);



/*
 * Function name:        create_object
 * Description  :        The constructor
 */
public void
create_object()
{
    set_name("duster");
    add_name( ({ FEATHER_DUSTER, "tool" }) );
    add_adj( ({ "feather" }) );

    set_short("feather duster");
    set_long("This is the duster the town crier gave you to help him"
      + " with the task of keeping the orbs in the Tower of Realms free"
      + " of dust. You were tasked to visit each room of the tower,"
      + " find any orbs and then <dust> them off. When you are finished"
      + " you are to return to him and <show> him the duster.\n");

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

    add_action(do_dust, "dust");
    add_action(do_dust, "clean");
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
    string *rooms_dusted = this_player()->query_prop(ORBS_TOUR_PROP);

    foreach(string this_room : SRooms)
    {
        if (!IN_ARRAY(this_room, rooms_dusted))
        {
            finished = 0;
        }
    }

    return finished;
} /* finished_task */


/*
 * Function name:        do_dust
 * Description  :        Allow players to dust an orb if it is dirty
 *                       and they are in the correct room.
 * Arguments    :        string arg - what the player typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_dust(string arg)
{
    object  orb = present("_genesis_quest_orb", environment(this_player()));
    string  room = file_name(environment(this_player()));
    string *rooms_dusted = this_player()->query_prop(ORBS_TOUR_PROP);

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[off] [the] [quest] 'orb' [with]"
      + " [the] [feather] [duster]"))
    {
        notify_fail("Are you trying to <dust> an orb,"
          + " perhaps?\n");
        return 0;
    }

    if (room == "/d/Liwitch/common/player_domain_office")
    {
         write("No matter how much you dust the orb, it is immediately"
           + " covered again by a fresh coat. It seems this room is"
           + " just cursed or something! Perhaps the town crier knows"
           + " better than to even try up here. Perhaps you should just"
           + " forget it and move on ... I'm sure this room doesn't"
           + " count anyway.\n");
        return 1;
    }

    if (!orb)
    {
        write("You would need to locate one of the quest orbs located"
          + " in Tower of Realms first. There doesn't seem to be one"
          + " in this location.\n");
        return 1;
    }

    if (IN_ARRAY(room, rooms_dusted))
    {
        write("You've already cleaned this orb quite thoroughly. It"
          + " looks completely dust-free!\n");
        return 1;
    }

    if (!sizeof(rooms_dusted))
    {
        rooms_dusted = ({ "" });
    }

    this_player()->reveal_me(1);
    write("You take your feather duster and wiggle it all over the quest"
      + " orb. Dust flies everywhere and you eventually feel that the"
      + " job is complete in this room. You also notice that the orb"
      + " looks pretty important. Perhaps you could <exa orb> for a bit"
      + " more info on how to see which quests exist in the realm"
      + " represented by this room in the tower.\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
      + " spends a few moments cleaning the orb with a"
      + " feather duster.\n", this_player());

    rooms_dusted += ({ room });
    this_player()->add_prop(ORBS_TOUR_PROP, rooms_dusted);

    set_alarm(1.0, 0.0, &check_finished_msg(this_player()));

    return 1;
} /* do_dust */



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
        who->catch_msg("\nIt looks as if you have finished dusting all of"
          + " the orbs. You can now return to Carlsan and <show>"
          + " him the feather duster.\n");
    }

    return;
} /* check_finished_msg */
