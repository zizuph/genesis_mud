/* 
   Bronze room in the Crystalline palace of the Calians.

   History:       
            6/4/96     tidied up kroug handling        Maniac
            122/12/95    vandalism possibility added   Maniac
            22/9/95     kroug raid code installed     Maniac     
            8.12.94     Minor changes                 Maniac
*/


#pragma save_binary

inherit "/d/Calia/std/kroug_palace_room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "/d/Calia/std/vandalism.c"

object calian = 0;

void
reset_room()
{
    if(calian) return;
    calian = clone_object(MONSTER("bronze_calian"));
    calian->move(THIS);
    tell_room(THIS, QCTNAME(calian) + " arrives.\n");
}

void
create_room()
{
    set_short("The bronze room");
    set_long(
	"This is a trapezoidal room whose west and south walls slant away " +
	"from you to the northeast.  " +
	"The walls are covered with bronze wallpaper, but strangely the bed " +
	"is brass.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(ROOM("light_gold"), "west", 0);
    add_exit(ROOM("light_lightroom"), "south",  0);
    add_exit(ROOM("light_sleepless"), "northeast", 0);

    add_item(({"wall", "walls", "wallpaper"}), "Bronze wallpaper covers " +
              "the walls here. It seems to be in perfect condition.\n");

    add_item_possible_vandalism("wallpaper", "Bronze wallpaper covers " +
              "the walls here.",
              ({"smear", "tear"}), 30); 

    add_item("bed", "The brass bed has bronze colored sheets. It seems " +
             "to be in perfect condition.\n");

    add_item_possible_vandalism("bed", "The brass bed has bronze colored " +
                                       "sheets.", ({"break"}), 30);
    reset_room();
}

void
init()
{
    ::init();
    init_vandalism();
}

