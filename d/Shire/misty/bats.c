/*
 * A place to hire curious little bat messengers
 * Borrowed code shamelessly from the Ranger HQ PO
 *
 * Varian - 3/9/2019
 * 
 * 2020-08-29 - Cotillion
 * - Limited bat stock and bumped price to 2 GC. 
 *
 */

#pragma strict_types

#include "local.h"
#include <money.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit "/std/room";
inherit "/lib/trade";

#define NUM_BATS  50
#define BAT_VALUE 288 
#define NF0(x)           { NF(x); return 0; }

static int         Fee = BAT_VALUE;
static int         bats = NUM_BATS;
object             actor;

void create_room()
{ 
    set_short("dark recess");
    set_long("You are huddled inside a dark recess at the back " +
        "of this filthy cave. There appears to be a small " +
        "opening covered by bars in the east wall, where the " +
        "cave seems to open up into a larger cavern, where " +
        "a slight flutter of movement on the ceiling catches " +
        "your eye. You should be able to crawl back out to " +
        "the cave entrance west of here.\n");

    add_item( ({"recess", "dark recess"}),
        "This part of the cave is recessed away from the rest " +
        "of the cave that opens up just west of here.\n");
    add_item( ({"cave", "filthy cave"}),
        "This cave is absolutely filthy! The inhabitants here " +
        "really should clean up after themselves.\n");
    add_item( ({"opening", "cavern", "small opening",
            "large cavern", "larger cavern", "eastern wall",
            "east wall"}),
        "There is a small opening in the east wall that is " +
        "covered in iron bars. On the other side of the bars, " +
        "there appears to be a much larger cavern that opens " +
        "up. You notice a small figure on the other side of " +
        "the bars.\n");
    add_item( ({"figure", "small figure", "goblin", 
            "small goblin"}),
        "This is a small goblin, who notices you staring at " +
        "her. She mutely points at a large boulder which " +
        "sits beside her.\n");
    add_item( ({"boulder", "large boulder"}),
        "There are crude letters scratched into the boulder " +
        "which read: hIrE bAT - mANy CoINs. \n\nIt seems like " +
        "you can rent bats here for some reason.\n");
    add_item( ({"entrance", "cave entrance"}),
        "The main entrance to the cave is west of here, " +
        "leading back out to the edge of the Misty " +
        "Mountains.\n");
    add_item( ({"bat", "bats", "black bats", "black bat",
            "ceiling", "up", "movement"}),
        "As you look up, you notice hundreds of bats huddled " +
        "together on the ceiling in the cavern on the other " +
        "side of the bars.\n");
    add_item( ({"bar", "bars", "iron bar", "iron bars", "iron"}),
        "Theare are several iron bars covering the opening in the " +
        "east wall here. A quick tug shows that they are still " +
        "strong and in excellent condition.\n");
    add_item( ({"wall", "walls"}),
        "This is a cave, and somewhat predictably, the walls " +
        "here seem to be made of stone. Was there a particular " +
        "wall you wished to examine?\n");
    add_item( ({"west wall", "western wall", "northwest wall",
            "northwestern wall", "southwest wall",
            "southwestern wall"}),
        "There is no wall in that direction, just the rest of " +
        "the filthy cave.\n");
    add_item( ({"south wall", "southern wall"}),
        "The southern wall appears to be made of solid stone, " +
        "crudely chiseled out in an unsuccessful attempt to " +
        "make the wall smoother.\n");
    add_item( ({"north wall", "northern wall"}),
        "The northern wall appears to be made of solid stone, " +
        "crudely chiseled out in an unsuccessful attempt to " +
        "make the wall smoother.\n");
    add_item( ({"southeast wall", "southeastern wall"}),
        "The southeastern wall appears to be made of solid stone, " +
        "crudely chiseled out in an unsuccessful attempt to " +
        "make the wall smoother.\n");
    add_item( ({"northeast wall", "northeastern wall"}),
        "The northeastern wall appears to be made of solid stone, " +
        "crudely chiseled out in an unsuccessful attempt to " +
        "make the wall smoother.\n");    
    add_item( ({"floor", "ground", "down"}),
        "The uneven ground below your feet appears to be the same " +
        "stone as on the walls and ceiling of this cave. It is " +
        "absolutely covered in guano.\n");
    add_item( ({"guano", "bat guano", "droppings", "bat droppings"}),
        "Droppings. Bat droppings to be precise.\n");

        
    add_exit(MISTY_DIR + "c1", "west", 0, 4);
    set_no_exit_msg( ({"north", "northwest", "northeast", "south",
            "southwest", "southeast"}),
        "You valiantly attempt to walk through a stone wall, " +
        "but alas, you fail.\n");
    set_no_exit_msg( ({"east"}),
        "You attempt to enter the large cavern to the east, " +
        "but the sturdy iron bars are simply too close together.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);  

    config_default_trade();
}

public int

rent_bat(string str)
{
    int     n;
    mixed   res;
    string  give, change;
    object  bat;

    actor = TP;

    if (!strlen(str) || (str != "bat" && str != "a bat"))
    {
       NF0("What exactly do you wish to rent?\n");
       return 0;
    }

    if (!bats) {
        write("The small goblin shakes her head unhappily indicating that " + 
            "she is out of bats.\n");
        return 1;
    }

    if (pointerp(res = pay(Fee, TP)) && (sizeof(res) > 1))
    {
        give = text(res);
        change = text(res[sizeof(MONEY_TYPES)..]);
        write("You toss " + text(res) + " to the small goblin" +
            (strlen(change) ? " and she gives you " + 
                change + " back as change" : "") +
            ".\nA bat swoops down from the ceiling and lands " +
            "on your shoulder.\n");
        tell_room(environment(actor), QCTNAME(actor) + " rents a bat.\n",
            actor);

        bats--;
        bat = clone_object(MISTY_OBJ_DIR + "bat.c");
        if (bat->move(TP)) {
            bat->move(environment(TP), 1);
        }

        return 1;
    }

    write("It seems you do not have enough money to afford a bat.\n");
    return 1;
}

public void
init() 
{
    ::init();

    add_action(rent_bat,  "rent");
    add_action(rent_bat,  "hire");
}

void
reset_room()
{
    bats = NUM_BATS;
}
