/*
 * Woodsmen village in Mirkwood.
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
int out();
int kit();

static object innkeeper;
static object ranger;

void
create_room()
{
    set_short("The Wild Boar Inn");
    set_long(fire_desc);
  
    add_item_light(({"floor", "wooden floor", "planks", "wooden planks"}),
        "The floor of the inn has been constructed out of many " +
        "long, wooden planks. The planks have been heavily stained " +
        "and worn with years of heavy use, but they still seem " +
        "solid enough.\n", LIGHT_ALL);
    add_item_light(({"stain", "stains"}),
        "There are countless stains from spilled food and " +
        "drink covering the wooden floor beneath your feet.\n", LIGHT_ALL);
    add_item_light(({"ceiling", "wooden ceiling"}),
        "The ceiling of the inn is filled with thick, wooden " +
        "beams that stretch across the entire length of the inn. " +
        "Above the beams, you can see the planks of the second " +
        "floor of the inn. In the middle of the ceiling, an " +
        "old iron chandelier hangs down, providing some additional " +
        "light.\n", LIGHT_ALL);
    add_item_light(({"candles", "candle", "chandelier", "iron chandelier"}),
        "There are several candles burning in an iron chandelier " +
        "which hangs down from the ceiling, offering some " +
        "additional light to what the massive fireplace " +
        "otherwise provides.\n", LIGHT_ALL);
    add_item_light(({"wall", "walls"}),
        "Which wall did you want to look at? The northern?, " +
        "eastern?, southern? or western wall?\n", LIGHT_ALL);
    add_item_light(({"door", "oak door", "heavy door", "heavy oak door"}),
        "This oak door appears to be quite thick and heavy, although " +
        "it always seems to be left unlocked. The door opens out into " +
        "the rest of the village of Weanting.\n", LIGHT_ALL);
    add_item_light(({"west wall", "western wall"}),
        "The western wall of the inn is covered mostly in a plain " +
        "wooden wall, with one narrow opening into the kitchen. Several " +
        "tables are clustered around a small bar here.\n", LIGHT_ALL);
    add_item_light(({"south wall", "southern wall"}),
        "The south wall of the inn has a massive, stone fireplace which " +
        "seems to be constantly burning, keeping the inn nice and " +
        "warm. You cannot help but notice that most of the patrons of " +
        "this inn seem to gather here.\n", LIGHT_ALL);
    add_item_light(({"east wall", "eastern wall"}),
        "The northern wall of the inn has two staircases which meet " +
        "at a small landing, before moving up to the second floor.\n", LIGHT_ALL);
    add_item_light(({"north wall", "northern wall"}),
        "A heavy oaken door, flanked by two rather dirty windows, stands " +
        "in the middle of the eastern wall, leading back out into the " +
        "village of Weanting.\n", LIGHT_ALL);
    /*
    add_item_light(({"fireplace", "stone fireplace", "massive fireplace", "massive stone fireplace"}),
        "This massive stone fireplace has been set into the south " +
        "wall of the inn, providing enough warmth to make the entire " +
        "inn feel cozy. A large fire burns brightly, with a massive " +
        "stack of firewood nearby to ensure that the fire never " +
        "goes out.\n", LIGHT_ALL);
    add_item_light(({"firewood", "wood", "stack", "stack of firewood"}),
        "There is a large stack of firewood here, in an effort to help " +
        "ensure that the fireplace will be constantly running.\n", LIGHT_ALL);
    */
    add_item_light(({"staircase", "stairs", "wooden staircase"}),
        "Two sets of wooden staircases climb up the eastern wall, meeting " +
        "at a small landing in the middle before continuing as one up to " +
        "the second floor. The southern staircase leads almost directly " +
        "from the fireplace, and is mostly used by the local staff, while " +
        "the northern staircase is more commonly used by the local patrons.\n", LIGHT_ALL);
    add_item_light(({"window", "windows"}),
        "Two rather dirty windows look through the northern wall and into " +
        "the middle of the village of Weanting.\n", LIGHT_ALL);
    add_item_light(({"kitchen", "busy kitchen", "active kitchen"}),
        "You can barely see any details through the narrow opening in the " +
        "western wall, but this appears to be a rather busy and active " +
        "kitchen which works tirelessly to feed the hungry villagers.\n", LIGHT_ALL);
    add_item_light(({"patrons", "customers"}),
        "There are plenty of woodsmen, and their families, who appear " +
        "to eat their daily meals at the Wild Boar. They occupy most " +
        "of the tables here.\n", LIGHT_ALL);
    add_item_light(({"tables", "round tables", "wooden tables", "round wooden tables"}),
        "There are plenty of round, wooden tables here, each with several " +
        "wooden chairs encircling it, offering you a comfortable place " +
        "to enjoy a meal and a drink.\n", LIGHT_ALL);
    add_item_light(({"chairs", "wooden chairs"}),
        "Dozens of wooden chairs are scattered around the inn, huddled " +
        "up against the round tables of the inn. They are here for " +
        "patrons of the inn as they enjoy their meals.\n", LIGHT_ALL);
    add_item_light(({"landing", "wooden landing"}),
        "This wooden landing sits high up on the eastern wall of the " +
        "inn, where the two staircases meet before going up to the " +
        "second floor above.\n", LIGHT_ALL);
    add_item_light(({"opening", "narrow opening"}),
        "This narrow opening in the western wall is partially hidden " +
        "behind a small, wooden bar and leads directly into " +
        "the kitchen. You would probably not be welcome in there, as " +
        "they are too busy preparing meals.\n", LIGHT_ALL);
    add_item_light(({"village", "weanting"}),
        "Weanting is the name of the small village outside this inn. You " +
        "can see the rest of it by going through the door in the northern " +
        "wall.\n", LIGHT_ALL);
    add_item_light(({"room", "main room", "inn", "wild boar inn"}),
        "You are standing in the common room of the Wild Boar " +
        "Inn. This inn is quite clearly the most popular building " +
        "in all of Weanting as many of the woodsmen seem to come " +
        "here for their daily meals. The solid wooden floor beneath " +
        "your feet seems quite worn from years of heavy use, although " +
        "much of it is covered by dozens of tables and chairs. A " +
        "massive, stone fireplace stands in the middle of the southern wall. " +
        "Across the eastern wall, two sets of stairs meet at a small, " +
        "wooden landing before continuing up to the second floor. The " +
        "western wall has many tables pressed up against it, with only " +
        "a small wooden bar which rests in front of the " +
        "narrow opening which leads into the kitchen. A heavy oak door " +
        "in the northern wall rests between two dirty windows, all " +
        "looking out into the village of Weanting beyond.\n", LIGHT_ALL);

    add_item_light(({ "wood", "firewood", "wood in fireplace",
             "firewood in fireplace", "log", "oak log", "logs", "oak logs" }), 
        &fire_desc("wood"), LIGHT_ALL);
    add_item_light(({ "ash", "ashes", "ash in fireplace", 
        "ashes in fireplace" }), &fire_desc("ashes"), LIGHT_ALL);
    add_item_light(({ "fireplace", "massive fireplace", "stone fireplace" }), 
        &fire_desc("fireplace"), LIGHT_ALL);
    add_item_light(({ "fire" }), &fire_desc("fire"), LIGHT_ALL);

    set_parse_pattern("[the] [massive] [stone] 'fireplace'");

    add_chair(CHAIR_NAME,
        "[down] [in] [on] [the] [comfortable] [wooden] 'chair'",
         30, "in", 1, 1);
    add_item_light( ({ "sturdy chair", "sturdy wooden chair",
        "wooden chair", "chair" }), &look_at(CHAIR_NAME), LIGHT_ALL);

    add_item_light(PRICELIST_ID, query_menu_description, LIGHT_ALL);

    add_prop(ROOM_I_INSIDE,1);

    add_exit(WOODSMEN_DIR + "weanting2", "out", out, 1,1);
    add_exit(WOODSMEN_DIR + "weanting2", "north", out, 1);
    add_exit(WOODSMEN_DIR + "weant_inn2.c", "up", check_sitting, 1);
    add_exit(WOODSMEN_DIR + "weant_shack", "west", kit, 1,1);

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
    bar->set_short("small, wooden bar");
    bar->set_long("This small wooden bar sits in front of the " +
        "opening to the kitchen in the western wall. Every now " +
        "and then, food and drink will be placed here for " +
        "the customers once it is ready.\n");
    set_bar(bar);

    config_default_trade();
    configure_inn();

    reset_room();
}

int
kit()
{
    check_sitting();
    write("Since you don't work here, the kitchen is strictly off-limits!\n");
    return 1;
}

int
out()
{
    check_sitting();
    write("\n\nYou open the oak door and pass out into the village of Weanting.\n\n");
    return 0;
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
        "his establishment warm so he shuts the door again. If you would " +
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
        innkeeper = clone_object(WOODSMEN_DIR + "npc/banor");
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
        return BSN("This massive, stone fireplace is set into the north "+
        "wall. Currently, a merry fire burns brightly in the fireplace, "+
        "casting its flickering light and warmth across the inn.");
    case FIRE_UNLIT_WOOD:
        return BSN("You see a massive, stone fireplace set into the " +
            "northern wall of the inn. Currently, there are several " +
            "oak logs neatly stacked, just waiting to be lit.");
    default:   
        return BSN("A massive, stone fireplace is set into the north "+
        "wall.");
    }

    case "fire":
    switch (fire_state)
    {
    case FIRE_BURNING:
        return BSN("There are several oak logs in the massive fireplace, " +
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
        "You are standing in the common room of the Wild Boar " +
        "Inn. This inn is quite clearly the most popular building " +
        "in all of Weanting as many of the woodsmen seem to come " +
        "here for their daily meals. The solid wooden floor beneath " +
        "your feet seems quite worn from years of heavy use, although " +
        "much of it is covered by dozens of tables and chairs. A " +
        "massive stone fireplace stands in the middle of the southern " +
        "wall, with a crackling fire which grants plenty of warmth and light. " +
        "Across the eastern wall, two sets of stairs meet at a small, " +
        "wooden landing before continuing up to the second floor. The " +
        "western wall has many tables pressed up against it, with only " +
        "a small wooden bar which rests in front of the " +
        "narrow opening which leads into the kitchen. A heavy oak door " +
        "in the northern wall rests between two dirty windows, all " +
        "looking out into the village of Weanting beyond.");
    }
    return BSN(
        "You are standing in the common room of the Wild Boar " +
        "Inn. This inn is quite clearly the most popular building " +
        "in all of Weanting as many of the woodsmen seem to come " +
        "here for their daily meals. The solid wooden floor beneath " +
        "your feet seems quite worn from years of heavy use, although " +
        "much of it is covered by dozens of tables and chairs. A " +
        "massive stone fireplace stands in the middle of the southern " +
        "wall, but there is currently no fire burning there. " +
        "Across the eastern wall, two sets of stairs meet at a small, " +
        "wooden landing before continuing up to the second floor. The " +
        "western wall has many tables pressed up against it, with only " +
        "a small wooden bar which rests in front of the " +
        "narrow opening which leads into the kitchen. A heavy oak door " +
        "in the northern wall rests between two dirty windows, all " +
        "looking out into the village of Weanting beyond.");
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