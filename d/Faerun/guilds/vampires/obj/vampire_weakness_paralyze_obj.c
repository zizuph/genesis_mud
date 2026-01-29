/* /d/Faerun/guilds/vampires/obj/vampire_weakness_paralyze_obj.c
 * 
 * Nerull 2020
 */
 
 inherit "/std/paralyze.c";

#include "/d/Faerun/defs.h"
#include "../guild.h";
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>



int cooldown = 0;


 /*
 * Function name: remove_illusion_paralyze
 * Description: Automatically removes the paralyzeobject.
 */
void
weakness_effect()
{
    setuid();
    seteuid(getuid());
   
    if (cooldown > 0)
    {
        environment(this_object())->catch_tell("You are too weak to move!\n");
    
        tell_room(environment(environment(this_object())), 
        environment(this_object())->query_name()+" is too weak to move.\n", 
        environment(this_object()));       
    }
      
    cooldown = cooldown - 1;
    
    if (cooldown < 0)
    {
        cooldown = 0;
    }
    
    return;
}
 
 
/*
 * Function name: create_paralyze
 * Description:   Set up paralyze
 */
void
create_paralyze()
{
    set_fail_message("You are too weak to move anywhere!\n");
    
    set_name(({"vampire_weakness_paralyze"}));
    
    set_alarm(5.0, 5.0, &weakness_effect());
}


/*
 * Function name: stop
 * Description:   Here all commands the player gives comes.
 * Argument:      str - The extra string the player sent.
 */
varargs int
stop(string str)
{
    int thirst = this_player()->query_vampires_thirst_occ();
    
    /* Only paralyze our environment */
    if (environment(this_object()) != this_player())    
    return 0;

    if (wildmatch("'*", query_verb()))
    return 0;

    /*switch (query_verb())
    {
        // Eyes:
        case "west":
        case "south":
        case "east":
        case "north":
        case "northwest":
        case "southwest":
        case "southeast":
        case "northeast":
        case "up":
        case "down":             
        if (thirst < 30)
        {
            if (cooldown > 0)
            {
                this_player()->catch_msg(fail_message);
                    
                return 1;
            }
            
            if (cooldown <= 0)
            {
                this_player()->catch_msg("You feel you are temporary strong enough to move!\n");
               
                cooldown = 3;
            }
        }
        
        return 0;        
        break;
        default:
        
        if (thirst < 30)
        {
            if (cooldown > 0)
            {
                this_player()->catch_msg(fail_message);
                    
                return 1;
            }
            
            if (cooldown <= 0)
            {
                this_player()->catch_msg("You feel you are temporary strong enough to move!\n");
               
                cooldown = 3;
            }
        }
        
        return 0;
    }*/
    
    if (thirst < 30)
    {
        if (cooldown > 0)
        {
            this_player()->catch_msg(fail_message);
                
            return 1;
        }
        
        if (cooldown <= 0)
        {
            this_player()->catch_msg("You feel you are temporary strong enough to move!\n");
           
            cooldown = 3;
        }
    }

    return 1;
}


void init()
{
    ::init();
}