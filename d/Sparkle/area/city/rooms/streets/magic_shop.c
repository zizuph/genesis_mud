
/*
 *  /d/Sparkle/area/city/rooms/streets/center_a.c
 *
 *  These are the city streets of Sparkle. Refer to outdoor_room.c for
 *  functionality.
 *
 *  Created October 2008, by Nerull
 *    - Much credit and thanks to Styles for his inspirational city
 *      design concepts.
 */
#pragma strict_types

#include "../../defs.h"
#include <money.h>
#include <stdproperties.h>
#include <macros.h>


inherit "/lib/shop";
inherit ROOMS_DIR + "sparkle_room_base";




#define BS(x)            break_string((x), 75)
#define BSN(x)           (BS(x) + "\n")

#define STORE (ROOMS_DIR + "streets/magic_shop_store")


/* Prototpyes */
public void        create_sparkle();




/*
 * Function name:        create_sparkle
 * Description  :        set up the room with area presets
 */
public void
create_sparkle()
{
    set_name("Inside Nystul's Magic Mojos shop");
    add_name( ({ "room", "hall" }) );

    set_short("You are standing inside Nystul's Magic Mojos shop");
    set_long("You are standing inside Nystul's Magic Mojos shop. The light emitting from a " +
    "shiny brass oil lamp hanging from the dark ceiling make obscure shadows of the many " +
    "enchanted items and potions sitting on the big dusty shelf behind a wooden counter. A single " +
    "porcelain statue sits in the northeastern corner of the room, collecting cobwebs. There is an " +
    "eerie smell filling the room, combined with the bubbling sound of a boiling large iron " +
    "cauldron placed in the fireplace that is buildt into the west wall. A small pricelist decorates " +
    "the left corner of the wooden counter.\n");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    
    add_item( ({ "smell" }),
            BSN("It smells a combination of flamable materials and boiling organic components.\n"));
            
            
    // Humorous content. Most people when asked about what a white cow drinks, without thinking 
    // the answer is often 'milk'. The porcelain part is a small Monkey Island tribute. :)    
    add_item( ({ "statue", "porcelain statue", "statue" }),
            BSN("Its a white statue of...ugh...porcelain...resembling the shape of a " +
            "white cow, drinking milk.\n"));
            
    add_item( ({ "lamp" }),
            BSN("This is a small circular lamp of brass containing oil. Its hanging, suspended " +
            "by four small iron chains attached to the ceiling by small hooks. It dimly illuminate " +
            "the room.\n"));
            
    add_item( ({ "counter" }),
            BSN("This wooden counter has seen better days, but has it yet seen more heaps of " +
            "gold exchange? A pricelist decorates its left corner.\n"));
            
    add_item( ({ "items", "potion", "potions", "vials", "shelf" }),
            BSN("This is a single broad wooden board that is painted black and attached to the north " +
            "wall by nails, and supported by two small iron chains on either side. On it you see a " +
            "curious pile of various sized potions and trinkets, partically cowered with some " +
            "cobweb and dust. However, what separate these trinkets and potions is that they " +
            "all give away a faint magical glow, indicating that they are all enchanted by " +
            "some magical effects.\n"));
            
    add_item(({"pricelist"}),
	          "\n"+
	          "    ------------------------------------------ \n"+
	          "    -            Magical Potions             - \n"+
	          "    -                                        - \n"+ 
	          "    -  Minor Healing Potion ......... 10 cc  - \n"+
	          "    -  Minor Mana Potion ...........  10 cc  - \n"+
 	          "    ------------------------------------------\n\n");
 	
	   add_cmd_item(({"pricelist"}), "read",
	          "\n"+
	          "    ------------------------------------------ \n"+	          
	          "    -            Magical Potions             - \n"+
	          "    -                                        - \n"+ 
	          "    -  Minor Healing Potion ......... 10 cc  - \n"+
	          "    -  Minor Mana Potion ...........  10 cc  - \n"+
 	          "    ------------------------------------------\n\n");
 	          
 	  config_default_trade();
    
    set_store_room(STORE);


    add_exit("center_b", "south");
    
} 

int
shop_hook_allow_sell(object ob)
{
    
        return notify_fail("The shopkeeper dont want anything from you.\n");

    return 1;
}

/*int
do_sell(string str)
{
    notify_fail("The shopkeeper doesnt want anything from you.\n");
    return 1;
}*/

void
init()
{
  ::init();
  //add_action(do_sell,"sell");
  init_shop();
}




