/* body_scl: Overlapping plates of bone and chitin armour */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    set_name("mail");
    set_short("ribbed scale mail");
    set_long("With rib-bones secured to an undersuit of leather and small "+
             "plates of chitin attached to important spots on the bones, "+
             "ribbed scale mail is an ugly, though effective, form of "+
             "Athasian protection.\n");
    set_adj("scale");
    add_adj("ribbed");

    set_ac(35);
    set_am(({ 5, 5, -10}));
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 2000);
}
