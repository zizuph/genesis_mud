
/* 
    ~Calia/fireball/inherit/help_support.c 

    This is support for fireball help topics. 

    Coded by Maniac@Genesis, 1999

    Copyright (C) Miguel Leith 1999
*/ 

#pragma strict_types

#include "defs.h"
#include FIREBALL_HEADER


int
do_help(string str)
{
    string *topics; 

    if (!stringp(str)) 
        return 0; 

    if (str == "fireball") {
        if (!sizeof(topics = get_dir(FIREBALL_HELP))) 
            return 0; 
        this_player()->more("Type \"help fireball <topic>\" for " +
                            "information. The topics are:\n" +
                            sprintf("%70#s\n", implode(topics, "\n"))); 
        return 1; 
    } 

    if (sscanf(str, "fireball %s", str) != 1 ||
        !sizeof(topics = get_dir(FIREBALL_HELP)) ||
        member_array(str, topics) == -1)
        return 0; 

    this_player()->more(read_file(FIREBALL_HELP+str)); 
    return 1; 
}


void
init_help_support()
{ 
    add_action(do_help, "help"); 
}
