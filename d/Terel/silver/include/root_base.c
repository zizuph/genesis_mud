
/* File         : /d/Terel/silver/include/root_base.c
 * Creator      : Pasqua
 * Date         : April 2006         
 * Purpose      : Base file for upcomming root system
 *                in the New Silver Forest.
 * Related Files: 
 * Comments     : Taken from Tomas /d/Terel/silver/include/
 *                road_base.c file
 * Modifications: 
 */


#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
inherit STDROOM;
#include <stdproperties.h>



public void
create_room()
{
    ::create_room();
	INSIDE;
    set_short("A tunnel within the root system");
    set_long("You find yourself standing in a tunnel within some sort of " +
             "rootsystem. These roots grow where the water, minerals and oxygen " +
             "can be found in the soil beneath the ground of the silver forest. " +
             "Even though the temperature above the soil is cold, the root walls " +
		     "gives the impression that they feel all fine even though someone " +
		     "have shaped a tunnel within these roots.\n");

    add_item(({"walls","root walls","wall","root wall","ceiling","ground"}),
       "The root looks healthy and living.\n");

    reset_room();

}



