/* Altar of the Kirk of the Port City; found in ksanct5.c
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 4/5/97      Zima        Created
** 3/7/98      Zima        Converted to ON container
**
*/
inherit "/std/container";
#include <stdproperties.h>
#include "defs.h"

void create_container() {
    set_name("altar");
    add_name(SR_ALTAR);
    set_adj(({"high","marble"}));
    set_short("the high altar");
    set_long(
       "It is the high altar of the kirk, a marble table with a square "+
       "top and a thick cylindrical pedestal base which rises out of "+
       "the floor. It is covered with a white cloth embroidered with "+
       "an emblem of three interlocked circles.\n");
    add_item("top",
       "The top of the altar is made of a thick square slab of marble, "+
       "and is covered with a white cloth.\n");
    add_item(({"pedestal","base"}),
       "The altar stands on a cylindrical marble pedestal base which "+
       "rises from the floor of the sanctuary to the bottom center of "+
       "the altar's top.\n");
    add_item("cloth",
       "It is a snow-white cloth which covers the altar. An emblem of "+
       "three large interlocked circles is embroidered in the center, "+
       "and the hem is embroidered with green shamrocks all around.\n");
 
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
}
