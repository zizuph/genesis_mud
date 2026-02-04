//-*-C++-*-
// file name:      urn.c 
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
    add_name(({"_columbarium_urn", "_isabella_urn"}));
    set_name("urn");
    set_short("red carnelian urn");
    set_adj(({"red", "carnelian", "columbarium", "isabella", "isabella's"}));
    set_long("It is a red carnelian urn, meant to hold the ashes "+
        "of those who have died. It bears the name Isabella.\n ");
    
    add_prop(OBJ_I_VOLUME, 1000);   
    add_prop(OBJ_I_WEIGHT, 1000);   
    add_prop(OBJ_I_VALUE, 100);
    add_cmd_item(({"urn"}), "open", "It is sealed closed.\n");
}             
