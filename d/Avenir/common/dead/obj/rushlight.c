//-*-C++-*-
// file name:     
// creator(s):    Lilith, June 2021.   
// purpose:       Light source in the catacombs
// note:          
// last update:

inherit "/std/torch";
inherit "/lib/keep";
#include <stdproperties.h>
#include <macros.h>

void 
create_torch()
{
    set_name("rushlight");
    add_name(({"_catacomb_rushlight"}));
    set_pname("rushlights");
    set_short("rushlight");
    set_pshort("rushlights");
    set_long("This rushlight provides gentle illumination when lighted. "
        +"It is made from the dried and peeled stem of a rush plant "
	    +"that is dipped in animal fat.@@lit_desc@@\n");
    set_keep(1);
    set_time(900); // 15 mins
    set_strength(1);
    set_value(100 + random(25));
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_M_NO_SELL, "@@dont_sell@@");
}

mixed 
dont_sell()
{
    if(query_prop(OBJ_I_HAS_FIRE))
        return "Extinguish it first.\n";
    else
        return 0;
}

string 
lit_desc()
{
    if(!query_time())
        return " It doesn't look like there is much left to burn.";
    else if(!query_prop(OBJ_I_HAS_FIRE))
        return "";
    else
        return " It casts a small pool of light.\n";
}

string
query_recover()
{
   return MASTER + ":" + query_torch_recover();
}

void
init_recover(string arg)
{
   init_torch_recover(arg);
} 


