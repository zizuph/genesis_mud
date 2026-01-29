/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/wep/cg_shield.c
* Comments: Updated by Luther Oct. 2001
*/

inherit "/std/armour";
inherit "/lib/keep";
#include "/sys/wa_types.h"
#include "defs.h"

void
create_armour()
{
  set_name("shield");
  set_pname("shields");
  set_short("nomad steel shield");
  set_pshort("nomad steel shields");
  set_long("This is a steel shield with a red stripe crossing "+
           "diagonally over it. It's the type of shield that "+
           "the nomad warriors use.\n");
  set_adj("steel");
  add_adj("nomad");

  set_ac(10);
  set_am(({ -1, 1, 0 }));
  set_at(A_SHIELD);
  
  add_prop(OBJ_I_WEIGHT,3000);
  add_prop(OBJ_I_VOLUME,1500);
}
