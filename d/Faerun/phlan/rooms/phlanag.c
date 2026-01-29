/*
 * Example Adventurers Guildhall, giving an example of how
 * to use the new functions within /lib/skill_raise.c
 * implemented by me, Lucius.
 *
 *   Adapted for Phlan by Tharizdun, 2021
 */

/*
 * This makes us write proper code.
 */
 
#pragma strict_types

/*
 * Standard inherits.
 */
 
inherit "/std/room";
inherit "/lib/skill_raise";
inherit "/lib/guild_support";

/*
 * Include this for the skill type defines.
 */
 
#include <ss_types.h>
#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "defs.h"

/*
 * This function adds our skills into the adventurer hall.
 */
 
private void
set_up_skills()
{
    
/*
 * This sets up the basics for us, from /lib/skill_raise.c
 */
 
    create_skill_raise();

/*
 * This is how we add skills into the adventurer guild.
 *
 * The strings are blank because we want to use the mud default
 * messages for the skill name and improve messages.
 *
 * The cost factor is only used on special skills, mudlib overrides
 * any setting you place for mudlib skills.
 *
 * The last value set is how high we can train here.
 */
 
    sk_add_train(SS_WEP_AXE,	  "", "", 0, 20);
    sk_add_train(SS_AWARENESS,	  "", "", 0, 20);
    sk_add_train(SS_DEFENCE,	  "", "", 0, 20);
    sk_add_train(SS_HERBALISM,    "", "", 0, 20);
    sk_add_train(SS_LOC_SENSE,	  "", "", 0, 20);
    sk_add_train(SS_TRADING,      "", "", 0, 20);    
}

/*
*   Check to see if player is on quest
*/

int
check_quest()
{
    if(this_player()->query_prop("_phlan_tour3_start"))
    {
        this_player()->remove_prop("_phlan_tour3_start");
        this_player()->catch_msg("You are ready to return to Daari for your reward.\n");
        this_player()->add_prop("_phlan_tour3_prop", 1);        
        return 0;
    }
} 

/*
 * This sets up our room descriptions, and some basic values.
 */
 
public void
create_room()
{
    ::create_room();

    set_short("Training Hall");
    set_long("This squat brick building has several training areas. You"
        +" notice a training dummy with deep slashes, reed tumbling mats"
        +" jars with various plants, maps and textbooks. Iron lamps are"
        +" mounted on the walls in various places. The doorway to the street"
        +" is to the east. In one peaceful corner are rugs for meditation.\n");

    add_item(({"dummy", "training dummy"}), 
    "A training dummy on a pedestal"
        +" shows deep hacking slashes. It is made to look like an orc.\n");

    add_item(({"mat", "mats"}), 
    "These mats are being used by students practicing"
	    +" safe falling, rolling and evation tactics.\n");
        
    add_item(({"jar", "jars", "plant", "plants"}), 
    "Various herbs and plants are on display here along with flashcards"
        +" giving key details about them.\n");

    add_item(({"map", "maps"}), 
    "There are various topographical maps along with compasses and protractors"
	    +" for determining position on a grid map.\n");     

    add_item(({"book", "books", "textbook", "textbooks"}), 
    "Books on economics, sales, and observation skills sit on desks"
        +" in a semi-circle around the trainers.\n");

    add_item(({"desk", "desks"}), 
    "Small uncomfortable desks where you would not want to spend a"
	    +" prolonged period of time.\n");        
        
    add_item(({"wall", "walls"}), 
    "The walls are of unadorned brick.\n");

    add_item(({"brick", "bricks"}), 
    "The bricks are common red construction  material with no frills.\n");

    add_item(({"ceiling"}), 
    "The ceiling is of simple wooden beams.\n");

    add_item(({"floor", "ground"}), 
    "Wooden floors with signs of years of use that are kept clean"
	    +" by the younger students and apprentices.\n");        
        
    add_item(({"lamp", "lamps"}), 
    "Iron lamps are mounted to the walls in regular intervals giving"
        +" even and contstant illumination.\n");

    add_item(({"rug", "rugs"}), 
    "Coarsely woven rugs for meditating.\n");

    add_item(({"door", "doorway"}), 
    "The door to the east leads back to the street.\n");    

    add_exit(ROOM_DIR + "road19", "east");

/*
 * Call to the above function so we have some skills to train here.
 */
 
    set_up_skills();
}

/*
 * Need this here to add the guild commands onto players as they enter
 */
 
public void
init()
{
    ::init();

/*
 * There are add_actions defined in the two inherit files,
 * /lib/skill_raise.c and /lib/guild_support.c
 * They give us the 'meditate' 'list' 'learn' and 'improve' commands.
 */
 
    init_skill_raise();
    init_guild_support();
}


