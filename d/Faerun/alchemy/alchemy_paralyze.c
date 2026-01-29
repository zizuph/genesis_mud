/* /d/Faerun/alchemy/alchemy_paralyze.c
 * 
 * Nerull 2021
 */

#include "/d/Faerun/defs.h"
#include "defs.h";
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>

inherit "/std/paralyze.c";

void remove_cutscene_paralyze();

float cutscene_timer = 0.0;
float timer;

string product;


int
set_product(string str)
{
    product = str;
    
    return 1;
}


float
set_timer(float i)
{
    timer = i;
}


void
remove_me()
{
	remove_object();
}


/*
 * Function name: remove_cutscene_paralyze
 * Description: Automatically removes the paralyzeobject.
 */
void
remove_cutscene_paralyze()
{
	setuid();
    seteuid(getuid());
    
    environment(this_object())->catch_tell("When you think its done, "
    +"you turn off the heater and pick up a "+product+".\n");
    
    tell_room(environment(environment(this_object())), 
    environment(this_object())->query_name()+" turns off the heater of "
    +"a large alchemy set and picks up a "+product+".\n", 
    environment(this_object()));       
	
	remove_object();
}
 
 
 /*
 * Function name: remove_illusion_paralyze
 * Description: Automatically removes the paralyzeobject.
 */
void
cutscene_effect()
{
    setuid();
    seteuid(getuid());

    if (cutscene_timer == 0.0)
    {
        environment(this_object())->catch_tell("You turn on the heater and "
        +"place the ingredients into a container with volatile "
        +"chemicals.\n");
        
        tell_room(environment(environment(this_object())), 
        environment(this_object())->query_name()+" turns on the heater of "
        +"a large alchemy set, and places some ingredients into a container "
        +"with volatile chemicals.\n", 
        environment(this_object()));       
    }
    
    if (cutscene_timer >= 1.0)
    {
        environment(this_object())->catch_tell("The large alchemy set gives "
        +"off boiling sounds while the heater is burning.\n");
        
        tell_room(environment(environment(this_object())), "The large alchemy "
        +"set gives off boiling sounds while the heater is "
        +"burning.\n", environment(this_object()));
    }
    
    if (cutscene_timer == timer)
    {
        remove_cutscene_paralyze();
        
        return;
    }
     
    cutscene_timer = cutscene_timer + 1.0;
    
    return;
}


int start_set()
{
    set_alarm(1.0, 3.0, &cutscene_effect());
}
 
 
/*
 * Function name: create_paralyze
 * Description:   Set up paralyze
 */
void
create_paralyze()
{
    set_fail_message("You are busy doing delicate work "
    +"of alchemy using the large alchemy set, and can't move!\n");
    
    set_name(({"alchemy_paralyze"}));
}


/*
 * Function name: stop
 * Description:   Here all commands the player gives comes.
 * Argument:      str - The extra string the player sent.
 */
varargs int
stop(string str)
{
    /* Only paralyze our environment */
    if (environment(this_object()) != this_player())    
    return 0;

    if (wildmatch("'*", query_verb()))
    return 0;

    switch (query_verb())
    {
        // Eyes:
        case "l":
        case "look":
        case "exa":
        case "who":
        case "list":
        case "vitals":
        case "examine":
        // meta-commands
        case "bug":
        return 0;
        break;
        default:
            if (fail_message)
                this_player()->catch_msg(fail_message);
            
            if (!this_player()->query_wiz_level())
                return 1;
            break;
    }
    
    write("Since you are a wizard this paralyze won't affect you.\n");
    return 0;
}


void init()
{
    ::init();
}