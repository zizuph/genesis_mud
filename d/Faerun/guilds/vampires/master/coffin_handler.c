/*
 * Guild object handler
 *
 */
inherit "/d/Faerun/guilds/vampires/rooms/std/vampires_std_room";
#pragma save_binary
#pragma no_clone
#pragma no_shadow
#pragma no_inherit
#pragma strict_types

#include <files.h>
#include <std.h>
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <std.h>
#include "../guild.h";





int stop_clone_coffins = 0;

object coffin_token1;



int query_cloned_coffins()
{
    return stop_clone_coffins;
}


void reset_cloned_coffins()
{
    write("You reset the cloned coffin flag.\n");
    stop_clone_coffins = 0;
    return;
}


public void clone_coffins()
{
    string * coffins=COFFIN_MANAGER->query_all_coffins();
    
    set_alarm(5.0, 0.0, &clone_coffins());
      
    foreach (string owner : coffins)
    {
        string coffin_location;        
        object coffin_locatione;        
        coffin_location = COFFIN_MANAGER->query_location(owner);
        
        coffin_locatione = find_object(coffin_location);
        
        // Location must be loaded before we populate it with coffin.
        if (coffin_locatione == 0)
        {
            LOAD_ERR(coffin_location);
            COFFINSPAWN_LOG("coffinspawn_log", "Loading " +coffin_location + ".\n");
            
            coffin_locatione = find_object(coffin_location);
        }
        
        if (coffin_locatione == 0)
        {
            COFFINSPAWN_LOG("coffinspawn_log",
            "Coffin location was "+coffin_location+" even after loading. Skipping...\n");
            
            continue;
        }

        object presentcoffin;
        
        presentcoffin = present(owner + "_coffin", coffin_locatione);

        if (VAMPIRES_MASTER->is_lay_vampires(owner) == 0)
        {
            COFFIN_MANAGER->remove_coffin(owner);
            presentcoffin->remove_object();
            
            COFFINSPAWN_LOG("coffinspawn_log",
            "Coffin for "+owner+" destroyed at "+coffin_location+".\n");   
            continue;            
        }

        if (presentcoffin->query_owner() != owner)
        {   

            if (coffin_location->query_prop(CONT_I_RIGID))
            {
            }
            else
            {            
                COFFINSPAWN_LOG("coffinspawn_log",
                "Coffin for "+owner+" spawning at "+coffin_location+".\n");
                   
                object coffin=clone_object(ROOM_DIR+"coffin");
                coffin->add_name(owner + "_coffin");
                coffin->load_coffin(owner);
                coffin->move(coffin_location, 1);    

                object player=find_player(owner);

                if (player != 0)
                {
                    player->catch_tell("Your coffin has materialized somewhere in "
                    +"the world. You may use sanctuary to enter it from a distance.\n");
                }
            }            
        }
        
        //COFFINSPAWN_LOG("coffinspawnloop_log",
          //  "Coffin for "+owner+" ok. Loop continues.\n");
    }  
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_vampires_room()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Vampire object coffin handler room");
    
    set_long("Vampire coffin room.\nFUNCTIONS:\n---------\n"
    +" - none.\n");
    
    stop_clone_coffins = 0;
    
    clone_coffins();
  
    reset_faerun_room();
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
    {
        if (ob->query_wiz_level())
        {
            WIZARD_ENTRY_VAMP_LOG("wizard_entry_vamp_log",
            "The immortal " +ob->query_name() 
            +" entered the Vampires Object Handler room!\n");
           
            ob->catch_tell(" >>> YOUR ENTRY HAS BEEN LOGGED. "
            +"UNLESS YOU HAVE BUSINESS "
            +"HERE, PLEASE IMMEDATELY MOVE ELSEWHERE! <<<\n");
        } 
    }
}


/*
 * Function name: init 
 * Description  : Add functions to the room
 */
void
init()
{
    ::init();
}
