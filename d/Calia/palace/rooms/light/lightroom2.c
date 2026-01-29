
/* 
   Light room, swords of darkness get turned into swords of light 
   here, this is part of the sword of light quest. 

   Coders: Glykron & Maniac 

   History: 
           28/1/2001    dark to light transform updated     Maniac 
            24/3/99     updated sword of light change       Maniac 
             6/4/96     tidied up kroug handling            Maniac 
             5/1/96  s.o.l bug sorted                       Maniac 
            22/9/95  Kroug raid code installed              Maniac 
*/

#pragma save_binary 

inherit "/d/Calia/std/kroug_palace_room"; 
#include <stdproperties.h> 
#include <macros.h> 
#include "defs.h" 


void 
create_room() 
{ 
    set_short("The room of light"); 
    set_long(
	"This is a small trapezoidal-shaped room whose north and south walls " +
	"slope away from you to the east.  " +
	"The light in this room is so dazzling that you cannot make out any " +
	"other details.  " +
	"\n"); 
    add_prop(ROOM_I_INSIDE, 1); 
    add_prop(ROOM_I_TYPE, ROOM_NORMAL); 
    add_prop(ROOM_I_LIGHT, 3); 
    add_exit(ROOM("light_stairs"), "west", 0); 
    add_exit(ROOM("light_hardware_shop"), "east", 0); 
    add_exit(ROOM("light_bronze"), "north", 0); 
    add_exit(ROOM("light_post"), "south", 0); 
}


/* 
 * Function:     check_weapons_of_darkness 
 * Description:  Tries to transform each "weapon of darkness" (from 
 *               the Calia domain) in the player's inventory to a weapon 
 *               of light. 
 */ 
private void 
check_weapons_of_darkness(object player) 
{ 
    object wep; 

    if (objectp(player) && (environment(player) == this_object())) { 
        while (objectp(wep = present("_calia_weapon_of_darkness", player))) 
            wep->effect_transformation(1); 
    } 
} 


/* Handle the sword of darkness to light transformation */ 
void 
enter_inv(object ob, object from) 
{ 
    ::enter_inv(ob, from); 

    if (interactive(ob)) 
        set_alarm(0.0, 0.0, &check_weapons_of_darkness(ob)); 
} 
