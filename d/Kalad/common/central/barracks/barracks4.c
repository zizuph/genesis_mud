/* Barracks */
/* Made by Korat 100195 */
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/filter_funs.h"

static object npc;

void
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   hear_bell = 2;
   set_short("Barracks");
   set_long("You have entered the office of the master of the militia guards "+
      "here in the city of Kabal. The wooden floor is "+
      "almost covered with a huge soft carpet, and on top of "+
      "it you see a large desk littered with sheets. "+
      "On the eastern wall you can see the enormous statue through an open plain window.\n");
   
   
   add_item("desk","A large desk with several closed drawers. Its "+
      "littered with sheets, feather pens and ink.\n");
   
   add_item(({"sheet","sheets"}),"When you take a quick look at all the "+
      "sheets, you recognize letters, orders to his officers and "+
      "some maps of Kabal.\n");
   
   add_item("window","It's a plain window that gives both fresh air "+
      "and an excellent view of the plaza and its huge statue. "+
      "The statue looks very ugly even from this height!\n");
   
   clone_object("/d/Kalad/common/central/doors/barracks_door2")->move(TO);
   set_alarm(0.0,0.0,"reset_room");
}

void
reset_room()
{
   if (!objectp(npc))
      {
      npc = clone_object("/d/Kalad/common/central/npc/guard_chief");
      npc -> arm_me();
      npc -> move_living("a human turns to face you", TO);
   }
}

