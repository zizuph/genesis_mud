


/*The Manor's Garden XII
*Coded by Marisol (9/7/97) 
*Modified by Marisol(07/27/98) to be used in the village of Ovejuno
*in Emerald.
*Copyright (c) Marisol Ramos 1997
*/

#include "defs.h"
inherit CASTLE_GARDEN;

void
create_emerald_garden()
{

    set_long("An old ruined garden lies in front of your eyes. "+
        "A tall hedge of rhododendrons surrounds the garden, making it "+
        "impossible to see outside the enclosure. This section is "+
        "different from the rest of the garden. Here, beautiful trees "+
        "are sparkled with flowers. All are white with a yellow "+
        "center, some are brighter than the others. Amid the "+
        "dandelions, you can see some of the white flowers that has "+
        "fallen onto the tall lawn. The mix of fresh and decaying "+
        "flowers blend to fill the air with an unique scent.\n");

    add_item("plants",
        "Here there are two different trees, blosoming white-yellow "+
        "flowers. The ground is also covered with their petals "+
        "decaying slowly over the tall grass. Yellow flowers mingle with "+
        "the petals and grass, making impossible to see if there is "+
        "anything hiding in it.\n");

    add_item(({"white-yellow flowers", "trees"}),
        "These trees are Plumerias! They are rare and they are only "+
        "found in the most remote forests in the realm of Emerald. They "+
        "are two species here. Elena, whose flowers has white petals "+
        "with a brilliant yellow center, and a narrow pink band on the. "+
        "back. It has a slight sweet fragance. It should not be confuse "+
        "with the Moonlight tree. This tree has small white flowers, "+
        "with a distintic yellow center. The flowers also have a "+
        "very strong fragance of gardenias.\n");



    add_exit("castle_garden08", "north");
    add_exit("castle_garden06", "south");

}                                                                    
