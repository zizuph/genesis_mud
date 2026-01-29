/* Flask of oil, to which a ground herbal powder can be added, and then
** blessed; used to make holy oils for various spells.
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 2/10/98     Zima        Created
** 6/24/98     Zima        Added beatha oil
**
*/
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include "defs.h"
#include "powder.h"
#include "oils.h"
 
int    amt=0;
int    oilid=0;
string adj1,adj2;
// adjectives for oils, index matches unblessed oil id num
mixed* oildesc = 
   (({
    ({"unknown","strange","unknown"}),
    ({"whale","light","smelly"}),
    ({"lilac","perfumed","lavendar"}),
    ({"honeysuckle","perfumed","pink"}), 
    ({"honey","thick","sweet"}),
    ({"uaine pine","dark","pine-scented"}),
    ({"saltpeter","red","crystalizing"}),
    ({"beatha","thick","red"})
   }));
string stdlong="It is a cylindrical glass flask with a small round "+
               "neck on its top. ";
 
/*
** init_flask - initialize it empty
*/
void init_flask() {
   amt   = 0;
   oilid = 0;
   adj1  = "";
   adj2  = "";
   remove_name("oil");
   remove_adj(query_adj(1));
   set_adj(({"oil","glass","empty"}));
   set_short("empty oil flask");
   set_pshort("empty oil flasks");
   set_long(stdlong+"It is used exclusively for holding special oils "+
                    "for anointing. It is empty.\n");
}
 
/*
** object creation
*/
void create_object() {
   set_name("flask");
   add_name(SR_FLASK);
   add_prop(OBJ_I_VOLUME,600);
   add_prop(OBJ_I_WEIGHT,700);
   add_prop(OBJ_I_VALUE,50);
   init_flask();
}
 
/*
** set_oil_adj - set 2 primary oil adjective acc. to oil type.
*/
void set_oil_adj()
{
   int descid=oilid;
   if (descid>=FIRST_BL_OIL) descid = oilid-BL_OFFSET;  //blessed same as not
   if ((descid<FIRST_OIL)||(descid>LAST_OIL)) descid=0; //range check
   adj1=oildesc[descid][1];
   adj2=oildesc[descid][2];
}
 
/*
** update_desc - updates descriptions/props when oil changes
*/
void update_desc() {
   string  longd=stdlong;
 
   /* determine desc of amount */
   switch (amt) {
      case 1: longd+="It contains a small amount of ";          break;
      case 2: longd+="It is less than half full of ";           break;
      case 3: longd+="It is half full of ";                     break;
      case 4: longd+="It more than half full of ";              break;
      case 5: longd+="It is full of ";                          break;
      default: init_flask(); return;
   }
   set_oil_adj();
   add_name("oil");
   longd += LANG_ART(adj1) + " " + adj1 + " " + adj2 +
            " oil which is used in anointings.\n";
   set_long(longd);
   remove_adj("empty");
   add_adj(({adj1,adj2}));
   set_short("flask of "+adj1+" "+adj2+" oil");
   set_pshort("flasks of "+adj1+" "+adj2+" oil");
}
 
/*
** small query/set functions
*/
int  query_blessed()     { if (oilid>=FIRST_BL_OIL) return 1; else return 0;}
int  query_oilid()       { return oilid;  }
int  query_amt()         { return amt;    }
void set_oilid(int i) {
   if (((i>=FIRST_OIL)&&(i<=LAST_OIL))||((i>=FIRST_BL_OIL)&&(i<=LAST_BL_OIL)))
      oilid=i;
   update_desc();
}
void set_amt(int newamt) {
   if ((newamt>=0)&&(newamt<=5)) amt=newamt;
   update_desc();
}
void set_blessed() {
   if ((oilid>=FIRST_OIL)&&(oilid<=LAST_OIL)) oilid+=BL_OFFSET;
}
 
/*
** anoint - allows player to anoint something/someone with oil
*/
int anoint(string cmd) {
   string flask=(TO->query_short()), obshort;
   object rm=ENV(TP),ob;
 
   // make sure player tries to anoint something
   if (!stringp(cmd)) {
      write("Anoint who or what with oil?\n");
      return 1;
   }
 
   // make sure there is some oil left!
   if (amt<=0) 
   {
      TP->catch_msg("The "+flask+" is empty.\n");
      return 1;
   }
 
   // see if anointing ground
   if (parse_command(cmd,(({all_inventory(TP)})),"'ground' [with] [oil]"))
      {
      write("You anoint the ground with the "+adj1+" "+adj2+" oil.\n");
      tell_room(rm,QCTNAME(TP)+" anoints the ground with oil.\n",TP);
      ob=rm;
      }
 
   // see if self
   else if (parse_command(cmd,all_inventory(TP),"'myself' / 'self' [with] [oil]"))
      {
      write("You anoint yourself with the "+adj1+" "+adj2+" oil.\n");
      tell_room(rm,QCTNAME(TP)+" anoints "+HIM_HER(TP)+"self with oil.\n",TP);
      ob=TP;
      }
 
   // see if anointing something in room
   else if (parse_command(cmd,all_inventory(rm),"%o [with] [oil]",ob))
      {
      if (ob==TP) { write("Anoint yourself with oil?\n"); return 1; }
      obshort = (ob->short());
      if (ob->query_prop(LIVE_I_IS))
         {
         TP->catch_msg("You anoint "+QTNAME(ob)+" with the "+adj1+" "+adj2+
                       " oil.\n");
         if (!(ob->query_npc()))
            ob->catch_msg(QCTNAME(TP)+" anoints you with a "+adj1+" "+
                                      adj2+" oil.\n");
         tell_room(rm,QCTNAME(TP)+" anoints "+QTNAME(ob)+" with oil.\n",
                      ({TP,ob}));
         }
      else //non-living
         {
         TP->catch_msg("You anoint the "+obshort+" with the "+adj1+" "+adj2+
                       " oil.\n");
         tell_room(rm,QCTNAME(TP)+" anoints the "+obshort+" with oil.\n",TP);
         }
      }
 
   // see if anointing something in inventory
   else if (parse_command(cmd,all_inventory(TP),"%o [with] [oil]",ob))
      {
      obshort = (ob->short());
      TP->catch_msg("You anoint the "+obshort+" with the "+adj1+" "+adj2+
                       " oil.\n");
      tell_room(rm,QCTNAME(TP)+" anoints "+HIS_HER(TP)+" "+obshort+
                   " with oil.\n",TP);
      }
   else
      {
      write("Anoint who or what with oil?\n");
      return 1;
      }
 
   // anoint successful, do the effects
   ob->add_prop(SR_OIL_ANOINTED,oilid);
   amt--;
   update_desc();
   return 1;
}
 
/*
** addable_powder - checks a ground powder of 1 ingredient to see if
**                  that ingredient is OK to add. returns oilid of
**                  resulting oil if OK, 0 otherwise
*/
int addable_powder(object powder)
{
   string* inglist = (powder->query_ingredients());
   int i;
   for (i=FIRST_OIL; i<=LAST_OIL; i++)
      if (oildesc[i][0] == inglist[0])
         return i;
   return 0;
}
 
/*
** add - allows player to add a powder to the oil
*/
int do_add(string cmd) {
   object ob;
   string obshort;
   int    newoilid;
 
   notify_fail("Add what to the flask of oil?\n");
   if (!stringp(cmd)) return 0;
   if (!parse_command(cmd,all_inventory(TP),"%s 'flask' / 'oil' %s"))
      return 0;
   if (!parse_command(cmd,all_inventory(TP),
      "%o 'to' [the] 'flask' [of] [oil]",ob))
      return 0;
 
   obshort = (ob->query_short());
 
   if (amt<=0)
      write("There is no oil in the flask.\n");
   else if (TP->query_skill(SS_ALCHEMY) < OIL_ALCHEMY_ADD_MIN)
      {
      write("You attempt to add the "+obshort+" into the oil but "+
            "spill it on the ground!\n");
      tell_room(ENV(TP),QCTNAME(TP)+" spills a flask of oil on the "+
                        "ground.\n",TP);
      init_flask();
      return 1;
      }
   else if (oilid >= FIRST_BL_OIL)
      write("The flask of oil has been blessed, nothing may be added.\n");
   else if (oilid!=WHALE_OIL)
      write("Something has already been added to the flask of oil.\n");
   else if (!(ob->id(GROUNDED_POWDER)))
      write("Only a ground powder may be added to the flask of oil.\n");
   else if (sizeof(ob->query_ingredients())!=1)
      write("Only a pure ground powder may be added to the flask of oil.\n");
   else if (!(newoilid=addable_powder(ob)))
      write("That powder may not be added to the flask of oil.\n");
   else
      {
      write("You add a "+obshort+" to the flask of oil and swirl it around "+
            "slowly.\n");
      write("The "+obshort+" slowly dissolves in the oil, changing its "+
            "nature.\n");
      tell_room(ENV(TP),QCTNAME(TP)+" adds a "+obshort+" to a "+
                       (query_short())+" and swirls it around slowly.\n",TP);
      ob->remove_object();
      set_oilid(newoilid);
      }
   return 1;
}
 
/*
** init - add anoint command
*/
void init() {
   ::init();
   add_action(&anoint(),"anoint");
   add_action(&do_add(),"add");
}
