/* Name      : /d/Gondor/harondor/room/camp/base_trail.c
 * Purpose   : The file handling the general descriptions
 *             for the trail and the callouts can be found
 *             last in the file.
 * Created by: Sir Toby, Gondor Domain, 2005-11-13
 *
 *   Modified: 2005-11-15, Sir Toby:
 *                         Added support to add pebbles to the trail
 *                         (varargs void add_pebbles(int palloc))
 *             2005-11-16, Sir Toby:
 *                         Added two functions for the secret trail
 *                         around the camp:
 *                          - int s_block()
 *                          - public void add_harad_secret_tells()
 *             2005-11-17, Sir Toby:
 *                         Begun the work on random open backdoor
 *                         to the camp. 
 *                         New functions:
 *                          - wind_block()
 *                          - query_wind_open()
 *                          - wind_block_set()
 *             2005-11-18, Sir Toby:
 *                         Functions query_wind_open() and
 *                         wind_block_set() moved to file:
 *                         /d/Gondor/harondor/room/camp/wind_check_open.c
 *             2005-11-21, Sir Toby
 *                         Changed the random exit code to the
 *                         wind_check_open.c file.
 *             2006-07-27, Sir Toby
 *                         Fixed the code in update_pebbles() and added
 *                         support in the hiddend trail rooms.
 *             May 4 2019, Finwe
 *                         Fixed some typos 
 *
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/harondor/room/camp/defs.h"
#include "/d/Gondor/std/tell.c"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <filter_funs.h>
#include "/d/Gondor/harondor/lib/harondor_herbs.h"

public void add_harad_trail_tells();

#define QUERY_WIND_OPEN (HAR_RM_DIR + "camp/wind_check_open.c")
#define I_PEBBLE_TIMESTAMP "i_harondor_pebble_timestamp_"
#define I_PEBBLE_EXIST "i_harondor_pebble_exist_"

#define DEBUG(x) find_player("toby")->catch_msg("[DEBUG - base_trail]: " + x + "\n")

void add_desert()
{
    add_item(({"wasteland", "desert", "arid land", "ground", "land", "area"}),
        "The land is barren and dry. Very little grows here among the " +
        "rocks and sand except for dried grass. It is brown and parched, " + 
        "and very hot.\n");
    add_item(({"grass", "dried grass", }),
        "It is short and thin, and dried out. The grass is little more " +
        "than stubble in this wasteland.\n");
    add_item(({"rocks"}),
        "They are fragments of large rocks. They are chipped and hard " +
        "looking, and lay scattered across the arid wasteland.\n");
    add_item(({"sand", "grit"}),
        "These are small, loose grains of disintegrated rocks. They are " +
        "dark colored, making the ground look a dark color.\n");
    add_item(({"mound", "mounds"}),
        "There is nothing special about the sand mounds, they vary in size " +
        "and can be seen all over the desert landscape.\n");
}

void add_road()
{
    add_item(({"road", "highway"}),
        "It is hard to make out any details of the road from here but " +
        "it runs generally north and south.\n");
}

void add_trail()
{
    add_item(({"trail", "small trail"}),
        "The small trail wind between the mounds of sand that forms " +
         "from the wind blowing. It runs generally to the east and west.\n");
}

void add_ephel_duath(string str)
{

    add_item(({"mountain", "mountains", "ephel duath", "peak",
        "peaks", "slope", "slopes"}), "The peaks of the Ephel Duath " +
        "loom ominously in the distance. They look jagged and evil, " +
        "rising to the " + str + ".\n");
}

/*   Adding pebbles to the track (if descided to) and hiding them at random.
     Might be part of a cleanup quest.
 */
varargs void update_pebbles()
{
    object pebble;
    int found_pebble, num_pebbles;
    int x;


    if(sizeof(FILTER_PLAYERS(all_inventory(this_object()))) > 0 )
       return;

    found_pebble = objectp(present("_harondor_pebble_chief_quest_part_I"));

    /* Following derived from: 
       (query_prop(I_PEBBLE_TIMESTAMP) < time()) || (query_prop(I_PEBBLE_EXIST) && !found_pebble)
     */

    if(query_prop(I_PEBBLE_TIMESTAMP) > time() && (!query_prop(I_PEBBLE_EXIST) || found_pebble))
       return;

    /* Removing pebbles if they do exist. */

    while(pebble = present("_harondor_pebble_chief_quest_part_I"))
       pebble->remove_object();

    /* Now, lets clone the new pebbles... */

    num_pebbles = random(4);

    for(x = 0; x < num_pebbles; x++)
    {
       pebble = clone_object(PEBBLE);
       pebble->move(this_object());
       pebble->add_prop(OBJ_I_HIDE, (random(65)+10) );
    }

    add_prop(I_PEBBLE_EXIST, num_pebbles);
    add_prop(I_PEBBLE_TIMESTAMP, (time() + 6900 + random(600)) );  

}

/*   Herbsupport for the trail. 
     Using already defined herblist:
     /d/Gondor/harondor/lib/harondor_herbs.h
 */
int set_trail_herbs()
{
    switch(random(100))
    {
    case 0..69:
        set_up_herbs( ({ ONE_OF_LIST(HARONDOR_HERBS),
            ONE_OF_LIST(HARONDOR_HERBS), 
            ONE_OF_LIST(HARONDOR_HERBS),
            ONE_OF_LIST(HARONDOR_HERBS) }),
            ({ areadesc, "ground", "grass", "herbs", "vegetation",
            "trail" }),
            4 );
    break;
    case 70..75:
        set_up_herbs( ({ HERB_DIR + "suranie", 
            HERB_DIR + "attanar", HERB_DIR + "lissuin",
            HERB_DIR + "redweed", HERB_DIR + "lothore",
            HERB_DIR + "seregon", HERB_DIR + "morgurth"}),
            ({ areadesc, "ground", "grass", "herbs", "vegetation",
            "trail" }),
            2 );
    case 76..99:
    default:
    break;
    }
    return 1;
}


/* A block message for directions on the secret trail that will
   not be used.
 */
int s_block()
{
   string str = one_of_list(({"The sand is too deep and " +
                    "treacherous to walk in that direction.",
                    "The mounds look far too large for you " +
                    "to tread in that direction.", 
                    "The risk of getting lost is too great " +
                    "in that direction.", 
                    "You would most probably not find your " +
                    "back should you walk in that direction."}));
   str += "\n";

   write(str);

   return 1;
}

/* Function name: wind_block
 * Description  : Gets called from room, argument is mandatory.
 * Arguments    : string dir - The west or east part of the 
 *                camp calling the function.
 * Returns      : int 1/0 - closed/open
 */
int wind_block(string dir)
{
   if(QUERY_WIND_OPEN->query_wind_open(dir))
      return 0;

   write("The mounds have grown too big to pass in that direction.\n");
   return 1;
}

/* The callouts to the trail */
public void add_harad_trail_tells()
{
    set_tell_time(120+random(30));
    add_tell("Hot winds blow across the land.\n");
    add_tell("Some sand blows up into your eyes.\n");
    add_tell("Dark clouds blow across the sky.\n");
    add_tell("An evil looking craban flies overhead.\n");
    add_tell("A group of Haradrim march past you as they head east on the trail.\n");
    add_tell("A bird runs across the trail in front of you and disappears.\n");

}

/* The callouts to the secret trail */
public void add_harad_secret_tells()
{
    set_tell_time(150+random(50));
    add_tell("Hot winds blow across the dry land.\n");
    add_tell("Sand blows up into your eyes.\n");
    add_tell("Dark clouds blow across the sky.\n");
    add_tell("A huge winged shape flies past you in the sky. It circles " +
        "back before continuing its journey.\n");
    add_tell("An evil looking craban flies far overhead.\n");
    add_tell("A piercing shriek echoes from above.\n");
    add_tell("The wind picks up speed and blows blows sand into your " +
        "ears and eyes.\n");
    add_tell("A very small, dark animal runs past you in your peripheral " +
        "vision and disappears.\n");
}
