/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/guards/g1.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "defs.h"
#include <macros.h>
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
//	bring_room_team(CIU_NPC + "c_guard", 3);
}

void 
create_room()
{
  	set_short("guard tower base");  
  	set_long("This is the ground floor inside one of the four towers that are used "+
           	"by the guards of Ciubori to scan the surroundings in order to discover "+
           	"enemies early. The tower itself is made by stone blocks, neatly put "+
           	"together. Here is the place where the guards, which aren't at duty, rest "+
           	"and eat.\n");  

  	add_item(({"stone","stones","block","blocks"}),"They are perfectly put together.\n");
  	add_item("tower","You are standing at the bottom level of the tower.\n");
  	add_item("ciubori","The third largest city in Cirath.\n");

  	INSIDE;

  	add_exit(CIU_STR + "tstreet1", "southeast", 0, 1);
  	add_exit(CIU_GUA + "t1", "up", 0, 1);
	reset_room();
}
