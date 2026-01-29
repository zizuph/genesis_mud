/*
   Pax Tharkas, Lomgswords for the zombies in the crypt.

   zlongsword.c
   ------------

   Coded ........: 95/04/25
   By ...........: Jeremiah

   Latest update : 95/04/25
   By ...........: Jeremiah


*/

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include "/d/Krynn/pax/local.h"

create_weapon()
{
   set_name(({"longsword", "sword"}));
   set_short("longsword");
   set_long("This is a fine elven sword, long and slender. A typical " +
            "elven longsword, a slim blade and a hilt, carefully " +
            "ornamented with metal carvings.\n");
   set_default_weapon(30, 25, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
   add_prop(OBJ_I_VOLUME, 1800);
   add_prop(OBJ_I_WEIGHT, 6000);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30,25));
}


