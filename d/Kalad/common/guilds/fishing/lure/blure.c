 /*****************************************************************************
*  /d/Kalad/common/guilds/fishing/bait/blure.c
*
*  Lure File: Basic Lure
*
*  Created November 2020, Greneth        
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

	set_name("basic lure");
	add_name("lure");
	add_name("green lure");
	add_name("_fishing_lure");
	add_name("_basic_lure");
	set_short("basic lure");
	set_long("A simple, green earthworm shaped lure with a hook inside it.\n");	
}