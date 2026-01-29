inherit "/std/room";

#include "defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

/* Prototypes */
void reset_room();

void
create_room() {
   set_short("pet shop");
   set_long(break_string(
      "You have entered a little pet shop. For sale there are several "
    + "kinds of dogs. Behind a small wooden counter is the owner of the "
    + "shop. On the counter lie some brochures for you to grab. Behind the "
    + "counter hangs a small sign.\n", 70));

   add_item(({"sign","small sign"}),"@@sign_long");

   add_item(({"counter","wooden counter","small wooden counter"}), break_string(
      "The small wooden counter is really a simple wooden table. On it lie "
    + "some brochures that you can grab.\n",70));

   add_exit(HINROOM_DIR + "hall2", "west",0);

   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
   add_prop(ROOM_I_NO_ATTACK, 1);
   reset_room();
}

void
reset_room() {
   if (!find_living("_petshop_owner_"))
      clone_object(NPC_DIR + "petshop_owner")->move(this_object());
}

void
init() {
   ::init();
   add_action("do_read","read",0);
   add_action("do_grab","grab",0);
}

string
sign_long() {
   return 
      "                 Welcome to the petshop!\n"
    + "            We have the following pets for sale:\n\n"
    + "            Beagle    ...... some copper coins\n"
    + "            Labrador  ...... some copper coins\n"
    + "            Pitbull   ...... some copper coins\n"
    + "            Dobermann ...... some copper coins\n";
}

int
do_read(string str) {
   if (str == "sign" || str == "small sign")
   {
       write("You read:\n" + sign_long());
       return 1;
   }
   return 0;
}

int
do_grab(string str) {
   object tp, obj;

   if (str == "brochure" || str == "brochure from counter")
   {
      tp = this_player();

      if (present("_pet_brochure_", tp))
      {
         write("You already have a brochure.\n");
         return 1;
      }

      obj = clone_object(OBJ_DIR + "brochure");
      if (obj->move(tp))
      {
         write("You fail to get the brochure.\n");
         say(QCTNAME(tp) + " tries to get a brochure from the counter, but "
           + "fails.\n");
         obj->remove_object();
      }
      else
      {
         write("You grab a brochure from the counter.\n");
         say(QCTNAME(tp) + " grabs a brochure from the counter.\n");
      }
      return 1;
   }
   return 0;
}
