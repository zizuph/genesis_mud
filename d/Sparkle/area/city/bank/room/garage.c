/*
 * /d/Sparkle/area/city/bank/room/garage.c
 *
 * This is the garage for the bank of Sparkle
 * This is where the bank vehicle will be stationed, maybe someday.
 *
 * Created March 2009, by Aeg (Matthew Morin)
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

inherit BANK_ROOM + "bank_standard"; /* inherit basic bank file */


/*
 * Function name:           create_bank_room
 * Description  :           Creates a room with bank settings
 */
public void
create_bank_room()
{
    set_short("Unfinished garage");
    set_long("This is a dirty garage of the main branch of the Gnomes of Genesis. The floor is made of dusty colored stone, and marked with cracks and oil stains. There are two wheel stains leading to and from two large double doors to the south. The walls and ceiling are made of a rust-colored brick. They are marked with scorch marks and stains of an unknown origin.\n");

    add_item( ({ "room", "garage", "unfinished garage" }),
        "The garage appears to be the place where mechanical work is done for mobile vehicles of the bank. A workbench with tools is on the the northwest wall. Gadgets and heaps of materials are strewn around the room.\n");
    add_item( ({ "wall", "walls" }),
        "Which wall would you like to examine?\n");
    add_item( ({ "north wall", "east wall", "southeast wall", "south wall",
                "southwest wall", "west wall", "northern wall",
                "eastern wall", "southeastern wall", "southern wall",
                "southwestern wall", "western wall" }),
        "The walls are made of rust colored bricks and are covered in scorch marks and stains of unknown origin.\n");
    add_item( ({ "northeast wall", "small door", "wooden door",
                 "northeast door", "northeastern wall",
                 "northestern door" }),
        "A wooden door leads back into the bank. It is sturDy looking and quite thick On the inside of the door are blast marks from explostions that went  bad in here. A lesser than simple metal brace holds it together.\n");
    add_item( ({ "brace", "metal brace" }),
        "This unnecessarily complicated metal brace holds the wooden door together. A handle is hanging on the right side.\n");
    add_item( ({ "handle" }),
        "This handle looks like a temporary fix to a broken handle. It is just a piece of scrap metal crudely attached to the door.\n");
    add_item( ({ "northwestern wall", "northwest wall", "dark dust",
                "dark spot", "different shade", "northwest corner",
                "behind workbench" }),
        "A dark spot reveals a small hole in the wall, just hidden behind the workbench.\n");
    add_item( ({ "floor", "ground" }),
        "The floor is made of cracked gray stone and covered with dust. The floor in the center of the room has the dust caked into a mess with oil splotches, but in the corners it is dusty and easily kicked around. A drain is placed in the center of the room.\n");
    add_item( ({ "gray stone", "stone", "dusty stone", "grey stone" }),
        "The floor stone is cracked, dusty and very poorly maintained. It is pock-marked with oil stains and junk.\n");
    add_item( ({ "cracks", "oil stains", "oil", "stains", "scorch marks",
                "marks", "scorches", "scorch", "crack" }),
        "Cracks, stains, and marks litter the walls and floor. What a mess!\n");
    add_item( ({ "doors", "door" }),
        "Which door, the wooden door the metal doors?\n");
    add_item( ({ "double doors", "double-doors", "metal doors",
            "metal door", "machine door", "mechanized door", }),
        "Two large double doors stand to the south. They are made of a thick metal and look impenetrable. Two wheel tracks lead toward the door, A mechanism hangs over the doors, which must be used to open them.\n");
    add_item( ({ "brick", "bricks", "clay", "rust bricks", "rust brick",
                "rust colored bricks", "rust colored brick" }),
        "These blocks are made of kiln-baked clay. They are the color of rust.\n");
    add_item( ({ "ceiling" }),
        "The ceiling is made of rust-colored, red brick.\n");
    add_item( ({ "dust" }),
        "The dust covers the ground. it appears to be soot and has  settlled on the ground. The dust appears to be a different shade in the northwestern corner of the garage.\n");
    add_item( ({ "drain" }),
        "Malodourous wisps drift up from the drain. It is made of iron and appears to be broken. It appears that small items or creatures could fit through the gaps.\n");
    add_item( ({ "workbench", "bench" }),
        "A workbench has been placed near the northwest corner. It is covered with coffee-stained blueprints and greasy, incomplete contraptions. Seemingly random tools weigh the blueprints to the surface.\n");
    add_item( ({"blueprints", "prints"}),
        "The undecipherable scribble seems less meaningful than the rings of coffee that mark the papers.\n");
    add_item( ({"scribble"}),
        "It is some type of writing that seems undecipherable, and made of uf what seem,s to be random pitucres..\n");
    add_item( ({ "rings", "coffee rings", "coffee stains",
                 "rings of coffee" }),
        "Faded rings of coffee stain the blueprints. They seem arranged in an unintentional artistic form.\n");
    add_item( ({ "tools" }),
        "Hammers, picks, screwdrivers, beakers and various other items lie around the room and workbench. They are either carelessly, or extremely meticulously, placed. Hard to tell...\n");
    add_item( ({ "contraption", "contraptions", "gadgets", "gadget",
                 "heap", "heaps" }),
        "Bells, levers, buttons... spinny thingies... They are gnomish in nature and seem useless.\n");
    add_item( ({ "hole", "small hole", "secret exit" }),
        "An ominous hole leads into the wall. Perhaps you could crawl through?\n");
    add_item( ({ "gap", "gaps" }),
        "Yes, they are large enough for you to squeeze through. The gap looks disgusting.\n");

    add_cmd_item(({"hole", "through the hole", "through hole", "thru hole",  
        "thru the hole", "in the hole", "in hole", "into hole" }), 
        "crawl", "@@crawl");
		
/* 
 *   April 2019: Not ready for this yet 
 *
 *   add_cmd_item(({"gap", "through the gap", "thru gap", "thru the gap",
 *        "through gap", "through the gaps", "in gap" }),
 *        "squeeze", "@@squeeze");
 *
 */
		
    add_tell("Scratching and hooting noises echo from the walls.\n");
	add_tell("A horrible smell seeps from the drain in the center of the garage.\n");
    add_tell("Something scurries around the workbench.\n");
	add_tell("Muffled noises ascend from the drain in the center of the garage.\n");
    add_tell("A small explosion blasts behind you! Turning about, you only see a small plume of wasted debris settling to the ground, with no apparent cause.\n");

    add_prop(ROOM_I_LIGHT, 1); /* lit room */

    add_exit(BANK_ROOM + "line1", "northeast", 0); /* line 1 */
}

public int
crawl()
{
    write("You crawl into the dark hole.\n");
    this_player()->move_living("crawling through the dark hole",
        "/d/Sparkle/area/city/bank/room/garage_hole" );
    return 1;
}

/* April 2019: Not ready for this. Maybe never ready for this. 
 *
 *public int
 * squeeze()
 *{
 *    write("You squeeze through the gap in the drain.\n");
 *    this_player()->move_living("through the gap in the drain",
 *        "/d/Sparkle/area/city/sewer/room/spawning_pools/entrance" );
 *    return 1;
 *}
 */

/*
 * Function name:       reset_room
 * Description  :       restore npcs and signs as needed
 */
public void
reset_room()
{

    object hapertacosh;
	object ornithopter;

    if (!present("hapertacosh"))
    {
//        hapertacosh = clone_object("/d/Sparkle/area/city/bank/npc/hapertacosh");
//        hapertacosh = clone_object(BANK_NPC " +hapertacosh");
        hapertacosh->move(this_object());
    }

	if (!present("ornithopter"))
	{
		ornithopter = clone_object( BANK_NPC + "ornithopter");
		ornithopter->move(this_object());
	}

} /* reset_room */