/* 
 * The base indoor room for Thanarian Church Basement
 * Near the Citadel in Kabal
 * Mirandus - February 21, 2018
 *
 * Update Log: -
 *
 *
 * Map of Church (Basement) - This is a smaller area. It will contain some 
 * cells, torture tools, blood, and be downright gruesome. It will also 
 * have a guilded door that can only be opened if you have the completed
 * Thanarian Medallion from the summon quest. The room beyond will be where
 * the ritual to summon Thanar will take place.
 *                  
 *         U--O--O---O---O--O--U                                                                
 *          \                 /                R - Ritual Chamber                                  
 *           O               O                 U - Stairs to Main Level                                 
 *            \             /                                                   
 *             O           O                                                    
 *              \         /                                                     
 *               O       O                                                      
 *                \     /                                                       
 *                 O   O                                                     
 *                  \ /
 *                   O
 *                   R
 *
 */
#pragma strict_types

#include "../local.h"
inherit "/std/room";
inherit STDIR + "room_tell";
inherit STDIR + "basement_thanar_tells";

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
    
    add_item(({"implements", "torture", "implements of torture", 
        "instruments"}), "Knives, whips, needles and other instruments "
        +"are hung along the wall. They have stains from the blood that has "
        +"been left to dry upon them. The Thanar are known for "
        +"their creative questioning techniques.\n");
    add_item(({"chair", "centre of room", "chairs", "restraints",
        "straps",}), "This chair has "
        +"straps on it to hold a victim in place while they are "
        +"'questioned'. Dried blood is visible in the fabric.\n");
	add_item(({"cages", "small cage", "cage", "small cages"}), "Small "
        +"cages that are no bigger than that of a standard dog, appear to have "
        +"been used to hold prisoners within them.\n");
	add_item(({"blood pools", "pools", "pools of blood","crimson fluid"}),
        "Pools of fresh "
        +"blood have settled on the floor near the chair. The crimson fluid "
        +"looks sticky in the light of the lanterns.\n");
    add_item(({"walls", "wall", "the walls", "the wall"}), "Constructed from "
        + "roughly hewn marble, there apparently is no concern with the "
        + "quality of the walls in this area. The walls are lined at various "
        + "intervals with instruments of torture. Unadorned oil lanterns "
        + "attached at regular intervals providing a grim amount of light.\n");
    add_item(({"lanterns","oil lantern","lantern", "oil lanterns",
        "light", "lights", "lamps", "lamp"}),
          "Common design of black iron these lanterns "
        + "are fed by a system of pipes that carry an endless supply of oil "
        + "automatically. A marvel of a design ensuring endless light to "
        + "cast shadows off the walls.\n");
    add_item(({"ceiling", "ceilings", "beams", "thick wood", 
          "pieces of wood", "wood"}), "The ceilings of the basement are "
        + "supported by beams of wood culled from some unknown "
        + "place and set in support of the ceiling. The ceiling is "
        + "held together by some unknown force. The ceilings are supported "
        + "by powerfully built marble columns.\n");
    add_item(({"floor", "floors"}), "The floors are made of scuffed marble "
        + "tile. Surface is worn, dusty, and covered with dried pools of blood "
        + "along with fresh crimson fluid.\n");
    add_item(({"snake", "symbol", "symbol of thanar", "thanar symbol",}),
          "Visible at various locations is the symbol of small black snake. This "
        + "is the holy symbol of Thanar. It protects the pure from the wicked and "
        + "ensures that the superiority of the human race will be recognized.\n");
    add_item(({"column", "columns", "pillar", "pillars", "marble column",
    "marble columns", "marble pillar", "marble pillars"}), "The ceiling is "
        + "supported by large marble columns and pillars. They are black, "
        + "dark, and stand tall. Engraved the length of the pillar "
        + "is a snake that winds it's way up from the floor to the ceiling.\n");
  
}


int
smell_air(string str)
{
    
    notify_fail("Smell what?\n");
    if (str != "air" && str != "the air" && str != "area" 
    && str != "the area" && str != "blood")
    return 0;
    
    else
    say(QCTNAME(this_player()) +
    " smells the area around them before wrinkling their nose with "
	+"displeasure.");
    write("You smell the air and are overwhelmed with the acridness "
	+"of all the blood in the air. You wrinkle your nose in displeasure.\n");
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