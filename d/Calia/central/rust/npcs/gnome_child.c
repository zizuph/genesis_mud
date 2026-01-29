/* Created 28/10/98 by Bishop, of Calia. This is a gnome child
NPC of the gnome village of Rust. */

inherit "/std/monster.c";
inherit "/std/act/domove.c";

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include "defs.h"

#define STATAV   20
#define STATDIFF  5
#define ALIGN   100

/* Equips the child */

void
equip_me()
{
    object armour;

    seteuid(getuid(this_object()));

    armour = clone_object(RUST_ARMOURS + "child_coat");
    armour->move(TO);

    command("wear all");
}


void
create_monster()
{
    int x;
    string *childfeatures;

    childfeatures = ({"playful","mischievous","impish","wide-eyed",
        "dark-eyed","grinning"});

    x = random(sizeof(childfeatures));

    set_race_name("gnome");
    set_short(childfeatures[x] +  " gnome child");
    add_adj(childfeatures[x]);
    add_name("child");

    set_gender(0);

    set_long("This freckled little guy stands about two feet tall, and" +
        " has a playful gleam in his eyes. He has a small nose, and his" +
        " curly black hair hangs" +
        " to his shoulders.\n");

    set_alignment(ALIGN);

    set_restrain_path(VILLAGE);
    set_random_move(30);

    set_base_stat(SS_STR, STATAV + random(STATDIFF));
    set_base_stat(SS_DEX, STATAV + random(STATDIFF));
    set_base_stat(SS_CON, STATAV + random(STATDIFF));
    set_base_stat(SS_INT, STATAV + random(STATDIFF));
    set_base_stat(SS_WIS, STATAV + random(STATDIFF));
    set_base_stat(SS_DIS, STATAV + random(STATDIFF));

    set_skill(SS_UNARM_COMBAT, 20);
    set_skill(SS_DEFENCE, 20);
    set_skill(SS_AWARENESS, 15);

    set_hp(query_max_hp());


    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(CONT_I_VOLUME, 10000);
    add_prop(CONT_I_HEIGHT, 50);
}

void
attacked_by(object enemy)
{
    object *friend;
  
    friend = (object *)query_team_others();

    friend->notify_attacked();

    (RUST_SPECIALS + "guard_rescue.c")->set_priority(0, TO);

    set_alarm(1.0, 0.0, &command("shout Help!"));
    ::attacked_by(enemy);
}


