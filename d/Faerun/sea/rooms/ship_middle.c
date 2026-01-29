/* /d/Faerun/sea/rooms/ow1.c
 *
 * Nerull 2020
 *
 */
#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "defs.h";

inherit STD_SEA_SURFACE;


object ship;


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
    
    set_short("In the middle of a frigate");
    
    set_extraline("You are on the middle of a frigate.");
    
    
    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
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


/*
* Function name: init()
* Description  : Enables the commands when a mortal enters.
*/
void init()
{
    ::init();
    add_action(leave_ship, "leave");
    add_action(leave_ship, "disembark");
}
