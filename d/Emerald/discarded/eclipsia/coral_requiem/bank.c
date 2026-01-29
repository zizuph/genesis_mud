inherit "/std/room";
inherit "/lib/bank";

#include <stdproperties.h>
#include "../edefs.h"

void
create_room()
{
   clone_object("/d/Genesis/obj/deposit")->move(this_object());
   set_short("Bank office");
   
   add_item( ({ "sign", "instructions" }), "There is writing on it.\n");
   set_long("   This is the bank of Coral Requiem.  It is " +
      "very beautiful in every respect.  Coral pillars rise to the " +
      "ceiling, and the counter is made of pearl.  You notice " +
      "a sign hanging on the counter with some instructions " +
      "written on it. The gnome teller here is surrounded by a " +
      "strange air bubble which allows him to breathe normally.\n\n");
   
   add_item(({"pillars","pillar"}), "The beautifully fashioned " +
      "coral pillars rise to the roof of the building.\n");
   add_item("counter","The counter is made of pearl.\n");
   add_item("bubble", "The strange bubble provides the gnome with " +
      "the air he needs to survive these conditions.\n");
   
   add_cmd_item( ({ "sign", "instructions" }), "read",
      "@@standard_bank_sign");
   
   add_exit(CRDIR + "cr26", "north");
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_prop(ROOM_I_INSIDE, 1);
   
   config_default_trade();
   set_bank_fee(19);
   config_trade_data();
}

void
init()
{
   ::init();
   bank_init();
}
