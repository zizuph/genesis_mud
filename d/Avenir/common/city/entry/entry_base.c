// file name:        /d/Avenir/common/city/entry_base.c
// creator(s):       Lilith, Sept '97
// revisions:	Lucius Oct 2008
//              Lilith Oct 2021: removed TERRAIN_OUTSIDE and changed to 
//                   TERRAIN_UNDERGROUND. Changed to Avenir domain base 
//                   room instead of just std room.
// purpose:          
// note:             This file is to be inherited in all sedan chair rooms.  
//                   The more frequent add_items should be entered here.		     
// bug(s):           
// to-do:            
#pragma strict_types

/* Inherit the standard room object */
inherit "/d/Avenir/inherit/room";

/* Include the local area defines, etc */
#include "../city.h"
#include "/d/Avenir/include/defs.h"

#include <stdproperties.h>
#include <terrain.h>


/* These are the add_items and add_cmd_items for the rooms 
 * (Those used more than once in the area)
 */
void add_courtyard()
{
    add_item(({"courtyard", "triangular courtyard" }),
        "If you are standing here, you have accomplished "+
        "quite a lot.  Getting into the City isn't always easy!\n"+
        "This courtyard is triangular in shape. The base is formed "+
        "by the Gate, while the two sides are formed by the curving "+
        "walls of the Inquisitor's and Executioner's enclaves.\n");
}

void add_gate()
{
    add_item(({"gate", "first gate", "First Gate", "gates", "slabs" }),
        "The First Gate dominates this area of the City, easily "+
        "visible from quite a distance away. It is made of pale "+
        "granite that gleams whitely in the light of the Source. "+
        "The slabs are so tremendously large that you can't help "+
        "but wonder what feats of engineering were necessary to "+
        "accomplish their placement. A golden trefoil, the symbol "+
        "of Sybarus, has been carved into the stone.\n");
    add_item(({"trefoil", "golden trefoil", "trefoil carved into "+
        "the stone", "trefoil on gate"}), 
        "A mind-boggling amount of gold has been used to create "+
        "the golden trefoil carved into the stone of the gate. "+
        "Since the City itself appears to be trefoil-shaped, "+
        "you now understand why it is the symbol of Sybarus.\n");

}

void add_stones()
{
    add_item(({"stones", "cobblestones"}),
        "The cobblestones of the courtyard look like they are made "+
        "of semi-precious stones such as jasper and carnelian, probably "+
        "pieces left over from the building of the City walls.\n");
}

void add_paths()
{
    add_item(({"path", "stone path", "south path", "rainbow path", "city path"}),
        "Each coloured band of stone represents that path toward a "+
        "area of the city.\n");
    add_item(({"purple", "purple stones", "purple path", "purple swath", "hegemon"}),
        "The purple swath of stones curves toward the Ziggurat and "+
        "continues beyond it, leading to the enclave of the Hegemon.\n");
    add_item(({"green", "green stones", "green path", "green swath", "inquisitor"}),
        "The green swath of stones curves toward the Ziggurat, but "+
        "turns west, at a break in the wall leading into the "+
        "enclave of the High Lord Inquisitor.\n");
    add_item(({"red", "red stones", "red path", "red swath", "executioner"}),
        "The red swath of stones curves toward the Ziggurat, but "+
        "turns east, at a break in the wall leading into the "+
        "enclave of the High Lord Executioner.\n");
    add_item(({"yellow", "yellow stones", "yellow path", "yellow swath"}),
        "The yellow swath of stones leads directly to the Ziggurat, "+
        "the pleasure palace of Sybarus.\n");
    add_item(({"blue path", "blue stones", "blue slate", "blue slate path"}),
        "This path flows from the Gate to the Bath.\n");
}

void add_source()
{
    add_item(({"Source", "source", "light", "illumination", "skein", 
        "glow", "above", "sky", "ceiling", "cavern ceiling"}),
        "High above, in the ceiling of this great cavern, is "+
        "a glowing skein of mineral that emits yellow-white light.\n");
}   

void add_urns()
{
    add_item(({"urn", "urns", "large urns" }),
        "You might think these urns had been placed randomly, were it not "+
        "for the fact that the overall effect of their placement is so "+
        "aesthetically pleasing.  You suspect that a great deal of care "+
        "was used in determining just the right spot so that the flowers "+
        "and plants contained within them are shown to their best effect "+
        "against the clean lines of the City.\n");
}

void add_zig()
{
    add_item(({"ziggurat", "palace", "pleasure palace"}),
        "The Ziggurat is built of black stones laid upon each other "+
        "to form a terraced pyramid of successively receding stories. "+
        "It has several visible levels, each of which appears to be a "+
        "garden.\n");
}

void add_bath()
{
    add_item(({"low building", "domed building", "low domed building",
        "bath", "bathhouse", "melchior's", "melchior's bath"}),
        "This place is what you've been hearing about all this time: "+
        "Melchior's Bath House. The building itself is unprepossessing: "+
        "a large, low dome seated within an outcropping of natural "+
        "stone. The dome appears to be constructed of glass that "+
        "is opaque from the steam of the warm waters within.\n");
}

void add_walls()
{
    add_item(({"walls", "wall", "chalcedony", "chalcedony walls",
       "city walls"}),
       "The walls of the Forbidden City are made from blocks of "+
       "stone from the chalcedony family of minerals: agate, "+
       "bloodstone, carnelian, chrysoprase, jasper, onyx, prase, "+
       "and sardonyx. Randomly placed, they are rectangular with "+
       "each one standing the height of a tall elf and thrice that "+
       "in length. The blocks are glossy as gemstones, making them "+
       "both beautiful and deadly difficult to climb.\n");
    add_cmd_item(({"wall", "walls", "block", "blocks"}), "climb",
       "Under the watchful eyes of the guards you casually approach "+
       "the wall. A cursory examination reveals that without the "+
       "proper equipment this wall would be impossible to climb.\n");
    add_cmd_item(({"walls", "walls", "block", "blocks"}), 
       ({"feel", "touch"}),
       "It is cool and smooth to the touch, with nary a crack or "+
       "a chip to mark the flawless finish.\n");
}

void add_paths_inner()
{
    add_item(({"path", "stone path", "south path", "rainbow path",
	"city path"}),
	"Each coloured band of stone represents that path toward a "+
	"area of the city.\n");
    add_item(({"purple", "purple stones", "purple path", "purple swath",
	"hegemon"}),
        "A purple swath of stones curves around the Ziggurat and "+
        "continues south beyond it, leading to the enclave of the Hegemon.\n");
    add_item(({"green", "green stones", "green path", "green swath",
	"inquisitor"}),
        "A green swath of stones curves west ahead of the Ziggurat, then "+
        "through a break in the wall leading into the "+
        "enclave of the High Lord Inquisitor.\n");

    add_item(({"red", "red stones", "red path", "red swath", "executioner"}),
        "A red swath of stones curves east ahead of the Ziggurat, then "+
        "through a break in the wall leading into the enclave of the "+
	"High Lord Executioner.\n");

    add_item(({"yellow", "yellow stones", "yellow path", "yellow swath"}),
        "A yellow swath of stones runs between the Ziggurat, "+
        "the pleasure palace of Sybarus, and the First gate.\n");
}

void add_outside()
{
    add_source();
    add_courtyard();
    add_gate();
    add_stones();
    add_paths();
    add_item(({"outcrop", "outcropping"}),
        "Though much of the island has been cleared for the building of "+
        "the Forbidden City, here and there you can see places where the "+
        "natural stone of the island has not been leveled, but rather, "+
        "allowed to remain, providing a contrast between the orderly "+
        "works of man and nature's chaos.\n");
}

void add_inside()
{
    add_zig();
    add_gate();
    add_urns();
    add_walls();
    add_source();
    add_paths_inner();
}

/*
 * Function name: create_admin_room
 * Description:   This function should be used for creating cave rooms.
 */
void create_entry_room() { }

/*
 * Function name: create_domain_room
 * Description:   This function creates a SMIS-enabled room.
 */

/*
 * Function name: reset_entry_room
 * Description:   This function should be called to reset tunnel rooms.
 */
void reset_entry_room()
{
    reset_domain_room();
}

/* Initialize the std domain room and the SMIS-enabled stuff. */
void create_domain_room()
{
    /* If an add_item will be in every room, add it here */

    LIGHT;
    IN;

    set_terrain(TERRAIN_UNDERGROUND | TERRAIN_COOL | TERRAIN_SHADOWS | TERRAIN_ONVEHICLE);

    create_entry_room();
	reset_entry_room();
}
