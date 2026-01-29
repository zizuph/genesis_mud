/*
* Created by: 
* Date: 
*
* File: /d/Cirath/katakoro/waste/kalad_connect.c
* Comments: edited by Luther Oct. 2001
*/


inherit "/std/room.c";
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>

void
create_room()
{
   	set_short("The endless wastes");
   	set_long("Long, majestic plains seem to roll endlessly into the "+
           	"distance. The only sign of civilization is the worn path "+
            	"below your feet. This hill slowly ascends to the "+
            	"southeast.\n");
   	add_item("plains", "They seem endless.\n");
   	add_item("path", "It is a trade rout.\n");

   	OUTSIDE;
   
   	add_exit(KAT_WASTE+"w4", "southeast");
   	add_exit(KAT_WASTE+"w2", "northwest");
}
