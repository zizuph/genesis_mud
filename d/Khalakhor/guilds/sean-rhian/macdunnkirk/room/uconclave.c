// Conclave - meeting and board room in the abbey
//
// History:
// Date         Coder       Action
// --------  -------------  -----------------------------------
// 6/27/98   Zima           Created
//
inherit  "/d/Khalakhor/std/room";
#include <stdproperties.h>
#include "defs.h"
inherit  MDKLIB+"coa";
 
void create_khalakhor_room()
{
   set_short("conclave of the abbey");
   set_long("   This chamber is dominated by a long polished oak table "+
            "which sits in the center atop an elegant carpet, surrounded "+
            "by several matching chairs. This is the conclave of the "+
            "abbey where the manachs and saggarts meet to discuss "+
            "matters of faith and of the Order. Light filters through "+
            "the opaque panes of a stained glass window on the west "+
            "wall mixing with the light of the dozens of candles in "+
            "the chandelier which hangs above. A large white banner "+
            "hangs on the north wall.\n");
 
   add_item("table",
       "It is a long heavy oak table, stained dark and highly waxed "+
       "and polished, reflecting the light from the window and "+
       "chandelier. Its thick top is supported by two pedestal "+
       "feet near either end of the table. It is surrounded by "+
       "several chairs of matching design, neatly pushed beneath "+
       "the table's top. Though it looks like a dining table for "+
       "a royal ball room, it sees more discussions than meals here.\n");
   add_item(({"chairs","chair"}),
       "Several chairs made of the same dark stained and highly "+
       "polished thick oak surround the long table, neatly and evenly "+
       "pushed beneath the table's top. The head chair at the west "+
       "end of the table is a bit larger.\n");
   add_item("head chair",
       "The chair at the head of the table on its west end is "+
       "made similarly to the others, only a bit larger and more "+
       "ornately carved. It is obviously the seat of one who would "+
       "preside at a conclave here.\n");
   add_item(({"carpet","floor","rug"}),
       "The floor is carpeted with a large rug made of purple and drab "+
       "wool, intricately woven with intricate scrolls, lines and "+
       "circles in the traditional celtic pattern.\n");
   add_item(({"banner","emblem","coat-of-arms","arms"}),
       "There is a large white banner hanging on the north wall of "+
       "the chamber, on which is embroidered the coat-of-arms of the "+
       "abbey. The emblem consists of a shield of violet on which is "+
       "emblazoned a holly leaf with three "+
       "red berries. A mitre surmounts the shield, with a tricircum "+
       "emblem on its front. Two silver censors flank the shield on "+
       "either side, and a ribbon below is inscripted with the motto: "+
       "Luaid Bi Seanchan Tor Solsheyder a'Orduigh.\n"+
       "You could get a better picture with 'view arms'.\n");
   add_cmd_item("arms","view","@@seanchan_tor_coa");
   add_item("window",
       "The window is tall and thin, its top rising to a "+
       "pointed arch. It is set in the western wall of the chamber, "+
       "its opaque pane a lattice of diamond shaped pieces of a "+
       "cream color.\n");
   add_item(({"candles","chandelier","ceiling"}),
       "There is a large golden chandelier hanging from the ceiling, "+
       "filled with small candles which are placed in holders around the "+
       "chandelier's circumference. They provide a good deal of light.\n");
 
   INSIDE;
 
   add_exit("ucorr6","east");
   add_exit("udorm", "south");
 
   reset_euid();
   clone_object(OBJ + "abbey_board")->move(TO);
}
 
int query_prevent_snoop() { return 1; }
