/* created by Macker 07/29/94 */
/* fixed up by Stevenson for the polar bear quest */


#include "/d/Krynn/common/defs.h";
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <formulas.h>
#include "/d/Krynn/icewall/local.h";
#include RND_MEET
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
object grease, crystal, glove, icy_sabre, nametag;

void
create_krynn_monster()
{
    set_name("cleric");
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
    
    add_ask(({"sword", "special sword", "magical sword", "sabre",
		"crystaline sabre", "special magic sword", "about sword",
		"about special sword", "about magic sword", "components", 
		"spell components", "about components", "about spell components",
		"sabre quest"}), VBFC_ME("sabre_quest"));
    trig_new("%s 'introduces' %s","my_intro");
    trig_new("%s 'bows' %s", "my_bow");
    seteuid(getuid(TO));
    
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    CUTLEFTOVER("head");
    LEFTOVER("tooth"); LEFTOVER("tooth"); LEFTOVER("tooth");
    LEFTOVER("nose");
    
    set_act_time(5);
    add_act("emote stops what he is doing and looks at you curiously.");
    add_act("emote goes on about his business, forging weapons of pure ice.");
    add_act("say At my age, forging icy weapons and armour is all " +
	    "I can do to help protect the village from thanoi.");
    add_act("say I wish I had some new sleeping furs. The ones I have now are almost as old as me.");
    add_act("say I wish we had more warriors who could use my " +
	    "weapons to kill thanoi.");
    add_act("say We regard the polar bear as sacred.");
    add_act("say If only the polar bear would visit our village.");
    add_act("say I could make you a very special...magical sword...if I had the right spell components.");
    
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
make_sabre()
{
    write("make_sabre() called.\n");
    ({grease, nametag, glove, crystal, icy_sabre})->remove_object();
    
    grease = 0;
    nametag = 0;
    crystal = 0;
    glove = 0;
    icy_sabre = 0;
    if((VILLAGE + "gathering")->query_all_hit_list(TP))
    {
        command("ack");
        set_alarm(1.0, 0.0, "command",
		  "say Wait a second! You are the " + TP->query_nonmet_name() +
		  " who attacked the village!!!");
        set_alarm(1.2, 0.0, "command", "say And now " +
		  "you want me to call upon the powers of Paladine to " +
		  "make you a magical sabre?!?!");
        set_alarm(1.5, 0.0, "command", "say You're crazy!");
	set_alarm(2.5, 0.0, "command", "say There are other ways of " +
		  "acquiring icy sabres, you know.");
	set_alarm(3.5, 0.0, "command", "emote mumbles something under " +
		  "his breath about evil scum.");
	return;
    }
    
    else
    {
	clone_object(PLAINS_O + "crystal_sabre")->move(TO);
	command("emote studies the spell components.");
	set_alarm(1.0, 0.0, "command", "emote " +
		  "puts the big glob of grease, the long icy crystal, " +
		  "and the gnomish name tag inside the blue leather glove." +
		  "The items seem to vanish as the enter the glove.");
	set_alarm(2.0, 0.0, "command", "emote " +
		  "wears the blue leather glove on his right hand.");
	set_alarm(3.0, 0.0, "command", "emote " +
		  "wields the icy sabre in his right hand, gripping it " +
		  "with Kitiara's glove.");
	set_alarm(4.0, 0.0, "command", "emote " +
		  "raises the icy sabre high above his head, and begins " +
		  "to mumble a prayer.");
	set_alarm(5.0, 0.0, "command", "emote " +
		  "is suddenly surrounded by an erie glow of blue light, " +
		  "and the sabre begins to vibrate in his grasp!");
	set_alarm(6.0, 0.0, "command", "emote " +
		  "resumes his prayer as the icy sabre starts to crystalize " +
		  "while he holds it.");
	set_alarm(7.0, 0.0, "command", "emote " +
		  "ends his prayer with a smile and slowly lowers the blade " +
		  "to his side.");
	set_alarm(9.0, 0.0, "command", "give " +
		  "crystaline sabre to " + TP->query_real_name());
	set_alarm(10.0, 0.0, "command", "say " +
		  "The crystaline sabre is now yours. Use it wisely.");
    }
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
      else if(ob->id("sabre_quest_item"))
      {
	  grease = present("grease", TO);
	  glove = present("glove", TO);
	  crystal = present("crystal", TO);
	  nametag = present("nametag", TO);
	  icy_sabre = present("sabre", TO);
	  if(grease&&crystal&&nametag&&glove&&icy_sabre)
	    make_sabre();
	  else
	    set_alarm(1.5, 0.0, "command", "say " +
		      " Thank you. If you bring me the rest of the spell " +
		      "components, I will make you a crystaline sabre.");
      }
      else
	set_alarm(1.0, 0.0, "command", "drop item");
  }


erase_no_bow() { no_bow = 0; }
     
int
my_bow(string s1, string s2)
{
    if (!no_bow)
    {
	set_alarm(1.0,0.0,"command", "bow");
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
	FILTER_LIVE(all_inventory(TO))->add_introduced(query_real_name());
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

string
sabre_quest()
{
    command("whisper " + TP->query_real_name() + " In order to make a magical crystaline sabre, I " +
	    "will need a few things:");
    set_alarm(1.0, 0.0, "command", "whisper " + TP->query_real_name() + " " +
	      "Dragon Highlord Kitiara's lost glove, which you can " +
	      "find somewhere in Solamnia.");
    set_alarm(2.0, 0.0, "command", "whisper " + TP->query_real_name() + " " +
	      "A gnomish name tag.");
    set_alarm(3.0, 0.0, "command", "whisper " + TP->query_real_name() + " " +
	      "Some gully-grease from Xak Tsaroth.");
    set_alarm(4.0, 0.0, "command", "whisper " + TP->query_real_name() + " " +
	      "A piece of crystalized ice.");
    set_alarm(5.0, 0.0, "command", "whisper " + TP->query_real_name() + " " +
	      "And finally, one of my icy sabres.");
    set_alarm(6.0, 0.0, "command", "whisper " + TP->query_real_name() + " If you can find all these " +
	      "components, I will cast a spell with the help of Paladine " +
	      "and make a crystaline sabre for you.");
    set_alarm(7.0, 0.0, "smile");
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
	write_file("/d/Krynn/common/log/quests/bear_quest",
		   extract(ctime(time()),4,15)+" Part 1: "+person->query_name()+"\n");
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
    write_file("/d/Krynn/common/log/quests/bear_quest",
	       extract(ctime(time()),4,15)+" Part 2: "+TP->query_name()+"\n");
}

void 
envelop(object from) 
{
    tell_room(E(from),"A warm light rises from the cleric and envelops "
	      + QCTNAME(from) + ".\n", from);
    from->remove_prop("_bear_bit");
    from->add_exp(BEAR_EXP2);
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
