/* /d/Faerun/guilds/vampires/obj/box4_paralyze.c
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
    write("You lose focus, and return to yourself "
    +"with a sense of loss.\n");

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
        environment(this_object())->catch_tell("\n\nAn acrid "
        +"smell fills the air.\n\n");
    }    

    if (cutscene_timer == 1)
    {
        environment(this_object())->catch_tell("Death and decay "
        +"compounded with a putrid stagnation assaults your "
        +"senses; a stale air that you can taste on your "
        +"tongue. Yet, there is an indiscernible sweetness buried "
        +"within that beckons you to follow, luring you to "
        +"something unseen, compelling you. It is yours for the "
        +"taking, you need only reach out and claim it as it "
        +"truly belongs to you and you alone. There is nothing but "
        +"it, nothing beyond ...it. It siezes you, inescapably "
        +"drawing you closer; resistance is futile. Suddenly it "
        +"escapes and disappears. Gone! Anger and frustration "
        +"envelop your thoughts.\n");
    }
    
    if (cutscene_timer == 2)
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
    set_fail_message("You are paralyzed, and can't move!\n");
    
    set_name(({"box4_paralyze"}));
    
    set_alarm(1.0, 10.0, &cutscene_effect());
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
        case "vitals":
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