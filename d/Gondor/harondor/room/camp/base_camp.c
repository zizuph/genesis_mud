/* Name      : /d/Gondor/harondor/room/camp/base_camp.c
 * Purpose   : The file handling the general descriptions
 *             for the camp and the callouts can be found
 *             last in the file.
 * Created by: Sir Toby, Gondor Domain, 2005-11-20
 * 
 *
 * Borrowed/reused code to check if to block players
 * from Gnadnar's: /d/Gondor/ithilien/forest/camp.c
 *
 *
 * This room:
 *	provides check_allow() to determine if any stopping npcs
 *	  see this player().
 *	if inheriting room calls set_tent_path() with the name
 *	  of the corresponding tent, takes care of "enter tent".
 *
 *   Modified: 2005-11-21, Sir Toby
 *                         Added the code to check for the 
 *                         random exit.
 *             2006-02-28, Sir Toby
 *                         Fixed cloning with make_haradrim
 *                         and moved it to npc_cloning.c
 *             2006-03-03, Sir Toby
 *                         Made updates to the check_allow()
 *                         Now it checks if the NPC can see the 
 *                         one it tries to block and also if 
 *                         its dark in the room.
 *             2007-02-21, Lord Toby
 *                         Added a random check to allow players
 *                         to escape from blocks to not make the
 *                         area a total death trap.
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/friend_or_foe";


#include <macros.h>
#include <filter_funs.h>
#include <ss_types.h>

#include "/d/Gondor/harondor/room/camp/defs.h"
#include "/d/Gondor/sys/sunlight.h"
#include "/d/Gondor/std/tell.c"

#include "/d/Gondor/harondor/room/camp/npc_cloning.c"

public void	set_tent_path(string path);
public void	set_move_msg(string move_msg);
public void	create_camp();
public int	check_allow();
public string	enter_tent();

static string	Tent_path;
static string	Move_msg = "";
static string	And_move_msg = "";

public void add_harad_camp_tells();

#define QUERY_WIND_OPEN (HAR_RM_DIR + "camp/wind_check_open.c")

public void
create_camp()
{
}

public void
create_area_room()
{
    create_camp();

    // Is this right to set the daylight for a blazing desert sun?
    // Should piss the vamps off, and I like that. They need a challenge too.

    add_prop("_room_i_sunlight", SUNLIGHT_BLAZING);

    if ( strlen(Tent_path) )
	add_cmd_item( ({ "tent", "large tent", }),
	    "enter", enter_tent);
}

public void
set_tent_path(string path)	
{ 
   Tent_path = path;
}

public void
set_move_msg(string move_msg)
{
    And_move_msg = " and "+move_msg;
    Move_msg = "You "+move_msg+".\n";
}

public string
enter_tent()
{
    if (!check_allow())
    {
        ENV(TP)->set_dircmd("tent");
        write("You step into the large tent.\n");
        TP->move_living("into the large tent", Tent_path);
    }
    return "";
}


/* Function name: check_allow()
 * Description  : The function handles the ability for npc to block players.
 *                It checks: CAN_SEE, player's SS_SNEAK >= npc's SS_AWARENESS
 *                and !fighting in all cases. This is true for all stopping
 *                npcs in the room, in case their abilities differ.
 *                It also checks that the player is actually sneaking.
 * Arguments    : -
 * Returns      : int 1/0 - player is stopped/let pass
 */
public int
check_allow()
{
    object	*stoppers, *can_see;
    int		aware, aware_max, i, s;

    if(random(100) < 15)
    {
        write("Haradrim in the camp look your way, but apparently does not register " +
              "or care enought to bother.\n");
        return 0;
    }

    if (query_friend_or_foe(TP) == -1)
        return 0;

    stoppers = filter(all_inventory(TO), &->id("_stopping_npc"));

    if ( !(sizeof(stoppers)) )
    {
	    write(Move_msg);
	    return 0;
    }

    can_see = FILTER_CAN_SEE(stoppers, TP);
    
    if ( !(s = sizeof(can_see)) )
    {
        write("You sneak past the " + stoppers[0]->query_race_name() + 
	    And_move_msg + "!\n");
	    return 0;
    }

    if ( !TP->query_attack() )
    {
	    i = aware_max = 0;
	    while ( s-- > 0 )
	    {
	        if ( (aware = can_see[s]->query_skill(SS_AWARENESS)) > aware_max )
	        {
		        i = s;
		        aware_max = aware;
	        }   
	    }
                                                 // New part (CAN_SEE)
	    if ( TP->query_skill(SS_SNEAK) >= aware_max || !CAN_SEE(can_see[i], TP))
	    {
           write("You sneak past the " + can_see[i]->query_race_name() + 
		          And_move_msg + "!\n");
	       return 0;
	    }
    }

       // New part to check if NPC can see in room
    if(CAN_SEE_IN_ROOM(can_see[i]))
    {
       write("The " + can_see[i]->query_nonmet_name() +
	      " looks straight at you and forcefully stops you from going that way.\n");
       return 1;
    }
    else
    {
       write("Using the cover of darkness you tread your way past the " + 
             can_see[i]->query_race_name() + And_move_msg + "!\n");
       return 0;
    }
}

/* Function name: wind_block
 * Description  : Gets called from room, argument is mandatory.
 * Arguments    : string dir - The west or east part of the 
 *                camp calling the function.
 * Returns      : int 1/0 - closed/open
 */
int wind_block(string dir)
{
   if(QUERY_WIND_OPEN->query_wind_open(dir))
      return 0;

   write("The mounds have grown too big to pass in that direction.\n");
   return 1;
}

/* ===============================
 * ====== Room descriptions ======
 * ===============================
 */


/*
 * Function name : add_tall_tents
 * Description   : adds descr of tents for in south camp
 */
void add_tall_tents()
{
    add_item( ({ "tent", "tents" }),	
	    "The tents appear to be well-maintained and made of canvas. They " +
        "are square shaped and rather low. There is one tent larger then " +
        "the others with its tent flaps open.\n");
    add_item( ({ "large tent"}),	
	    "A large tent that appear to be well-maintained and made of canvas. " +
        "It is rectangular shaped with its entrance on one of the short sides " +
        "and the tent flaps are put aside.\n");
    add_item(({"canvas"}),
        "It is a gray material used to make the tents. It is tightly woven " +
        "and looks very sturdy. The material appears to be in good condition.\n");    
}

/*
 * Function name : add_large_pavilion
 * Description   : adds descr of the large pavilion in south camp
 */
void add_large_pavilion()
{
    add_item(({"pavilion", "large pavilion", "colorful pavilion",
               "large colorful pavilion"}),	
	    "The large and colorful pavilion appear to be well-maintained and made " +
        "of canvas. It stands taller, with its wooden corner poles driven deep " +
        "into the sand, than an average man with a broad open entrance. The " +
        "roof is almost flat apart from what could be a centerpole holding it " +
        "up from inside. Along the sides, where the roof meets the sides, " +
        "colored canvas have been draped. Bright colors in red, yellow and blue. " +
        "Right next to the pavilion a quite large tent have been errected.\n");
    add_item( ({ "large tent"}),	
	    "A large tent that appear to be well-maintained and made of canvas. " +
        "It is rectangular shaped with its entrance on one of the short sides " +
        "and the tent flaps are put aside.\n");
    add_item(({"canvas"}),
        "It is a gray material used to make both the pavilion and the tent. It " +
        "is tightly woven and looks very sturdy. The material appears to be in " +
        "a very good condition.\n");    
}

/*
 * Function name : add_small_pavilion
 * Description   : adds descr of the the small pavilions in south camp
 */
void add_small_pavilion()
{
    add_item( ({ "pavilion", "small pavilion" }),	
	    "The large pavilion appear to be well-maintained and made of canvas. It " +
        "stands taller then an average man with a broad open entrance.\n");
    add_item(({"canvas"}),
        "It is a gray material used to make the pavilion. It is tightly woven and " +
        "looks very sturdy. The material appears to be in a very good condition.\n");    
}

/*
 * Function name : add_animal_pens
 * Description   : adds descr of animal pens
 */
void add_animal_pens()
{
    add_item(({"pens", "animal pens", "small pens"}),
        "These are areas sectioned of by fences. A variety of animals " +
        "are kept in them, some for eating, and others for riding.\n");
    add_item(({"fences"}),
        "The fences are made of rails and fence posts and surround " +
        "the pens. They are crude looking but effective in keeping " +
        "the animals in.\n");
    add_item(({"fence posts", "posts"}),
        "They are spaced evenly around the perimeter of the pens. " +
        "The posts are from hewn trees and sunk into the ground. " +
        "Wooden rails are connected to the fence posts\n");
    add_item(({"rails", "wooden rails"}),
        "These are long trees that are connected together and attached " +
        "to the fence posts.\n");
}

/*
 * Function name : add_ephel_duath
 * Description   : adds descr for Ephel Duath
 * Arguments:    : string str - mandatory
 */
void add_ephel_duath(string str)
{
    add_item(({"mountain", "mountains", "ephel duath", "peak",
        "peaks", "slope", "slopes"}), "The peaks of the Ephel Duath " +
        "loom ominously in the distance. They look jagged and evil, " +
        "rising to the " + str + ".\n");
}


/*
 * Function name : add_desert
 * Description   : adds descr for the desert
 */
void add_desert()
{
    add_item(({"wasteland", "desert", "arid land", "ground", "land", "area"}),
        "The land is barren and dry. Very little grows here among the " +
        "rocks and sand except for dried grass. It is brown and parched, " + 
        "and very hot.\n");
    add_item(({"grass", "dried grass", }),
        "It is short and thin, and dried out. The grass is little more " +
        "than stubble in this wasteland.\n");
    add_item(({"rocks"}),
        "They are fragments of large rocks. They are chipped and hard " +
        "looking, and lay scattered across the arid wasteland.\n");
    add_item(({"sand", "grit"}),
        "These are small, loose grains of disintegrated rocks. They are " +
        "dark colored, making the ground look a dark color.\n");
}


/*
 * Function name : add_harad_camp_tells
 * Description   : adds callouts to the camp
 */
public void add_harad_camp_tells()
{
    set_tell_time(225+random(50));
    add_tell("Hot winds blow across the dry land. The wind makes the tents canvases flap.\n");
    add_tell("Nearby animals make a ruckus in their pens.\n");
    add_tell("Dark clouds blow across the sky.\n");
    add_tell("An evil looking craban flies far overhead.\n");
    add_tell("A male haradrim walks out of a tent and hurries into another tent.\n");
}
