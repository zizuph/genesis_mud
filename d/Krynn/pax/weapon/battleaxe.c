/*
   Pax Tharkas, Axes for the zombies in the crypt.

   battleaxe.c
   -----------

   Coded ........: 95/04/30
   By ...........: Jeremiah

   Latest update : 95/07/02
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
   set_name(({"battle axe", "axe"}));
   set_short("battle axe");
   set_long("This is a fine dwarven weapon. A sturdy double bladed " +
            "battle axe, with a solid haft. The weapon preferred by " +
            "the dwarves of the clan Neidar, also known as hill " +
            "dwarves.\n");
   set_default_weapon(30, 25, W_AXE, W_SLASH, W_ANYH);
   add_prop(OBJ_I_VOLUME, 1800);
   add_prop(OBJ_I_WEIGHT, 6000);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30,25));
}
