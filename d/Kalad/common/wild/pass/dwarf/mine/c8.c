inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object shred;
int opened;
/* by korat */
create_room()
{
   ::create_room();
   INSIDE;
   DIRTY(2);
   add_prop(ROOM_I_LIGHT,0);
   set_short("Within some cave close to Underhome");
   set_long("This cave is natural, being excavated in the "+
      "hard rock by flowing water. It is huge and formed like a "+
      "vaulted dome with a large stone sarcophagus placed in the middle."+
      "Large stalagmites and stalactites covers the cave on the "+
      "floor and ceiling. Small drops of water drips down from "+
      "them as it has done for hundreds of years. The air is cold "+
      "and filled with moisture. It must be a burrial site, long "+
      "forgotten by any living creature. The only exit is to the south.\n");
   add_item("sarcophagus","The sarcophagus is placed in the center "+
      "of this cave, @@coffin@@.\n"); 
  add_item(({"stalagmite","stalagmites","stalactite","stalactites"}),
      "The stalactites is shaped like icicles, hanging from the "+
      "roof of the cave in different lenghts. Just like the stalactites "+
      "the stalagmites are formed from the dripping of water saturated "+
      "with calcium, but stands on the floor like small cone-formed towers.\n");

   add_exit(CPASS(dwarf/mine/c7),"south",0,3);

   set_noshow_obvious(1);
   set_alarm(0.0,0.0,"reset_room");
}
coffin()
{
   if(opened)
      return "but it is empty with the lid lying cracked on "+
      "the side";
   return "and looks untouched with a large stone-lid covering it";
}
init()
{
   ::init();
   add_action("push","push");
}
push(string str)
{
   notify_fail("Push what?\n");
   if(!str || str!="lid") return 0;
   notify_fail("But it is already open!\n");
   if(opened) return 0;
   write("You push on the lid.\n");
   if(TP->query_base_stat(SS_STR) < 50)
   {
      write("You cannot open it! The lid is too heavy for "+
         "you to push it off.\n");
      say(QCTNAME(TP)+" tries to push the lid off, but failes.\n");
      return 1;
   }
   opened=1;
   write("You push the lid off the sarcophagus.\n");
   say(QCTNAME(TP)+" pushes the lid off the sarcophagus.\n");
   tell_room(TO,"The lid falls to the floor with a crush, and cracks into "+
      "large pieces.\n");
   write("Inside the sarcophagus you see a small shred of stone lying on top "+
      "of a human skeleton. You pick it up with a puzzled look on your "+
      "face. The skeleton turns to dust as you by accident touched it.\n");
   say(QCTNAME(TP)+" bends over and picks up something from the sarcophagus. "+
      capitalize(TP->query_pronoun())+" gets a puzzled look.\n");
   shred=clone_object(CPASS(dwarf/obj/quest_shred));
   shred->move(TP);
   return 1;
}
reset_room()
{
   opened = 0;
}
