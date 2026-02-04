//-*-C++-*-
// file name:      
// creator(s):     Lilith June 2008
// last update:    
// note: 
// bug(s):
// to-do:

inherit "/std/receptacle";

#include "../defs.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>

object key;

void
clone_key(object to)
{
    reset_euid();

    if (!key || ENV(key)!=TO)
    {
        key = clone_object(OBJ_DIR +"key");
        key->move(to, 1);
    }
}

public string 
search_drawer(object player, string str)
{      
    object player = this_player();
    switch (str)
    {
        case "drawer":    
        case "desk":  
        case "desk drawer":
        case "back of drawer":
        if (TO->query_prop(CONT_I_CLOSED))
        {
            return "You brush your fingers along the edges of the drawer "+
                   "but find nothing of interest. Perhaps you should open "+
                   "it.\n";
            break;
        }        
        if (!key || ENV(key)!=TO)
        {
            clone_key(player);
            return "Your fingers fish a key out of the back of the drawer.\n";
            break;
        }
        default:  return "";

    }
     return "";    
}


void
create_receptacle()
{
    set_name("drawer");
    add_name("desk drawer"); 
    set_long("This is the central drawer of the desk, located "+
        "directly beneath the desktop.\n");
    add_prop(OBJ_I_VALUE,  100); 
    add_prop(CONT_I_CLOSED, 1);
    add_prop(OBJ_M_NO_GET, "You try to remove the drawer from the "+
        "desk but cannot.\n");
    add_prop(CONT_I_WEIGHT, 1000);
    add_prop(CONT_I_VOLUME, 4000);     
    add_prop(CONT_I_MAX_VOLUME, 90000);  
    add_prop(CONT_I_MAX_WEIGHT, 90000); 
    add_prop(CONT_I_RIGID, 1);

    seteuid(getuid(TO));
    clone_key(TO);
    set_no_show_composite(1); 
    add_prop(OBJ_S_SEARCH_FUN, "search_drawer");

}
