/*
 * /d/Kalad/common/guilds/sh_walkers/obj/torch.c
 * Created By : Rico 7.01.97
 * First Modif:
 */

inherit "/std/torch";

#include <stdproperties.h>

void
create_torch()
{
   ::create_torch();

   set_short("small torch");
   set_long(
      "A small torch used to light the way.\n");

   set_time(500);
   set_strength(3);
   set_value(50);
}

