/* File:    /d/Avenir/common/obj/sair_wall.c
 * Created: Lilith, June 2015
 * Purpose: Clonable object file that makes a Sair Wall with an octagon
 *          on it that players can interact with. If they have a fire opal
 *          they have a chance of being moved through the wall by Sair
 *          to another room. 
 *          Sair is the Goddess of Walls and Obstacles in Sybarus. 
 *
 * Since this is an object, there is a greater chance of player interaction
 * issues.  If you want to have a Sair Wall in a room, please consider
 * using /d/Avenir/inherit/sair_wall.c instead. This file is best used
 * in instances when you want to be able to easily add and remove access
 * to the teleportation aspects. For example, if someone makes an offering
 * at an altar and it "activates" an octagon for a short window of time. 
 *   -- Lilith 
 *
 * Instructions: 
 *    Clone this file to a room and be sure to call this function 
 *    in the object when you move it to the room.      
 *      
 *      set_sair_dest(({"room1.c", "room2.c, "room3.c"}));
 *
 * Example using reset_room
 *
 *   object wall;  
 *   void
 *   reset_room()
 *   { 
 *        if (!wall)
 *        {	
 *           wall = clone_object("/d/Avenir/common/obj/sair_wall");
 *	         wall->set_sair_dest(({"/d/Avenir/common/outpost/bridge"
 *	                               "/d/Avenir/common/dark/l2/add/t36"}));
 *	         wall->move(this_object(), 1);
 *	      }
 *	    ::reset_room();
 *   }
 *
 *   You could also inherit it and customize it as a unique object.
 *   See /d/Avenir/common/dark/obj/wall_sair.c for an example.
// Updates:    Lilith Sept 2021 made it so set_sair_dest will take an array of rooms.
//                 and query_sair_dest would choose randomly from the list of rooms.
//                 Updated descriptions in place_it() to be more exciting.
//                 Added IS_INFIDEL check: the goddess will drop them at the 
//                 ship to Sparkle no matter what.
//    Lilith May, 2022: bug fix with query_short in the place_it func
*/
#pragma strict_types

inherit "/std/object";
#include "/sys/cmdparse.h"
#include "/sys/language.h"
#include "/sys/macros.h"
#include "/d/Avenir/smis/sys/statserv.h"
#include "/d/Avenir/include/relation.h"

string *room_list;

/*
 * Function name: mod_list 
 * Description:   Routine to add elements to a list
 * Arguments:     list: The list of elements
 *                elem: string holding one new element.
 *                first: True if it is the main element, 
 * Returns:       The new list.
 */
public string *
mod_list(string *list, mixed elem, int first)
{
    string *e;

    if (obj_no_change)
        return list;

    if (pointerp(elem))
        e = elem;
    else
        e = ({ elem });

    if (!pointerp(list))
        list = ({ }) + e;
    else if (first)
        list = e + (list - e);
    else
        list = list + (e - list);

    return list;
}

/* set_sair_dest() 
 * Allows an array of locations to be set for moving players to.
 * If this isn't set, the place() function has a default room set.
 * Argument: string dest - the destination(s) to be moved to.
 */
public void set_sair_dest(mixed dest)
{   
    room_list = mod_list(room_list, dest, 1);
}

/* query_sair_dest()
 * Will choose a random room from the list provided.
 * Returns: string - one of the rooms from the list.
 */
public string query_sair_dest()
{
    return (one_of_list(room_list));
}

/* sair_search()
 * Can be masked for a custom message but don't forget to 
 * add the prop to the player or the place_it() function will
 * always fail.
 * Returns: string - Result from searching the wall in the room.
 */
public string sair_search()
{ 
    this_player()->add_prop("_avenir_found_sair_symbol", 1);
    return "You search the wall.\n Your sensitive fingertips find an octagon "
        +"shape carved into the wall.\n";	
}
/*
 * sair_symbol()
 * What the player sees when they look at the symbol/octagon.
 * Can be masked for a custom message.
 * Returns: string - symbol description. 
 *
 */ 
public string sair_symbol()
{
    if(this_player()->query_prop("_avenir_found_sair_symbol"))
	{
        return "There is an octagon carved into the wall. This is a "
		    +"fairly common practice in Sybarus. It honors the "
			+"Goddess Sair, builder, keeper, and destroyer of walls.\n";
	}
	else
	    return "What?\n";
}    
	

void
create_object()
{
	set_name(({"wall"})); 
	add_name("_Avenir_Sair_Wall");
	set_long("It is a wall much like all the others in this place.\n");
	add_cmd_item(({"wall"}), ({"feel", "touch", "search"}), "@@sair_search");
    add_item(({"carving", "octagon"}), "@@sair_symbol");
    // This is the room sacred to Sair. Over-ride of you want.	
    set_sair_dest("/d/Avenir/common/dark/l2/add/t36");
	add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
	add_prop(OBJ_M_NO_GET, 1);	
	
	/* Players cant see it but they can interact with it */
	set_no_show_composite(1);
	
    /* If you want the Sair Wall to activate, you need to
     * set_sair_dest("path of new room");
	 * otherwise this will just be a wall with an octagon on it.
     */	 

}

/* place_it()
 * This is the add_action added to the room via init().
 * It enables players to try placing an object against the octagon 
 * symbol on the wall to activate Sair's blessing - which moves the 
 * player through the wall to another place.
 * Requires a fire opal for success.
 * Success moves player to one of the rooms listed in the 
 * set_sair_dest function. The fire opal is dested.
 */
public int place_it(string str)
{
    string what;
    object *obs, ob;
    
	notify_fail(capitalize(query_verb()) + " what where?\n");
    if (!strlen(str))
	return 0;
	
	if(!this_player()->query_prop("_avenir_found_sair_symbol"))
	    return 0;
	
	/* place fire opal on the octagon */
    if (!parse_command(str, ({}),
	    "[the] %s 'on' / 'onto' / 'into' / 'in' / 'to' / 'against' [the] "
		+"'octagon' / 'octagonal' [carving] / [shape] / [carved] [on] / [in] "
		+"[the] [wall]", what))
    {
	    return 0;
    }
    obs = FIND_STR_IN_OBJECT(what, this_player());
    if (!sizeof(obs))
	    return 0;
    
	ob = obs[0];
	/* using query_short() instead of short() intentionally */
    if (ob->query_short() != "fire opal")
    {
	    write(capitalize(LANG_THESHORT(ob)) + " is not the right shape or size.\n");
	    return 1;
    }
    write("You " + query_verb() + " the fire opal against the "
	    +"octagon carved in the wall.\n");
	
	/* Will fail about 66% of the time */ 
    if (random(3) != 2)
    {
	   write("Hmm. Nothing happens.\n");
	   return 1;
    }
	
	/* It's working. Lets reduce the num of opals by 1. */
	ob->reduce_heap_size(1);
	this_player()->catch_msg("The gem you were using disappears!\n");	
    tell_room(environment(this_object()), "A section of wall suddenly "
	    +"transforms into a giant hand and a huge red-gold eye stares "
		+"at you.\nAn intense flash of orange-red light momentarily "
		+"blinds you.\n");	
	this_player()->catch_msg("\nYou feel yourself being engulfed and "
        +"pulled into the wall!\n\n");
		
    /* Let's get a destination and move the player there. 
	 * If there isn't one set, then use the default: 
	 * the utterdark room with Sair's Pillar
	 */
    string move_to = this_object()->query_sair_dest();
	
	if (!move_to)
		move_to = "/d/Avenir/common/dark/l2/add/t36"; 
	
	/* If player is an infidel, show them the door. */
	if (IS_INFIDEL(this_player()))
	   move_to =  "/d/Avenir/common/port/port11";
		
	/* Now move the player to where they should go */	
    this_player()->move_living("M", move_to, 1, 0);   
	
	/* Now remove the prop since they are moving to a new room. */
    this_player()->remove_prop("_avenir_found_sair_symbol");
	STATSERV_LOG_EVENT("Sair", "used Sair's wall");
	return 1;
}

public void
init(void)
{
	/* If set_sair_dest() was called when this was cloned, 
	 * then add these actions: 
	 */
    if (query_sair_dest())
    {		
        ::init();
        add_action(place_it, "place");
	    add_action(place_it, "fit");
        add_action(place_it, "lay");
		add_action(place_it, "match");
	    add_action(place_it, "overlay");
		add_action(place_it, "insert");
	}
	
}
