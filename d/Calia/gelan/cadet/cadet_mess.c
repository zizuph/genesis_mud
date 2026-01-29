
/*
     Cadet mess hall.  

     A room for cadets to get a bite to eat or a drop to drink.

     Coded by Maniac@Genesis, 23/8/97 
 */ 

inherit "/std/room"; 
inherit "/lib/pub"; 

#include <stdproperties.h>
#include <macros.h> 
#include "cadet.h"


int
gc_query_private_room()
{
    return 1;
}


void
create_room()
{
    set_short("Cadets' mess hall");  
    set_long("Several neatly aligned " +
             "matt varnished oak tables run the length of the room, " +
             "each with a stack of earthenware dishes at one end. " + 
             "Alongside them are benches of similar material and finish. " +
             "A little counter with a menu on it stands " +
             "near to a pair of swing doors, through which you can " +
             "hear the clanking of pots and pans. " +
             "There is a sign over the south exit.\n"); 

    add_item(({"south exit"}), "It leads to a sitting room. " +
             "There is a sign over it.\n");  
    add_item(({"sign"}), 
             "The sign reads: Cadets only!\n"); 
    add_cmd_item(({"sign"}), ({"read"}),  
             "The sign reads: Cadets only!\n");  

    add_item(({"doors", "kitchen doors", "swing doors" }), 
            "The swing doors lead to a room from which the clanking " +
            "of pots and pans can be heard. Nearby " + 
            "is a counter with a menu on it.\n"); 

    add_item("counter", "On the counter is a menu.\n");  

    add_item(({"table", "tables", "oak tables", "oak table" }), 
             "These are matt varnished oak tables.\n"); 

    add_item(({"bench", "benches"}), "These are matt varnished oak " + 
             "benches alongside the tables.\n"); 

    add_item(({"stack", "stacks", "dish", "dishes", 
               "earthenware dish", "earthenware dishes" }), 
             "These are plain earthenware dishes.\n"); 

    add_item(({"menu", "pricelist", "prices"}),  
              VBFC_ME("display_menu")); 
    add_cmd_item(({"menu", "pricelist", "prices"}), "read",   
              VBFC_ME("display_menu")); 

    add_prop(ROOM_I_INSIDE, 1); 
    add_prop(ROOM_I_NO_CLEANUP, 1); 
    add_exit(GC_STARTROOM, "northeast");  
    add_exit(GC_DIR+"cadet_sitroom", "south", "@@cadets_only"); 

    add_food(({"apple", "green apple"}), ({"apple"}), ({"green"}),  
             50, 10, "green apple", "green apples",  
             "A green apple.\n"); 

    add_food(({"apple", "red apple"}), ({"apple"}), ({"red"}),  
             50, 10, "red apple", "red apples",  
             "A red apple.\n"); 

    add_food(({"bread", "brown bread"}),  ({"bread", "slice"}), ({"brown"}), 
             100, 22, "slice of brown bread", "slices of brown bread", 
             "A slice of brown bread.\n"); 

    add_food(({"soup", "broccoli soup"}),  ({"soup", "bowl"}), ({"broccoli"}), 
             150, 43, "bowl of broccoli soup", "bowls of broccoli soup", 
             "A bowl of broccoli soup.\n"); 

    add_food(({"drumstick", "chicken drumstick"}), 
             ({"drumstick" }), ({"chicken"}), 
             200, 72, "chicken drumstick", "chicken drumsticks", 
             "A chicken drumstick.\n"); 

    add_food(({"beans", "dish of beans" }), 
             ({"beans", "dish"}), ({ }), 
             250, 110, "dish of beans", "dishes of beans", 
             "A dish of beans.\n"); 

    add_food(({"pie", "shark pie"}), 
             ({"pie" }), ({"shark"}), 
             300, 155, "shark pie", "shark pies", 
             "A pie containing a large portion of " +
             "shark meat.\n"); 

    add_drink(({"orange juice", "juice"}), ({"juice"}), ({"orange"}),   
            100, 0, 2, "glass of orange juice", "glasses of orange juice",
            "A glass of orange juice.\n");  

    add_drink(({"tea", "cup of tea"}), ({"tea", "cup"}), ({ }), 
            200, 0, 4, "cup of tea", "cups of tea", 
            "A cup of tea.\n"); 
}


int
cadets_only()
{
    if (!IS_GELAN_CADET(this_player()) && !this_player()->query_wiz_level()) { 
        write("That area is for cadets only.\n"); 
        return 1;
    } 
    return 0;
}


string
food_desc(mixed food)
{
    return sprintf("%-25s %6d cc", capitalize(food[4]), food[3]);  
}

string
drink_desc(mixed drink)
{
    return sprintf("%-25s %6d cc", capitalize(drink[5]), drink[4]);  
}

string
display_menu()
{
    return ("Cadets' Mess Menu\n" + 
            "------------------\n" + 
           implode(map(query_food(), food_desc), "\n") + "\n" +  
           implode(map(query_drinks(), drink_desc), "\n") + "\n");   
}


void
init()
{
    ::init(); 
    init_pub(); 
}

