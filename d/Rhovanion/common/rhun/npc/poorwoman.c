
inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"
#define THIS this_object()

create_monster() {
set_race_name("woman");
set_adj("poor");

  set_alignment(50);
set_gender(1);
   set_long(
	"This poor woman apparently lives here.\n");
add_prop(CONT_I_WEIGHT, 70*1000);
add_prop(CONT_I_VOLUME, 70*1000);
add_prop(CONT_I_HEIGHT, 168);
set_stats(({20,25,20,25,25,20}));
set_hp(query_max_hp());


set_skill(SS_UNARM_COMBAT, 12);
set_skill(SS_DEFENCE, 12);
   set_pick_up(43);

set_chat_time(5);
add_chat("Nearly everyone has left our little town!");
add_chat("The guards will protect us; I'm sure of it.");
add_chat("Rumor has it that the Easterling have a base in the forest.");

}

