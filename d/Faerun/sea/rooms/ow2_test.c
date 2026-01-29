/* /d/Faerun/sea/rooms/ow1.c
 *
 * Nerull 2020
 *
 */
#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "defs.h";

inherit STD_SEA_SURFACE;

string sink_path;

object instances_room = 0;
object instances_endroom = 0;
int direction = 0;
int rooms_left = 3;
int at_end = 0;
int instancetype = 0;


/*
 * Function name: set_direction
 * Description  : Sets the next direction of the dungeon.
 */
void
set_direction(int i)
{
    direction = i;
}


/*
 * Function name: query_direction
 * Description  : Returns the direction.
 */
int
query_direction()
{
    return direction;
}


/*
 * Function name: set_rooms_left
 * Description  : Sets the number of rooms left before the dungeon
 *                ends.
 */
void
set_rooms_left(int z)
{
    rooms_left = z;
}


/*
 * Function name: query_rooms_left
 * Description  : Tells us how many rooms there are left before the
 *                dungeon ends.
 */
int
query_rooms_left()
{
    return rooms_left;
}


/*
 * Function name: set_instancetype
 * Description  : Sets variant of the instance.
 */
void
set_instancetype(int i)
{
    instancetype = i;
}


void
set_sink_path(string sp)
{
    sink_path = sp;
}


string
query_sink_path()
{
    return sink_path;
}


/*
 * Function name: add_swim_exit
 * Description:   Add one swim exit to the room. 
 */
varargs void
add_swim_exit(string place, string cmd, mixed efunc, mixed tired, 
              mixed non_obvious)
{
    if ((cmd == "down") && (!stringp(query_sink_path())))
        set_sink_path(place); 
    
    add_exit(place, cmd, efunc, tired, non_obvious);  
}


public int
into_water()
{
    int swim_skill = TP->query_skill(SS_SWIM);
    
    if (swim_skill < 30)
    {
        if (swim_skill > 0)
            write("Maybe you should learn to swim alittle better first?\n");
        else
            write("You cannot swim! Much less dive.\n");

        return 1;
    }

    write("You dive into the cold dark water.\n");
    return 0;
}


int
block_exit()
{
    if (this_player()->query_prop(OBJ_I_FAERUN_SHIP) 
        || this_object()->query_prop(OBJ_I_FAERUN_SHIP))
    {
        /*write("The guard dogs raise their heads to look at you "
        +"suspiciously, but they "
        +"let you pass.\n");
        
        tell_room(environment(this_player()), QCTNAME(this_player())
        +" receives a suspicious glance from the guard dogs, but "
        +"is let through.\n", this_player());*/
            
        return 0;    
    }
    
    write("You can't swim far in that direction due to the great "
    +"distance.\n");
        
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
    int i = direction;
        
    if (rooms_left == 0 && at_end == 0)
    {
        instances_endroom = clone_object(SEA_ROOM_DIR
        +"uw_bottom.c");
               
        this_object()->add_swim_exit(file_name(instances_endroom),
        "down");
        
        instances_endroom->add_swim_exit(file_name(this_object()), "up");
        
        at_end = 1;

        return;
    }
    
    if (at_end == 1)
    {
        return;
    }
    
    if (instances_room == 0)
    {
        instances_room = clone_object(SEA_ROOM_DIR
        +"uw_test.c");

        this_object()->add_swim_exit(file_name(instances_room),
            "down");
            
        instances_room->add_swim_exit(file_name(this_object()), "up");
            
        rooms_left = rooms_left - 1;
            
        instances_room->set_rooms_left(rooms_left);
    }
}


/*
 * Function name: create_sunken_outoor
 * Description  : Constructor, redefine this to configure your room
 */
void
create_sea_surface()
{
    set_short("Somewhere in the middle of the ocean");
    
    set_extraline("You are somewhere in the middle of the "
	+"ocean, and you see nothing but rolling waves in every "
	+"direction.");
    
    
    add_prop(FAERUN_SHIP_CAN_SAIL, 1);

    /*add_item(({"sloping platform","ledge"}),
        "The platform is less slippery than it should "
        +"be with all the falling snow. "
        +"It is as if it would be periodically maintained "
        +"with tiny rocks spread out "
        +"across it to ensure firm footing upon it.\n");*/
    
    //add_exit(SEA_ROOM_DIR + "uw_test.c", "down", into_water);
    //add_swim_exit(SEA_ROOM_DIR + "uw_test.c", "down", into_water);
    
    set_alarm(0.0, 0.0, &add_instance_room());
    
    // These are primmary for ships only
    //add_exit(SEA_ROOM_DIR + "ow_test.c", "east", block_exit, 0, 1);
    add_exit(SEA_ROOM_DIR + "ow_test.c", "east", 0, 1);
    
    //set_sink_path("down");
   
    reset_faerun_room();
}


void
do_remove_slow(object playah)
{   
    seteuid(getuid());
	
	object token;

    if (objectp(token = present("_slowme_swim_obj", playah)))
    {   
        playah->remove_slow_shadow();
        token->remove_object();
    }

    return;
}


/* An object sinks */
void
sink(object ob)
{
    string sp, sv;
    
    if (!objectp(ob)) 
        return;
	
    if (!objectp(present(ob, this_object())))
        return;
    
    if (ob->query_prop(OBJ_I_FLOAT))
        return;
	
    if (!stringp(sp = query_sink_path()))
        return;
	
    sv = ((ob->num_heap() > 1) ? "sink" : "sinks"); 
	
    tell_room(this_object(), capitalize(LANG_THESHORT(ob)) + 
                             " " + sv + " downwards.\n");
    setuid();
    seteuid(getuid());
	
    if (!LOAD_ERR(sp))
    {
        ob->move(sp);
        //ob->move("down");
        tell_room(sp, capitalize(LANG_THESHORT(ob)) + " " + sv + " in.\n");
    }
}


void
do_add_effects(object playah)
{   
    seteuid(getuid());

    object drown_obj = 0;

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
        if (ob->query_wiz_level())
        {
            
        } 
		
		if (present("_slowme_swim_obj", ob))
		{
			set_alarm(0.0, 0.0, &do_remove_slow(ob));
		}    
    }
    
    if (interactive(ob))
    {
        set_alarm(0.0, 0.0, &do_add_effects(ob));
    }
	
	if ((!living(ob)) && (stringp(query_sink_path()))
		 && !ob->query_prop(OBJ_I_FLOAT)) {
         set_alarm(1.0, 0.0, &sink(ob));
         return;
    }
	 
    /* Burn out torches dropped into water */ 
    if (ob->query_lit(0) == -1) {    
        ob->burned_out();  
        return;
    }
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}