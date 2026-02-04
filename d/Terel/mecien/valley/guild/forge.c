/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

#define PATH   "/d/Terel/mecien/valley/guild/"
#define TP  this_player()

reset_room(arg){
   object smith;
   if(present("eringil")) return 0;
   smith = clone_object(PATH + "smith");
   smith ->move(this_object());
}


create_room(){
   
   object obj;
   
   set_short("Forge");
   set_long(
   "Alive with clouds of steam and smoke, this ancient chamber is the\n"
  + "forge of the mystic shrine. This dark stone chamber is small and\n"
  + "circular in shape, its walls barren and craggy. The thick air is\n"
  + "hot and small particles of metal and ash coat the floor.\n"
  + "A huge stone forge is in the center of the chamber, its massive\n"
  + "size dominates. Intense fires war inside it, roaring and hissing\n"
  + "like mythic creatures in battle. A large stone basin stands next\n"
  + "to the forge.\n"
  );
   
    add_item("forge",
         "A massive stone forge in which metals are heated, this one seems\n"
        + "to be lit by somekind of coal. Its fire roaring in intensity.\n");
    add_item(({"fire", "fires"}), "Intense flames within the forge itself.\n");

   add_item("clouds", "The clouds are smoke from the fire and steam from\n"
    + "the water used to cool the metals.\n");
   add_item("smoke", "It comes from the forge.\n");
   add_item("steam", "This steam comes from the waters used to cool metals.\n");
   add_item("basin", "This stone basin is where hot metal are placed to cool.\n"
          + "It is filled with water.\n");
    add_item("water", "Used to cool hot metals, it fills the basin.\n");
    add_item("walls", "The are barren and craggy, of darkened stone.\n");
    add_item("air", "Thick, filled with smoke and steam.\n");
    add_item("particles", "Small scraps of metal cast from the forge.\n");
    add_item("ash", "Bits of ash from the forge, it coats the floor.\n");
   
    add_exit(PATH + "emporium", "east", 0);

   obj = clone_object(PATH + "anvil");
   obj->move(this_object());
   
    reset_room();
}


init() {
   ::init();
   // add_action("do_wax","wax",0);
   // add_action("do_sharpen","sharpen",0);
   // add_action("do_harden","harden",0);
}

/*

do_wax(str) {
   if(!str || !(weapon = present(str,this_player())))
      return 0;
   write("The blacksmith says: I am sorry, I am out of wax!\n");
   return 1;
}

do_sharpen(str) {
   if(!str || !(weapon = present(str,this_player())))
      return 0;
   write("The blacksmith says: I am sorry, I cannot do that now!\n");
   return 1;
}

do_harden(str) {
   if(!str || !(weapon = present(str,this_player())))
      return 0;
   write("The blacksmith says: I am sorry, I do not have the proper tools!\n");
   return 1;
}
*/
