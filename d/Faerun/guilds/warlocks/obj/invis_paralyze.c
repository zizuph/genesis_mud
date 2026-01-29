/* /d/Faerun/guilds/warlocks/rooms/obj/invis_paralyze.c
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

void remove_illusion_paralyze();

/*
 * Function name: remove_illusion_paralyze
 * Description: Automatically removes the paralyzeobject.
 */
 void
 remove_illusion_paralyze()
 {
     write("You are now suddenly visible, and you can move again.\n");
     
     this_player()->remove_prop(OBJ_I_INVIS);
     
     remove_object();
 }
 
 
/*
 * Function name: create_paralyze
 * Description:   Set up paralyze
 */
void
create_paralyze()
{
    set_fail_message("In this invisible state you can do "
    +"nothing but observe or end the effect with the command "
    +"'urgrendbel', "
    +"which will return you back to normal.\n");
    
    set_name(({"_war_illusion_paralyze"}));
    
    this_player()->add_prop(OBJ_I_INVIS, 50);
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
        case "urgrendbel":
        remove_illusion_paralyze();
        return 1;
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