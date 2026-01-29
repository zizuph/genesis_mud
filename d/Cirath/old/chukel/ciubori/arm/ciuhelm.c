/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/arm/ciuhelm.c
* Comments: Edited by Luther Oct. 2001
*/

inherit "/std/armour";
inherit "/lib/keep";

#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include <stdproperties.h>

void
create_armour()
{
  	set_name("helmet");
  	set_pname("helmets");
  
  	set_short("leather helmet");
  	set_pshort("leather helmets");
  
  	set_long(break_string(
           	"This helmet is made of hard leather to protect you from "+
           	"nasty hits in the head.\n",60));
           
  	set_adj("leather");

  	set_ac(13);
  	set_am(({ 0, 0, 0}));
  	set_at(A_HEAD);

   	add_prop(OBJ_I_VALUE,250);
  	add_prop(OBJ_I_WEIGHT,1000);
  	add_prop(OBJ_I_VOLUME,500);
}
