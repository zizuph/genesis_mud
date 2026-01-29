#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"

inherit THWIL_BASE_ROOM;

object boar, boar1;

void
reset_room()
{
  /*
   if(!objectp(boar))
      {
      boar = clone_object(CARISCA + "monster/bore1");
      boar->set_short("dirty smelling pig");
      boar->set_name("pig"); 
      boar->remove_adj("wild");
      boar->set_adj("dirty");
      boar->set_long("This is a tame dirty pig. "+
         "Having a second look at the pigs grim teeth "+
         "you hold it for true that some boar blood still "+
         "fleets in the pig's veins. \n");
      boar->set_race_name("pig");
      boar->set_hp(100);
      boar->set_alignment(0);
      boar->move(TO);
   }
   if(!objectp(boar1))
      {
      boar1 = clone_object(CARISCA + "monster/bore2");
      boar1->set_short("tame confused pig");
      boar1->remove_adj("wild");
      boar1->set_name("pig"); 
      boar1->set_adj("tame");
      boar1->set_long("This is a tame confused pig. "+
         "Having a second look at the pigs grim teeth "+
         "you hold it for true that some boar blood still "+
         "fleets in the pig's veins. \n");
      boar1->set_race_name("pig");
      boar1->set_hp(50);
      boar1->set_alignment(0);
      boar1->move(TO);
   }
  */
}

void create_thwil_room()
{
   set_short("Street");
   set_long("The street is bustling with activity. Just beside the door, "+
      "on the left of the eastern building a sign is nailed. "+
      "To the north and south the street continues flanked by "+
      "the cozy homes of Thwil's citizens. \n");
   
   add_item("sign","It's a nice sign, why don't you try to read it?\n");
   add_cmd_item("sign","read","@@rd_fun");
   add_exit(THWIL + "ta" , "north" , 0);
   add_exit(THWIL + "shop" , "east" , 0);
   add_exit(THWIL + "t1", "south",0);
   STREET;
   reset_room();   
}

int
rd_fun()
{
   say(QCTNAME(TP) + " scratches his head in vain when reading the "+
      "letters on the sign.\n");
   TP->catch_msg("                Thwil general store! \n"+
      "We have all the things necessary for a decent living. \n");
   return 1;
}

