/* /d/Faerun/sea/rooms/uw_test.c
 *
 * Nerull 2020
 *
 */
#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "defs.h";

inherit STD_SEA_UNDERWATER;


string sink_path;

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


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_sea_underwater(void)
{
    //underwater_room();
    
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(FAERUN_UNDERWATER, 1);

    set_short("Somewhere under the surface of the ocean");
    
    set_long("You are below the surface of the ocean.\n");

    add_swim_exit(SEA_ROOM_DIR + "uw_test.c", "up");
    
    reset_room();
}


void
do_add_effects(object playah)
{   

    seteuid(getuid());

    object slow_obj = 0;
    object drown_obj = 0;

    if (!present("_slowme_swim_obj", playah))
    {
        slow_obj = clone_object(DEFAULT_DIR + "obj/sea_slow_obj");
        slow_obj->move(playah, 1);
        slow_obj->setup_spell_effect();
    }
    
    if (!present("_sea_drown_obj", playah))
    {
        drown_obj = clone_object(DEFAULT_DIR + "obj/sea_drown_obj");
        drown_obj->move(playah, 1);
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
        tell_room(sp, capitalize(LANG_THESHORT(ob)) + " " + sv + " in.\n");
    }
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
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
reset_room()
{
    ::reset_room();
}
