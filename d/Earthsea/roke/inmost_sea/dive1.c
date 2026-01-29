/* Dive1 room, Jakob 95-07-13 */
#include "defs.h"
inherit "/d/Earthsea/std/room";
#include <stdproperties.h>
#include "/d/Earthsea/sys/room_defs.h"
#pragma strict_types

/* Variables */


/* Headers */
public int enter_boat();
public void enter_inv(object ob,object from);

public void
create_earthsea_room()
{
   set_short("Under water");
   set_long("You dive as far as you can, luckily the water is " +
      "shallow here. The sun barely lights up the muddy " +
      "bottom.\n");
   add_exit(INMOST_SEA + "S", "up", "@@up_again", 6);
   UNDER_SEA
}

public void
up_again()
{
   write ("You set off for the light far above you.\n");
   set_alarm(2.0, 0.0, &enter_boat());
}

public int
enter_boat()
{
   write("You break the surface of the water and quickly " +
      "enter the boat again.\n");
   return 1;
}

public void
enter_inv(object ob,object from)
{
   ::enter_inv(ob, from);
   if(ob->id("shark"))
      return;
   if(present("waterobj", ob))
      return;
   if(living(ob))
      clone_object(INMOST_SEA + "obj/waterobj")->move(ob, 1);
}



