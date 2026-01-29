#pragma strict_types

#include <stdproperties.h>

// #include "../defs.h"
#include <macros.h>
#include "/d/Sparkle/area/city/defs.h"
#include "/d/Genesis/gsl_ships/ships.h"
#define  TOWN_DIR   ("/d/Genesis/start/human/town/")
inherit STDPIER;

/* Prototypes */
public int         check_exit();

/* Definitions */
#define            MERCS_CLOSED               0

void
create_room()
{
    set_short("Berth 6 - Newports");
    set_long("\n"+
        "This is the south pier.\n"
      + "A large warehouse lies due south and the harbour is due north."
      + " Sea birds are flying overhead, swooping down to get the goodies"
      + " left in the water by the fishermen. The pier continues east."
      + " A road leads south between some warehouses before passing out"
      + " of Sparkle through the City Gates.\n"
      + "There is a sign here that reads: Berth 6 - Newports.\n");

    add_item( ({ "road" }),
        "The road heads through the southern parts of the city,"
      + " eventually passing through the city gates in the distance.\n");
    add_item( ({ "gate", "gates", "city gates" }),
        "The city gates are a ways off to the south.\n");
    add_item( ({ "southern parts of the city" }),
        "South of here, Sparkle spreads out for a distance before ending"
      + " before the city walls.\n");
    add_item( ({ "wall", "walls", "city walls", "walls of the city",
                 "wall of the city" }),
        "They are far to the south. You can't see much from here.\n");
    add_item(({"water" }),
                "Pieces of fish and other leftovers from the fishermen's\n"+
                "boats are floating in the water. It makes it less inviting\n"+
                "to swim around in, unless you're a seagull.\n"+
                "");
    add_item(({"birds","bird","seagull","seagulls" }),
                "The seagulls are quite busy trying to get the best"
              + " pieces of fish"
              + " and their shrieks are quite deafening.\n"+
                "");
        add_item(({"sign" }), "Berth 6 - Newports");
    add_item(({"warehouses" }), "They look very large.\n");
    add_item(({"pier" }), "Nothing seems to be out of the ordinary.\n");

    add_exit(TOWN_DIR + "pier5","west");
    add_exit(TOWN_DIR + "pier7","east");
    add_exit("/d/Sparkle/guilds/new_merc/rooms/south_of_sparkle",
             "south", check_exit, 1, 0);

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");
    add_pier_entry(MASTER_OB(TO), "Sparkle", "Pier to Newports");
    initialize_pier();
}


/*
 * Function name:        check_exit
 * Description  :        Send the players a message when they leave
 *                       town.
 * Returns      :        int 1 - prevent exit
 *                           0 - allow exit
 */
public int
check_exit()
{
    /* The Merc guild is finished with beta. We'll leave the code in case
     * we need it later, but comment it out for now. (Gorboth)
    string  *allowed_persons = ({ "amberlee",
                                  "madmartigan",
                                  "azalin",
                                  "gorbyjr",
                                  "porter",
                                  "gorbothjr"
                               });

    if (member_array(this_player()->query_real_name(),
        allowed_persons) == -1)
    {
        if (this_player()->query_wiz_level())
        {
            write("WIZ-INFO: Only beta testers for the Mercenary Guild are"
              + " currently allowed to use this exit. Wizards, of course"
              + " go where they please.\n");
        }
        else
        {
            write("A few city officials halt you as you try to leave the"
              + " city. They apologize and inform you that only Morgan and"
              + " a few of her select personnel are permitted to travel"
              + " to the old logging compound south of town.\n");
            say(QCTNAME(this_player()) + " is halted by some city"
              + " officials as " + this_player()->query_pronoun()
              + " attempts to travel south.\n");

            return 1;
        }
    }
     */

    if (MERCS_CLOSED)
    {
        write("A few city officials halt you as you try to leave and"
          + " explain that the way is not open yet.\n");
        return 1;
    }

    if (this_player()->query_wiz_level() && MERCS_CLOSED)
    {
        write("WIZ-INFO: Only beta testers for the Mercenary Guild are"
          + " currently allowed to use this exit. Wizards, of course"
          + " go where they please.\n");
    }

    write("\nYou pass beyond a number of buildings, eventually passing"
      + " through the city gates and out of town.\n\n");

    return 0;
} /* check_exit */
