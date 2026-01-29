/* /d/Faerun/sunken_ruins/rooms/ow1.c
 *
 * Nerull 2019
 *
 */
#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "defs.h";

inherit STD_SUNKEN_OUTDOOR;


/*public string
hook_no_swim(string str)
{
    if ((str == "east") || (str == "south"))
    {
        return "You decide that isn't a good idea, since the currents "+
            "seem dangerous in that direction.\n";
    }
    else if (str == "north")
    {
        return "The cliff blocks your way.\n";
    }

    return "";
}*/


/*public int
swim_exit(void)
{
    if (swim_dir != "down")
	return 0;

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
}*/


/*public int
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
}*/


/*
 * Function name: create_sunken_outoor
 * Description  : Constructor, redefine this to configure your room
 */
void
create_sunken_outdoor()
{
    set_short("Somewhere in the middle of the ocean");
    
    set_extraline("You are somewhere in the middle of the "
	+"ocean, and you see nothing but rolling waves in every "
	+"direction.");

    /*add_item(({"sloping platform","ledge"}),
        "The platform is less slippery than it should "
        +"be with all the falling snow. "
        +"It is as if it would be periodically maintained "
        +"with tiny rocks spread out "
        +"across it to ensure firm footing upon it.\n");*/
    
    //add_exit(SUNKEN_ROOM_DIR + "uw1.c", "down", into_water);
   
    reset_faerun_room();
}


/*
 * Function to cleanup props if a player leaves before standing
 */
/*void leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    
    object token;
    
    if(!objectp(to) || !objectp(ob))
      return;
  
    if (objectp(token = present("_slowme_swim_obj", ob)))
    {   
        ob->remove_slow_shadow();
        token->remove_object();
    }
    
    return;
}*/


/*void
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


string
query_sink_path()
{
    return "down";
}


/* An object sinks */
/*void
sink(object ob)
{
    string sp = "down", sv;
    
    if (!objectp(ob)) 
        return;
	
    if (!objectp(present(ob, this_object())))
        return;
	
    if (!stringp(sp = "down"))
        return;
	
    sv = ((ob->num_heap() > 1) ? "sink" : "sinks"); 
	
    tell_room(this_object(), capitalize(LANG_THESHORT(ob)) + 
                             " " + sv + " downwards.\n");
    setuid();
    seteuid(getuid());
	
    if (!LOAD_ERR(sp))
    {
        ob->move(sp);
        tell_room(sp, capitalize(LANG_THESHORT(ob)) + " " + sv + " in.\n");
    }
}


/*
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 *                We need to add the drown object to livings who enter.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
/*public void
enter_inv(object ob, object from)
{
     object d; 
	 
     ::enter_inv(ob, from);
	 
     if ((!living(ob)) && (stringp(query_sink_path())))
		 //&& 
         /*!ob->query_prop(OBJ_I_FLOAT))*/ //{
    /*     set_alarm(1.0, 0.0, &sink(ob));
         return;
     }
	 
     /* Burn out torches dropped into water */ 
    /* if (ob->query_lit(0) == -1) {    
         ob->burned_out();  
         return;
     }
	 
     /*if (!interactive(ob) || ob->query_prop(LIVE_I_GILLS))
         return;*/
	 
     /*if (query_standard_water_room()) { 
         if (!objectp(d = ob->query_prop(LIVE_O_DROWN_OB))) { 
             d = clone_object(DROWN_OBJECT);
             d->move(ob, 1); 
         }
         d->reset_trap_move(); 
         /* Burn out torches held by player when in deep water */ 
        /* if (deep_water_room(this_object()) && 
             !deep_water_room(from)) 
             d->extinguish_lights(); */
   // }
//}



 /*void
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
	
	if ((!living(ob)) && (stringp(query_sink_path())))
		 //&& 
         /*!ob->query_prop(OBJ_I_FLOAT))*/ //{
         /*set_alarm(1.0, 0.0, &sink(ob));
         return;
     }
	 
     /* Burn out torches dropped into water */ 
     /*if (ob->query_lit(0) == -1) {    
         ob->burned_out();  
         return;
     }
}*/


void
reset_faerun_room()
{
    ::reset_faerun_room();
}