/* This comment tells emacs to use c++-mode -*- C++ -*- */
// Field leading to Stonehold 
// Dwarven Stronghold.
// Tomas  -- May 2000

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include "/d/Terel/include/herb_arrs.h"
#include <stdproperties.h> 

inherit STDROOM;
inherit "/d/Terel/std/room_tell.c";
inherit "/d/Terel/std/herbsearch.c";
inherit "/d/Terel/mountains/elderwood/include/cold_fatigue.c";

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])
#define  ARGIL_HERB        ({(TER_HERB  + "argil")})

#define ROAD_DIR   MOUNTAIN_DIR + "elderwood/road/"
#define DEFAULT    MOUNTAIN_DIR + "elderwood/field/"
#define FOREST_DIR MOUNTAIN_DIR + "elderwood/forest/"

object pebble;



init()
{
    ::init();
    add_action("do_smell",  "smell",  0);
    start_room_tells();
}


public string
smell_desc()
{
    return "The air smells of dry grass.\n";
}


/*
 * Function name: do_smell
 * Description:   Handle the smell action
 * Returns:       1/0
 */ 
public int
do_smell(string str)
{
    NF("Smell what?\n");
    if (!strlen(str))
        return 0;
    
    if (str == "air" || str == "scent" || str == "strange scent") {
        write(smell_desc());
        return 1;
    }
    return 0;
}


public void
create_room()
{
    ::create_room();
    set_short("in a snow covered field");
    set_long("Drifts of snow cover the field with the exception of " +
       "some rocky exposed patches. Bits of tall frozen grass " +
       "can be seen growing around the exposed areas of the " +
       "field. A vast jagged mountain range can be seen to the north. " +
       "Towards the south is a densely populated forest. ");

    add_item(({"mountain","mountainrange","pass"}),
       "The vast jagged mountainrange extends all along the " +
       "northern horizon. You notice what looks like " +  
       "a mountain pass towards the middle of the field.\n");

 
    add_item(({"tall frozen grass","grass","frozen grass"}),
       "Tall grass frozen, colored yellow by the bitter cold " +
       "sticks out of the thinner areas of the snow drifts and along " +
       "the rocky patches.\n");

    add_item(({"field","snow covered field"}),
       "The field is covered in snow with the exception of some " +
       "rocky exposed areas. Clumps of tall frozen grass " +
       "grow about rocks and shallow areas of the snow drifts.\n");

    add_item(({"rocks","rocky patches","patches"}),
       "Patches of exposed rock can be seen scattered about " +
       "the frozen snow covered field.\n");

    add_item(({"snow","drifts of snow","snow drift","snow drifts"}),
       "The drifts of snow remind you of the sutble rolling " +
       "ocean waves. One looks largely like another.\n");

    add_item(({"snow covered road","snowy road","road"}),
       "The snow covered road leads north and southward "+
       "through a densely populated forest, which grows " +
       "on either side of the road.\n");

    add_item(({"forest","trees","undergrowth", "bushes",
               "shrubs","plants","evergreens","floor",
               "ground","shrub","plant","evergreen",
               "bush"}),
       "To the south you can see the treeline of a densely " +
       "populated forest. Its tall trees tower high above " +
       "casting shadows on the basin below.\n");


    set_tell_time(300 + random(200));
    add_tell("You hear birds chirping off in the distance.\n");

    add_cmd_item(({"rocks","rock","pebble","pebbles"}),
                 ({"collect","gather","get"}),"@@get_pebble");

    set_up_herbs( ({ ONE_OF_LIST(PLAINS_HERBS),
                     ONE_OF_LIST(PLAINS_HERBS),
                     ONE_OF_LIST(ARGIL_HERB),
                  }),
                  ({"grass","rocks","snow"}) , 3 );
    
  
    reset_room();

}


int             //Am I skilled enough to see the exits?
exits()
{
   if ((TP->query_skill(SS_LOC_SENSE) > 60))
   {
       return 0;
   }
       return 1;
}


get_pebble()
{
    object pebble;

    seteuid(getuid(TO));
    pebble = clone_object(CALATHIN_DIR + "houses/obj/pebble");
    pebble->move(TP);
    write("You sift through the snow finding a small pebble.\n");
       say(QCTNAME(TP) + " reaches into the snow and picks up a pebble.\n");
    return 1;
}

