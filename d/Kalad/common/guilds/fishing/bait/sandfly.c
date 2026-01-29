 /*****************************************************************************
*  /d/Kalad/common/guilds/fishing/bait/sandfly.c
*
*  Bait File: Sandfly Bait
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

	set_name("sand fly");
	add_name("fly");
	add_name("bait");
	add_name("_fishing_bait");
	add_name("_sandfly_bait");
	set_short("sand fly");
	set_long("One of the bloated sand flies found in the salt flats.\n");
		
}