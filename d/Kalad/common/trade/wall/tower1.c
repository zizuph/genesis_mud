inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"
#include "/sys/filter_funs.h"
int pres,i;
object *ob;
object ob1;
object ob2;

void
create_room()
{
   set_short("Guard Tower");
   set_long("You have entered the guard tower at the southeastern "
      +"corner of Kabal. The room you are in has the basic neccessities "
      +"for guard duty, a table, a deck of cards, and some chairs "
      +"to sit in. There is a window to the south, and a ladder "
      +"going up.\n");
   add_exit(TRADE(wall/tower2),"up");
   add_exit(TRADE(cliffside/cliff_turn),"northwest");
   add_item(({"table"}),"This is a plain wooden table, there are boot "
      +"marks on it. It apparently gets lots of use.\n");
   add_item(({"deck","cards","deck of cards"}),"This is a standard deck "
      +"of 52 cards. The edges "
      +"are bent from the use "
      +"they so frequently get.\n");
   add_item(({"chair","chairs"}),"These are plain chairs, that are old "
      +"and creaky, and look well used.\n");
   add_item(({"window"}),"It looks southward over the vast port district "
      +"and the ocean.\n");
   hear_bell = 2;
   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_NO_TIME_DESC,1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if (!ob1 || !ob2)
      {
      ob1 = clone_object("/d/Kalad/common/caravan/npc/kguard.c");
      ob1 -> arm_me();
      ob1 ->move_living("xxx", this_object());
      ob2 = clone_object("/d/Kalad/common/caravan/npc/kguard.c");
      ob2 -> arm_me();
      ob2 ->move_living("xxx", this_object());
      ob1->team_join(ob2);
   }
}
query_move()
{
   object *ob;
   int pres,i;
   ob = FILTER_LIVE(all_inventory(this_room()));
   pres = 0;
   for (i = 0; i < sizeof(ob); i++){
      if (ob[i]->query_name() == "Drew"){
         pres = 1;
        }
   }
   if (pres == 1){
      write("You are stopped by the kabal guard.\n");
      say("The kabal guard moves to block the way up.\n");
   }
   return pres;
}
