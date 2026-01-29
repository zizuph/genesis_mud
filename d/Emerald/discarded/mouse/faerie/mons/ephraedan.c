/* a humanoid npc coded by Elizabeth Cook/Mouse, October 1996 */

inherit "/std/monster";
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <alignment.h>
inherit "/std/act/chat";
inherit "/std/act/action";
#include "../../mouse.h"  

void create_monster() {
     set_name("ephraedan");
     set_living_name("mouse:ephraedan");
     set_race_name("faerie");
     set_short("faerie king");
     set_long("Judging from his great stature and stately bearing, "+
          "you immediately recognize this individual as Ephraedan, "+
          "High King of Torgwylan and Ruler of Mystickal Wanderers in "+
          "those Mortal Realms known as Festiwycke and Briarwood. His "+
          "penetrating dark eyes look as if they could pluck every "+
          "secret from the deepest corners of your soul. His complexion "+
          "is quite pale due to immeasurable time spent living within "+
          "the bowels of the earth. Long auburn braids hang down from "+
          "beneath his helmet. His dragon helm and scaled armour render "+
          "his appearance even more formidable. Your heart begins to "+
          "pound loudly in your chest while his cold, black eyes take "+
          "your full measure.\n");

     set_stats(({105,115,115,110,110,115}));    
     set_gender(G_MALE);
     set_alignment(ALIGN_DEVOUT);
     set_skill(SS_WEP_SWORD, 90);
     set_skill(SS_WEP_DAGGER, 90);
     set_skill(SS_PARRY, 85);
     set_skill(SS_2H_COMBAT, 80);
     set_skill(SS_DEFENSE, 90);
     set_skill(SS_AWARENESS, 90);
     add_prop(NPC_I_NO_LOOKS,1);
     add_prop(NPC_I_NO_RUN_AWAY,1);
     add_prop(LIVE_I_ALWAYSKNOWN,1);
     add_weapon(ROOT+"faerie/items/anlace.c");
     add_weapon(ROOT+"faerie/items/vandalbane.c");
     add_armour(ROOT+"faerie/items/scalearmour.c");
     add_armour(ROOT+"faerie/items/dragonhelm.c");
     
     set_chat_time(20);
     add_chat("What do you want, you useless mortal vermin? Haven't "+
          "you stolen enough from us?\n");
     add_chat("My poor Hypaethra! Someone shall pay dearly for all "+
          "that she suffered!\n");
     add_chat("The world would be well rid of your worthless mortal "+
          "hide.\n");
     set_act_time(30);
     add_act("emote looks at you as if he can see right through you.\n");

}

