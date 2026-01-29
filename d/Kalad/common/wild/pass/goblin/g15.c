inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define GG "/d/Kalad/common/wild/pass/npc/gob_guard"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Entrance to dungeon cell");
   set_long("This small square chamber doesn't smell quite as bad as the "+
      "one to the south, and at least there aren't standing pools of murky "+
      "liquid. What is in this room is a group of small boulders and a "+
      "ladder in the room's center, leading down through a hole there.\n");
   add_item(({"small square chamber","small chamber","square chamber","chamber"}),
      "Its what you are currently inside.\n");
   add_item(({"group of small boulders","small boulders","boulders","boulder"}),
      "Small in size and strangely smooth to the touch, it looks as if "+
      "they are used as seats, which might explain their relatively smooth "+
      "surface. The three boulders have been arranged in a half circle around "+
      "the ladder, facing to the south.\n");
   add_item(({"hole"}),"A dark opening in the floor.\n");
   add_item(({"floor"}),"The bare rock of the ground is littered with "+
      "gnawed bones.\n");
   add_item(({"gnawed bones","bones","bone"}),"It looks like the "+
      "remnants of a humanoid creature.\n");
   add_item(({"ladder"}),"A rickety wooden ladder, it looks quite unstable. "+
      "It looks to be the only way down.\n");
   add_exit(CPASS(goblin/g16),"west",0,1,2);
   add_exit(CPASS(goblin/g12),"south",0,1,2);
   add_exit(CPASS(goblin/jail_cell),"down","@@query_move",1,2);
   set_alarm(1.0,0.0,"reset_room");
   set_alarm(10.0,60.0,"stinky");
}

int
block()
{
    write("This way is closed now, but soon will be open!\n");
    return 1;
}

void
init()
{
   ::init();
   AA(sit,sit);
}
int
sit(string s)
{
   if(!s || s != "down")
      {
      NF("Sit where? Down perhaps?\n");
      return 0;
   }
   write("You sit down on a boulder. Thump!\n");
   say(QCTNAME(TP) + " sits down on a boulder. Thump!\n");
   return 1;
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(GG);
      ob1 -> move_living("xxx",TO);
   }
}
stinky()
{
   tell_room(TO,"A putrid odor wafts from the south.\n");
   return 1;
}
query_move()
{
   object *ob;
   int pres,i;
   ob = FILTER_LIVE(all_inventory(this_room()));
   pres = 0;
   for(i = 0; i < sizeof(ob); i++){
      if(ob[i]->query_name() == "Goblin"){
         pres = 1;
       }
   }
   if(pres == 1){
      write("The goblin stops you from going down the ladder.\n");
      say("The goblin stops " + QCTNAME(TP) + " from going down the ladder.\n");
   }
   return pres;
}
