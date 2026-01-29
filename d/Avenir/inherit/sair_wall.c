/* File:    /d/Avenir/inherit/sair_wall.c
 * Created: Lilith, June 2015
 * Revised: Lilith, Oct 2021: made it so set_sair_dest will take an 
 *                  array of rooms, and query_sair_dest would choose 
 *                  randomly from the list of rooms.
 *                  Updated descriptions in place_it() to be more interesting.
 *                  Added more verbs to interact with the wall.
 *                  Added IS_INFIDEL check: the goddess will drop them at the 
 *                  ship to Sparkle no matter what.
 *                  Made it so the Sair Wall desc is appended to the add_item.
 *          Lilith, May 2022: bug fix with query_short in the place_it func.
 *
 * Purpose: Inheritable file that makes a Sair Wall with an octagon
 *          on it that players can interact with. If they have a fire opal
 *          they have a chance of being moved through the wall by Sair
 *          to another room. 
 *          Sair is the Goddess of Walls and Obstacles in Sybarus. 
 *
 * Instructions: 
 * 
 * inherit "/std/room"; or /d/Avenir/inherit/room
 * inherit "/d/Avenir/inherit/sair_wall";
 *
 * void
 * create_room()
 * {
 *     set_short("It is a short");
 *     set_long("This is my long.\n");
 * 
 *     // do add_item for the wall here, or...
 *
 *     set_sair_dest(({"room1.c", "room2.c, "room3.c"}));
 *     add_sair_wall();
 *
 *     // ... do add_item for the wall here. See below. 
 * }
 * 
 * public void
 * init()
 * {
 *     ::init();
 *     sair_init();  
 * }
 *
 * Important Note:
 *     You will need to do an add_item() with the wall description.
 *
 *     The location of the add_item() before or after the add_sair_wall()
 *     influences what the player sees. 
 *     
 *     If you do the add_item() before the add_sair_wall() then the line:
 *          "It looks like some shape may be carved into the wall "
 *            +"here but it is hard to tell.\n" 
 *     is appended to the add_item you provided above it.
 *
 *     If you place the add_item() for the wall description after the 
 *     add_sair_wall() then there will be no indication that there is
 *     a mark on the wall unless you provide a custom one. 
 * 
 *  Be sure to review the add_sair_wall() function to see how it handles
 *  the add_item and add_cmd_item for the Sair Wall.
 *
 */


#pragma strict_types

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

public mixed* existing_description(object room, string name)
{
    mixed items = room->query_item();
    if (!items)
    {
	return 0;
    }
    int index;
    for (index = 0; index < sizeof(items); index++)
    {
	if (IN_ARRAY(name, items[index][0]))
	{
	    return items[index];
	}
    }
    return 0;
}


void add_sair_wall()
{
    object room = this_object();
    room->add_item(({"octagon", "shape"}), sair_symbol);
    room->add_item(({"carving", "something"}), 
        "Your fingers would be of more help than your eyes.\n");
    room->add_cmd_item(({"wall", "carving", "something"}), 
	      ({"feel", "touch", "search"}), sair_search);
    /* If there is a previous add_item, append this message to it */
    mixed* wall_desc = existing_description(room, "wall");
    if (wall_desc)
    {
	room->remove_item("wall");
	room->add_item(wall_desc[0], wall_desc[1] +
	  "It looks like something has been carved into the wall "
	  +"here.\n");
    }    
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

    // No help from notify_fail if you don't know the object exists.
    if(!this_player()->query_prop("_avenir_found_sair_symbol"))
	return 0;

    notify_fail(capitalize(query_verb()) + " what where?\n");
    if (!strlen(str))
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
    if (!this_player()->query_relaxed_from_combat())
    {
	write("You try to " + query_verb() + " the fire opal against the "+
	  "octagon, but your hands are too shaky.\n");
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
    if (IS_INFIDEL(this_player()))
    {
        write("Hmm. Nothing happens.\n");
        return 1;
    }

    if (present("nasty_sickness", this_player())) 
    {
        write("Hmm. Nothing happens.\n");
        return 1;
    }

    /* It's working. Lets reduce the num of opals by 1. */
    ob->reduce_heap_size(1);
    this_player()->catch_msg("The gem you were using disappears!\n");	
    tell_room(this_object(), "A section of wall suddenly "
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
sair_init(void)
{
    /* If set_sair_dest() was called when this was cloned, 
     * then add these actions: 
     */
    if (query_sair_dest())
    {		
	add_action(place_it, "place");
	add_action(place_it, "fit");
	add_action(place_it, "lay");
	add_action(place_it, "match");
	add_action(place_it, "insert");
	add_action(place_it, "overlay");
    }

}
