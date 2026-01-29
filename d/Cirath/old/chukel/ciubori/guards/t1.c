/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/guards/t1.c
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
  	set_long("You stand at the top of the northwestern tower in Ciubori. You have "+
           	"an excellent view from here. North, you can see the river Durni flowing "+
           	"slowly and a jungle. To your west lies the marches.\n");  

  	add_item(({"river","durni"}),"It's big.\n");
  	add_item(({"march","swamp","marches"}),"They're wet.\n");
  	add_item("tower","You are standing at the top level of the tower.\n");
  	add_item("ciubori","The third largest city in Cirath.\n");

  	OUTSIDE;

  	add_exit(CIU_GUA + "g1","down");
  	reset_room();
}
