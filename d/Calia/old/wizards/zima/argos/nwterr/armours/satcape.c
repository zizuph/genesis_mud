/* The cape of the priestly satyr (monsters/psatyr) */
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() {
    set_name("cape");
    set_adj(({"long","purple"}));
    set_short("long purple cape");
    set_long(
             "It is a long purple cape with a wide border embroidered "+
             "with leaves of gold thread. Its silk lining seems to be "+
             "covered in goat hair.\n");
    set_ac(1);
    set_at(TS_ROBE);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 1000);
}
