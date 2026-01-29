inherit "/std/object";
inherit "/cmd/std/command_driver.c";

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <cmdparse.h> 
#include <filter_funs.h>
#include "/d/Gondor/defs.h"


public int	read_map(string arg);

void
create_object()
{
    set_name("map");
    add_name("horse-lovers-map");
    set_adj("half-finished");
    add_adj("horse-lovers");
    set_short("half-finished map");
    set_long("\n"+
    "             Map of the horse-lovers' fortress.             \n"+
    "                                                            \n"+
    "                                                            \n"+
    "                                                *           \n"+ 
    "                                                |           \n"+ 
    "                                                *           \n"+ 
    "                                              /             \n"+ 
    "                                * - *       *               \n"+ 
    "                                      \\     |               \n"+ 
    "              * - - - - *           * - * - *               \n"+ 
    "           door           \\       /         |               \n"+ 
    "                            * - *           *               \n"+ 
    "           **************                   |               \n"+ 
    "       ****   *          **  gate           *               \n"+ 
    "              *          * **               |               \n"+ 
    "              *          *   **             *               \n"+ 
    "              *          *    *           /                 \n"+ 
    "               *        *     **         *                  \n"+ 
    "                ********      * ***                         \n"+ 
    "                              *    ***                      \n"+ 
    "                             **       ***                   \n"+ 
    "                           **            ***                \n"+ 
    "              *************                 ***             \n"+ 
    "                                                            \n"+
    "                                                            \n"+
    "");

    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,10);
    add_prop(OBJ_I_VALUE, 0);
}

void
init()
{
    add_action(read_map, "read");
}

public int
read_map(string arg)
{
    if ( arg == "map" || arg == "horse-lovers-map" ||
    arg == "half-finished map" || arg == "horse-lovers map" )
    {
	write(query_long());
	return 1;
    }
    return 0;
}

/* This object is not recoverable on purpose. */
