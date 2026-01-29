inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
object ob2;

/* by korat */
void
create_room()
{
   ::create_room();
   INSIDE;
   set_short("The entrance to the Duergar Clan.");
   set_long("This must be the old cellar of the temple, used "+
      "by the dewars as their hideout in this city. You have a "+
      "feeling that they will fiercely protect it against any "+
      "stranger that tries to continue through the door eastwards.\n");
   add_item("cellar","It is dark and uninviting, with "+
      "a stench drifting out from the cracks in the door.\n");
   add_item("door","The door looks old but still will "+
      "keep unwanted people outside since its construction of "+
      "oak and hinges of hard metal makes it into a solid object.\n");
   add_exit(CPASS(dwarf/duergar/d7),"up");
   set_noshow_obvious(1);
   clone_object("/d/Kalad/common/wild/pass/dwarf/door/door1")->MOVE(TO);
   set_alarm(1.0,0.0,"reset_room");
}
void
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(dwarf/npc/duergar));
      ob1->set_stats(({120,70,100,30,30,120}));
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(CPASS(dwarf/npc/duergar));
      ob2->set_stats(({120,70,100,30,30,120}));
      ob2 -> move_living("M",TO);
      tell_room(TO,"Some huge duergar guards comes scrambling into the "+
         "room.\n");
      ob1 -> team_join(ob2);
   }
}

int
guards()
{
   object *ob;
   int pres,i;
   ob = FILTER_LIVE(all_inventory(this_room()));
   pres = 0;
   for(i = 0; i < sizeof(ob); i++)
   {
      if(ob[i]->query_name() == "Duergar")
      {
         pres = 1;
       }
   }
   if(pres == 1 && TP->query_race() != "dwarf")
      {
      write("The duergar guard slashes out against you, but misses "+
         "by an inch!\n");
      say("The duergar guard slashes out after "+QCTNAME(TP)+", but "+
         "misses by an inch!\n");
   }
   if(pres != 1 || TP->query_race()=="dwarf")
      {
      write("You open the door and enter inside it.\n");
      say(QCTNAME(TP) + " opens the door and enter inside.\n");
   }
   return pres;
}
