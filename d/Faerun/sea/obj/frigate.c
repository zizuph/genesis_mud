/*
 * /d/Ravenloft/core/darkon/martira_bay/bountiful/obj/bountiful_sea.c
 *
 * The Bountiful. Ship object.
 *
 * Nerull 2015
*/

inherit "/std/object";
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <filter_funs.h>

#define TP this_player()


int sunk = 0;
int speed = 0;
int anchored = 0;
int direction = 0;

string sea_view;

string ship_direction = 1;

string sail_path;

object instances_ship_1;
object instances_ship_2;
object instances_ship_3;

int moves;


int 
set_sailing_direction(int i)
{
    direction = i;
}


int query_sailing_direction()
{
    return direction;
}


string query_sea_view()
{
    sea_view = environment(this_object())->long();
    
    return sea_view;
}


int set_sunk()
{
    sunk = 1;
    
    instances_ship_1->add_prop(ROOM_I_LIGHT, 0);
    instances_ship_1->add_prop(FAERUN_UNDERWATER, 1);
    instances_ship_1->set_short("In the aft of a sunken frigate");
    instances_ship_1->set_long("In the aft of a sunken frigate. The cold "
    +"embrace of seawater is everywhere.\n");
        
    instances_ship_2->add_prop(ROOM_I_LIGHT, 0);
    instances_ship_2->add_prop(FAERUN_UNDERWATER, 1);
    instances_ship_2->set_short("In the middle of a sunken frigate");
    instances_ship_2->set_long("You are on the middle of a frigate. The cold "
    +"embrace of seawater is everywhere.\n");
        
    instances_ship_3->add_prop(ROOM_I_LIGHT, 0);
    instances_ship_3->add_prop(FAERUN_UNDERWATER, 1);
    instances_ship_3->set_short("In the fore of a sunken frigate");
    instances_ship_3->set_long("You are on the fore of a sunken frigate. The cold "
    +"embrace of seawater is everywhere.\n");
}


int query_sunk()
{
    return sunk;
}


int 
ship_game_loop()
{
    int test = 1;
    
    if (sunk == 1)
    {
        this_object()->remove_prop(OBJ_I_FLOAT);
        environment(this_object())->sink(this_object());
    }
    
    if (direction == 1)
    {
        ship_direction = "ship west";
        
        this_object()->sail(ship_direction);
        
        return 1;
    }
    
    if (direction == 2)
    {
        ship_direction = "ship north";
        
        this_object()->sail(ship_direction);
        
        return 1;
    }
    
    if (direction == 3)
    {
        ship_direction = "ship east";
        
        this_object()->sail(ship_direction);
        
        return 1;
    }
    
    
    if (direction == 4)
    {
        ship_direction = "ship south";
        
        this_object()->sail(ship_direction);
        
        return 1;
    }
    
    return 1;
}


/*
 * Function name: add_instance_room
 * Description  : Builds the next room in the instance and adding proper
 *                exits.
 */
void
add_instance_room()
{
    seteuid(getuid());
    
    instances_ship_1 = clone_object(SEA_ROOM_DIR
        +"ship_aft.c");
        
    instances_ship_2 = clone_object(SEA_ROOM_DIR
        +"ship_middle.c");
        
    instances_ship_3 = clone_object(SEA_ROOM_DIR
        +"ship_fore.c");
 
 
    instances_ship_1->add_exit(instances_ship_2, "middle");
    
    instances_ship_2->add_exit(instances_ship_1, "aft");
    instances_ship_2->add_exit(instances_ship_3, "fore");
    
    instances_ship_3->add_exit(instances_ship_2, "middle");
    
    instances_ship_1->set_ship_object(this_object());
    instances_ship_2->set_ship_object(this_object());
    instances_ship_3->set_ship_object(this_object());

    return;
}


/*
 * Function name: create_object()
 * Description  : Constructor. Creates the object.
 */
void
create_object()
{
    seteuid(getuid());
    
    set_name("frigate");
    add_name("bountiful");
    add_name("_bountiful_true");
    add_name("ship");
    set_adj("three");
    add_adj("masted");
    set_long("This Frigate is quite large. Having three masts "
    +"adorned with black sails makes you wonder if this is a pirate "
    +"ship. But it isn't the odd colour of the masts that draws "
    +"your eye, it is the massive opulent sterncastle. This sterncastle "
    +"overhangs the sides of the frigate by at least eight feet on each "
    +"side and all the wood work is enchanced by white ivory inlays and "
    +"solid gold trim. There are also bars upon all the sterncastle "
    +"windows making you wonder if it is for visiting or never "
    +"leaving.\n");

    add_prop(CONT_I_RIGID,  1);
    add_prop(OBJ_M_NO_GET, "Ehm...no.\n");
    add_prop(OBJ_M_NO_STEAL, "Ehm...no.\n");
    
    add_prop(OBJ_I_FLOAT, 1);
    
    add_instance_room();
    
    set_alarm(20.0, 20.0, &ship_game_loop());
}

int 
sail(string str)
{
    string *ss, to, cond;
    mixed *arr;
    int i, result;
    object from;
	
	//if (this_player()->query_interactive())
	//{
		//return 0;
	//}
    
    notify_fail("Sail what?\n");
    if (!str)
	return 0;

    ss = explode(str, " ");
    
    if (ss[0] != "ship")
	return 0;
    
    notify_fail("Sail ship where?\n");
    if (sizeof(ss) == 1)
	return 0;

    if (!(from = environment(this_object())))
        
	return 0;
    
    switch(ss[1])
      {
        case "w": ss[1] = "west";
                  break;
        case "n": ss[1] = "north";
                  break;
        case "e": ss[1] = "east";
                  break;
        case "s": ss[1] = "south";
                  break;
        case "se": ss[1] = "southeast";
                   break;
        case "sw": ss[1] = "southwest";
                   break;
        case "ne": ss[1] = "northeast";
                   break;
        case "nw": ss[1] = "northwest";
                   break;
        /*case "u": ss[1] = "up";
                  break;
        case "d": ss[1] = "down";*/

        break;
      }
      
    arr = from->query_exit();
    
    for (i = 1; i < sizeof(arr); i += 3)
    {
        if (arr[i] == ss[1])
        {	    
            to = arr[i - 1];
            if (intp(arr[i + 1]))
            {
                result = arr[i + 1];
            } 
            
            /*if (!intp(arr[i + 1]))
            {
                    cond = extract(arr[i + 1], 2);
                result = call_other(from, cond);
            }*/

            if (result)
            {
                notify_fail("You can't sail the ship in that direction!\n");
                return 0;
            }
            
            if (!move(to))
            {
                //tell_room(from, QCTNAME(TP) + " sails the ship " + ss[1] + 
                  //      ".\n", TP);
                        
                tell_room(to, "A ship arrives.\n");
				
				tell_room(instances_ship_1, "The ship crashes "
				+"through the waves, sailing to the " + ss[1] + ".\n");
				
				tell_room(instances_ship_2, "The ship crashes "
				+"through the waves, sailing to the " + ss[1] + ".\n");
				
				tell_room(instances_ship_3, "The ship crashes "
				+"through the waves, sailing to the " + ss[1] + ".\n");
				
				tell_room(environment(this_object()), "The "
				+short()+" sails " + ss[1] + ".\n");
                
               // write("The "+short()+" sails " + ss[1] + ".\n");
                
                //moves++;
                
                //if (moves > 15)
                  //  set_alarm(8.0, 0.0, owner_arrives);
                return 1;
            }
        }
    
    }
    
    notify_fail("No direction " + ss[1] + " found.\n");
    return 0;
}


/*
 * Function name: enter_ship()
 * Description  : Determines if possible to enter the ship.
 */
int
enter_ship(string str)
{
    if (str == "ship" || str == "frigate")
    {
        if (sunk == 1)
        {
            write("You swim and enter the sunken "+short()+".\n");

            tell_room(instances_ship_2, QCNAME(this_player())
            +" arrives swimming in from the sea.\n", this_player());

            tell_room(environment(this_object()), QCTNAME(this_player())
            + " swim into the sunken "+short()+".\n", this_player());

            this_player()->move_living("M", instances_ship_2, 1);
            
            return 1;
        }      
        
        write("You climb aboard the frigate from the sea.\n");

        tell_room(instances_ship_2, QCNAME(this_player())
        +" arrives climbing up from the sea.\n", this_player());

        tell_room(environment(this_object()), QCTNAME(this_player())
        + " climbs aboard the "+short()+".\n", this_player());

        this_player()->move_living("M", instances_ship_2, 1);

        return 1;
    }

    return 0;
}


/////////////////////////////////////////////////////////////////////////////


/*void
set_sail_path(string str)
{
    if (str == "west")
    {
        sail_path = environment(this_object()->query_exit
    }
    sail_path = sp;
}*/


string
query_sail_path()
{
    return sail_path;
}


/*int sail_ship()
{
    if (!LOAD_ERR(sp))
    {
        this_object()->move(sp);
        //ob->move("down");
        tell_room(sp, capitalize(LANG_THESHORT(ob)) + " " + sv + " in.\n");
    }
}*/


/*
* Function name: init()
* Description  : Enables the commands when a mortal enters.
*/
void init()
{
    ::init();
    add_action(enter_ship, "enter");
    add_action(enter_ship, "climb");
    
    //add_action(sail, "sail");
}
