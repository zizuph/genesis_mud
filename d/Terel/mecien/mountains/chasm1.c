inherit "std/room";
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"
#define TP this_player
#define PATH "/d/Terel/mecien/mountains/"

create_room(){
set_short("Chasm Bottom");
set_long(
"Howling in the winds, this icy pit is the bottom of an immense\n"
+ "chasm. The edges of the chasm are high above, strung with\n"
+ "myriads of icicles. Some of the icicles are so long that they\n"
+ "hang to the bottom of the chasm, transforming this place, as if\n"
+ "they are pillars of some majestic hall. All the ice sparkles\n"
+ "and glitters in the light.\n"
);

add_my_desc("There is a hole in the icy chasm wall.\n");
add_exit(PATH + "chasm2", "north", 0);

add_item("icicles", "These icicles hang from high above, around the\n"
 +"edge of the chasm, some descend all the way down here.\n"
);
add_item("chasm", "It is immense, icy and forsaken.\n");
add_item("hole", "It is a strange ascending tunnel.\n");
add_cmd_item("hole",({"enter","climb"}),({"@@climb_func@@","@@climb_func@@"}));
}

string
climb_func()
{
        object ob;

        if (ob = present("axe",TP()))
        {
                write("Using the "+ob->query_short()+", you claw your way up "
                + "the tunnel.\n");
                TP()->move_living("up the tunnel",MECIENDIR+"mountains/ice4");
                return "";
        }
        else
        return break_string("You cannot climb up the tunnel unassisted; it is too icy. "+ 
        "Perhaps if you had something to sink into the ice as a means of purchase?\n",70);
}    

