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
    set_name("spear");
    add_name("polearm");
    set_short("bone-bladed spear");
    set_long("The blade of this crude spear is made of sharpened "+
        "bone. Though neither as strong nor as sharp as steel, it "+
        "is still capable of inflicting mortal wounds. The flimsy "+
        "wooden handle only adds to the wielders concern that it "+
        "might break.\n");
        
    set_adj("bone-bladed");

    set_hit(21);
    set_pen(14);

    likely_dull=16;
    likely_corr=0;
    likely_break=28;

    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);

    add_prop(OBJ_I_WEIGHT,3450);
    add_prop(OBJ_I_VOLUME, 2990);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(21,14)-random(150));
}
