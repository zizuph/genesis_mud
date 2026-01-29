#include "../defs.h"

inherit ROSE_ROOM;
#include <macros.h>

#define TO this_object()
#define TP this_player()
#define ENV environment

create_rose_garden()
{

    set_em_long("A wondrous rose garden lays in front of you. "+
       "The design of this garden is awe-inspiring with such interplay "+
       "of green and pinks. There is a huge formation of roses and the "+
       "beauty of it simply takes your breath away. You cast your eyes "+
       "to the hedge and the supple orange roses which embelish the "+
       "garden. You can stroll the gravel path into the garden to visit "+
       "the fountain southeast, or the rest of the garden.\n");

   set_up_roses(0, ({"orange"}));

    add_item("orange roses",
        "You look closer at the orange roses and recognize them as "+
        "Angels Mateu roses. They have double, globular petals in a "+
        "bright orange-rose color. They are of course big, bright, "+
        "eye-catching flowers. They have a very distintive fragance like "+
        "ripe raspberries.\n");

    add_item( ({"roses"}),
      "Such wonderous flowers all around you. There are many "+
      "different colored roses.\n");


    add_item("fountain",
        "The ivory fountain is the centerpiece of the rose garden. "+
        "You will have to stroll southeast to see it better.\n");


    add_exit("rose1", "east");
    add_exit("rosefountain", "southeast");
    add_exit("rose3", "south");
}

