/*
   Pax tharkas. Lamp descriptions, and add_actions.

   Ilamp_base.c   
   ------------

   This file provides the corridors in the lower level of Pax Tharkas 
   with the descriptions of lamps, when examined. 

 
   Coded ........: 95/01/11
   By ...........: Jeremiah

   Latest update : 95/04/30
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
   TO->add_item(({"lamp", "oil lamp", "iron lamp", "iron oil lamp"}),
   "@@lamp_descr");
}


string
lamp_descr()
{
   switch(lamp_descr_type)
   {
      case 0 : lamp_descr_str = "This is an old rusty iron lamp. It " +
                                "doesn't give much light, just enough " +
                                "to make the surroundings visible.";
      break;
      case 1 : lamp_descr_str = "An old iron oil lamp. It doesn't look " +
                                "as it is of any real value, not even as " +
                                "a light source.";
      break;
      case 2 : lamp_descr_str = "It's an old iron oil lamp. It looks as " +
                                "if it has to be filled a couple of times " +
                       	         "a day to keep it going.";
      break;
      case 3 : lamp_descr_str = "A dented and rusty old iron lamp. Once " +
                                "it might have been a fine lamp, but that " +
                                "must have been long ago.";
      break;
   }
   lamp_descr_str += " The lamp is mounted in a holder, fastened to the " +
                     "stone wall.\n";

   return lamp_descr_str; 
}

