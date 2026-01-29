/*Created by Macker 07/17/94 */

#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "/sys/money.h"
#include "/d/Krynn/icewall/local.h"
inherit "/std/act/domove";
inherit "/std/act/action";


inherit M_FILE

int my_intro(string s1, string s2);
int no_intro = 0;
string *hit_list = ({ });

void
create_krynn_monster()
{
    int i;

  set_name("warrior");
	add_name("human");
        set_race_name("warrior");
        set_living_name("ice folk warrior");
        set_adj("ice");
        add_adj("folk");
        add_adj("master");

set_long("This is the ice folk master warrior. He earned this " +
        "title by defending the village against minotaurs and thanoi with " +
        "his mighty axe wielding abillity.\n");

set_monster_home(VILLAGE + "gathering.c");
set_restrain_path(VILLAGE);
set_random_move(20 + random(20));


        set_stats(({120, 100, 110, 50, 50, 100}));
        set_skill(SS_DEFENCE, 70);
        set_skill(SS_WEP_AXE, 90);

        set_alignment(300);
        set_knight_prestige(-2);

    NEVERKNOWN;

    set_all_attack_unarmed(30, 40);
    set_all_hitloc_unarmed(30);


    set_tell_active(1);

        trig_new("%s 'Help!' 'This' %s 'is' 'attacking' %s", "new_attacker");
/*
        trig_new("%s 'introduces' %s","my_intro");
*/
        set_act_time(10);

        add_act("emote eyes you distrustfully.");
        add_act("emote studies your every move.");
        add_act("emote looks down at the top of your head, wondering " +
        "how deep his axe could slice into it.");
        add_act("emote runs his finger along the edge of his axe, " +
        "remembering what happened to the last stranger " +
        "who entered the village.");
        add_act("say Did you see any minotaurs on your way here? " +
                "How many? Did you kill them?");




    if (IS_CLONE)
      set_alarm(1.0,0.0,"arm_me");
}

erase_no_intro() { no_intro = 0; }

int
my_intro(string s1, string s2)
{
    object *players;
    if (!no_intro)
      {
          set_alarm(2.0,0.0,"command", "emote introduces himself as: " +
		    "\nRaggart Knug, Cleric of the Ice Folk.");
          set_name("raggart Knug");
          add_name("raggart");
          add_name("raggart knug");
          add_name("cleric");
          FILTER_LIVE(all_inventory(TO))->add_introduced("raggart");
          no_intro = 1;
          set_alarm(6.0,0.0,"erase_no_intro");
          return 1;
      }
    return 1;
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


public int
second_life(object killer)
{
        (VILLAGE + "gathering")->remove_master(TO);
        return 0;
}

init_attack()
{
    if (query_hit_list(TP) &&
       (sizeof(FILTER_PLAYERS(all_inventory(E(TO)))) > 0))
      {
          command("say There you are! You will pay for attacking " +
                  "this village!");
          set_alarm(2.0,0.0,"aggressive_attack", this_player());
          return;
      }
    return (::init_attack());
}

void
arm_me()
{
    seteuid(getuid(this_object()));
                tell_room(E(TO), "An ice folk warrior arrives.\n");
        clone_object(PLAINS_O + "" +
                "frostreaver.c")->move(TO);
        clone_object(PLAINS_O + "icy_shield.c")->move(TO);
        clone_object(PLAINS_O + "icy_armour1.c")->move(TO);
    MONEY_MAKE_CC(random(3)+3)->move(TO);
    command("wield weapon");
        command("wear all");


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


