/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/arm/ciuarmor.c
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
  	set_name("shirt");
  	set_pname("shirts");
  
  	set_short("leather shirt");
  	set_pshort("leather shirts");
  
  	set_long("This shirt is made of leather from some creature. The "+
           	"leather is soft, which makes it nice to wear.\n");
           
  	set_adj("leather");
  	add_adj("chukelian");

  	set_ac(12);
  	set_am(({0,1,1}));
  	set_at(A_TORSO);
  
  	add_prop(OBJ_I_VALUE,250);
  	add_prop(OBJ_I_WEIGHT,2000);
  	add_prop(OBJ_I_VOLUME,1000);
}
