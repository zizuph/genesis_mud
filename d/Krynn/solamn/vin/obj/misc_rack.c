/*
 * Filename:        misc_rack.c
 * Description:     A box for storing herbs
 *
 * Coded by Daniel W. Mathiasen aka Boron
 *
 * Revision history:
 *
 */
inherit "/std/container";

#include "/d/Krynn/common/defs.h"
#include "../knight/guild.h"
#include <stdproperties.h>
#include <macros.h>
#include <files.h>

void
create_container()
{
  set_name("rack");
  add_name(({"box", "armoury"}));
  set_adj(({"dark", "green"}));

  set_short("dark green rack");
  set_long("Your eyes behold a nice looking rack. The wooden structure "
           + "is rather clear. Here Knights store various items of interest "
           + "to other Knights.\n\n");

  add_prop(CONT_I_MAX_WEIGHT,  3000000); /* 2000 kilos */
  add_prop(CONT_I_MAX_VOLUME,  2000000); /* 2000 liters */
  add_prop(CONT_I_WEIGHT, 20000);
  add_prop(CONT_I_VOLUME, 160000);
  add_prop(CONT_I_RIGID, 1);
  add_prop(OBJ_M_NO_GET, "The rack is bolted to the wall..\n");
}

int
prevent_leave(object ob)
{
    if (MEMBER(TP))
    return 0;

   if(TP->query_wiz_level())
      return 0;
   write("A squire arrives and informs you not to remove the " +
      "items from the rack.\n");
   return 1;
}



