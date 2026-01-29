/*
 * Jarlaxle NPC/Entrance quest Underdark city
 * by Clyptas, July, 2017
 */
inherit "/std/monster";

#include <macros.h>
#include "/d/Faerun/defs.h"

#define OBJ "/d/Faerun/bootcamp/obj/"


create_monster()
{
    set_name("jarlaxle");

    set_race_name("drow");

    set_adj( ({"stoic"}) );

    set_stats( ({49, 89, 68, 78, 78, 40}) );

    set_alignment(0);

    set_gender(G_MALE);
    
	
	
		equip(({ 
		  (OBJ + "j_hat"),
		  (OBJ + "j_rapier"),
		  (OBJ + "j_cape"),
		  (OBJ + "j_boots"),
		  (OBJ + "j_bracelets"),
		  (OBJ + "j_breeches"),
		  (OBJ + "j_vest"),
    }));
}


	
	
