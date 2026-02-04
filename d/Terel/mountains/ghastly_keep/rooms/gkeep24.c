/* /d/Terel/mountains/ghastly_keep//rooms/gkeep24.c
 *
 * The crepuscular laboratory within the Ghastly Keep
 *
 *  Created by Znagsnuf.
 *
 *  Relase date:
 *
 *
 *  Date:                      What is done:                           By whom:            
 *  ---------------------------------------------------------------------------
 *  20/04-17                   Language tweak complete                  Gorboth  
 *  27/04-17                   Updated because of potion names         Znagsnuf
 *
 */

#include "defs.h";
#include <macros.h>
#include <stdproperties.h>

inherit GKEEP_STD_ROOM;

/*
 * Function name: create_gkeep_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_gkeep_room()
{
    update_longdesc();

    set_short("Crepuscular laboratory");
    set_long("A narrow overgrown boulder looms in the dark here, witness to "
        + "a science experiment gone wrong. Beyond the overgrown boulder "
        + "lies a large, dusty room. It's covered with dead vermin, broken "
        + "pottery and remains. You also notice a wooden desk, destroyed "
        + "and butchered by time itself. Mounds of soot, layers of dust, "
        + "and ropes of cobwebs cover every surface here in a "
        + "sticky veil. Shriveled brown flowers droop from dismal vases "
        + "and all is dark and dank. Smoke from the strangling fire puffs "
        + "into the air and swirls about the ceiling.\n");

    add_item( ({"boulder", "boulders", "overgrown boulder"}), "This boulder "
        + "has been split into two equal pieces, both are covered with "
        + "moss. You wonder who carried this boulder down here. You also "
        + "notice claw marks along the surface of the boulder.\n");

    add_item( ({"claw", "marks", "claw marks"}), "These marks are made "
               + "by a rather small dragon, maybe an experiment gone "
               + "wrong?\n");

    add_item( ({"moss", "grass"}), "There is moss all around the split "
               + "boulder.\n");

    add_item( ({"vermin", "pottery", "remains"}), "All the corners are "
               + "covered with it.\n");

    add_item( ({"corner", "corners"}), "Its covered with dead vermin, "
               + "broken pottery and remains. A gloomy picture can be "
               + "seen hanging from the east wall.\n");

    add_item( ({"wall", "east wall", "picture"}), "The picture hanging "
               + "on the east wall displays a coven gathered in the "
               + "forest clearing under the full moon. There where six "
               + "of them kneeling at the points of a star, their black "
               + "garb blended with the shadows and faces obscured "
               + "from any accidental onlookers by their black hoods. "
               + "They appear to be chanting in a trance-like "
               + "state.\n");

    add_item( ({"soot", "dust", "cobwebs", "surface"}), "Everything is "
               + "covered with it, making this a most unpleasant place to "
               + "be.\n");

    add_item( ({"desk", "wooden desk"}), "There isn't much left of the "
               + "desk, it seems destroyed and butchered by time itself.\n");

    add_item( ({"flowers", "brown flower", "flower", "vase",
                "brown flowers", "vases"}), 
               "Shriveled brown flowers droop from dismal vases and all is "
               + "dark and dank.\n");

    add_item( ({"smoke", "puffs", "fire", "ceiling", "fire puffs"}), "Smoke "
               + "from the strangling fire puffs into the room and swirls "
               + "about the ceiling.\n");
    
    add_cmd_item(({"desk","wooden desk"}), 
                 ({"push", "move", "pull"}), "There isn't much left on "
                  + "the desk, and certainly nothing of value.\n");

    add_cmd_item(({"boulder","boulders"}), 
                 ({"push", "move", "pull"}), "The boulder is too heavy "
                  + "for you to move.\n");

    add_cmd_item(({"picture","pictures"}), 
                 ({"get", "take", "pull"}), "The picture is nailed to "
                  + "the wall, making it impossible to remove.\n");

    set_no_exit_msg( ({ "northeast", "northwest", "north", "southeast", 
                        "east", "west", "south", "southwest" }),
                        "A wall stops you from walking in that direction.\n");
        
    set_no_exit_msg( ({ "up", "down" }),
                        "After struggling for a while you find out that is "
                      + "not possible.\n");

    add_exit(GKEEP + "gkeep23", "west");

    add_prop(OBJ_S_SEARCH_FUN, "search_desk");

    add_npc(GKEEP_NPC + "g_witch", 1);

    //Fires in the room, emitting light.
    add_prop(ROOM_I_LIGHT,  1);
    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}

/*
 * Function name: reset_room()
 * Description  : Resets the room
 */
void
reset_room()
{
    update_longdesc();
}

/*
 * Function name: search_desk()
 * Description  : Only the player with the right prop might find it.
 *                The player is only able to find one.
 */
public string 
search_desk(object player, string str)
{     

    object potion;
    object witch = present("sabine", TO);

    if(witch)
    {
     return "Suddenly the " +witch->short()+ " points her right crooked finger "
           + "in your direction, forcing you to halt your investigation of "
           + "the wooden desk.\n";
    }

    switch (str)
    {
        case "desk":    
        case "wooden desk":

            if (TP->query_prop("_gkeep_can_find_potion"))
                { 
                    if (random(2))
                    {
                        potion = clone_object(GKEEP_OBJ + "hatred_brew");
                        potion -> move(TP, 1);
                    }
                    else
                    {
                        potion = clone_object(GKEEP_OBJ + "icy_brew");
                        potion -> move(TP, 1);
                    }

                    TP->remove_prop("_gkeep_can_find_potion", 1);
                    tell_room(ENV(TP), QCTNAME(TP) + " locates "
                             +LANG_ASHORT(potion)+ " hidden beneath the wooden "
                             + "desk.\n", TP);
                    return "You locate " +LANG_ASHORT(potion)+ " hidden beneath "
                          + "the wooden desk.\n";
                    break;
                }
                else
                  tell_room(ENV(TP), QCTNAME(TP) + " searches all around the "
                            + "desk but finds nothing.\n", TP);
                return "You search all around the desk, but you can't seem to "
                      + "find anything of use.\n";  
        default:  return "";

    }
     return "";    
}