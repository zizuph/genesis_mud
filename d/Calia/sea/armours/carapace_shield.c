/*  file:  /d/Calia/sea/armours/carapace_shield.c
 *  description:  Water kroug shield for xlarge water krougs
 *  coder      :  Tigerlily
 *  date       :  2002-06-24                
 */


inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

void
create_armour()
{
    int ac = 25;
    set_name("shield");
    set_adj(({"black", "carapace"}));
    set_short("black carapace shield");
    set_long("A heavy black shield made from some strange"+
      " material resembling the ridged exoskeleton of a large"+
      " insect. It is hard as bone and has a shiny black"+
      " patina. It is designed to protect the body's softer"+
      " areas.\n");
    set_ac(ac);
    set_at(A_SHIELD);
    set_af(this_object());
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 6000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac));

}
