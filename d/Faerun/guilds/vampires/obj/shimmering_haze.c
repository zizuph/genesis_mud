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
#include "../guild.h";

object instances_main;

int instance_open;


int
create_instance()
{
    setuid();
    seteuid(getuid());
    
	instance_open = 1;

    instances_main = clone_object(VAMPIRES_GUILD_DIR + "rooms/anomality_room");

    //instances_main->add_exit(file_name(environment(this_object())), "leave");

    return 1;
}


void
rem_me()
{
    VAMPIRES_OBJHANDLER->set_anomalitytarget_inactive();
    
    ANOMALITY_TARGET_LOG("anomalitytarget_log",
        "Anomalitytarget Despawned..\n");
    
    remove_object();
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
     
    set_long("This is an almost completley invisible shimmering or "
    +"haze, slightly tinted in a blood-red colour, floating in the "
    +"middle of the air. You think it's some sort of a gateway or "
    +"portal to somewhere else. You barely missed this one, but "
    +"your heightened unnatural senses discovered it just barely.\n");
    
    set_name("_anomality_");
    add_name("haze");
    set_adj("blood-red");
    add_adj("shimmering");
    
    set_short("blood-red shimmering haze");

    

    add_prop(OBJ_M_NO_GET, "The "+short()+" is too heavy to "
    +"move.\n");

    add_prop(OBJ_M_NO_STEAL, "The "+short()+" is too heavy to "
    +"steal.\n");

    add_prop(CONT_I_VOLUME,  45000);
    add_prop(CONT_I_WEIGHT,  500000);
    
    set_alarm(1.0, 0.0, &create_instance());
    
    set_alarm(49995.0, 0.0, &rem_me());
}


int
enter_anomality(string str)
{
    if (str == "shimmering haze" || str == "red shimmering haze"
    || str == "red haze" || str == "haze")
    {
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name()) > 0)
        {
            if (instance_open == 1)
            {
                
                write("You daringly the "
		        + short() + "!\n");

                tell_room(environment(this_object()),
                QCTNAME(this_player()) +" fades from view.\n", this_player());
                
                this_player()->move_living("M", instances_main, 1);
                
                instance_open = 0;
                               
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
    
    if (instance_open == 0)
    {
        return 0;
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



