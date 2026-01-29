/* Stralle @ Genesis 041220
 */
#pragma strict_types

inherit "/std/torch";

#include <stdproperties.h>

void
create_torch()
{
    set_name("candle");
    set_adj(({"black", "small"}));
    set_long("This candle has a thick base, about the size of a palm. " +
             "It is deep black while the inside at the wick has a " +
             "slight reddish hue. Due to it being short having a " +
             "thick base it is most likely meant to be put directly " +
             "on an stone tablet.\n"); 

    set_strength(1);
    set_time(300 + random(100));

    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VALUE, 60);
} 
