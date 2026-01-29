/*
 * /d/Sparkle/area/city/bank/room/guard_room.c
 *
 * This is the guard room for the second floor vaults of the main branch
 * of the Gnomes of Genesis in Sparkle.
 *
 * Created Feb 2009, by Aeg (Matthew Morin)
 */
 
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

inherit BANK_ROOM + "bank_standard";

/* Prototypes */
public int 			not_yet();

/*
 * Function name:           create_bank_room
 * Description  :           Creates a room with bank settings
 */
public void
create_bank_room()
{
set_short("Vault guard station");
    set_long("This is the central vault guard station of the Gnomes of "
          + "Genesis. The room is shaped like an irregular hexagon, with "
          + "the southern wall being the largest. Travelling south will "
          + "lead one down a tunnel to the machine room and ultimately to "
          + "the main bank. The other exits lead to what look like vaults. "
          + "Being a guard station, this room is a sort of military post "
          + "with eyes watching your every move.\n\n");
    
    add_item( ({ "room", "area", "guard room", "guard station" }),
            "The room is shaped like an irregular hexagon, with "
          + "the southern wall being the largest. Travelling south will "
          + "lead one down a tunnel to the machine room and ultimately to "
          + "the main bank. The other exits lead to what look like vaults. "
          + "Being a guard station, this room is a sort of military post "
          + "with eyes watching your every move.\n");
          
    add_item( ({ "wall", "walls" }),
            "Yep, the guard station has walls. They look like they are made "
          + "with some thick stone. All of the walls, save the southern wall "
          + "are equally sized. Which wall would you like to examine?\n");
             
    add_item( ({ "north wall", "northern wall", "platinum vault",
				 "platinum coin vault" }),
            "The northern wall is made of solid stone and contains the "
		  + "platinum vault. It is guarded vigilantly.\n");
		  
    add_item( ({ "northeast wall", "northeastern wall", "gem vault",
	    		 "stone vault" }),
            "The northern wall is made of solid stone and contains the "
		  + "gem vault. It is guarded vigilantly.\n");
		  
	add_item( ({ "northwest wall", "northwestern wall", "gold vault",
			 "gold coin vault" }),
            "The northern wall is made of solid stone and contains the "
		  + "gold vault. It is guarded vigilantly.\n");
		  
	add_item( ({ "west wall", "western wall", "silver vault",
			 "silver coin vault" }),
            "The northern wall is made of solid stone and contains the "
		  + "silver vault. It is guarded appropriately.\n");
          
	add_item( ({ "southwest wall", "southwestern wall", "copper vault",
			 "copper coin vault" }),
            "The northern wall is made of solid stone and contains the "
		  + "copper vault. It is guarded appropriately.\n");

    add_item( ({ "coin vault" }),
		    "Which vault would you like to inspect?\n");
		  
	

    /* Exits */
    add_exit(BANK_ROOM + "vault_gem", "northeast", not_yet, 1, 0);
    add_exit(BANK_ROOM + "vault_platinum", "north", not_yet, 1, 0);
    add_exit(BANK_ROOM + "vault_gold", "northwest", not_yet, 1, 0);
    add_exit(BANK_ROOM + "vault_silver", "west", not_yet, 1, 0);
    add_exit(BANK_ROOM + "vault_copper", "southwest", not_yet, 1, 0);
    add_exit(BANK_ROOM + "gear_room_n", "south", 0);    

    
} /* create_bank_room */

/*
 * Function name:        not_yet
 * Description  :        provide a message to the let the player know
 *                       this is currently not a viable exit
 * Returns      :        int 1 - blocked
 */
public int
not_yet()
{
    write("A gnomish guard, who is armed to the teeth, blocks "
		+ "your way.\n");
    return 1;
	
} /* not_yet */
