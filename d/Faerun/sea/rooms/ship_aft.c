/* /d/Faerun/sea/rooms/ow1.c
 *
 * Nerull 2020
 *
 */
#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include "defs.h";

inherit STD_SEA_SURFACE;


object ship;

object ship_loc;
string ship_loc_str;
string ship_out_str;


void
set_ship_object(object ob)
{
    ship = ob;
}


mixed query_ship_object()
{
    return ship;
}


/*
 * Function name: create_sunken_outoor
 * Description  : Constructor, redefine this to configure your room
 */
void
create_sea_surface()
{
    seteuid(getuid());
    
    set_short("In the aft of a frigate");
    
    set_extraline("You are on the aft of a frigate.");
    
    
    reset_faerun_room();
}


void
set_ship_loc(object bl)
{
     if (objectp(bl) && bl->query_prop(ROOM_I_IS)) {
         ship_loc = bl;
         ship_loc_str = file_name(bl);
     }
}


object
query_ship_loc()
{
    return ship_loc; 
}


void
outer_room_check()
{
    if (!objectp(ship_loc))
        if (stringp(ship_loc_str))  {
            ship_loc_str->load_me();
            ship_loc = find_object(ship_loc_str);
        }
}


int
do_sail(string str)
{
     //int r;
     //object o;
     //outer_room_check();
     
     /*if (!objectp(ship_loc)) {
         notify_fail("Ack! No sea environment! This should not " +
                     "happen, please commune a wizard.\n");
                     
         return 0;
     }*/
     
     //r = ship_loc->try_row(str); 
     
     //r = environment(ship)->try_row(str); 
     
     //if (r)
       //   owned_object_action(this_player(), "row " + str);  
      
     //return r;
	 
	 
	if (str == "west")
    {
		if (ship->query_sailing_direction() == 1)
		{
			write("The ship is sailing in that direction already.\n");
			
			return 1;
		}
		
		ship->set_sailing_direction(1);
		
		write("You grab the wheel and set course westwards.\n");
		
		return 1;
	}
	
	if (str == "north")
    {
		if (ship->query_sailing_direction() == 2)
		{
			write("The ship is sailing in that direction already.\n");
			
			return 1;
		}
		
		ship->set_sailing_direction(2);
		
		write("You grab the wheel and set course northwards.\n");
		
		return 1;
	}
	
	if (str == "east")
    {
		if (ship->query_sailing_direction() == 3)
		{
			write("The ship is sailing in that direction already.\n");
			
			return 1;
		}
		
		ship->set_sailing_direction(3);
		
		write("You grab the wheel and set course eastwards.\n");
		
		return 1;
	}
	
	if (str == "south")
    {
		if (ship->query_sailing_direction() == 4)
		{
			write("The ship is sailing in that direction already.\n");
			
			return 1;
		}
		
		ship->set_sailing_direction(4);
		
		write("You grab the wheel and set course southwards.\n");
		
		return 1;
	}
}


/* Move the boat to a new location, this is called from the water room one
   rowed _from_ when one tries to row in a legitimate direction */
void
carry_out_sail(string direc, string to_path)
{
    object tp = this_player(); 
    
    if (!stringp(to_path))
        return;
    
    say(QCTNAME(tp) + " sails " + LANG_THESHORT(ship) + " " + 
                             direc + ".\n"); 
                             
    write("You sail " + LANG_THESHORT(ship) + " " + direc + ".\n"); 
    
    ship->set_direc(direc); 
    
    ship->move(to_path);  
    
    set_ship_loc(find_object(to_path));
    
    //remove_exit("out");
    //add_exit(to_path, "out");
    
    //tell_room(this_object(), view_long()); 
}


int leave_ship(string str)
{
    if (str == "frigate" || str == "ship")
    {
        if (ship->query_sunk() == 1)
        {
            write("You swim out of the sunken frigate.\n");

            tell_room(environment(ship), QCNAME(this_player())
            +" arrives swimming from the sunken frigate.\n", this_player());

            tell_room(environment(this_object()), QCTNAME(this_player())
            + " swims out of the sunken frigate.\n", this_player());

            this_player()->move_living("M", environment(ship), 1);
            
            return 1;
        }
                
        write("You leave "+short()+".\n");

        tell_room(environment(ship), QCNAME(this_player())
        +" arrives from the "+short()+".\n", this_player());

        tell_room(this_object(), QCTNAME(this_player())
        + " leaves the "+short()+".\n", this_player());

        this_player()->move_living("M", environment(ship), 1);

        return 1;
    }

    return 0;
}


void
do_add_effects(object playah)
{   
    seteuid(getuid());

    object drown_obj = 0;
    object slow_obj = 0;
    
    if (!present("_slowme_swim_obj", playah))
    {
        if (ship->query_sunk() == 1)
        {
            slow_obj = clone_object(DEFAULT_DIR + "obj/sea_slow_obj");
            slow_obj->move(playah, 1);
            slow_obj->setup_spell_effect();
        }    
    }

    if (!present("_sea_drown_obj", playah))
    {
        drown_obj = clone_object(DEFAULT_DIR + "obj/sea_drown_obj");
        drown_obj->move(playah, 1);
    }

    return;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
    {
        set_alarm(0.0, 0.0, &do_add_effects(ob));
    }
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}





/*public string
sea_view(string desc, string street_file)
{
    object street = find_object(street_file),
           *people;

    people = FILTER_LIVE(all_inventory(street));
    
    if (sizeof(people))
        desc += " You can see " + COMPOSITE_LIVE(people) + " on the street.";
    else
        desc += " There is no one on the street.";

    return BSN(desc);
}*/


public int
sea_view(string str)
{  
    if (str == "view")
    {   
        string descr;

        descr = ship->query_sea_view();
        
        object street = find_object(MASTER_OB(environment(ship))),
               *people;

        people = FILTER_LIVE(all_inventory(street));
        
        if (sizeof(people))
            descr += " You can see " + COMPOSITE_LIVE(people) + " swimming in the sea.";
        else
            descr += " There is no one in the sea.";
        
        this_player()->catch_tell(descr);

        return 1;
    }
    
    return 0;
}










/*int
sea_view(string str)
{
    if (str == "view")
    {
        string sea_view;
                
        sea_view = ship->query_sea_view();
        
        this_player()->catch_tell(sea_view);
        
        return 1;
    }
    
    return 0;
}*/


void
init()
{
    ::init();
    add_action(do_sail, "sail");
    add_action(leave_ship, "leave");
    add_action(leave_ship, "disembark");
    add_action(sea_view, "examine"); 
}
