//
// A honeycomb - taken from a bee hive
// Player can suck honey off it for food, and use wax to make candles
//
// Zima 5/19/98
//
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/guilds/sean-rhian/defs.h"
#include "/d/Khalakhor/guilds/sean-rhian/tool/chalice.h"
#include "honey.h"
#define  TPN QCTNAME(TP)
#define  RM  ENV(TP)
 
int honey; // is there honey in this comb?
 
public int  query_honey() { return honey; }
 
//
// set_comb - set the descriptions of the comb
//
public void set_comb(int h)
{
   string longd="It is a honeycomb taken from the hive of honeybees. "+
                "Made of beeswax, it is constructed of many small "+
                "octagonal pockets. ";
   honey=h;
   if (honey)
      {
      add_name("honey");
      set_adj(({"sticky","sweet"}));
      remove_adj("dry");
      set_short("sticky honeycomb");
      set_long(longd+"It is saturated with sweet sticky honey. You could "+
               "probably suck the honey from it, or squeeze it into "+
               "something.\n");
      add_prop(OBJ_I_WEIGHT,300);
      add_prop(OBJ_I_VOLUME,500);
      add_prop(OBJ_I_VALUE,6);
      }
   else
      {
      remove_name("honey");
      remove_adj(({"sticky","sweet"}));
      add_adj("dry");
      set_short("dry honeycomb");
      set_long(longd+"There is no honey in it so its just a comb of "+
                     "of beeswax.\n");
      add_prop(OBJ_I_WEIGHT,200);
      add_prop(OBJ_I_VOLUME,400);
      add_prop(OBJ_I_VALUE,1);
      }
}
 
//
// create_object()
//
void create_object()
{
    set_name("honeycomb");
    add_name("_beeswax_honeycomb");
    add_name(({"wax","beeswax","comb","_bk_honeycomb"}));
    set_adj("honey");
    set_comb(1);
}
 
//
// do_eat - allow the player to attempt to eat the honeycomb
//
int do_eat(string cmd)
{
   notify_fail("Eat what? The honeycomb?\n");
   if (!stringp(cmd)) return 0;
   if (!parse_command(cmd,all_inventory(TP),"'honeycomb' / 'comb' / 'honey'"))
      return 0;
   if (ENV(TO)!=TP)
      {
      notify_fail("You do not have the honeycomb in your possession.");
      return 0;
      }
   write("You wouldn't want to do that, all that wax would clog up "+
         "your stomach!\n");
   if (honey)
      write("You could probably suck the honey off it, or squeeze it "+
            "into something though.\n");
   return 1;
}
 
//
// do_suck - allow player to suck the honey off the honeycomb
//
int do_suck(string cmd)
{
   object *inv=all_inventory(TP);
 
   notify_fail("Suck what? Honey off the honeycomb?\n");
   if (!stringp(cmd)) return 0;
   if (!parse_command(cmd,inv,"'honeycomb' / 'comb' / 'honey' %s"))
      return 0;
   if (ENV(TO)!=TP)
      {
      notify_fail("You do not have the honeycomb in your possession.");
      return 0;
      }
   if (honey)
      if (TP->eat_food(HONEY_AMT))
         {
         write("You suck the sweet sticky honey from the comb.\n");
         tell_room(RM,TPN+" sucks the honey from a honeycomb.\n",TP);
         set_comb(0);
         }
      else
         write("You are too full to suck any honey from the comb.\n");
   else
      {
      notify_fail("There is no honey left on the comb.\n");
      return 0;
      }
   return 1;
}
 
//
// check_receptacle
//
int check_receptacle(object ob)
{
   string obs=(ob->short());
   object *inv;
   if (ob->id(HONEYPOT))
      if (ob->query_honey())
         write("The "+obs+" is full.\n");
      else
         {
         ob->set_honey(1);
         return 1;
         }
   else if (ob->id(SR_CHALICE))
      {
         inv=(ob->subinventory());
         if ((sizeof(inv)>0)||((ob->query_contents()) != CHAL_EMPTY))
            write("The "+obs+" is not empty.\n");
         else
            {
            ob->add_honey();
            return 1;
            }
      }
   else
      write("The "+obs+" is not a proper receptacle for the honey.\n");
   return 0;
}
 
//
// squeeze - allow player to squeeze honey into a honeypot
//
int do_squeeze(string cmd)
{
   object *inv=all_inventory(TP), ob;
   string obs;
 
   notify_fail("Squeeze what? the honeycomb?\n");
   if (!stringp(cmd)) return 0;
   if (!parse_command(cmd,inv,"'honey' / 'honeycomb' / 'comb' %s")) return 0;
   if (ENV(TO)!=TP)
      {
      notify_fail("You do not have the honeycomb in your possession.");
      return 0;
      }
 
   if (!honey)
      {
      notify_fail("There is no honey left on the comb.\n");
      return 0;
      }
 
   if (parse_command(cmd,inv,"'honeycomb' / 'comb'"))
      {
      write("You squeeze the honeycomb, dripping the honey on the ground.\n");
      tell_room(RM,TPN+" squeezes a honeycomb dripping the honey on the "+
                       "ground.\n",TP);
      set_comb(0);
      }
   else if (parse_command(cmd,inv,
      "'honey' / 'honeycomb' / 'comb' 'into' / 'in' %o",ob))
      {
      if (check_receptacle(ob))
         {
         obs=(ob->short());
         write("You squeeze the honey from a honeycomb into the "+obs+".\n");
         tell_room(RM,TPN+" squeezes honey from a honeycomb into a "+obs+
                          ".\n",TP);
         set_comb(0);
         }
      }
   else
      {
      notify_fail("Squeeze honeycomb into what?\n");
      return 0;
      }
   return 1;
}
 
//
// init - add actions
//
void init() {
   ::init();
   add_action(&do_eat(),"eat");
   add_action(&do_suck(),"suck");
   add_action(&do_squeeze(),"squeeze");
}
