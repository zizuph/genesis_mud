inherit "/std/armour";
#include "/d/Kalad/defs.h"


void
create_armour()
{
    set_name("pants");
    add_adj("black");
    set_adj("studded-leather");
    set_short("pair of black studded-leather pants");
    set_pshort("pairs of black studded-leather pants");
    set_long("These are a pair of pants made of soft, flexible leather "+
    "covered "+
    "with dark, steel studs. It is ideal for thieves who want to "+
    "be protected, yet want some measure of comfort.\n");
    set_at(A_LEGS);
    set_ac(20);
    add_prop(OBJ_I_WEIGHT,5000);
    add_prop(OBJ_I_VOLUME,3700);
    add_prop(OBJ_I_VALUE,300);
}
