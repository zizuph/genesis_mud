/* This old gnome is a former fisherman who has lost his family.
He should have a quest, eventually. Created 10.10.98, Bishop of
Calia */

inherit "/std/monster.c";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <const.h>
#include "defs.h"

#define STATAV   80
#define STATDIFF  5
#define ALIGN   0

void
equip_me()
{
    object armour;
    object weapon;

    seteuid(getuid(this_object()));

    weapon = clone_object(RUST_WEAPONS + "old_battleaxe");
    weapon->move(this_object());
   
    armour = clone_object(RUST_ARMOURS + "dusty_old_coat");
    armour->move(this_object());

    command("wear armours");
}


void
create_monster()
{
    set_name("jessup");
    add_name("jessup");
    set_race_name("gnome");
    add_adj("ancient");
    add_adj("big-nosed");

    set_gender(G_MALE);

    set_long("This ancient gnome regards you quietly as he sits in" +
        " his rocking chair, his steel grey eyes unblinking." +
        " The heavy set of his features makes him seem both stern" +
        " and sad.\n");

    set_alignment(ALIGN);

    set_base_stat(SS_STR, STATAV + random(STATDIFF));
    set_base_stat(SS_DEX, STATAV + random(STATDIFF));
    set_base_stat(SS_CON, STATAV + random(STATDIFF));
    set_base_stat(SS_INT, STATAV + random(STATDIFF));
    set_base_stat(SS_WIS, STATAV + random(STATDIFF));
    set_base_stat(SS_DIS, STATAV + random(STATDIFF));

    set_skill(SS_WEP_AXE, 70);
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_AWARENESS, 75);

    set_hp(query_max_hp());


    add_prop(CONT_I_WEIGHT, 35000);
    add_prop(CONT_I_VOLUME, 35000);
    add_prop(CONT_I_HEIGHT, 90);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(LIVE_S_EXTRA_SHORT," is sitting in a rocking chair");
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

    set_alarm(1.0, 0.0, &command("sigh")); 
    set_alarm(2.0, 0.0, &command("wield battleaxe")); 
}

int 
query_option(int opt)
{ 
    if (opt == OPT_UNARMED_OFF) 
        return 1; 
   
    else return
       ::query_option(opt);

}
