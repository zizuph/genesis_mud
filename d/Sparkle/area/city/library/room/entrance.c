/*
 * /w/petros/sparkle/library/room/entrance.c
 *
 * Main Entrance for the Genesis Library
 *
 * Created by Petros, March 2008
 */

#pragma strict_types

// Includes
#include <macros.h>
#include <files.h>
#include <stdproperties.h>
#include "defs.h"

// Defines

// Inheritance
inherit LIBRARY_ROOM_BASE;
inherit "/d/Sparkle/area/city/lib/utility_functions";

// Global Variables

// Prototypes
public void             create_library_room();
public void             init();
public void             reset_room();
public string           sparkle_short();
public varargs string   sparkle_long();


/*
 * Function name:        do_drink
 * Description  :        let players drink from the fountain
 * Arguments    :        string str - what the player typed
 * Returns      :        1 - success,
 *                       0 - failure
 */
public int
do_drink(string str)
{
    int     i;

    if (!strlen(str))
    {
        notify_fail("Drink what?\n");
        return 0;
    }

    if (!parse_command(str, ({ }),
        "[from] [the] 'water' / 'fountain' / 'basin' [from] [the]"
      + " [basin] [of] [the] [fountain]"))
    {
        notify_fail("What do you wish to drink from where?\n");
        return 0;
    }

    /* Drink small amounts up to 500 soft */ 
    for (i = 0; i < 10; i++)
    {
        if (!this_player()->drink_soft(50))
        {
            /* Can't drink any more */
            break;
        }
    }

    if (i == 0)
    {
        write("You are too full to drink any water.\n");
        return 1;
    }

    if (!this_player()->drink_soft(50, 1))
    {
        write("People nearby peer curiously at you as you dip your hand"
             + " in the fountain and draw the water to your mouth. Though"
             + " cold and refreshing, it has an odd and somewhat"
             + " unpleasant taste. You seem to have drunk your fill.\n");
    }
    else
    {
        write("People nearby peer curiously at you as you dip your hand"
             + " in the fountain and draw the water to your mouth. Though"
             + " cold and refreshing, it has an odd and somewhat"
             + " unpleasant taste. You feel refreshed.\n");
    }

    say(QCTNAME(this_player()) + " drinks some water from the"
        + " fountain.\n");

    return 1;
} /* do_drink */

/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!IS_PLAYER_OBJECT(ob))
    {
        return;
    }
    
    object outside_room = safely_load_master_file(STREET_DIR + "center_f");
    if (outside_room != from)
    {
        // We only log if the player came from the outside.
        return;
    }
    
    send_debug_message("library_entry", "\n\n\t"
      + capitalize(this_player()->query_real_name()) + " enters the"
      + " Library!\n\n");
}

/*
 * Function name:        init
 * Description  :        add some actions for the player
 */
public void
init()
{
    ::init();

    add_action(do_drink, "drink");
} /* init */

/* 
 * Function name:       create_room
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_library_room()
{
    // Room Item Section                              
    try_item( ({ "archway", "marble archway", "entryway", 
                  "beautifully crafted archway" }),
                  "Carved into the sides of the archway are intricately "
                + "detailed reliefs. The emblem of the Sparkle Library "
                + "sits where one would expect the keystone of an archway "
                + "to be.\n");

    try_item( ({ "emblem of the sparkle library", "emblem" }),
                "You can see the emblem emblazoned prominently on the "
              + "sides of the archway. The detailed reliefs are a "
              + "pleasure to take in.\n");
              
    try_item( ({ "reliefs", "relief", "detailed reliefs",
                  "detailed relief", "intricately detailed reliefs",
                  "intricately detailed relief",
                  "carving", "carvings", "sides", "side",
                  "history" }),
                  "The reliefs depict the storied history of the city of "
                + "Sparkle, from its time as a small town, to becoming "
                + "the city that it is today.\n");

    try_item( ({ "fountain", "flowing fountain", "middle of the foyer",
                "middle" }),
                 "The fountain gushes with crystal clear water from its "
               + "spout at the very top. The light from the open dome "
               + "above shines down upon it, often creating a spectrum of "
               + "various colors as you gaze upon it.\n");
    
    try_item( ({ "dome", "open dome", "ceiling", "light" }),
                "What you see above you is not the typical ceiling, but "
              + "rather an open dome that allows the sunlight to grace "
              + "the foyer in which you stand.\n");
    
    try_item( ({ "water", "crystal water", "crystal clear water",
                "clear water", "spout", "top of the fountain",
                "various colors", "colors", "reflective colors" }),
                "Water flows smoothly from the top of the fountain. It "
              + "looks quite refreshing as well as being dauntingly "
              + "beautiful with the various reflective colors.\n");
    
    try_item( ({ "foyer" }),
                "You are standing in the foyer, which serves as the "
              + "entrance to the Sparkle library.\n");
    
    try_item( ({ "north", "street", "exit" }),
                "To the north you hear the sounds of the street. It "
              + "appears to be the exit out of the Library.\n");
    
    try_item( ({ "south", "books", "heart of the library" }),
                "To the south you see the heart of the Genesis library, "
              + "overflowing with an abundance of books. You can only "
              + "wonder at the vast knowledge this grand building "
              + "contains.\n");
              
    try_item( ({ "building", "grand building" }),
                "You stand in the grand building known in these parts "
              + "as the Sparkle Library. It was one of the first buildings "
              + "to be built when Sparkle was transformed from being a "
              + "rather small town to a grand city.\n");
            
    try_item( ({ "statues", "statue", "meticulously carved statues",
            "carved statues", "carved statue", "meticulously carved statue",
        "sides", "standing statues" }),
            "Artisans have crafted wonderful statues that stand at the "
          + "sides of the foyer. They all seem to represent prominent "
          + "officials throughout Sparkle's history.\n");
              
    // Properties Section
    add_prop(ROOM_I_INSIDE, 1);
    
    // Exits Section
    add_exit(STREET_DIR + "center_f", "north", 0);    
    add_exit(LIBRARY_ROOM_DIR + "circulation", "south", 0);    
} // create_room

/*
 * Function name:        reset_room
 * Description  :        Override the standard reset_room to bring in
 *                       objects that should be here.
 * Arguments    :        none
 * Returns      :        nothing
 */
public void
reset_room()
{
} // reset_room

/*
 * Function name:        sparkle_short
 * Description  :        provide a short description for locations
 *                       in the City of Sparkle
 * Deturns      :        string -- the short description
 */
public string
sparkle_short()
{
    return "Genesis Library entrance foyer";
} // sparkle_short


/*
 * function name:        sparkle_long
 * description  :        provides a long descriptions for locations
 *                       in the city of Sparkle
 * returns      :        the room description
 */
public varargs string
sparkle_long()
{
    return "A beautifully crafted marble archway lies as an entryway to "
           + "the guardian of knowledge known as the Genesis Library from "
           + "the outside world. The Genesis Library is one of the prides "
           + "of Sparkle. For though Sparkle came from humble roots, this "
           + "Library is anything but humble. The flowing fountain in the "
           + "middle of the foyer, the meticulously carved statues "
           + "standing to the sides, the light shining down through the "
           + "open dome above all testify to the grandeur and grace that "
           + "Sparkle has grown into over the years. To the north you "
           + "hear the sounds of the street. To the south you see an "
           + "overflowing abundance of books which you know to be the "
           + "heart of the Genesis Library."
           + "\n\n";
} // sparkle_long
