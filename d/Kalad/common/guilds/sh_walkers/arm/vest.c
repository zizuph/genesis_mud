inherit "/std/armour";
#include "/d/Kalad/defs.h"


void
create_armour()
{
    set_name("vest");
    add_adj("black");
    set_adj("studded-leather");
    set_short("black studded-leather vest");
    set_long("This is a vest made of soft, flexible leather covered "+
    "with dark, steel studs. It is ideal for thieves who want to "+
    "be protected, yet want some measure of comfort.\n");
    set_at(A_TORSO);
    set_ac(22);
    add_prop(OBJ_I_WEIGHT,5000);
    add_prop(OBJ_I_VOLUME,3700);
    add_prop(OBJ_I_VALUE,300);
}
