/*   
    Black greaves for the small water krougs
    
    Coded by Digit and Maniac

*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("greaves");
    set_adj("black");
    set_short("pair of black greaves"); 
    set_pshort("pairs of black greaves"); 
    set_long("A pair of black greaves.\n");
    set_ac(11);
    set_at(A_LEGS);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 3000);
}

