/*
 * 9jail.c
 * Another Jail Cell in the Caverns.
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
  object door;
  
  set_short("Prison Cell");
  set_long("   Standing in the dark, circular chamber, your eyes "+
	   "peer through the darkness to examine your surroundings. "+
	   "You are in what appears to be an old cell of some kind. The "+
	   "sight of shackles and a broken whip in the center of the "+
	   "room confirms this observation. Looking to the corner "+
	   "of the stone room, you notice an unkept bed which seems "+
	   "to be exuding a foul odor.\n\n");
  
  add_item(({"shackles","shackle"}),
	   "These shackles are deeply stained by blood and rust. The "+
	   "recent blood tells of frequent use of this death device.\n");
  add_item(({"blood","stains","blood stains","blood stain"}),
	   "The dried blood appears to be from the wrists of the "+
	   "poor souls who once occupied the shackles.\n");
  add_item(({"bed","unkept bed"}),
	   "This bed reeks of putrified flesh.  It looks as if the sheets "+
	   "have never been changed.  You cannot image what hard creature "+
	   "would lie in such filth and smell.\n");

  add_prop(ROOM_I_INSIDE, 1);

   add_exit(THIS_DIR + "1guardrm","northwest");
   seteuid(geteuid());

   door = clone_object(THIS_DIR+"obj/pdoor1b");
   door ->move(TO);
}

void
enter_inv(object ob, object from)
{
   object guard;
   ::enter_inv(ob,from);
   guard = present("guard",ENV(ob));
   if(guard)
      tell_room(ENV(ob),"The guard wakes from his nap.\n");
   return;
}







