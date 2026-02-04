inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <comb_mag.h>
#include <ss_types.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h";

#define TO this_object()
#define TP this_player()
#define EN environment


int stop, close;

init(){
   add_action("seal", "seal");
   ::init();
}

seal(){
   
   if(stop > 0){
      write("You remove the seal from the door.\n");
      say(QCTNAME(this_player()) + " removes the seal from the door.\n");
      stop = 0;
      return 1;
   }
   write("You place a seal upon the door.\n");
   say(QCTNAME(this_player()) + " places a seal upon the door.\n");
   stop = 1;
   return 1;
}

create_room(){
   
   set_short("Hall of Lords");
   set_long(
      "Rising up in colossal proportions, this august stone hall stands as\n"
      +"a monument and symbol to the world. Its grand tiered dome reaching\n"
      +"upward, grasping vainly to the heavens. Long majestic banners hang from the\n"
      +"tiers and mask the stone walls with their gleaming splendour. An ancient\n"
      +"wooden table rests in the center of the hall.\n"
   );
   
   add_item("banners", "There are ten banners.\n");
   add_item(({"first banner", "banner 1"}),
      "It bears the image of a proud knight in shining gold armour\n"
      +"holding aloft a broadsword, set upon a background split one\n"
      +"side black and one side white.\n");
   add_item(({"second banner", "banner 2"}),
      "Upon this sparkling blue banner is a noble white ship, over which\n"
      +"rise three golden stars.\n");
   add_item(({"third banner", "banner 3"}),
   );
   add_item(({"fourth banner", "banner 4"}),
   );
   add_item(({"fifth banner", "banner 5"}),
      "");
   add_item(({"sixth banner", "banner 6"}),
      "");
   add_item(({"seventh banner", "banner 7"}),
      "");
   add_item(({"eighth banner", "banner 8"}),
      "");
   add_item(({"ninth banner", "banner 9"}),
      "");
   add_item(({"tenth banner", "banner 10"}),
      "");
   add_prop(ROOM_I_NO_TELEPORT, 1);
   add_prop(ROOM_I_LIGHT, 1);
   add_prop(ROOM_I_INSIDE, 1);
   
   
}

enter_inv(ob, from){
   
   if(TP->query_average_stat() < 100){
      stop = 1;
      write("You sense such power that you fear to enter!\n");
   }
   if(stop>0)
      {
      if(this_player()->query_wiz_level() > 29){
         write("That place has been sealed.\n");
      }
      ob->move(from);
   }
}



leave_inv(ob, to){
   
   ::leave_inv(ob, to);
}


