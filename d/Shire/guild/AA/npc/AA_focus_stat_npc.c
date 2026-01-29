/*
   AA statistic monster by Milan
 */

inherit "/w/milan/stat_npc";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include "../guild.h"

void
aa_special_enabled()
{
    set_alarm(0.0, 0.0, &command("focus on defence"));
}

void
kill_command()
{
    if (query_prop(SPEC_ATTACK_IS)) // we wait till previous special resets
    {
    	set_alarm(1.0, 0.0, kill_command);
    	return;
    }
    command("smash "+OB_NAME(oponent));
    //command("focus on defence");
}

void
create_monster()
{
    set_base_stat(6,100);
    set_base_stat(7,100);
    set_base_stat(8,100);
    ::create_monster();
    set_race_name("human");
    set_log_str("AA focus results:\n");
    set_name("soldier");
    set_adj("AA");
}

void
arm_me()
{
    object ob;
    mixed sh = AA_DIR + "shadow/aa_sh_occ";
    int err;

    seteuid(geteuid());

    sh = clone_object(sh);
    if((err = sh->shadow_me(TO, "occupational", GUILD_STYLE, GUILD_NAME)) != 1)
    {
		"secure/master"->do_debug("destroy",sh);
    	tell_room(ENV(TO), "*** shadow_me error: "+err+" ***\n");
    	return;
	}
    add_cmdsoul(AA_DIR + "soul/aa_emotes");
    add_cmdsoul(AA_DIR + "soul/aa_soul");
    remove_cmdsoul("/cmd/std/soul_cmd");
    load_command_souls();

    set_skill(SS_WEP_CLUB,     100);
    set_skill(SS_SHIELD,       100);
    set_skill(SS_SMASH,        100);
    set_skill(SS_BASH,         100);
    set_skill(SS_DEFENCE,      80);
    set_skill(SS_PARRY,        50);
    set_skill(SS_BLIND_COMBAT, 60);
    set_skill(SS_AWARENESS,    60);

    ob = clone_object("/std/weapon");
    ob->set_name("club");
    ob->set_adj("standard");
    ob->set_default_weapon(40, 40, W_CLUB, W_BLUDGEON, W_ANYH);
    ob->set_likely_dull(-500);
    ob->set_likely_break(-500);
    ob->update_prop_settings();
    ob->move(this_object(), 1);

    ob = clone_object("/std/armour");
    ob->set_name("helm");
    ob->set_adj("standard");
    ob->set_ac(40);
    ob->set_at(A_HEAD);
    ob->set_likely_cond(-500);
    ob->set_likely_break(-500);
    ob->update_prop_settings();
    ob->move(this_object(), 1);

    ob = clone_object("/std/armour");
    ob->set_name("shield");
    ob->set_adj("standard");
    ob->set_ac(40);
    ob->set_at(A_SHIELD);
    ob->set_likely_cond(-500);
    ob->set_likely_break(-500);
    ob->update_prop_settings();
    ob->move(this_object(), 1);

    ob = clone_object("/std/armour");
    ob->set_name("mail");
    ob->set_adj("standard");
    ob->set_ac(40);
    ob->set_at(A_BODY);
    ob->set_likely_cond(-500);
    ob->set_likely_break(-500);
    ob->update_prop_settings();
    ob->move(this_object(), 1);

    command("wield all");
    command("wear all");
}
