inherit "/std/object";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/cmdparse.h"
/* by Antharanos */
void
create_object()
{
    ::create_object();
    set_name("foil");
    set_adj("gold");
    set_short("gold foil");
    set_long("A worthless piece of gold-colored foil paper.\n");
    add_prop(OBJ_I_VALUE,1);
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,50);
}
