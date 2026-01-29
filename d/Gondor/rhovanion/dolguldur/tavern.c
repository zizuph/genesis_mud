/*
 * Dol Guldur tavern - /d/Gondor/rhovanion/dolguldur/tavern.c
 *
 * Varian - November 2020
 */

#pragma strict_types

#include "/d/Gondor/rhovanion/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/open/fireplace/fireplace.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"


inherit "/d/Gondor/std/room";
inherit "/d/Gondor/lib/inn";
inherit "/d/Gondor/open/fireplace/fireplace";
inherit "/d/Gondor/open/room_chairs/room_chairs";
inherit "/d/Gondor/common/lib/room_tell";

#pragma save_binary
#pragma strict_types

#define PRICELIST_ID ({"menu", "list", "sign", "pricelist", "prices"})
#define RESET_WOOD 10
#define CHAIR_NAME "chair"
#define CHAIR_CAPACITY 30

public void create_gondor();
public void reset_room();
public void init();
public string   fire_desc(string arg);
public void leave_inv(object ob, object dest);
public string   look_at(string arg);

static object innkeeper;

void
create_gondor()
{
    set_short("The Rusty Axe Tavern");

    set_long(fire_desc);

    add_item( ({"stones", "stone", "fieldstone", "fieldstones",
            "field stone", "field stones"}),
        "There are dozens of fieldstones which have been used to " +
        "construct the fireplace. Considering how much of the rest of " +
        "Dol Guldur is in ruins, it's a bit surprising to find such " +
        "a well built fireplace in a tavern like this.\n");
    add_item( ({"down", "floor"}),
        "The floor here is in quite good condition, made from many long, " +
        "solid wooden planks.\n");
    add_item( ({"up", "ceiling"}),
        "The ceiling here has recently been rebuilt, and rebuilt quite " +
        "well actually. It is somewhat surprising considering the " +
        "condition of the rest of the city.\n");
    add_item( ({"wall", "walls"}),
        "The walls of the tavern are mostly covered in wide planks of " +
        "wood, save for the stone fireplace in the north wall.\n");
    add_item( ({"door", "doorway", "opening", "city", "dol guldur"}),
        "There is a door in the western wall that leads back out into " +
        "the city of Dol Guldur.\n");
    add_item( ({"plank", "planks", "wooden plank", "wooden planks"}),
        "The wooden planks that cover the walls and floor here all " +
        "appear to have been recently cut and crafted with a skill " +
        "that has not been apparent elsewhere in Dol Guldur.\n");
    add_item( ({"table", "tables"}),
        "There are many round wooden tables here, most of which are " +
        "very sturdily constructed. There are several chairs circling " +
        "each of the tables, and if you wanted, you could probably " +
        "sit down at one.\n");
    add_item( ({"broken table", "broken tables"}),
        "There are some broken tables cleared off in the far corner " +
        "of the tavern. Considering how much effort was put into " +
        "rebuilding this tavern, you assume the owner is probably not " +
        "best pleased.\n");
    add_item( ({"window", "windows"}),
        "There are several small, narrow windows along both the " +
        "eastern and southern walls.\n");
    add_item( ({"painted sign", "sign"}),
        "Hanging on the wall beside the bar is a painted sign which " +
        "proudly displays the menu of the Rusty Axe.\n");

    add_item( ({"wood", "firewood", "wood in fireplace",
        "firewood in fireplace", "log", "oak log", "logs", "oak logs" }), 
        &fire_desc("wood"));
    add_item( ({"ash", "ashes", "ash in fireplace", 
        "ashes in fireplace" }), &fire_desc("ashes"));
    add_item( ({"fireplace", "large fireplace", "stone fireplace",
        "fieldstone fireplace" }), 
        &fire_desc("fireplace"));
    add_item( ({"fire", "flames", "flame"}), &fire_desc("fire"));

    set_parse_pattern("[the] [large] [stone] [fieldstone] 'fireplace'");

    add_chair(CHAIR_NAME,
        "[down] [in] [on] [the] [sturdy] [wooden] 'chair'",
         30, "in", 1, 1);
    add_item( ({ "sturdy chair", "sturdy wooden chair",
        "wooden chair", "chair", "wood chair" }), &look_at(CHAIR_NAME));

    add_item(PRICELIST_ID, query_menu_description);

    add_tell("Loud curses and hearty laughter fill the air.\n");
    add_tell("Someone shouts: Barkeep! More ale over here!\n");
    add_tell("A drunken human bumps into you before staggering out the " +
        "door.\n");
    add_tell("A bunch of rowdy patrons spontaneously break into song.\n");
    add_tell("A wooden mug whizzes past your head. Where did THAT come " +
        "from?\n");
    add_tell("A brawl suddenly breaks out in the middle of the tavern, " +
        "resulting in another broken table.\n");
    add_tell("A brawl suddenly breaks out in the middle of the tavern.\n");
    add_tell("Someone shouts: Keep that ale coming barkeep!\n");
    add_tell("A glass mug shatters after someone throws it against the " +
        "stone fireplace.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT, 2);

    set_no_exit_msg( ({"north", "northeast", "northwest"}),
        "You think about entering the fireplace, but there really " +
        "doesn't seem to be a good way of doing that.\n");
    set_no_exit_msg( ({"east", "southeast", "south", "southwest"}),
        "You consider going out through one of the windows, but " +
        "you don't think you would quite fit. You will have to use " +
        "the door instead.\n");
    
    add_exit(DG_DIR + "street2", "west", "@@door@@", 0, 0);

    setuid(); 
    seteuid(getuid());

    add_menu_item(DG_DIR + "obj/water", "drink");
    add_menu_item(DG_DIR + "obj/ale", "drink");
    add_menu_item(DG_DIR + "obj/gin", "drink");
    add_menu_item(DG_DIR + "obj/steak", "food");
    add_menu_item(DG_DIR + "obj/pig", "food");

    set_menu_group_title("drink", "Drinks");
    set_menu_group_title("food", "Food");

    set_tell_time(40);

    object bar = clone_object("/d/Gondor/std/inn_bar");
    bar->move(this_object());
    bar->set_short("long, oaken bar");
    bar->set_long("This long bar, made entirely of oak, stretches across " +
        "the length of the western wall. The wood of the bar itself is " +
        "heavily scratched, stained and worn from what appears to be years " +
        "of heavy use. However, this does not seem to be a problem for the " +
        "customers, it is in far better condition than everything else in " +
        "Dol Guldur.\n");
    set_bar(bar);    

    config_default_trade(); 
    configure_inn();

    reset_room();
}

int
door()
{
    write("You push the door open and stagger back out into Dol Guldur.\n\n");
    return 0;
}

/*
 * Function name:        enter_inv
 * Description  :        Needed to start the room tells
 */
void
enter_inv(object ob, object from)
{
    start_room_tells();
    ::enter_inv(ob, from);
}
/*enter_inv*/

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
    add_action("do_read", "read");
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
        innkeeper = clone_object(DG_DIR + "npc/norgsh");
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
        return ("This large, fieldstone fireplace is set into the north "+
        "wall. Currently, a roaring fire burns brightly in the fireplace, "+
        "casting its flickering light and warmth across the tavern.\n");
    case FIRE_UNLIT_WOOD:
        return ("You see a large, fieldstone fireplace set into the " +
            "northern wall of the tavern. Currently, there are several " +
            "oak logs neatly stacked, just waiting to be lit.\n");
    default:   
        return ("A large, fieldstone fireplace is set into the north "+
            "wall.\n");
    }

    case "fire":
    switch (fire_state)
    {
    case FIRE_BURNING:
        return ("There are several oak logs in the large fireplace, " +
            "crackling as they burn. You can feel the warmth of the fire " +
            "radiating across the entire tavern.\n");
    case FIRE_UNLIT_WOOD:   
        return ("The fireplace is not lit at this time, there is no fire!\n");
    default:
        return ("You find no fire.\n");
    }

    case "wood":
    switch (fire_state)
    {
    case FIRE_BURNING:
        return ("There are several oak logs stacked in the stone " +
            "fireplace, crackling merrily as they burn and providing " +
            "plenty of warmth to the tavern.\n");
    case FIRE_UNLIT_WOOD:
       return ("A large pile of oak logs has been stacked in the fireplace, " +
        "ready and waiting to be lit.\n");
    default: 
        return ("You find no firewood.\n");
    }

    case "ashes":
    switch (fire_state)
    {
    case FIRE_BURNING:
        return ("As you stare into the brightly burning fireplace, you " +
            "notice some ashes gathering on the stone base.\n");
    case FIRE_UNLIT_WOOD:
        return ("You can see some ashes at the bottom of the " +
            "stone fireplace, under the stack of wooden logs.\n");
    default: 
        return ("Ashes cover the bottom of the fireplace.\n");
    }

    default:    /* room long description */
    if (fire_state == FIRE_BURNING)
    {
        return (
        "You are inside the common room of the Rusty Axe, the local tavern " +
        "which serves the soldiers of Dol Guldur. A long, oaken bar runs " +
        "along the south wall serving up the various options for food " +
        "and drink which are displayed on a painted sign nearby. " +
        "Meanwhile, dominating the north side of the tavern is a large " +
        "fireplace which has been constructed from dozens of " +
        "multi-coloured fieldstones set in a grey mortar. A bright fire " +
        "currently blazes furiously inside the fireplace, warming the " +
        "entire tavern and offering plenty of light. A dozen round, " +
        "wooden tables are scattered around the rest of the tavern, " +
        "with chairs haphazardly encircling most of them. The city of " +
        "Dol Guldur is visible through the door in the west wall.\n");
    }
    return (
        "You are inside the common room of the Rusty Axe, the local tavern " +
        "which serves the soldiers of Dol Guldur. A long, oaken bar runs " +
        "along the south wall serving up the various options for food " +
        "and drink which are displayed on a painted sign nearby. " +
        "Meanwhile, dominating the north side of the tavern is a large " +
        "fireplace which has been constructed from dozens of " +
        "multi-coloured fieldstones set in a grey mortar. Currently the " +
        "fireplace stands cold and empty, hopefully the barkeeper will " +
        "light a fire again soon. A dozen round, wooden tables are " +
        "scattered around the rest of the tavern, with chairs haphazardly " +
        "encircling most of them. The city of Dol Guldur is visible " +
        "through the door in the west wall.\n");
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
    return "This wooden chair is of rather simple, yet sturdy, " +
        "construction. \n" +
        sitting_on_chair(CHAIR_NAME, this_player(), 0);
    
    }
}