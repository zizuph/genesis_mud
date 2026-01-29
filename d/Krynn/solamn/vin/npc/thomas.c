/* Thomas uth Maer, horse trainer */
/* Vencar 20-09-2003 - made Santos able to sit on his horse again */
#include "../knight/guild.h"
#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>

inherit "/std/act/action";
inherit M_FILE

#include "killer.h"

int query_knight_level() { return 5; }

mapping crest = ([ ]);
mapping colour = ([ ]);
int soul_id;
void get_me_soul();


string query_race_name()
{
    return(calling_function() == "query_presentation" ? "Solamnian" :
      "human");
}

public void
create_krynn_monster()
{
    int i;

    set_name("santos");
    set_living_name("santos");
    set_adj(({"noble","middle-aged"}));
    set_title("Silverblade, the Master of Justice");
    set_gender(0);
    set_introduce(1);
    set_long("This middle-aged man looks every bit the part of nobility. Short, "+
      "straight black hair falls around his angular face, and sharp features. Gentle "+
      "light brown eyes sparkle strangely on the otherwise cold face. He sits "+
      "proudly in the courtyard, instructing Knights on the arts of mounted "+
      "combat, a skill for which they are renowned across Krynn.\n"+
      "His tunic is decorated with the symbol of the Order of the Rose.\n");
    set_race_name("human");
    for (i = 0; i < 6; i++)
    set_base_stat(i, 130 + random(50));

    set_knight_prestige(-9);
    set_alignment(1200);

    set_skill(SS_KATTACK, 120);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_PARRY, 90);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_AWARENESS, 75);
    /* Vencar 20-09-2003 : new steeds require animal handling > 20 */
    set_skill(SS_ANI_HANDL, 80);

    set_skill(SS_RIDING, 100);
    set_skill(SS_MOUNTED_COMBAT, 100);

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(CONT_I_HEIGHT, 190);
    add_prop(CONT_I_WEIGHT, 70100);
    MONEY_MAKE_GC(random(15) + 5)->move(TO);
    soul_id = set_alarm(1.0, 0.0, &get_me_soul());
    set_alarm(1.0,0.0,"arm_me");

    set_act_time(5);
    add_act("ksmooth");
    add_act("kstudy");
    add_act("tend halberd");
    add_act("hcalm");
    add_act("hrub");
    add_act("hrear");
    add_act("hsnap");
    add_act("htug");

    set_default_answer("For some reason, you are ignored.\n");
    add_ask(" [about] [solamnian] 'cavalry'",
      "say The Solamnian Cavalry is an elite force of mounted warriors. It's "+
      "often said that no army on foot has ever withstood a charge of a cavalry "+
      "force.",1);
    add_ask(" [about] [how] [to] 'join'",
      "say To join, you must simply enlist in the Solamnian Cavalry. Of course, "+
      "only Knights may do this.", 1);
    add_ask(" [about] 'horse' / 'horses' / 'warhorse' / 'warhorses'", "say The "+
      "Knights of Solamnia are known for their superior warhorses, and unmatchable "+
      "skill in fighting from horseback.",1);
}
void
get_me_soul()
{
    object horse;

    TO->add_cmdsoul(KOBJ + "solamnian_soul");
    TO->add_cmdsoul(VOBJ + "kattack_special");
    TO->update_hooks();
    remove_alarm(soul_id);

    horse = clone_object(STEED);
    horse->set_short("spirited steel-grey warhorse");
    horse->move(E(TO));
    TO->command("mount horse");

    setuid();
    seteuid(getuid());
    clone_object(KOBJ + "cavalry_npc_shadow")->shadow_me(TO);

}


int
special_attack(object enemy)
{
    TO->charge_special(enemy);
    TO->command("sp "+enemy->query_real_name());

    return 0;
}

void
arm_me()
{
    object cloak;

    restore_object(CREST);
    cloak = clone_object(VARM+"crest_cloak");
    cloak->set_colour(colour["Silverblade"]);
    cloak->set_crest(crest["Silverblade"]);

    clone_object(VARM + "full_armour")->move(TO);
    clone_object(VARM + "s_boots")->move(TO);
    clone_object(VARM + "s_gauntlets")->move(TO);
    clone_object(VARM + "s_helm")->move(TO);
    clone_object(VWEP + "s_halberd")->move(TO);
    cloak->move(TO);
    command("wear all");
    command("wield all");
}

/* due to fact that this npc is designed to be mounted on the horse and
 * that he falls down from it I added masking on this function so
 * he may mount the horse
 */
int
query_knight_sublevel()
{
    return 10;
}

/* Due to this is an npc, I cannot get the set_bit to work,
 * Instead I override the test_bit function. Vencar 20-09-2003
 */
public int
test_bit(string dom, int group, int bit)
{
    if ( (dom == "Krynn") && (group == GUILD_GROUP) && (bit == MEMBER_BIT) )
        return 1;

    return 0;

}
