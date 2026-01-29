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

#define PRICELIST_ID ({"menu","list","sign","pricelist","prices"})
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
    set_short("The Rusty Axe Tavern");

    set_long(fire_desc);
  
    add_item_light(({"tavern", "room", "common room"}),
        "You are inside the common room of the Rusty Axe, the local tavern " +
        "which serves the local residents of the village of Garient. A long, oaken " +
        "bar runs along the west wall serving up drinks and food for customers. " +
        "Meanwhile, dominating the south end of the tavern is a large fireplace " +
        "which has been constructed from dozens of multi-coloured fieldstones set " +
        "in a grey mortar. Plenty of round, wooden tables are scattered around the " +
        "rest of the tavern, with chairs haphazardly encircling most of them. " +
        "Underneath the tables, the wooden planks of the floor are covered " +
        "with loose clumps of sawdust. Above your head, several crude iron " +
        "lamps hang down from wooden beams, adding a little additional light. " +
        "A couple of dirty windows flank the stout wooden door in the north " +
        "wall as they look out towards the rest of the village of Gairent.\n", LIGHT_ALL);
/*
    add_item_light(({"bar", "oak bar", "oaken bar", "west wall", "long bar", "long oaken bar"}),
        "A long bar, made entirely of oak, stretches across the length of the western " +
        "wall. The wood of the bar itself is heavily scratched, stained and worn " +
        "from what appears to be years of heavy use. However, this does not seem " +
        "to be a problem for the customers or the kitchen staff who keep serving " +
        "up plates of warm food and mugs of cold ale on the bartop.\n", LIGHT_ALL);
*/
    add_item_light(({"kitchen", "plate", "plates", "opening", "mug", "mugs"}),
        "A narrow opening in the west wall leads into a small kitchen where the " +
        "food and drink is prepared for the customers. The barmaids seem to be " +
        "constantly bringing out mugs of cold ale and plates of warm food for " +
        "all of the customers here. \n", LIGHT_ALL);
    add_item_light(({"south wall", "southern wall"}),
        "The southern wall is almost completely filled with a large, stone fireplace " +
        "which provides a friendly, and warm, atmosphere to the tavern. The fireplace " +
        "has been constructed from dozens of rounded, multi-coloured fieldstones all " +
        "set into a dark, grey mortar. A generous pile of black" +
        "wooden logs sit on a flat stone hearth, where every now and then a barmaid " +
        "will toss another log on the fire to keep it burning.\n", LIGHT_ALL);
    add_item_light(({"table", "tables", "wooden tables", "round tables", "wooden table", "round table"}),
        "Several round tables of wood have been placed around the floor of the tavern here. " +
        "There are also plenty of chairs available, so that if you wished to sit down and " +
        "enjoy a hot meal or a cold mug of ale, you could do so with some semblance of " +
        "comfort.\n", LIGHT_ALL);
    add_item_light(({"chair", "chairs", "wooden chair", "wooden chairs"}),
        "There are dozens of wooden chairs scattered around the tavern, most of them " +
        "encircling the round tables which have been left here for the convenience of " +
        "the customers. Most of the chairs appear to be in relatively poor condition, " +
        "but you suppose they are probably still servicable.\n", LIGHT_ALL);
    add_item_light(({"beam", "beams", "oak beams"}),
        "Several thick oak beams stretch across the ceiling of the tavern, supporting " +
        "the roof above and providing a convenient place to hang all of the iron " +
        "lamps which light the tavern.\n", LIGHT_ALL);
    add_item_light(({"nails", "nail", "iron nail", "iron nails", "nail head", "head", "nail heads", "heads"}),
        "The oak planks of the floor are mostly secured with iron nails, however you " +
        "notice that several of the nail heads rise up exposed in several areas, suggesting " +
        "that perhaps the owner of this tavern could perhaps take a little better care " +
        "of this establishment.\n", LIGHT_ALL);
    add_item_light(({"dust", "sawdust", "clump", "clumps"}),
        "Scattered across the floor of the tavern are dozens of clumps of sawdust. It " +
        "seems that the barmaids use the sawdust to catch most of the food and ale " +
        "which spills, making cleaning up somewhat easier.\n", LIGHT_ALL);
    add_item_light(({"oak planks", "floor planks", "oak plank", "floor plank", "floor"}),
        "The floor of the tavern appears to be made of wide planks of oak. The planks " +
        "are not in very good condition, having been heavily worn over the years, as " +
        "some of the planks are splintered around nail heads which sit exposed to " +
        "unsuspecting feet.\n", LIGHT_ALL);
    add_item_light(({"lamp", "iron lamp", "lamps", "iron lamps", "ceiling"}),
        "The ceiling of the tavern is covered with many iron lamps which hang down " +
        "from the oak beams which stretch across from wall to wall.\n", LIGHT_ALL);
    add_item_light(({"east wall", "stag", "stag head"}),
        "The east wall of the tavern is relatively unadorned, with only the " +
        "mounted head of a stag sitting in the middle of it.\n", LIGHT_ALL);
    add_item_light(({"wall", "walls", "wooden wall", "wooden walls"}),
        "The walls here are all made of wood, did you want to look at one wall " +
        "in particular?\n", LIGHT_ALL);
    add_item_light(({"window", "windows", "dirty window", "dirty windows"}),
        "There are two very dirty windows in the north wall, one on each side " +
        "of the door. If they were clean enough to look through, you would " +
        "undoubtedly be able to see the rest of the village.\n", LIGHT_ALL);
    add_item_light(({"door", "stout door", "north wall"}),
        "This stout door in the north wall leads back out into the village of " +
        "Gairent. \n", LIGHT_ALL);
    add_item_light(({"mortar", "grey mortar", "cement"}),
        "This dark grey mortar is the cement which has been used to set the " +
        "fieldstones which decorate the large fireplace on the south wall.\n", LIGHT_ALL);
    add_item_light(({"stones", "fieldstones", "stone", "fieldstone"}),
        "The fireplace has been decorated with dozens of multi-coloured fieldstones " +
        "which have been set into a grey mortar. The stones vary in size, and are " +
        "irregularily shaped, but their rounded contours display a vivid colour " +
        "palette which is quite pleasing to the eye.\n", LIGHT_ALL);
    add_item_light(({"hearth", "stone hearth"}),
        "At the base of the fireplace is a wide stone hearth. Resting on top of " +
        "the hearth is a pile of black logs which are occasionally fed into the " +
        "fire which warms the tavern.\n", LIGHT_ALL);
    add_item_light(({"village", "gairent"}),
        "Just outside the door in the north wall is the rest of the small village of " +
        "Gairent. The village appears to be made up almost entirely of the woodsmen " +
        "who harvest timber from Mirkwood forest.\n", LIGHT_ALL);

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
        "[down] [in] [on] [the] [comfortable] [wooden] 'chair'",
         30, "in", 1, 1);
    add_item_light( ({ "sturdy chair", "sturdy wooden chair",
        "wooden chair", "chair" }), &look_at(CHAIR_NAME), LIGHT_ALL);

    add_item_light(PRICELIST_ID, query_menu_description, LIGHT_ALL);

    add_prop(ROOM_I_INSIDE,1);
    
    add_exit(WOODSMEN_DIR + "gairent2", "out", "@@door@@");
    add_exit(WOODSMEN_DIR + "gairent2", "north", "@@door@@",0,1);
    add_exit(WOODSMEN_DIR + "gairent2", "open", "@@open@@",0,1);

    setuid(); 
    seteuid(getuid());

    add_menu_item(WOODSMEN_DIR + "obj/water", "drink");
    add_menu_item(WOODSMEN_DIR + "obj/ale", "drink");
    add_menu_item(WOODSMEN_DIR + "obj/gin", "drink");
    add_menu_item(WOODSMEN_DIR + "obj/steak", "food");
    add_menu_item(WOODSMEN_DIR + "obj/pig", "food");

    set_menu_group_title("drink", "Drinks");
    set_menu_group_title("food", "Food");

    object bar = clone_object("/d/Gondor/std/inn_bar");
    bar->move(this_object());
    bar->set_short("long, oaken bar");
    bar->set_long("This long bar, made entirely of oak, stretches across the length of the western " +
        "wall. The wood of the bar itself is heavily scratched, stained and worn " +
        "from what appears to be years of heavy use. However, this does not seem " +
        "to be a problem for the customers or the kitchen staff who keep serving " +
        "up plates of warm food and mugs of cold ale on the bartop. \n");
    set_bar(bar);    

    config_default_trade(); 
    configure_inn();

    reset_room();
}

int
door()
{
write("You open the door and make your way out into the village of Gairent.\n\n");
return 0;
}

int
open()
{
write("\n\nYou open the door, however it is not long before one of the barmaids " +
    "closes it again. You can just go out to the village if you want to leave.\n\n");
return 1;
}

void
remove_object()
{ 
    remove_inn_object();
    ::remove_object();
}

int
open_cmd(string args)
{
    if (!args || args != "door") 
    {
        notify_fail("Open what?\n");
        return 0;
    }

    write("\n\nYou open the door of the inn, but the innkeeper wants to keep " +
        "his establishment warm so he has a barmaid shut the door again. If you would " +
        "like to leave, you can simply go out.\n\n");
    return 1;
}


void 
init()
{
    ::init();
    add_action(open_cmd, "open");
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
        innkeeper = clone_object(WOODSMEN_DIR + "npc/faelund");
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
            + "setting them ablaze and providing the inn with "
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
        return BSN("This large, fieldstone fireplace is set into the north "+
        "wall. Currently, a merry fire burns brightly in the fireplace, "+
        "casting its flickering light and warmth across the inn.");
    case FIRE_UNLIT_WOOD:
        return BSN("You see a large, fieldstone fireplace set into the " +
            "northern wall of the inn. Currently, there are several " +
            "oak logs neatly stacked, just waiting to be lit.");
    default:   
        return BSN("A large, fieldstone fireplace is set into the north "+
        "wall.");
    }

    case "fire":
    switch (fire_state)
    {
    case FIRE_BURNING:
        return BSN("There are several oak logs in the large fireplace, " +
            "crackling as they burn. You can feel the warmth of the fire " +
            "radiating across the entire inn.");
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
            "to the inn.");
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
        "You are inside the common room of the Rusty Axe, the local tavern " +
        "which serves the local residents of the village of Garient. A long, oaken " +
        "bar runs along the west wall serving up drinks and food for customers. " +
        "Meanwhile, dominating the south end of the tavern is a large fireplace " +
        "which has been constructed from dozens of multi-coloured fieldstones set " +
        "in a grey mortar. A bright fire currently dances merrily inside the fireplace, " +
        "warming the entire tavern and offering plenty of light. A dozen round, " +
        "wooden tables are scattered around the " +
        "rest of the tavern, with chairs haphazardly encircling most of them. " +
        "Underneath the tables, the wooden planks of the floor are covered " +
        "with loose clumps of sawdust. Above your head, several crude iron " +
        "lamps hang down from wooden beams, adding a little additional light. " +
        "A couple of dirty windows flank the stout wooden door in the north " +
        "wall as they look out towards the rest of the village of Gairent.");
    }
    return BSN(
        "You are inside the common room of the Rusty Axe, the local tavern " +
        "which serves the local residents of the village of Garient. A long, oaken " +
        "bar runs along the west wall serving up drinks and food for customers. " +
        "Meanwhile, dominating the south end of the tavern is a large fireplace " +
        "which has been constructed from dozens of multi-coloured fieldstones set " +
        "in a grey mortar. Currently the fireplace stands cold and empty, hopefully " +
        "the barkeeper will light a fire again soon. A dozen round, " +
        "wooden tables are scattered around the " +
        "rest of the tavern, with chairs haphazardly encircling most of them. " +
        "Underneath the tables, the wooden planks of the floor are covered " +
        "with loose clumps of sawdust. Above your head, several crude iron " +
        "lamps hang down from wooden beams, adding a little additional light. " +
        "A couple of dirty windows flank the stout wooden door in the north " +
        "wall as they look out towards the rest of the village of Gairent.");
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