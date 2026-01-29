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
       "of green and pinks. There is a huge formation of roses and "+
       "the beauty of it simply takes your breath away. You notice on "+
       "both sides of the precious bronze gate a tall hedge and two "+
       "different types of roses which embelish the garden. You can "+
       "stroll the gravel path into the garden to visit the fountain south "+
       "of you, or the rest of the garden.\n");

   set_up_roses(0, ({"orange","red"}));

    add_item("orange roses",
        "You look closer at the orange roses and recognize them as "+
        "Angels Mateu roses. They have double, globular petals in a "+
        "bright orange-rose color. They are of course big, bright, "+
        "eye-catching flowers. They have a very distintive fragance like "+
        "ripe raspberries.\n");

    add_item("red roses",
        "You examine these roses closely and discover they are Crimson "+
        "Glory roses. They are gorgeous flowers with very dark red "+
        "velvety petals, that are soft to the touch. Their delicate beauty "+
        "is captivating along with their intoxicating fragrance, just like "+
        "the best sweet wine.\n");

    add_item( ({"roses"}),
      "Such wonderous flowers all around you. There are many "+
      "different colored roses.\n");

    add_item("fountain",
         "The ivory fountain is the centerpiece of the rose garden. You "+
         "will have to stroll south to see it better.\n");

    add_door_exit(TELBERIN_ROSE_GARDEN_DIR + "garden_gate",
	"../tel07_09", "east");

    add_exit("rosefountain", "south");
    add_exit("rose2", "west");
    add_exit("rose5", "southeast");
}

