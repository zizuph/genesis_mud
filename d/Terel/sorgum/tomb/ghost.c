/* A ghost. Mortricia 920720 */
/*

    Modified: 13 June 2003, by Bleys
        - Updated includes.
        - Now logging to the correct quest log.

*/

#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;
inherit "/std/act/seqaction";
inherit "/std/act/domove";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/include/quest_bits.h"

create_monster()
{
    set_name("sandal_ghost");
    add_name("ghost");
    set_living_name("sandal_ghost");
    set_short("strange ghost");
    set_long("A strange looking ghost.  His image is very faded and " +
	     "hard to make out, but it looks like a vagabond.  His clothes " +
	     "are all tattered.  He is wearing a sandal with leather straps " +
	     "on his left foot.\n"
	     );
    set_adj(({"strange", "old"}));
    set_race_name("human");
    set_gender(0);

    set_stats(({100,100,100,100,100,100}));
    set_hp(2800);
    set_alignment(random(50) + 300);
    set_skill(SS_DEFENCE, random(50) + 25);
    set_skill(SS_AWARENESS, random(50) + 25);
    set_skill(SS_UNARM_COMBAT, random(50) + 30);
    set_skill(SS_BLIND_COMBAT, random(60) + 30);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_act_time(10);
    add_act(({"moan sadly", "sniff"}));

    set_chat_time(5);
    add_chat("Oh! I wish I could rest!");
    add_chat("I wish I could find it.");
    set_random_move(20, 1);
    trig_new("%s 'gives' %s", "ring_give");
}

ring_give(s1, s2)
{
    object sandal;

    sandal = present("sandal", TO);

    if (sandal) {
	if (sandal->query_prop("_sandal_finder") == TP->query_name()) {
	    sandal->remove_prop("_sandal_finder");
	    set_alarmv(2.0, -1.0, "right_msg", ({TP}));
	} else {
	    set_alarm(2.0, -1.0, "wrong_msg");
	}
    }
}

wrong_msg()
{
     TO->command("ponder");
     TO->command("say Too bad you are not the one who found it!");
     TO->command("drop sandal");
     tell_room(environment(TO), "The sad ghost departs.\n");
     remove_object();
}

right_msg(object me)
{
    string name;

    name = capitalize(me->query_name());
    TO->command("wear sandal");
    TO->command("smile " + name);
    if (me -> test_bit("Terel", QUEST_SS2_GROUP, QUEST_SS2_BIT)) {
	tell_object(me, "You have done this once! " +
			"Don't you remember?\n");
    } else {
	if (me -> query_exp() <= QUEST_SS2_EXP ) {
	    me -> add_exp(me->query_exp());
        } else {
	    me -> add_exp(QUEST_SS2_EXP);
	}
        me -> set_bit(QUEST_SS2_GROUP, QUEST_SS2_BIT);
        tell_object(me, "You suddenly feel more experienced.\n");
	tell_room(environment(TO), QCTNAME(me) +
	     " has become more experienced.\n", me);
    /*
	write_file(QUEST_LOG, name +
	   " solved the missing sandal quest (" + ctime(time()) + ")\n");
    */
    write_file(QUEST_LOG, TP->query_name() + " found a ghost's " +
        "missing sandal (missing sandal quest) (" +
        ctime(time()) + ")\n");
    }
    tell_room(environment(TO), "The happy ghost departs.\n");    
    remove_object();
}
