/* A wrestler. Mortricia 920927 */
/*
    Modified: 11 Sep 2003, by Bleys
        - Added the global var reaction and the functions set_reaction()
            and react_to_feat() so that the room this guy stands in
            can initiate an alarm in him. Previously his reaction
            occurred before the actual event that he was reacting to.

    Lucius - Jan 2021
       Make the belt reset so more people can do the quest per-boot.
*/

inherit "/std/monster";
inherit "/std/act/action";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()
#define CAMP_DIR        MORTRICIADIR + "camp/"
#define OUT             CAMP_DIR + "camp_07"
#define ALIGN           0
#define W_DAM           300
#define W_LIM           100
#define W_LIM1          W_LIM +  400
#define W_LIM2          W_LIM +  900
#define THIS_QUEST_NO   3

int check_qring(string sh_desc, int no, object ob);
string reaction;

public void
init_living()
{
    ::init_living();
    add_action("do_wrestle", "wrestle");
}

public void
dress_me(object ob)
{
    if (objectp(ob))
    {
        object otp = this_player();
        set_this_player(TO);
        ob->wear_me();
        set_this_player(otp);
    }
}

public void
create_monster()
{
    if (!IS_CLONE)
        return;

    seteuid(getuid(TO));
    set_name("wrestler");
    set_short("muscular wrestler");
    set_long("@@my_long");
    set_adj("muscular");
    set_race_name("human");
    set_gender(0);

    set_stats(({75,75,75,5,5,20}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(ALIGN);

    set_skill(SS_AWARENESS, 40);
    set_skill(SS_UNARM_COMBAT, 75);
    set_all_hitloc_unarmed(5);
    set_all_attack_unarmed(75, 50);

    set_chat_time(20);
    add_chat("Come on you little creep!");

    set_act_time(3);
    add_act(({"get weight", "smile",  "drop weight"}));

    set_cact_time(10);
    add_cact("fart");

    add_object(CAMP_DIR + "belt", 1, TO->dress_me);
}

public string
my_long()
{
    string str;
    object my_belt;

    str = "It's a muscular human.";
    my_belt = present("belt", TO);
    if (my_belt && my_belt->query_worn() == TO)
    {
	str = str + " He looks very strong.";
    }
    str = BSN(str);
    return str;
}

public int
do_wrestle(string what)
{
    int i;
    int tp_str, w_hp, dam, tp_dis;
    object *enemies, my_belt;

    if (!what || what == "wrestler" ||
	what == "muscular human" || what == "human")
    {
	tp_dis = TP -> query_stat(SS_DIS);
	tp_str = TP -> query_stat(SS_STR);
	if (present("oil", TP))
        {
/* Detect here if a fight is going on with TP and wrestler.
   If so, stop it.
 */
	    if (check_qring("iron ring", THIS_QUEST_NO, TP))
            {
	        enemies = TO -> query_enemy(-1);
	        for (i=0; i<sizeof(enemies); i++)
                {
		    if (enemies[i] == TP)
                    {
		        TO->stop_fight(TP);
		        TP->stop_fight(TO);
		        TO->command("say So you want to wrestle! Ok.");
		        break;
		    }
	        }
	    }
	    write(BSN(
		"The wrestler tries to get a grip of you, but " +
		"his hands slip on the slippery oil. He loses his " +
		"balance and falls on the floor."
	    ));
	    say("While wrestling with " + QCNAME(TP) + " " +
		"the wrestler loses his balance and falls " +
		"on the floor.\n");
	    w_hp = TO -> query_hp();
	    dam = W_DAM + random(tp_str);
	    if (dam > w_hp)
		dam = w_hp - (W_LIM / 2);
	    TO -> reduce_hit_point(dam);
	    w_hp = TO -> query_hp();
	    if (w_hp < W_LIM) {
		write(BSN(
		    "He is so tired that he cannot rise from " +
		    "the floor anymore."
		));
		TO -> command("say I give up! You have won.");
		my_belt = present("belt", TO);
		if (my_belt) {
		    my_belt -> add_prop("q_solver", TP->query_name());
		    my_belt -> remove_prop("blood_stained");
		    TO -> command("remove belt");
		    TO -> command("drop belt");
		}
		return 1;
	    }
	    if (w_hp < W_LIM1) {
		write(BSN(
		      "The wrestler looks rather tired, but he " +
		      "manages to rise.\n"
		));
		say(QCTNAME(TP) + " seems to be an excellent " +
		    "wrestler.\n");
		return 1;
	    }
	    if (w_hp < W_LIM2) {
		write(BSN(
		      "The wrestler looks tired, but is rather " +
		      "quickly up on his feet again.\n"
		));
		return 1;
	    }
	    write(BSN(
	          "The wrestler looks a bit shaken, but is " +
	          "quickly up on his feet.\n"
	    ));
	    return 1;
	} else {
	    write("The wrestler takes a firm grip around your waist.\n");
	    write("You panic and attack him!\n");
	    TP -> attack_object(TO);
	    TO -> command("say Is this what you call a fair fight!");
	    if (tp_dis + tp_str <= 70) {
		write("The wrestler throws you out of his carriage.\n");
		say(QCTNAME(TP) + " is thrown out of the carriage!\n");
		TP -> move_living("south with his head first", OUT);
	    }
	    return 1;
	}
    }
    return 0;
}

int
check_qring(string sh_desc, int no, object ob)
{
    int i, q_no = 0;
    object *ob_arr = all_inventory(ob);

    for(i=0; i<sizeof(ob_arr); i++)
    {
	if (ob_arr[i]->query_short() == sh_desc &&
	    ob_arr[i]->query_prop("q_solver") == ob->query_name() &&
	    ob_arr[i]->query_prop("q_number") == no &&
	    ob_arr[i]->query_worn() == ob)
        {
	    q_no = 1;
	    break;
	}
    }
    return q_no;
}

public void
set_reaction(string react)
{
    reaction = react;
    set_alarm(1.0, 0.0, "react_to_feat");
}

public void
react_to_feat()
{
    command(reaction);
}
