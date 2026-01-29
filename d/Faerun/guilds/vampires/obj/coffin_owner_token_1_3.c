/*  /d/Faerun/guilds/vampires/obj/coffin_owner_token_1_3.c
 *
 *  Placable coffin for vampires.
 *
 *  Nerull, 2021
 *
 */
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "../guild.h";
#include "../blacklist.h";


int
no_drop()
{
}


int
do_destroy(string str)
{
    if (str == "coffin")
    {
        write("You destroy your coffin!\n");

        remove_object();
        
        return 1;
    }
    
    return 0;
}


int
place_coffin(string str)
{
    setuid();
    seteuid(getuid());
    
    if (str == "coffin")
    {
        // We try to avoid parking coffins in instances.
        if (MASTER_OB(environment(this_player())) != file_name(environment(this_player())))
        {
            write("You sense that this location is not fit for a vampire "
            +"coffin. Look elsewhere for a more suited location.\n");
            
            return 1;
        }
        
        if (member_array(MASTER_OB(environment(this_player())), blacklisted_locations) >= 0)
        {
            write("You sense that this location is not fit for a vampire "
            +"coffin. Look elsewhere for a more suited location.\n");
            
            return 1;
        }
        
        if (environment(this_player())->query_prop(NO_COFFIN_PLACEMENT))
        {
            write("You sense that this location is not fit for a vampire "
            +"coffin. Look elsewhere for a more suited location.\n");
            
            return 1;
        }
        
        if (environment(this_player())->query_prop(ROOM_I_TYPE) == 2)
        {
            if (member_array("down", environment(this_player())->query_exit_cmds() != -1))
            {
                write("The coffin requires solid ground or bedrock. You "
                +"can't place it here.\n");
            
                return 1;
            }
        }
        
        write("You place your elaborate wood coffin on the ground!\n");
        
        object coffin=clone_object(VAMPIRES_GUILD_DIR +"rooms/coffin");
			
        coffin->set_owner(COFFIN_MANAGER->get_name(this_player())); 
        coffin->set_material("wood");
        coffin->set_material_cost(82);
        coffin->set_owner_avg(this_player()->query_average());  
        
        coffin->move(environment(this_player()), 1);
        
        string owner = coffin->query_owner();
        
        COFFIN_MANAGER->set_location(owner,MASTER_OB(environment(coffin)));
        
        coffin->save_coffin();
        
        coffin->update_position();
        
        coffin->add_name(owner + "_coffin");
        
        COFFINPLACEMENT_LOG("coffinplacement_log",
        "The player " +this_player()->query_name() 
        +" placed a coffin at"+MASTER_OB(environment(coffin))+".\n");
        
        if (!present("_vampire_powers_unlock_ob", this_player()))
        {
            clone_object(VAMPIRE_POWERS_UNLOCK_OB)->move(this_player(), 1);
            
            this_player()->catch_tell("As you place your coffin on the ground, "
            +"you feel your power surging.\n");
        }
        
        if (VAMPIRES_MASTER->is_aging_check(this_player()->query_real_name()))
        {
            // Remove vampires to list of noaging vampires.
            VAMPIRES_MASTER->remove_aging_check(this_player()->query_real_name());
        }
        
        remove_object();
        
        return 1;
    }
    
    return 0;
}


void
create_object()
{
    set_name("_coffin_owner_token_1_3");
    add_name("coffin");
    set_adj("elaborate");
    add_adj("wood");
    
    set_short("elaborate wood coffin");
    
    set_long("This is an elaborate wood coffin.\nYou may "
    +"<destroy coffin> if you wish to rid yourself of this "
    +"object, or <place coffin> in a room you deem fit.\n");
    
    add_prop(OBJ_I_VALUE, 123);
    // Questitem no-drop properties.
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_SELL, 1);
}


init()
{
    ::init();
    add_action(do_destroy,"destroy");
    add_action(place_coffin,"place");
}


string
query_recover()
{
    return 0;
}
