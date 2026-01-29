inherit "/std/armour";
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
void
create_armour()
{
    set_name("hat");
    set_short("weathered wide brim hat");
    set_adj(({"weathered","wide","brim"}));
    set_long("This " + short() + "Made from leather " +
       "with raw hide stitching. It looks pretty durable. The brim is probably wide " +
       "enough to keep the sun and rain off your face.\n");
    set_ac(1);
    set_at(A_HEAD);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 100);
}