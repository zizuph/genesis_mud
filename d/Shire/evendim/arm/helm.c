/*
 * Helmet used in prisoner quest
 * -- Finwe May 2001
 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name(({"helmet", "helm"}));
    set_short("bright silver helmet");
    set_pshort("bright silver helmets");
    set_adj(({"bright","silver"}));
    set_long("This winged helmet is made from a bright silver " +
        "metal. It looks like it is brand new despite its age. " +
        "Two silver wings adorn both sides of the helmet and " +
        "make it look like it is from a forgotten time.\n");
        
    set_ac(27);
    set_at(A_HEAD);
    
    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VALUE, 750+random(500));
    add_prop(OBJ_I_VOLUME, 1000);
}
