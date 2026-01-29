/* Kirk of Port City - Office of the Abbot/Bishop
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 4/20/97     Zima        Created
**
*/
/* inherits/includes */
inherit "/d/Khalakhor/std/room";
#include "/sys/ss_types.h"
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
inherit  MDKLIB+"coa";
 
object abbot;
 
void reset_room () {
   if (abbot) return;
   abbot=clone_object(SR_NPC+"semion");
   abbot->equip_me();
   abbot->move(this_object());
   tell_room(this_object(),QCTNAME(abbot)+" enters the chamber.\n");
}
 
/* room definition */
void create_khalakhor_room() {
   set_short("An ornate office");
   set_long(
      "   A great oak desk sits in the middle of this chamber, dominating "+
      "what must be an office for an official of the kirk. An almost throne-"+
      "like chair sits behind the desk, with an emblem carved at the top of "+
      "its high coushioned back. There is an elegantly carved bookshelf "+
      "along the eastern wall, and a large silk banner on the western. "+
      "Two candelabrum sit on either side of a window on the northern "+
      "wall, lighting the stone chamber.\n");
   INSIDE;
 
   add_item(({"candelabra","candelabrum","candelabras","candles"}),
      "There are two ornate candelabrum on either side of the "+
      "window on the northern wall, similar to those in the "+
      "corridor. Dozens of candles sit along its branches, lighting "+
      "the chamber.\n");
   add_item("bookshelf",
      "It is an elegantly carved bookshelf with glass doors. It seems to "+
      "hold books of documents, probably financial and statistical "+
      "information for the kirk. It is locked and can not be opened.\n");
   add_item("banner",
      "The banner on the wall is made of white silk, and bear a heraldric "+
      "emblem sewn in threads of gold, green and red.\n");
   add_item(({"window","sunlight"}),
      "The window is made of opaque panes of cream colored glass arranged "+
      "in a lattice of diamond shapes. It is flanked by two candelabrum.\n");
   add_item(({"entrance","cooridor"}),
      "The entrance leads into the cooridor to the south.\n");
   add_item("desk",
      "It is a long, heavy oak desk, carved with a ring of shamrocks "+
      "around its top. Heavily polished, the surface of the desk "+
      "reflects even the dim light from the candles behind it. There "+
      "is a piece of parchment laying on top of it.\n");
   add_item("parchment",
      "The parchment laying on the desk seems to be some official document."+
      " It has a message written on it with an elegant penmanship, and "+
      "bears a seal beneath its signature.\n");
   add_cmd_item(({"parchment","message","document"}),"read","@@do_read");
   add_item(({"in chair","chair"}),
      "The plush, high-backed chair is made of the same polished oak as "+
      "the desk. It is marked with sets of parallel grooves and carved "+
      "with figures of angels and shamrocks. A regal emblem is set in "+
      "the center of the high back, right above the head of someone who "+
      "might sit there.\n");
   add_cmd_item(({"chair","in chair"}),"sit","That wouldn't be proper.\n");
   add_item(({"coat-of-arms","arms","emblem","coat of arms"}),
      "The emblem is a coat-of-arms which consists of a "+
      "shield of violet on which is emblazoned a holly leaf with three "+
      "red berries. A mitre surmounts the shield, with a tricircum "+
      "emblem on its front. Two silver censors flank the shield on "+
      "either side, and a ribbon below is inscripted with the motto: "+
      "Luaid Bi Seanchan Tor Solsheyder a'Orduigh.\n"+
      "You could get a better picture with 'view arms'.\n");
   add_cmd_item("arms","view","@@seanchan_tor_coa");
   add_exit("kcorr1",    "south");
   reset_room();
}
 
int do_read() {
   if (this_player()->query_skill(SS_LANGUAGE)>40) {
   write(
      "To Abbot Semion of Kirk Seanchan Tor in Port MacDunn: \n\n"+
      "I am in desperate need of incense for the upcoming rites here "+
      "in the kirk of Tabor Sogh. Please send someone to me as soon as "+
      "possible.\n\n"+
      "In the Harmony of Ardaugh, \n"+
      "Prior Gebann of the Kirk at Tabor Sogh.\n\n");
   }
   else write("You can not read the cryptic language.\n");
   return 1;
}
