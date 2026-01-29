/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/houses/mayor.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

string
sign()
{
  return "\n+-----------------------------------------------------+\n"+
         "| o                                                 o |\n"+
         "|   C I ' U ' B O R I   M A Y O R ' S   O F F I C E   |\n"+
         "|                                                     |\n"+
         "|     We have lots of jobs for you brave one, just    |\n"+
         "|   ask for them and you will be able to experience   |\n"+
         "|                 adventures unlimited.               |\n"+
         "| o                                                 o |\n"+
         "+-----------------------------------------------------+\n\n";
}

void
create_room()
{
  	set_short("Mayor's office");  
  	set_long("This is the mayor's office in Ci'u'bori. The mayor here "+
           	"has much power. He carry out the king's orders, collects "+
           	"the taxes (taking his share) and is also a very important "+
           	"business man. The office itself is stunning. Gold and gem "+
           	"stones everywhere, and in the middle of it stand is a huge "+
           	"desk, filled with heaps of documents. Some stairs leads up "+
           	"to the upper floor, the mayor's private flat. There's a "+
           	"sign on one of the walls.\n");  

  	add_item("desk","It's a very impressive oak desk, must have costed a "+
    		"fortune.\n");
  	add_item(({"gold","gemstones"}),"Lot's of it. A bit tasteless in your "+
    		"opinion.\n");
  	add_item(({"heap","heaps","papers"}),"The desk is full of them, and on "+
    		"you can see the king's insignia.\n");
  	add_item("office","Impressive, that's the word for it.\n");
  	add_item("sign","There's some readable text on it.\n");
  	add_item("ciubori","The third largest city in Cirath.\n");
  	add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    		"and very well-kept. The city looks very wealthy.\n");
  	add_cmd_item("sign","read","@@sign");

  	INSIDE;

  	add_exit(CIU_STR + "tstreet3", "east", 0, 1);
  	add_exit(CIU_HOU + "mayorpriv.c", "up", 0, 1);
  	reset_room();
}
