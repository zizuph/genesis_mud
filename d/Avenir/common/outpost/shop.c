/*  Shop based on Gondor's /lib/shop.c
 *   by Iliyian
 *  Lilith May 2014 Just a copy of the Bazaar shop for the Fort area.
 */
inherit "/d/Avenir/common/lib/shop";
#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Avenir/include/relation.h"

#define STORE_ROOM (OUTPOST +"store") /* Where the items are stored*/

void
create_shop()
{
    object bin;

    set_store_room(STORE_ROOM);
    set_short("a cramped little shop");
    set_long("This little shop has been carved out of the living "+
    "stone of the cavern wall. It opens north onto the second "+
    "floor of the main tower of Fort Sybarus. "+
    "Some crystal and copper wall lamps gently illuminate the room. "+
    "There are rows of stone shelves along the east and west "+
    "walls. A wooden sign hangs over the stone counter, which "+
    "has a storeroom behind it.\n");

    add_item(({"sign"}), "It has writing on it.\n");
    add_item(({"counter","countertop"}),"It is of solid oak, well-worn and "+
       "weathered over the years.\n");
    add_item(({"wall","walls"}),"The walls are of ancient pale stone.\n");
    add_item(({"floor","ground"}),"The flagstones are fairly clean, "+
       "considering all the traffic that comes through here.\n");
	add_item(({"shelf", "shelves"}), "It appears that the pickings "+
	   "are slim in this outpost area of Sybarus. The shelves are "+
	   "mostly empty.\n");
    add_item(({"source", "source lights", "octagonal crystals",
        "source crystals", "octagonal crystal", "crystal",
    	"source crystal", "source lamp", "source lamps", "source",
        "wall lamps", "lamps", "lamp", "crystal and copper lamps"}),
        "Glowing crystals the size of your palm have been "+
        "set in the walls at regular intervals. The crystals "+
        "are octagonal in shape, and a mirrored half-circle "+
        "of copper has been installed above them, reflecting "+
        "the light.\n");  		
    add_item(({"copper mirror", "copper mirrors", "mirror", "mirrors",
	    "mirror on the wall", "mirror above the crystal", "copper",
        "half-circle", "copper half-circle", "half-circle of copper"}),
        "A mirror made of copper has been installed over each "+
        "source crystal, amplifying and reflecting the light.\n");			
    add_item(({"limestone", "white cobbles", "cobblestone", "floor",
    	"grey cobbles", "grey-white cobbles", "ground", "paving",
        "pavers", "calcite crystals", "floor tiles", "flooring"}),
	    "The ground is covered in pale grey limestone containing "+
        "calcite crystals that glitter when they catch the light.\n");
    add_item(({"wall","walls","stones", "stone", "basaltic stone", 
        "basalt", "dark stone", "black stone", "smooth stone",
		"blocks", "stone blocks", "dark blocks", "dark stone blocks"}),
        "These walls are made of dark, smooth stone blocks perfectly "+
        "joined together. Basalt is a very hard, very dense stone "+		
        "that is useful for construction.\n");
    add_item(({"cavern wall", "natural stone", "natural wall", 
        "natural stone wall", "uncarved stone", "rough stone",
        "rough stone wall", "original wall", "original cavern wall",
        "living stone"}),
        "This wall is natural stone, part of the original cavern "+
        "wall. It is rough and uncarved.\n");
    add_item(({"ceiling", "up" }), 
        "You crane your neck to see the ceiling and find more "+
        "of the same dark stone as in the rest of the fort.\n");
    add_item(({"fort", "tall fort", "black fort", "tall black fort",
	    "fortress", "basalt fortress", "fort sybarus", "tower"}),
        "You are inside Fort Sybarus. "+
	    "This fortress was built into the opening between the Underdark "+
        "and the Sybarus Cavern using the black, smooth basaltic stone "+
		"native to these parts. The fortress has stood here for over a "+
        "thousand years and will surely stand for thousands more.\n" );

    add_exit(OUTPOST+"tower_middle3", "north", 0);
    add_exit(STORE_ROOM, "south", "@@wiz_check");

    set_shop_name("Sybarus Fort Goods and Services");
    set_keeper_file(MON+"shopkeeper");
    set_suspected_race(({"hobbit"}));    // 'cause there aren't any in Avenir
    set_favoured_race(({"elf","dwarf"}));
    add_item("poster","It has readable words on it.\n");
  
    bin = clone_object("/d/Avenir/common/obj/trash_can");
    bin->move(this_object());

    add_prop(ROOM_M_NO_MAGIC_ATTACK, "The Gods of Sybarus brook no "+    
       "such magick in this place.\n");
    add_prop(ROOM_M_NO_ATTACK, "Mmmm... on second thought, maybe not.\n");
    IN_IN;
	add_prop(ROOM_I_LIGHT, 50); // So trade can go on.
	
}


/*
 * Function name: init_shop
 * Description  : This function is called for each living that enters the
 *                room. It adds the necessary commands to the players.
 *                You should call this from the init() function in your
 *                room.
 */
void
init_shop()
{
    add_action(do_buy,   "buy");
    add_action(do_sell,  "sell");
    add_action(do_value, "value");
    add_action(do_show,  "show");
    add_action(do_list,  "list");
    add_action(do_read,  "read");
    add_action(do_store, "store");
}



int
do_buy(string args)
{
    if (IS_INFIDEL(this_player()))
    {
        tell_object(this_player(), "The shopkeeper does not conduct "+
            "business with criminals.\n");
        return 1;
    }
    if (check_keeper()) return ::do_buy(args);
        return 0;
}

int
do_value(string args)
{
    if (check_keeper()) return ::do_value(args);
        return 0;
}

int
do_sell(string args)
{
    if (IS_INFIDEL(this_player()))
    {
        tell_object(this_player(), "The shopkeeper does not conduct "+
            "business with criminals.\n");
        return 1;
    }

  if (check_keeper()) return ::do_sell(args);
  return 0;
}

int
do_list(string args)
{
  if (check_keeper()) return ::do_list(args);
  return 0;
}


mixed
shop_hook_filter_sell(object ob)
{
   return 0;
  // cause we want it to buy everything...
}
