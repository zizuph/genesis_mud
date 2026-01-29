/* Cathedra (bishop's throne) of Kirk Sean Tor in port MacDunn
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 7/25/97     Zima        Created
**
*/
inherit "/std/object";
#include <stdproperties.h>
 
void create_object() {
   set_name("cathedra");
   set_short("the cathedra");
   set_long(
      "It is the cathedra of the kirk, a throne-like chair made of "+
      "marble and cushioned with royal violet silk. It is sculpted "+
      "with holly leaves and berries along its side, and bears a "+
      "coat-of-arms at the top of its high back. It is symbolic of the "+
      "seat of authority of the one who rules here.\n");
 
   add_item(({"coat-of-arms","arms","emblem","coat of arms"}),
      "The coat-of-arms on the back of the cathedra consists of a "+
      "shield of violet on which is emblazoned a large crystal "+
      "filled with the colors of the rainbow. A mitre sits atop "+
      "the shield, with a tricircum emblem on its front. A half "+
      "wreath of holly leaves and berries encompases the shield on "+
      "the bottom.\n");
 
   add_item("crystal",
      "It is a prism-like crystal in a diamond shape.\n");
   add_item("mitre",
      "It is a headress worn by the high cleric of this place, the "+
      "back and front arching to a point at the top. It bears a "+
      "tricircum emblem on the front.\n");
   add_item(({"emblem","tricircum"}),
      "The tricircum emblem on the mitre consists of three rings "+
      "linked at a point, like the leaves of a clover.\n");
 
    add_prop(OBJ_I_NO_GET, 1);
}
 
int do_sit(string parms) {
   string *parm;
   if (!(parms)) {
      write("Sit in what?\n");
      return 1;
   }
   parm = explode(parms," ");
   if (member_array("cathedra",parm)>=0) {
      write("The cathedra mysteriously resists you.\n");
      return 1;
   }
   write("Sit in what?\n");
   return 1;
}
 
void init() {
   ::init();
   add_action(&do_sit(),"sit");
}
