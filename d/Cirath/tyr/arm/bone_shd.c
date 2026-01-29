/*
* Created by: Luther
* Date: August 2001
*
* File: /d/Cirath/tyr/arm/bone_shd.c
* Comments: Zarth's shield...
*/

inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    set_name("shield");
    set_short("medium bone shield");
    set_long("With the bones of dead foes. This shield has been perfectly "
    	+"put together with leather straps and old ropes. This shield will "
    	+"provide decent protection until it breaks.\n");
    set_adj("bone");
    add_adj("medium");
    
    set_ac(30);
    set_at(A_SHIELD);

    add_prop(OBJ_I_WEIGHT, 11000);
    add_prop(OBJ_I_VOLUME, 5000);
}
