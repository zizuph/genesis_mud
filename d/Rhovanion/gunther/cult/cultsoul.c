'
/*
 * cultsoul.c
 *
 * Cult of Melkor guild soul 
 * Based in part on the Spellweaver soul by Farlong.
 * Gunther 940716
 *
 */

inherit "/cmd/std/command_driver";

#include "guild.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <composite.h>
#include "/d/Rhovanion/defs.h"

#define WIZLEV_APPRENTICE 1
#define SOULEXTRA(x)		TP->change_prop(LIVE_S_SOULEXTRA, x);

string
get_soul_id()
{
   return CULT_NAME;
}

int
query_cmd_soul()
{
   return 1;
}

/* Test to see if someone is a member*/
/* Returns 1 if yes; 0 if not. */

int
is_member(mixed who)
{
    object ob;
    if (!who)
        return 0;
    if (stringp(who))
        ob = find_player(lower_case(who));
    else if (objectp(who))
        ob = who;
    else
        return 0;
    if (!ob || !interactive(ob))
        return 0;
    if (ob->query_guild_member(CULT_NAME))
        return 1;
    return 0;
}


/*
 * List of verbs & functions (Alphabetical)
 */

mapping
query_cmdlist()
{
   return([
   		"amplify"	: "amplify",
   		"cast"		: "cast",
   		"command" 	: "command",
   		"cont_sacr" : "continue",
   		"distaste"	: "distaste",
   		"ecstatic"  : "ecstatic",
   		"favor"		: "favor",
   		"granted"	: "granted",
   		"gesture"   : "gesture",
   		"help"		: "help",
			"members" 	: "members",
			"mess_tell"	: "mess",
			"mess_tell" : "message",
			"obey"    	: "obey",
			"offering"	: "offering",
			"perform"	: "perform",
			"reconsider": "reconsider",
			"revenge"	: "revenge",
			"submit"  	: "submit",
			"tongues"	: "tongues",
			"trace"		: "trace"
	]);
}

int
amplify(string str)
{  
	int manad, gs;
	status am;
	NF("You can <amplify little> or <amplify much>.\n");
	if(str != "little" && str != "much") return 0;
	if(str == "little") am = 0; else am = 1;
	
	/* trade 1 favor point for 1 mana point */
	/* little = 1* guildstat */
	/* much = 4 * guildstat */
	
	gs = TP->query_base_stat(SS_OCCUP);
	if(am) gs *= 4;
	
	manad =TP->query_max_mana() - TP->query_mana();
	if( manad < gs) TP->add_mana(manad);
	else TP->add_mana(gs);
	
	if(TP->add_some_favor(-1 * gs))	/* if not ; wrath of Melkor   B^)=  */
		write("You daringly ask Melkor for more mana and He grants it to you.\n");
	return 1;
}

int
cast(string str)
{
	/* cast a spell */
	object spellbook;
	
	spellbook = present("spellbook", all_inventory(TP));
	NF("You seem to have lost communication with Melkor, please"
		+" report it to the wizard guildmaster.\n");
	if(!spellbook) return 0;
	
	NF("Cast what?\n");
	return call_other(spellbook, str);
}

int
command(string str)
{
	object command_obj;
	
	NF("Command what?\n");
	if(strlen(str)) return 0;
	
	command_obj = present("_cult_command_obj", all_inventory(TP));
	NF("You have a serious flaw in you making you unable to receive"
		+" commands from Melkor. Please report it as soon as possible to"
		+" the wizard guildmaster.\n");
	if(!command_obj) return 0;
	
	command_obj->show_command();
}

int
cont_sacr(string str)
{
	object sacrifice_obj;
	
	NF("Continue what?\n");
	if(str != "rite" && str != "ritual" && str != "sacrifice") return 0;
	
	sacrifice_obj = present("_cult_sacrifice_obj", all_inventory(ENV(TP)));
	NF("There is no sacrifice going on here.\n");
	if(!sacrifice_obj) return 0;
	
	sacrifice_obj->goto_next_stage(TP);
}

int
distaste(string str)
{
    object *oblist;
    
    if(!strlen(str))
    {
		write("You show your distaste for all that is good and weak.\n");
		allbb(" shows "+HIS(TP)+" distaste for the good and the weak.");
		return 1;
    }
    oblist=parse_this(str, "[at] %l");
    NF("Show distaste for whom?\n");
    if (!sizeof(oblist))
		return 0;
    target(" shows distaste for the goodness in your soul.", oblist);
    actor("You show your distaste for the goodness in", oblist);
    all2act("shows distaste for the goodness in", oblist);
    return 1;
}

int
ecstatic(string str)
{
	NF("Ecstatic what?\n");
	if(strlen(str)) return 0;
	
	write("You grin ecstatically as you raise your bloodied hands above your head.\n");
	allbb("grins ecstatically as " + HE(TP) + " raises " + HIS(TP) + " bloodied hands"
		+" above " + HIS(TP) + " head.\n");
	return 1;
}

int
favor(string str)
{
	int mf, cf;
	float f, uf;
	string mess, a, b;
	
	/* check if the player is in Melkor's favor */
	mf = TP->calculate_max_favor();
	cf = TP->query_favor_points();
	f = cf / mf;
	uf = f;
	if(f < 0) { b = "dis"; uf *= -1; } else b = "";
	
	a = "You feel that Melkor is";
	b = " " + b + "pleased with you.\n"
	
	if(uf > 0.9) mess = a + " incredibly" + b;	else
	if(uf > 0.8) mess = a + " extremely" + b;	else
	if(uf > 0.7) mess = a + " very" + b;			else
	if(uf > 0.6) mess = a + " clearly" + b;		else
	if(uf > 0.5) mess = a + " quite" + b;		else
	if(uf > 0.4) mess = a + " rather" + b;		else
	if(uf > 0.3) mess = a + b;						else
	if(uf > 0.2) mess = a + " a little" + b;	else
	if(uf > 0.1) mess = a + " marginally" + b;	else
	mess = "You feel that Melkor is studying you, apprehensive of your actions.\n";
	
	write(mess);
	say(QCTNAME(TP) + " looks thoughtful for a moment.\n");
}

int
gesture(string str)
{
	/* needs to be modified to check seen/unseen */
	object *people, *spellweavers;
	int i;
	string m1, m2;
	    
	people = FILTER_OTHER_LIVE(all_inventory(ENV(TP)));
	spellweavers = filter(people, "is_member", TO);
	people -= spellweavers;
	    
	NF("You must specify a gesture to make.  Type help gestures to list them.\n");
	if(!strlen(str)) return 0;
	    
	NF("Make what gesture?\n");
	switch(str) {
		case "greetings" :
			m1 = "of greeting.";
			m2 = m1;
			break;
		case "flee" :
			m1 = "urging your fellow guildmembers to flee!";
			m2 = "urging you to flee!";
			break;
		case "attack" :
			m1 = "calling for an attack!";
			m2 = m1;
			break;
		case "agree" :
			m1 = "signifying your agreement.";
			m2 = "signifying " + HIS(TP) + " agreement.";
			break;
		case "negative" :
			m1 = "to the negative.";
			m2 = m1;
			break;
		case "adieu" :
			m1 = "bidding your fellows `Goodbye.'";
			m2 = "bidding you `Goodbye.'";
			break;
		case "help" :
			m1 = "requesting help.";
			m2 = "requesting your help.";
			break;
		case "victory" :
			m2 = "showing " + HIS(TP) + " confidence in victory.";
			m1 = "showing your confidence in victory.";
		default : return 0;
	}
	    
	if(TP->query_get_echo())
		write("You make a Cult gesture "+m1+"\n");
	else
		write("Ok.\n");
	
	if(sizeof(spellweavers))
		spellweavers->catch_msg(QCTNAME(TP) + "makes a gesture "
			+ m2 + "\n", TP);
	if(sizeof(people))
		people->catch_msg(QCTNAME(TP)+" makes a slight curious gesture.\n", TP);
		
	return 1;
}

int
granted(string str)
{
	int fp, i;
	string mess;

	NF("Granted what?\n");
	if(strlen(str)) return 0;
	
	mess = "Melkor will currently grant you the following spells:\n");
	
	fp = TP->query_favor_points();
	for(i = 0; i < sizeof(FP_SPELLS); i++)
		if(fp > FP_SPELLS[i])
			mess += ALL_SPELLS[i] + "\t" + SPELL_DESCRIPT[i] + "\n";
	
	write(mess);
	say(QCTNAME(TP) + " studies the sky.\n");
}	

int
help(string str)
{
	if(str == "cult") {
	write("These are the commands you have as a member of the Cult of Melkor.\n"
		+"amplify       : ask Melkor to increase your mana. He does not like doing so\n"
		+"cast <spell>  : ask Melkor to cast a spell through you\n"
		+"command       : show the command Melkor has placed on you, if any\n"
		+"continue rite : continue with a ritual sacrifice, if you lead it\n"
		+"distaste      : show distaste for all that is good and weak\n"
		+"ecstatic      : live out the joy of the occasion\n"
		+"favor         : feel how much in Melkor's favor you are\n"
		+"gesture       : make a gesture conveying information\n"
		+"granted       : a list of the spells Melkor will grant you\n"
		+"help cult     : this message\n"
		+"help ritual   : obtain help on how the sacrifice is performed\n"
		+"help favor    : obtain help on how to gain the favor of Melkor\n"
		+"help gestures : a list of gestures used in the Cult\n"
		+"members       : a list of the currently playing members of the Cult\n"
		+"message/mess  : send a mental message to another member\n"
		+"obey          : command someone to obey you\n"
		+"offering      : offer a devotion to Melkor\n"
		+"perform rite  : initiate/join a ritual sacrifice\n"
		+"reconsider    : brave the wrath of Melkor asking Him to make you a Disciple\n"
		+"revenge       : promise someone revenge"
		+"submit        : submit to someone else's will\n"
		+"tongues       : chant in tongues in devotion\n"		
		+"trace         : thoughtfully trace the outline of your brand\n"
		);
	}
	else if(str == "ritual") {
	write("The ritual of sacrifice is the oldest known way of worshipping Melkor."
		+" It can be held by a single priest, but the effect is increased if more"
		+" than one Cult member is present. The objects sacrificed are body parts"
		+" of slain enemies.\n"
		+"One priest is chosen to officiate the rite. He must first insure that he"
		+" is in possession of a brazier, and that it is lit. A ritual knife and a"
		+" pair of thongs are useful too, but not needed. He may start the rite by"
		+" doing <perform rite>. Any others who wish to join in the sacrifice"
		+" may also do <perform rite> after this. After all worshippers have joined"
		+" in the ritual, the officiating priest may <continue rite>. Now the actual"
		+" sacrifice starts. During the entire rite, the worshippers are usually in"
		+" trance, chanting praise to Melkor.\n"
		+"The sacrifice is done with the officiating priest taking all body parts held"
		+" by the other worshippers and himself and burning them on the brazier while"
		+" dividing them into small parts.\n" 
		+"After the sacrifice is finished Melkor will judge the worshippers if He choses"
		+" to.\n");
	}
	else if(str == "favor") {
	write("As a member of the Cult, you should always strive for the favor of Melkor."
		+" You can gain His favor by obeying his commands, holding ritual sacrifice for"
		+" Him and by spreading evil in the land. Likewise, you may loose favor by"
		+" not obeying His commands, and irritating Him. If Melkor is too much displeased"
		+" with you, He will throw you out of the Cult and kill you.\n"
		+"You can feel yourself to see how pleased Melkor is with you at any time by"
		+" doing <favor>.\n");
	}
	else if(str == "gestures") {
	write("The early worshippers of Melkor were not an organized society like we are"
		+" today. They were forced to hide from the leaders of the land and the populace"
		+" generally disliked them. Therefore they developed a system through wish they"
		+" could exchange information by slight gestures while idly conversing the weather.\n"
		+"Today many of the gestures have fallen out of use as the Cult members freely"
		+" speak with each other, but some still remain.\nThe following gestures are available:\n"
		+"attack        : make a sign calling for attack\n"
		+"adieu         : bid farewell to a fellow Cult member\n"
		+"agree         : signify agreement\n"
		+"flee          : urge your fellow Cult members to retreat\n"
		+"greeting      : greet a fellow Cult member\n"
		+"help          : request help\n"
		+"negative      : make a sign to the negative\n"
	   +"victory       : make a sign of victory\n");
	}
	return 0;
}

int
members()
{
  string sh_name, sh_title, str;
  int i, cnt, lsize;
  object player_ob, active, *list;

  list = filter_array(users(),"is_member",this_object());
  lsize = sizeof(list);
  cnt = 0;

  write("You incant a prayer of seeing and the"
	+" faces of the following members appear before you:\n");
  say(QCTNAME(TP) + " incants a prayer.\n");

  for (i=0; i < lsize; i++) 
  {
    str = "";
    player_ob = list[i];

    {
      /* Everyone knows one another in the guild */
      if (!(sh_name = player_ob->query_name()))
            sh_name = "";

      if (!(sh_title = player_ob->query_title()))
            sh_title = "";

      str = sh_name + " " + sh_title;

      if (player_ob->query_ghost())
        str += " <dead>";

      /* Mark invisible players for wizards */
      if (player_ob->query_invis() &&
        this_player()->query_wiz_level() >= WIZLEV_APPRENTICE)
      str = "(" + str + ")";
      cnt++;      /* Increment for another member */

      this_player()->catch_msg("--> " + str + "\n");
    }
  }
  write("There are currently "+cnt+" worshippers in the game.\n");
  return 1;
}

int
mess_tell(string str)
{
	string name, message;
	object ob;
	
	NF("Send what message to whom?\n");
	if(!parse_command(str, TP, "%w %s", name, message)) return 0;
	
	ob = find_player(name);
	NF("You couldn't locate that person.\n");
	if(!ob) return 0;
	
	NF("You can't send a mental message to a non-member!\n");
	if (!ob->query_guild_member(GUILD_NAME)) return 0;
	
	NF("That person is in a state of business and cannot receive your message.\n");
	if((ob->query_prop(WIZARD_I_BUSY_LEVEL))&156) return 0;

	/* skill check */
	NF("Your spell of sending failed.\n");
	if(resolve_task(SS_ROUTINE, SS_SPELLCRAFT, SS_INT) <= 0) return 0;
	
	ob->catch_msg("The shadows whisper a message from " + QTNAME(TP) + ",
					+"saying:\n" + message + "\n");
	if (TP->query_get_echo()) 
		write("You send these thoughts to " + QTNAME(ob) + ":\n" + message + "\n");
	else
		write("Ok.\n");
	if(!(TP->query_wiz_level()))
		TP->set_mana(TP->query_mana()-10);
	return 1;                          
}

int
obey(string str)
{
	object *oblist;
	    
	if(!strlen(str))
	{
		write("You command that everyone should obey your wishes.\n");
		allbb(" commands that you obey "+HIS(TP)+" wishes.");
		return 1;
	}
	
	oblist = parse_this(str, "[at] %l");
	NF("Command whom to obey you?\n");
	if (!sizeof(oblist))	return 0;
	
	target(" commands that you obey "+HIS(TP)+" wishes.", oblist); 
	actor("You command that your will be obeyed by", oblist);
	all2act("commands that "+HE(TP)+" will be obeyed by", oblist);
	return 1;
}

int
offering(string str)
{
    NF("What?\n");
    if(strlen(str)) return 0;
    write("You offer a devotion to Melkor.\n");
    allbb(" offers a devotion to dark powers.");
    return 1;
}

int
perform(string str)
{
	object *stuff, brazier, *organs, sac_ob;
	
	NF("Perform what?\n");
	if(str != "rite" && str != "ritual" && str != "sacrifice") return 0;
	
	/* ok, either this guy is the first in the room to start the sacrifice,
		or he isn't */
	sac_ob = present("_cult_sacrifice_obj", ENV(TP));
	stuff = all_inventory(TP);
	organs = filter(stuff, "is_organ");
	if(!sac_ob)
	{
		NF("You don't have a brazier!\n");
		brazier = present("_cult_brazier", stuff);
		if(!brazier) return 0;
		
		NF("Your brazier isn't lit.\n");
		if(!brazier->query_prop(OBJ_I_HAS_FIRE)) return 0;
		
		seteuid(getuid(TO));
		sac_ob = clone(CULT_DIR + "sacrifice_obj");
		sac_ob->move(TO);
	}
	sac_ob->add_sacrifice(TP, organs);
}	

int
reconsider(string str)
{  
	string *names, instr;
	int *dpoints, mydp;      
	int n, o, m, x;
	
	NF("Reconsider what?\n");
	if(strlen(str)) return 0;
	names = allocate(GM_FILE_SIZE);
	dpoints = allocate(GM_FILE_SIZE);

   for(n = 0; n < GM_FILE_SIZE; n++)
   {
   	instr = read_file(GMFILE, n + 1, 1);
   	parse_this(instr, "%s %n", names[n], dpoints[n]);
   }
   /* ok, we got the file with the old stuff */
   /* calculate TP dpoints */
   mydp = TP->query_base_stat(SS_OCCUP)*3 + TP->query_average_stat();
   
   for(n = 0; n < GM_FILE_SIZE && dpoints[n] >= mydp; n++);
	for(o = 0; o < GM_FILE_SIZE && names[o] != TP->query_name(); o++);

	/* ok now we know where he was and where he is going. */
	rm(GMFILE);
	for(m = 0; m < GM_FILE_SIZE; m++)
		if(m == n) write_file(GMFILE, TP->query_name() + "  " + mydp + "\n");
		else
		{					
			if(m < oldf		&&		m < n)		x = 0;
			if(m == oldf	&&		m < n)		x = 1;
			if(m > oldf		&&		m < n)		x = 1;
			if(m < oldf		&&		m > n)		x = -1;
			if(m == oldf	&&		m > n)		x = -1;
			if(m > oldf		&&		m > n)		x = 0;
			if(m + x == GM_FILE_SIZE) write(GMFILE, "empty\n");
			else write_file(GMFILE, names[m + x] + "  " + mydp + "\n");
		}
	
	/* ok, did the guy make disciple ? */
	if(n < 3)
	{
		NF("You are already a Disciple of Melkor!\n");
		if(TP->test_bit("Rhovanion", GM_BIT)) return 0;
		write("The voice of Melkor rushes unstoppably into your head, saying:\n"
			+"'I accept thee as my servant and Disciple, " + TP->query_name() + "'.\n");
		TP->set_bit(GM_BIT);
	}
	else if(o < 3) /* demoted disciple */
	{
		write("The voice of Melkor rushes unstoppably into your head, saying:\n"
			+"'Others may serve me better, so I demote thee, " + TP->query_name() + "'.\n");
		TP->clear_bit(GM_BIT);
	}
	else
	{
		/* he did not */
		write("The voice of Melkor rushes unstoppably into your head, saying:\n"
			+"'Others serve me better, do not pester me with stupid questions, " + TP->query_name() + "'.\n");
		TP->add_some_favor(-10 * n);
	}
	return 1;
}

int
revenge(string str)
{
	object *oblist;
	    
	NF("You must threaten some specific person with revenge.\n");
	if(!strlen(str)) return 0;
	oblist = parse_this(str, "[at] %l");
	
	NF("Threaten whom with revenge?\n");
	if (!sizeof(oblist))	return 0;
	
	target(" threatens you with the revenge of Melkor.", oblist);
	actor("You threaten", oblist, "with the revenge of Melkor.");
	all2act("threatens", oblist,"with the revenge of Melkor.");
	return 1;
	

int
submit(string str)
{
	object *oblist;
	    
	NF("You must submit to some specific person's will.\n");
	if(!strlen(str)) return 0;
	oblist = parse_this(str, "[at] %l");
	
	NF("Submit to whom?\n");
	if(!sizeof(oblist)) return 0;

	target(" submits to your wishes.", oblist);
	actor("You submit obediently to the will of", oblist);
	all2act("submits to the will of", oblist);
	return 1;
}

int
tongues(string str)
{
   NF("What?\n");
   if(strlen(str)) return 0;
   
   write("You start to chant in tongues.\n");
   all2act("starts to chant in tongues.\n");
	SOULEXTRA("chanting in tongues");   
   return 1; 
}

int
trace(string str)
{
   NF("What?\n");
   if(strlen(str)) return 0;
   
   write("You thoughfully trace the outline of the brand on your cheek.\n");
   allbb("thoughtfully trace the outline of the brand on " + HIS(TP) + " cheek.\n");
   return 1; 
}
