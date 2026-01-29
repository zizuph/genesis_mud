#pragma strict_types

#include "local.h"
#include DEFS
#include CLOCKH

inherit OR_FILE

static string leading;

public void create_south_ergoth_road()
{
}

void create_krynn_room()
{
    string *dirs;
    int exits;
    
    create_south_ergoth_road();

    dirs = this_object()->query_exit_cmds();
    exits = sizeof(dirs);
    if(!exits)
        leading = "nowhere";
    else
    {
        leading = dirs[0];
        
        if(2 == exits)
            leading += " and " + dirs[1];
        
        if(2 < exits)
        {
            int i;
            for(i = 1; i < exits - 1; i++)
                leading += ", " + dirs[i];
            leading += " and " + dirs[i];
        }
    }

    set_short("A road leading " + leading);
    set_long("This is not a style-guide approved road, but it leads "
        + leading + ".\n");
}
