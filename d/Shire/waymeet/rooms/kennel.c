/* Dog Kennel
 * Not intented for players. Just a set_home() for the dogs.
 * Raymundo, Feb 2020
 */
 
#pragma save_binary
#pragma strict_types

#include "defs.h"
#include "/d/Shire/waymeet/defs.h"
#include "/d/Shire/eastroad/western/local.h"
#include "/d/Shire/waymeet/lib/hobbitmaker.h"
inherit WAYM_LIB_DIR + "base_waymeet.c";





void reset_shire_room();



void
create_waymeet_room()
{
	set_short("A dog kennel.\n");
	set_long("This is a kennel where the dogs of Waymeet go "
		+ "home to.\n");
	
	

	
	
}
void
reset_shire_room()
{
	
}



void
init()
{
	::init();


}
