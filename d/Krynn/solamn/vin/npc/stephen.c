/* Stephen MarKenin, Knight of the Crown by Morrigan
Made to defend the helpless and innocent bard that
is being killed by undesirables in the Keep. He
comes upon Celeste being attacked, and leaves when
she is safe once again. *grin*
10/12/96
*/

#include "../local.h"
#include "../knight/guild.h"
#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>
inherit "/std/act/action";
inherit VSTD + "knight_base";

#include "killer.h"

int sublevel, level;
string subtitle, title;
object attacker;

string
query_race_name()
{
    return (calling_function() == "query_presentation" ? "Solamnian" : "human");
}

string
set_my_title()
{
    level = 3;
    sublevel = 10;
    subtitle = CROWN_TITLES[sublevel];
    return "Knight of the Crown";
}

create_knight_npc()
{
    int i;

    set_name("stephen");
    set_living_name("stephen");
    set_race_name("human");
    set_title("MarKenin, the Knight of the Crown");
    set_gender(0);
    set_introduce(1);
    set_long("This young, but stern, looking man is a "+set_my_title()+
      ". His moustache, though not as grand as many, is impressive. "+
      "His armour is resplendent, and he is apparently from a wealthy "+
      "family. Golden brown hair flows over his shoulders, and cool "+
      "hawkish green eyes study the surroundings intently.\n"+
      "He is a "+subtitle+".\n");
    set_stats(({180, 180, 180, 140, 140, 140}));
    set_adj("young");
    add_adj("stern");
    set_act_time(3);
    add_act("@@name_attacker");
    set_alignment(800);
    set_knight_prestige(-6);
    set_skill(SS_KATTACK, 125);
    set_skill(SS_BLOCK, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_PARRY, 90);
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_2H_COMBAT, 90);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(CONT_I_HEIGHT, 186);
    add_prop(CONT_I_WEIGHT, 46500);
    MONEY_MAKE_GC(random(15) + 5)->move(TO);
    set_alarm(1.0,0.0,"arm_me");
    set_alarm(3.0, 0.0, "defend_celeste");
    trig_new("%w 'fail' %s", "retry_rescue");
    trig_new("%w 'attacks' %s", "rescue_celeste");
}

string
name_attacker()
{
    if (!attacker)
	return "say I am here to protect the fair Celeste from any "+
	"that may do her harm.";
    else
	return "say It's a good thing I was here to defend Celeste from that "+
	"cowardly "+attacker->query_nonmet_name()+".";
}

void
rescue_celeste()
{
    set_alarm(2.0, 0.0, "command","rescue celeste");
    set_alarm(2.5, 0.0, "define_attacker");
    set_alarm(3.0, 0.0, "do_block");
}

define_attacker()
{
    attacker = TO->query_attack();
}

retry_rescue()
{
    TO->remove_prop("_k_rescue_time");
    set_alarm(1.0, 0.0, "command", "rescue celeste");
}

void
defend_celeste()
{
    command("emote comes running into the room!");
    command("kassist celeste");
    set_alarm(1.0, 0.0, "command", "rescue celeste");
    set_alarm(2.0, 0.0, "define_attacker");
    set_alarm(3.0, 0.0, "command", "say Attacking a defenseless one "+
      "such as this lady is inexcusable! You have thrown away the "+
      "defence afforded you by the Measure, and shall be dealt with "+
      "accordingly.");
    set_alarm(3.5, 0.0, "do_block");
}
do_block()
{
    attacker = TO->query_attack();
    if (attacker->query_average_stat() >= 120)
    {
	command("block south");
	command("block south");
    }
}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(VWEP+"two_handed_sword")->move(TO);
    clone_object(VARM + "full_armour")->move(TO);
    clone_object(VARM + "s_boots")->move(TO);
    command("wield swords");
    command("wear armours");
}

int
special_attack(object enemy)
{

    TO->command("sp");
}

int
query_knight_level() { set_my_title(); return level; }

int
query_knight_sublevel() { return sublevel; }

