 /*****************************************************************************
*  /d/Kalad/common/guilds/fishing/bait/earthworm.c
*
*  Bait File: Earthworm Bait
*
*  Created June 2019, Greneth        
*
 *****************************************************************************/

 /*****************************************************************************
*  Includes
 *****************************************************************************/
#include "/d/Kalad/common/guilds/fishing/defs.h"

 /*****************************************************************************
*  Inherits
 *****************************************************************************/
inherit "/std/object";

 /*****************************************************************************
*  Function name: create_object
*  Description  : Constructor for the object
 *****************************************************************************/
void create_object()
{

	set_name("earthworm");
	add_name("worm");
	add_name("bait");
	add_name("_fishing_bait");
	add_name("_earthworm_bait");
	set_short("earthworm");
	set_long("A slimy and wriggling earthworm that would be perfect to use "
	+ "for fishing bait.\n");	
}