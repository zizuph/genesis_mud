/*
 * The Order, layman cleric soul
 *
 * Nerull, 2021
 *
 */

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";
inherit "/d/Genesis/specials/guilds/lib/utility_functions";


#include "../guild.h"
#include <ss_types.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <macros.h>


public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "The Order"; }

public mapping
query_cmdlist()
{
    return ([
        // Commands
        //"orlist"        : "orlist",
        "orhelp"          : "s_orhelp",
        
        // Emotes
        "orgrin"          : "do_orgrin",
        ]);
}


int
s_orhelp(string str)
{  
    if (str == "emotes")
    {
        write(""   
        +"================================================================\n"
        +"|       T H E   O R D E R  --  C L E R I C   E M O T E S       |\n"
        +"|--------------------------------------------------------------|\n"
        +"|            The general emotes for warlocks.                  |\n"
        +"|                                                              |\n"
        +"| orgrin                  : Contort face into a slight grin    |\n"
        +"|______________________________________________________________|\n");
        
        return 1;
    }
    
    write(""
    +"=====================================================================\n"
    +"|           T H E   O R D E R  --  C L E R I C   H E L P            |\n"
    +"|-------------------------------------------------------------------|\n"
    +"|  You can get help for The Order by using the commands             |\n"
    +"|  below.                                                           |\n"
    +"|                                                                   |\n"
    +"|    > orhelp                           : This list                 |\n"
	+"|    > orhelp emotes                    : List of emotes            |\n"
    +"|    > spelleffects                     : List active spells        |\n"
    +"|-------------------------------------------------------------------|\n"
    +"|___________________________________________________________________|\n");
    
    return 1;   
}


/*public int
orlist(string str)
{
    setuid();
    seteuid(getuid());

    MEMBER_LIST_UTILITY->list_members();

    return 1;
}*/


//////////////////////////// EMOTES /////////////////////////////
int
do_orgrin()
{
    write("Your face contorts into a slight, barely noticable grin.\n");
    all("'s face contorts into a slight, barely noticable grin.");

    return 1;
}