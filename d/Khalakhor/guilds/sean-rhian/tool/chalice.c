//
// A chalice - used to hold honey mixed with water
//
// Zima 5/28/98
//
inherit "/std/container";
#include <stdproperties.h>
#include <macros.h>
#include </d/Khalakhor/sys/defs.h>
#include "defs.h"
#include "chalice.h"
#define  RM  ENV(TP)
#define  TPN QCTNAME(TP)
#define  CHAL_WT     300
#define  CHAL_MAX    100
 
int    amt;            // food or soft amt
int    contents;       // contents EMPTY, HONEY, DRINK, NECTAR
 
string clong="It is an ornate chalice made of gold, cast with small "+
             "shamrocks around the rim and three large interlocked "+
             "circles on the side. It has a thick short stem which "+
             "fans out to a base.\n";
 
void update_desc()
{
   string m;
   if (amt<=0) contents=CHAL_EMPTY;
   switch (contents)
      {
      case CHAL_EMPTY:
         m=""; break;
      case CHAL_HONEY:
         m=" It contains sweet sticky honey.\n"; break;
      case CHAL_HONEY_WATER:
         m=" It contains honey mixed with water.\n"; break;
      case CHAL_NECTAR:
         if      (amt==100) m="";
         else if (amt>=70)  m="almost ";
         else if (amt>=40)  m="about half ";
         else               m="about one quarter ";
         m=" It is "+m+"full of holy nectar.\n"; break;
         break;
      default: m=" It seems to be broken.\n";
      }
   if (contents==CHAL_EMPTY)
      {
      remove_prop(CONT_M_NO_INS);
      remove_prop(CONT_I_HIDDEN);
      }
   else
      {
      add_prop(CONT_I_HIDDEN,1);
      add_prop(CONT_M_NO_INS,"There is something in the "+short()+".");
      }
   set_long(clong+m);
}
 
int  query_amt()        { return amt;  }
int  query_contents()   { return contents; }
void set_amt(int i)     { amt=i;      update_desc(); }
void set_contents(int i){ contents=i; update_desc(); }
void add_honey()        { contents=CHAL_HONEY; amt=75; update_desc(); }
void add_water()        { contents=CHAL_HONEY_WATER; amt=100; update_desc();}
void consecrate()       { contents=CHAL_NECTAR; update_desc(); }
 
void create_container()
{
   set_name("chalice");
   add_name(SR_CHALICE);
   set_short("gold chalice");
   add_adj(({"ornate","gold"}));
   add_prop(CONT_I_RIGID,1);
   add_prop(CONT_I_MAX_WEIGHT,300);
   add_prop(CONT_I_MAX_VOLUME,200);
   add_prop(OBJ_I_VALUE,150);
   amt=contents=0;
   update_desc();
}
 
int do_eat(string cmd)
{
   object *inv=all_inventory(TP),ob;
   string sh=short();
   if (!stringp(cmd)) return 0;
   if ((!parse_command(cmd,inv,"[the] 'honey' 'from' / 'in' [the] %o",ob))
      ||(ob!=TO))
      return 0;
   if (contents==CHAL_EMPTY)
      write("There is no honey in the "+sh+".\n");
   else if (contents!=CHAL_HONEY)
      write("It is watered down. You must drink or sip from the chalice.\n");
   else if (!(TP->eat_food(amt)))
      write("The honey in the "+sh+" is too much for you to eat.\n");
   else
      {
      write("You eat the honey from the "+sh+".\n");
      tell_room(RM,TPN+" eats some honey from a "+sh+".\n",TP);
      contents=CHAL_EMPTY;
      amt=0;
      update_desc();
      }
   return 1;
}
 
int do_drink_sip(string cmd)
{
   object *inv=all_inventory(TP),ob;
   string sh=short(), verb=query_verb();
   int    ok=0, samt;
   string scont="honey mixed with water";
 
   if (!stringp(cmd)) return 0;
   if ((!parse_command(cmd,inv,
      "[the] [honey] [nectar] [from] [the] %o",ob))||(ob!=TO)) return 0;
   if (contents==CHAL_EMPTY)
      write("There is noting in the "+sh+".\n");
   else if (contents==CHAL_HONEY)
      write("The honey is too thick. You must eat the honey from "+
            "the chalice.\n");
   else ok=1;
   if (!ok) return 1;
 
   if (verb=="sip") samt=10; else samt=amt;
   if (samt>amt) samt=amt;
 
   else if (!(TP->drink_soft(amt)))
      write("You are to full to "+verb+" from the "+sh+".\n");
   else
      {
      if (contents==CHAL_NECTAR) scont="holy nectar";
      write("You "+verb+" "+scont+" from the "+sh+".\n");
      tell_room(RM,TPN+" "+verb+"s from the "+sh+".\n",TP);
      amt -= samt;
      if (amt<=0) contents=CHAL_EMPTY;
      update_desc();
      }
   return 1;
}
 
void init()
{
   ::init();
   add_action(&do_eat(),"eat");
   add_action(&do_drink_sip(),"sip");
   add_action(&do_drink_sip(),"drink");
}
