/*
   Pax tharkas. Lamp descriptions, and add_actions.

   Blamp_base.c 
   ------------

   This file provides the corridors in the lower level of Pax Tharkas
   with the descriptions of lamps, when examined.


   Coded ........: 95/01/11
   By ...........: Jeremiah

   Latest update : 95/01/23
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

int    lamp_descr_type = random(4);       
string lamp_descr_str;

void
add_the_lamp()
{
   TO->add_item(({"lamp", "oil lamp", "brass lamp", "brass oil lamp"}), 
   "@@lamp_descr");
}


string
lamp_descr()
{
   switch(lamp_descr_type)
   {
      case 0 : lamp_descr_str = "This is an old brass oil lamp. It looks " +
                                "like it a good source of light.";
      break;
      case 1 : lamp_descr_str = "This is a well maintained brass lamp. " +
                                "Its has been well polished, and the " +
                                "wick looks new.";
      break;
      case 2 : lamp_descr_str = "A nice old brass lamp. It is a bit " +
                                "dented, but else it looks as if in " +
                                "good shape.";
      break;
      case 3 : lamp_descr_str = "This brass oil lamp looks rather new. " +
                                "It has probably replaced an older " +
                                "one.";
      break;
   }
   lamp_descr_str += "The lamp is mounted in a solid holder, fastened to " +
                     "the stone wall.\n";

   return lamp_descr_str; 
}

