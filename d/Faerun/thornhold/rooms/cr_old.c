inherit "/std/room";

#include <cmdparse.h>
#include <composite.h>
#include <const.h>
#include <files.h>
#include <filter_funs.h>
#include <flags.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <mail.h>
#include <options.h>
#include <state_desc.h>
#include <std.h>
#include <stdproperties.h>
#include <time.h>

// Send all zone debugs to this dude
#define DEBUGGING
#ifdef DEBUGGING
#define DEBUGGER "gnim"
#define DEBUG(s) find_player(DEBUGGER)->catch_msg("Quest Helper: "+s+"\n")
#else
#define DEBUG(s)
#endif

public int
who_plus(string str)
{
    object *list = users();
    object *mortals;
    object *wizards;
    int size, k;
    string infoline, loc;
    string *subpaths;
    object env;
    
    /* This filters out players logging in and such. */
    list = FILTER_LIVING_OBJECTS(list);
    
    wizards = filter(list, &->query_wiz_level());
    list    -= wizards;

    
    infoline = sprintf("%15s : %8s : %s\n", "Name", "Idle (s)", "Location");
    write(infoline);
    infoline = sprintf("-Mortals------------------------------------------------\n");
    write(infoline);
    for(k=0; k < sizeof(list); k++)
    {
        loc = objectp(env = environment(list[k])) ? file_name(env) : "VOID";
        subpaths = explode(loc, "/");
        infoline = sprintf("%15s : %8d : %s\n", list[k]->query_real_name(), query_idle(list[k]), subpaths[2]);
        write(infoline);
    }

    infoline = sprintf("-Wizards------------------------------------------------\n");
    write(infoline);
    for(k=0; k < sizeof(wizards); k++)
    {
        loc = objectp(env = environment(wizards[k])) ? file_name(env) : "VOID";
        subpaths = explode(loc, "/");
        infoline = sprintf("%15s : %8d : %s\n", wizards[k]->query_real_name(), query_idle(wizards[k]), subpaths[2]);
        write(infoline);
    }
    
    
    return 1;
}

public int
who_dom(string str)
{
    object *list = users();
    object *mortals;
    object *wizards;
    int size, k;
    string infoline, loc;
    string *subpaths;
    object env;
    
    /* This filters out players logging in and such. */
    list = FILTER_LIVING_OBJECTS(list);
    
    wizards = filter(list, &->query_wiz_level());
    list    -= wizards;

    
    infoline = sprintf("%15s : %8s : %s\n", "Name", "Idle (s)", "Location");
    write(infoline);
    infoline = sprintf("-Mortals------------------------------------------------\n");
    write(infoline);
    for(k=0; k < sizeof(list); k++)
    {
        loc = objectp(env = environment(list[k])) ? file_name(env) : "VOID";
        subpaths = explode(loc, "/");
        if(subpaths[2] == "Faerun")
        {
            infoline = sprintf("%15s : %8d : %s\n", list[k]->query_real_name(), query_idle(list[k]), subpaths[2]);
            write(infoline);
        }
    }

    infoline = sprintf("-Wizards------------------------------------------------\n");
    write(infoline);
    for(k=0; k < sizeof(wizards); k++)
    {
        loc = objectp(env = environment(wizards[k])) ? file_name(env) : "VOID";
        subpaths = explode(loc, "/");
        if(subpaths[2] == "Faerun")
        {
            infoline = sprintf("%15s : %8d : %s\n", wizards[k]->query_real_name(), query_idle(wizards[k]), subpaths[2]);
            write(infoline);
        }
    }
    
    
    return 1;
}

void
create_room()
{
    set_long("This is Gnim's control room.\n" +
             "    whop | who list for location and idle state.\n");

    add_exit("/w/gnim/workroom", "east");
}

/* 
 * Function name : init (masked)
 * Description   : sman init for more detals. It's masked here for 
 *                 command  support.
 */
public void
init()
{
    ::init();
    add_action(who_plus, "whop");
    add_action(who_dom, "dwho");
}
