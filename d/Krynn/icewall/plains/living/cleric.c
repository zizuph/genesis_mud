/* created by Macker 07/29/94 */
/* fixed up by Stevenson for the polar bear quest */


#include "/d/Krynn/common/defs.h";
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <formulas.h>
#include "/d/Krynn/icewall/local.h";
#include "/d/Krynn/guilds/sohm/defs.h"
#define  ICEWALL_I_HIDE_BALANCE    "_icewall_i_hide_balance"


inherit M_FILE


/*prototypes*/
void give_first_exp(object person, object bear);
int my_intro(string s1, string s2);
int my_bow(string s1, string s2);
string my_answer();
string reward_player();

/*an alarm_id*/
int alrm = 0;
int no_intro = 0,
no_bow = 0;

#define GOT_SCROLL "_sohm_received_tusk_scroll"

void
create_krynn_monster()
{
    set_name("cleric");
    set_race_name("human");
    set_living_name("Raggart Knug");
    add_name("raggart_knug");
    add_name("raggart knug");
    add_name("raggart");
    add_name("human");
    add_adj("wise");
    add_adj("clerical");
   
    set_long("This is the cleric of the ice folk. He is the only " +
	     "one on Krynn who has the knowledge to forge ice weapons. He normally " +
	     "makes them for the ice folk warriors to protect the village. " +
	     "Perhaps you could somehow convince him to forge something for you.\n");
   
    set_stats(({30, 50, 30, 100, 100, 30}));
    set_alignment(900);
    set_knight_prestige(-4);
   
    set_default_answer(VBFC_ME("my_answer"));
    add_ask(({"weapons", "weapon", "icy weapon", "icy weapons",
		"ice weapon", "ice weapons", "about weapons", "about weapon",
		"about icy weapons", "about icy weapon", "about ice weapon",
		"about ice weapons"}), ""+
      
	    QCTNAME(TO) + " says: I am very proud of my icy weapons, especially my frostreavers.\n" +
	    QCTNAME(TO) + " says: I am the only one in all of Krynn who knows how to forge them, you know.\n" +
	    QCTNAME(TO) + " smiles proudly.\n" +
	    QCTNAME(TO) + " says: The handles can be a bit slippery, but the weapons are very sharp and can be rather deadly.\n");
    add_ask(({"trade", "how to trade", "about trade", "about a trade",
		"make", "make me a weapon", "make weapon", "make me weapons",
		"forge", "forge me a weapon", "forge weapon", "forge me weapons",
		"make deal", "deal", "give", "give me weapon", "give weapon to me"}), ""+ 
      
	    VBFC_ME("offer_trade"));
    add_ask(({"reward","about reward", "about my reward", "for my reward",
		"for reward", "my reward"}),    
      
	    VBFC_ME("reward_player"));
    add_ask(({"bear","polar bear","about bear",
		"about polar bear"}),VBFC_ME("intro_bearquest"));

    add_ask(({"scroll","spell","teach magic","teach spell","magic",
      "spells"}), VBFC_ME("spell_hint"));
   
    trig_new("%s 'introduces' %s","my_intro");
    trig_new("%s 'bows' %s", "my_bow");
    seteuid(getuid(TO));
   
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    CUTLEFTOVER("head");
    LEFTOVER("tooth"); LEFTOVER("tooth"); LEFTOVER("tooth");
    LEFTOVER("nose");
   
    set_act_time(10);
    add_act("emote stops what he is doing and looks at you curiously.");
    add_act("emote goes on about his business, forging weapons of pure ice.");
    add_act("say At my age, forging icy weapons and armour is all " +
	    "I can do to help protect the village from thanoi.");
    add_act("say I wish I had some new sleeping furs. The ones I have now are almost as old as me.");
    add_act("say I wish we had more warriors who could use my " +
	    "weapons to kill thanoi.");
    add_act("say We regard the polar bear as sacred.");
    add_act("say If only the polar bear would visit our village.");
   
}

string
offer_trade()
{
    command("whisper " + TP->query_real_name() + 
	    " I normally only forge this equipment for our " +
	    "warriors" +
	    " so they can protect our village from the thanoi.");
    set_alarm(2.0, 0.0, "command", "ponder");
    set_alarm(5.0, 0.0, "command", "whisper "
	      + TP->query_real_name() +
	      " Then again, we are a bit short on good warriors " +
	      "these days.");
    set_alarm(6.0, 0.0, "command", "whisper " + TP->query_real_name() +
	      " Maybe you could help us.");
    set_alarm(8.0, 0.0, "command", "whisper " + TP->query_real_name() +
	      " If you prove to me that you are willing to protect our " +
	      "village, and perhaps offer me a trade, I will forge something " +
	      "for you.");
    set_alarm(9.0, 0.0, "command", "smile");
    return("");
}
string *
query_ob(object who)
{
    string * temp = ({ });
    int hides;
    hides = who->query_prop(ICEWALL_I_HIDE_BALANCE);
    while(hides > 0)
    {
	if(hides == 1)
	  if(random(2))
	    temp += ({ "icy_knife" });
	  else
	    temp += ({ "icy_shield" });
	if(hides == 2)
	  if(random(2))
	    temp += ({ "icy_longsword" });
	  else
	    temp += ({ "icy_club" });
	if(hides == 3)
	  if(random(2))
	    temp += ({ "icy_sabre" });
	  else
	    temp += ({ "icy_armour1" });
	if(hides >= 4)
	  temp += ({ "frostreaver" });
	hides = hides - 4;
    }
    who->remove_prop(ICEWALL_I_HIDE_BALANCE);
    return temp;
}

void
answer_hide_number(object from)
{
    command("whisper " + from->query_real_name() + " You have " +
	    "now given me " + from->query_prop(ICEWALL_I_HIDE_BALANCE) + " hides.");
    alrm = 0;
}

void
inform_balance(object from)
{
    if (alrm)
      return;
    alrm = set_alarm(1.0, 0.0, "answer_hide_number", from);
    set_alarm(1.2, 0.0, "command", "whisper " +
	      TP->query_real_name() + " I will gladly reward you " +
	      "what I consider to be fair compensation for the danger " +
	      "you faced while protecting our village.");
    set_alarm(1.4, 0.0, "command", "whisper " + TP->query_real_name() +
	      " All you have to do is " +
	      "ask for your reward, but remember the more thanoi hides " +
	      "you bring me, the greater your reward.");
    return;
}

string
reward_player()
{
    string * reward;
    object obj;
    int i;
    if((VILLAGE + "gathering")->query_all_hit_list(TP))
    {
	command("ack");
	set_alarm(1.0, 0.0, "command",
		  "say Wait a second! You are the " + TP->query_nonmet_name() +
		  " who attacked the village!!!");
	set_alarm(1.2, 0.0, "command", "say And now " +
		  "you want me to give you weapons?!?!");
	set_alarm(1.5, 0.0, "command", "say You're crazy!");
	return "";
    }
    reward = query_ob(TP);
    for(i=0;i<sizeof(reward);i++)
    {
	obj = clone_object(PLAINS_O + reward[i]);
	obj->move(TO);
	command("give " + reward[i] + " to " + TP->query_real_name());
	/* in case the weapon has 'icy_' prefixed, remove that and then give */
	/*Umm...why didn't I just query_name() ??? *duh* */
	command("give " + reward[i][4..] + " to " + TP->query_real_name());
	if (E(obj) == TO)
	{
	    command("drop " + reward[i]);
	    command("drop " + reward[i][4..]);
	}
    }
    if (sizeof(reward))
    {
	command("say There you go.");
	command("say I hope you will use what I " +
		"have given you to kill more thanoi.");
    }
    else
      command("say I owe you nothing as of right now.");
    return "";
}

void
alter_balance(object ob, object from)
{
    TP->add_prop(ICEWALL_I_HIDE_BALANCE, TP->query_prop(ICEWALL_I_HIDE_BALANCE) + 1);
    ob->remove_object();
    inform_balance(TP);
}

void
return_give_thanoi_tusk(object ob, object from)
{
    string who, what;

    object scroll;

    if(this_player()->query_guild_name_occ() != "School of High Magic" &&
       this_player()->query_guild_name_occ() != "Wizards of High Sorcery")
    {
        command("ponder");
        command("say A thanoi tusk, my tribe thanks you for slaying one " +
           "of our foes who plague our village!");
        command("emote stores the tusk under some furs.");
        ob->remove_object();
        return;
    }
    if((this_player()->query_lesser_spells_max() < 1))
    {
        command("say Interesting you bring this to me.");
        command("say A thanoi tusk! My tribe thanks you for slaying one " +
           "of our foes who plague our village!");
        ob->remove_object();
        return;
    }
    if(SOHM_MANAGER->query_scribed_spell(this_player(),"trothgul"))
    {
        command("eyebrow");
        command("say Another thanoi tusk? My thanks for slaying another " +
           "of our thanoi foes who plague our village!");
        command("ponder");
        command("say Although I have nothing further to reward you with.");
        ob->remove_object();
        return;
    }

    if(this_player()->query_prop(GOT_SCROLL))
    {
        command("eyebrow");
        command("say Another thanoi tusk? My thanks for slaying another " +
           "of our thanoi foes who plague our village!");
        command("ponder");
        command("say Although I have nothing further to reward you with.");
        ob->remove_object();
        return;
    }
	
    command("cheer");
    command("say Ah! A thanoi tusk! My tribe thanks you for slaying one " +
           "of our foes who plague our village!");
    command("say Here, as promised a reward for your bravery! May it " +
           "serve you well.");
    command("emote pulls a scroll out from under a fur.");
    this_player()->catch_msg("You are given a furled parchment by Raggart Knug.\n");

    scroll = clone_object("/d/Krynn/common/scrolls/prot_cold_scroll");
    scroll->move(this_player());
    
    this_player()->add_prop(GOT_SCROLL, 1);

    seteuid(getuid());
    
    return;
}

enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (!from)
      return;
    if (ob->id("beargem"))
      give_more_exp(ob, from);
    else if(ob->id("thanoi_hide"))
      set_alarm(1.0, 0.0, "alter_balance", ob, from);
    else if(ob->id("_thanoi_tusk"))
      set_alarm(1.0,0.0, &return_give_thanoi_tusk(ob, from));
    else
      set_alarm(1.0, 0.0, "command", "drop item");
}

erase_no_bow() { no_bow = 0; }
     
     int
     my_bow(string s1, string s2)
{
    if (!no_bow)
    {
	set_alarm(1.0,0.0,"command",  "bow");
	no_bow = 1;
	set_alarm(6.0,0.0,"erase_no_bow");
	return 1;
    }
    return 1;
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
	FILTER_LIVE(all_inventory(E(TO)))->add_introduced(query_real_name());
	no_intro = 1;
	set_alarm(6.0,0.0,"erase_no_intro");
	return 1;
    }
    return 1;
}

string
my_answer()
{
    set_alarm(1.0,0.0,"command","shrug");
    set_alarm(3.0,0.0,"command","say I have absolutely no idea what you are talking about.");
    return "";
}

void
friek_out(object ob)
{
    object * helpers;
    set_alarm(1.2, 0.0, "command", "shout Help! This " +
	      ob->query_nonmet_name() + " " +
	      "is attacking the village!");
    helpers = FILTER_OTHER_LIVE(all_inventory(E(TO)));
    helpers = helpers - ({ TO });
    helpers->aid_folk(ob);
   
}

public void
attacked_by(object who)
{
    command("ack");
    set_alarm(1.0, 0.0, "command", 
	      "say Oh, come on. I am a cleric! Don't hurt me.");
    set_alarm(1.5, 0.0, "friek_out", who);
    ::attacked_by(who);
}

string 
intro_bearquest() 
{
    command("whisper " + TP->query_real_name() 
	    + " The polar bear loves the fish from "
	    + "beyond the salt cave.");
    return "";
}

void 
init_attack()
{
    object person;
    ::init_attack();
    if((TP->query_short() == "polar bear") &&
       (person=TP->ret_follow()) &&
       (E(person) == E(TP))) 
    {
	if (person->test_bit("Krynn",2,17)) 
	  return;
	person->set_bit(2,17);
	person->add_prop("_bear_bit",1);

	give_first_exp( person, TP );
    }
} 

void 
give_more_exp(object ob, object from) 
{
    command("smile happily");
    if (TP->query_prop("_bear_bit") != 1) 
    {
	command("say Thank you!");
	ob->remove_object();
	return;
    }
    set_alarm(3.0,0.0,"command","whisper "
	      + TP->query_real_name()
	      + " You have chosen to aid my people over your own self.");
    set_alarm(5.0,0.0,"command","whisper "
	      + TP->query_real_name()
	      + " For this, I will use the power of the gem to help you!");
    set_alarm(7.0,0.0,"command","emote begins to concentrate.");
    set_alarm(9.0,0.0,"envelop", TP);
    set_alarm(5.0,0.0,"kill_gem",ob);
}

void 
envelop(object from) 
{
    tell_room(E(from),"A warm light rises from the cleric and envelops "
	      + QCTNAME(from) + ".\n", from);
    from->remove_prop("_bear_bit");
    from->add_exp(BEAR_EXP2);

    K_QUEST_LOG("quest", "Bear quest part 2", from, BEAR_EXP2);
   
    from->change_prestige(BEAR_ALIGN * 2);
    from->set_alignment(from->query_alignment() +
			F_KILL_ADJUST_ALIGN(from->query_alignment(),
					    - BEAR_ALIGN));
    from->catch_msg("You feel more experienced.\n");
}

void 
give_first_exp(object person, object bear)
{
    person->catch_msg("You feel a little more experienced.\n");
    person->add_exp(BEAR_EXP1);

    K_QUEST_LOG("quest", "Bear quest part 1", person, BEAR_EXP1);
   
    set_alarm(1.0,0.0,"command","emote begins tracing out "
	      + "strange patterns in the air.");
    set_alarm(5.0,0.0,"bear_glow");
    set_alarm(7.0,0.0,"bear_vanish",bear);
    set_alarm(8.5,0.0,"command","whisper "
	      + person->query_real_name()
	      + " This gem has the power to save my people from");
    set_alarm(8.6,0.0,"command","whisper "
	      + person->query_real_name()
	      + " the brutal savagery of the Thanoi.");
    set_alarm(10.5,0.0,"command","whisper "
	      + person->query_real_name()
	      + " It is also of great value to those seeking evil.");
    set_alarm(11.5,0.0,"command","whisper "
	      + person->query_real_name()
	      + " As your heart dictates, so will your actions be.");
    set_alarm(13.0,0.0,"want_gem");
}

void 
bear_glow() 
{
    tell_room(E(TO),"The polar bear begins to glow.\n\n");
}

void 
bear_vanish(object bear)
{
    tell_room(E(TO),"The light surrounding the polar bear "
	      + "intensifies and suddenly the bear vanishes. On the "
	      + "ground where it stood is a small, glowing gem.\n\n");
    bear->remove_object();
    clone_object(ICE_CAST_O+"beargem")->move(E(TO));
}

void 
kill_gem(object ob) 
{
    ob->remove_object();
}

void 
want_gem() 
{
    command("emote looks at the gem and then "
	    + "looks at you as though he is "
	    + "expecting something.\n");
}

string 
spell_hint()
{
    string what, who;
    if(this_player()->query_guild_name_occ() != "School of High Magic" &&
       this_player()->query_guild_name_occ() != "Wizards of High Sorcery")  
    {
        command("ponder");
        command("say While I am the Revered Cleric of my tribe, I don't think " +
          "there is anything I can teach you on the arts of magic.");
        return "";
    }
    if((this_player()->query_lesser_spells_max() < 1))
    {
        command("emote Ah, young one... I may have something " +
           "you could use to protect you from the " +
           "icy chill of death common to these parts...");
        command("say However you will need to advance in the Arts before you " +
           "are ready to master that spell.");
        command("say Return to my tent when you are more powerful in your craft.");
        command("smile comfort");
        return "";
    } 
    if(this_player()->query_skill(SS_SPELLCRAFT) < 40)
    {
        command("say Ah, young one... I may have something " +
           "you could use to protect you from the " +
           "icy chill of death common to these parts...");
        command("say However you will need to advance in the Arts before you " +
           "are ready to master that spell.");
        command("say Return to my tent when you have improved your spellcraft.");
        command("smile comfort");
        return "";
    }
    if(!SOHM_MANAGER->query_scribed_spell(this_player(),"trothgul"))
    {
        command("ponder");
        command("say To the warm-blooded the cold is amathema.");
        command("say Here in Ice Reach, with the return of white dragons, " +
           "the cold is brother to death.");
        command("say I have a scroll from ancient times, scribed by the " +
           "Ice Plain shamans, that protects from the cold.");
        command("say I will give it to you...");
        command("emote narrows his eyes, his leathery skin wrinkling.");
        command("say Although first you must do something for me.");
        command("say The thanoi of the plains are emboldened by the forces " +
           "of the Dragonarmies, and they plan to war against our tribe.");
        command("say Bring me a tusk of a thanoi, and I will give you this " +
           "scroll of protection.");
        return "";
    }
    command("ponder");
    command("say Sorry, I cannot help you with that.");
    return "";
}

