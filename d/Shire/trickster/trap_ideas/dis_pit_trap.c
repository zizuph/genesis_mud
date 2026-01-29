#pragma save_binary

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

object oldtraproom;
object traproom;

#define SHORT ({"jumbled pile of leaves", "gaping hole","open pit",\
      "pile of dirt"})
#define HOLENAME ({"pile","hole","pit","pile"})
#define HOLENAME2 ({"leaves","gaping hole","open pit","dirt"})
#define ADJ   ({"jumbled","gaping","open","dirt"})
#define LONG ({"This jumbled pile of leaves is a broken trap of "+\
      "some kind, you can see straight to the bottom.\n",\
      "A gaping hole is all that separates you from its bottom.\n",\
      "This open pit is someone's failed attempt at making a trap "+\
      "for the unwary.\n",\
      "This pile of dirt is a deep pit which you might not have seen "+\
      "had it been covered with leaves.\n"})
#define TRAP_LAST_ROOM "trap_last_room"

void
set_trapped_room(object room)
{
   oldtraproom = room;
}

object
get_trap_room()
{
   FIXEUID
   traproom = clone_object("/d/Shire/trickster/obj/pit_room");
   traproom->set_short("Deep in a hole");
   traproom->set_long("You're at the bottom of a newly dug pit.  The way "+
      "out looks like it would be a hard climb.\n");
   return traproom;
}


void
create_object()
{
   int ran;
   ran = random(4);
   set_short(SHORT[ran]);
   set_name("trap");
   add_name("trickster_disarmed_pit_trap");
   add_name(HOLENAME[ran]);
   add_name(HOLENAME2[ran]);
   set_adj("disabled");
   add_adj(ADJ[ran]);
   set_long(LONG[ran]);
   add_prop(OBJ_I_WEIGHT, 15000);
   add_prop(OBJ_I_VOLUME, 150000);
   add_prop(OBJ_I_NO_GET,1);
   set_alarm(3600.0,0.0,"remove_object");
}

void
init()
{
   ::init();
   add_action("do_enter","enter");
}

int
do_enter(string str)
{
   
   if((!str) || (str != "hole") && (str != "pit") && (str != "pile"))
      {
      write("Enter what?\n");
      return 1;
   }
   
   if (oldtraproom)
      {
      TP->add_prop(TRAP_LAST_ROOM,environment(TO));
      TP->move_living("M",oldtraproom,1,0);
      tell_room(environment(TO),QCTNAME(TP)+ " leaves entering the hole.\n");
      return 1;
   }
   if(!traproom)
      {
      TP->add_prop(TRAP_LAST_ROOM,environment(TO));
      TP->move_living("M",get_trap_room(),1,0);
      tell_room(environment(TO),QCTNAME(TP)+ " leaves entering the hole.\n");
      return 1;
   }
   
   TP->add_prop(TRAP_LAST_ROOM,environment(TO));
   TP->move_living("M",traproom,1,0);
   tell_room(environment(TO),QCTNAME(TP)+ " leaves entering the hole.\n");
   return 1;
}
