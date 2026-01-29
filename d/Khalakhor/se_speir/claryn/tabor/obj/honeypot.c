//
// A honeypot - an object which can "contain" honey from a beehive
//
// Zima 5/28/98
//
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include </d/Khalakhor/sys/defs.h>
#include "honey.h"
#define  RM  ENV(TP)
#define  TPN QCTNAME(TP)
#define  POT_WT   200
 
int    honey=0;   // is there honey in the pot?
string hlong="It is a honeypot made of clay used to hold a small "+
             "quantity of honey. ";
 
int  query_honey() { return honey;  }
void set_honey(int i)
{
   honey=i;
   if (honey)
      {
      set_long(hlong+"It is full of sticky sweet honey.\n");
      add_name("honey");
      add_prop(OBJ_I_WEIGHT,POT_WT+HONEY_AMT);
      add_prop(OBJ_I_VALUE,10);
      }
   else
      {
      set_long(hlong+"It is empty.\n");
      remove_name("honey");
      add_prop(OBJ_I_WEIGHT,POT_WT);
      add_prop(OBJ_I_VALUE,5);
      }
}
 
void create_object()
{
   set_name("honeypot");
   add_name(({"pot",HONEYPOT}));
   set_short("small honeypot");
   add_adj(({"small","clay"}));
   add_prop(OBJ_I_VOLUME,150);
   set_honey(0);
}
 
int do_eat(string cmd)
{
   object *inv=all_inventory(TP);
   string sh=short();
   if (!stringp(cmd)) return 0;
   if (!parse_command(cmd,inv,"'honey' [from] [pot] [honeypot]")) return 0;
   if (!honey)
      {
      notify_fail("The "+sh+" is empty.\n");
      return 0;
      }
   if (TP->eat_food(HONEY_AMT))
      {
      write("You eat the honey from the "+sh+".\n");
      tell_room(RM,TPN+" eats some honey from a "+sh+".\n",TP);
      set_honey(0);
      }
   else
      write("You seem unable to eat the honey.\n");
   return 1;
}

void init() 
{
   ::init();
   add_action(&do_eat(),"eat");
}
