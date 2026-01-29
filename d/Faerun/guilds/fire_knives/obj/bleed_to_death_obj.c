/* /d/Faerun/guilds/fire_knives/obj/bleed_to_death_obj.c
 * 
 * Nerull 2018
 */

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

inherit "/std/paralyze.c";

void remove_bleed_paralyze();

int bleed_timer = 0;

/*
 * Function name: remove_bleed_paralyze
 * Description: Automatically removes the paralyzeobject.
 */
void
remove_bleed_paralyze()
{
    environment(this_object())->catch_tell("You finally bleed out, and "
    +"the world fades to black ...\n");
     
    tell_room(environment(environment(this_object())), environment(this_object())->query_name()
    +" finally bleeds out and closes "+environment(this_object())->query_possessive()
    +" eyelids.\n", environment(this_object()));
    
    environment(this_object())->set_hp(0);
    environment(this_object())->do_die(this_object());
	
	BLED_LOG("bled_to_death_log",
    "The individual "+environment(this_object())->query_name()
    +" bled to death!\n");
          
    remove_object();
}
 
 
 /*
 * Function name: remove_illusion_paralyze
 * Description: Automatically removes the paralyzeobject.
 */
void
bleed_effect()
{
    environment(this_object())->catch_tell("Blood rapidly pulses out "
    +"of your open femoral artery!\n");
    
    tell_room(environment(environment(this_object())), "Blood rapidly "
    +"pulses out "
    +"of "+environment(this_object())->query_name()+"'s femoral artery!\n", 
    environment(this_object()));
     
    if (bleed_timer == 3)
    {
        remove_bleed_paralyze();
        
        return;
    }
     
    bleed_timer = bleed_timer + 1;
    
    return;
}
 
 
/*
 * Function name: create_paralyze
 * Description:   Set up paralyze
 */
void
create_paralyze()
{
    set_fail_message("You are in agony and in the state of shock. Paralyzed "
    +"by the critical trauma bestowed upon you, you feel weaker and weaker "
    +"for every second as you rapidly bleed out and can do nothing but "
    +"wait for the inevitable.\n");
    
    set_name(({"_fireknife_bleed_paralyze"}));
    
    set_alarm(1.0, 1.0, &bleed_effect());
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
        case "v":
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