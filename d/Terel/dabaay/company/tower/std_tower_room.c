/* 
 * std room for the Tower of Stars of the Company of the 
 * Silver Dragon.
 * Shinto 012800
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <macros.h>
#include <stdproperties.h>


public void
create_room()
{


    add_item(({"walls","wall","stone walls","stone wall","stones","stone"
               "white stone","white stones","white stone walls",
               "white stone wall"}), 
               "The whole tower is made from this white stone. It's seems "+
               "stronger then any other type of rock. It shines as if it "+
               "were white marble and is just as smooth.\n");
    add_item(({"floor","ground"}), "The floor is made from the same stone as "+
               "the rest of the tower. It's smooth and shines as if it were "+
               "white marble.\n");

}
