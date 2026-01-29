#include <filter_funs.h>
#define QUEST_NAME "firequest"

enter_inv(object ob,object from)
{
   object *inv;
   if (ob->query_npc())
      {
      ::enter_inv(ob,from);
      return;
   }
   inv = all_inventory();
   inv=FILTER_PLAYERS(inv);
   if (sizeof(inv)==1)
      {
      ::enter_inv(ob,from);
      set_alarm(0.0,0.0,"reset_variables");
      return;
   }
   /* someone already here! */
   if (living(ob))
      {
      ob->catch_msg("There is already someone there!\n");
      ob->catch_msg("In the panic you decide to get out of here fast!\n");
      ob->move(from);
   }
   tell_room(TO,"The "+ob->short()+" hurridly leaves back through the window.\n");
   tell_room(WALL_ROOM,"Suddenly "+ob->short()+" comes crawling back through the window.\n");
   ob->move(WALL_ROOM);
}


