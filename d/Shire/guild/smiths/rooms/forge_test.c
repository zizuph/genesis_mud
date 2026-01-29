/*
    
   Template Forge Room

   Use this room as an example for making a forge in your domain.
   You probably want to change inherit "/std/room" to your custom room code


   15 Aug 2006 - Palmer

 */
 
#pragma strict_types;

inherit "/std/room";
inherit "/d/Shire/guild/smiths/rooms/base_forge_room";
#include "/d/Shire/guild/smiths/smiths.h"

void
create_forge_room()
{
    set_short("The an example forge of the Smiths Guild");
    set_long("This is an exmample forge of the Smiths guild. It " +
        "is the pride of the Guild, allowing Smiths to forge many " +
        "items. The forge burns hot, so windows are open to allow " +
        "fresh air to blow through. Forging tools are available for " +
        "anyone with the skills to forge. A brass sign hangs on " +
        "one wall.\nA brass sign.\n");

    set_room_tell_time(300);
    add_room_tell("A cool breeze blows in the door, cooling " +
        "the room slightly.");
    add_room_tell("An apprentice smith comes and stocks the " +
        "forge with more coal.");
    add_room_tell("Some raucous sounds float in from the windows.");
    add_room_tell("The sound of a creaking cart rolls by " +
        "outside the window.");
    add_room_tell("An apprentice smith empties the barrels full " +
        "of dirty water and refills them with water from the " +
        "large barrel.");
    add_room_tell("An apprentice checks the water level in the " +
        "large barrel.");
    add_room_tell("As it begins to rain outside, the rainwater " +
        "begins to fill the large barrel. Soon the rain stops.");

    
}

