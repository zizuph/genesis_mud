/* legs_wod: Wooden leg guards for the tree fan in us all... */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    ::create_armour();
    set_name("guards");
    set_short("pair of wooden leg guards");
    set_pshort("pairs of wooden leg guards");
    set_long("Upon the leather of workman's boots have been fastened "+
             "plates of wood. It is primitive, but effective.\n");
    set_adj("wooden");
    add_adj("leg");

    set_ac(21);
    set_am(({ 1, -2, 0}));
    set_at(A_LEGS);

    add_prop(OBJ_I_WEIGHT, 2700);
    add_prop(OBJ_I_VOLUME, 1350);
}
