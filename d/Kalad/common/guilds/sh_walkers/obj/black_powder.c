inherit "/std/object";
#include "/d/Kalad/defs.h"
 /* Sarr */
#define KALAD_SHADOW_INGR "_kalad_shadow_ingr"

void
create_object()
{
    set_name("powder");
    set_adj("black");
    set_short("handfull of black powder");
    add_name("_kalad_black_powder");
    set_long("This is a small handfull of strange black powder. It "+
    "looks like it was scraped off metal and then burned.\n");
    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,10);
    add_prop(KALAD_SHADOW_INGR,10);
}
