/* The normal guards by Percy. */
/* base file to inherit for all knight npc's by Aridor, 09/94 */
/* modified by Teth and Morrigan, 01/97 */

#include "/d/Krynn/solamn/vin/knight/guild.h"
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>

inherit M_FILE
#include "killer.h"

int sublevel, level, soul_id;
string subtitle, title;
void get_me_soul();

string
set_my_title()
{
    if (!level)
    {
	level = random(2) + 2;
	sublevel = random(5) + 3;
    }
    if (level == 3)
    {
	subtitle = CROWN_TITLES[sublevel];
	return "Order of the Crown";
    }
    else
    {
	subtitle = SQUIRE_TITLES[sublevel];
	return "Knighthood";
    }
}

void
create_knight_npc()
{
    set_my_title();
}

void
create_krynn_monster()
{
    int i;
    add_name("knight");
    set_adj("knight");
    set_extra_long("His tunic is decorated with the symbol of the "+
      set_my_title()+".\n");
    set_race_name("human");
    for (i = 0; i < 6; i++)
	set_base_stat(i, 70 + random(50));
    set_base_stat(5, 150);
    set_skill(SS_BLOCK, 70 + random(30));
    set_skill(SS_KATTACK, 70 + random(30));
    set_skill(SS_WEP_SWORD, 60 + random(40));
    set_skill(SS_PARRY, 60 + random(30));
    set_skill(SS_DEFENCE, 50 + random(25));
    set_skill(SS_2H_COMBAT, 60);
    set_skill(SS_AWARENESS, 50 + random(15));
    set_act_time(random(2) + 1);
    add_act("@@do_rescue");
    set_cact_time(random(2) + 1);
    add_cact("@@do_rescue");
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop("_knight_npc", 1);
    set_alignment(500);
    set_knight_prestige(-2);
    set_aggressive(VBFC_ME("check_if_aggressive"));
    soul_id = set_alarm(0.5, 0.0, &get_me_soul());
    create_knight_npc();
    if (IS_CLONE)
	set_alarm(1.0,0.0,"arm_me");
}

void
attack_func(object enemy)
{
    command("kill "+enemy->query_real_name());
}

void
init_living()
{
    if (interactive(TP) && TP->query_prop("_i_attacked_in_vingaard"))
	set_alarm(0.5, 0.0, "attack_func", TP);
    ::init_living();
}

void
get_me_soul()
{
    TO->add_cmdsoul(KOBJ + "solamnian_soul");
    TO->add_cmdsoul(VOBJ + "kattack_special");
    TO->update_hooks();
    remove_alarm(soul_id);
}

void
arm_me()
{
    seteuid(geteuid(TO));
    clone_object(VARM + "s_armour")->move(TO);
    clone_object(VARM+"s_helm")->move(TO);
    clone_object(VARM+"s_shield")->move(TO);
    clone_object(VWEP + "s_sword")->move(TO);
    command("wear armours");
    command("wield weapon");
}

int
check_if_aggressive()
{
    return TP->query_prop("_i_attacked_in_vingaard");
}

int
query_knight_level() { set_my_title(); return level; }

int
query_knight_sublevel() { return sublevel; }

void
attacked_by(object ob)
{
    if (ob->query_race_name() != "draconian")
	TO->do_rescue();
    ::attacked_by(ob);
}

string
do_rescue()
{
    /* rescue a fellow knight who is currently under attack */
    object *who = FILTER_LIVE(all_inventory(E(TO)));
    object *ene, *good = ({ }), *bad = ({ });
    object person;
    int i;
    who -= ({ TO, 0 });
    ene = who->query_attack();
    for(i = 0;i<sizeof(ene);i++)
	if (who[i] != TO  && (who[i]->id("knight") ||
	    who[i]->query_guild_name_occ() == "Solamnian Knights")
	  && ene[i] && !ene[i]->id("knight") &&
	  ene[i]->query_guild_name_occ() != "Solamnian Knights")
	{
	    good += ({ who[i] });
	    bad += ({ ene[i] });
	}
    if (!good || !sizeof(good))
	return "";
    i = random(sizeof(bad));
    if (!good[i]->id("knight") || random(5))
    {
	if (good[i]->query_hp() < query_hp())
	{
	    attack_object(bad[i]);
	    bad[i]->attack_object(TO);
	    tell_room(E(TO),"The human knight heroically rescues " +
	      QTNAME(good[i]) + ".\n");
	}
    }
    else
    {
	if (E(TO)->not_called_for_help_yet() &&
	  (bad[i])->query_race_name() != "draconian")
	    E(TO)->call_for_help(TO,good[i],bad[i]);
    }
    return "";
}

int
do_sp(object enemy)
{
    TO->command("sp "+enemy->query_name());
}

int
special_attack(object enemy)
{
    do_sp(enemy);
    return 0;
}
