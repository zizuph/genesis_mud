/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/arm/ciuboots.c
* Comments: Edited by Luther Oct. 2001
*/

inherit "/std/armour";
inherit "/lib/keep";

#include "/sys/wa_types.h"
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_armour()
{
    	set_name("boots");
    	set_pname("boots");
    
    	set_short("pair of leather boots");
    	set_pshort("pairs of leather boots");

    	set_adj("leather");
    	add_adj("white");
    
   	set_long("These boots are made of white leather. They look nice and "+
           	"warm.\n");

    	set_default_armour(10, A_FEET, ({-1,1,0}), 0);

    	add_prop(OBJ_I_VALUE,250);
    	add_prop(OBJ_I_WEIGHT,3000);
    	add_prop(OBJ_I_VOLUME,1500);
}