/* A witch. Mortricia 920720 */
/*
    Modified: 13 June 2003, by Bleys
        - Updated to modern includes.
        - Now logging to the right logfile.

*/

#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/include/quest_bits.h"

#define HOME_DIR        "/d/Terel/silver/cottage/"

public void
create_monster()
{
    set_name("ragata");
    add_name("witch");
    set_pname("witches");
    set_living_name("ragata");
    set_short("old witch");
    set_pshort("old witches");
    set_long("A bitchy old witch. All her clothes are black.\n");
    set_adj(({"bitchy", "old"}));
    set_race_name("human");
    set_gender(1);

    set_stats(({100,100,100,100,100,100}));
    set_hp(1000);
    set_mana(1000);
    set_alignment(random(50) - 300);
    set_skill(SS_DEFENCE, random(10) + 25);
    set_skill(SS_AWARENESS, random(10) + 25);
    set_skill(SS_WEP_KNIFE, random(10) + 30);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_act_time(10);
    add_act(({"spit", "grin"}));

    set_chat_time(5);
    add_chat("Woe betide you!");
    add_chat("Beware, I might turn you into a toad.");
    add_chat("My grandmother was also a witch, but she was burned " +
	     "at the stake.");
    add_chat("I wish I had my grandmother's magic ring.");
    add_chat("I need some droppings of a bat for my love potion.");
    add_chat("If you'd get it, I'd be very glad."); 

    trig_new("%s 'gives'  %s", "ring_give");
    trig_new("%s 'introduces' %s", "intro_me");

    seq_new("do_stream");
    seq_addfirst("do_stream", ({"@@dress_me"}));
}

public void
dress_me()
{
    seteuid(getuid());
    
    clone_object(HOME_DIR + "cloak")->move(TO);
    clone_object(HOME_DIR + "hat")->move(TO);
    clone_object(HOME_DIR + "knife")->move(TO);
    command("wear armours");
    command("wield knife");
}

public void
close_shut()
{
    command("close door");
    command("lock door with key");
}

public void
wrong_msg()
{
    command("ponder");
    command("say This ring is of no use to me!");
    command("drop ring");
}

public void
wrong_msg2()
{
    command("ponder");
    command("say This batguano is too stale, I can't use it!");
    command("drop batguano");
}

public void
right_msg(object me)
{
    string name;

    if (!me || ETO != environment(me)) return;

    name = me->query_real_name();
    command("wear ring");
    command("smile " + name);
    if (me -> test_bit("Terel", QUEST_WIT_GROUP, QUEST_WIT_BIT)) {
	tell_object(me, "You have done this once! " +
			"Don't you remember?\n");
    } else {
	if (me->query_exp() <= QUEST_WIT_EXP ) {
	    me->add_exp(me->query_exp(), 0);
        } else {
	    me->add_exp(QUEST_WIT_EXP, 0);
	}
        me->set_bit(QUEST_WIT_GROUP, QUEST_WIT_BIT);
        me->catch_msg("You suddenly feel more experienced.\n");
	tell_room(ETO, QCTNAME(me) +
	     " has become more experienced.\n", me);
	seteuid(getuid());
    /*
	write_file(QUEST_LOG, capitalize(name) +
	   " solved the witch quest (" + ctime(time()) + ")\n");
    */
    write_file(QUEST_LOG, TP->query_name() + " solved " +
        "the witch's ring quest (witch quest) (" +
        ctime(time()) + ")\n");
    }
}

public void
right_msg2(object me)
{
    string name;

    if (!me || ETO != environment(me)) return;
    
    name = me->query_real_name();
    command("smile " + name);
    if (me->test_bit("Terel", QUEST_JJ5_GROUP, QUEST_JJ5_BIT)) {
	tell_object(me, "Sorry, too late! Someone a bit quicker than you " +
	"brought me sufficient amounts of droppings from a bat. \n");
    } else {
	if (me->query_exp() <= QUEST_JJ5_EXP ) {
	    me->add_exp(me->query_exp(), 0);
        } else {
	    me->add_exp(QUEST_JJ5_EXP, 0);
	}
        me->set_bit(QUEST_JJ5_GROUP, QUEST_JJ5_BIT);
        me->catch_msg("You get a tingly feeling, things seems more " +
                      "clear now.\n");
	tell_room(ETO, QCTNAME(me) +
	     " looks more experienced.\n", me);
	seteuid(getuid());
    /*
	write_file(QUEST_LOG, name +
	   " solved the batshit quest (" + ctime(time()) + ")\n");
    */
    write_file(QUEST_LOG, TP->query_name() + " solved " +
       "the bat guano quest (batshit quest) (" +
       ctime(time()) + ")\n");
    }
}

public void
ring_give(string s1, string s2)
{
    object ring = present("ring", TO);
    object batshit = present("batguano", TO);
    
    if (batshit) {
        if (batshit->query_prop("_shit_picker") == TP->query_name()) {
	    batshit->remove_prop("_shit_picker");
	    set_alarm(2.0, -1.0, &right_msg2(TP));
	    batshit->remove_object(); 
	} else {
	    set_alarm(2.0, -1.0, wrong_msg2);
	}
    }
    
    if (ring) {
	if (ring->query_prop("_skull_finder") == TP->query_name()) {
	    ring->remove_prop("_skull_finder");
	    set_alarm(2.0, -1.0, &right_msg(TP));
	} else {
	    set_alarm(2.0, -1.0, wrong_msg);
	}
    }
}

public void
do_intro(object who)
{
    if (!who || environment(who) != ETO) return;
    
    command("introduce me to " + who->query_real_name());
}

public void
intro_me(string s1, string s2)
{
    object who = present(lower_case(s1), ETO);
    
    if (who->query_npc() || !CAN_SEE(TO, who)) return;
    
    set_alarm(2.0, -1.0, &do_intro(who));
}
