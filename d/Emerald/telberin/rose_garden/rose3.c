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
       "to the hedge and the dark red roses which captivates this section "+
       "growing thickly in their beds. You can stroll the gravel path into "+
       "the garden to visit the fountain east, or the rest of the garden.\n");

   set_up_roses(0, ({"red"}));

    add_item(({"red roses", "dark red roses"}),
        "You examine these roses closely and discover they are Crimson "+
        "Glory roses. They are gorgeous flowers with very dark red "+
        "velvety petals, that are soft to the touch. Their delicate beauty "+
        "is captivating along with their intoxicating fragrance, like the "+
        "best sweet wine.\n");

    add_item( ({"roses"}),
      "Such wonderous flowers all around you. There are many "+
      "different colored roses.\n");

    add_item("fountain",
        "The ivory fountain is the centerpiece of the rose garden. "+
        "You will have to stroll east to see it better.\n");

    add_exit("rose2", "north");
    add_exit("rose4", "southeast");
    add_exit("rosefountain", "east");
}
