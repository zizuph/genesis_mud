inherit "/std/container";

#include <stdproperties.h>

public void
create_container()
{
    set_name("desk");
    set_adj("writing");

    set_long("This desk is marred by age and heavy use. Ink stains and"
           + " black melted wax can be seen along its writing surface,"
           + " which would seem to have been the location of many"
           + " hours of study over many many years.\n");

    add_item( ({ "ink", "ink stains", "stains", "stain", "ink stain" }),
        "The ink has stained the wood a dark black in numerous places"
      + " along the desk.\n");
    add_item( ({ "wax", "black wax", "melted wax",
                 "black melted wax" }),
        "Though there are many areas of the desk which are coated"
      + " with wax, there is no sign of any candles or candleabra"
      + " which have been used here in the near past.\n");
    add_item( ({ "surface", "writing surface" }),
        "The writing surface is covered with ink stains and old"
      + " wax marks. Many hours of study have been spent here over"
      + " the years.\n");
    
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_MAX_VOLUME, 400000);
    add_prop(CONT_I_MAX_WEIGHT, 300000);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 200000);
}
