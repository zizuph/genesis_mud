/* /d/Terel/mountains/ghastly_keep/rooms/gkeep32.c
 *
 * Dragon's lair in the Ghastly Keep.
 *
 * Znagsnuf
 *
 * 
 * - Language tweak complete (Gorboth)
 *
 */

#include "defs.h";
#include <macros.h>
#include <stdproperties.h>

inherit GKEEP_STD_ROOM;

int torch = 0;

/*
 * Function name: create_keep_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_gkeep_room()
{

    update_longdesc();

    set_short("A dragon's lair");
    set_long("You have come to the lair of Verath the Protective. The "
            + "smell of fear and pain lingers in the air. The room is "
            + "filled with lifelike statues of terrified people. Several "
            + "heaps of bones are stacked against a wall. A skeleton "
            + "holding a @@torch2@@ torch lies before it.\n");

    add_item( ({"lair", "room"}), "The smell of fear and pain lingers in "
               + "the air.\n");

    add_item( ({"statues", "statue", "people", "humans"}), "The statues "
               + "resemble petrified humans running away from something.\n");

    add_item( ({"bone", "bones", "heaps"}), "Several heaps of bones are "
               + "stacked against the wall.\n");

    add_item( ({"wall", "walls"}), "Blood is dripping down the walls, "
               + "leaving a red pattern of sorrow and dread. Spiders "
               + "have woven their tales of woe in a code only the dead and "
               + "the dying can read.\n");

    add_item( ({"spider", "spiders"}), "The spiders are circling around "
               + "the vibrating southwest wall. An outline of a door "
               + "flashes of light in the darkness.\n");

    add_item( ({"southwest", "southwest wall"}), "The southwest wall "
               + "seems to covered in a shroud of magic.\n");

    add_item( ({"torch", "torches", "hand"}), "@@torch@@.\n");

    add_item( ({"skeleton", "skeletons", "stack"}), "The skeleton lies in front"
               + " of the heap of bones stacked against the wall.\n");

    add_item( ({"door", "doors", "veil", "outlines", "outline"}), 
                "@@see_door@@.\n");

    add_cmd_item( ({ "bone", "bones" } ), 
                 ( { "get", "take", "steal" } ), "The heaps of bones have "
                  + "no value to you.\n");

    add_cmd_item( ( { "torch", "torches" } ), 
                 ({"get", "take", "steal"}), "Why would you want to take it? "
                 + "It's better to light it.\n");

    add_cmd_item( ({ "torch", "skeletons torch"} ), 
                 ({ "light", "lights" }), "@@light_torch@@.\n");

    add_cmd_item( ({ "torch","skeletons torch" }), 
                 ( {"extinguish", "extinguishes"}), "@@ext_torch@@.\n");

    add_cmd_item( ( { "pain", "fear" }), 
                 ({"smell", "smells", "sniff"}), "Pure terror surges through "
                 + "your veins, like icy daggers straight to the heart.\n");

    add_exit(GKEEP + "gkeep34", "southeast", "@@block_exit@@",     1, 1);
    add_exit(GKEEP + "gkeep33", "southwest", "@@treasure_check@@", 1, 1);
    add_exit(GKEEP + "gkeep30", "northwest");

    add_npc(GKEEP_NPC + "g_dragon", 1);

    add_prop(OBJ_S_SEARCH_FUN, "search_wall");
    add_prop(ROOM_I_LIGHT, -2);
    add_prop(ROOM_I_INSIDE, 1);

    torch = 0;

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
 * Function name: search_wall()
 * Description  : Make them search the wall
 */
public string 
search_wall(object player, string str)
{  

    object player = TP;

    if(present("verath", TO))
    {
     return "The horrendous ghastly dragon is getting suspicious of your "
           + "activities, and stops you from doing any further "
           + "investigation.\n";
    }

    switch (str)
    {
        case "wall":    
        case "southwest":
        case "southwest wall":    
            player->add_prop("_gkeep_hidden_exit", 1);
            return "You notice something strange with the southwest wall "
            + "\n\nHidden behind a shadowy veil, outlines of a door can "
            + "be seen\n";
            break;
        default:  return "";

    }
    return "";    
}


/*
 * Function name: treasure_check()
 * Description  : A check to see if the player can pass the door. 
 */
int
treasure_check()
{

    if (TP->query_prop("_gkeep_hidden_exit") < 2)
    {
        TP->catch_msg("There is no obvious exit southwest.\n");
        return 1;  
    }
    else
    {
        TP->catch_msg("You slip past the tapestry and into "+
                      "the room beyond.\n");
        TP->remove_prop("_gkeep_hidden_exit");
        return 0;
    }
    return 1;
}

/*
 * Function name: block_exit()
 * Description  : Blocks the exit if the dragon is present.
 * Returns      :   0 -- the player gets through
 *                  1 -- the player is blocked
 */
 
int
block_exit(string room)
{

    object  dragon = present("verath", TO);
    string  dragon_short = dragon->query_nonmet_name();

   if(dragon)
   {
        write("The " + dragon_short + " stop you from going in that "
             + "direction!\n");
        say(QCTNAME(dragon) + " stops " + QCTNAME(TP) + " from going"
        + " southeast.\n", ({TP, dragon}));
        return 1;
   }

   return 0;  
}


/*
 * Function name: do_push()
 * Description  : Makes the door pushable.
 */
int 
do_push(string str)
{

    if (!TP->query_prop("_gkeep_hidden_exit"))
    {
        notify_fail("What?\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Push what?\n");
        return 0;
    }

    notify_fail("Are you trying to push the hidden door?\n");
    if (!parse_command(str, ({ }), " [the] " + "'door' / 'wall'"))
        return 0;    

    // Keep them from spam it.
    if (TP->query_prop("_gkeep_hidden_exit") > 1)
    {
        write("You gently push your right hand against the southwest "
        + "wall.\n\nNothing more seems to happen.\n");
        return 1;
    }

    write("You gently push your right hand against the southwest "
    + "wall.\n\nThe shadowy veil covering the hidden exit leading "
    + "southwest disappears.\n");

    TP->add_prop("_gkeep_hidden_exit", 2);
    return 1;
}

/*
 * Function name: init
 * Description  : Add commands to the player on the deck
 */
void
init() 
{
    ::init();
    add_action(do_push, "push");
}

/*
 * Function name: see_door()
 * Description  : The door is visible if the player has the correct prop.
 */
 
public string
see_door()
{

    if (TP->query_prop("_gkeep_hidden_exit") < 1)
    {
        return "An outline of a door is barely visible in the southwest wall";
    }

    return "Hidden behind a shadowy veil, outlines of a door can be seen. "
          + "\nYou wonder if you somehow can open it";
}

/*
 * Function name: light_torch()
 * Description  : Light the torch
 */
 
public string
light_torch()
{
    if(torch)
    {
        return "The torch held in the skeletons hand, is already lit";
    }
    else
    {
        TO->add_prop(ROOM_I_LIGHT, 2);
        torch = 1;
        tell_room(ENV(TP), QCTNAME(TP) + " lights the torch held in "
               + "the skeletons hand.\n", TP);
        return "You light the torch held in the skeletons hand, the whole "
              + "room radiates in a crimson red light";
    }
}

/*
 * Function name: ext_torch()
 * Description  : Ext. the torch
 */
 
public string
ext_torch()
{
    if(!torch)
    {
        return "The torch held in the skeleton's hand is already extinguished";
    }
    else
    {
        TO->add_prop(ROOM_I_LIGHT, -2);
        torch = 0;
        tell_room(ENV(TP), QCTNAME(TP) + " extinguishes the torch "
              + "held in the skeleton's hand.\n", TP);
        return "You extinguish the torch held in the skeleton's hand. Utter "
              + "blackness creeps back into the room, and engulfs it";
    }
}

/*
 * Function name: torch()
 * Description  : See if its lit
 */
 
public string
torch()
{
    if(torch)
    {
        return "The skeleton is holding a lit torch in his hand";
    }
    else
    {
        return "The torch in the skeleton's hand has burnt out long ago";
    }
}

/*
 * Function name: torch2()
 * Description  : See it its lit
 */
 
public string
torch2()
{
    if(torch)
    {
        return "burning";
    }
    else
    {
        return "burnt out";
    }
}
