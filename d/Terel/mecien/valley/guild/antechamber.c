/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

init(){
 add_action("enter", "enter");
  add_action("bathe", "bathe");
 ::init();
}

enter(string str){
 if (str!="water" && str!="bath") return 0;
 if (this_player()->query_skill(SS_SWIM) < 1)
 {
  write("You do not know how to swim.\n");
  say(QCTNAME(this_player()) + " goes near the water, but steps back.\n");
 return 1;
 }
 write("You step down into the bath.\n");
  say(QCTNAME(this_player()) + " steps down into the bath.\n");
 this_player()->move("/d/Terel/mecien/valley/guild/bath");
 return 1;
 }
bathe(){
write("You will have to enter the waters to do that.\n");
return 1;
}

create_room(){
  set_short("Antechamber");
  set_long("This beautiful little hall is made from a dull white\n"
   + "stone like gypsum. It is carved and inscibed with symbols\n"
   + "and bas-relief. Thin columns line the hall, they lead down\n"
   + "into a small bath that forms at the south end of the hall.\n"
   + "Stone steps lead down into the bath, its sparkling water\n"
   + "a bright aqua color.\n"
);
  add_item("water", "It is clear and bright, vivid aqua color.\n");
  add_item("symbols", "They seem astrological in nature.\n");
  add_cmd_item("water", "touch", "It feels strangely warm.\n");
  add_item(({"bas-relief", "relief", "carvings"}),
    "They are faces of mystic and wise people, perhaps of many\n"
    + "differing times. A sense of peace and hope emanates from them.\n"
    + "Interspersed amoung them are figures of winged spirits,\n"
    + "loftly and regal, in their hands long spears and shields\n"
    + "with the mystic star inscribed upon them.\n");
  add_item("columns", "They are thin, made of a soft white stone.\n");
  add_item("steps", "They are white stone like the rest of the small\n"
    +"hall, they lead into the waters of the bath. Upon them is\n"
    +"a short inscription.\n");
   add_cmd_item("inscription", "read", 
     "Let us come before the Ancients purified by the living waters.\n");
   add_item("inscription", "A few letters inscribed upon the steps.\n");
  add_item("bath", "It is a rather large bath, set into an enclosed area\n"
   + "within the shrine. It looks as though water flows in from\n"
   + "outside the shrine. A bit of steam rises from the bath, it\n"
   + "obscures vision across the bath.\n");
  add_item("steam", "It rises from the waters.\n");
  add_exit("/d/Terel/mecien/valley/guild/chamber", "north", 0);
}
