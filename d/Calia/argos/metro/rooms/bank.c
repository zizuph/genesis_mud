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
public void reset_room();

string
show_sign(void)
{
    return(
"          The gold plated plaque reads:\n"+
"          +----------------------------------------+\n"+
"          |          Royal Bank of Argos           |\n"+
"          |        " + sprintf("%2d", bank_fee) +
                     "% fee to change coins         |\n"+
"          |----------------------------------------|\n"+
"          | Examples:                              |\n"+
"          | change copper and silver for gold      |\n"+
"          | test change copper and silver for gold |\n"+
"          | change 1 platinum for copper           |\n"+
"          | change platinum for 100 silver         |\n"+
"          | minimize coins                         |\n"+
"          +----------------------------------------+\n");
}
 
void create_room()
{
	config_default_trade();
	bank_fee = 5 + random(10);
	set_bank_fee(bank_fee);
	config_trade_data();
	set_short("The Royal Bank of Argos");
	set_long("You are standing in the Royal Bank of "+
	"Argos, constructed of glistening marble which shines "+
	"from continual cleaning. A Bursar stands behind a "+
	"barred window on the northern wall of the chamber "+
	"ready to assist you in your financial transactions. "+
	"A seal has been sculpted on the western wall, "+
	"while a plaque is bolted next to the window.\n");
	
	add_item(({"plaque"}), show_sign);
	add_cmd_item("plaque","read", show_sign);
	add_item("seal", "It is a shield emblazoned with a rampant "+
	"winged horse, surmounted "+
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
 
   /* exits */
   add_exit(ROOM_DIR+"croad9", "south",0);
   add_exit(ROOM_DIR+"droad10","east",0);
	
	object deposit = clone_object("/d/Genesis/obj/deposit");
	deposit->set_bank_id(1403, "Argos");
	deposit->move(this_object(), 1);
	reset_room();

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
void
reset_room()
{
}

void
init()
{
    ::init();
    bank_init();
    add_action("ask","ask");
}
