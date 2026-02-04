/* This comment tells emacs to use c++-mode -*- C++ -*- */
// Southern road traversing between southern terel and the 
// Dwarven Stronghold.
// Tomas  -- Jan 2000

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>

inherit STDROOM;
inherit "/d/Terel/std/room_tell.c";
inherit "/d/Terel/mountains/elderwood/include/cold_fatigue.c";

// Special thanks to Mortis for his smell_world code.
inherit "/d/Terel/mountains/elderwood/include/smell_forest";

#include <stdproperties.h>

#define DEFAULT    MOUNTAIN_DIR + "elderwood/road/"
#define FOREST_DIR MOUNTAIN_DIR + "elderwood/forest/"

object pebble;
int long, short;
public int do_smell(string arg);


int set_long_desc(int i)
{
    long = i;
}

int set_short_desc(int i)
{
    short = i;
}

public void
init()
{
    ::init();
    add_action(do_smell, "smell");
    add_action(do_smell, "sniff");
    add_action(do_smell, "inhale"); /* a few different verbs, same effect*/

    start_room_tells();
}


/*
 * Function name:        do_smell
 * Description  :        allow the player to smell the air
 * Arguments    :        string arg - the commands following the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_smell(string arg)
{
    if (strlen(arg) && !parse_command(arg, ({}),
        "[the] 'air' / 'here' / 'area' [of] [the] [city]"))
    {
        return 0; /* the player used syntax we don't agree with */
    }

    /*
     * Note: The above if statement searches for combinations of the
     *       syntax in quotes. Statementes in [] are optional, statements
     *       in '' are required, with / acting as "or" statements. Thus,
     *       we can handle a vast number of combinations, including, but
     *       not limited to:
     *
     *       air
     *       the air
     *       the air of the city
     *       here
     *       area
     *       etcetera
     *
     *       Of course, we have also made possible odd combinations such
     *       as:
     * 
     *       here the
     *       the area city
     *       etcetera
     *
     *       But a small price to pay for being user friendly. :-)
     */


    smell_world(this_player());
    return 1;
} /* do_smell */

public void
create_room()
{
    ::create_room();
    set_short("@@short_desc@@");
    set_long("@@long_desc@@");


/*    add_prop("_room_m_da_dragonsteed_no_land","The trees " +
       "have extended their branches creating " +
       "a makeshift canopy over the road. The branches " +
       "are too thick for your dragon to land safely.\n");
*/
    add_item(({"hoof prints","horse hoof prints","prints"}),
       "The road is rutted with several hoove prints in the snow.\n");

    add_item(({"mountain","mountain range", "mountains","Dragon Tooth mountains"}),
       "The fabled Dragon Tooth mountains. A vast jagged snow-capped mountain " +
       "range extending across the northern horizon.\n");

    add_item(("pass", "mountain pass"),
       "The pass appears to be a natural ravine, cut by water " +
       "runoff from the mountains above. The path floor has been cleared " +
       "to form a wide well travelled dirt road which winds through " +
       "the Dragon Tooth mountain range. Its sides are mostly comprised of " +
       "granite and shale rock formations. A dense treeline lines the top " +
       "of the pass wall on either side.\n");

//majestic Douglas-fir, red cedar and western hemlock

    add_item(({"field","snow covered field"}),
       "The field is covered in snow with the exception of some " +
       "rocky exposed areas. Clumps of tall frozen grass " +
       "grow about rocks and shallow areas of the snow drifts.\n");

    add_item(({"snow covered road","snowy road","road","dirt road"}),
       "The snow covered road leads north and southward "+
       "through a densely populated forest, which grows " +
       "on either side of the road.\n");

    add_item(({"forest","trees","undergrowth", "bushes",
               "shrubs","plants","evergreens","floor",
               "ground","shrub","plant","evergreen",
               "bush"}),
       "The evergreens loom high overhead creating a " +
       "semi-shaped canopy over the road. Dense undergrowth " +
       "covers the forest floor on either sides of the road.\n");

    add_item(({"branches","tree branches"}),"The tree branches " +
       "extend from either side entertwining over the road.\n");

    add_item(({"snow"}),"The snow covers everything, piling up along " +
       "the road and at the tree basin.\n");
    
    set_tell_time(500 + random(200));
    add_tell("Snow drifts stir as a gust of icy wind blows by.\n");

    add_cmd_item(({"rocks","rock","pebble","pebbles"}),
                 ({"collect","gather","get"}),"@@get_pebble");
    
  
    reset_room();

}


get_pebble()
{
    object pebble;

    seteuid(getuid(TO));
    pebble = clone_object(CALATHIN_DIR + "houses/obj/pebble");
    pebble->move(TP);
    write("You pickup a pebble from the ground.\n");
       say(QCTNAME(TP) + " reaches into the snow and picks up a pebble.\n");
    return 1;
}


string short_desc()
{
    switch(short)
        {
                case "road":
                        return "on a snow covered road";
                        break;

                case "pass":
                        return "in a rocky forest lined pass";
                        break;

                case "forest_road":
                        return "deep within a vast forest on " + 
                        "a snow covered road";
                        break;

                case "field_road":
                        return "on a snow covered road traversing " +
                        "fields of snow.";
                        break;                       
        }
 }



string long_desc()
{
    switch(long)
        {
               case "field_road":
                     return "The snow covered road leads through " +
                     "the barren snow fields towards a jagged " +
                     "mountain range pass to the north.\n"; 
                     break;

                case "forest_road":
                     return "You continue to travel on the snow covered " +
                     "road. Drifts of snow have built up along the " +
                     "treeline along the sides of the road. The " +
                     "Elderwood forest extends on either side of you.\n";
                     break;

                case "road":
                     return "The snow covered road continues to rise steadily " +
                     "to the north through the pass towards the Dragon Tooth " +
                     "mountains. The path gradually leads downwards towards " +
                     "the southern pass entrance.\n";
                     break;

               default:
                        return "You stand on a snow covered road deep " +
                        "within the northern territory of Terel.\n";
                        break;
        }
}



