 /*
    Modified: 30 Apr 2003, by Bleys
        - There were two set_longs. I commented out the one that
            didn't seem to belong.
*/
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include "/sys/stdproperties.h"
#include <wa_types.h>

create_terel_armour(){
    set_name("shield");
    set_adj("black-horned");

    set_short("black-horned shield");
    set_long("A strange round black shield with spiked "+
        "horns protruding around it's edges.\n");
 // set_long("A strange runed silver shield.\n");
    set_ac(18);
    set_at(A_SHIELD);
    set_am(({0, 0, 0}));
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_VALUE, 700);
}
