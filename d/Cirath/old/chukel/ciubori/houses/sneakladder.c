/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/houses/sneakladder.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
  	set_short("On a ladder");  
  	set_long("You're standing on a ladder leading downwards into the darkness. "+
           	"Upwards, you can see some light.\n");  
           
  	add_item("ladder","It's a wooden ladder leading down.\n");

  	INSIDE;

  	add_exit(CIU_HOU + "home3","up");
  	add_exit(CIU_HOU + "sneakroom","down");
  	reset_room();
}

