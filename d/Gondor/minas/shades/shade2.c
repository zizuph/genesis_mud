/* 
 *	A standard member of the Shades
 */
#pragma strict_types

inherit "/d/Gondor/minas/shades/team.c";
inherit "/d/Gondor/common/lib/logkill.c";

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define SADJ ({ "sinister", "malicious", "evil", "sneaky", "angry" })

public void
create_monster()
{
    int ran = random(5);
    set_name("human");
    set_race_name("human");
    add_name(({ "shade", "thief", "assassin", "man", }));
    set_adj(SADJ[ran] + " dark-robed");
    set_short(SADJ[ran] + " dark-robed man");
    set_pshort(SADJ[ran] + " dark-robed men");
    set_long("The slender man is clad in black clothes, and he is wearing\n"+
    "a cloak over his shoulders. Grey, narrow eyes follow you\n"+
    "closely and suspiciously when you move around.\n");
    set_alignment(-150);

    default_config_npc(40 + random(30));
    set_base_stat(SS_CON, 60 + random(30));
    set_base_stat(SS_DEX, 75);
    set_skill(SS_WEP_KNIFE, 75);
    set_skill(SS_WEP_SWORD, 60);
    set_skill(SS_BLIND_COMBAT, 60);
    set_skill(SS_2H_COMBAT, 60);
    set_skill(SS_DEFENCE, 65);
    set_skill(SS_PARRY, 65);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_OPEN_LOCK, 50+random(50));
    set_skill(SS_PICK_POCKET, 50+random(50));
    set_skill(SS_ACROBAT, 50+random(50));
    set_skill(SS_SNEAK, 60+random(50));
    set_skill(SS_HIDE, 60+random(50));
    set_skill(SS_BACKSTAB, 90);
    set_aggressive(1);
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_act_time(15);
    add_act("grin");
    add_act("snicker");
    add_act("chuckle");
    add_act("peek all");
    set_cchat_time(7);
    add_cchat("You won't beat the Shades!");
    add_cchat("Alright you bastard. Now you've pissed me off!");
    add_cchat("I hope my poison feels good!");
    add_cchat("I can't wait to loot your corpse, but a loser like you is "+
    "probably broke.");
    add_cchat("Wait till Talin hears of this. You will regret you were born!");
}

public void
arm_me() 
{
    FIX_EUID;

    clone_object(SHADES_DIR + "obj/shadesword")->move(TO);
    clone_object(SHADES_DIR + "obj/poisoned_dagger")->move(TO);
    command("wield all");  
    clone_object(SHADES_DIR + "obj/ablackcloak")->move(TO);
    clone_object(SHADES_DIR + "obj/atunic")->move(TO);
    clone_object(SHADES_DIR + "obj/atrousers")->move(TO);
    clone_object(SHADES_DIR + "obj/aboots")->move(TO);
    command("wear all");

    MONEY_MAKE(random(30) + 10, "silver")->move(TO);
    MONEY_MAKE(random(3) + 1, "gold")->move(TO);
}

public int query_knight_prestige() { return 300; }
