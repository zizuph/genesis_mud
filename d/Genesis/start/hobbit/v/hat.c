/*
 *  hat.c
 *    A hat for the mayor of Hobbiton
 */

#pragma save_binary

inherit "/std/armour";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"

create_armour()
{
   int i, max, type;

   set_name("hat");
   set_pname("hats");
   set_short("green fishing hat");
   set_pshort("green fishing hats");
   set_adj(({"green","fishing"}));
   set_long("The little green hat is best worn while fishing.\n");
    
   set_default_armour(2, A_HEAD, 0, 0);

   add_prop(OBJ_I_WEIGHT,370);
   add_prop(OBJ_I_VOLUME,240);
   add_prop(OBJ_I_VALUE,37);
}