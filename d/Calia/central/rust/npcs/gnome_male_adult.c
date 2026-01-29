/* Created 28/10/98 by Bishop, of Calia. This is a gnome adult male
NPC of the gnome village of Rust. */

inherit "/std/monster.c";

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <options.h>
#include "defs.h"

#define STATAV   50
#define STATDIFF  20
#define ALIGN   50

/* Equips him */

void
equip_me()
{
    object armour;
    object weapon;

    seteuid(getuid(TO));

    weapon = clone_object(RUST_WEAPONS + "woodsmans_axe");
    weapon->move(TO);

    armour = clone_object(RUST_ARMOURS + "leather_jacket");
    armour->move(TO);
    
    armour = clone_object(RUST_ARMOURS + "leather_pants");
    armour->move(TO);

    command("wear armours");
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
    set_short(adultfeatures[x] +  " big-nosed male gnome");
    add_adj(adultfeatures[x]);
    add_adj("big-nosed");

    set_gender(0);

    set_long("This is an adult male gnome. He wears a short," +
        " well-trimmed beard, and looks to be in decent shape." +
        " His stance is not that of a warrior though, as he" +
        " regards you with curious eyes.\n");

    set_alignment(ALIGN);

    set_base_stat(SS_STR, STATAV + random(STATDIFF));
    set_base_stat(SS_DEX, STATAV + random(STATDIFF));
    set_base_stat(SS_CON, STATAV + random(STATDIFF));
    set_base_stat(SS_INT, STATAV + random(STATDIFF));
    set_base_stat(SS_WIS, STATAV + random(STATDIFF));
    set_base_stat(SS_DIS, STATAV + random(STATDIFF));

    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_WEP_AXE, 50);
    set_skill(SS_AWARENESS, 45);

    set_hp(query_max_hp());


    add_prop(CONT_I_WEIGHT, 35000);
    add_prop(CONT_I_VOLUME, 35000);
    add_prop(CONT_I_HEIGHT, 90);

}

void
notify_attacked(object friend, object attacker)
{
    if (!objectp(query_attack()))
        set_alarm(1.0, 0.0, &command("assist"));
    set_alarm(2.0, 0.0, &command("wield axe"));
}

void
attacked_by(object enemy)
{
    object *friend;
  
    friend = (object *)query_team_others();

    friend->notify_attacked();

    (RUST_SPECIALS + "guard_rescue.c")->set_priority(0, TO);

    set_alarm(1.0, 0.0, 
        &command("shout Someone is trying to kill me! Guards!"));
    set_alarm(2.0, 0.0, &command("wield axe"));
    ::attacked_by(enemy);
}

int 
query_option(int opt)
{ 
    if (opt == OPT_UNARMED_OFF) 
        return 1; 
   
    else return
       ::query_option(opt);

}

