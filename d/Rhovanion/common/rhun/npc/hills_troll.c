
inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"
#define THIS this_object()

create_monster() {

set_race_name("troll");
set_adj("dirty");
add_adj("hungry");
set_name("harry");
add_name("_rhun_hills_cave_troll");

set_alignment(-700);
set_long("This dirty troll looks rather hungry.  "+
    "Perhaps you don't want to mess with him.\n");
   add_prop(CONT_I_WEIGHT, 100*1000);
add_prop(CONT_I_VOLUME, 100*1000);
add_prop(CONT_I_HEIGHT, 250);
set_stats(({90,80,95,10,10,99}));
set_hp(query_max_hp());


set_skill(SS_UNARM_COMBAT, 90);
set_skill(SS_DEFENCE, 78);

set_aggressive(1);


}

