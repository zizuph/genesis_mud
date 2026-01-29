/*
 * List of basic dragonarmy emotes
 * (included in dragonarmy_soul.c)
 */

#include <macros.h>
#include <composite.h>
#include <files.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <options.h>
#include <cmdparse.h>
#include <adverbs.h>

#include "../guild.h"

#define LANGUAGE_TO_UNDERSTAND   100


/*
 * List of commands
 * Add new in alphabetic order
 */
mapping
emotes_cmdlist()
{
    return ([
      "da"        :   "da",
      "dbow"      :   "dbow",
      "dburp"     :   "dburp",
      "dcheck"    :   "dcheck",
      "dcheer"    :   "dcheer",
      "dcongrat"  :   "dcongrat",
      "dconvince" :   "dconvince",
      "dcry"      :   "dcry",
      "dfare"     :   "dfare",
      "dglare"    :   "dglare",
      "dgreet"    :   "dgreet",
      "dhalt"     :   "dhalt",
      "dlook"     :   "dlook",
      "dmarch"    :   "dmarch",
      "dnod"      :   "dnod",
      "dpace"     :   "dpace",
      "dponder"   :   "dponder",
      "dpraise"   :   "dpraise",
      "drage"     :   "drage",
      "dsalute"   :   "dsalute",
      "dsay"      :   "dsay",
      "dshield"   :   "dshield",
      "dshine"    :   "dshine",
      "dshout"    :   "dshout",
      "dsmile"    :   "dsmile",
      "dtoast"    :   "dtoast",
      "dvow"      :   "dvow",
    ]);
}

int
dbow(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "slightly", 0);

    if(!strlen(how[0]))
    {
	write("You bow"+how[1]+" keeping the eyes up, waiting.\n");
	allbb(" bows"+how[1]+" keeping "+HIS(TP)+" eyes up, waiting.");
	return 1;
    }

    oblist = parse_this(how[0], "[to] [the] %l");
    if (!sizeof(oblist))
    {
	NF("Bow to whom?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	actor("You bow"+how[1]+" before", oblist,
		" keeping your eyes on them, waiting.");
	targetbb(" bows"+how[1]+" before you keeping "+HIS(TP)+
		" eyes on you, waiting.", oblist);
	all2actbb(" bows"+how[1]+" before", oblist," keeping "+HIS(TP)+
		" eyes on them, waiting.");
    }
    else
    {
	actor("You bow"+how[1]+" before", oblist,
		" never taking your eyes from "+HIS(oblist[0])+", waiting.");
	targetbb(" bows"+how[1]+" before you never taking "+HIS(TP)+
		" eyes from yours, waiting.", oblist);
	all2actbb(" bows"+how[1]+" before", oblist," never taking "+HIS(TP)+
		" eyes from "+HIM(oblist[0])+", waiting.");
    }
    return 1;

}

int
dburp(string str)
{
    string *how = parse_adverb_with_space(str, "rudely", 0);

    if(strlen(how[0]))
    {
	NF("Burp how?\n");
	return 0;
    }

    write("You burp"+how[1]+" and pat your stomach, while pondering where the next pub is.\n");
    all(" burps"+how[1]+", pats " +HIS(TP)+ " stomach, and ponders where the next pub is.");
    return 1;
}

int
dcheck(string str)
{
    object *oblist, ob, *oblist2 = ({});
    int i;

    if (!strlen(str) ||
	!parse_command(str, all_inventory(TP), "[the] %i", oblist) ||
	!sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
    {
	NF("Check what?\n");
	return 0;
    }

    for(i=0; i<sizeof(oblist); i++)
    {
	ob = oblist[i];
	if (ob->check_armour() || ob->check_weapon())
	    oblist2 += ({ ob });
    }

    if (!sizeof(oblist2))
    {
	NF("You can check only weapons and armours.\n");
	return 0;
    }


    str = COMPOSITE_DEAD(oblist2);
    write("You intently study "+str+".\n");
    allbb(" intently studies "+str+".");
    for(i=0; i<sizeof(oblist2); i++)
    {
	ob = oblist2[i];
	write(C(ob->short())+": ");

	if (ob->check_weapon())
	{
	    write(ob->wep_condition_desc());
	    if (TO->query_dattack_damage_type() & ob->query_dt())
	    {
		write("It can be used for your special attack.\n");
	    }
	}
	else
	{
	    write(ob->arm_condition_desc());
	}
    }
    return 1;
}

int
dcheer(string str)
{
    int i;
    object troom, *rooms;
    string *how = parse_adverb_with_space(str, "enthusiastically", 0);

    if(strlen(how[0]))
    {
	NF("Cheer how?\n");
	return 0;
    }

    write("You cheer"+how[1]+", shouting: Victory for the Dragonarmies!\n");
    all(" cheers"+how[1]+", shouting: Victory for the Dragonarmies!");
    if (!(troom = E(TP)))
	return 1;
    rooms = FIND_NEIGHBOUR(({ troom }), ({ troom }), 1);
    rooms -= ({ troom });
    for (i = 0; i < sizeof(rooms); i++)
	tell_room(rooms[i], "@@shout_name:"+CMD_LIVE_SPEECH+"@@ shouts"+how[1]+
			": Victory for the Dragonarmies!\n", TP);
    return 1;
}

int
dcongrat(string str)
{
    object *oblist;

    if(!strlen(str) || !sizeof(oblist = parse_this(str, "[the] %l")))
    {
	NF("Congratulate whom?\n");
	return 0;
    }

    actor("You congratulate", oblist," on a successful battle.");
    target(" congratulates you on a successful battle.", oblist);
    all2act(" congratulates", oblist," on a successful battle.");
    return 1;
}

int
dconvince(string str)
{
    object *oblist;
    string lecture;

    if(!strlen(str) || !sizeof(oblist = parse_this(str, "[the] %l")))
    {
	NF("Convince who?\n");
	return 0;
    }

    switch(random(2))
    {
    case 1:
	lecture = " the world's problems all stem from the region of Solamnia.";
	break;
    default:
	lecture = " the world would be a better place if Solamnia was wiped from it's surface.";
    }

    actor("You convincingly lecture", oblist," about how"+lecture);
    target(" presents you a flurry of arguments that"+lecture, oblist);
    all2act(" lectures", oblist," in an attempt to prove that"+lecture);

    return 1;
}

int
dcry(string str)
{
    if(strlen(str))
	return 0;

    write("A member of the dragonarmy does not cry!\n");
    allbb(" seems to be having trouble holding back " +HIS(TP)+ " grief.");
    return 1;
}

int
dfare(string str)
{
    object *oblist;
    string who = "Takhisis, Queen of Darkness";

    if(!strlen(str) || !sizeof(oblist = parse_this(str, "[the] %l")))
    {
	NF("Farewell who?\n");
	return 0;
    }

    switch(random(3))
    {
    case 0:
	actor("Pressing a fist to your heart you bid", oblist, " farewell.");
	targetbb(" bids you farewell with a fist pressed on " +HIS(TP)+
		" heart.", oblist);
	all2actbb(" bids", oblist, " farewell with a fist pressed on "+
		HIS(TP)+ " heart.");
	break;
    case 1:
    	switch(TP->query_dragonarmy_division())
    	{
    	case "red":  who = "Ariakas, Emperor of Krynn"; break;
    	case "blue": who = "Kitiara, Dark Lady"; break;
	}
    default:
	actor("You bid", oblist, " farewell in the name of "+who+".");
	targetbb(" bids you farewell in the name of "+who+".", oblist);
	all2actbb(" bids", oblist, " farewell in the name of "+who+".");
    }
    return 1;
}

int
dglare(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "angrily", 0);

    if (!strlen(how[0]))
    {
	write("Your muscles tense as you glare"+how[1]+" around.\n");
	allbb("'s muscles tense as "+HE(TP)+" glares"+how[1]+" around.");
	return 1;
    }
    oblist = parse_this(how[0], "[at] [the] %l");
    if (!sizeof(oblist))
    {
	NF("Glare how [at whom]?\n");
	return 0;
    }

    actor("You feel your muscles tense as you glare"+how[1]+" at", oblist,".");
    targetbb("'s muscles tense as " +HE(TP)+ " glares"+how[1]+" at you, " +HIS(TP)+ " eyes " +
      "gleaming with an evil light.", oblist);
    all2actbb(" glares"+how[1]+" at", oblist,", " +HIS(TP)+ " muscles tensing and " +HIS(TP)+
      " eyes gleaming with an evil light.");
    return 1;
}

int
dgreet(string str)
{
    object *oblist;

    if(!strlen(str) || !sizeof(oblist = parse_this(str, "[the] %l")))
    {
	NF("Greet whom?\n");
	return 0;
    }

    actor("You greet", oblist," with a crushing embrace as you would " +
      "any long-time friend.");
    target(" greets you with a crushing embrace you would expect from a long-time " +
      "friend.", oblist);
    all2act(" greets", oblist," with a crushing embrace.");
    return 1;
}


int
dhalt(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "empiriously", 0);

    if(!strlen(how[0]))
    {
    write("You raise your hand"+how[1]+", shouting: Halt in the name "+
          "of the Dragon Empire!\n");
    all(" raises "+HIS(TP)+ " hand"+how[1]+", shouting: Halt in the "+
        "name of the Dragon Empire!");
    return 1;
    }

    oblist = parse_this(how[0], "[the] %l");
    if (!sizeof(oblist))
    {
	NF("Halt whom?\n");
	return 0;
    }

    actor("You raise your hand"+how[1]+" to", oblist,", shouting: "+
          "Halt in the name of the Dragon Empire!");
    targetbb(" raises "+HIS(TP)+" hand"+how[1]+" to you, shouting: " +
      "Halt in the name of the Dragon Empire!", oblist);
    all2actbb(" raises "+HIS(TP)+" hand"+how[1]+" to", oblist,", "+
      "shouting: Halt in the name of the Dragon Empire!");
    return 1;

}

int
dlook(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "suspiciously", 0);

    if (!strlen(how[0]))
    {
	write("You look around"+how[1]+".\n");
	allbb(" looks around"+how[1]+".");
	return 1;
    }
    oblist = parse_this(how[0], "[at] [the] %l");
    if (!sizeof(oblist))
    {
	NF("Look how [at whom]?\n");
	return 0;
    }

    actor("You look at", oblist,how[1]+".");
    targetbb(" looks at you"+how[1]+".",oblist);
    all2actbb(" looks at", oblist,how[1]+".");
    return 1;
}

void
da_command(object who, string *cmds, int m_in_out = 0)
{
    int i, s;
    string in, out;

    if (m_in_out)
    {
	in = who->query_m_in();
	out = who->query_m_out();
	who->set_m_in("marches in");
	who->set_m_out("marches");
    }

    for(i = 0, s = sizeof(cmds); i < s; i++)
	who->command("$"+cmds[i]);

    if (m_in_out)
    {
	who->set_m_in(in);
	who->set_m_out(out);
    }
}

int
dmarch(string str)
{
    string *dirs;
    string *std = ({ "s","se","e","ne","n","nw","w","sw" });

    if (!strlen(str))
    {
	NF("March where?\n");
	return 0;
    }
    
    dirs = explode(str, ",") - ({ "" });

    if (sizeof(dirs - std) || sizeof(dirs) != 5)
    {
	write("Specify five directions (from s,se,e,ne,n,nw,w,sw) "+
		"separated by ','.\n"+
		"        Example:  dmarch s,s,se,n,w\n");
	return 1;
    }

    TP->command("$shout Howling Horns Of War - Dragonarmy March!");

    set_alarm(1.0, 0.0, &da_command(TP, ({ dirs[0] }), 1) );
    set_alarm(2.0, 0.0, &da_command(TP, ({
		"shout Drums of war are pounding,",
		"shout Dragons high up in the sky!",
		"shout Howling horns that tell you:",
		"shout Soon it's time to die!",
					}) ) );
    set_alarm(3.0, 0.0, &da_command(TP, ({ dirs[1] }), 1) );
    set_alarm(4.0, 0.0, &da_command(TP, ({
		"shout Troops are marching onward,",
		"shout Warriors without any fear.",
		"shout Howling horns that tell you:",
		"shout The Dragonarmy is here!",
					}) ) );
    set_alarm(5.0, 0.0, &da_command(TP, ({ dirs[2] }), 1) );
    set_alarm(6.0, 0.0, &da_command(TP, ({
		"shout The kiss of death awaits all,",
		"shout Which are daring to defend.",
		"shout Howling horns that tell you:",
		"shout This battle will be their end!",
					}) ) );
    set_alarm(7.0, 0.0, &da_command(TP, ({ dirs[3] }), 1) );
    set_alarm(8.0, 0.0, &da_command(TP, ({
		"shout Bloody swords harvesting souls,",
		"shout Dragons take their feasts.",
		"shout Howling horns that tell you:",
		"shout Dinner for the beasts!",
					}) ) );
    set_alarm(9.0, 0.0, &da_command(TP, ({ dirs[4] }), 1) );
    set_alarm(10.0, 0.0, &da_command(TP, ({
		"shout  Howling horns that tell you:",
		"shout  Nightfall is coming soon.",
		"shout  Howling horns that tell you:",
		"shout  Krynn awaits its fate.",
		"shout  Howling horns that tell you:",
		"shout  Knights prepare for your doom.",
		"shout  Howling horns are praising:",
		"shout  Takhisis, Queen of Darkness is great!",
					}) ) );
    return 1;
}

int
dnod(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "curtly", 0);

    if (!strlen(how[0]))
    {
	write("You nod your head"+how[1]+" in acknowledgment.\n");
	allbb(" nods " +HIS(TP)+ " head"+how[1]+" in acknowledgment.");
	return 1;
    }
    oblist = parse_this(how[0], "[at] [the] %l");
    if (!sizeof(oblist))
    {
	NF("Nod how [at whom]?\n");
	return 0;
    }

    actor("You nod"+how[1]+" in acknowledgment to",oblist,".");
    targetbb(" nods"+how[1]+" to you in acknowledgment.", oblist);
    all2actbb(" nods"+how[1]+" to", oblist," in acknowledgment.");
    return 1;
}

int
dpace(string str)
{
    string *how = parse_adverb_with_space(str, "rigidly", 0);

    if(strlen(how[0]))
    {
	NF("Pace how?\n");
	return 0;
    }

    write("You pace"+how[1]+" back and forth, collecting your thoughts.\n");
    all(" paces"+how[1]+" back and forth, collecting " 
    +HIS(TP)+ " thoughts.");
    return 1;
}


int
dponder(string str)
{
    object *oblist;

    if(strlen(str) && !sizeof(oblist = parse_this(str, "[the] %l")))
    {
	NF("Ponder who?\n");
	return 0;
    }

    if (sizeof(oblist))
    {
	actor("Your mind wanders elsewhere as you ponder what havoc you " +
		"can wreak to", oblist, ".");
	targetbb("'s mind wanders elsewhere as " +HE(TP)+ " ponders what "+
		"havoc "+HE(TP)+ " can wreak to you.", oblist);
	all2actbb("'s mind wanders elsewhere as " +HE(TP)+ " ponders what "+
		"havoc "+HE(TP)+ " can wreak to", oblist, ".");
	return 1;
    }

    write("Your mind wanders elsewhere as you ponder what havoc you " +
      "can wreak next.\n");
    allbb("'s mind wanders elsewhere as " +HE(TP)+ " ponders what "+
      "havoc "+HE(TP)+ " can wreak next.");
    return 1;
}

int
dpraise(string str)
{
    if(strlen(str))
	return 0;

    write("You scream at the top of your lungs praise to the Queen of Darkness!\n");
    all(" screams praise to the Queen of Darkness!");
    return 1;
}

int
drage(string str)
{
    object *ob;

    if(!strlen(str))
    {
	write("You feel your face contort in rage at the insult, and your hands " +
	  "curl into tight fists in fury.\n");
	allbb("'s face contorts in rage at the insult, " +HIS(TP)+
	  " fists clenching in fury.\n");
	return 1;
    }

    ob = parse_this(str, "[at] [the] %l");
    if(!sizeof(ob))
    {
	NF("Rage at whom?\n");
	return 0;
    }

    actor("You feel your face contort in rage at", ob,"'s insult, your hands curling " +
      "into tight fists of fury.");
    targetbb("'s face contorts in rage at your insult, " +HIS(TP)+ " fists clenching " +
      "in fury.", ob);
    all2actbb(" clenches " +HIS(TP)+ " fists in fury, " +HIS(TP)+ " face contorting in rage " +
      "at", ob,"'s insult.");
    return 1;
}

int
dsalute(string str)
{
    object *oblist;
    string message, div;
    int i, hi, lo, eq, ot, p, pro;

    if(strlen(str))
    {
	oblist = parse_this(str, "[the] %l");
    }
    else
    {
	oblist = filter(all_inventory(E(TP)) - ({ TP }),
			&->check_seen(TP) @ &->query_dragonarmy_occ_member());
    }

    if (!sizeof(oblist))
    {
	NF("Salute whom?\n");
	return 0;
    }

    div = TP->query_dragonarmy_division();
    pro = TP->query_dragonarmy_promotions();
    for(i=0; i<sizeof(oblist); i++)
    {
	if(IS_MEMBER(oblist[i]))
	{
	    if(div == oblist[i]->query_dragonarmy_division())
	    {
		p = oblist[i]->query_dragonarmy_promotions();
		if(pro > p)
		{
		    ++lo;
		}
		else if(pro < p)
		{
		    ++hi;
		}
		else
		    ++eq;
	    }
	    else
		++eq;
	}
	else
	    ++ot;
    }

    if(!hi && !eq && !ot) /* lower only */
    {
	actor("You salute", oblist, " in an aloof manner, as you "+
	  "would any subordinate.");
	targetbb(" salutes you in an aloof manner, common to those "+
	  "of a higher rank.", oblist);
	all2actbb(" salutes", oblist," in an aloof manner.");
	return 1;
    }
    if(!lo && !eq && !ot) /* higher only */
    {
	actor("You swiftly stand to attention, saluting", oblist,
	  " respectfully.");
	targetbb(" swiftly stands to attention, saluting you "+
	  "respectfully.", oblist);
	all2actbb(" swiftly stands to attention, saluting", oblist,
	  " respectfully.");
	return 1;
    }
    if(hi || lo || eq) /* mixed or equal */
    {
	actor("You raise your fist in a smart military "+
	  "salute to", oblist,".");
	targetbb(" raises " +HIS(TP)+ " fist, saluting you in a smart "+
	  "military fashion.", oblist);
	all2actbb(" raises " +HIS(TP)+ " fist in a smart military "+
	  "salute to", oblist,".");
	return 1;
    }
    /* only nonmembers */
    switch(div)
    {
    case "red":
	message = "Hail in the name of Ariakas, Emperor of Krynn!"; break;
    case "blue":
	message = "Hail in the name of Kitiara, Dark Lady!"; break;
    default:
	message = "In the name of Takhisis, Queen of Darkness, I greet you.";
    }
    actor("You salute", oblist, ", saying: " +message);
    target(" salutes you, saying: " +message, oblist);
    all2act(" salutes", oblist,", saying: " +message);
    return 1;
}

private int
query_dsay_understand(object who)
{
    if (IS_MEMBER(who) ||
	(who->query_wiz_level()) ||
	(who->query_guild_name_occ() == "Priests of Takhisis") ||
        (who->query_skill(SS_LANGUAGE) >= LANGUAGE_TO_UNDERSTAND))
        return 1;
    return 0;
}

private string
query_dsay_what_get(object who, string *words)
{
    int j, s, dots = 0, lan_skill = who->query_skill(SS_LANGUAGE);
    string what_get = "";

    lan_skill = lan_skill*lan_skill*lan_skill/(LANGUAGE_TO_UNDERSTAND*LANGUAGE_TO_UNDERSTAND);
    for (j = 0, s = sizeof(words); j < s; j++)
	if(lan_skill > random(LANGUAGE_TO_UNDERSTAND))
	{
            what_get += words[j]+" ";
            dots = 0;
        }
        else if(!dots)
        {
            dots = 1;
            what_get += "... ";
        }

    if(what_get == "... ")
        return " something that you don't understand at all.\n";
    return " something like: " + what_get + "\n";
}

/*
 * Function name: dsay_text
 * Description  : It creates proper messages for dsay and dshout.
 * Arguments    : string str     - the message
 *                string adverb  - adverb with leading space
 *                object *tar    - the people we say to or shout at
 *                int shout      - 0 if we say, othervise we shout
 */
private void
dsay_text(string str, string adverb, object *tar, int shout = 0)
{
    int i, s;
    object *tmp;
    string *words, qcomp = "", r_sound = " shouts", to = " at ";
    object *oblist = FILTER_OTHER_LIVE(all_inventory(E(TP))) - tar; // watchers

    if (!shout)
    {
	TP->set_say_string(str);
	r_sound = (" @@race_sound:" + file_name(TP) + "@@");
	to = " to ";
    }

    
    if (s = sizeof(tar))
	qcomp = to + COMPOSITE_ALL_LIVE(tar);
    if (TP->query_option(OPT_ECHO))
	write("You" + adverb + " " +
		(shout ? "shout" : TP->actor_race_sound()) +
		" in Draco" + qcomp + ": " + str + "\n");
    else
	write("Ok.\n");
    if (s)
	qcomp = to + QCOMPLIVE;
    
    tmp = filter(oblist, query_dsay_understand);
    oblist -= tmp; // watchers that do not understand
    
    // display only to watchers that understand
    tmp = oblist + tar;
    say(QCTNAME(TP) + adverb + r_sound + qcomp + " in Draco: " + str + "\n",
		tmp + ({ TP }) );
    
    words = explode(str, " ");

    // display to watchers that do not understand (skip npcs)
    oblist = FILTER_PLAYERS(oblist);
    for (i = 0, s = sizeof(oblist); i < s; i++)
        oblist[i]->catch_msg(TP->query_The_name(oblist[i]) + adverb +
		" " + (shout ? "shouts" : TP->race_sound(oblist[i])) +
		qcomp + query_dsay_what_get(oblist[i], words));

    // finaly display to targets
    if (!sizeof(tar))
	return; // there are no targets

    tmp = filter(tar, query_dsay_understand); // targets that understand
    tar -= tmp; // targets that do not understand	

    tmp = FILTER_PLAYERS(tmp);
    tmp->catch_msg(QCTNAME(TP) + adverb + r_sound + to + "you in Draco: " + str + "\n");

    tar = FILTER_PLAYERS(tar);
    for (i = 0, s = sizeof(tar); i < s; i++)
	tar[i]->catch_tell(TP->query_The_name(tar[i]) + adverb + " " +
		(shout ? "shouts" : TP->race_sound(tar[i])) + to + "you" +
		query_dsay_what_get(tar[i], words));
}

private int
dsay_to(string str, string adverb)
{
    object *oblist;
    string say_string;

    say_string = str;
    if (!parse_command(L(str), E(TP), "[the] %l %s", oblist, str))
        return 0;

    oblist = NORMAL_ACCESS(oblist, 0, 0) - ({ this_player(), 0 });
    if (!sizeof(oblist) || !strlen(str))
        return 0;

    say_string = extract(say_string, -(strlen(str)));
    dsay_text(say_string, adverb, oblist );
    return 1;
}

/*
 * Function used to say something in draco.
 * command: 'dsay [adverb] [to target] <message>'
 * It is based on mudlib code for 'say' and 'asay' commands
 */
varargs int
dsay(string str)
{
    string *how;
    mixed gag;


    if (!E(TP))
        return 0;

    if (!strlen(str))
    {
        NF("What do you want to say in language of Draco?\n");
        return 0;
    }

    if (gag = TP->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        write(stringp(gag) ? gag : "You are gagged and cannot speak.\n");
        return 1;
    }

    how = parse_adverb_with_space(str, NO_DEFAULT_ADVERB, 0);
    if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
    	how[1] = "";

    if (!strlen(how[0]))
    {
	how[1] = "";
	how[0] = str;
    }

    /* This is a test for the command 'dsay to'. If it fails, we just default
     * to the normal say.
     */
    if (wildmatch("to *", how[0]))
        if (dsay_to(extract(how[0], 3), how[1]))
            return 1;

    dsay_text(how[0], how[1], ({}) );
    return 1;
}

int
dshield(string str)
{
    if(strlen(str))
	return 0;

    if (!CAN_SEE_IN_ROOM(TP))
    {
	NF("You can't see here.\n");
	return 0;
    }
    if(E(TP)->query_prop(ROOM_I_INSIDE))
    {
	NF("You are inside.\n");
	return 0;
    }

    write("You look expectantly up into the sky, shielding your eyes with your hand.\n");
    allbb(" shields " +HIS(TP)+ " eyes with "+HIS(TP)+" hand, looking expectantly "+
       "up into the sky.");
    return 1;
}

string get_short(object o) { return o->short(); }

int
dshine(string str)
{
    object *oblist, uniform;
    string uni;

    if (!strlen(str) ||
	!parse_command(str, all_inventory(TP), "[the] %i", oblist) ||
	!sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
    {
	NF("Shine what?\n");
	return 0;
    }

    uniform = TP->query_worn_uniform();
    if (objectp(uniform))
	uni = explode(uniform->short()+" of a", " of a")[0];
    str = " "+COMPOSITE_DEAD(oblist);
    str = implode(explode(str, " a "), " ");
    str = implode(explode(str, " an "), " ");
    write("You buff your"+str+" to a perfect shine"+
    	(uni ? " with the sleeve of your "+uni : "")+".\n");
    allbb(" buffs "+HIS(TP)+str+" to a perfect shine"+
    	(uni ? " with the sleeve of "+HIS(TP)+" "+uni : "")+".");
    return 1;
}

void
dshout_text(string str, object* tar)
{
    object *rooms, troom, *tmp, *oblist = ({});
    int i, s;
    string who, *words;

    if (!(troom = E(TP)))
        return;

    /* first we shout in our room */
    dsay_text(str, "", tar, 1);

    /* now what people in neighbourhood hear */
    rooms = FIND_NEIGHBOUR( ({ troom }), ({ troom }), 1);
    rooms -= ({ troom });

    for(i = 0, s = sizeof(rooms); i < s; i++)
	oblist += FILTER_PLAYERS(all_inventory(rooms[i]));
    
    who = "A "+TP->query_gender_string() + " " + TP->query_race_name() +
	" voice shouts";

    tmp = filter(oblist, query_dsay_understand); // targets that understand
    oblist -= tmp;

    tmp->catch_tell(who + " in Draco: " + str + "\n");

    words = explode(str, " ");
    for(i = 0, s = sizeof(oblist); i < s; i++)
	oblist[i]->catch_tell(who + query_dsay_what_get(oblist[i], words));
}

int
dshout_at(string str)
{
    object *oblist;
    string say_string;

    say_string = str;
    if (!parse_command(L(str), E(TP), "[the] %l %s", oblist, str))
        return 0;

    oblist = NORMAL_ACCESS(oblist, 0, 0) - ({ this_player(), 0 });
    if (!sizeof(oblist) || !strlen(str))
        return 0;

    say_string = extract(say_string, -(strlen(str)));
    dshout_text(say_string, oblist);
    return 1;
}

int
dshout(string str)
{
    mixed tmp;

    if (!strlen(str))
    {
        NF("Shout what?\n");
        return 0;
    }

    if (tmp = TP->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        write(stringp(tmp) ? tmp : "You are gagged and cannot shout.\n");
        return 1;
    }
 
    /* This is a test for the command 'dsay to'. If it fails, we just default
     * to the normal say.
     */
    if (wildmatch("at *", str))
        if (dshout_at(extract(str, 3)))
            return 1;

    dshout_text(str, ({}) );
    return 1;
}

int
dsmile(string str)
{
    if(strlen(str))
	return 0;

    write("The corner of your mouth curls up into a wicked smile of amusement.\n");
    say("The corner of "+QTNAME(TP)+"'s mouth curls up into a wicked "+
      "smile of amusement.\n");
    return 1;
}

int
dtoast(string str)
{
    object *oblist;

    if (strlen(str) && !sizeof(oblist = parse_this(str, "[to] [the] %l")))
    {
	NF("Toast to who?\n");
	return 0;
    }

    if (sizeof(oblist))
    {
	actor("You make a toast to", oblist,".");
	target(" makes a toast to you.", oblist);
        all2act(" makes a toast to", oblist, ".");
    }
    else
    {
	write("You make a toast to Takhisis, Queen of Darkness!\n");
	all(" makes a toast to Takhisis, Queen of Darkness!\n");
    }
    return 1;
}

int
dvow(string str)
{
    object *oblist;

    if (strlen(str) && !sizeof(oblist = parse_this(str, "[the] %l")))
    {
	NF("Vow who?\n");
	return 0;
    }

    if (sizeof(oblist))
    {
	actor("You vow to destroy", oblist,
		" in the name of Takhisis, Queen of Darkness!");
	target(" vows to destroy you in the name of Takhisis, Queen of Darkness!",
		oblist);
	all2act(" vows to destroy", oblist,
		" in the name of Takhisis, Queen of Darkness!");
	return 1;
    }
    write("You vow to destroy all in the name of Takhisis, Queen of Darkness!\n");
    allbb(" vows to destroy all in the name of Takhisis, Queen of Darkness!");
    return 1;
}

int
da(string str)
{
    int i;
    string sss, *arr;

    if (!str || !sizeof(arr = explode(str, " ")))
	return 0;

    if (sizeof(arr) > 1)
    {
	sss = arr[1];
	for (i=2; i < sizeof(arr); i++)
	    sss += " " + arr[i];
    }

    switch(arr[0])
    {
    case "bow":
	return dbow(sss);
    case "burp":
	return dburp(sss);
    case "check":
	return dcheck(sss);
    case "cheer":
	return dcheck(sss);
    case "congrat":
	return dcongrat(sss);
    case "convince":
	return dconvince(sss);
    case "cry":
	return dcry(sss);
    case "fare":
	return dfare(sss);
    case "glare":
	return dglare(sss);
    case "greet":
	return dgreet(sss);
    case "halt":
	return dhalt(sss);
    case "look":
	return dlook(sss);
    case "march":
	return dmarch(sss);
    case "nod":
	return dnod(sss);
    case "pace":
	return dpace(sss);
    case "ponder":
	return dponder(sss);
    case "praise":
	return dpraise(sss);
    case "rage":
	return drage(sss);
    case "salute":
	return dsalute(sss);
    case "say":
	return dsay(sss);
    case "shield":
	return dshield(sss);
    case "shine":
	return dshine(sss);
    case "shout":
	return dshout(sss);
    case "smile":
	return dsmile(sss);
    case "toast":
	return dtoast(sss);
    case "vow":
	return dvow(sss);
    default:
	return 0;
    }
}

