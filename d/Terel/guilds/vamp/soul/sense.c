
#include "../guild.h"

#include "/std/combat/combat.h"
#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>


int
sense(string str)
{
    if (MASTER_OB(ENV(TP))==ROOM_DIR+"coffin")
    {
        object * targets=FILTER_LIVE(all_inventory(ENV(ENV(TP))));
        targets=filter(targets,&operator(==) (0) 
                @ &->query_prop(LIVE_I_UNDEAD));
        if (sizeof(targets))
        {
            write("You hear the " +
            (sizeof(targets)==1 ? "heartbeat" : "heartbeats") +
            " of "+ LANG_NUM2WORD(sizeof(targets)) + 
            (sizeof(targets)==1 ? " mortal" : " mortals") +
            " from outside your coffin.\n");
        }
        else
        {
            write("You hear nothing from outside your coffin.\n");
        }
        return 1;
    }
    mixed * exits=ENV(TP)->query_exit();
    if (!sizeof(exits))
    {
        write("You do not sense any prey nearby.\n");
        return 1;
    }
    if (TP->query_attack())
    {
        write("You are too busy fighting to listen for noise.\n");
        return 1;
    }
    int found_room=0;
    for (int i=0;i<sizeof(exits);i+=3)
    {
        object room=find_object(exits[i]);
        if (!room)
            continue;
        object * targets=FILTER_LIVE(all_inventory(room));
        targets=filter(targets,&operator(==) (0) 
                @ &->query_prop(LIVE_I_UNDEAD));
        if (sizeof(targets))
        {
            write("You hear the sound" +
            " of "+ LANG_NUM2WORD(sizeof(targets)) + " " +
            (sizeof(targets)==1 ? "heartbeat" : "heartbeats") +
            " from the "+ exits[i+1]+ " exit.\n");
            found_room=1;
        }
    }
    if (!found_room)
    {
        write("You do not sense any prey nearby.\n");
    }
    return 1;
}
