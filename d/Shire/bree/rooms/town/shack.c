/*
 * Shack on top of the hill.
 * Finwe, June 2002
 */

inherit "/d/Shire/common/lib/room";

#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>
 
object hermit;

create_room()
{
    set_short("A small shack");
    set_long("You are inside a small shack on top of the Hill. The " +
        "shack is rather clean despite its size and age. Scattered " +
        "about the room are the few possessions of the hermit who " +
        "lives here. Some furniture is scattered about the room " +
        "with a mirror on a wall and a rug on the floor.\n");
    	    
    add_item(({"book shelf","bookshelf","shelf"}),
        "The bookshelf is filled with books. It is made of pine and " +
        "looks sturdy.\n");
    
    add_item("books",
        "There are lots of different books here. One book you notice " +
        "is one with the title 'My Journies to Gondor'. Various other " +
        "books are also there such as gardening, cooking, books on " +
        "travels, and other exciting subjects.\n");
    
    add_item(({"wall", "walls"}),
        "The walls looks strong, compared to what they look like " +
        "outside. They are bare of decorations except for a large " +
        "mirror on one wall.\n");
    		   
    add_item("desk",
        "The desk has some drawers in it, which are closed. It looks " +
        "very old, and the wood it is probably made from oak, a very " +
        "common wood around here.\n");
    
    add_item("drawers",
        "Like the desk, they are made of wood. However, they are " +
        "securely closed.\n");
    
    add_item("chair",
        "This is a wooden chair, made of pine. It is rather plain " +
        "looking and the only chair in the shack. It is next to the desk.\n");
    		    
    add_item("furniture",
        "Looking about the shack, you see a desk in one corner " +
        "with a chair, a bookcase against one wall, and a bed " +
        "against another wall.\n");
    add_item("rug",
        "It is oval shaped and made from twisted pieces of fabric. " +
        "It is multi-colored and adds some color to the room.\n");
    add_item("bed",
        "The bed is nothing special. An old mattress set against " +
        "a wall with some blankets piled on top.\n");
    add_item(({"blankets"}),
        "They are piled up on the bed, dirty and well used.\n");
    add_item(({"mattress"}),
        "The mattress is old and lumpy looking. It is set against " +
        "a wall with some blankets piked on top of it.\n");
	    
    add_prop(ROOM_I_INSIDE,1);
    room_add_object(OBJ_DIR + "mirror");
    
    add_exit(ROAD_DIR +"broad15","out");
        
    reset_room();  
}
  
reset_room()
{ 
    if (!hermit)
    {
        hermit = clone_object(NPC_DIR + "hermit");
        hermit->move(TO);
    }
}

