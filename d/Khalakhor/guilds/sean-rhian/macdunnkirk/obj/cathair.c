// Cathair (bishop's throne) of Kirk Seanchan Tor in port MacDunn
//
// History:
// Date        Coder       Action
//----------   ----------- ----------------------------------
// 6/25/98     Zima        Created
//
//
inherit "/std/object";
#include <stdproperties.h>
#include "defs.h"
inherit  MDKLIB+"coa";
 
void create_object() {
   set_name("cathair");
   set_short("the cathair");
   set_long(
      "It is the cathair of the kirk, a throne-like chair made of "+
      "marble and cushioned with royal violet silk. It is sculpted "+
      "with holly leaves and berries along its side, and bears a "+
      "coat-of-arms at the top of its high back. It is symbolic of the "+
      "seat of authority of the one who rules here.\n");
 
   add_item(({"coat-of-arms","arms","emblem","coat of arms"}),
      "The coat-of-arms on the back of the cathair consists of a "+
      "shield of violet on which is emblazoned a holly leaf with three "+
      "red berries. A mitre surmounts the shield, with a tricircum "+
      "emblem on its front. Two silver censors flank the shield on "+
      "either side, and a ribbon below is inscripted with the motto: "+
      "Luaid Bi Seanchan Tor Solsheyder a'Orduigh.\n"+
      "You could get a better picture with 'view arms'.\n");
 
   add_cmd_item("arms","view","@@seanchan_tor_coa");
 
    add_prop(OBJ_I_NO_GET, "It is much too heavy for you to lift.\n");
    add_prop(OBJ_I_VOLUME, 50000);
    add_prop(OBJ_I_WEIGHT, 100000);
}
 
int do_sit(string cmd)
{
   notify_fail("Sit on what?\n");
   if (!stringp(cmd)) return 0;
   if (!parse_command(cmd,all_inventory((this_player())),"'on' / 'in' 'cathair'"))
      return 0;
   write("The cathair mysteriously resists you.\n");
   return 1;
}
 
void init()
{
   ::init();
   add_action(&do_sit(),"sit");
}
