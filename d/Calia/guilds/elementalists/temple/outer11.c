/*
 * Outer Circle of the Elemental Temple of Calia
 * 
 * Created by Petros, April 2010
 * 
 * Updated 2/24/2016 by Leia, based on suggestions from TT
 */

#pragma strict_types

#include "defs.h"

inherit TEMPLE_ROOM_BASE;

// Defines

// Prototypes


public string
generate_desc(object THIS_PLAYER)
{
	if ((THIS_PLAYER->query_skill(109)) <= 30)
	{
		return "The glyphs are ancient and eroded. You are not able to decipher them.\n";
	}
	
	else if ((THIS_PLAYER->query_skill(109)) <= 50)
	{
		return "You recognize the glyphs as an ancient form of text and make out parts of them: "
			+ "... mountain ... island ... .me.\n";
	}
	
	else if ((THIS_PLAYER->query_skill(109)) <= 80)
	{
		return "You recognize the glyphs as an ancient form of text, native to Calia, and make out "
			+ "most of them: From mount Kyrus ... this island ... we were saved ... new home.\n";
	}
	
	else if (((THIS_PLAYER->query_skill(109)) > 80) || IS_MEMBER(THIS_PLAYER))
	{
		return "You recognize the glyphs as an ancient form of text, Kyrullian, and they read: "
			+ "From Mount Kyrus to this Island. We were saved. Praise be the Elementals. A new "
			+ "home for us.\n";
	}
	
	else
	{
		return "The glyphs are ancient and eroded. You are not able to decipher them.\n";
	}
	
}

public void
create_temple_room()
{
    set_short("Inside the Elemental Temple of Calia");
    set_long("You stand inside the Elemental Temple of Calia, an ornately "
        + "constructed building that houses those devoted to the service "
        + "of the Elementals. The walls are made from white marble or grey stone "
		+ "while the foundation is made from crystalline. The vaulted ceiling is "
		+ "comprised of wood and supported by mighty columns. A display table is standing here. "
		+ "You see a post office to the southwest.\n"); 
		
	try_item( ({ "table" }),
        "The table is made of wood and has various things put on display.\n");
		
	try_item( ({ "display" }),
	    "The display mostly holds broken stone fragments but you also notice "
		+ "a small statue, a rusty blade and some fragments.\n");
	
	try_item( ({ "fragment", "fragments", "stone fragment", "stone fragments"}),
		"The fragments are ancient and worn down from ages of erosion and show signs of "
		+ "having been underwater for a very long time. The fragments are "
		+ "full of small glyphs most of which are but shaded indentions worn down "
		+ "by time.\n");
	
	try_item( ({"glyph", "glyphs"}),generate_desc(TP));
		
	try_item( ({"statue", "small statue"}),
		"A relatively simple iron statue that has been cast with a flaming red hue. "
		+ "The eyes of the statue has a vague burning yellow glow and seems to follow your "
		+ "every move.\n");
	
	try_item( ({"blade", "rusty blade"}),
		"The blades origin of weapon is hard to determine. It has a thin layer of red rust and. "
		+ "seems very brittle.\n");
	
	try_item( ({"red rust", "rust", "layer", "thin layer"}),
		"The rust seems unnatural somehow and as you look closer it appears to move about, hungrily.\n");

    add_exit(ELEMENTALIST_TEMPLE + "outer9", "north");
    add_exit(ELEMENTALIST_TEMPLE + "gu", "southeast"); 
    add_exit(ELEMENTALIST_TEMPLE + "postoffice", "southwest");
}
