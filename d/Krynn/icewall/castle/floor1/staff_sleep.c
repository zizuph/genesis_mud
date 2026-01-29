/************************************************/
/*  Staff Sleeping Quarters of Icewall castle */
/*              coded by Stevenson                 */
/************************************************/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>

inherit ICEINROOM;

object trash, box;
int krynn_wizard_here = 0;


void reset_icewall_room() {
   if (!krynn_wizard_here) krynn_wizard_here = 1;
   if (!trash) {
      trash = clone_object(ICE_CAST_O+"litter_bin");
      trash->move(TO);
   }
   if (!box) {
      box = clone_object(ICE_CAST_O+"kender_box");
      box->move(trash);
   }
}

void create_icewall_room()
{
   set_short("Staff Sleeping Quarters");
   set_long(
      "\nYou find yourself standing in what seems to be a dormitory."
+ " There are several beds in the room@@c@@. "
      + "Immediately to the left of the bed is a beautiful "
      + "wardrobe made of lustrous wood. "
      + "\n" );
   
   add_item("man",
      "@@issleep");
   add_item(({"beds","bed"}),
      "The beds in the room are very basic and made of some cheap wood.\n");
   add_item("paper",
      "The bits of paper look unimportant.\n");
   add_item("wardrobe",
      "The old wardrobe is locked shut.\n");
   add_cmd_item("wardrobe",({"open","unlock"}),
      "The wardrobe is quite locked. You cannot open it.\n");
   add_cmd_item("man","wake","@@krynn_wizard");
   
   add_exit(ICE_CAST1_R + "west_corner.c", "north");
   
   reset_icewall_room();
}

string c() {
   if (krynn_wizard_here) return
      ", one of which is occupied by a strange man";
   return "";
}

string krynn_wizard() {
   if (!krynn_wizard_here) return "What man?\n";
   write("You reach over and shake the man.\n");
   say(QCTNAME(TP) + " rudely attempts to awaken the sleeping man.\n");
   
   set_alarm(1.0,0.0,"appear",TP);
   return "";
}

void appear(object obj) {
   tell_room(TO,"A Krynn Wizard tumbles out of the bed.\n");
   tell_room(TO,"The Krynn Wizard says: Damn! " + QCTNAME(obj)
      + " went and woke me up!!!\n");
   tell_room(TO,"The Krynn Wizard disappears in a puff of smoke.\n");
   krynn_wizard_here = 0;
}

string issleep() {
   if (!krynn_wizard_here) return "What man?\n";
   return "The man appears to be very fast asleep: snoring, in fact.\n";
}
