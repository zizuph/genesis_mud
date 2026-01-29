/**********************************************************************
 * - Added a laying function so players can lay upon grass or some  - *
 * - other player.                                                  - *
 * - Modified by Damaris@Genesis 02/2005                            - *
 * - Added a stream (foundation for the Distillers guild)           - *
 * -- Tapakah 04/2021                                               - *
 **********************************************************************/
#include "plains.h"
#include <macros.h>
#include "/d/Khalakhor/sys/paths.h"

inherit PLAINBASE;
#include "laying.c"

public void
create_khalakhor_room()
{
    extra = "A small swift stream is flowing from the north, rapidly expanding towards the southeast. There are the remains of an old campfire here. ";
    proxim = (["shore":({1, "west"}),
               "t_hills":({1, "north"})]);

    create_plain();
    
    add_my_desc(lay_desc, this_object());
    
    add_item(
             ({"remains","fire","campfire"}),
             "A small patch of burnt grass and sticks is all that remains "+
             "of the fire. Strange that someone would camp out in the "+
             "middle of the plains. Perhaps they just didn't make it "+
             "to the village before dark. It looks as if they have been "+
             "gone for a while anyway.\n"
             );
    add_item(
             ({"stream", "current", "water"}),
             "A small stream, about a couple feet wide and a foot deep rushes from the north into the plains. It is very swift.\n"
             );
    add_cmd_item(
                 ({"stream", "current", "water"}),
                 ({"swim", "drink"}),
                 ({"It's too small to swim in.\n", "You drink from the stream and feel refreshed.\n"})
                 );

    add_exit(PLAINS + "plains_2_1", "north");
    add_exit(PLAINS + "plains_3_1", "northeast");
    add_exit(PLAINS + "plains_3_2", "east");
    add_exit(PLAINS + "plains_3_3", "southeast");
    add_exit(PLAINS + "plains_2_3", "south");
    add_exit(PLAINS + "plains_1_2", "west");
    add_exit(PLAINS + "plains_1_1", "northwest");
}

public void setup_plains_herbs()
{
    herbs = ({KRHERB+"fireweed"}); // grows in recently burnt areas
    set_up_herbs(herbs, ({"grass","here","remains","campfire"}),3);
}

public void
init()
{
    ::init();
    init_lay();
}
