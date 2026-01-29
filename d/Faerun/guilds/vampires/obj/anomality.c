/*  /d/Ravenloft/core/darkon/fos/obj/item_spawn.c
 *
 *  Random spawnitem for the forest. This item can be anything, from
 *  just regular rocks, debris, spawnpoints, dungeon instances etc.
 *
 *  Nerull 2015.
 */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "../defs.h";

object instances_main;

int instance_open;


int
create_instance()
{
	instance_open = 1;

    instances_main = clone_object(VAMPIRES_GUILD_DIR + "rooms/anomality");

    instances_main->add_exit(file_name(environment(this_object())), "leave");

    return 1;
}


/*
 * Function name: create_object()
 * Description  : Creates the object we wish to clone.
 */
void
create_object()
{
    setuid();
    seteuid(getuid());

    set_short("sinking broken mausoleum");
    set_name("_anomality_");
    set_adj("strange");

    set_long("This is an invisible but detectable vampire "
    +"anomality.\n");

    add_prop(OBJ_M_NO_GET, "The "+short()+" is too heavy to "
    +"move.\n");

    add_prop(OBJ_M_NO_STEAL, "The "+short()+" is too heavy to "
    +"steal.\n");

    add_prop(CONT_I_VOLUME,  45000);
    add_prop(CONT_I_WEIGHT,  500000);
    
    set_alarm(1.0, 0,0, &create_instance());
}


int
enter_anomality(string str)
{
    if (str == "shimmering haze")
    {
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name()) > 0)
        {
            if (instance_open == 1)
            {
                
                write("You try to struggle and wriggle free from the "
		        + short() + ", but fail.\n");

                tell_room(environment(this_object()),
                QCTNAME(this_player()) +" tries to wriggle free from the "
                +short()+", but remain stuck.\n", this_player());
                               
                return 1;
            }
            
            return 1;
        }        
    }
    
    return 0;
}


public int 
check_seen(object for_obj)
{
    // Wizards can always see us.
    if (for_obj->query_wiz_level())
    {
        return 1;
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(for_obj->query_name()) > 0)
    {
        return 1;
    }
               
    return 0;
}


/*
 * Function name: create_object()
 * Description  : Creates the object we wish to clone.
 */
void init()
{
    ::init();

    add_action(enter_anomality, "enter");
}



