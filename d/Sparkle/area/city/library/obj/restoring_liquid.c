/*
 *  /w/petros/sparkle/library/obj/restoring_liquid.c
 *
 *  This is the restoring liquid that Nikolon needs for
 *  the book restoring quest. It is made of a lemon and
 *  10 kidneys. This item is cloned by Gastol.
 *  
 *  Created by Petros, April 2008
*/

#pragma strict_types

inherit "/std/object";

// Includes
#include <stdproperties.h>
#include <macros.h>

// Global Variables
string owner;

void
create_object()
{
    set_name("liquid");
    add_name("_library_restoring_liquid");
    add_name("flask");
    set_adj( ({ "restoring", "book" }) );
    set_short("book restoring liquid");
    set_long("The small flask contains a liquid of a murky cream color. "
           + "A small label on the flask indicates that this liquid is "
           + "to be used to restore books.\n");

    add_prop(OBJ_M_NO_SELL, "No one would want to buy this item.\n"); 
    
    add_prop(OBJ_I_WEIGHT, 15);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 100);
    
    owner = "nobody";
    
    add_item( ({ "label", "small label" }),
                 "The label indicates that this liquid is to be used "
               + "to restore books."
               + "\n");
}

public void
set_owner(string name)
{
    owner = name;
}

public string
get_owner()
{
    return owner;
}

public string
query_recover()
{
    string recovery_string;
    recovery_string = MASTER + ":";
    if (!strlen(owner))
    {
        return recovery_string;
    }
    recovery_string += owner + "#";
    return recovery_string;
}

public void
init_recover(string arg)
{
    sscanf(arg, "%s#", owner);    
}
