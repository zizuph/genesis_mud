/* standard karg lance wielded by kargs in Gont
 *  Ten Alders 
 *  Amelia 11/97
*/

#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

public void
create_weapon()
{
    set_name("lance");
    set_adj(({"long", "red-plumed", "bronze", "kargish"}));
    set_short("red-plumed bronze lance");   
    set_long("A long bronze lance. The ashwood shaft, "+
        "almost three meters in length, is tipped with a razor sharp bronze "+
        "lancehead that has a wicked set of double flanges. "+
        "An ornament of blood-red plumes adorns the shaft "+
        "near to the tip in typical Kargish fashion.\n");
    set_default_weapon(25, 29, W_POLEARM, W_IMPALE | W_SLASH, W_BOTH);
    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VALUE, 300);
}
