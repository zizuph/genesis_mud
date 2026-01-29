/* 
 * Block Room of the Dewar Caverns
 */

#include <macros.h>
#include "../local.h"
#include CLOCKH

inherit PAL_DEWAR_BASE; 

object dwarf1;

/*
 * Function name: reset_pal_dewar_room
 * Description  : Resets the room
 */
void
reset_pal_dewar_room()
{
    if (!objectp(dwarf1))
    {
        dwarf1 = clone_object(LIV + "dewarthane");
        dwarf1->move(TO);
    }
}

/*
 * Function name: create_pal_dewar_room()
 * Description  : Constructor for the room, modify this to change room.
 */
void 
create_pal_dewar_room()
{
    set_short("Throne Chamber");
    set_long("This small comfortable chamber is that "
    +"of the current Thane of the Dewar. While Dewar "
    +"do not have a seat at the table of the dwarven "
    +"realms, their Thane is no less revered. In this "
    +"case, cruelty and thirst for blood are important "
    +"features. The room is barren except for a small "
    +"throne in the corner and a massive desk with instruments "
    +"of death resting upon them. Diagrams and "
    +"schematics are upon the wall and the room is lit using "
    +"oil lanterns attached to the walls.\n");
    
    add_item(({"diagrams", "diagram", "plans", "plan", "plan of attack", 
    "attack plans"}), "Diagrams of infiltration techniques, entry points and "
    +"tactical plans are attached to the walls near the front of the room. "
    +"It appears the Dewar are planning an attack on someone.\n");
    add_item(({"schematics", "schematic", "schematics of a mine", "mine"}),
    "Floor plans and a layout of an old abandoned mine are up on "
    +"the wall near the attack plans. They show where the refuse and "
    +"garbage has and should be dumped, and where they must eliminate "
    +"the Aghar Dwarves in order to reclaim their dumping site.\n");
    
    add_item(({"throne", "small throne", "chair"}), "Small but well made, "
    +"this orante throne has symbols of a dwarf with a crown "
    +"upon his head.\n");
	add_item(({"symbol", "symbols","carving", "carved", "intricate carving",
	"image", "gilded crown", "crown"}),"Carved intricately into the throne "
	+"is an image of a Dwarf being coronated. The gilded crown being lowered "
	+"onto the Dwarves head.\n");
    add_item(({"instruments", "instruments of death"}), "Knives, axes, "
    +"whips and other nefarious instruments coated in dried blood "
    +"rest on the table. It seems this is the one responsible for the "
    +"torture that has been happening.\n");
	add_item(({"desk", "desks", "tables", "table"}), "A large wooden desk "
    +"with instruments of death resting upon it.\n");
    
    
    add_exit(RDIR + "d15","northwest",0);
    reset_pal_dewar_room();
    
}