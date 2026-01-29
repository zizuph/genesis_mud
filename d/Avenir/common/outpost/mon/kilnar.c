//		     kilnar.c
//                   Dwarven guard for the outpost gate
// creator(s):       Cirion, Jan 1996, updated it for the quest.
//                           taken from the normal outpost guards, by Kazz
// revision history: Denis, Jul'96: Removed the usage of triggers for intro.
//		     Denis, Aug'99: Corrected a runtime error in
//				    quest ending code. Some other cosmetic
//				    changes.
//                   Lucius, Jun 2017: Fixed a runtime errors with bad water.
//                   Lucius, Jun 2017: More fixes. Also give out less free tokens.
//
// purpose:          dwarven guards (initially for the outpost)
//                   This one asks you for a glass of water, and
//                   if you bring it, he will reward you. evil_guard
//                   will ask you to poison it, and if you do,
//                   Kilnar will die.

inherit "/d/Avenir/inherit/helper";
inherit "/d/Avenir/inherit/quest";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/inherit/givetask";

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Avenir/common/outpost/water_quest.h"
#include <language.h>
#include <money.h>
#include </sys/ss_types.h>

/* Prototypes */
void     add_gate_talk();
void     reset_wangle();
int      reset_quest();
string   give_task();
void     drop_unwanted(object what, object who);
int      test_quest(object obj, object from);
void     do_good_routine(object water, object player);
void     do_evil_routine(object water, object player);
int      query_busy();
int      unbusy();
void 	 death_actions(object player);

object wangle;
int done_quest, busy, alarm_id, action, tok_alarm, tst_alarm;


void
create_monster()
{
    set_name("kilnar");

    add_name("avenir_dwarf_id");
    add_name("guard");
    set_pname( "guards" );
    add_pname( "dwarves" );
    set_race_name( "dwarf" );
    set_gender(G_MALE);
    set_adj(({"thirsty", "aging"}));
    set_long("He guards the fort and watches all strangers. There "
		+"is sweat on his brow, and he looks like he could "
      +"use a drink.\n" );

    // stats?  50+random(10)
    set_stats(({ 80, 75+random(10), 75+random(10),
	35+random(10), 35+random(10), 75 }));

    set_hp(1000);
    set_alignment(-100+random(200));
    set_monster_home(OUTPOST + "cave2");
    set_title("a guard of the Sybarus outpost");

    set_skill( SS_DEFENSE, 50 );
    set_skill( SS_WEP_AXE, 50 );
    set_skill( SS_WEP_POLEARM, 50 );               // for hammer?
    set_skill( SS_WEP_CLUB, 50 );               // for hammer
    set_skill( SS_BLIND_COMBAT, 50 );
    set_skill( SS_AWARENESS, 50 );

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
	 add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop("_live_m_attack_thief", 1);

    set_cact_time(3+random(3));
    add_cact("emote grumbles: You will die." );
    add_cact("emote says: The Source gives me strength you can't imagine.");
    add_cact("emote says: I will enjoy presenting your heart to the Elves!" );
    add_cact("emote growls at you.");
    add_cact("emote growls: You better leave while you can." );

    add_ask(({"[where] [is] [the] 'sybarus' / 'bazaar'"}),
       "say Its just over the water to the north.", 1);
    add_ask(({"[forbidden] 'city' / 'ziggurat'"}), 
	"say I believe the city is still off-limits to "+
      "Outlanders like you. Unless you have a sybarun coin...", 1);
    add_ask(({"[what] [did] [you] [do] [to] 'wangle'"}), 
		"say Oh, poor Wangle. He thinks I hate and "+
		"insult him. He is so silly sometimes.", 1);
	add_ask(({"[what] [was] [the] 'insult'"}), 
		"say It was nothing, really. Just a passing comment "
      +"about his beard. By the Source, was he mad though!", 1);
	add_ask(({"[do] [you] [want] [a] 'beer' / 'alcohol' / 'wine' / 'mead'"}), 
			"say I gave all that up after me poor mum passed away.",1);
	add_ask(({"[for] [a] 'task' / 'job' / 'water' / 'drink' / 'quest' / 'help'"}), give_task);
	add_ask(({"maivia", "'dark' 'elf' 'leader'", "'leader' [of] [the] 'dark' 'elves'"}),
			"say The High Lords have put out the word that he's out to destroy Sybarus.", 1); 
	add_ask(({"[open] [the] 'gate'"}), "say Just knock on it. If the guards up top "+
			"like the looks of you, they'll open it for you.", 1);

    set_helper_friends( ({}) );                 // help any npc?
    set_helper_actions(({"shout Guards! Help me!",
                         "shout Hold strong! I'm coming!",
		         "say You will die for this!"}));

    if (random(3) > 1)
	clone_object (OBJ +"dw_rhammer")->move(this_object());
    else
	clone_object (OBJ + "dw_raxe")->move(this_object());
    command("wield all");

    clone_object(OBJ + "dw_rchain")->move(this_object());
    clone_object(OBJ + "dw_rhelmet")->move(this_object());
    command("wear all");
    MONEY_MAKE_CC(22 + random(5))->move(this_object());
    MONEY_MAKE_SC(3 + random(5))->move(this_object());
}

void reset_wangle()
{
    if (wangle)
	return;
    // Allow for the possibility that this guard was
    // killed, but wangle was not.

    wangle = find_living("wangle");
    if (wangle)
	return;

    wangle = clone_object(MON + "wangle");
    wangle->equip_me();
    wangle->move_living("away", OUTPOST + "cave2");
}

void
add_gate_talk()
{
    set_chat_time(4+random(2));
    add_chat("I like the heat, but it sure makes me thirsty.");
    add_chat("I can't wait to get back to the islands!");
    add_chat("I wish there was some Source in this dead cave.");
    add_chat("I could really use something to drink.");
    add_chat("That Barort really gets on my nerves sometimes.");
    add_chat("Hmm ... I wish I could just run up to the pub in the port.");
} 

int query_knight_prestige()
{
    return -1;
}

void
give_token(object from)
{
    tok_alarm = 0;

    if (environment(from) != environment(this_object()))
	return;

    object token = clone_object("/d/Avenir/common/obj/syb_coin");
    token->move(from);
    string str = token->short();

    from->catch_msg(QCTNAME(TO) + " digs into a pocket and "+
        "gives you one of his most treasured possessions, " + str + ".\n");
    tell_room(ENV(TO), QCTNAME(TO) + " digs into his pocket "+
        "and gives "+ str +" to " + QTNAME(from) + ".\n", ({ from }));
}

/* ******* The Quest functions: ****** */

int reset_quest()
{
    if(wangle)
	wangle->reset_quest();

    if(done_quest)
    {
	done_quest = 0;
	return 1;
    }
    done_quest = 0;
    return 0;
}

string give_task()
{
    if(query_busy())
	return "";

    busy = 1;
    set_alarm(12.0, 0.0, &unbusy());
    if(done_quest)
    {
	set_alarm(2.0, 0.0, &command("say Well, I was a bit thirsty "
	    +"before, but someone brought me some water."));
	set_alarm(3.0, 0.0, &command("sigh content"));
	set_alarm(4.0, 0.0, &command("say I really have no needs right now. "
	    +"I might want someone to bring me some more a little later, "
	    +"though."));
	return "";
    }

    if(TP->query_prop(GOOD_PROP))
    {
	command("say Yes, some sparkling water would be lovely! "
	  +"Or some juice, even. Just nothing alcoholic.");
	return "";
    }

    if(!TP->test_bit("Avenir",GROUP,BIT))
    {
	TP->add_prop(GOOD_PROP, 1);
	set_alarm(1.0, 0.0, &command("sigh"));
	set_alarm(2.0, 0.0, &command("say These shifts last so long, and "
	    +"it is so hot down here."));
	set_alarm(4.0, 0.0, &command("say The elves have no respect "
	    +"for honest working dwarves like me."));
	set_alarm(6.0, 0.0, &command("say Not that I mind, but I am getting "
	    +"on in years, and these long shifts make me so thirsty..."));
	set_alarm(8.0, 0.0, &command("say Maybe you could find me something to "
	    +"drink?"));
	set_alarm(11.0, 0.0, &command("say Not anything alcoholic, mind you! Its "
	    +"not allowed, and I gave it up years ago."));

	return "";
    }

	 check_group_one(TP, ({0, 0, 0, 0}));
	 return "";
}

public void enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!living(from))
	return;

    if (!tst_alarm &&
	function_exists("query_soft_amount", obj) &&
	function_exists("query_alco_amount", obj))
    {
	tst_alarm = set_alarm(2.0, 0.0, &test_quest(obj, from));
	return;
    }

    if (obj->id("waterskin"))
    {
	set_alarm(1.0, 0.0, &command("say Sorry, "
	    +"but I don't drink from anything that I "
	    +"can't see through."));
    }

    set_alarm(2.0, 0.0, &drop_unwanted(obj, from));
}

void drop_unwanted(object what, object who)
{
    if (!objectp(what))
	return;

    if (!objectp(who))
    {
	what->remove_object();
	return;
    }

    string item = OB_NAME(what),
	   whom = OB_NAME(who);

    if (!tst_alarm)
	command("peer . " + whom);

    if (!command("give "+ item +" to "+ whom))
	command("drop " + item);
}

int test_quest(object obj, object from)
{
    tst_alarm = 0;

    if (obj->query_alco_amount())
    {
	set_alarm(1.0, 0.0, &command("spit"));
	set_alarm(2.0, 0.0, &command("say I gave this swill up years ago?"));
	set_alarm(3.5, 0.0, &command("say Are you trying to get me drunk "
	    +"or something?"));
	set_alarm(4.5, 0.0, &command("drop "+ OB_NAME(obj)));
	set_alarm(5.0, 0.0, &command("glare "+from->query_real_name()));

	return 0;
    }

    if (done_quest)
    {
	set_alarm(1.0, 0.0, &command("say Oh, you brought me some "
	    +"water!"));
	set_alarm(2.0, 0.0, &command("say But someone just brought me "
	    +"some a little while ago."));
	set_alarm(3.0, 0.0, &command("say I'm really not very thirsty "
	    +"anymore."));
	set_alarm(4.0, 0.0, &command("say Sorry for putting you through "
	    +"all the trouble of bringing me some more."));
	set_alarm(4.5, 0.0, &command("drop "+ OB_NAME(obj)));

	tok_alarm = set_alarm(5.0, 0.0, &give_token(from));
	return 0;
    }

    if (from->test_bit("Avenir", GROUP, BIT))
    {
	obj->remove_object();
	set_alarm(1.0, 0.0, &command("say Ahhh, thanks again for the water."));

	if (!random(3) && !tok_alarm)
	    tok_alarm = set_alarm(2.0, 0.0, &give_token(from));

	return 0;
    }

    if (!from->query_prop(GOOD_PROP))
    {
	set_alarm(1.0, 0.0, &command("say Eh? How did you know "
	    +"that I wanted some water?"));
	set_alarm(2.0, 0.0, &command("say As much as I'd like "
	    +"some, I can't drink anything given to me by a stranger."));
	obj->remove_object();
	return 0;
    }

    if(obj->query_prop(POISON_PROP))
	do_evil_routine(obj, from);
    else
	do_good_routine(obj, from);

    return 1;
}

void do_good_routine(object water, object player)
{
    string what = (objectp(water) ? file_name(water) : "something");

    if (!command("drink "+ water->query_name()))
    {
	WRITE_THIS_LOG(QUEST_FILE, "Odd! "+player->query_name()+" gave "
	  + what +" to Kilnar, but he couldn't drink it.\n");

	set_alarm(1.0, 0.0, &command("say Aye! Sorry, but I just "
	    +"can't seem to drink this."));
	set_alarm(2.0, 0.0, &command("say Maybe you could bring me "
	    +"something more suitable?"));

	if (objectp(water))
	    set_alarm(2.5, 0.0, &command("drop "+water->query_name()));

	return;
    }

    set_alarm(0.5, 0.0, &command("say Ahhh! This is just what I needed!"));
    if (player->test_bit("Avenir", GROUP, BIT))
	return;

    player->remove_prop(GOOD_PROP);
    player->remove_prop(EVIL_PROP);

    reward_quest("Bring Water to Kilnar", player, GROUP, BIT, EXP, 
      GOOD_ALIGN, GOOD_PRESTIGE);

    WRITE_THIS_LOG(QUEST_FILE, player->query_name() + " gave "+
	what +": "+EXP+" xp.\n");
}

void do_evil_routine(object water, object player)
{
    if (!wangle)
	reset_wangle();

    if (!command("drink "+water->query_name()))
    {
	string what = (objectp(water) ? file_name(water) : "something");
	WRITE_THIS_LOG(QUEST_FILE, "Odd! "+player->query_name()+" gave "
	  + what +" to Kilnar, but he couldn't drink it.\n");

	set_alarm(1.0, 0.0, &command("say Aye! Sorry, but I just "
	    +"can't seem to drink this."));
	set_alarm(2.0, 0.0, &command("say Maybe you could bring me "
	    +"something more suitable?"));

	if (objectp(water))
	    set_alarm(2.5, 0.0, &command("drop "+water->query_name()));

	return;
    }

    clear_chat();
    clear_cchat();
    action = 0;
    remove_alarm(alarm_id);  // Remove any alarms.
    alarm_id = set_alarm(1.0, 2.0, &death_actions(player));
}

void death_actions(object player)
{
    action++;
    switch(action)
    {
    case 1:
	command("say Ahhh! This is just what I needed!");
	break;
    case 2:
	command("say Wait ... this tastes strange...");
	break;
    case 3:
	command("glare fierce "+player->query_real_name());
	break;
    case 4:
	break;
    case 5:
	if(!wangle)
	    reset_wangle();
	wangle->move_living("southeast", ENV(TO));
	break;
    case 6:
	wangle->command("cackle");
	break;
    case 7:
	command("emote gasps for breath.");
	break;
    case 8:
	wangle->command("say That will teach you to mock " +
			"me, you pathetic wretch.");
	break;
    case 9:
	break;
    case 10:
	command("drop weapons");
	break;
    case 11:
	command("emote stumbles around slightly.");
	break;
    case 12:
	break;
    case 13:
	wangle->command("laugh evil kilnar");
	break;
    case 14:
	break;
    case 15:
	command("emote falls to his knees.");
	break;
    case 16:
	break;
    case 17:
	break;
    case 18:
	command("emote tries to say something, but his voice is gone.");
	break;
    case 19:
	break;
    case 20:
	command("emote falls unconscious to the floor.");
	break;
    case 21:
	if (present(player, ENV(wangle)))
	    wangle->reward(player);
	break;
    case 22:
	heal_hp(-query_max_hp());
	if (present(player, ENV(TO)))
	    do_die(player);
	else
	    do_die(wangle);
	break;

    default:
	remove_alarm(alarm_id);
	alarm_id = 0;
	break; 
    }
    return;
}

int unbusy()
{
    if (!busy)
	return 0;
    busy = 0;
    return 1;
}

int query_busy()
{
    if(busy || query_attack() || sizeof(get_alarm(alarm_id)) )
    {
	command("emote seems to be occupied by something.");
	return 1;
    }
    else
	return 0;
}
