/* Npc trainer for the Union
 *
 * Revisions:
 * 	Lucius, Jul 2017: Re-Code.
 *
 */
#pragma strict_types

#include "../defs.h"
inherit (NPC + "npc");

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

public void
create_monster()
{
    set_name("riyligan");
    set_living_name("riyligan");
    set_race_name("elf");
    set_adj("forgotten");

    set_long("A forgotten legend of lost times, this epitome of "+
	"shadows has resided in darkness for aeons.\n");

    set_union_npc();

    set_base_stat(SS_OCCUP, 300);
    set_stats(({ 94, 200, 105, 65, 61, 94 }));

    set_gender(G_MALE);
    set_appearance(75);

    set_skill(SS_LANGUAGE,     100);
    set_skill(SS_WEP_KNIFE,     99);
    set_skill(SS_PARRY,         85);
    set_skill(SS_WEP_MISSILE,  100);
    set_skill(SS_ACROBAT,       80);
    set_skill(SS_AWARENESS,     85);
    set_skill(SS_DEFENCE,       90);
    set_skill(SS_UNARM_COMBAT,  94);
    set_skill(SS_SWIM,          30);
    set_skill(SS_CLIMB,         61);
    set_skill(SS_LOC_SENSE,     80);
    set_skill(SS_HERBALISM,     91);
    set_skill(SS_LOC_SENSE,     54);
    set_skill(SS_SWAY,          90);
    set_skill(SS_FLING,        100);
    set_skill(SS_SLASH,        100);

    set_alignment(-1000);

    set_act_time(35);
    add_act("emote seems to move slightly.");

    set_all_attack_unarmed(30, 20);
    set_all_hitloc_unarmed(30);
}

private void
leave(void)
{
    command("emote seems to disintigrate before you.");
    remove_object();
}

public void
attacked_by(object who)
{
    set_alarm(1.0, 0.0, leave);
    ::attacked_by(who);
}

/*
 * Mask these from regular union npc's to avoid problems.
 */
public void init_living() { }
public void add_introduced(string str) { }
public void summon_for_union_ceremony(object where) { }
public void respect(object who) { }
public void return_ectios(object who) { }
public void union_hook_got_ectios(object who) { }

