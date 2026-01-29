/* 
 * The base indoor room for Thanarian Church
 * Near the Citadel in Kabal
 * Mirandus - January 16, 2018
 *
 * Update Log: -
 *
 *
 * Map of Church (Main Level) - The idea is you're walking around a huge
 * big room. This is why things are visible from everywhere. The pews are
 * what determine the path you can follow.
 *                    o                             o                                          
 *                   / \                           / \                                               
 *                  o   o         SANCTUM         o   o                                              
 *                 /     \   pews  pews  pews    /     \                                              
 *                o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o                                              
 *              pews pews\  pews  pews  pews   / pews pews                                             
 *              pews pews o-o-o-o       o-o-o-o pews pews                           
 *                  pews   \     \ALTAR/     /    pews                            
 *               pews  pews o     o-o-o     o pews  pews                                                          
 *               pews  pews  \    / | \    /  pews  pews 
 *               pews  pews   o-o-o-o-o-o-o   pews  pews                                                         
 *                                 \|/                                                 
 *                                o-E-o                                                    
 *                                  |
 *                                Street                        
 *
 *
 * The High-Lord DID try to push the Thanar underground as their power
 * was growing too strong. In the end, the Avatar of Thanar returned granting
 * too much power to the Thanarian order and he was forced to reopen their
 * church in the city and allow them to return above ground.
 */
#pragma strict_types

#include "../local.h"
inherit "/std/room";
inherit STDIR + "room_tell";
inherit STDIR + "thanar_tells";

/* Definitions */


/* Prototypes */
public nomask void  create_room();
public void         create_std_thanar();
public void         add_thanar_items();

string smell_air(string str);

/*
 * This function creates the room
 */
public nomask void
create_room()
{
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);
    create_std_thanar();
    add_thanar_items();
    set_tell_time(random(400) + 90);
    add_tell("@@get_tells@@" + "\n");
    //add_prop(ROOM_S_MAP_FILE, "/d/Kalad/open/MAP_FILES/new_thanar_church.txt");
    
}
/* Function name:        create_std_thanar
 * Description  :        dummy function for inheriting rooms to mask
 */
public void
create_std_thanar()
{
    set_short("a set_short is needed here");
    set_long("A set_long is needed here.\n");
    
} 
/*
 * Function name:        add_thanar_items
 * Description  :        Adds the standard items for the road
 *
 */
public void
add_thanar_items()
{  
    
    add_item(({"walls", "wall", "the walls", "the wall"}), "Constructed from "
        + "beautifully hewn black marble, The walls have beautifully "
        + "elaborate oil lanterns attached at regular intervals providing "
        + "an adequate, if not grim, amount of light. They are adorned are "
        + "certain instances along the walls are opulent framed oil "
        + "paintings.\n");
    add_item(({"lanterns","oil lantern","lantern", "oil lanterns",
        "light", "lights", "lamps", "lamp"}),
          "Marvellously designed with flourishes of black iron these lanterns "
        + "are fed by a system of pipes that carry an endless supply of oil "
        + "automatically. A marvel of a design ensuring endless light to "
        + "cast shadows off the black marble walls.\n");
    add_item(({"ceiling", "ceilings", "beams", "thick wood", 
          "pieces of wood", "wood"}), "The ceilings of this church are "
        + "constructed from massive beams of wood culled from some unknown "
        + "place and set in support of the steel ceiling in a marvel of "
        + "ingenuity and engineering. The steel slats on the ceiling are "
        + "held together by some unknown force. The ceilings are supported "
        + "by powerfully built marble columns.\n");
    add_item(({"floor", "floors"}), "The floors are made of polished marble "
        + "tile. The black surface shows no signs of dirt or dust and appears "
        + "well tended.\n");
    add_item(({"pew", "pews", "seat", "seats", "benches", "bench"}), "Pews "
        + "are visible from most places within the church. Made of a dark "
        + "unknown wood, they shimmer in the dim light cast by the lanterns "
        + "attached to the walls. They look as though they would not be "
        + "uncomfortable, but they offer no luxury.\n");
    add_item(({"snake", "symbol", "symbol of thanar", "thanar symbol",}),
          "Visible at various locations is the symbol of small black snake. This "
        + "is the holy symbol of Thanar. It protects the pure from the wicked and "
        + "ensures that the superiority of the human race will be recognized.\n");
    add_item(({"column", "columns", "pillar", "pillars", "marble column",
    "marble columns", "marble pillar", "marble pillars"}), "The ceiling is "
        + "supported by large marble columns and pillars. They are black, "
        + "shimmering and stand tall. Engraved the length of the pillar "
        + "is a snake that winds it's way up from the floor to the ceiling.\n");
    add_item(({"sanctum", "sanctum sanctorum", "holy place", "holy space", 
    "sanctuary"}), "From where you stand you can see the sanctum, or sanctum "
        + "sanctorum. This is the most sanctified space within the Cathedral "
        + "and is only accessible to the Priests. Items of great import can "
        + "be kept there. You can see shimmering objects along with tomes "
        + "and scrolls.\n");
    add_item(({"shimmering items", "treasures", "tomes", "books", "tome", 
    "book", "holy tomes", "holy books", "holy tome", "holy book",
    "shimmering item", "shimmering object", "shimmering objects"}),
        "Behind the sanctum you see a variety of items shimmering and dull. "
        + "The glittering gold of crosses, coins, and jewelery along with gems "
        + "and encrusted books. Dusty tomes are stacked on shelves created from "
        + "the marble walls. Scrolls are neatly stacked within a marble scroll "
        + "store. Details can not be seen from outside the santum.\n");
}

int
smell_air(string str)
{
    
    notify_fail("Smell what?\n");
    if (str != "air" && str != "the air" && str != "area" 
    && str != "the area" && str != "incense"   && str != "smoke")
    return 0;
    
    else
    say(QCTNAME(this_player()) +
    " smells the area around them subtly, inhaling deeply with a calming "
    +"smile.\n");
    write("You smell the air around you and immediately feel calm from the "
    +"marvellous incense.\n");
    return 1;
}

/*
 * Function name: get_all_no_exits
 * Description: Returns an array of strings with exits for use with
 *              set_no_exit_msg()
 * Argument: Array of exits to exclude, for simplicity you can use
 *           nw instead of northwest, etc.
 */
string *
get_all_no_exits(string *exits)
{
    string *r_exits = m_values(NORMAL_EXITS);
    foreach (string exit: exits) {
        foreach (string ind, string val: NORMAL_EXITS) {
            if (exit == ind || exit == val) {
                r_exits -= ({ val });            
            }
        }
    }
    return r_exits;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        start_room_tells();
    }
}

public void
init()
{
    ::init();
    add_action(smell_air, "smell");
}