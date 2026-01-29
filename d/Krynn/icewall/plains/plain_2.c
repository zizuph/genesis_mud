/* Created by Stevenson */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

object penguin;

reset_icewall_room() {
   if (!penguin) {
      penguin = clone_object(ICE_CAST_M+"penguin");
      penguin->move(TO);
   }
}

create_icewall_room() {
   set_short("Icy Plains");
   set_long(BS(
         "Around you are the remains of what may have been "
         + "a house a very long time ago. Unfortunately, the "
         + "glacier has removed any traces of what the house "
         + "was used for. "
         + "Small footprints can be seen in the snow. "
         ,67));
   
	add_item(({"remains", "house", "remains of house"}),
		"You can see a few timbers poking out here "
      + "and there.\n");
   add_item(({"timber","timbers"}),"They are rotted and frozen.\n");
   add_item("glacier","It covers these plains like a slow-moving "
      + "slug devouring all in its path.\n");
   add_item("snow","You wonder how anyone can live with so "
      +"much snow everywhere.\n");
   add_item("footprints","They are about 5cm in diameter with "
      + "three toes.\n");
   
   add_exit(ICE_PLAINS+"plain_1","southwest");
   add_exit(ICE_PLAINS+"plain_3","north","@@wind");
   
   reset_icewall_room();
}

int wind() {
   write("A quick gust of wind forces you to slip on the ice, but "+ "you quickly regain your footing.\n");
   say(QCTNAME(TP)+" slips on the ice.\n");
   if (random(10) > 8) {
      set_alarm(1.0,0.0,"slip");
   }
   return 0;
}

slip() {
   write("You slide back down the ice.\n");
   say(QCTNAME(TP)+" slides helplessly down the ice.\n");
   tell_room(ICE_PLAINS+"plain_1",QCTNAME(TP)+" arrives, "
      + "sliding on his bumm.\n");
   TP->move_living("M",ICE_PLAINS+"plain_1",1,0);
}
