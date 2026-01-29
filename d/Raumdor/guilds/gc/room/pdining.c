/*********************************************************************
 * - dining.c                                                      - *
 * - This is a public dining hall to be used in the                - *
 * - Gentlemans club                                               - *
 * - Created by Damaris 10/2001                                    - *
 * - Last modified by Damaris 1/2/2002                             - *
 *********************************************************************/
#pragma no_clone
#pragma no_inherit
#pragma strict_types
#include <macros.h> 
#include <stdproperties.h>
#include <money.h> 
#include "/d/Raumdor/defs.h"
#include "../guild.h"
inherit CLUB;
inherit "/d/Raumdor/lib/pub";
#include "fireplace.c"
#include "seating1.c"
string
dummy_menu()
{
    read_menu("menu");
    return "";
}
public void
create_guild_room()
{
    set_short("A private dining room");
    set_long("This is a private dining hall. Elegant tables set "+
        "with fine white tablecloths fill the room. In the far "+
        "corner there is a massive fireplace set deep into the "+
        "wall. A large fire dances and flickers brightly within "+
        "it's depths.\n");
    add_item(({"area", "room", "dinning room", "dinning hall", "hall"}),
        query_long);
    add_item(({"wall", "walls"}),
        "The walls are light coloured with etchings drawn upon them.\n");
    add_item(({"floor", "flooring", "ground"}),
        "The floor is made from a hard wood and has been polished "+
        "to a perfect shine.\n");
    add_item(({"etching", "etchings"}),
        "The etchings are of vines and flowers that border the walls "+
        "near the ceiling and the floor.\n");
    add_item(({"ceiling", "roof"}),
        "The ceiling is slightly darkened with age but is still holds "+
        "it's light colouring.\n");
    add_item(({"candles", "candle"}),
        "Cream coloured along with red coloured candles have been "+
        "placed in various spots on the tables.\n");
    add_item(({"table", "tables"}),
        "The tables have been elegantly set with fine china and "+
        "white tablecloths.\n");
    add_item(({"hearth", "fireplace"}),
        "The hearth is large and placed deep within the wall.\n");
    add_item(({"mantle"}),
        "The mantle is long and made of cherry wood.\n");
    add_item(({"fire", "flames"}),
        "The fire dances and flickers providing warmth to the room.\n");
    add_item(({"log", "logs", "wood"}),
        "There is a large stack of logs set next to the fireplace.\n");
    add_item(({"china", "plate", "plates", "place setting", "place settings"}),
        "Fine china place settings have been set upon a few of the "+
        "tables along with long stemmed roses and candles.\n");
    add_item(({"roses", "rose", "red rose", "red roses", "long-stemmed rose",
        "long-stemmed roses"}),
        "The roses are red with long stems that have been placed in "+
        "delicate vases upon a few of the tables.\n");
    add_item(({"tablecloth", "tablecloths", "table cloth", "table cloths"}),
        "There are fine white table cloths placed elegantly on the "+
        "tables in this room.\n");
    add_item(({"bar", "bar counter"}),
        "There is a small bar set up in the corner with bar stools "+
        "in front of.\n");
    add_item(({"east"}), 
        "There is a doorway in that direction.\n");
    add_item(({"chair", "chairs", "barstool", "stool", "barstool", "stools"}),
        seat_desc);
    add_my_desc(seat_desc, this_object()); 
    add_item(({"vase", "vases"}),
        "There are vases that have been placed on the elegant tables "+
        "with stunning red roses in them.\n");
    add_item(({"north", "south", "east", "northwest", "northeast",
        "southeast", "southwest"}),
        "There is a wall in that direction.\n");

    add_drink(({ "brandy", "snifter", "snifter of brandy" }),
      "brandy",
      "snifter",
      200, 40, 50,
      "snifter of brandy",
      "snifters of brandy",
      "It's a snifter of brandy.\n",
      0);
    add_drink(({
            "wine",
            "glass of wine",
            "glasses of wine",
            "white wine",
            "glass of white wine",
            "glasses of white wine",
        }),
        ({"wine", "glass"}),
        "white",
        150, 20, 40,
        "glass of white wine",
        "glasses of white wine",
        "It's a glass of sparkling white wine.\n",
        0);
    add_drink(({
            "wine",
            "glass of wine",
            "glasses of wine",
            "red wine",
            "glass of red wine",
            "glasses of red wine",
        }),
        ({"wine", "glass"}),
        "red",
        150, 20, 40,
        "glass of red wine",
        "glasses of red wine",
        "It's a glass of sweet red wine.\n",
        0);
    add_drink(({
            "water",
            "glass of water",
            "glasses of water" }),
            ({"water", "glass"}),
            ({}),
            100, 0, 8,
            "glass of water",
            "glasses of water",
            "It's a glass of water.\n",
            0);
    add_food(({
            "biscuit",
            "hot biscuit",
            "hot buttered biscuit",
            "buttered biscuit",
        }),
        "biscuit",
        ({"hot", "buttered"}),
        30, 80,
        "hot buttered biscuit",
        "hot buttered biscuits",
        "It is hot with melting butter dripping down its soft " +
            "flaking sides.\nIt looks very tempting.\n",
        0);
    add_food(({
            "roll",
            "hot roll",
            "buttered roll",
            "hot buttered roll",
        }),
        "roll",
        ({"hot","buttered"}),
        30, 80,
        "hot buttered roll",
        "hot buttered rolls",
        "It is hot with melting butter dripping down its soft "+
            "flaking sides.\nIt looks very tempting.\n",
        0);
        add_food(({
                "fillet",
                "roasted fillet",
                "deer fillet",
                "roasted deer fillet",
                "deer",
                "roasted deer",
            }),
            "deer",
            ({"roasted", "deer"}),
            100, 110,
            "roasted deer fillet",
            "roasted deer fillets",
            "It is hot and roasted to perfection. Juices are " +
                "dripping down its tender flaking meat.\n",
            0);
        add_food(({
                "cake",
                "frosted cake",
                "vanilla cake",
                "frosted vanilla cake",
            }),
            "cake",
            ({"frosted","vanilla"}),
            30, 100,
            "frosted vanilla cake",
            "frosted vanilla cakes",
            "It is a frosted cake that smalls of vanilla. The frosting is " +
                "made of cream cheese and has oddly chopped nuts sprinkled " +
                "on it.\n",
            0);

    add_exit("lobby", "west");
    set_no_exit_msg(({"north", "south", "east", "northeast", "northwest",
        "southeast", "southwest"}),
        "You walked into a wall!\n"+
        "Ouch! That's gotta hurt!\n");
    add_room_tell(({
        "The fire flickers and snaps as a dining room attendent "+
        "puts another log on it and stokes the embers.\n",       
        "A young dinging room attendent cleans a table nearby.\n",
        "The aroma of fresh roasted deer lingers in from the kitchen.\n",
    }));
}
void
pub_hook_menu_header()
{
    write(sprintf("%|76s\n\n", "Guest Dining Menu"));
}

/*********************************************************************
 * - This is for smells in the room.                               - *
 *********************************************************************/
void
hook_smelled(string str)
{
    if (!strlen(str) || parse_command(str, ({}), "[the] 'air'"))
    {
        write("The air is filled with sweet wine and roasting deer.\n");
        return;
    }   
}

void
init()
{
    ::init();
    init_pub();
    init_fire();
    init_seat();
}

