inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include <stdproperties.h>
#include <macros.h>
/* by Antharanos */
void
create_room()
{
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Flat hilltop.\n");
   set_long("You are standing atop a hill, verdant plains of grass "+
      "filling your view in every direction. In the distance far to the "+
      "north and south are what appear to be mountains. A worn trail leads "+
      "down the hill, heading east.\n");
   add_item(({"hill"}),"A small rise in an otherwise flat landscape.\n");
   add_item(({"verdant plains of grass","verdant plains","plains","plain","grass"}),
      "Tall, waist-high grass grows all around you, stretching to the "+
      "horizon and swaying slightly in the breeze.\n");
   add_item(({"horizon"}),"A fine line in the distance.\n");
   add_item(({"sky"}),"The sky above is partly cloudy, and the faint image "+
      "of the sun seems to glow from behind some of them.\n");
   add_item(({"clouds","cloud"}),"They float lazily across the sky.\n");
   add_item(({"sun"}),"The faint outline of the sun is visible behind a "+
      "group of clouds.\n");
   add_item(({"mountains","mountain"}),"Only a brown line in the horizon is "+
      "visible.\n");
   add_item(({"worn trail","trail"}),"A dirt pathway that leads off the "+
      "hill into the plains east of here.\n");
   add_exit("/d/Cirath/katakoro/wastes/kalad_connect","east",0,2);
}
come_and_go(which)
{
   object oncarpet,realcarpet;
   oncarpet=present("carpet",TO);
   if(which==0&&!oncarpet) { /* 0 = arriving, 1 = leaving */
      oncarpet=clone_object("/d/Kalad/common/wild/pass/desert/carpet/carpet");
      oncarpet->move(TO);
      tell_room(TO,
         "The flying carpet come hurtling out of the sky to land at your feet.\n");
      return 1;
   }
   if(which==1&&oncarpet) {
      realcarpet=present("carpet",TO);
      "secure/master"->do_debug("destroy",realcarpet);
      tell_room(TO,
         "The flying carpet rises into the air and disappears into the distant "+
         "horizon.\n");
      return 1;
   }
}
