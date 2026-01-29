inherit "/std/monster.c";

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <options.h>
#include <const.h>
#include "defs.h"

#define STATAV   50
#define STATDIFF  20
#define ALIGN   0

void
create_monster()
{
    set_name("mons");
    add_name("mons");
    add_name("shopkeeper");
    set_race_name("gnome");
    add_adj("wrinkled");
    add_adj("big-nosed");

    set_gender(G_MALE);

    set_long("This is an old gnome who appears to be the shopkeeper." +
        " He looks like he could be a few hundred years old, and he" +
        " regards your possessions with scrutiny, as if appraising" +
        " their worth.\n"); 

    set_alignment(ALIGN);

    set_base_stat(SS_STR, STATAV + random(STATDIFF));
    set_base_stat(SS_DEX, STATAV + random(STATDIFF));
    set_base_stat(SS_CON, STATAV + random(STATDIFF));
    set_base_stat(SS_INT, STATAV + random(STATDIFF));
    set_base_stat(SS_WIS, STATAV + random(STATDIFF));
    set_base_stat(SS_DIS, STATAV + random(STATDIFF));

    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_AWARENESS, 75);

    set_hp(query_max_hp());


    add_prop(CONT_I_WEIGHT, 35000);
    add_prop(CONT_I_VOLUME, 35000);
    add_prop(CONT_I_HEIGHT, 90);
}

void
add_introduced(string str)
{
    set_alarm(1.0, 0.0, &command("introduce me")); 
}

void
attacked_by(object enemy)
{
    ::attacked_by(enemy);

    (RUST_SPECIALS + "guard_rescue.c")->set_priority(1, TO);

    set_alarm(1.0, 0.0, &command("shout I'm being attacked! Guards!"));
}
