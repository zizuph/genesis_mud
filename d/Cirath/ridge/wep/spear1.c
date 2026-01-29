/* A mediocre bone-bladed spear.
   Code (c) 1998 to Damian Horton (aka Dethraine).
*/
#pragma strict_types 
#pragma save_binary

inherit "/std/weapon";
#include "defs.h"
#include "/sys/wa_types.h"
#include <formulas.h>

void create_weapon()
{
    set_name("staff");
    add_name("polearm");
    set_short("bone staff");
    set_pshort("bone staves");
    
    set_long("The entire length of the staff was carved out of a huge "+
        "bone. Each end being blunt and no decorations at all on the "+
        "length of the staff makes it very plain. The bone of which it "+
        "was made seems parculiarly strong and somewhat flexible. The staff "+
        "spans about 5 feet, allthough short for a staff it is extremely "+
        "light and manouverable.\n");
        
    set_adj("bone");

    set_hit(31);
    set_pen(28);

    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_VALUE, 400);
}
