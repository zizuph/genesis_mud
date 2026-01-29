/* /d/Faerun/guilds/vampires/obj/box3_paralyze.c
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
    write("The acuteness of your senses returns to normal "
    +"leaving you utterly confused. What is happening?\n");

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
        environment(this_object())->catch_tell("\n\nA loud "
        +"thud deafens you.\n\n");
    }    

    if (cutscene_timer == 1)
    {
        environment(this_object())->catch_tell("Panic!\n"
        +"You relax and while calmness overcomes you, everything "
        +"is in clear, sharp focus, as if you were seeing everything "
        +"closely.\nPAIN!\nLips move in the distance, whispering, "
        +"yet the sound is a tumult of screams. Suddenly you hear "
        +"mumbling in the distance accompanied by a stutter. Chains "
        +"rattle and clank along with a cry for help. From where? "
        +"Who is it? As suddenly as the sounds washed over you, "
        +"they disappear as though they were washed away.\n");
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
    
    set_name(({"box3_paralyze"}));
    
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