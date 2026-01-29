/*
 * Gairent in Mirkwood.
 * Varian 2015
 */

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/open/fireplace/fireplace.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"


inherit MIRKWOOD_STD_DIR + "room";
inherit "/d/Gondor/lib/inn";
inherit "/d/Gondor/open/fireplace/fireplace";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#pragma save_binary
#pragma strict_types

#define PRICELIST_ID ({"pricelist","list","sign","menu","prices"})
#define RESET_WOOD 10
#define CHAIR_NAME "chair"
#define CHAIR_CAPACITY 30

public void create_room();
public void reset_room();
public void init();
public string   fire_desc(string arg);
public void leave_inv(object ob, object dest);
public string   look_at(string arg);

static object innkeeper;
static object ranger;

void
create_room()
{
    set_short("The Chipped Mug Tavern");

    set_long(fire_desc);
  
    add_item_light(({"tavern", "room", "common room"}),
        "This appears to be the common room of the Chipped Mug Tavern. The " +
        "room itself is filled with wooden tables of various sizes and " +
        "shapes scattered across the stone floor, each of them surrounded " +
        "by mismatched sets of chairs and stools. All along the southern " +
        "wall, a stone bar stands ready to serve patrons with either drink " +
        "or food. Just behind the bar, you can see a rather dirty looking " +
        "kitchen. The northern end of the tavern is dominated by a large " +
        "stone fireplace which juts out from the wall aggressively. The " +
        "eastern wall seems to be decorated with a variety of weapons, " +
        "all of which appear to have been well used in battle. A large " +
        "arch carved into the stone of the western wall opens out into " +
        "the center of the village of Hargnak.\n", LIGHT_ALL);
/*
    add_item_light(({"bar", "oak bar", "oaken bar", "west wall", "long bar", "long oaken bar"}),
        "A long bar, made entirely of oak, stretches across the length of the western " +
        "wall. The wood of the bar itself is heavily scratched, stained and worn " +
        "from what appears to be years of heavy use. However, this does not seem " +
        "to be a problem for the customers or the kitchen staff who keep serving " +
        "up plates of warm food and mugs of cold ale on the bartop.\n", LIGHT_ALL);
*/
    add_item_light(({"kitchen", "dirty kitchen"}),
        "Secluded behind the bar, you spy a very dirty looking kitchen " +
        "which appears to be busy preparing food for customers of the " +
        "Chipped Mug.\n", LIGHT_ALL);
    add_item_light(({"south wall", "southern wall"}),
        "The southern wall is dominated by a long bar carved from a dark " +
        "grey stone. A couple of stools have been casually pushed up " +
        "against the bar as the odd patron goes to pick up their food " +
        "or drink. Behind the bar, you can see a very busy, and very dirty, " +
        "kitchen preparing food.\n", LIGHT_ALL);
    add_item_light(({"table", "tables", "wooden tables", "wooden table"}),
        "There are several wooden tables which have been scattered around " +
        "the tavern. Most of them have a mismatched collection of chairs " +
        "and stools clustered around them to offer a place to sit while " +
        "you enjoy your food or drink.\n", LIGHT_ALL);
    add_item_light(({"chair", "chairs", "wooden chair", "wooden chairs"}),
        "There are lots of rough, wooden chairs here! However, upon closer " +
        "inspection, you notice that many of them appear to be broken " +
        "in some fashion. However, you are pretty sure you could find one in " +
        "reasonable condition if you wanted to have a seat.\n", LIGHT_ALL);
    add_item_light(({"stone slab", "slab", "slabs", "stone slabs", "floor"}),
        "The floor of the tavern is covered in massive stone slabs. The " +
        "slabs are mostly smooth, having been worn down by customers " +
        "over the years, but you could still trip yourself if you are " +
        "not careful.\n", LIGHT_ALL);
    add_item_light(({"lamp", "iron lamp", "lamps", "iron lamps", "ceiling"}),
        "The ceiling of the tavern has several iron lamps hanging down from " +
        "chains which are attached to the ceiling.\n", LIGHT_ALL);
    add_item_light(({"east wall", "decorations", "weapons"}),
        "The east wall of the tavern has been decorated with several " +
        "swords, axes and other weapons. Most of these weapons appear " +
        "to be somewhat rusty and notched, suggesting that they have seen " +
        "their share of use in battle.\n", LIGHT_ALL);
    add_item_light(({"wall", "walls", "stone wall", "stone walls"}),
        "There are four stone walls here, did you want to look at one wall " +
        "in particular?\n", LIGHT_ALL);
    add_item_light(({"opening", "arch", "west wall", "western wall"}),
        "This large arch opens through the stone of the western wall, " +
        "leading you back out into the middle of Hargnak.\n", LIGHT_ALL);
    add_item_light(({"stones", "fieldstones", "fieldstone"}),
        "This fireplace appears to have been constructed using many " +
        "large fieldstones. The stones seem to have been piled in a jumbled " +
        "heap, with very little concern for aesthetics. However, the " +
        "fireplace does look very solid and functional.\n", LIGHT_ALL);
    add_item_light(({"hearth", "stone hearth"}),
        "At the base of the fireplace is a wide stone hearth which appears " +
        "to have been carved from one massive chunk of basalt. The hearth " +
        "has not been well smoothed, but it does provide a convenient " +
        "place to store some firewood.\n", LIGHT_ALL);
    add_item_light(({"village", "hargnak"}),
        "Through the open arch in the west wall, you can see the small " +
        "goblin village of Hargnak, perched on a tall hill near the " +
        "eastern edge of Mirkwood forest.\n", LIGHT_ALL);

    add_item_light(({ "wood", "firewood", "wood in fireplace",
        "firewood in fireplace", "log", "oak log", "logs", "oak logs" }), 
        &fire_desc("wood"), LIGHT_ALL);
    add_item_light(({ "ash", "ashes", "ash in fireplace", 
        "ashes in fireplace" }), &fire_desc("ashes"), LIGHT_ALL);
    add_item_light(({ "fireplace", "large fireplace", "stone fireplace", "fieldstone fireplace" }), 
        &fire_desc("fireplace"), LIGHT_ALL);
    add_item_light(({ "fire" }), &fire_desc("fire"), LIGHT_ALL);

    set_parse_pattern("[the] [large] [stone] 'fireplace'");

/*    
    add_item_light(({"woodpile", "wood", "log", "black log", "logs", "black logs", "pile"}),
        "This woodpile contains many short, dry logs ready to be tossed on " +
        "the fire. Unsurprisingly in a town of woodsmen, the pile is frequently " +
        "refilled to keep the fire burning.\n", LIGHT_ALL);
*/

    add_chair(CHAIR_NAME,
        "[down] [in] [on] [the] [wooden] [rough] 'chair'",
         30, "in", 1, 1);
    add_item_light( ({ "rough chair", "rough wooden chair",
        "wooden chair", "chair" }), &look_at(CHAIR_NAME), LIGHT_ALL);

    add_item_light(PRICELIST_ID, query_menu_description, LIGHT_ALL);

    add_prop(ROOM_I_INSIDE,1);
    
    add_exit(GOBLINS_DIR + "hargnak2", "west", "@@opening@@");


    setuid(); 
    seteuid(getuid());

    add_menu_item(GOBLINS_DIR + "obj/water", "drink");
    add_menu_item(GOBLINS_DIR + "obj/beer", "drink");
    add_menu_item(GOBLINS_DIR + "obj/blackwater", "drink");
    add_menu_item(GOBLINS_DIR + "obj/fingers", "food");
    add_menu_item(GOBLINS_DIR + "obj/roast", "food");

    set_menu_group_title("drink", "Drinks");
    set_menu_group_title("food", "Food");

    object bar = clone_object("/d/Gondor/std/inn_bar");
    bar->move(this_object());
    bar->set_short("long, stone bar");
    bar->set_long("This long bar appears to have been carved out of one " +
        "massive stone block. It has become smooth and well-worn with " +
        "age, even if it appears to be a bit uneven in some areas. " +
        "The bartender often leaves food and drink here for paying " +
        "customers.");
    set_bar(bar);    

    config_default_trade();
    configure_inn();

    reset_room();
}

int
opening()
{
write("You duck through the stone arch and come out into the village " +
    "of Hargnak.\n\n");
return 0;
}


void
remove_object()
{ 
    remove_inn_object();
    ::remove_object();
}

void 
init()
{
    ::init();
    add_action("do_read","read");
    init_inn();
    init_fire();
    init_room_chairs();
}
int
do_read(string str)
{
    if(!str)
    {
        notify_fail("Read what?\n");
        return 0;
    }
    
    if(member_array(str, PRICELIST_ID) == -1)
    { 
        notify_fail("Read what?\n");
        return 0;
    }
    write(query_menu_description());
    SAYBB(" reads the sign.");
    return 1;
}

void
reset_room()
{
    if (!objectp(innkeeper)) 
    {
        innkeeper = clone_object(GOBLINS_DIR + "npc/rukh");
        set_innkeeper(innkeeper);
    }

    if (environment(innkeeper) != this_object())
    {
        innkeeper->move_living("inside", this_object());
    }

    set_wood(-1);

    if (query_fire_state() != FIRE_BURNING)
    {
        tell_room(this_object(), QCTNAME(innkeeper)
            + " carefully stacks some oak logs in the fireplace, "
            + "setting them ablaze and providing the tavern with "
            + "some much needed light and warmth.\n");
        set_fire_state(FIRE_BURNING);
    }
}


public string
fire_desc(string arg)
{
    int fire_state = query_fire_state();

    switch (arg)
    {

    case "fireplace":
    switch (fire_state)
    {
    case FIRE_BURNING:        
        return BSN("This large, fieldstone fireplace juts out from the north "+
        "wall. Currently, a merry fire burns brightly in the fireplace, "+
        "casting its flickering light and warmth across the inn.");
    case FIRE_UNLIT_WOOD:
        return BSN("You see a large, fieldstone fireplace jutting out from " +
            "the northern wall of the inn. Currently, there are several " +
            "oak logs neatly stacked, just waiting to be lit.");
    default:   
        return BSN("A large, fieldstone fireplace juts out from the north "+
        "wall.");
    }

    case "fire":
    switch (fire_state)
    {
    case FIRE_BURNING:
        return BSN("There are several oak logs in the large fireplace, " +
            "crackling as they burn. You can feel the warmth of the fire " +
            "radiating across the entire tavern.");
    case FIRE_UNLIT_WOOD:   
        return BSN("The fireplace is not lit at this time, there is no fire!");
    default:
        return BSN("You find no fire.");
    }

    case "wood":
    switch (fire_state)
    {
    case FIRE_BURNING:
        return BSN("There are several oak logs stacked and burning in the " +
            "stone fireplace, burning merrily and providing plenty of warmth " +
            "to the tavern.");
    case FIRE_UNLIT_WOOD:
       return BSN("A large pile of oak logs has been stacked in the fireplace, " +
        "ready and waiting to be lit.");
    default: 
        return BSN("You find no firewood.");
    }

    case "ashes":
    switch (fire_state)
    {
    case FIRE_BURNING:
        return BSN("As you stare into the brightly burning fireplace, you " +
            "notice some ashes gathering on the stone base.");
    case FIRE_UNLIT_WOOD:
        return BSN("You can see some ashes at the bottom of the " +
            "stone fireplace, under the stack of wooden logs.");
    default: 
        return BSN("Ashes cover the bottom of the fireplace.");
    }

    default:    /* room long description */
    if (fire_state == FIRE_BURNING)
    {
        return BSN(
        "This appears to be the common room of the Chipped Mug Tavern. The " +
        "room itself is filled with wooden tables of various sizes and " +
        "shapes scattered across the stone floor, each of them surrounded " +
        "by mismatched sets of chairs and stools. All along the southern " +
        "wall, a stone bar stands ready to serve patrons with either drink " +
        "or food. Just behind the bar, you can see a rather dirty looking " +
        "kitchen. The northern end of the tavern is dominated by a large " +
        "stone fireplace which juts out from the wall aggressively. Inside " +
        "the fireplace, you can see a bright fire dancing merrily, casting " +
        "shadows and warmth all across the entire tavern. Nearby, the " +
        "eastern wall seems to be decorated with a variety of weapons, " +
        "all of which appear to have been well used in battle. A large " +
        "arch carved into the stone of the western wall opens out into " +
        "the center of the village of Hargnak.");
    }
    return BSN(
        "This appears to be the common room of the Chipped Mug Tavern. The " +
        "room itself is filled with wooden tables of various sizes and " +
        "shapes scattered across the stone floor, each of them surrounded " +
        "by mismatched sets of chairs and stools. All along the southern " +
        "wall, a stone bar stands ready to serve patrons with either drink " +
        "or food. Just behind the bar, you can see a rather dirty looking " +
        "kitchen. The northern end of the tavern is dominated by a large " +
        "stone fireplace which juts out from the wall aggressively. " +
        "Currently, the fireplace is cold and empty, perhaps the " +
        "bartender will light a new fire sometime soon! The " +
        "eastern wall seems to be decorated with a variety of weapons, " +
        "all of which appear to have been well used in battle. A large " +
        "arch carved into the stone of the western wall opens out into " +
        "the center of the village of Hargnak.");
    }
    return "";

}

public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} 

public string
look_at(string arg)
{
    switch ( arg )
    {
    case CHAIR_NAME:
    return "The wooden chair is of rather simple, yet sturdy, construction. \n" +
        sitting_on_chair(CHAIR_NAME, this_player(), 0);
    
    }
}