/*
 *  Hammer with which you can smash the board that blocks the waterwheel
 */

#pragma save_binary

inherit "/std/object";

#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

create_object() {
   set_name(({"hammer","quest_hammer","mill_hammer"}));
   set_pname("hammers");
   set_short("hammer");
   set_pshort("hammers");
   set_long("The hammer is small but heavy.\n");

 /* Some properties of this hammer */
   add_prop(OBJ_I_WEIGHT, 4000);    /* 4.0 Kg            */
   add_prop(OBJ_I_VALUE, 7);        /* 7 Copper coins    */
   add_prop(OBJ_I_VOLUME, 90);      /* 0.09 Ltr          */
   add_prop(OBJ_S_WIZINFO,
      "Hammer that can smash the board that blocks the whaterwheel.\n");
}

init() {
   add_action("do_smash","smash");
   add_action("do_smash","crush");
   add_action("do_smash","break");
   add_action("do_smash","hit");
   add_action("do_smash","destroy");
}

do_smash(str) {
   object room;
   if (str == "" || !str) return 0;
   if (((str == "board") || (str == "the board")) &&
       (environment(this_player()) == find_object(STAND_DIR + "river3")) &&
       !((STAND_DIR + "mill")->query_wheel_fixed()))
   {
      (STAND_DIR + "mill")->set_wheel_fixed(1);

   /* Okay, now the player solved a mini-quest. Give him some
      kind of reward for it... Experience?
   */
      write(break_string(
         "You smash the board to small pieces. Now the board no longer is "
       + "blocking the wheel, it slowly starts to turn again.\n",70));
      say(QCTNAME(this_player()) + " smashes the board to pieces.\n"
        + "The big wheel slowly starts to turn again.\n");
      return 1;
   }
   return 0;
}