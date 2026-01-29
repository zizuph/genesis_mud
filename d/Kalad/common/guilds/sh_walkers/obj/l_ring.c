
/*
 * /d/Kalad/common/guilds/sh_walkers/obj/l_ring.c
 * Created By : Rico 7.01.97
 * First Modif: 
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
   ::create_armour();

   set_short("light ring");
   set_long("This is one of the famous Shadow Light Rings "+
      "of the Deep Darks.  Hard to come by, this is one of "+
      "the few tools which permits the infamous Shadow "+
      "Walkers of Kabal to cast light into a room when the "+
      "dark proves too much even for them.\n");


   add_prop(MAGIC_AM_MAGIC, ({ 20, "abjured"}) );
   add_prop(MAGIC_AM_ID_INFO, ({ "You feel there is something good about "+
                                  "this ring",10,
                                  "This ring raidates limited light when "+
                                  "worn.",20,
                                  "This ring adds +5 to the light in the "+
                                  "room",50 }) );

   set_default_armour(5, A_MAGIC);
}
