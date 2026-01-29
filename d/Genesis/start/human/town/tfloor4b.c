

// /d/Genesis/start/human/town/tfloor4b.c

/* 
 *  This is the fourth floor in the tower of realms
 * 
 *  Coded by Maniac 20/12/96
 *
 *
 *
 *  Styles 2020-09-16:  This floor-file has added functionality to 
 *  find the way to the tower attic. If you add new floors in the  
 *  tower, keep this file as the top floor of the tower to have it 
 *  just below the attic.
 *
 *  The required skills to successfully reach the attic are
 *  SS_AWARENESS >50 and SS_CLIMB >50.
 *
 *
 *  Development status:
 *  I'm currently exploring a way to use hidden add_items that are
 *  non-searchable until they are discovered. The way add_item is
 *  currently implemented even a hidden items existence may be
 *  revealed by using search [itemname] whish will allow 'fishing'
 *  for item names.
 *  
 *  2021-07-27   /Styles.
 *
 */ 


#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <files.h>
#include "/d/Liwitch/sys/liwitch_ss_types.h"
#include "tower.h"
#include "../defs.h"


inherit TOWER_FLOOR;


// Prototypes
public void			  init();
public void	          create_tower_floor();
public string         ladder_desc();
public string         crack_desc();



// Global Variables



/*
 * Function name: create_tower_floor
 * Description  : Creates the floor determined by set_floor_number()
 */
void
create_tower_floor()
{
     set_short("Tower of Realms Floor Four"); 
     set_long("This is the fourth floor of the Tower of Realms. " +
              "The floor and walls are made of polished marble, " +
              "reflecting your image as you look around in wonder. " +
              "From each floor it is possible to access the information "+
              "office of one or more domains. " +
           // "Broad stairs lead up to the next floor of the tower. " +
              "\n<resetskill>\n");

     set_floor_number(4); 

     ADD_FLOOR_ITEMS;

     add_item( ({"south wall", "east wall", "west wall", "north wall", 
                 "wall", "ground"}),"Everything here seems to be made "+
                 "of finely polished marble.\n");

     add_prop(OBJ_S_SEARCH_FUN, "search_cmd");
     add_prop(ROOM_S_MAP_FILE, "tower_map.txt");  // Not registered yet.

     add_exit(TOWN_DIR + "tfloor3", "down", 0);
}



/*
 * Function name: init()
 * Description  : Called when a living object enters the room.
 */
public void
init()
{
    add_action("climb_cmd", "climb");
    add_action("resetskill", "resetskill");
    ::init();
}



/*
 * Function name: ladder_desc
 * Description  : The ladder description.
 */
public string
ladder_desc()
{
    if(this_player()->query_skill(LI_SS_DOMAIN_OFFICE) > 1) 
        return "It is an amazingly well concealed ladder that "+
               "you actually may be able to climb.\n";

    return "You find no ladder.\n";
}



/*
 * Function name: crack_desc
 * Description  : A description of the crack in the north wall.
 */
public string
crack_desc()
{
	if(TP->query_skill(LI_SS_DOMAIN_OFFICE) > 0)
	    return "It is barely visible in the marble wall.\n";

    return "You find no crack.\n";
}



/*
        TP->catch_msg("You start searching the wall.\n");
        say(QCTNAME(TP)+" is inspecting the walls.\n");
 */



/*
 * Function name: search_cmd
 * Description  : The function to call when a search is performed.
 */
public string
search_cmd(object player, string args)
{
    seteuid(getuid(this_object()));

    switch (args)
    {
        case "floor":
        case "ground":
        case "south wall":
        case "east wall":
        case "west wall":
        case "walls":
        case "cieling":
             return  "Your search of the "+ args +" reveals nothing special.\n";
        case "here":
             return "Your general search reveals nothing special.\n";        
        case "wall":
             return "Your search of the wall in front of you reveals nothing "+
                    "special.\n";



        case "north wall":
             // Check if the player awareness is >40
             if (TP->query_skill(SS_AWARENESS) > 40)
             {
                 add_item( ({"wallcrack", "crack"}), "@@crack_desc@@");
                 TP->set_skill(LI_SS_DOMAIN_OFFICE, 1); // USE: 0x00000001
                 return "As you search the north wall you discover a hairline "+
                        "crack. Something is very well hidden in the wall...\n";
             }
             return  "Your search of the "+ 
                     args +" reveals nothing special...\n";



        case "crack":
             // Check if this player has found the crack before.
             if (TP->query_skill(LI_SS_DOMAIN_OFFICE) < 1)
                return "You find no crack.\n";

             // Check if the player has awareness >50 to find the ladder.
             if (TP->query_skill(SS_AWARENESS) > 50)
             {
                 add_item( ({"atticladder", "ladder"}), "@@ladder_desc@@");
                 TP->set_skill(LI_SS_DOMAIN_OFFICE, 2); // USE: 0x00000010
                 return "As you search the thin crack in the wall "+
                        "you realize that it is an amazingly well concealed "+
                        "ladder of some kind. It might be quite tricky but "+
                        "perhaps you may be able to climb it.\n";
             }

             return "As you search the thin crack in the wall "+
                    "you realize that there is more to it than meets "+
                    "the eye. Something is there but you just can't "+
                    "seem to grasp what it is.\n";



        case "ladder":
             // Check if the ladder is known to the player.
             if (TP->query_skill(LI_SS_DOMAIN_OFFICE) > 1)
             {
                 return "The concealed ladder is hard to see "+
                        "and may also be hard to climb.\n";
             }
             return "You find no ladder.\n";

    }
    return "Debug: Unhandled argument to switch()\n";
}



/*
 * Function name: climb_cmd
 * Description  : The function to call when a climb is atempted.
 */
public int
climb_cmd(string cmd) // Someone tries to climb something
{

    //seteuid(getuid(this_object()));

    if(!cmd)
    {
        write("What???\n");
        return 1;
    }

    // Test if the ladder is already known to the player.
	if (TP->query_skill(LI_SS_DOMAIN_OFFICE) > 1)
	{

        // Test if the player has a climbing skill > 50.
        if (TP->query_skill(SS_CLIMB) < 51) //Not skilled.
        {
            tell_object(TP, "You give it a try but the wall is just to "+
                            "smooth to scale, even with the help of the "+
                            "concealed ladder.\n\n");
            say(QCTNAME(TP) +" tries to climb the wall but fails.\n");

            return 1;
        }


        // Is skilled.
		tell_object(TP, "You climb up the hidden ladder.\n"+
			  "Just as you reach the top you feel a strange force "+
			  "pulling you up through the ceiling.\n\n");
		say(QCTNAME(TP) +" suddenly scurries up the wall "+
			  "and disappears with a popping sound!\n\n");

		remove_item("wallcrack");
        remove_item("atticladder");


		// Move the player up to attic.
		TP->move_living("M", "/d/Liwitch/common/player_domain_office", 1, 0);

        return 1;
	}


    // Ladder is not known to the player.
	write("What??\n");
    return 1;
}



/*
 * Function name: resetskill
 * Description  : Debug function that resets this players
 *                LI_SS_DOMAIN_OFFICE skill to 0.
 */
public void
resetskill()
{
    TP->set_skill(LI_SS_DOMAIN_OFFICE, 0);
    write("LI_SS_DOMAIN_OFFICE set to "+ 
        TP->query_skill(LI_SS_DOMAIN_OFFICE) +"\n");
    return;
}
