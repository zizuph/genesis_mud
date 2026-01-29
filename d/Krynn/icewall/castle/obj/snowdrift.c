/*
 * Some idiot abuser forced us to limit the amount of snowballs one can get.
 *
 * Cotillion
 */
#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
inherit "/std/object";

#define SNOWBALL_PROP "krynn_i_got_snowball"
#define SNOWBALL_LIMIT 50


void
create_object() {
    set_name("snowdrift");
    add_name("drift");
    set_short("snowdrift");
    set_long("It is a large and impressive snowdrift. " +
        "It appears that something may be buried within it.\n");
    
    add_prop(OBJ_I_WEIGHT, 560000);
    add_prop(OBJ_I_VOLUME, 5600000);
        
    add_prop(OBJ_I_NO_GET,1);
    
    add_prop(OBJ_S_SEARCH_FUN, "search_snowdrift");
}

string
search_snowdrift(object player, string arg)
{
    return "You discover that a very large horde of snowballs has been "
        + "buried here. Maybe you should get one or two for fun?\n";
}

int
get(string arg)
{
    object ob;
    if (arg == "snowball")
    {
        if (TP->query_prop(SNOWBALL_PROP) >= SNOWBALL_LIMIT)
        {
            write("There are no more snowballs for you.\n");
            return 1;
        }
        
        TP->add_prop(SNOWBALL_PROP,
            TP->query_prop(SNOWBALL_PROP) + 1);
            
        
        setuid();
        seteuid(getuid());
        
        write("You get a snowball.\n");
        say(QCTNAME(TP)+" pulls something from the snowdrift.\n");

        ob = clone_object(SNOWBALL);
        if (ob->move(TP))
        {
            ob->move(environment());
            write("The snowball is too heavy.\n");
            return 1;
        }
        return 1;
    }
    NF("Get what?\n");
    return 0;
}

void
init()
{
    ::init();
    add_action(get, "get");
}
