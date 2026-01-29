/*
 * Svirfneblin of Underdark, also known as the Dark Gnomes
 * by Finwe, July, 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit FAERUN_NPC_BASE;
inherit "/d/Faerun/lib/assist_friend";
inherit "/d/Faerun/lib/gems";

void arm_me();

void create_monster()
{
    int x, y, i;
    string *type, *phys;

    seteuid(getuid());

    type = ({"elusive", "sullen", "withdrawn", "suspicious", "watchful", "cautious", "evasive" });
    phys = ({"brown-skinned", "grey-skinned", "grey-eyed", "grey-haired", "bald", "gnarled"});

    x = random(sizeof(type));
    y = random(sizeof(phys));

    npc_name = "svirfneblin";

    add_adj(type[x]);
    add_adj(phys[y]);
    add_prop(LIVE_I_NEVERKNOWN, 1);
 
    set_race_name("gnome");
    add_name("gnome");
    add_name("svirfneblin");
    add_name(npc_name);

    set_short(type[x] + " " + phys[y] + " svirfneblin");
    set_pshort(type[x] + " " + phys[y] + " svirfnebli");
    set_long("This is one of the secret svirfneblin, sometimes called dark " +
        "gnomes. They are related to gnomes and live deep in the Underdark. " +
        "They are skilled at mining and are wary of everything.\n");

    add_prop(NPC_I_NO_FEAR, 1);     /* all svirfnebli defend each other */
    add_prop(CONT_I_WEIGHT,50000);  /* 102 Kg */
    add_prop(CONT_I_HEIGHT,63);     /* 63 cm */
    add_prop(LIVE_I_SEE_DARK,10);
            /* STR DEX CON INT WIS DIS */
    for (i = 0; i < 5; i++)
        set_base_stat(i, 110 + random(25));
    set_base_stat(5, 70);


    set_alignment(0);
    add_prop(LIVE_I_SEE_DARK,10);

    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_WEP_AXE,90);
    set_skill(SS_PARRY, 70);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_2H_COMBAT, 90);

   /* Actions */
    set_act_time(5);
    add_act("listen attent");
    add_act("watch");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    arm_me();

    set_random_move(8);
    set_restrain_path(ROOM_DIR);

    set_pick_up_team(({"svirfneblin"}));
}


int
query_magic_res(string prop)
{
    if (prop == MAGIC_I_RES_EARTH ||
        prop == MAGIC_I_RES_FIRE  ||
        prop == MAGIC_I_RES_AIR   || 
        prop == MAGIC_I_RES_WATER ||
        prop == MAGIC_I_RES_ILLUSION )
        return 50;
    else
        return 25;
}


void
arm_me()
{
    object arm, wep, gem;

    make_gems(TO, 1);

    arm = clone_object(ARM_DIR + "sv_chainmail");
    arm -> move(TO);
    arm = clone_object(ARM_DIR + "sv_shield");
    arm -> move(TO);
    wep = clone_object(WEP_DIR + "sv_axe");
    wep -> move(TO);

    command("wear all");
    command("wield all");

}
void
init_living()
{
    ::init_living();
    init_team_pickup();
}
