/*
**   ARGOS - Metro - Royal Bank of Argos
**   A player can ask the bursar for a quill if he is on the Registry Quest
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   3/5/95     Zima       Created
**
*/
inherit  "/std/room";
inherit  "/lib/bank";
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "defs.h"
#include "../tours.h"
#define BANK_FEE 25
 
void create_room() {
   set_short("The Royal Bank of Argos");
   set_long(
      "You are standing in the Royal Bank of Argos, constructed "+
      "of glistening marble which shines from continual cleaning. "+
      "A Bursar stands behind a barred window on the northern "+
      "wall of the chamber ready to assist you in your financial "+
      "transactions. A seal has been sculpted on the western wall, "+
      "while a plaque is bolted next to the window.\n");
   add_item("plaque",
      "Cast of brass etched with gold, this large plaque is bolted to "+
      "the wall next to the Bursar's window, bearing the seal of the "+
      "Exchequer. Perhaps you should read it.\n");
   add_cmd_item("plaque","read","@@read_plaque");
   add_item("seal",
      "It is a shield emblazoned with a rampant winged horse, surmounted "+
      "by a crown of three jewels. Two large keys are crossed behind "+
      "the shield. It is the emblem of the Exchequer, or Royal Treasury.\n");
   add_item(({"Bursar","bursar"}),
      "He is an elderly gentleman with a crooked nose, dressed in a "+
      "long blue tunic with a gold sash. He is standing behind the "+
      "safety of the bars of the window of the bank.\n");
   add_item("bars",
      "They are set in the window to protect the Bursar behind it.\n");
   add_item("window",
      "It is a large window set with bars, behind which stands the "+
      "Bursar ready to assist you.\n");
   add_prop(ROOM_I_INSIDE,1);
 
   /* setup banking functions */
   config_default_trade();
   set_bank_fee(BANK_FEE);
   config_trade_data();
 
   /* exits */
   add_exit(ROOM_DIR+"croad9", "south",0);
   add_exit(ROOM_DIR+"droad10","east",0);
}
 
 
string read_plaque() {
    return
   "On the sign you read:\n\n" +
   "We change copper, silver, gold, and platinum coins.  " +
   "Simply mention the kind you want to change, and the kind you want " +
   "to get.  " +
   "Our bank provides you with a cheap way to relief you of the burden " +
   "of heavy coins.  " +
   "For each transaction we ask only a " + BANK_FEE + "% fee.  " + "\n" +
 
   "This is an example of what you can do:\n" +
   "    change copper and silver to gold\n" +
   "  This would make you change all your copper and silver coins\n" +
   "  into as much gold as possible.\n" +
   "    test change copper and silver to gold\n" +
   "  This would show you the out come of the command behind\n" +
   "  the 'test' word.\n" +
   "    change 1 platinum to copper\n" +
   "  This would change 1 platinum coin to copper coins.\n" +
   "    change platinum to 100 silver\n" +
           "  This would change platinum coins to 100 silver coins + " +
   "the change\n" +
   "  that would be left from the platinum coins needed after " +
   "100 silver\n" +
   "  coins has been given.\n" +
   "    minimize coins\n" +
   "  This changes all coins into the most valuable types possible.\n" +
   "\n";
}
 
int ask(string StringParm) {
   /* allows player to "ask bursar for quill" for the Registry Tour */
   object Tp=this_player();
   object Tr=this_object();
   object Quill=present(REG_TOUR_QUILL,Tp);
   string *Parm;
 
   Parm=explode(StringParm," ");
   if (!StringParm) return 0;                      /* must pass parameters */
   if (!(lower_case(Parm[0])=="bursar")) return 0; /* must ask bursar      */
 
   tell_room(Tr,QCTNAME(Tp)+" asks the bursar behind the window something.\n",
             Tp);
   if (member_array("quill",Parm) == -1) {         /* must ask for quill   */
      tell_room(Tr,"The Royal Bursar says: What is it you want?\n");
      return 1;
   }
 
   /* don't give another quill */
   if (Quill) {
      tell_room(Tr,"The Royal Bursar says: You already have one. Don't "+
                   "be greedy!\n");
      return 1;
   }
 
   /* don't give if not officially on the tour */
   if (Tp->query_prop(ARGOS_TOUR_PROP) != ON_REG_TOUR) {
      tell_room(Tr,"The Royal Bursar says: I don't know you stranger. Why "+
                   "don't you go talk to Alexis before you come around "+
                   "asking me for handouts!\n");
      return 1;
   }
 
   /* all is OK..give quill to player */
   write("The Royal Bursar hands a quill to you through the bars of "+
                "the window.\n");
   tell_room(Tr,"The Royal Bursar hands a quill to "+QCTNAME(TP)+
                " through the bars of the window.\n",Tp);
   tell_room(Tr,"The Royal Bursar says: Compliments of the Royal "+
                "Exchequer. Have a nice day!\n");
   tell_room(Tr,"The Royal Bursar smiles behind the window.\n");
   (clone_object(OBJ_DIR+"regquill"))->move(Tp);
   return 1;
}
 
void init() {
    ::init();
    bank_init(); /* init banking support */
    add_action("ask","ask");
}
