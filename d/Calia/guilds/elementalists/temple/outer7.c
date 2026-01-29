/*
 * Outer Circle of the Elemental Temple of Calia
 * 
 * Created by Petros, April 2010
 *
 * Updated 2/24/2016 by Leia. Added some murals designed by
 * TT.
 */

#pragma strict_types

#include "defs.h"

inherit TEMPLE_ROOM_BASE;

// Defines

// Prototypes

public void
create_temple_room()
{
	set_long("You stand inside the Elemental Temple of Calila, an ornately constructed "
		+ "building that houses those devoted to the service of the Elementals. The walls "
		+ "are made from white marble or grey stone, while the foundation is made from "
		+ "crystalline. The vaulted ceiling is comprised of wood and supported by mighty "
		+ "columns. Murals have been set into the marble wall to your west.\n");
		
	try_item( ({ "murals" }),"There are five murals. You could look at them individually.\n");
	
	try_item( ({ "first mural"}),"A mural from hardened basalt with colored crystalline surfaces, "
		 + "it depicts a cloaked man visiting a small village. The villagers "
		 + "faces are brightening with joy.\n");
		  
	try_item( ({ "cloaked man", "visitor", "hands", "sunlight", "fauna" }),
         "The visitor wears a sturdy granite-coloured cloak and approaches the village "
		 + "hands spread out in a welcoming gesture. The fauna seems to flourish in "
		 + "his presence. \n");
	
	try_item( ({"village", "forest"}),"A small village in a large forest. It is surrounded by "
		+ "disease ridden crops.\n");
		 
	try_item( ({"villagers", "faces"}),"Recognition, relief and joy brightens their faces.\n");
		 
	try_item( ({"second mural"}),"The second mural is made from a black grainy stone with "
		+ "silvery engravings.\n");
	
	try_item( ({"black stone", "stone", "grainy stone", "black grainy stone"}),"The black stone "
		+ "is very grainy to the touch. \n");
	
	try_item( ({"engravings", "silvery engravings"}),"The engravings depict three people sitting "
		+ "at a table. A cloaked woman flanked by two men. \n");
	
	try_item( ({"three people", "people", "table"}),"The two men flanking the woman appear to "
		+ "be in a heavy argument. The cloaked woman appears completely composed. She appears "
		+ "to be arbitrating the men's dispute.\n");
	
	try_item( ({"woman", "cloaked woman"}),"Clad in a brilliant aquamarine cloak she is "
		+ "radiating calm and reason.\n");
		
	try_item( ({"third mural"}),"The mural is made from polished grey stone with simple coloring. "
		+ "On it a figure is standing in a smithy, a hammer held high over a smouldering iron "
		+ "piece.\n");
		
	try_item( ({"figure"}),"The figure is a woman wearing a ruby red cloak. Her eyes and cloak "
		+" seem to flicker in unison with the blazing furnace fire.\n");
	
	try_item( ({"smithy", "fire", "furnace"}),"The smithy is of a simple build with a blazing "
		+ "furnace that seems to fuel itself somehow.\n");
	
	try_item( ({"iron piece"}),"It appears the figure is crafting a gardening tool of some kind.\n");
		 
	try_item( ({"fourth mural"}),"A mural made from clear white marble with azure-blue veins "
		+"depicting a person standing on a passenger filled boat.\n");
		
	try_item( ({"person"}),"The person is standing up, palms facing the sails. His airy white "
		+ "cloak and the sails billow strongly in return, as if caught in heavy winds. The sea "
		+ "is completely still though.\n");
	
	try_item( ({"boat", "passengers"}),"It is a small sturdy boat, filled with passengers. "
		+ "The passengers appear haggard and tired. Some look famished, some wear torn clothing. "
		+ "You surmise they could be refugees from a calamity of sorts.\n");
		
	try_item( ({"sea", "winds"}),"The deep blue sea is completely still, yet the boat seems "
		+ "to be sailing swiftly, towards an island on the horizon.\n");
	
	try_item( ({"island", "horizon"}),"A small island on the horizon emanates peace and "
		+"calm. It seems to be a sanctuary for the passengers.\n");
	
	try_item( ({"fifth mural"}),"On this crystalline mural, a couple of individuals, one "
		+"cloaked, are sitting across from each other holding hands.\n");
	
	try_item( ({"individuals"}),"One of the individuals, face wrought with concern, is speaking "
		+ "to the second. The cloaked individual seems to be offering counsel and comfort to "
		+ "the first.\n");
	
	try_item( ({"cloaked individual"}),"Grasping the hands of the other while listening intently, " 
		+ "the cloak seems to expand and surround both into a shadow of comfort and reassurance.\n");

    add_exit(ELEMENTALIST_TEMPLE + "outer5", "north");
    add_exit(ELEMENTALIST_TEMPLE + "aeria", "south"); 
}
