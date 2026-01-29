/*
   breadknife.c
   ------------

   Coded ........: 95/03/26
   By ...........: Jeremiah

   Latest update : 95/03/26
   By ...........: Jeremiah

   Breadknife for the gullies in Pax tharkas.

*/


inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name(({"bread knife", "knife"}));
    set_adj("large");
    set_long("This is a knife mostly used to cut bread, vegetables or " +
             "things like that. In other words it's mostly used as a " +
             "kitchen tool. It could probably be used a weapon though. " +
             "It looks quite sharp.\n");
    set_short("bread knife");
    set_default_weapon(8, 10, W_KNIFE, W_SLASH , W_ANYH);
    add_prop(OBJ_I_VOLUME, 600);
    add_prop(OBJ_I_WEIGHT, 600);
}

