/*Created by Macker 07/17/94 */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "/sys/money.h"
inherit "/std/act/domove";
inherit "/std/act/action";


inherit M_FILE

string *hit_list = ({ });

void
create_krynn_monster()
{
    int i;

    set_name("warrior");
	add_name("human");
    set_race_name("warrior");
    set_living_name("ice folk warrior");
    set_adj("folk");
    set_adj("ice");

    set_long("This is one of the ice folk warriors. Since the ice folk " +
             "live in such a harsh environment, they need these " +
             "warriors to protect and hunt for the village.\n");

set_monster_home(VILLAGE + "gathering.c");
set_restrain_path(VILLAGE);
set_random_move(20 + random(15));


        set_stats( ({ 70 + random(50),65 + random(50),
                75 + random(50), 10 + random(20), 10 + random(20),
                100 }) );
    set_skill(SS_DEFENCE, 40 + random(10));
    set_skill(SS_WEP_SWORD, 40 + random(40));
        set_skill(SS_PARRY, 30 + random(30));

    set_alignment(300);
    set_knight_prestige(-2);

    NEVERKNOWN;

    set_all_attack_unarmed(30, 40);
    set_all_hitloc_unarmed(30);

    set_tell_active(1);

trig_new("%s 'Help!' 'This' %s 'is' 'attacking' %s","new_attacker");



    set_act_time(10);

    add_act("emote eyes you distrustfully.");
    add_act("emote studies your every move.");
	add_act("say How do I know you are not a spy, an allie of the thanoi?");
    add_act("say Did you see any minotaurs on your way here? " +
            "How many? Did you kill them?");



    if (IS_CLONE)
      set_alarm(1.0,0.0,"arm_me");
}

void
aid_folk(object attacker)
{
    set_alarm(1.5, 0.0, "command", "say How dare you attack our people in " +
	      "our own town! You shall die for this offense!");
    set_alarm(2.0,0.0,"aggressive_attack", attacker);

        return;
}


int
query_hit_list(object who)
{
    int i;
    string whos_nonmet;
    whos_nonmet = who->query_nonmet_name();
    for(i=0;i<sizeof(hit_list);i++)
      if(hit_list[i] == whos_nonmet)
        {
            return 1;
        }
        return 0;
}

int
new_attacker(string s1, string attacker, string s2)
{
        command("hmm");
        hit_list = hit_list + ({attacker});
        return 1;
}

init_attack()
{
    if (query_hit_list(TP) &&
       (sizeof(FILTER_PLAYERS(all_inventory(E(TO)))) > 0))
      {
          command("say There you are! You will pay for attacking " +
                  "this village!");
          call_out("aggressive_attack", 2, this_player());
          return;
      }
    else if((TP->query_short() == "polar bear")&&
                (sizeof(FILTER_PLAYERS(all_inventory(E(TO)))) > 0))
        {
                command("gasp");
                command("saowy An ice bear graces our humble village " +
                        "with " + TP->query_possessive() + " " +
                                "presence!!");
                command("bow bear");
                return;
        }

    return (::init_attack());
}



void
arm_me()
{
    seteuid(getuid(this_object()));
    tell_room(E(TO), "An ice folk warrior arrives.\n");
    clone_object(PLAINS_O + "icy_sabre.c")->move(TO);
    clone_object(PLAINS_O + "icy_shield.c")->move(TO);
    clone_object(PLAINS_O + "icy_armour1.c")->move(TO);
    MONEY_MAKE_CC(random(3)+3)->move(TO);
    command("wield weapon");
    command("wear all");

}

void
do_die(object killer)
{
        command("scream");
        ::do_die(killer);
}

public int
second_life(object killer)
{
	(VILLAGE + "gathering")->remove_warrior(TO); 
	return 0;
}

public void
attacked_by(object ob)
{
object * helpers;
        helpers = FILTER_OTHER_LIVE(all_inventory(E(TO)));
        helpers = helpers - ({ TO });
                helpers->aid_folk(ob);
        ::attacked_by(ob);
}

