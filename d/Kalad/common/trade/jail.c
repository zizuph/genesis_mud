inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   hear_bell = 1;
   set_short("Inside the Kabal Jail");
   set_long("You are in jail. It looks to be heavily frequented, judging by the "+
      "lack of dust and the closed door in the west. You must have commited "+
      "a horrible crime to have been placed here.\n");
   add_item(({"dust"}),"The dust is very thick here, covering everything.\n");
   add_exit(TRADE(tsquare/c3),"west","@@query_move",-1,-1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(TRADE(npc/sheriff_captain));
      ob1 -> arm_me();
      ob1 -> move_living("xxx",TO);
   }
}
 
int
query_move()
{
   object *ob;
   int pres, i, j;
   string text;
 
   ob = FILTER_LIVE(all_inventory(this_room()));
   pres = 0;
   for (i = 0; i < sizeof(ob); i++)
   {
      if (ob[i]->query_name() == "Keldain")
         pres = 1;
   }
 
    if (!(pres))
        return 0;
 
    object jail_object = present("_jail_object", TP);
 
    if (jail_object)
    {
        write("The sheriff refuses to allow you to leave.\n");
        say("The sheriff refused to allow " +
            QTNAME(TP) + " from leaving.\n");
 
    j = jail_object->query_time_left();
 
    switch (j)
    {
        case 1..60:
        {
            text = " is just a few seconds before you may leave";
            break;
        }
        case 61..300:
        {
            text = " is just a little while before I can let you go";
            break;
        }
        case 301..1200:
        {
            text = " will take quite a while before I will allow you to leave";
            break;
        }
        return 0; // Should not happen
    }
 
        present("sheriff-captain", TO)->command("say It" +
            text+".\n");
        return 1;
    }
    present("sheriff-captain", TO)->command("say Ok, behave " +
        "now so I won't see you here again.\n");
    return 0;
}
 
void
enter_inv(object player, object ob)
{
 
    ::enter_inv();
 
    object jailob = clone_object(TRADE (obj/jail_time_left));
    jailob->move(player, 1);
}
