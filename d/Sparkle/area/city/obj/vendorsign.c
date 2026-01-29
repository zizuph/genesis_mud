/*
 *  /d/Sparkle/area/city/obj/vendorsign.c
 *
 *  This is a sign that is placed on the docks of Sparkle by the
 *  Market Vendors who arrive each Wednesday. They will place this
 *  sign out the day before the event, and then pick it up again
 *  once the Market begins its day of operation.
 *
 *  Created March 2008, by Gorboth (Cooper Sherry)
 */
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <time.h>

#include "../defs.h"


/* Prototypes */
public void          create_object();
public void          init();
public int           read_poster(string arg);
public void          goodbye();



/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("display");

    add_name( ({ "poster", VENDORSIGN }) );
    set_adj( ({ "large", "colorful", "colourful" }) );

    set_short("large colorful poster");
    set_long("A large colorful poster has been placed here. It reads:\n\n"
      + "\t .--------------------------------------------------------.\n"
      + "\t|                                                          |\n"
      + "\t|     REMINDER! BE SURE TO COME TO TOWN TOMORROW           |\n"
      + "\t|  TO DEAL WITH THE VENDORS AT THE WEDNESDAY MARKET!       |\n"
      + "\t|                                                          |\n"
      + "\t `------------------------------------------------------- '\n\n");

    add_prop(OBJ_M_NO_GET, "Best to just leave that where it is.\n");
    add_prop(OBJ_I_WEIGHT, 100 + random(100));
    add_prop(OBJ_I_VOLUME, 100 + random(100));
} /* create_object */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(read_poster, "read");
} /* init */


/*
 * Function name:        read_poster
 * Description  :        allow players to read the poster
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        1 - success, 0 - failure
 */
public int
read_poster(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Read what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [a] [large] [colorful] [colourful] 'poster'"))
    {
        notify_fail("Do you want to read the poster?\n");
        return 0;
    }

    write(long());
    return 1;
} /* read_poster */


/*
 * Function name:        goodbye
 * Description  :        Once the day before the Market ends (a real life
 *                       day, determined in the defs.h file) the vendors
 *                       clean up this sign.
 */
public void
goodbye()
{
    tell_room(environment(this_object()),
        "A travel-worn man in a dusty robe arrives, removes the poster,"
      + " and departs again.\n");

    remove_object();
} /* goodbye */