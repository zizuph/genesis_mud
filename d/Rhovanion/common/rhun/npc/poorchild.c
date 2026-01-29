
inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"
#define THIS this_object()

create_monster() {

set_race_name("child");
set_adj("poor");
add_adj("hungry");

set_alignment(13);
   set_long(break_string(
	"This child's family is apparently penniless.  He looks"
	+" rather tired and hungry.\n",75));
   add_prop(CONT_I_WEIGHT, 10*1000);
add_prop(CONT_I_VOLUME, 10*1000);
add_prop(CONT_I_HEIGHT, 80);
set_stats(({5,5,5,5,5,6}));
set_hp(query_max_hp());


set_skill(SS_UNARM_COMBAT, 2);
set_skill(SS_DEFENCE, 3);

set_chat_time(11);
add_chat("I'm hungry!");
add_chat("Have you seen my daddy?");

}

