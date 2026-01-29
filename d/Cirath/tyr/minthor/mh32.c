inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/tyr/tyr.h"
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

object leader;
object guard1;
object guard2;
object guard3;

/*
void
help_func();

void
rescue_func(object foo);
*/

void
reset_room()
{
    if (leader) return;
  bring_room_team(TZ_MINTHOR+"npc/mwarrior",1,2,TZ_MINTHOR+"npc/guard2",1);
/*
   leader = clone_object(TZ_MINTHOR + "npc/mwarrior");
	leader->move(TO);
	leader->arm_me();
	leader->set_monster_home(TZ_MINTHOR+"mh32");
*/
}


 
void
create_room()
 {
  set_short("Hallway");
  set_long("You are in the northern hall of the second floor of the "
	+"Minthor House.  South of you lies the way back to the stairs "
	+"and some bedrooms, while to your northwest there is a door "
	+"and the hall continues on to the northeast.  The walls here "
	+"decorated with strange paintings that are hard to comprehend, "
	+"it almost seems like the artist was not trying to convey "
	+"a traditional visual idea.  There are also strange globes "
	+"hovering in the air near the ceiling that are providing light.\n");
  add_item(({"globe","globes"}),"They are roughly six inches in diameter "
	+"and provide light equivalent to that of a torch.\n");
  add_item(({"painting","paintings"}),"They seem to be splashed with "
	+"various colors in a random pattern.  There are streaks of "
	+"black and grey interspersed which makes the paintings seem "
	+"as if they were trying to get a point across.  What point, you "
	+"are not sure.\n");
  add_item(({"wall","walls"}),"The walls stretch out around you.\n");
  add_item(({"door","doors","northwest door"})," The door "
	+"looks to be made of beautiful carved agafari wood, which is known "
	+"for its strength and durability.  It would be a mistake to try and "
	+"break it down.\n");
  INSIDE

   add_exit(TZ_MINTHOR + "mh35","northeast");
  add_exit(TZ_MINTHOR + "mh33","northwest","@@k_block");
  add_exit(TZ_MINTHOR + "mh29","south");
  set_alarm(1.1,0.0,"reset_room");
}


k_block()
{
  object guard = present ("kranj'k", TO);
  if(objectp(guard))
    {
     TP->catch_msg(QCTNAME(guard)+" puts his hand on your "
	+"chest and says: Sorry buddy, no visitors.\n");
   return 1;
    }
   return 0;
}

/*
void
help_func()
{
	if (!guard1)
	{
		guard1 = clone_object(TZ_MINTHOR + "npc/guard3.c");
		guard1->move(TO);
		guard1->arm_me();
		guard1->command("assist kranj'k");
	}
	if (!guard2)
	{
		guard2 = clone_object(TZ_MINTHOR + "npc/guard3.c");
		guard2->move(TO);
		guard2->arm_me();
		guard2->command("assist kranj'k");
	}
	if (!guard3)
	{
		guard3 = clone_object(TZ_MINTHOR + "npc/guard3.c");
		guard3->move(TO);
		guard3->arm_me();
		guard3->command("assist kranj'k");
	}
}

void
rescue_func(object foo)
{
	if (guard1)
		foo->attack_object(guard1);
	if (guard2)
		foo->attack_object(guard2);
	if (guard3)
		foo->attack_object(guard3);
}
*/
