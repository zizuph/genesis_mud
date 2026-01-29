/*
 * Poison used in quest.
 * -- Finwe April 2005
 */

#pragma save_binary
#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";

int poison_used = 0;

create_object()
{
    set_name(({"poison","_faerie_poison"}));
    add_name("bottle");
    set_adj(({"small", "brown"}));
    set_short("small brown bottle");
    set_pshort("small brown bottles");
    set_long("@@long_descr@@");

   add_prop(OBJ_I_WEIGHT, 1);
   add_prop(OBJ_I_VALUE, 5);
   add_prop(OBJ_I_VOLUME, 10);
}
void
init()
{
    ::init();

    add_action("smell_poison", "sniff");
    add_action("smell_poison", "");
}

string
long_descr()
{
    string long_desc = "This is a small brown bottle. It is used to store liquids. " ;
        
    if(poison_used == 0)
    {
        long_desc += "The bottle has a small amount of clear liquid in it. The liquid looks deadly.\n";
    }
    else
    {
        long_desc += "The bottle is empty.\n";
    }

    return long_desc;
}

int smell_poison(string str)
{
    if (!strlen(str) ||
        !parse_command(str, ({ }),
             "[the] [small] [brown] 'bottle' / 'poison'"))
    {
        notify_fail ("Smell what, the bottle?\n");
        return 0;
    }
    
    write("You take a small sniff of the bottle and don't smell anything.\n");
    say(QCTNAME(TP) + " smells a " + short() + "\n");
    return 1;
}
