/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/guards/t4.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "defs.h"
#include <macros.h>
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{ 	
    object npc = present ("guard", TO);
    if(!objectp(npc))
	{
    	  //  bring_room_mob("guard", CIU_NPC + "c_guard", 1, 1);
	}
}

void create_room()
{
  	set_short("guard tower");
  	set_long("You stand at the top of the southwestern tower in Ciubori. You have "+
           	"an excellent view from here. North, you can see the city and to your "+
           	"south lies the pier and the ocean.\n");  

  	add_item("pier","It's where the boats load and unload cargo and passagers.\n");
  	add_item("ocean","It seems never ending.\n");
  	add_item("tower","You are standing at the top level of the tower.\n");
  	add_item("ciubori","The third largest city in Cirath.\n");

  	OUTSIDE;

  	add_exit(CIU_GUA + "g4","down");
  	reset_room();
}
