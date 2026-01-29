/* Vial for holding holy water
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 2/10/98     Zima        Created
**
*/
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "hwvial.h"
#include "powder.h"
 
int       amt=0;
int       isholy=0;
 
/*
** init_vial - initialize it empty
*/
void init_vial() 
{
   isholy = 0;
   amt    = 0;
   add_adj("empty");
   set_short("small empty glass vial");
   set_long("It is a small empty glass vial.\n");
   add_prop(OBJ_I_WEIGHT,VIAL_WEIGHT);
}
 
/*
** object creation
*/
void create_object() 
{
   set_name("vial");
   add_name(SR_HWVIAL);
   set_adj(({"small","glass"}));
   add_prop(OBJ_I_VOLUME,VIAL_WEIGHT+FULL_AMT);
   add_prop(OBJ_I_VALUE,1);
   init_vial();
}

/*
** query_hwater_code - determines info about availability of [h]water in rm
*/
int query_hwater_code(object room) 
{
   switch (room->query_prop(OBJ_I_CONTAIN_WATER)) {
      case 0: /* no water prop, check terrain type */
         if ((room->query_prop(ROOM_I_TERRAIN_TYPE))==TERRAIN_FRESHWTR)
            return WATER_HERE;
         else
            return NO_WATER_HERE;
      case HWATER_PROP_NUM:  /* water prop indicates hwater present */
         return HOLY_WATER_HERE;
      default:               /* just regular water present */
         return WATER_HERE;
   }
}
 
/*
** update_desc - updates descriptions/props when water changes
*/
void update_desc() 
{
   string desc,adj="";
 
   /* check for empty */
   if (amt<=0) { init_vial(); return; }
   if (isholy) adj="holy ";
   desc="It is a small glass vial of "+adj+"water.\n";
 
   /* determine desc of amount */
   if      (amt==FULL_AMT)     desc=desc+"It is full.\n";
   else if (amt<(FULL_AMT/4))  desc=desc+"It is almost empty.\n";
   else if (amt<(FULL_AMT/2))  desc=desc+"It is less than half full.\n";
   else if (amt==(FULL_AMT/2)) desc=desc+"It is half full.\n";
   else                        desc=desc+"It is more than half full.\n";
 
   set_long(desc);
   set_short("small glass vial of "+adj+"water");
   remove_adj("empty");
   add_prop(OBJ_I_WEIGHT,VIAL_WEIGHT+amt);
}
 
/*
** small query/set functions
*/
int  query_holy()        { return isholy; }
int  query_amt()         { return amt;    }
int  full() 			 { return (amt>=FULL_AMT); }
int  empty()			 { return (amt<=0); }
void set_holy(int i)     { isholy = i;    }
void set_amount(int i)   { amt=i; update_desc(); }
 
/*
** fill - allows player to fill vial with water if available in room
*/
int fill(string cmd) 
{
   object room=ENV(TP);
   string adj="";
 
   if ((!stringp(cmd)) ||
      (!parse_command(cmd,all_inventory(TP),"'vial' 'with' [holy] 'water'"))){
      NF("Fill vial with what?\n");
      return 0;
   }
   switch (query_hwater_code(room)) {
      case NO_WATER_HERE:
         NF("There is no water here you can use to fill it with.\n");
         return 0;
      case HOLY_WATER_HERE:
         isholy=1;
         adj="holy ";
      case WATER_HERE:
         write("You fill the "+query_short()+" with "+adj+"water.\n");
         tell_room(room,QCTNAME(TP)+" fills a vial with "+adj+"water.\n",TP);
         amt=FULL_AMT;
         update_desc();
   }
   return 1;
}
 
/*
** check_effect - what is the effect of being sprinkled?
*/
void check_effect(object targ, object room) 
{
   object powder;
 
   if (!isholy) return;
   /* check for turning ground powder to incense in mortar */
   if (targ->id("mortar")) {
      if (objectp(powder=present(GROUNDED_POWDER,targ)))
         if (powder->convert(POWDER_INCENSE1)) {
         tell_room(room,"There is a loud pop and a ball of smoke rises "+
                        "from the "+(targ->query_short())+".\n");
         return;
      }
   }
}
 
/*
** sprinkle - allows player to sprinkle holy water on something
*/
int sprinkle(string cmd) 
{
   string adj="";
   object room=ENV(TP),targ;
   int    OK=0;
 
   /* no sprinkle if empty */
   if (isholy) adj="holy ";
   if (amt<=0) {
      NF("The "+query_short()+" is empty.\n");
      return 0;
   }
 
   /* if no parms, just sprinkle all around */
   if (!stringp(cmd)) {
      write("You sprinkle "+adj+"water all around.\n");
      tell_room(room,QCTNAME(TP)+" sprinkles "+adj+"water all around.\n",TP);
      amt -= SPRINKLE_AMT;
      update_desc();
      return 1;
   }
 
   /* check cmd for sprinkling something in player inv or room */
   if (parse_command(cmd,all_inventory(room),"%o 'with' [holy] 'water'",targ))
      OK=2; /* found object in player's environment */
   if ((!OK)&&
      (parse_command(cmd,all_inventory(TP),"%o 'with' [holy] 'water'",targ)))
      OK=1; /* found object in player's inventory */
   if (!OK) {
      NF("Sprinkle what or whom with "+adj+"water?\n");
      return 0;
   }
 
   /* update vial amount */
   amt -= SPRINKLE_AMT;
   update_desc();
 
   /* write messages */
   if (living(targ))
      {
      TP->catch_msg("You sprinkle "+QTNAME(targ)+" with "+adj+"water.\n");
      tell_room(room,QCTNAME(TP)+" sprinkles "+QTNAME(targ)+" with "+
                 adj+"water.\n",TP);
      }
   else
      {
      write("You sprinkle the "+(targ->query_short())+" with "+adj+"water.\n");
      if (OK==1) /* in player inventory */
         tell_room(room,QCTNAME(TP)+" sprinkles "+HIS_HER(TP)+" "+
            (targ->query_short())+" with "+adj+"water.\n",TP);
      else /* in room */
         tell_room(room,QCTNAME(TP)+" sprinkles the "+(targ->query_short())+
            " with "+adj+"water.\n",TP);
      }
   check_effect(targ,room);
   return 1;
}
 
/*
** init - add sprinkle and fill commands
*/
void init() 
{
   ::init();
   add_action(&sprinkle(),"sprinkle");
   add_action(&fill(),"fill");
}
