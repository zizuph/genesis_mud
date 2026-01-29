/*
 * Road to Blue Mountains
 * - Finwe, July 2002
 *
 *   2006.09.05, Toby; Added add_items according to bug log
 */

#include "local.h"
#include "/d/Shire/sys/defs.h"

inherit BASE_ROAD;

void
create_blue_road()
{
   area = "on top of a ridge in";
   areaname = "the Blue Mountains";
   land = "Eriador";
   areatype = 5;
   areadesc = "path";


    extraline = "Tall peaks surround you here in the tops of the Blue " +
        "Mountains. Green grass grows everywhere, and is dotted with " +
        "various wildflowers. A rocky path leads south from the top " +
        "of the mountains.";
   
    add_item(({"green grass", "grass", "matted grass"}),
        "It is soft and matted flat. Small wildflowers dot the grass.\n");
    add_item(({"path", "road", "rocky path", "rocky road"}),
        "The path is rocky, leading down south out of the mountains.\n");
    add_item(({"blue mountains", "mountains", "mountains of the lune", 
            "ered luin"}),
        "The Blue Mountains are a tall chain of mountains. They run " +
        "north and south with tall, rugged peaks that reach to the sky.\n");
    add_item(({"wild flower", "wildflowers", "flowers"}),
        "Wildflowers grow scattered across the grass. They dot the " +
        "area with their cheery blossoms.\n");
    add_item(({"ridge", "plateau"}),
        "The ridge is a flat plateau in the mountains. Its west and north " +
        "sides are sheer drop-offs that lead down into the depths of the " +
        "mountains. On the south and east side, peaks rise up. The ridge " +
        "is covered with green grass.\n");
    add_item(({"peaks", "mountain peaks"}),
        "The peaks are craggy and obviously very ancient. They are " +
        "various heights, some rising above you, looking like broken towers.\n");
    add_item(({"drop-off", "drop-offs"}),
        "The drop-offs lead down into the depths of the mountains.\n");
    add_item("depths",
        "You make out no details of the depths of the mountains from up here.\n");
 

   add_exit(ROAD_DIR + "rd10","south");
   reset_shire_room();
}

void
reset_shire_room()
{
/*
    object crystal;

        if (!present("crystal",TO))
    {
        crystal = clone_object("/d/Shire/scav_hunt/crystal");
        crystal->add_prop(OBJ_I_HIDE, 10 + random(10));
        crystal->move(TO);
    }
*/
}

