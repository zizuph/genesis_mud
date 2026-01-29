/* Created 28/10/98 by Bishop, of Calia. This is a gnome housewife
NPC of the gnome village of Rust. */

inherit "/std/monster.c";

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include "defs.h"

#define STATAV   40
#define STATDIFF  10
#define ALIGN   50

/* Equips her */

void
equip_me()
{
    object armour;
    object weapon;

    seteuid(getuid(TO));

    armour = clone_object(RUST_ARMOURS + "apron");
    armour->move(TO);

    weapon = clone_object(RUST_WEAPONS + "wooden_broom");
    weapon->move(TO);
    command("wear all");
}


void
create_monster()
{
    int x;
    string *adultfeatures;
    
    adultfeatures = ({"smiling","carefree","grinning","dark-eyed",
        "long-haired","curly-haired","pointy-eared"});

    x = random(sizeof(adultfeatures));

    set_race_name("gnome");
    set_short(adultfeatures[x] +  " big-nosed female gnome");
    add_adj(adultfeatures[x]);
    add_adj("big-nosed");

    set_gender(1);

    set_long("This adult gnome woman looks like a gentle creature." +
        " Her hair is fashioned into a bun, and her gaze sweeps across" +
        " the room, keeping an eye on her family.\n");

    set_alignment(ALIGN);

    set_base_stat(SS_STR, STATAV + random(STATDIFF));
    set_base_stat(SS_DEX, STATAV + random(STATDIFF));
    set_base_stat(SS_CON, STATAV + random(STATDIFF));
    set_base_stat(SS_INT, STATAV + random(STATDIFF));
    set_base_stat(SS_WIS, STATAV + random(STATDIFF));
    set_base_stat(SS_DIS, STATAV + random(STATDIFF));

    set_skill(SS_UNARM_COMBAT, 20);
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_WEP_POLEARM, 40);

    set_hp(query_max_hp());

    add_prop(CONT_I_WEIGHT, 30000);
    add_prop(CONT_I_VOLUME, 30000);
    add_prop(CONT_I_HEIGHT, 80);
}

void
notify_attacked(object friend, object attacker)
{

    if (!objectp(query_attack()))
        set_alarm(1.0, 0.0, &command("assist"));
    set_alarm(2.0, 0.0, &command("wield broom"));
}

void
attacked_by(object enemy)
{
    object *friend;
  
    friend = (object *)query_team_others();

    friend->notify_attacked();

    (RUST_SPECIALS + "guard_rescue.c")->set_priority(0, TO);

    set_alarm(1.0, 0.0, 
        &command("shout Goodness gracious! Guards!"));
    set_alarm(2.0, 0.0, &command("wield broom"));

    ::attacked_by(enemy);
}

