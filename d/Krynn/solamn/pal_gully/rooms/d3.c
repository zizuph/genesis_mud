/* 
 * Games Room of the Dewar Caverns
 * d3.c
 */

#include <macros.h>
#include "../local.h"
#include CLOCKH

inherit PAL_DEWAR_BASE; 

object dwarf1;
object dwarf2;
object dwarf3;

/*
 * Function name: reset_pal_dewar_room
 * Description  : Resets the room
 */
void
reset_pal_dewar_room()
{
    if (!objectp(dwarf1))
    {
        dwarf1 = clone_object(LIV + "dewar");
        dwarf1->move(TO);
    }
    if (!objectp(dwarf2))
    {
        dwarf2 = clone_object(LIV + "dewar");
        dwarf2->move(TO);
    }
	if (!objectp(dwarf3))
    {
        dwarf3 = clone_object(LIV + "dewar");
        dwarf3->move(TO);
    }
}

/*
 * Function name: create_pal_dewar_room()
 * Description  : Constructor for the room, modify this to change room.
 */
void 
create_pal_dewar_room()
{
    set_short("Games Room");
    set_long("The home of the Dewar Dwarves. "
    +"The walls of the caverns are smooth and well "
    +"carved. This appears to be a common room for "
    +"gathering and playing games or slaughtering "
    +"small animals. The floor is covered in blood "
    +"stains and small tables and desks are set up "
    +"with steins and cards. This room is lit with "
    +"oil lanterns attached to the walls.\n");
    
    add_item(({"desk", "desks", "tables", "table"}), "Small wooden desks "
    +"and tables. Set upon them are steins filled with mead and "
    +"decks of cards that have been used for gambling.\n");
	add_item(({"stein", "steins"}), "Well-crafted glasses used for drinking "
    +"whatever the Dewar are in the mood to drink.\n");
    add_item(({"cards", "deck of cards", "deck", "card", "decks"}), 
    "Standard playing cards. 52 cards in a deck, four suits and two colours.\n");
	add_item(({"mead", "meads", "cups of mead", "steins of mead"}), "The "
	+"current drink of choice for the Dewar. Ale which has been fermented "
	+"using honey rather than another type of sugar. Sweat, alcoholic, "
	+"and expensive to make.\n");
   
      
    add_exit(RDIR + "d4","northwest",0);
    add_exit(RDIR + "d2","east",0);
    reset_pal_dewar_room();
    
}