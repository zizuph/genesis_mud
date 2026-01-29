/*
 * Rich Men's Club (Command Soul)
 *
 * Creator Conan (1992)
 *
 * Current Maintainer: Lunatari (2006)
 *
 * Change Log:
 * 2006-01-31 Lunatari - The Club was moved to Sparkle.
 * 2006-02-01 Lunatari - The rc account command for wizards was recoded.
 * 2006-02-01 Lunatari - Re added rc counthi as rc count and rc stop.
 * 2008-01-28 Lunatari - Made the changes for the new account object 
 *                       query_account_coins instead of query_account.
 *                       Should fix support for gems as value of RMC.
 * Updated by Gronkas August 4, 2016 to fix some typos
 */
#pragma save_binary
#pragma strict_types

inherit "/cmd/std/soul_cmd";

#include "defs.h"
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <filter_funs.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#define FILTHILY if((RMCMASTER)->query_purchased(TP->query_real_name())<2000) return "No such RMC command.\n"
#define BIGSHOT  if((RMCMASTER)->query_purchased(TP->query_real_name())<4000) return "No such RMC command.\n"

int    purge  = 0;
mixed  *id;
object purse = present("rich_club_obj",TP);
string type = purse->query_short();

mixed  *emote = (({
    ({8, "|*bankbook................................check your nice account. |",}),
    ({33,"| account <all/m/name/wiz>.........checks the account of a person. |",}),
    ({4, "| advice <target>....give somebody some advice how to gain wealth. |",}),
    ({2, "| assure <target>....assure somebody that the future will be good. |",}),
    ({8, "| board..........................................bribe the sailor. |",}),
    ({17,"| bounce....................................bounce around happily. |",}),
    ({2, "| busy..................make clear that you are busy making money. |",}),
    ({4, "| buy <something>...................................buy something. |",}),
    ({2, "| cackle.........................................cackle wealthily. |",}),
    ({16,"|*catch <target>.....try to catch a coin that <target> has tossed. |",}),
    ({33,"| checklog 'rich'/'pier'.....shows the logs rich.log and gold.log. |",}),
    ({4, "|*checkpocket........................check your pockets for coins. |",}),
    ({1, "| close..........................................close your purse. |",}),
    ({16,"| comfort <target>........comfort someone, since (s)he is so poor. |",}),
    ({16,"| compare <target>...............compare someone's wealth to your. |",}),
    ({8, "| consider <target>.....................consider someone's wealth. |",}),
    ({2, "| convince <target>.....convince somebody that money is important. |",}),
    ({16,"| count <coin type>.........................count your coins loud. |",}),
    ({8, "| dislike.........................dislike someone poorer than you. |",}),
    ({8, "| disgust................show what you think of sniveling beggars. |",}),
    ({2, "|*dream..................dream about the fortunes that lies ahead. |",}),
    ({2, "| drop.........................................drop a copper coin. |",}),
    ({4, "| dropall............drop all your coppers because of their value. |",}),
    ({2, "| evaluate.........................notify the importance of money. |",}),
    ({1, "|*get...................................get coins from your purse. |",}),
    ({1, "| greet <target>...................................greet a player. |",}),
    ({2, "| grin..................................grin and show your wealth. |",}),
    ({1, "|*hide......................hide your purse so that noone sees it. |",}),
    ({16,"| hold....................hold your money-sack close to your body. |",}),
    ({4, "| hope...........hope that the future will be rich and prosperous. |",}),
    ({1, "|*humble <on/off>......decide whether you want to show off or not. |",}),
    ({4, "| jump....................jump high after controlling your income. |",}),
    ({16,"|*list.........................................fellow rich people. |",}),
    ({2, "| look...........................check the contents of your purse. |",}),
    ({8, "| loot <pgsc>...........................loot the corpse for money. |",}),
    ({33,"| members..................................show member statistics. |",}),
    ({4, "|*mini..............................minimize your coins in a bank. |",}),
    ({1, "|*news......................to see the latest changes in the club. |",}),
    ({1, "|*note <on/off>................get notification about competitors. |",}),
    ({1, "| nudge.....................................show the joy of money. |",}),
    ({1, "| offer <target>.....................................offer a loan. |",}),
    ({4, "|*order <something>...............................order something. |",}),
    ({1, "| open.........................................open up your purse. |",}),
    ({16,"| panic.........panic since you think you've lost your money-sack. |",}),
    ({1, "| pat...........................................admire your purse. |",}),
    ({4, "| peer <target>.......peer at somebody, disliking the competition. |",}),
    ({2, "| pick....................................smell the taste of gold. |",}),
    ({33,"| purge..................purge wiz members onlogged without purse. |",}),
    ({17,"|*pos...............................see your position in the club. |",}),
    ({33,"|*ps <target>.................see a member's position in the club. |",}),
    ({1, "|*put.....................................put coins in your purse. |",}),
    ({1, "| scream..................scream in agony after losing some money. |",}),
    ({8, "|*search.....................search for money in your empty purse. |",}),
    ({4, "|*sell <something>.................................sell something. |",}),
    ({33,"| setlevel...............................set a members club title. |",}),
    ({33,"| setnews.............................set all members news status. |",}),
    ({2, "|*shop............................dislike the prices in the store. |",}),
    ({4, "| sing.............sing about all the fun you can have with money. |",}),
    ({4, "|*slip <target>.................slip a coin into someone's pocket. |",}),
    ({1, "| smile.......................smile greedily over your big income. |",}),
    ({1, "|*smile2..........................................smile wealthily. |",}),
    ({2, "| smirk....................smirk and think of your poor childhood. |",}),
    ({33,"| spent............how much money mortals have spent on this club. |",}),
    ({4, "|*sponsor <target>..............sponsor a poor fellow with a coin. |",}),
    ({16,"| stop <counting>........................stop counting your coins. |",}),
    ({2, "|*sulk.......................sulk because your purse is too small. |",}),
    ({16,"| sup..........................tell everyone how superior you are. |",}),
    ({17,"| tboard..............bribe the sailor and pay for the whole team. |",}),
    ({4, "| tease <target>....................................tease someone. |",}),
    ({33,"| tell <something>.........................tell all RMC something. |",}),
    ({4, "|*think....................................think hard about money. |",}),
    ({16,"|*title.......................check how far you are to next title. |",}),
    ({4, "|*toss.....................................toss a coin in the air. |",}),
    ({33,"| vars <target>...................check <target>'s club variables. |",}),
    ({4, "|*walk...........................walk a coin around your knuckles. |",}),
    ({17,"|*wonder <member>.......wonder about your and a co-members wealth. |",}),
    ({8, "| yawn........yawn as you have to listen to all these poor people. |",}), }));
        
string
get_soul_id()
{
	return("The Rich Men's Club");
}

int
query_command_soul()
{
	return 1;
}

mapping
query_cmdlist()
{
    return (["rc"         :      "rmc_commands"]);
}

    
mapping
query_rmc_commands()
{
    return ([
        "help"        :         "help",
        "bankbook"    :     "bankbook",
        "account"     :     "raccount",
        "advice"      :      "radvice",
        "assure"      :      "rassure",
        "board"       :       "rboard",
     	"bounce"      :      "rbounce",
        "busy"        :        "rbusy",
        "buy"         :         "rbuy",
        "cackle"      :      "rcackle",
        "catch"       :       "rcatch",
        "checkpocket" : "rcheckpocket",
        "checklog"    :    "rchecklog",
        "close"       :       "rclose",
        "comfort"     :     "rcomfort",
        "compare"     :     "rcompare",
        "consider"    :    "rconsider",
        "convince"    :    "rconvince",
        "count"       :       "rcount",
        "disgust"     :     "rdisgust",
        "dislike"     :     "rdislike",
        "dream"       :       "rdream",
        "drop"        :        "rdrop",
        "dropall"     :     "rdropall",
        "evaluate"    :    "revaluate",
        "get"         :         "rget",
        "greet"       :       "rgreet",
        "grin"        :        "rgrin",
        "hide"        :        "rhide",
        "hold"        :        "rhold",
        "hope"        :        "rhope",
        "humble"      :      "rhumble",
        "list"        :        "rlist",
        "jump"        :        "rjump",
        "look"        :        "rlook",
        "loot"        :        "rloot",
        "members"     :     "rmembers",
        "mini"        :        "rmini", 
        "news"        :        "rnews",
        "note"        :        "rnote",
        "nudge"       :       "rnudge",
        "offer"       :       "roffer",
        "open"        :        "ropen",
        "order"       :       "rorder",
        "panic"       :       "rpanic",
        "pat"         :         "rpat",
        "peer"        :        "rpeer",
        "pick"        :        "rpick",
        "pos"         :         "rpos",
        "ps"          :          "rps",
        "purge"       :       "rpurge",
        "put"         :         "rput",
        "scream"      :      "rscream",
        "search"      :      "rsearch",
        "sell"        :        "rsell",
        "setlevel"    :    "rsetlevel",
        "setnews"     :     "rsetnews",
        "shop"        :        "rshop",
        "sing"        :        "rsing",
        "slip"        :        "rslip",
        "smile"       :       "rsmile",
        "smile2"      :      "rsmile2",
        "smirk"       :       "rsmirk",
        "spent"       :       "rspent",
        "sponsor"     :     "rsponsor",
        "stop"        :        "rstop",
        "sulk"        :        "rsulk",
        "sup"         :         "rsup",
        "tboard"      :      "rtboard",
        "tease"       :       "rtease",
        "tell"        :        "rtell",
        "title"       :       "rtitle",
        "think"       :       "rthink",
        "toss"        :        "rtoss",
        "vars"        :        "rvars",
        "walk"        :        "rwalk",
        "wonder"      :      "rwonder",
        "yawn"        :        "ryawn"
     ]);
}

/*
 * +-------------------------------------+
 * | SUB-FUNCTIONS FOR THE R.M.C. EMOTES |
 * +-------------------------------------+
 */
string
query_purse()
{
    string s;
    
    s = present("rich_club_obj",TP)->query_name();
    return s;
}

int
bank_account(object ob)
{
    int *coins = GOG_ACCOUNTS->query_account_coins(ob->query_real_name());

    return MONEY_MERGE(coins) / MONEY_VALUES[MONEY_PC_INDEX];
}

int
level_account(object ob)
{
    int level,tot;

    level = (RMCMASTER)->query_level(ob->query_real_name()); 
    tot = (200 * level);
    return tot;
}

int
inv_account(object ob)
{
    int tot;

    tot = TOTAL_MONEY(ob);
    tot = tot/1728;
    return tot;
}

int
total_account(object ob)
{
    int tot;
    tot = level_account(ob) + inv_account(ob) + bank_account(ob);
    return tot;
}

void
change_account()
{
    int plats;
    plats = bank_account(TP);
    (RMCMASTER)->change_account(TP->query_real_name(), plats);
}

int
retaccount(int sum)
{
    write("You find your bankbook.\nYou have " +
	  sum + " platinum coins in the bank.\n");
    TP->add_prop(SET_EMOTE,"reading a bankbook");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    say(QCTNAME(TP)+" reads a small book.\n");
    return 1;
}

int
retaccount2(int summa)
{
    write("You find your gold-plated bankbook.\n"+
	  "| $   T H Y   B E L O V E D   B A N K B O O K   $ |\n"+
	  "|           B A N K   O F   G E N E S I S         |\n"+
	  "|\t\t\t\t\t\t|\n"+
	  "\n");
    TP->add_prop(SET_EMOTE,"reading a bankbook");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    say(QCTNAME(TP)+" reads a small book.\n");
    return 1;
}

int
raccwrite(string str, int acc, int lvl)
{
    write("<RMC> " + capitalize(str));
    if (strlen(str) < 10)
	write("\t");
    
    write("\tlvl:");
    write(lvl);
    write("\tbank:");
    write(acc);
    write(".\n");

    return 1;
}

int
topurse(int silent)
{
    int i, drp;
    object pc,gc,sc,cc,*gm;

    FIXEUID;

    purse = present("rich_club_obj",TP);

    pc = present("platinum coin", TP);
    gc = present("gold coin", TP);
    sc = present("silver coin", TP);
    cc = present("copper coin", TP);
    gm = FIND_STR_IN_OBJECT("gems", TP);
    
    if (pc) drp = pc->move(purse);
    if (gc) drp += gc->move(purse);
    if (sc) drp += sc->move(purse);
    if (cc) drp += cc->move(purse);

    if (sizeof(gm))
    {
        for (i = 0; i < sizeof(gm); i++)
        {
            if (!(wildmatch("/d/Terel/dust/magic_gem*", file_name(gm[i])) == 1))
                drp += gm[i]->move(purse);
        }
    }
    

    if (silent)
    {
        TP->catch_msg("You put some coins into your "+query_purse()+".\n");
        say(QCTNAME(TP)+" puts some coins into "+HIS_HER(TP)+" "+query_purse()+
            ".\n");
    }
    return drp;
}

void
frompurse(int silent)
{
    object pc,gc,sc,cc,*gm;
    int i;

    FIXEUID;

    purse = present("rich_club_obj",TP);

    pc = present("platinum coin", purse);
    gc = present("gold coin", purse);
    sc = present("silver coin", purse);
    cc = present("copper coin", purse);
    gm = FIND_STR_IN_OBJECT("gems", purse);
    
    if (pc) pc->move(TP);
    if (gc) gc->move(TP);
    if (sc) sc->move(TP);
    if (cc) cc->move(TP);

    if (sizeof(gm))
    {
        for (i = 0; i < sizeof(gm); i++)
            gm[i]->move(TP);
    }
    
    if (silent && (pc || gc || sc || cc || gm))
    {
        TP->catch_msg("You fetch some coins from your "+query_purse()+".\n");
        say(QCTNAME(TP)+" fetches some coins from "+HIS_HER(TP)+" "+query_purse()+
            ".\n");
    }
}

int
getta_coins(object who)
{
    who->command("get coins");
    write("You giggle.\n");
    say(QCTNAME(who)+" giggles greedily.\n");
    TP->add_prop(SET_EMOTE,"smiling greedily holding the coins near the heart");
    topurse(1);
    return 1;
}

int
catch_coin()
{
    int dexxy, strength;
    object ob, catcher;

    dexxy = TP->query_stat(SS_DEX)/10 + random(20);
    strength  = TP->query_stat(SS_STR)/10;
    catcher = TP->query_prop("_live_o_tries_to_catch");

    FIXEUID;
    
    TP->remove_prop("_live_o_tries_to_catch");
    TP->remove_prop("_live_i_has_tossed_coin");
    frompurse(0);
    ob = present("platinum coin",TP);
  
    if (ob)
    {
	if (catcher && (catcher->query_stat(SS_DEX)/10 + random(20))>dexxy)
	{
	    TP->catch_msg("You are about to catch the coin, when suddenly "+QTNAME(catcher)+
			  " raises "+HIS_HER(catcher)+" hand and grabs it before "+
			  "your very eyes!\n");
	    catcher->catch_msg("You jump up and catch the coin before "+QTNAME(TP)+"'s very "+
			       "eyes!\n");
	    tell_room(ENV(TP),QCTNAME(catcher)+" jumps up and catches the coin before "+QTNAME(TP)+"'s "+
		      "very eyes!\n",({TP, catcher}));
	    ob->split_heap(1);
	    ob->move(catcher);
	    catcher->command("grin");
	    TP->command("grumble");
	    topurse(0);
	    return 1;
	}
	else if (catcher)
	{
	    TP->catch_msg("You are about to catch the coin, when suddenly "+QTNAME(catcher)+
			  " raises "+HIS_HER(catcher)+" hand and tries to catch your "+
			  "coin! Luckily "+HE_SHE(catcher)+" misses.\n");
	    catcher->catch_msg("You jump up to try to catch the coin before "+QTNAME(TP)+"'s very "+
			       "eyes, but you miss!\n");
	    tell_room(ENV(TP),QCTNAME(catcher)+" jumps up to try to catch the coin before "+QTNAME(TP)+"'s "+
		      "very eyes, but "+HE_SHE(catcher)+" misses.\n",({TP, catcher}));
	    catcher->command("grumble");
	}
	if (dexxy < strength )
	{
	    write("You fumble and the platinum coin falls down on the ground.\n");
	    TP->add_prop(SET_EMOTE,"not proud at all");
	    say("Suddenly a platinum coin falls down from above.\n"+
		QCTNAME(TP)+" fumbles with the platinum coin and it falls down to the ground.\n");
	    TP->command("sigh");
	    ob->split_heap(1);
	    ob->move(ENV(TP));
	    topurse(0);
	    return 1;
	}
	write("You catch the platinum coin without any problem.\n");
	say("Suddenly a platinum coin falls down from above.\n");
	say(QCTNAME(TP)+" caught it without any problem\n");
	TP->command("cheer");
	TP->add_prop(SET_EMOTE,"cheering enthusiastically of pure happiness");
	topurse(0);
	return 1;
    }
    topurse(0);
    return 1;
}

int
move_random_coin_amount(object coin, object where)
{
    int c,d;

    FIXEUID;
    
    c = coin->num_heap();
    if (c > 10)
	d = random(10);
    else
	d = random(c);

    if (d)
    {
	coin->split_heap(d);
	coin->move(where);
	return 1;
    }
    return 0;
}

/*
 * +------------------------------------------------------------------+
 * | EMOTES FOR THE R.M.C. (should be added in alphabetically order.) |
 * +------------------------------------------------------------------+
 */
string
help(string str)
{
    string fnurp;
    int i, p, level;
    RICH_ACCESS(1);
    
    FIXEUID;
    TP->catch_tell(":" + str +":\n");
    
    level = (RMCMASTER)->query_level(TP->query_real_name());
    p = (RMCMASTER)->query_purchased(TP->query_real_name());
    
    if (p > 4000)
	level += 2;
    else if (p > 2000)
	level++;
    
    fnurp ="\n+------------------------------------------------------------------+\n"+
	"| $             This is the Rich Men's Club's emotes:            $ |\n"+
	"+------------------------------------------------------------------+\n";
    
    if (!str || str == "")
    {
	for (i = 0; i < sizeof(emote); i++)
	{
	    if (level >= emote[i][0]) fnurp += emote[i][1]+"\n";
	}
    }
    else if (str=="p")
    {
	fnurp += "| Poor Member's Emotes:                                            |\n";
	for (i = 0; i < sizeof(emote); i++)
	{
	    if (emote[i][0] == 1) fnurp += emote[i][1]+"\n";
	}
    }
    else if (str == "a" && level >= 2)
    {
	fnurp += "| Average Member's Emotes:                                         |\n";
	for (i = 0; i < sizeof(emote); i++)
	{
	    if (emote[i][0] == 2) fnurp += emote[i][1]+"\n";
	}
    }
    else if (str == "w" && level >= 4)
    {
	fnurp += "| Wealthy Member's Emotes:                                         |\n";
	for (i = 0; i < sizeof(emote); i++)
	{
	    if (emote[i][0] == 4) fnurp += emote[i][1]+"\n";
	}
    }
    else if (str == "e" && level >= 8)
    {
	fnurp += "| Extremely Wealthy Member's Emotes:                               |\n";
	for (i = 0; i < sizeof(emote); i++)
	{
	    if (emote[i][0] == 8) fnurp += emote[i][1]+"\n";
	}
    }
    else if (str == "o" && level >= 16)
    {
	fnurp += "| Obscenely Wealthy Member's Emotes:                               |\n";
	for (i = 0; i < sizeof(emote); i++)
	{
	    if (emote[i][0] == 16) fnurp += emote[i][1]+"\n";
	}
    }
    else if (str == "f" && level >= 17)
    {
	fnurp += "| Filthily Rich Member's Emotes:                                   |\n";
	for (i = 0; i < sizeof(emote); i++)
	{
	    if (emote[i][0] == 17) fnurp += emote[i][1]+"\n";
	}
    }
    else if (str == "b" && level >= 18)
    {
	fnurp += "| Big Shot Member's Emotes:                                        |\n";
	for (i = 0; i < sizeof(emote); i++)
	{
	    if (emote[i][0] == 18) fnurp += emote[i][1]+"\n";
	}
    }
    else if (str == "d" && level >= 33)
    {
	fnurp += "| Admin Commands:                                                  |\n";
	for (i = 0; i < sizeof(emote); i++)
	{
	    if (emote[i][0] >= 33) fnurp += emote[i][1]+"\n";
	}
    }
    else
	return "Wrong syntax to 'rc help'.\n";
    
    fnurp = fnurp + "+------------------------------------------------------------------+\n"+
	"|       To leave the club: Return to the join-room and type:       |\n"+
	"|                      'leave rich club'                           |\n"+
	"|   All commands should have 'rc ' in front of them, ie 'smile'    |\n"+
	"| becomes 'rc smile'.  'rc help' and the first letter in the title |\n"+
	"| shows that titles emotes, 'rc help p' shows Poor Members emotes. |\n"+
	"|  An * before the emote desc means that it works in humble mode.  |\n"+
	"+------------------------------------------------------------------+\n\n";
    write(fnurp);
    
    say(QCTNAME(TP)+" examines "+HIS_HER(TP)+" "+query_purse()+" closely.\n");
    TP->command("smile greedily");
    
    return 0;
}

string
bankbook()
{
    int acc;
    
    RICH_ACCESS(8);
    
    acc = bank_account(TP);
    TP->add_prop(LIVE_S_EXTRA_SHORT," is reading a small book");
    write("You start to search for your bankbook.\n");
    set_alarm( 4.0, 0.0,"retaccount",acc);
    say(QCTNAME(TP)+" digs deep into "+HIS_HER(TP)+" "+query_purse()+
	" looking for something.\n");
    return 0;
}

string
raccount(string str)
{
    object *players, player;
    int i, lvl, acc, level;
    string name;
    
    RICH_ACCESS(33);

    str = lower_case(str);

    if (!strlen(str))
    {
        write("<RMC> rc account <all> or <playername>\n");
        return 0;
    }

    if ( str == "all" )
   	{
        players = users();
    
        for (i = 0; i < sizeof(players); i++)
        {
            if(RMCMASTER->query_member(players[i]->query_real_name()) && !players[i]->query_wiz_level())
            {
            	lvl = (RMCMASTER)->query_level(players[i]->query_real_name()); 
            	acc = bank_account(players[i]);
            	name = players[i]->query_real_name();
	    
   	    	    if (lvl>0 || acc>0)
           	    	raccwrite(name,acc,lvl);
        
            }
    	}

        return 0;
   	}

   	if ((player = (SECURITY)->finger_player(str)) && (RMCMASTER)->query_member(str))
   	{
       	acc = bank_account(player);

        write("\n<RMC> "+capitalize(str)+" has level ");
        write((RMCMASTER)->query_level(str));
   	    write(" in the RMC.\n");
   	    write("<RMC> "+capitalize(str)+" has ");
   	    write(acc);
   	    write(" plats in the bank.\n\n");
   	    return 0;
   	}
    else
    {
        write("\n<RMC> Player "+capitalize(str)+" was not found or is not a member.\n");
        return 0;
    }

    return 0;
}

string
radvice(string s)
{
  object *a,ob, *obs;
  string str;
  int align, i;

  RICH_ACCESS(4);
  XNOTHUMBLE;
  
  if (!s || s == "all")
  {
    write("You advise everyone that the best way of gaining a lot of money is "+
          "not to spend it.\n");
    say(QCTNAME(TP)+" advises you that the best way of gaining a lot of money "+
        "is not to spend it.\n");
    return 0;
  }

  if (s == "me")  
  {
    write("Advise yourself?\n");
    say(QCTNAME(TP)+" advises "+HIM_HER(TP)+"self something. What a strange "+
        "person!\n");
    return 0;
  }
    
  obs = FIND_STR_IN_OBJECT(s, environment(TP));
  obs = FILTER_OTHER_LIVE(obs);

  if (!sizeof(obs))  return "Advice who?\n";    
  {
    for (i=0; i<sizeof(obs); ++i)  
    {
      obs[i]->catch_msg(QCTNAME(TP)+" advices you that the best way of gaining a "+
                        "lot of money is to not spend them.\n");
    }

    write("You advice "+COMPOSITE_LIVE(obs)+" that the best way of gaining a lot "+
          "of money is is to not spend them.\n");
    tell_room(ENV(TP), QCTNAME(TP)+" gives "+QCOMPLIVE+" an advice.\n",({TP})+obs);
  }
  return 0;
}

string
rassure(string s)
{
  object *a,ob, *obs;
  string str;
  int align, i;

  RICH_ACCESS(2);
  XNOTHUMBLE;

  if (!s || s == "all")
  {
    write("You assure your companions that the future will be good for the market./n");
    say(QCTNAME(TP)+" assures you that the future will be good for the market.\n");
    return 0;
  }

  if (s == "me")  
  {
    write("Assure yourself? Are you that insecure about the future?\n");
    return 0;
  }
    
  obs = FIND_STR_IN_OBJECT(s, environment(TP));
  obs = FILTER_OTHER_LIVE(obs);

  if (!sizeof(obs))  return "Assure who?\n";    
  {
    for (i=0; i<sizeof(obs); ++i)  
    {
      obs[i]->catch_msg(QCTNAME(TP)+" assures you that the future will be good for the market.\n");
    }

    write("You assure "+COMPOSITE_LIVE(obs)+" that the future will be good for the market.\n");
    TP->add_prop(SET_EMOTE,"assuring that the future will be good for the market");
    tell_room(ENV(TP), QCTNAME(TP)+" assures "+QCOMPLIVE+
          " that the future will be good for the market.\n",({TP})+obs);
  }
  return 0;
}

string
rboard(string str)
{
  object ob;
  string mt;

  RICH_ACCESS(8);
  XNOTHUMBLE;

  FIXEUID;

  if (!str || str == "")
      str = "ship";
  
  if (!present(str, ENV(TP)))
      return "There is no "+str+" present!\n";
  
  if (!present(str, ENV(TP))->query_captain())
      return "There is noone here to bribe!\n";
    
  frompurse(1);
  mt = "silver";
  ob = present("silver coin",TP);
  if (!ob)
  {
    mt = "gold";
    ob = present("gold coin",TP);
    if (!ob)
    {
      mt = "platinum";
      ob = present("platinum coin",TP);
      if (!ob)
      {
        topurse(0);
        return "You haven't got any lovely money to pay the captain!\n";
      }
    }
  }

  write("You ask the sailor for a favour and hand him a "+mt+" coin.\n");
  say(QCTNAME(TP)+" asks the sailor for a favour and gives him a "+mt+" coin.\n");
  TP->command("buy ticket");
  TP->command("board");
  ob->split_heap(1);
  ob->move(ENV(TP));
  ob->remove_object();
  topurse(0);
  return 0;
}

string
rbounce()
{
    object purse, w,pc,gc,sc,cc;
    int c,d,f;
    
    RICH_ACCESS(16);
    FILTHILY;
    XNOTHUMBLE;

    write("You bounce around, happily thinking about your awesome wealth.\n");
    say(QCTNAME(TP)+" bounces around happily, thinking about "+HIS_HER(TP)+" awesome "+
	"wealth.\n");
    FIXEUID;
    
    purse = present("rich_club_obj",TP);

    if (!purse->query_prop(CONT_I_CLOSED))
    {
	w = environment(TP);
	pc = present("platinum coin", purse);
	gc = present("gold coin", purse);
	sc = present("silver coin", purse);
	cc = present("copper coin", purse);

	f = 0;
	if (pc) f += move_random_coin_amount(pc, w);
 	if (gc) f += move_random_coin_amount(gc, w);
	if (sc) f += move_random_coin_amount(sc, w);
	if (cc) f += move_random_coin_amount(cc, w);

	if (f)
	{
	    say("You see that "+HIS_HER(TP)+" money-sack bounces around in "+
		"time with "+HIM_HER(TP)+"self, causing a few coins to scatter "+
		"to the ground.\n");
	    write("The money-sack bounces together with you and the coins inside "+
		  "clang as sweet music to your ears.\n");
	}
    }
    return 0;
}

string
rbusy()
{
    RICH_ACCESS(2);
    XNOTHUMBLE;
    
    write("You tell the audience that you are busy making money.\n");
    TP->add_prop(SET_EMOTE,"busy making money");
    say(QCTNAME(TP)+" are busy collecting plats.\n");
    return 0;
}

string
rbuy(string str)
{
    RICH_ACCESS(4);
    XNOTHUMBLE;

    if (!str)
        return "Buy what?\n";

    write("You study the prices carefully, and finally decide to "+
          "purchase "+LANG_ADDART(str)+".\n");
    say(QCTNAME(TP)+" studies the prices carefully, and finally decides "+
        "to purchase "+LANG_ADDART(str)+".\n");
    frompurse(1);
    TP->command("$buy "+str);
    topurse(0);
    return 0;
}
string
rcackle()
{
    RICH_ACCESS(2);
    XNOTHUMBLE;
    
    write("You cackle wealthily.\n");
    say(QCTNAME(TP)+" cackles wealthily.\n");
    return 0;
}

string
rcatch(string s)
{
    object *a, ob, ob2, *obs;
    string str;
    int align, i;

    RICH_ACCESS(16);

    if (s == "all")
    {
        write("Everybody hasn't tossed a coin...\n");
        return 0;
    }

    if (s == "me")  
    {
        write("You will do that anyway....maybe...");
        return 0;
    }
    
    if (!s) return "Catch who's coin?\n";

    obs = FIND_STR_IN_OBJECT(s, environment(TP));
    obs = FILTER_OTHER_LIVE(obs);

    if (!sizeof(obs))  return "Catch who's coin?\n";
    if (sizeof(obs) > 1) return "Catch who's coin?\n";    
    
    if(!obs[0]->query_prop("_live_i_has_tossed_coin"))
    {
        TP->catch_msg(QCTNAME(obs[0])+" hasn't tossed any coin....\n");
        return 0;
    }
    if(obs[0]->query_prop("_live_o_tries_to_catch"))
    {
        TP->catch_msg("Somebody is already waiting...\n");
        return 0;
    }

    obs[0]->add_prop("_live_o_tries_to_catch",TP);
    write("You make yourself ready to catch the coin.\n");

    return 0;
}


string
rchecklog(string str)
{
    string data;

    RICH_ACCESS(33);
    
    if (str == "rich")
    {
	//data = read_file(RMC_RLOG);
	TP->more(RMC_RLOG, 1);
	return 0;
    }
    else if (str == "coat")
    {
	// data = read_file(RMC_CLOG);
	TP->more(RMC_CLOG, 1);
	return 0;
    }

    return "Rchecklog what? (rich or coat)\n";
}

string
rcheckpocket()
{
    RICH_ACCESS(4);
    
    write("You check your pockets for plats.\n");
    TP->add_prop(SET_EMOTE,"searching around for plats");
    say(QCTNAME(TP)+" checks "+HIS_HER(TP)+" pockets for plats.\n");
    return 0;
}

string
rclose()
{
    RICH_ACCESS(1);
    purse = present(PURSE_ID, TP);

    if (!objectp(purse))
    {
        write("The unfathomable has happened, your purse is misplaced!\n");
	return 0;
    }

    purse->do_default_close(PURSE_ID);
    return 0;
}

string
rcomfort(string s)
{
  object *a,ob, *obs;
  string str;
  int align, i;

  RICH_ACCESS(16);
  XNOTHUMBLE;

  if (!s || s == "all")
  {
    write("You comfort everybody because they are so poor and you are so rich.\n");
    say(QCTNAME(TP)+" comforts you, since you are so poor and "+HE_SHE(TP)+" is "+
        "so rich.\n");
    return 0;
  }

  if (s == "me")  
  {
    write("Comfort yourself?\n");
    say(QCTNAME(TP)+" comforts "+HIM_HER(TP)+"self because "+HE_SHE(TP)+" feels "+
        "so poor.\n");
    return 0;
  }
    
  obs = FIND_STR_IN_OBJECT(s, environment(TP));
  obs = FILTER_OTHER_LIVE(obs);

  if (!sizeof(obs))  return "Comfort who?\n";    
  {
    for (i=0; i<sizeof(obs); ++i)  
    {
      obs[i]->catch_msg(QCTNAME(TP)+" comforts you, since you are so poor and "+
                        HE_SHE(TP)+" is so rich.\n");
    }
    write("You comfort "+COMPOSITE_LIVE(obs)+" because the difference in "+
          "wealth between you, ie that you are much richer.\n");

    tell_room(ENV(TP), QCTNAME(TP)+" comforts "+QCOMPLIVE+" because "+HE_SHE(TP)+
                       "is much richer.\n",({TP})+obs);
  }
  return 0;
}

string
rcompare(string s)
{
    object *a, ob, *obs;
    string str;
    int align, acc1, acc2;

    RICH_ACCESS(16);
    XNOTHUMBLE;

    if (s == "me" || !s || s == "all")
    {
        return "Compare with who?\n";
    }

    obs = FIND_STR_IN_OBJECT(s, environment(TP));
    obs = FILTER_OTHER_LIVE(obs);

    if (!sizeof(obs) || sizeof(obs) > 1)  return "Compare with who?\n";
    
    obs[0]->catch_msg(QCTNAME(TP)+" compares "+HIS_HER(TP)+" wealth with yours.\n");
    TP->catch_msg("You compare "+QTNAME(obs[0])+"'s wealth with yours.\n");
    tell_room(ENV(TP), QCTNAME(TP)+" compares "+HIS_HER(TP)+" wealth with "+QTNAME(obs[0])+
              " trying to figure out who's the richest.\n",({TP, obs[0]}));
    
    acc1 = ((total_account(TP) + (RMCMASTER)->query_purchased(TP->query_real_name())) / 100) * 100;
    acc2 = ((total_account(obs[0]) + (RMCMASTER)->query_purchased(obs[0]->query_real_name())) / 100) * 100;

    if (acc1 > acc2)
        str = "richer than ";
    else if (acc1 < acc2)
        str = "a poor fella compared to ";
    else
        str = "about as rich as ";
    
    TP->catch_msg("You are worth about " + acc1 + " plats and " +
		  QTNAME(obs[0])+" about " + acc2 +
		  " plats which means that you are " +
		  str + HIM_HER(obs[0]) + ".\n");
    obs[0]->catch_msg(QCTNAME(TP)+" seems to be "+str+"you.\n");
    tell_room(ENV(TP),QCTNAME(TP)+" seems to be "+str+QTNAME(obs[0])+".\n", ({TP, obs[0]}) );
    
    return 0;
}

string
rconsider(string s)
{
    object *a, ob, *obs;
    string str;
    int align, acc1, acc2;

    RICH_ACCESS(8);
    XNOTHUMBLE;

    if (s == "me" || !s || s == "all")
    {
        return "Consider who?\n";
    }

    obs = FIND_STR_IN_OBJECT(s, environment(TP));
    obs = FILTER_OTHER_LIVE(obs);

    if (!sizeof(obs) || sizeof(obs) > 1)
	return "Consider whom?\n";
    
    obs[0]->catch_msg(QCTNAME(TP)+" gives you a strange look.\n");
    TP->catch_msg("You consider "+QTNAME(obs[0])+"'s wealth.\n");
    tell_room(ENV(TP), QCTNAME(TP)+" peers at "+QTNAME(obs[0])+
              " estimating the difference in cash between them.\n",({TP, obs[0]}));
    
    acc1 = total_account(TP) + (RMCMASTER)->query_purchased(TP->query_real_name());
    acc2 = total_account(obs[0]) +
	(RMCMASTER)->query_purchased(obs[0]->query_real_name());
    if (acc1 > (acc2 + 500))
    {
        TP->catch_msg("You are much wealthier than "+QTNAME(obs[0])+".\n");
        TP->command("rc smile2");
    }
    else if (acc1 > acc2)
    {
        TP->catch_msg("You are wealthier than "+QTNAME(obs[0])+".\n");
        TP->command("smile");
    }
    else if ((acc1 + 500) < acc2)
    {
        TP->catch_msg(QCTNAME(obs[0])+" are much wealthier than you.\n");
        TP->command("grumble pitiful");
    }
    else if (acc1 < acc2)
    {
        TP->catch_msg(QCTNAME(obs[0])+" are wealthier than you.\n");
        TP->command("sulk");
    }
    else
    {
        TP->catch_msg("You are as wealthy as "+QTNAME(obs[0])+".\n");
        TP->command("shake "+obs[0]->query_name());
    }
    return 0;
}

string
rconvince(string s)
{
  object *a,ob, *obs;
  string str;
  int align, i;

  RICH_ACCESS(2);
  XNOTHUMBLE;

  if (!s || s == "all")
  {
    write("You can't convince them all, try one at a time...\n");
    return 0;
  }

  if (s == "me")  
  {
    write("Convince yourself?\n");
    TP->add_prop(SET_EMOTE,"trying to convince someone");
    return 0;
  }
    
  obs = FIND_STR_IN_OBJECT(s, environment(TP));
  obs = FILTER_OTHER_LIVE(obs);

  if (!sizeof(obs))  return "Convince who?\n";    
  {
    for (i=0; i<sizeof(obs); ++i)  
    {
      obs[i]->catch_msg(QCTNAME(TP)+" tries to convince you that the only thing that is important is money.\n");
    }

    write("You try to convince "+COMPOSITE_LIVE(obs)+" that the only thing that is important is money.\n");
    tell_room(ENV(TP), QCTNAME(TP)+" tries to convince "+QCOMPLIVE+
          " that the only thing that is important is money.\n",({TP})+obs);
  }
  return 0;
}

string 
rdislike()
{
    RICH_ACCESS(8);
    XNOTHUMBLE;
    
    write("You show, with an evil grin, how much you hate poor and greedy people.\n");
    TP->add_prop(SET_EMOTE,"hates poor and greedy people");
    say(QCTNAME(TP)+" shows you how much "+HE_SHE(TP)+" dislikes people as poor as you.\n");
    return 0;
}

string
rdisgust(string s)
{
    object *a,ob, *obs;
    string str;
    int align, i;

    RICH_ACCESS(8);
    XNOTHUMBLE;

    if (!s || s == "all")
    {
        write("You look at the crowd in disgust, you really hate sniveling beggars!\n");
        say(QCTNAME(TP)+" looks at you and the others with disgust showing what "+
            HE_SHE(TP)+" thinks of sniveling beggars.\n");
        
        return 0;
    }

    if (s == "me")  
    {
        write("Disgusted of yourself?\n");
        TP->add_prop(SET_EMOTE,"is disgusted by "+HIM_HER(TP)+"self.");
        return 0;
    }
    
    obs = FIND_STR_IN_OBJECT(s, environment(TP));
    obs = FILTER_OTHER_LIVE(obs);

    if (!sizeof(obs))  return "Dislike who?\n";    
    {
        for (i=0; i<sizeof(obs); ++i)  
        {
            obs[i]->catch_msg(QCTNAME(TP)+" looks at you with disgust as you "+
                              "showing what a sniveling beggar you are.\n");
        }

        write("You look at "+COMPOSITE_LIVE(obs)+" with disgust, you can't stand "+
              "sniveling beggars!\n");
        tell_room(ENV(TP), QCTNAME(TP)+" looks at "+QCOMPLIVE+
                  " with disgust, showing what "+HE_SHE(TP)+" thinks of sniveling "+
                  "beggars.\n",({TP})+obs);
    }
    return 0;
}

string
rdream()
{
    RICH_ACCESS(2);
    
    write("You start to dream about all the fortunes that lies ahead.\n");
    say(QCTNAME(TP)+" starts to dream about all the fortunes that lies ahead.\n");
    return 0;
}

string
rdrop()
{
  object ob;

  RICH_ACCESS(2);
  XNOTHUMBLE;
  
  frompurse(1);
  if (ob = present("copper coin",TP)) /* MAKE SURE YOU DROP A COPPER COIN */
  {
    write("You yawn and drop one copper coin just to make sure the worth of money.\n");
    TP->add_prop(SET_EMOTE,"yawning tiredly");
    say(QCTNAME(TP)+" yawns and smiles coldly as "+HE_SHE(TP)+" drops one copper coin.\n");
    ob->split_heap(1);
    ob->move(ENV(TP));
    topurse(0);
    return 0;
  }
  topurse(0);
  return "You haven't got any coppers!\n";
}

string
rdropall()
{
    object ob;
    RICH_ACCESS(4);
    XNOTHUMBLE;

    frompurse(1);
    ob = present("copper coin", TP);

    if (!ob)
        return "You don't have any coppers to drop.\n";
    
    write("You drop all your coppers, because their low value. You like "+
          "_big_ money!\n");
    say(QCTNAME(TP)+" drops all "+HIS_HER(TP)+" coppers, because of their "+
        "low value. "+QCTNAME(TP)+" likes _big_ money!\n");
    ob->move(environment(TP));
    topurse(0);
    return 0;
}

string
revaluate()
{
    RICH_ACCESS(2);
    XNOTHUMBLE;
    
    write("You announce your inner feelings about how you evaluate other people.\n");
    say(QCTNAME(TP)+" announces that the only way to evaluate a person is to check that "+
        "person's bank account!\n");
    return 0;
}

string
rget()
{
  RICH_ACCESS(1);
  
  purse = present("rich_club_obj", TP);
  
  if (present("coin",purse) || present("gem",purse))
  {
      write("You look into your "+query_purse()+" and quickly pick up its contents.\n");
      say(QCTNAME(TP)+" looks into "+HIS_HER(TP)+" "+query_purse()+
          " and quickly picks up its contents.\n");
      frompurse(0);
  }
  else
  {
      write("You look into your "+query_purse()+" and find out that it is empty!\n");
      say(QCTNAME(TP)+" looks into "+HIS_HER(TP)+" "+query_purse()+
          " and finds out that it is empty! What a disaster!\n");
  }
  
  return 0;
}

string
rgreet(string s)
{
  object *a,ob, *obs;
  string str;
  int align, i;

  RICH_ACCESS(1);
  XNOTHUMBLE;
  
  if (!s || s == "all")
  {
    write("You greet everyone even though they are poor and miserable creatures.\n");
    say(QCTNAME(TP)+" greets you even though "+HE_SHE(TP)+" knows you are poor "+
        "compared to "+HIM_HER(TP)+".\n");
    return 0;
  }

  if (s == "me")  
  {
    write("Greet yourself?\n");
    say(QCTNAME(TP)+" greets "+HIM_HER(TP)+"self because "+HE_SHE(TP)+" is so rich.\n");
    return 0;
  }
    
  obs = FIND_STR_IN_OBJECT(s, environment(TP));
  obs = FILTER_OTHER_LIVE(obs);

  if (!sizeof(obs))  return "Greet who?\n";

  for (i=0; i<sizeof(obs); ++i)  
  {
    obs[i]->catch_msg(QCTNAME(TP)+" greets you although "+HE_SHE(TP)+" knows you are poor and miserable.\n");
    write("You greet "+COMPOSITE_LIVE(obs)+" even though "+HE_SHE(obs[i])+" is poor and miserable.\n");
  }
  tell_room(ENV(TP), QCTNAME(TP)+" greets "+QCOMPLIVE+
           " even though "+HE_SHE(TP)+" knows "+COMPOSITE_LIVE(obs)+" is poor and miserable.\n",({TP})+obs);

  return 0;
}

string
rgrin()
{
    RICH_ACCESS(2);
    XNOTHUMBLE;
    
    write("You grin as you think of the amount of money you have.\n");
    TP->add_prop(SET_EMOTE,"showing a wealthy grin");
    say(QCTNAME(TP)+" shows with a wealthy grin that "+HE_SHE(TP)+" got lots of plats.\n");
    return 0;
}

string
rhide()
{
    int v;
    
    RICH_ACCESS(1);
    FIXEUID;

    v = (RMCMASTER)->query_visible(TP->query_real_name());
    
    if (v)
    {
        write("You hide your "+query_purse()+" so that noone can see that you are so wealthy "+
              "and leave you alone.\n");
        say(QCTNAME(TP)+" hides "+HIS_HER(TP)+" "+query_purse()+" so that noone can see it and "+
            "thereby come running begging.\n");
        (RMCMASTER)->set_visible(TP->query_real_name(), 0);
        return 0;
    }
    write("You fetch your "+query_purse()+" from somewhere inside your clothes and place it "+
          "so that everyone can see that you are so wealthy.\n");
    say(QCTNAME(TP)+" fetches "+HIS_HER(TP)+" "+query_purse()+" from somewhere inside the "+
        "clothes and places it so that everyone can see it.\n");
    (RMCMASTER)->set_visible(TP->query_real_name(), 1);
    return 0;
}

string
rhold()
{
    RICH_ACCESS(16);
    XNOTHUMBLE;
    
    write("You hold your "+query_purse()+" close to your body, in case that someone would "+
          "make an attempt to steal it from you, and all the lovely plats that it holds.\n");
    say(QCTNAME(TP)+" holds "+HIS_HER(TP)+" "+query_purse()+" close to "+HIS_HER(TP)+" body, "+
        "in case someone would try to steal it and its contents from "+HIM_HER(TP)+".\n");
    return 0;
}

string
rhope()
{
    RICH_ACCESS(4);
    XNOTHUMBLE;
    
    write("You hope that the future will be filled with good opportunities of making lots "+
          "of money.\n");
    say(QCTNAME(TP)+" hopes that the future will be filled with good opportunities of making "+
        "lots of money.\n");
    return 0;
}

string
rhumble(string str)
{
    int hum;

    RICH_ACCESS(1);

    FIXEUID;

    hum = (RMCMASTER)->query_humble(TP->query_real_name());

    if (str == "on")
    {
        if (hum == 1)
            return "You're already humble enough!\n";
        
        write("You feel much more humble now.\n");
        (RMCMASTER)->toggle_humble(TP->query_real_name());
        return 0;
    }
    if (str == "off")
    {
        if (hum == 0)
            return "You're already showing off yer wealth!\n";
        
        write("You feel like showing off!\n");
        (RMCMASTER)->toggle_humble(TP->query_real_name());
        return 0;
    }
    return "Rhumble what? On or off?\n";
}   

int
is_member(object obj)
{
    return RMCMASTER->query_member(obj->query_real_name());
}

/*
 * Filters mortals, well if you are a wiz you are filtered out.
 */
int
is_mortal(object obj)
{
   if(obj->query_wiz_level()) return 0;

   return 1;
}

/*
 * Filters out suspended members, returns 1 if not suspended.
 * This is needed since suspended members cant list members,
 * hence they should not either be on the list.
 */
int
is_active(object obj)
{
    if(RMCMASTER->query_suspension(obj->query_real_name())) return 0;

    return 1;
}

mixed *
calc_val(object obj)
{
    return ({ obj, (RMCMASTER)->query_valuation(obj->query_real_name()) });
}

int
compare_val(mixed *a, mixed *b)
{
    if (a[1] > b[1])
	return -1;
    if (a[1] < b[1])
	return 1;
    return 0;
}

string
rstop(string str)
{
    if ((RMCMASTER)->query_level(TP->query_real_name()) < 16)
        return 0;

    if (str == "counting")
    {
        update_actions();
        write("You stop counting.\n");
        remove_alarm(id[0]);

        return 0;
    }
    else if (str == "done")
    {
        update_actions();
        write("You finished counting.\n");
        return 0;
    }
    else if (id)
    {
        write("You are counting, if you want to stop you have to do " +
	      "<rc stop counting>\n");
        return 0;
    }
    else
    {
	write("You arent counting anything.\n");
	return 0;
    }
}

void
rcount_up(int *count_arg, object ob, object tp, string what)
{
    int apa, bepa, time;

    FIXEUID;

    time = MAX(2 ,MIN(5, 400/tp->query_stat(SS_INT)));

    count_arg[2] += count_arg[1];

    if (count_arg[2] < ob->num_heap())
    {
        bepa = random(4) + 1;

        if (bepa == 1)
            tp->command("say I have "+count_arg[2] + " " +what);
        else if (bepa == 2)
            tp->command("say And "+count_arg[2] + " " +what);
        else if (bepa == 3)
            tp->command("say Ahh... I have "+ count_arg[2] + " " + what + ".");
        else if (bepa == 4)
        {
            tp->command("grin greed");
            tp->command("say  " + capitalize(count_arg[2]) + " " + what +
                        " is what " + "I have.");
        }

        apa = set_alarm(itof(time), 0.0, &rcount_up(count_arg, ob, tp, what));
        id = get_alarm(apa);
    }
    else
    {
        tp->command("shout YES! I have "+ ob->num_heap() + " " + what);
        rstop("done");
    }
}

string
rcount(string str)
{
    string *tmp;
    int *count_arg, intg, apa, time;
    object ob;

    RICH_ACCESS(16);
    XNOTHUMBLE;

    if (!strlen(str))
    {
	write("Count what? Platinum? Gold? Silver?\n");
        return 0;
    }

    if (str != "platinum" && str != "gold" && str != "silver")
    {
	write("You don't really feel like counting anything else than platinum, "+
	      "gold and of course silver coins.\n");
	return 0;
    }

    str += " coin";

    ob = present(str, TP);

    if (!ob || !ob->num_heap()) 
    {
	write("You sulk as you realize you dont have any "+str+
	      "s to count.\n");

        return 0;
    }

    intg = this_player()->query_stat(SS_INT);

    str += "s";

    write("You begin counting your "+str+".\n");

    time = MAX(2 ,MIN(5, 400/intg));
    count_arg = ({ 5 * (60 / intg), 5 * (intg / 10 + 1), 0 });
    apa = set_alarm(itof(time), 0.0, &rcount_up(count_arg, ob, TP, str));
    id = get_alarm(apa);

    return 0;
}

string
rlist()
{
    object *list, *wizards, *suspended, p;
    mixed *sorted;
    int i,j,lvl, no, who;
    string title, str;

    RICH_ACCESS(16);
  
    FIXEUID;

    say(QCTNAME(TP)+" looks around searching for rich people.\n");
    write("\n+-------------------------------------------------------+\n");
    write("| $              Wealthy people working               $ |\n");
    write("+-------------------------------------------------------+\n");

    list = filter(users(), &is_member());

    if(is_mortal(TP)) 
    {
        /* Filter Mortals */
        list = filter(list, &is_mortal());
	//list -= wizards;

        /* Filter Suspended members */
        list = filter(list, &is_active());
	//list -= suspended;
    }

    if (sizeof(list))
    {
        no = sizeof(list);

        write(sprintf("| There are %3d active members right now.               |\n",
	no-1));

    	list = map(list, &calc_val());
    	list = sort_array(list, &compare_val());

    	for (j = 0; j < no; j++)
    	{
    	    p = list[j][0];
    	    lvl = (RMCMASTER)->query_level(p->query_real_name());
	    
    	    if (!p->query_invis() || TP->query_wiz_level())
    	    {
		write(sprintf("| (%s) %-14s %-33s|\n",
			      (p == TP ? "You" :
			       p->query_wiz_level() ? "Wiz" :
			       RMCMASTER->query_president() == p->query_real_name() ? "Prs" :
			       RMCMASTER->query_vice_president() == p->query_real_name() ? "VPr" : 
			       RMCMASTER->query_suspension(p->query_real_name()) ? "Sus" : 
			       "---"),
			      p->query_name(),
			      (lvl &&
			       (RMCMASTER)->query_humble(p->query_real_name()) ?
			       "Humble member" :
			       (RMCMASTER)->query_title(p->query_real_name()))
			  ));
	    } 
        }
    }
    write("+-------------------------------------------------------+\n\n");
    return 0;
}

string
rjump()
{
    RICH_ACCESS(4);
    XNOTHUMBLE;
    
    purse = present("rich_club_obj",TP);
    if (present("platinum coin", purse))
    {
        write("You check your "+query_purse()+" and jump high in pure happiness since you find lovely plats "+
          "in it.\n");
        say(QCTNAME(TP)+" checks "+HIS_HER(TP)+" "+query_purse()+" and jumps high in pure happiness.\n");
        return 0;
    }

    write("You sulk when you realize that your "+query_purse()+" hasn't got any plats in it.\n");
    say(QCTNAME(TP)+" starts to sulk as "+HE_SHE(TP)+" finds out that "+HIS_HER(TP)+" "+query_purse()+
        "hasn't got any lovely plats.\n");
    return 0;
}

string
rlook()
{
    RICH_ACCESS(2);
    XNOTHUMBLE;
  
    purse = present("rich_club_obj",TP);
  
    TP->add_prop(SET_EMOTE,"looking eagerly into a nice "+query_purse());

    if (!(present("coin",purse) || present("gem",purse)))
    {
        say(QCTNAME(TP)+" looks eagerly into "+HIS_HER(TP)+" "+query_purse()+
            " checking its contents, but it is empty!\n");
        write("But...but...it's empty!\n");
        TP->command("sulk");
    }
    else
    {
        say(QCTNAME(TP)+" looks eagerly into "+HIS_HER(TP)+" "+query_purse()+
            " checking its contents.\n");
        TP->command("exa "+query_purse());
        TP->command("rc grin");
    }
  
    return 0;
}

string
rloot(string str)
{
    object *ob, ob2;
    int i,j,x,y;
    string *ctypes,*tmp;

    RICH_ACCESS(8);
    XNOTHUMBLE;

    if (!str || str == "")
        ctypes = ({"platinum", "gold", "silver", "copper"});
    else
    {
        tmp = explode(str, "");

        ctypes = ({ });
        
        for (i = 0; i < sizeof(tmp); i++)
        {
            switch(tmp[i])
            {
            case "p":
                ctypes += ({"platinum"});
                break;
            case "g":
                ctypes += ({"gold"});
                break;
            case "s":
                ctypes += ({"silver"});
                break;
            case "c":
                ctypes += ({"copper"});
                break;
            default:
                break;
            }
        }
    }

    x = 0;
    
    ob = FIND_STR_IN_OBJECT("corpses", environment(TP));

    if (sizeof(FIND_STR_IN_OBJECT("coins", environment(TP))))
    {
        y = 0;

        for (j = 0; j < sizeof(ctypes); j++)
        {
            ob2 = present(ctypes[j] + " coin", environment(TP));
            
            if (ob2)
            {
                y = 1;
                ob2->move(TP);
            }
        }
        if (y)
        {
            write("You quickly pick up the coins from the ground.\n");
            say(QCTNAME(TP)+" quickly picks up the coins from the ground.\n");
            topurse(0);
            x = 1;
        }
        else
        {
            write("It was only scrap money on the ground, nothing for you "+
                  "to bother.\n");
        }    
    }
    
    if (!sizeof(ob))
        return "There's no corpse here!\n";

    for (i = 0; i < sizeof(ob); i++)
    {
        if (sizeof(FIND_STR_IN_OBJECT("coins", ob[i])))
        {
            y = 0;

            for (j = 0; j < sizeof(ctypes); j++)
            {
                ob2 = present(ctypes[j] + " coin", ob[i]);
            
                if (ob2)
                {
                    y = 1;
                    ob2->move(TP);
                }
            }
        if (y)
            x = 1;
        }
    }

    if (!x)
        return "There's no money to loot!\n";
    
    if (sizeof(ob) > 1)
    {
        write("You look with greed at the corpses, since you can clearly feel the "+
              "smell of money from them.\nYou quickly search the corpses and put the "+
              "money into your "+query_purse()+".\n");
        say(QCTNAME(TP)+" looks with greed at the corpses, since "+HE_SHE(TP)+
            " can clearly feel the smell of money from them.\n"+QCTNAME(TP)+
            " quickly searches the corpses and puts the money into "+HIS_HER(TP)+
            " "+query_purse()+".\n");
    }
    else
    {
        write("You look with greed at the corpse, since you can clearly feel the "+
              "smell of money from it.\nYou quickly search the corpse and put the "+
              "money into your "+query_purse()+".\n");
        say(QCTNAME(TP)+" looks with greed at the corpse, since "+HE_SHE(TP)+
            " can clearly feel the smell of money from it.\n"+QCTNAME(TP)+
            " quickly searches the corpse and puts the money into "+HIS_HER(TP)+
            " "+query_purse()+".\n");
    }
    
    topurse(1);
    return 0;
}

string
rmembers()
{
    RICH_ACCESS(32);

    write((RMCMASTER)->query_member_list());
    return 0;
}

string 
rmini()
{
    RICH_ACCESS(4);
    
    if (function_exists("set_bank_fee",ENV(TP))=="/lib/bank")
    {
        frompurse(1);
        write("With a galant gesture you give the clerk some money to "+
              "exchange them for you.\n");
        TP->add_prop(SET_EMOTE,"smiling very proudly");
        say("With a galant gesture "+QCTNAME(TP)+" gives some money to the "+
            "clerk to exchange.\n");
        TP->command("minimize coins");
        topurse(1);
        return 0;
    }
    return "You can't do that here!\n";
}

string
rnews()
{
    RICH_ACCESS(1);
    FIXEUID;

    write("\n+--------------------------------------------------+\n"+
          "| $             RICH MEN'S CLUB NEWS             $ |\n"+
          "+--------------------------------------------------+\n"+
          "|                                                  |\n"+
          "| - For all of the filthily rich and above:        |\n"+
          "|   Rc wonder works slightly better, and even,     |\n"+
          "|   if we are lucky, correctly. :)        (971130) |\n"+
          "|                                                  |\n"+
          "| - Rc Tboard has moved back to its old position   |\n"+
          "|   as Filthily Rich command              (971130) |\n"+
          "|                                                  |\n"+
          "| - Filthily Rich has recieved another command:    |\n"+
          "|   Rc Bounce.                            (971130) |\n"+
          "|                                                  |\n"+
          "| - Rc Counhi has been reintroduced, the command   |\n"+
          "|   is now: Rc Count                               |\n"+
          "|   To use together with this is: Rc Stop          |\n"+
          "|                                         (060201) |\n"+
          "|                                                  |\n"+
          "| Current Maintainer: Lunatari      Creator: Conan |\n"+
          "+--------------------------------------------------+\n\n");
    (RMCMASTER)->clear_news(TP->query_real_name());
    return 0;
}

string
rnote(string str)
{
    RICH_ACCESS(1);
    FIXEUID;
    
    if (!str)
        return "Notification on/off?\n";

    if (str == "on")
    {
        (RMCMASTER)->set_notification(TP->query_real_name(), 1);
        write("You will now feel the shifts in the market.\n");
        return 0;
    }
    else if (str == "off")
    {
        (RMCMASTER)->set_notification(TP->query_real_name(), 0);
        write("You will now ignore the shifts in the market.\n");
        return 0;
    }
    return "Notification on/off?\n";
}

string
ropen()
{
    RICH_ACCESS(1);
    purse = present(PURSE_ID, TP);

    if (!objectp(purse))
    {
        write("The unfathomable has happened, your purse is misplaced!\n");
	return 0;
    }

    purse->do_default_open(PURSE_ID);
    return 0;
}

string
roffer(string s)
{
  object *a,ob, *obs;
  string str;
  int align, i;

  RICH_ACCESS(1);
  XNOTHUMBLE;
  
  if (!s || s == "all")
  {
    write("You offer everyone a loan with a HUGE interest.\n");
    say(QCTNAME(TP)+" offers everyone a loan with HUGE interest.\n");
    return 0;
  }

  if (s == "me")  
  {
    write("Offer yourself?\n");
    say(QCTNAME(TP)+" offers "+HIM_HER(TP)+"self a loan with no interest.\n");
    return 0;
  }
    
  obs = FIND_STR_IN_OBJECT(s, environment(TP));
  obs = FILTER_OTHER_LIVE(obs);

  if (!sizeof(obs))  return "Offer to whom?\n";
    
  for (i=0; i<sizeof(obs); ++i)  
  {
    obs[i]->catch_msg(QCTNAME(TP)+" offers you a loan with HUGE interest, "+
      "because "+HE_SHE(TP)+" thinks you need it badly.\n");
  }

  write("You offer "+COMPOSITE_LIVE(obs)+" a loan with HUGE interest. "+COMPOSITE_LIVE(obs)+
        " seems to need it badly.\n");
  tell_room(ENV(TP), QCTNAME(TP)+" offers a loan to "+QCOMPLIVE+
              " to a HUGE interest. "+COMPOSITE_LIVE(obs)+" looks happy.\n",({TP})+obs);

  return 0;
}

string
rorder(string str)
{
    RICH_ACCESS(4);

    if (!str)
        return "Order what?\n";

    write("You study the prices carefully, and finally decides to "+
          "order "+LANG_ADDART(str)+".\n");
    say(QCTNAME(TP)+" studies the prices carefully, and finally decides "+
        "to order "+LANG_ADDART(str)+".\n");
    frompurse(1);
    TP->command("$order "+str);
    topurse(0);
    return 0;
}

string
rpanic()
{
    RICH_ACCESS(16);
    XNOTHUMBLE;
    
    write("You start to panic as you suddenly get a thought that you have lost your "+
          query_purse()+". You start to search fiercly through your pockets and "+
          "with relief you find that it is still there.\n");
    say(QCTNAME(TP)+" suddenly gets panic in "+HIS_HER(TP)+" eyes and starts to "+
        "search fiercly through "+HIS_HER(TP)+" pockets. "+capitalize(HE_SHE(TP))+
        " appearantly found what "+HE_SHE(TP)+" was searching for since "+HE_SHE(TP)+
        " sighs with relief and calms down.\n");
    return 0;
}

string
rpat()
{
  RICH_ACCESS(1);
  XNOTHUMBLE;
  
   write("You pat your "+query_purse()+" lovingly. It looks well filled.\n");
   TP->add_prop(SET_EMOTE,"patting a well filled money purse");
   say(QCTNAME(TP)+" pats "+HIS_HER(TP)+" "+query_purse()+" lovingly. It looks well filled.\n");
   return 0;
}

string
rpeer(string s)
{
    object *a,ob, *obs;
    string str;
    int align, i;

    RICH_ACCESS(4);
    XNOTHUMBLE;

    if (!s || s == "all")
    {
        write("You peer at tour companions, disliking the competition.\n");
        say(QCTNAME(TP)+" peers at you, obviously disliking the competition.\n");
        return 0;
    }

    if (s == "me")
    {
        write("Peer at yourself?\n");
        return 0;
    }

    obs = FIND_STR_IN_OBJECT(s, environment(TP));
    obs = FILTER_OTHER_LIVE(obs);

    if (!sizeof(obs))  return "Peer who?\n";
    {
        for (i=0; i<sizeof(obs); ++i)
        {
            obs[i]->catch_msg(QCTNAME(TP)+" peers at you, obviously disliking the competition.\n");
            TP->catch_msg("You peer at "+QTNAME(obs[i])+", disliking the competition.\n");
        }
        tell_room(ENV(TP), QCTNAME(TP)+" peers at "+QCOMPLIVE+
                  ", obviously displeased with the competition.\n",({TP})+obs);
    }
    return 0;
}

string 
rpick()
{
    RICH_ACCESS(2);
    XNOTHUMBLE;
    
    write("You feel the smell from gold and platinum coins here.\n");
    set_alarm(0.0, 0.0, "getta_coins", TP);
    TP->add_prop(SET_EMOTE,"smelling the nice smell of gold and platinum");
    say(QCTNAME(TP)+" stops as if "+HE_SHE(TP)+" is smelling something.\n");
    return 0;
}

string
rnudge()
{
    RICH_ACCESS(1);
    XNOTHUMBLE;
    write("You nudge everybody in the room, showing how much joy there is in money.\n");
    TP->add_prop(SET_EMOTE,"having very fun with money");
    say(QCTNAME(TP)+" nudges you as "+HE_SHE(TP)+" shows you how much joy there is in money.\n");
    return 0;
}

string
rpos()
{
    RICH_ACCESS(16);
    FILTHILY;

    write((RMCMASTER)->query_pos(TP->query_real_name(), 1));
    return 0;
}

string
rps(string str)
{
    int i;

    RICH_ACCESS(33);
    FIXEUID;

    write((RMCMASTER)->query_pos(str));
    return 0;
}

string
rpurge()
{
  object *players;
  int i,lvl,n;

  RICH_ACCESS(33);

  if (!purge)
  {
    write("\n<RMC> Will purge all wiz members onlogged without clubobject.\n"+
      "<RMC> Type 'rbanish' again to execute the command.\n\n");
    purge = 1;
    return 0;
  }
  purge = 0;
  players = users();

  write("\n\n<RMC> Starting to purge...\n");
  for (i = 0; i < sizeof(players); i++)
  {
    lvl = (RMCMASTER)->query_level(players[i]->query_real_name());
    if (lvl && !present("rich_club_obj",players[i]) && players[i]->query_wiz_level())
    {
      write("<RMC> Purging "+capitalize(players[i]->query_real_name())+".\n");
      (RMCMASTER)->purge_member(players[i]->query_real_name(),
			       TP->query_real_name());
      n++;
    }
  }
  write("<RMC> Done. ");
  if (n)
  {
    write(n);
    write(" members purged.\n\n");
    return 0;
  }
  write("Found not anyone to purge.\n\n");
  return 0;
}

string
rput()
{
    int d;
    
    RICH_ACCESS(1);
  
    d = topurse(0);

    purse = present("rich_club_obj",TP);
    if (d == 0)
    {
        write("You look in your "+purse->short()+" and notice some more "+
	      "room for your coins.\n");
        say(QCTNAME(TP)+" looks in "+HIS_HER(TP)+" "+query_purse()+
            " to make sure there is room left.\n");
    }
    else
    {
        write("You look in your "+purse->short()+" and notice that it "+
	      "is full.\n");
        say(QCTNAME(TP)+" looks in "+HIS_HER(TP)+" "+query_purse()+
            " to make sure there is room left, which it isn't, because "+
	    "it's full of lovely coins.\n");
    }
  
    return 0;
}

string
rscream()
{
    RICH_ACCESS(1);
    XNOTHUMBLE;
    
    write("AAAAARRRRGGGHHHH!!!!!\nYou scream in agony after discovering that you have "+
          "missed an opportunity to make lots of money!\n");
    say(QCTNAME(TP)+" screams high after discovering that "+HE_SHE(TP)+" has missed "+
        "an opportunity to make lots of money!\n");
    return 0;
}

string
rsearch()
{
    RICH_ACCESS(8);
    
    write("You start to turn your "+query_purse()+" inside out realizing that you spent way too much "+
          "money at the pub last night.\n");
    TP->add_prop(SET_EMOTE,"is holding a "+query_purse()+" inside out looking really poor");
    say(QCTNAME(TP)+" turns "+HIS_HER(TP)+" "+query_purse()+" inside out realizing that "+
        HE_SHE(TP)+" spent way too much money at the pub last night.\n");
    return 0;
}

string
rsell(string str)
{
    RICH_ACCESS(4);

    if(!str)
        return "Sell what?\n";
    
    say(QCTNAME(TP)+" decides to increase "+HIS_HER(TP)+" fortune by "+
        "selling some stuff, expensive...\n");
    write("You decide to sell some stuff and increase your wealth.\n");
    TP->command("$sell "+str);
    topurse(1);
    return 0;
}

string
rsetlevel(string str)
{
    string *arr, name;
    int level;

    RICH_ACCESS(33);

    FIXEUID;
    
    arr = explode(str, " ");

    if (sizeof(arr) != 2)
        return "(RMC) Error. Not able to set that level\n";

    name = arr[0];
    level = atoi(arr[1]);

    if ((RMCMASTER)->set_level(name, level))
    {
        write("(RMC) " + capitalize(name) +
	      " has now level " + level + " in RMC.\n");
        return 0;
    }
    return "(RMC) Error. Not able to set that level\n";
}

string
rsetnews()
{
    RICH_ACCESS(33);

    FIXEUID;
    (RMCMASTER)->set_all_news();
    write("OK. All members news status have been set.\n");
    return 0;
}

string
rshop()
{
    RICH_ACCESS(2);
    
    write("You laugh at the prices in the store.\n");
    say(QCTNAME(TP)+" laughs at the prices in the store.\n");
    return 0;
}

string
rsing()
{
    RICH_ACCESS(4);
    XNOTHUMBLE;
    
    write("You sing a little song about how fun there is to be wealthy, and how boring it is "+
          "to be poor.\n");
    say(QCTNAME(TP)+" sings a little song about how fun there is to be wealthy, and how boring "+
        "it is to be poor.\n");
    return 0;
}

string
rslip(string s)
{
    object *a,ob, *obs;
    string str;
    int align, i;

    RICH_ACCESS(4);
    
    if (s == "me" || !s || s == "all")
    {
        return "Slip a coin to who?\n";
    }

    obs = FIND_STR_IN_OBJECT(s, environment(TP));
    obs = FILTER_OTHER_LIVE(obs);

    frompurse(1);
    if (!sizeof(obs))  return "Slip a coin to who?\n";
    {
        for (i=0; i<sizeof(obs); ++i)
        {
            if(present("platinum coin",TP))
            {
                if(random(obs[i]->query_skill(SS_AWARENESS))>=TP->query_skill(SS_SNEAK))
                {
                    obs[i]->catch_msg(QCTNAME(TP)+" slips a plat into your pocket.\n");
                }
                TP->catch_msg("You slip a plat into "+QTNAME(obs[i])+"'s pocket.\n");
                TP->command("rc smile2");
                tell_room(ENV(TP), QCTNAME(TP)+" slips a plat into "+QTNAME(obs[i])+
                          "'s pocket.\n",({TP,obs[i]}));
                ob = present("platinum coin",TP);
                ob->split_heap(1);
                ob->move(obs[i]);
           }
            else
                TP->catch_msg("You have no plats to give "+QTNAME(obs[i])+",\n");
        }
    }
    topurse(0);
    return 0;
}

string
rsmile()
{
  RICH_ACCESS(1);
  XNOTHUMBLE;
  
  write("You smile greedily over the big income of yours.\n");
  TP->add_prop(SET_EMOTE,"smiling greedily");
  say(QCTNAME(TP)+" smiles so greedily over "+HIS_HER(TP)+" big income "+
     "that you almost feel sick.\n");
  return 0;
}

string
rsmile2()
{
    RICH_ACCESS(1);
  
    if ((RMCMASTER)->query_humble(TP->query_real_name()))
    {
        write("You smile generously.\n");
        TP->add_prop(SET_EMOTE,"smiling generously");
        say(QCTNAME(TP)+" smiles generously.\n");
        return 0;
    }
    write("You smile wealthily.\n");
    TP->add_prop(SET_EMOTE,"smiling wealthily");
    say(QCTNAME(TP)+" smiles wealthily.\n");
    return 0;
}

string
rsmirk()
{
    RICH_ACCESS(2);
    XNOTHUMBLE;
    
    write("You smirk wealthily, remembering the struggle from a poor newbie to the position "+
          "you have today.\n");
    say(QCTNAME(TP)+" smirks wealthily, remembering "+HIS_HER(TP)+" struggle from poor newbie "+
        "to the position "+HE_SHE(TP)+" has today.\n");
    return 0;
}

string
rspent()
{
  int hmuch;

  RICH_ACCESS(33);

  seteuid(getuid(TO));

  write("\n<RMC> The Mortals have spent " +
	(RMCMASTER)->query_howmuch() +
	" plats on the RMC.\n\n");
  return 0;
}

string
rsponsor(string s)
{
    object *a, ob, ob2, *obs, tp;
    string str;
    int align, i;

    RICH_ACCESS(4);
    FIXEUID;
    
    tp = TP;
    purse = present("rich_club_obj",TP);
    
    if (!s || s == "all")
    {
        write("Nah, you don't wanna sponsor the whole world...\n");
        return 0;
    }

    if (s == "me")  
    {
        write("Sponsor yourself? Strange....\n");
        return 0;
    }
    
    obs = FIND_STR_IN_OBJECT(s, environment(tp));
    obs = FILTER_OTHER_LIVE(obs);

    if (!sizeof(obs))  return "Sponsor who?\n";    
    {
        for (i=0; i<sizeof(obs); ++i)  
        {
            ob = present("platinum coin", tp);
	    if (purse)
		ob2 = present("platinum coin",purse);

            if (ob)
            {
                obs[i]->catch_msg(QCTNAME(tp)+" sponsors you with a platinum coin.\n");
                tp->catch_msg("You sponsor "+QTNAME(obs[i])+" with a platinum coin.\n");
                tell_room(ENV(tp), QCTNAME(TP)+" sponsors "+QTNAME(obs[i])+
                          " with a platinum coin.\n",({tp, obs[i]}));
                ob->split_heap(1);
                ob->move(obs[i]);
            }
            else if (ob2)
            {
                obs[i]->catch_msg(QCTNAME(tp)+" gets a platinum coin from "+
				  HIS_HER(tp)+" "+ query_purse()+".\n"+
				  QCTNAME(tp)+" sponsors you "+
                                  "with a platinum coin.\n");
                tp->catch_msg("You get a plat from your "+query_purse()+".\nYou "+
                              "sponsor "+QTNAME(obs[i])+" with a platinum coin.\n");
                tell_room(ENV(tp), QCTNAME(tp)+" gets a platinum coin from "+
			  HIS_HER(tp)+
                          query_purse()+".\n"+QCTNAME(tp)+" sponsors "+
                          QTNAME(obs[i])+" with a platinum coin.\n",({tp, obs[i]}));
                ob2->split_heap(1);
                ob2->move(obs[i]);
           }
            else
                tp->catch_msg("You haven't got the money to sponsor "+
			      QTNAME(obs[i])+"!\n");
        }
    }
    return 0;
}

string
rsulk()
{
    RICH_ACCESS(2);
    
    write("You sulk in the corner since your "+query_purse()+" doesn't carry "+
          "all your platinum coins.\n");
    TP->add_prop(SET_EMOTE,"sulking because the "+query_purse()+
                 " is to small for the coins");
    say(QCTNAME(TP)+" sulks in the corner since the purse doesn't carry all "+
        HIS_HER(TP)+" coins.\n");
    return 0;
}

string
rsup()
{
    RICH_ACCESS(16);
    XNOTHUMBLE;
    
    write("You tell everyone how superior to them you are, since you have more money "+
          "on your account than they have, at least you think so.\n");
    say(QCTNAME(TP)+" expresses "+HIS_HER(TP)+" belief that "+HE_SHE(TP)+" is "+
        "superior to you, based on the amount of wealth.\n");
    return 0;
}

string
rtboard(string str)
{
    object ob, *tm, ticket;
    string mt;
    int i;

    RICH_ACCESS(16);
    FILTHILY;
    XNOTHUMBLE;

    FIXEUID;

    if (!str || str == "")
	str = "ship";
    
    if (!present(str, ENV(TP)))
        return "There is no "+str+" present!\n";

    tm = TP->query_team_others();
    if (!sizeof(tm))
    {
        rboard(str);
        return 0;
    }
    
    frompurse(1);
    mt = "gold";
    ob = present("gold coin",TP);
    if (!ob)
    {
        mt = "platinum";
        ob = present("platinum coin",TP);
        if (!ob)
        {
            topurse(0);
            return "You haven't got any lovely money to pay the captain!\n";
        }
    }

    write("You ask the sailor for a favour and hand him a "+mt+" coin.\n");
    say(QCTNAME(TP)+" asks the sailor for a favour and gives him a "+mt+" coin.\n"+
        "The captain lets the team board the boat.\n");

    for (i = 0; i < sizeof(tm); i++)
    {
        if (present(tm[i],environment(TP)) && TP != tm[i])
        {
            TP->command("buy ticket");
            ticket = present("ticket",TP);
            ticket->remove_prop(OBJ_M_NO_GIVE);
            ticket->move(tm[i]);
            tm[i]->command("board");
        }
    }
    TP->command("buy ticket");
    TP->command("board");
    
    ob->split_heap(1);
    ob->move(ENV(TP));
    ob->remove_object();
    topurse(0);
    return 0;
}

string
rtease(string s)
{
  object *a,ob, *obs;
  string str;
  int align, i;

  RICH_ACCESS(4);
  XNOTHUMBLE;

  if (!s || s == "all")
  {
    write("You tease everyone because you think you are much richer than them. \n");
    say(QCTNAME(TP)+" teases you because "+HE_SHE(TP)+" thinks you are a poor one "+
        "compared to "+HIM_HER(TP)+".\n");
    return 0;
  }

  if (s == "me")  
  {
    write("Tease yourself?\n");
    say(QCTNAME(TP)+" teases "+HIM_HER(TP)+"self.\n");
    return 0;
  }
    
  obs = FIND_STR_IN_OBJECT(s, environment(TP));
  obs = FILTER_OTHER_LIVE(obs);

  if (!sizeof(obs))  return "Tease who?\n";    
  {
    for (i=0; i<sizeof(obs); ++i)  
    {
      obs[i]->catch_msg(QCTNAME(TP)+" teases you because "+HE_SHE(TP)+" thinks you "+
        "are poorer than "+HE_SHE(TP)+" is.\n");
    }

    write("You tease "+COMPOSITE_LIVE(obs)+" because you think you are richer than "+COMPOSITE_LIVE(obs)+".\n");
    tell_room(ENV(TP), QCTNAME(TP)+" teases "+QCOMPLIVE+
          " because "+HE_SHE(TP)+" thinks "+HE_SHE(TP)+" is the richest around.\n",({TP})+obs);
  }
  return 0;
}

string
rtell(string str)
{
    object *players;
    int i, p, o, l, m;

    RICH_ACCESS(33);

    FIXEUID;
    
    players = users();
    
    for (i = 0; i < sizeof(players); i++)
    {
        if (present("rich_club_obj", players[i]) &&
            (RMCMASTER)->query_notification(players[i]->query_real_name()))
        {
            players[i]->catch_msg("[RMC - "+CQRLNAME(TP)+"] informs you: "+str+"\n");
        }
    }
    write("You have talked to all the members.\n");
    return 0;
}

string
rtitle()
{
    int v;
    string s;

    RICH_ACCESS(16);
    FIXEUID;

    v = (RMCMASTER)->query_purchased(TP->query_real_name());
    if (v > 2000)
    {
        v -= 2000;
    }
    
    if (v > 2000)
        s = "You'll have to wait until a new title arrives. You have the highest already.\n";
    else if (v > 1900)
        s = "You are very close to obtain the next level.\n";
    else if (v > 1750)
        s = "You are close to obtain the next level.\n";
    else if (v > 1300)
        s = "You are more than halfway in your efforts to reach a new title.\n";
    else if (v > 750)
        s = "You're about halfway to reach the next title.\n";
    else if (v > 250)
        s = "You're far from the next title.\n";
    else
        s = "You're very far from reaching the next title.\n";

    write(s);
    return 0;
}

string
rthink()
{
    RICH_ACCESS(4);
    
    write("You think hard about going on a money hunt.\n");
    TP->add_prop(SET_EMOTE,"longing for a money hunt");
    say(QCTNAME(TP)+" looks like "+HE_SHE(TP)+" is thinking hard about going on a money hunt.\n");
    return 0;
}

string
rtoss()
{
    int styrka;
    object ob;

    RICH_ACCESS(4);
    
    frompurse(1);
    if (ob = present("platinum coin",TP))
    {
        if (TP->query_prop("_live_i_has_tossed_coin"))
        {
            write("You already have one coin in the air.\n");
            topurse(0);
            return 0;
        }
        else
        {
            TP->add_prop("_live_i_has_tossed_coin",1);
            styrka = TP->query_stat(SS_STR)/40;
            write("You toss a platinum coin high up in the air.\n");
            TP->add_prop(SET_EMOTE,"waiting for a platinum coin to fall down from the sky");
            say(QCTNAME(TP)+" tosses a platinum coin high up in the air.\n");
            set_alarm( itof(styrka), 0.0, "catch_coin");
            topurse(0);
            return 0;
        }
    }
    topurse(0);
    return "You haven't got any lovely plats!\n";
}

string
rvars(string str)
{
    int i;

    RICH_ACCESS(32);
    FIXEUID;

    (RMCMASTER)->query_member_vars(str , TP);
    return 0;
}

string
rwalk()
{
  int dex,con;
  object ob;

  RICH_ACCESS(4);
  
  dex = TP->query_stat(SS_DEX);
  con = TP->query_stat(SS_CON);

  frompurse(0);
  if(ob = present("platinum coin",TP))
  {
    write("You let a platinum coin walk across your knuckles, ");
    TP->add_prop(LIVE_S_EXTRA_SHORT," playing with a platinum coin");
    say(QCTNAME(TP)+" walks a coin across his knuckles, ");

    if (((dex/2)+(random(dex/2)))>random(con))
    {
       write("you succeed and smile proudly.\n");
       TP->remove_prop(LIVE_S_EXTRA_SHORT);
       say("and smiles proudly as "+HE_SHE(TP)+" succeeds.\n");
       topurse(0);
       return 0;
    }
    write("you fail and full of shame you see the coin fall to the floor.\n");
    say(HE_SHE(TP)+" fails and looks ashamed as the coin fall to the floor.\n");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    ob->split_heap(1);
    ob->move(ENV(TP));
    topurse(0);
    return 0;
  }
  topurse(0);
  return "You don't have any plats!\n";
}

string
rwonder(string str)
{
    int diff, ma, oa;
    string dfeel;
    
    RICH_ACCESS(16);
    FILTHILY;

    FIXEUID;

    if (!str || str == "")
    {
	write("Surpassing your own standing in the club should be easy,\n" +
	      "with some careful money management. \n");
	return 0;
    }

    ma = (RMCMASTER)->query_valuation(TP->query_real_name());
    oa = (RMCMASTER)->query_valuation(str);

    if (oa <= 0)
    {
	if ((RMCMASTER)->query_acc(str) < 0)
	    write(capitalize(str)+" isn't a member of our distinguished club..."+
		  "propably some poor fella running around begging rich people "+
		  "like you for cash!\n");
	else
	    write(capitalize(str)+" isn't present!\n");
	
        return 0;
    }
    
    diff = oa - ma;

    if (diff > 20) dfeel = "terrified";
    else if (diff > 10) dfeel = "desperate";
    else if (diff > 5) dfeel = "annoyed";
    else if (diff > 3) dfeel = "prosperous";
    else if (diff > 1) dfeel = "excited";
    else if (diff < (-20)) dfeel = "very secure";
    else if (diff < (-10)) dfeel = "secure";
    else if (diff < (-5)) dfeel = "a little insecure";
    else if (diff < (-3)) dfeel = "very insecure";
    else if (diff < (-1)) dfeel = "close to ruin";
    else dfeel = "uncertain";
    
    if (diff >= 0)
    {
        write("You wonder how much money you have to get to pass "+capitalize(str)+
              " in the club, and thereby become an even more distinguished "+
              "member.\n\nYou evaluate the difference and feel "+dfeel+" about "+
              "your situation.\n");
        say(QCTNAME(TP)+" looks "+dfeel+" as "+HE_SHE(TP)+" checks the prospects "+
            "of getting a more distinguished rank in the Rich Men's Club.\n");
    }
    else
    {
        write("You wonder how much money "+capitalize(str)+" has to get hold of "+
              "to become richer and more distinguished member than you.\n\n"+
              "You quickly estimate the difference and feel "+dfeel+" about your "+
              "situation.\n");
        say(QCTNAME(TP)+" looks "+dfeel+" as "+HE_SHE(TP)+" checks the prospects "+
            "of losing "+HIS_HER(TP)+" distinguished rank in the Rich Men's Club.\n");
    }
    
    return 0;
}

string
ryawn()
{
    RICH_ACCESS(8);
    XNOTHUMBLE;
    
    write("You yawn, bored by all these poor people.\n");
    say(QCTNAME(TP)+" yawns, appearantly bored by having to listen to all these poor people.\n");
    return 0;
}

int
rmc_commands(string str)
{
    mapping m;
    string *c,s;
    string a;
    int i;

    NF("No such RMC command.\n");
    if (!str)
	return 0;

    c = explode(str, " ");
    s = implode(c[1..], " ");

    m = query_rmc_commands();

    if (m[c[0]])
    {
        a = call_other(TO, m[c[0]], s);

        if (a)
            write(a);
        
        return 1;
    }

    return 0;
}
