// wall_sair     /d/Avenir/common/dead/wall_sair.c
// Creator       Lilith, Sep 2021
//               A Sair Wall for the Catacombs, made with the crypt_placer in mind.
//               If you figure out how to activate it, a pleased Sair may
//               move you through the wall to another place (33% chance)
//               More proof of the existence of the Gods of Sybarus, this
//               will probably freak out anyone who is in the room ;)
// 
#pragma strict_types

inherit "/d/Avenir/common/obj/sair_wall"; 
#include "/d/Avenir/smis/sys/statserv.h"
#include "../dead.h"

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
        +"has been carved into the wall.\n";	
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
        return "There is an octagon carved into the wall. This is a "
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
	
	// two thirds of rooms are in the catacombs,
	// all but one is on the Necronisi
	set_sair_dest(({ SAIR_CENTER, PATH+"entry", BARROW+"barrow1",
               CRYPT+"crypt15", CRYPT+"crypt44", CRYPT+"crypt93", 
			   CRYPT+"crypt80", CRYPT+"crypt110", CRYPT+"crypt22"}));		
	set_name("_Avenir_Sair_Wall");
	add_name(({"wall", "catacomb wall", "limestone wall"})); 
	set_long("It is carved into the limestone of the island, same as "
	    +"all the other walls. It is mostly smooth but there are rough "
		+"patches here and there.\n");
	add_item(({"patch", "rough patch", "patches", "rough patches" }), 
	    "@@sair_search");
	add_cmd_item(({"wall","patch","patches"}),({"feel","touch","search"}),
    	"@@sair_search");
    add_item(({"carving", "octagon"}), 
	    "@@sair_symbol"); 
	
	
}
