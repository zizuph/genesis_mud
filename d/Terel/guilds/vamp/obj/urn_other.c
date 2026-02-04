//-*-C++-*-
// file name:      urn_other.c 
// creator(s):     Lilith June 2008
// last update:    
// note: 
// bug(s):
// to-do:

inherit "/std/object";
#include <stdproperties.h>
#include "../guild.h";

void
create_object()
{
    set_name("urn");
    set_short("columbarium urn");
    set_adj(({"columbarium"}));
    set_long("It is a columbarium urn, meant to hold the ashes "+
        "of those who have died.\n ");
    
    add_prop(OBJ_I_VOLUME, 1000);   
    add_prop(OBJ_I_WEIGHT, 1000);   
    add_prop(OBJ_I_VALUE, 100);
    add_cmd_item(({"urn"}), "open", "It is sealed closed.\n");
}             
