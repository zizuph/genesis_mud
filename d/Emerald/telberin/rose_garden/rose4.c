#include "../defs.h"

inherit ROSE_ROOM;
#include <macros.h>

#define TO this_object()
#define TP this_player()
#define ENV environment

void
create_rose_garden()
{

    set_em_long("A wondrous rose garden lays in front of you. "+
       "The design of this garden is awe-inspiring with such interplay "+
       "of green and pinks. There is a huge formation of roses and the "+
       "beauty of it simply takes your breath away. You cast your eyes "+
       "to the hedge and pale pink roses which enhance the garden "+
       "generously. You can stroll the gravel path into the garden to "+
       "visit the fountain north, or the rest of the garden.\n");

   set_up_roses(0, ({"pink"}));

    add_item(({"pale pink roses", "pale roses"}),
        "These roses are Briarcliff. They are big roses with double petals "+
        "in a bright rose-pink color. Their fragrance is quite "+
        "pleasant like summer honey, sweet and warm.\n");

    add_item( ({"roses"}),
      "Such wonderous flowers all around you. There are many "+
      "different colored roses.\n");


    add_item("fountain",
        "The ivory fountain is the centerpiece of the rose garden. "+
        "You will have to stroll north to see it better.\n");

    add_exit("rose3", "northwest");
    add_exit("rose5", "northeast");
    add_exit("rosefountain", "north");
}

