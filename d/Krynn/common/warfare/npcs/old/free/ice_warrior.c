/*Created by Macker 07/17/94 */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "/sys/money.h"

inherit M_FILE
inherit "/lib/unique";  

string *hit_list = ({ });

#define ONE_ADJ_OF(x)   (x[random(sizeof(x))])

#define ADJ ({ "grim", "bearded", "stubborn", "weathered", \
    "thoughtful" })

void
create_krynn_monster()
{
    int i;

    set_name("warrior");
    add_name("ice folk");
    set_race_name("human");
    set_adj(ONE_ADJ_OF(ADJ));
    set_short(query_adj(0) + " ice folk warrior");

    set_long("This is one of the ice folk warriors of Icewall Glacier. " +
             "Since the ice folk " +
             "live in such a harsh environment, they need these " +
             "warriors to protect and hunt for their people.\n");


        set_stats( ({ 70 + random(150),65 + random(150),
                75 + random(150), 10 + random(120), 10 + random(120),
                130 }) );
    set_skill(SS_DEFENCE, 40 + random(50));
    set_skill(SS_WEP_SWORD, 40 + random(40));
    set_skill(SS_WEP_AXE, 80 + random(20));
    set_skill(SS_PARRY, 30 + random(60));

    set_alignment(300);
    set_knight_prestige(-2);

    NEVERKNOWN;

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
                  "me!");
          call_out("aggressive_attack", 2, this_player());
          return;
      }
    else if((TP->query_short() == "polar bear")&&
                (sizeof(FILTER_PLAYERS(all_inventory(E(TO)))) > 0))
        {
                command("gasp");
                command("saowy An ice bear graces us " +
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
    clone_unique(PLAINS_O + "frostreaver", 10, PLAINS_O + "icy_sabre")->move(TO, 1); 
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



public void
attacked_by(object ob)
{
object * helpers;
        helpers = FILTER_OTHER_LIVE(all_inventory(E(TO)));
        helpers = helpers - ({ TO });
                helpers->aid_folk(ob);
        ::attacked_by(ob);
}

