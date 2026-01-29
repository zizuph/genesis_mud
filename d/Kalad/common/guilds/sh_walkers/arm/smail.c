/*
 *	File: ~Kalad/common/guilds/sh_walkers/arm/smail.c
 *
 *	A standard Shadow Walker's chainmail.
 *
 *			-Rico  7.01.97
 *			Revision:
 */

#include "../defs.h"

inherit "/std/armour";

create_armour()
{
   set_name("chainmail");
   add_name("mail");
   set_adj("rough");
   set_long("This mail armour is the basic body armour available to "+
      "Shadow Walkers.  It is quite beat up and blood stained, but "+
      "looks as though it has done the work it was intended for.\n");

   set_at(TS_TORSO);
   set_ac(19);

   add_prop(OBJ_I_WEIGHT, 8000);
   add_prop(OBJ_I_VOLUME, 1250);
   add_prop(OBJ_I_VALUE, 200);
}

