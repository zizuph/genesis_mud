/*
* Created by: 
* Date: 
*
* File: /d/Cirath/katakoro/desert/desert7.c
* Comments: edited by Luther Oct. 2001
*/


inherit "/std/room.c";
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>

void
create_room()
{
  	set_short("Northern Wastelands");
  	set_long("This is the base of a hill among many hills scattered "+
		"throughout the wastelands of the north. Only the patches of "+
		"white snow, green grass and brown dirt break up the seemingly "+
		"unchanging view.\n");
	
	OUTSIDE;
  
   	add_exit(KAT_DES + "desert6","northeast", 0, 1, 1);
   	add_exit(KAT_DES + "desert8","northwest", 0, 1, 1);
	reset_room();
}
