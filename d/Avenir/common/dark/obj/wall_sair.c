// wall_sair     /d/Avenir/common/dark/obj/wall_sair.c
// Creator       Lilith, Sep 2021
//               A Sair Wall for the Utterdark, made with the crypt_placer 
//               in mind (internally configured rather than post-cloning
//               configured as the usual sair_wall is.
// Notes          If you figure out how to activate it, a pleased Sair may
//               move you through the wall to another place (33% chance)
//               More proof of the existence of the Gods of Sybarus, this
//               will probably freak out anyone who is in the room ;)
// 
#pragma strict_types

inherit "/d/Avenir/common/obj/sair_wall"; 
#include "/d/Avenir/smis/sys/statserv.h"
#include "../dark.h"

//This is where the object dedicated to Sair is.
#define SAIR_CENTER "/d/Avenir/common/dark/l2/add/t36"

/* sair_search()
 * Can be masked for a custom message but don't forget to 
 * add the prop to the player or the place_it() function will
 * always fail.
 * Returns: string - Result from searching the wall in the room.
 */
public string sair_search()
{ 
    this_player()->add_prop("_avenir_found_sair_symbol", 1);
    return "A careful inspection reveals that an octagon shape "
        +"has been chiseled into the wall.\n";	
}
/*
 * sair_symbol()
 * What the player sees when they look at the symbol/octagon.
 * Can be masked for a custom message.
 * Returns: string - symbol description. 
 *
 */ 
public string sair_symbol()
{
    if(this_player()->query_prop("_avenir_found_sair_symbol"))
	{
        return "There is an octagon chiseled into the wall. This is a "
		    +"fairly common practice in Sybarus. It honors the "
			+"Goddess Sair, builder, keeper, and destroyer of walls.\n";
	}
	else
	    return "What?\n";
}    
	

void
create_object()
{
	::create_object(); 
	
	set_sair_dest(({ SAIR_CENTER, OUTPOST+"bridge", DARK+"l1/center", 
	            DARK+"l2/center", DARK+"l3/center", DARK+"l4/center" }));		
	set_name("_Avenir_Sair_Wall");
	add_name(({"wall", "utterdark wall", "walls"})); 
	set_long("It is a wall just like all the others in the Utterdark. "
	    +"There are some chisel marks that seem interesting.\n");
    add_item(({"shape", "octagon", "octagon shape"}), "@@sair_symbol"); 
	add_item(({"marks", "chisel marks"}), "@@sair_search");
	add_cmd_item(({"wall", "marks"}), ({"feel", "touch", "search"}), 
	    "@@sair_search");
		
}
