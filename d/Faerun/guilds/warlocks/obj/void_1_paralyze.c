/* 
 * 
 * Nerull 2020
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

void remove_cutscene_paralyze();

int cutscene_timer = 0;

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
    
    environment(this_object())->catch_tell("\nThe light below you grows fast in size, and consumes "
    +"you! You realize you are somewhere else!\n\n");
    
    environment(this_object())->move_living("M", "/d/Gondor/rohan/plains/j06", 1);  
    
    tell_room("/d/Gondor/rohan/plains/j06", QCTNAME(environment(this_object()))
    +" arrives in a puff of smoke.\n", environment(this_object()));
	
    //write("You feel you can move again.\n");

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

    if (cutscene_timer == 0)
    {
        environment(this_object())->catch_tell("\nYou are suddenly in a black empty "
        +"void! You feel that you are falling towards the abyss below you!\n\n");
    }
    
    if (cutscene_timer == 1)
    {
        environment(this_object())->catch_tell("You are falling, and you "
        +"sense you are picking up speed!\n");
    }
    
    if (cutscene_timer == 2)
    {
        environment(this_object())->catch_tell("You feel the wind passes you as "
        +"you keep accelerating towards the bottomless void below you!\n");
    }
    
    if (cutscene_timer == 3)
    {
        environment(this_object())->catch_tell("You are flailing with your arms "
        +"as you are falling downwards with great speed!\n");
    }
    
    if (cutscene_timer == 4)
    {
        environment(this_object())->catch_tell("Far below you, a tiny point of light "
        +"which starts to grow!\n");
    }
    
    
    if (cutscene_timer == 5)
    {
        remove_cutscene_paralyze();
        
        return;
    }
     
    cutscene_timer = cutscene_timer + 1;
    
    return;
}
 
 
/*
 * Function name: create_paralyze
 * Description:   Set up paralyze
 */
void
create_paralyze()
{
    set_fail_message("You are busy being moved through time "
    +"and space, and can't do anything!\n");
    
    set_name(({"void_1_paralyze"}));
    
    set_alarm(1.0, 20.0, &cutscene_effect());
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