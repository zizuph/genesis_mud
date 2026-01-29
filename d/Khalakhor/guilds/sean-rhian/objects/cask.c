/* Cask of oil, used to reserve plain unblessed oil over reboots.
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 4/25/98     Zima        Created
**
*/
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "defs.h"
#include "oils.h"
#define  FULL_AMT       500
#define  AMT_PER_FLASK  5
#define  CASK_FILE      SR_OBJ+"cask.dat"
#define  OIL            "light-green oil"
 
int amt=0;
 
//
// set_desc - sets the description of the cask acc. to amt
//
void set_desc() {
   int perc = (amt*10) / FULL_AMT;
   string desc =
   "It is a large wooden cask made like a barrel used to hold a special "+
   "type of oil. It has no lid, allowing oil to be poured into it, and "+
   "has a spiggot near the bottom from which a flask with a special "+
   "spout can be filled with oil. ";
 
   if (amt<=0) perc=-1;
   switch (perc) {
      case -1:desc += "It is empty";   break;
      case 0: desc += "There is a little "+OIL+" in the bottom, but it is "+
                       "almost empty";
                       break;
      case 1: desc += "There is a little "+OIL+" left  in the bottom"; break;
      case 2: desc += "It is about one quarter full of "+OIL;          break;
      case 3: desc += "It is about one third full of "+OIL;            break;
      case 4: desc += "It is a little less than half full of "+OIL;    break;
      case 5: desc += "It is about half full of "+OIL;                 break;
      case 6: desc += "It is about two thirds full of "+OIL;           break;
      case 7: desc += "It is about three quarters full of "+OIL;       break;
      case 8: desc += "It is almost full of "+OIL;                     break;
      case 9: desc += "It is almost completely full of "+OIL;          break;
      case 10:desc += "It is brimming with "+OIL;                      break;
   }
   desc += ".\n";
   set_long(desc);
}
 
//
// read/write_cask_amt - read/write amount of oil in cask from/to file
//
void write_cask_amt() {
   seteuid(getuid());
   rm(CASK_FILE);
   write_file(CASK_FILE,"*** This file is a data file for the cask.c object\n");
   write_file(CASK_FILE,"*** # below read/written as amt of oil in cask\n");
   write_file(CASK_FILE,""+amt+"\n");
}
void read_cask_amt() {
   string samt;
   samt = read_file(CASK_FILE,3,1); //first 2 lines are comments
   if (stringp(samt))
      amt = atoi(samt);
   write_cask_amt();
}
int  query_cask_amt() { return amt; }
void set_cask_amt(int i) {
   if (i<0) i=0;
   if (i>FULL_AMT) i=FULL_AMT;
   amt = i;
   set_desc();
   write_cask_amt();
}
 
//
// fill - allows player to "fill flask with oil"
//
int fill(string cmd) {
   object flask;
   string fshort;
   int    flaskamt, qtytofill;
 
   //make sure player identifies what to fill with what.
   notify_fail("Fill what with what?\n");
   if (!stringp(cmd)) return 0;
   if (!parse_command(cmd,all_inventory(TP),"%o 'with' 'oil'",flask))
      return 0;
   fshort   = (flask->query_short());
   flaskamt = (flask->query_amt());
 
   //check if cask is empty
   if (amt==0)
      write("The cask it empty.\n");
 
   //check if the flask is the right kind
   else if (!(flask->id(SR_FLASK)))
      write("The "+fshort+" may not be used to hold this special oil.\n");
 
   //check if the oil in the flask matches that in the cask
   else if ((flaskamt) && ((flask->query_oilid())!=OLIVE_OIL))
      write("The oil in the "+fshort+" can not be mixed with oil from "+
            "the cask.\n");
 
   //check if the flask is already full
   else if (flaskamt==AMT_PER_FLASK)
      write("The "+fshort+" is already full.\n");
 
   //all is OK, go ahead and fill the flask
   else
      {
      qtytofill = AMT_PER_FLASK - flaskamt;
      if (qtytofill>amt) qtytofill = amt;
      flask->set_amt((flaskamt+qtytofill));
      flask->set_oilid(OLIVE_OIL); //actually plain unblessed whale oil
      set_cask_amt(amt-qtytofill);
      write("You fill the "+fshort+" with oil from the cask.\n");
      tell_room(ENV(TO),QCTNAME(TP)+" fills a "+fshort+" with oil from "+
                        "the cask.\n", TP);
      }
 
   return 1;
}
 
//
// pour - allows player to pour oil from a flask into the cask
//
int pour(string cmd) {
   object flask=present(SR_FLASK,TP);
   string pcpat="'oil' / 'flask' 'in' / 'into' [the] 'cask'";
   string verb=query_verb();
   string fshort;
   if (objectp(flask)) fshort=(flask->query_short());
 
   //make sure player specifies pouring/emptying oil into the cask
   notify_fail(verb+" what into what?\n");
   if (!stringp(cmd)) return 0;
   if (!parse_command(cmd,all_inventory(TP),pcpat)) return 0;
 
   //check if player has a proper flask
   if (!objectp(flask))
      write("You do not have a proper flask of oil.\n");
 
   //check if the flask is empty
   else if ((flask->query_amt())==0)
      write("The "+fshort+" is empty.\n");
 
   //check if the oil in the flask is plain unblessed whale oil
   else if ((flask->query_oilid())!=OLIVE_OIL)
      write("The oil in the "+fshort+" may not be mixed with the oil "+
            "in the cask.\n");
 
   //check if the cask if full
   else if (amt>=FULL_AMT)
      write("The cask is already full!\n");
 
   //all is well, empty the flask of oil into the cask
   else
      {
      set_cask_amt(amt+(flask->query_amt()));
      flask->init_flask();
      write("You "+verb+" the "+fshort+" into the cask.\n");
      tell_room(ENV(TO),QCTNAME(TP)+" pours a "+fshort+" into the cask.\n",
                        TP);
      }
   return 1;
}
 
//
// object creation
//
void create_object() {
   set_name("cask");
   add_name("barrel");
   add_adj(({"large","wooden"}));
   set_short("large wooden cask");
   add_prop(OBJ_I_VOLUME,1000000);
   add_prop(OBJ_I_WEIGHT,1000000);
   add_prop(OBJ_I_VALUE,0);
   add_prop(OBJ_I_NO_GET,1);
   read_cask_amt();
   set_desc();
}
 
//
// init - add pour and fill commands
//
void init() {
   ::init();
   add_action(&fill(),"fill");
   add_action(&pour(),"pour");
   add_action(&pour(),"empty");
}
