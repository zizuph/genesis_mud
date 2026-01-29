/*
   meatcleaver.c
   -------------

   Coded ........: 95/03/26
   By ...........: Jeremiah

   Latest update : 95/03/26
   By ...........: Jeremiah

   Meatcleaver for the gullies in Pax tharkas.

   Modified by Navarre June 11th 2006,
   Added set_short, and fixed the set_name to do it correctly.
*/


inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("cleaver");
    set_adj("sturdy");
    add_adj("meat");
    set_short("sturdy meat cleaver");
    set_pshort("sturdy meat cleavers");
    set_long("This is actually a kitchen tool, but if used as a weapon " +
             "it might be very deadly. It looks quite heavy and very " +
             "sharp.\n");
    set_default_weapon(10, 15, W_AXE, W_SLASH , W_ANYH);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_WEIGHT, 2000);
}

