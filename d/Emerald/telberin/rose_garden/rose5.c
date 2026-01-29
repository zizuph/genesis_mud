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
       "to the hedge and bright yellow roses which embelish the garden "+
       "serenely. You can stroll the gravel path into the garden to visit "+
       "the fountain west, or the rest of the garden.\n");



    add_item(({"bright yellow roses", "yellow roses"}),
        "These roses are called Carpet of Gold. They are ideal creepers "+
        "for banks and boulders. In this setting they cover grey boulders, "+
        "and are as tall as the other rose bushes. The effect "+
        "is quite uncoventional for a garden but natural in an elven "+
        "way. These roses are small and delicate with little "+
        "bottoms of brilliant yellow. Their aroma is sweet as ripened "+
        "peaches.\n");

    add_item( ({"roses"}),
      "Such wonderous flowers all around you. There are many "+
      "different colored roses.\n");

   set_up_roses(0, ({"yellow"}));

    add_item("fountain",
        "The ivory fountain is the centerpiece of the rose garden. "+
        "You will have to stroll west to see it better.\n");

    add_exit("rose1", "northwest");
    add_exit("rose4", "southwest");
    add_exit("rosefountain", "west");
}
