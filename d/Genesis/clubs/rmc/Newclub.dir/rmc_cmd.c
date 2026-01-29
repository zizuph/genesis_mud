#pragma save_binary
#pragma strict_types

#include "xdefs.h"
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <money.h>

inherit "/cmd/std/command_driver";

#define XNF(xxx) xnf = xxx
#define FILTHILY if(r_purc<2000) XNF("No such RMC command.\n");return 0
#define BIGSHOT  if(r_purc<4000) XNF("No such RMC command.\n");return 0

int purge  = 0;
string type;
object purse = present("rich_club_obj",TP);
string type = purse->query_short();
int r_paid, r_acc, r_humb, r_purc, level;
string xnf;

mixed *emote = (({
    ({8, "|*bankbook................................check your nice account. |",}),
    ({33,"| account <all/m/name/wiz>.........checks the account of a person. |",}),
    ({4, "| advice <target>....give somebody some advice how to gain wealth. |",}),
    ({2, "| assure <target>....assure somebody that the future will be good. |",}),
    ({8, "| board..........................................bribe the sailor. |",}),
    ({2, "| busy..................make clear that you are busy making money. |",}),
    ({4, "| buy <something>...................................buy something. |",}),
    ({2, "| cackle.........................................cackle wealthily. |",}),
    ({16,"|*catch <target>.....try to catch a coin that <target> has tossed. |",}),
    ({33,"| checklog 'rich'/'pier'.....shows the logs rich.log and gold.log. |",}),
    ({4, "|*checkpocket........................check your pockets for coins. |",}),
    ({16,"| comfort <target>........comfort someone, since (s)he is so poor. |",}),
    ({16,"| compare <target>...............compare someone's wealth to your. |",}),
    ({8, "| consider <target>.....................consider someone's wealth. |",}),
    ({2, "| convince <target>.....convince somebody that money is important. |",}),
    ({16,"| counthi <coin type>.......................count your coins loud. |",}),
    ({8, "| dislike.........................dislike someone poorer than you. |",}),
    ({8, "| disgust................show what you think of sniveling beggars. |",}),
    ({2, "|*dream..................dream about the fortunes that lies ahead. |",}),
    ({2, "| drop.........................................drop a copper coin. |",}),
    ({4, "| dropall............drop all your coppers because of their value. |",}),
    ({2, "| evaluate.........................notify the importance of money. |",}),
    ({35,"| force......................force dested players out of the club. |",}),
    ({1, "|*get...................................get coins from your purse. |",}),
    ({1, "| greet <target>...................................greet a player. |",}),
    ({2, "| grin..................................grin and show your wealth. |",}),
    ({1, "|*hide......................hide your purse so that noone sees it. |",}),
    ({16,"| hold....................hold your money-sack close to your body. |",}),
    ({4, "| hope...........hope that the future will be rich and prosperous. |",}),
    ({1, "|*humble <on/off>......decide whether you want to show off or not. |",}),
    ({4, "| jump....................jump high after controlling your income. |",}),
    ({16,"|*list.........................................fellow rich people. |",}),
    ({1, "| look...........................check the contents of your purse. |",}),
    ({8, "| loot <pgsc>...........................loot the corpse for money. |",}),
    ({33,"| members..................................show member statistics. |",}),
    ({4, "|*mini..............................minimize your coins in a bank. |",}),
    ({1, "|*news......................to see the latest changes in the club. |",}),
    ({1, "|*note <on/off>................get notification about competitors. |",}),
    ({1, "| nudge.....................................show the joy of money. |",}),
    ({1, "| offer <target>.....................................offer a loan. |",}),
    ({4, "|*order <something>...............................order something. |",}),
    ({16,"| panic.........panic since you think you've lost your money-sack. |",}),
    ({1, "| pat...........................................admire your purse. |",}),
    ({4, "| peer <target>.......peer at somebody, disliking the competition. |",}),
    ({2, "| pick....................................smell the taste of gold. |",}),
    ({33,"| purge..................purge wiz members onlogged without purse. |",}),
    ({17,"| pos...............................see your position in the club. |",}),
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
        
mapping
query_rmc_commands()
{
    return ([
        "help"      :      "help",
        "bankbook"  :  "bankbook",
        "account"  :  "raccount",
        "advice"   :   "radvice",
        "assure"   :   "rassure",
        "board"    :    "rboard",
        "busy"     :     "rbusy",
        "buy"      :      "rbuy",
        "cackle"   :   "rcackle",
        "catch"    :    "rcatch",
        "checkpocket":"rcheckpocket",
        "checklog" : "rchecklog",
        "comfort"  :  "rcomfort",
        "compare"  :  "rcompare",
        "consider" : "rconsider",
        "convince" : "rconvince",
        "disgust"  :  "rdisgust",
        "dislike"  :  "rdislike",
        "dream"    :    "rdream",
        "drop"     :     "rdrop",
        "dropall"  :  "rdropall",
        "evaluate" : "revaluate",
        "force"    :    "rforce",
        "get"      :      "rget",
        "greet"    :    "rgreet",
        "grin"     :     "rgrin",
        "hide"     :     "rhide",
        "hold"     :     "rhold",
        "hope"     :     "rhope",
        "humble"   :   "rhumble",
        "list"  :  "richlist",
        "jump"     :     "rjump",
        "look"     :     "rlook",
        "loot"     :     "rloot",
        "members"  :  "rmembers",
        "mini"     :     "rmini", 
        "news"     :     "rnews",
        "note"     :     "rnote",
        "nudge"    :    "rnudge",
        "offer"    :    "roffer",
        "order"    :    "rorder",
        "panic"    :    "rpanic",
        "pat"      :      "rpat",
        "peer"     :     "rpeer",
        "pick"     :     "rpick",
        "pos"      :      "rpos",
        "ps"       :       "rps",
        "purge"    :    "rpurge",
        "put"      :      "rput",
        "scream"   :   "rscream",
        "search"   :   "rsearch",
        "sell"     :     "rsell",
        "setlevel" : "rsetlevel",
        "setnews"  :  "rsetnews",
        "shop"     :     "rshop",
        "sing"     :     "rsing",
        "slip"     :     "rslip",
        "smile"    :    "rsmile",
        "smile2"   :   "rsmile2",
        "smirk"    :    "rsmirk",
        "spent"    :    "rspent",
        "sponsor"  :  "rsponsor",
        "sulk"     :     "rsulk",
        "sup"      :      "rsup",
        "tboard"   :   "rtboard",
        "tease"    :    "rtease",
        "tell"     :     "rtell",
        "title"    :    "rtitle",
        "think"    :    "rthink",
        "toss"     :     "rtoss",
        "vars"     :     "rvars",
        "walk"     :     "rwalk",
        "wonder"   :   "rwonder",
        "yawn"     :     "ryawn"
    ]);
}

/*
 * +-------------------------------------+
 * | SUB-FUNCTIONS FOR THE R.M.C. EMOTES |
 * +-------------------------------------+
 */
int
simple_emote(string arg1, string arg2)
{
    write(arg1);
    say(arg2);
    
    return 1;
}

int
simple_emote_silent(string arg1, string arg2)
{
    write(arg1);
    targetbb(arg2, ({ TP }));
    
    return 1;
}

int
targ_emote(string s, string emote,
	   string me_no_targ, string all_no_targ,
	   string me_i_targ, string all_i_targ,
	   string me_a_targ, string all_a_targ,
	   string me_mes1, string me_mes2,
	   string tg_mes,
	   string al_mes1, string al_mes2)
{	
    object *a,ob, *obs;
    string str;
    int align, i;

    if (!s)
    {
        write(me_no_targ + "\n");
        if (all_no_targ)
            say(all_no_targ + "\n");
        return 1;
    }

    if (s == "all")
    {
        write(me_a_targ + "\n");
        if (all_a_targ)
            say(all_a_targ + "\n");
        return 1;
    }
    
    if (s == "me")  
    {
        write(me_i_targ + "\n");
        if (all_i_targ)
            say(all_i_targ + "\n");
        return 1;
    }
    
    obs = FIND_STR_IN_OBJECT(s, environment(TP));
    obs = FILTER_OTHER_LIVE(obs);

    XNF(CAP(emote)+" who?\n");
    if (!sizeof(obs))
        return 0;    
    
    actor(me_mes1, obs, me_mes2);
    target(tg_mes, obs);
    all2act(al_mes1, obs, al_mes2);
    
    return 1;
}

int
targ_emotebb(string s, string emote,
	     string me_no_targ, string all_no_targ,
	     string me_i_targ, string all_i_targ,
	     string me_a_targ, string all_a_targ,
	     string me_mes1, string me_mes2,
	     string tg_mes,
	     string al_mes1, string al_mes2)
{	
    object *a,ob, *obs;
    string str;
    int align, i;

   if (!s)
    {
        write(me_no_targ + "\n");
        if (all_no_targ)
            allbb(all_no_targ, ({ TP }));
        return 1;
    }

    if (s == "all")
    {
        write(me_a_targ + "\n");
        if (all_a_targ)
            allbb(all_a_targ, ({ TP }));
        return 1;
    }
    
    if (s == "me")  
    {
        write(me_i_targ + "\n");
        if (all_i_targ)
            allbb(all_i_targ, ({ TP }));
        return 1;
    }
    
    obs = FIND_STR_IN_OBJECT(s, environment(TP));
    obs = FILTER_OTHER_LIVE(obs);

    XNF(CAP(emote)+" who?\n");
    if (!sizeof(obs))
        return 0;    
    
    actor(me_mes1, obs, me_mes2);
    targetbb(tg_mes, obs);
    all2actbb(al_mes1, obs, al_mes2);
    
    return 1;
}

string
query_purse()
{
    string s;
    
    s = present("rich_club_obj",TP)->query_name();
    return s;
}

/* ACCOUNT FUNKTIONS */
int
bank_account(object ob)
{
    mapping acc = ACCOUNTS->query_account(ob->query_real_name());
    int tot;
    object account_list = find_object(ACCOUNTS);
  
    if (m_sizeof(acc) < 6)
        return 0;
    return (acc["pc"] + acc["gc"]/12 + acc["sc"]/144 + acc["cc"]/1728);
}

int
level_account(object ob)
{
    int tot;

    tot = (200 * level) - 100;
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
    (RICHROOM)->change_account(TP,plats);
}

int
retaccount(int summa)
{
    write("You find your bankbook.\nYou have "+summa+" platinum coins in the "+
          "bank.\n");
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
    write("<RMC> "+capitalize(str));
    if (strlen(str)<10)
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
        write("You put some coins into your "+query_purse()+".\n");
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
        write("You fetch some coins from your "+query_purse()+".\n");
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
    int dexxy,strength;
    object ob,catcher;
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
            write("You are about to catch the coin, when suddenly "+QTNAME(catcher)+
                  " raises "+HIS_HER(catcher)+" hand and grabs it before "+
                  "your very eyes!\n");
            catcher->catch_msg("You jump up and catch the coin before "+QTNAME(TP)+
                               "'s very eyes!\n");
            tell_room(ENV(TP),QCTNAME(catcher)+" jumps up and catches the coin "+
                      "before "+QTNAME(TP)+"'s very eyes!\n",({TP, catcher}));
            ob->split_heap(1);
            ob->move(catcher);
            catcher->command("grin");
            TP->command("grumble");
            topurse(0);
            return 1;
        }
        else if (catcher)
        {
            write("You are about to catch the coin, when suddenly "+QTNAME(catcher)+
                  " raises "+HIS_HER(catcher)+" hand and tries to catch your "+
                  "coin! Luckily "+HE_SHE(catcher)+" misses.\n");
            catcher->catch_msg("You jump up to try to catch the coin before "+
                               QTNAME(TP)+"'s very "+
                               "eyes, but you miss!\n");
            tell_room(ENV(TP),QCTNAME(catcher)+" jumps up to try to catch the "+
                      "coin before "+QTNAME(TP)+"'s very eyes, but "+
                      HE_SHE(catcher)+" misses.\n",({TP, catcher}));
            catcher->command("grumble");
        }
        if (dexxy < strength )
        {
            write("You fumble and the platinum coin falls down on the ground.\n");
            TP->add_prop(SET_EMOTE,"not proud at all");
            say("Suddenly a platinum coin falls down from above.\n"+
                QCTNAME(TP)+" fumbles with the platinum coin and it falls "+
                "down to the ground.\n");
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

/*
 * +------------------------------------------------------------------+
 * | EMOTES FOR THE R.M.C. (should be added in alphabetically order.) |
 * +------------------------------------------------------------------+
 */
int
help(string str)
{
    string fnurp;
    int i, p;

    RICH_ACCESS(1);
  
    FIXEUID;

    p = r_purc;

    if (p > 4000)
        level += 2;
    else if (p > 2000)
        level++;
  
    fnurp ="\n+------------------------------------------------------------------+\n"+
        "| $             This is the Rich Men's Club's emotes:            $ |\n"+
        "+------------------------------------------------------------------+\n";

    XNF("Level doesn't exist, or you haven't reached it yet.\n");
    if (!str)
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
        return 0;

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

    return 1;
}

int
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
    return 1;
}

int
raccount(string str)
{
    object *players;
    int i,lvl,acc;
    string name;

    RICH_ACCESS(33);

    players = users();

    for (i = 0; i < sizeof(players); i++)
    {
        lvl = (RICHROOM)->query_level(players[i]); 
        acc = bank_account(players[i]);
        name = players[i]->query_real_name();
    
        if (name == str)
        {
            write("\n<RMC> "+capitalize(str)+" has level ");
            write(level);
            write(" in the RMC.\n");
            write("<RMC> "+capitalize(str)+" has ");
            write(acc);
            write(" plats in the bank.\n\n");
            return 1;
        }
        else if (str == "all")
        {
            if (lvl>0 || acc>0)
            {
                raccwrite(name,acc,lvl);
            }
        }
        else if (str == "m" && !players[i]->query_wiz_level())
        {
            if (lvl>0 || acc>75)
            {
                raccwrite(name,acc,lvl);
            }
        }
        else if (str == "wiz" && players[i]->query_wiz_level())
        {
            if (lvl>0 || acc>0)
            {
                raccwrite(name,acc,lvl);
            }
        }
    }
    return 1;
}


int
radvice(string s)
{
    int a;

    RICH_ACCESS(4);
    XNOTHUMBLE;

    a = targ_emote(s, "advice",
		   "You advice everyone that the best way of gaining a lot "+
		   "of money is to not spend them.",
		   QCTNAME(TP)+" advices you that the best way of gaining a "+
		   "lot of money is to not spend them.",
                        
		   "Advice yourself?",
		   QCTNAME(TP)+" advices "+HIM_HER(TP)+"self something. What "+
		   "a strange person!",

		   "You advice everyone that the best way of gaining a lot "+
		   "of money is to not spend them.",
		   QCTNAME(TP)+" advices you that the best way of gaining a "+
		   "lot of money is to not spend them.",

		   "You advice", " that the best way of of gaining a lot of "+
		   "money is to not spend them.",
		   " advices you that the best way of gaining a lot of money "+
		   "is to not spend them.",
		   "gives"," an advice.");
  
    return a;
}

int
rassure(string s)
{
    int a;

    RICH_ACCESS(2);
    XNOTHUMBLE;

    a = targ_emote(s, "assure",
		   "You assure your companions that the future will "+
		   "be good for the market.",
		   QCTNAME(TP)+" assures you that the future will be "+
		   "good for the market.",

		   "Assure yourself? Are you that insecure about the future?",
		   0,

		   "You assure your companions that the future will "+
		   "be good for the market.",
		   QCTNAME(TP)+" assures you that the future will be "+
		   "good for the market.",

		   "You assure", " that the future will be good for the "+
		   "market.",
		   " assures you that the future will be good for the "+
		   "market.",
		   "assures", " that the future will be good for the "+
		   "market.");
    
    return a;
}

int
rboard()
{
    object ob;
    string mt;

    RICH_ACCESS(8);
    XNOTHUMBLE;

    FIXEUID;

    XNF("There is no ship present!\n");
    if (!present("ship",ENV(TP)))
        return 0;
  
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
                XNF("You haven't got any lovely money to pay the captain!\n");
                return 0;
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
    return 1;
}

int
rbusy()
{
    RICH_ACCESS(2);
    XNOTHUMBLE;
    
    write("You tell the audience that you are busy making money.\n");
    TP->add_prop(SET_EMOTE,"busy making money");
    say(QCTNAME(TP)+" are busy collecting plats.\n");
    return 1;
}

int
rbuy(string str)
{
    RICH_ACCESS(4);
    XNOTHUMBLE;

    XNF("Buy what?\n");
    if (!str)
        return 0;

    write("You study the prices carefully, and finally decides to "+
          "purchase "+LANG_ADDART(str)+".\n");
    say(QCTNAME(TP)+" studies the prices carefully, and finally decides "+
        "to purchase "+LANG_ADDART(str)+".\n");
    frompurse(1);
    TP->command("$buy "+str);
    topurse(0);
    return 1;
}
int
rcackle()
{
    RICH_ACCESS(2);
    XNOTHUMBLE;
    
    write("You cackle wealthily.\n");
    say(QCTNAME(TP)+" cackles wealthily.\n");
    return 1;
}

int
rcatch(string s)
{
    object *a, ob, ob2, *obs;
    string str;
    int align, i;

    RICH_ACCESS(16);

    if (s == "all")
    {
        write("Everybody hasn't tossed a coin...\n");
        return 1;
    }

    if (s == "me")  
    {
        write("You will do that anyway....maybe...");
        return 1;
    }

    XNF("Catch who's coin?\n");
    if (!s) return 0;

    obs = FIND_STR_IN_OBJECT(s, environment(TP));
    obs = FILTER_OTHER_LIVE(obs);

    XNF("Catch who's coin?\n");
    if (!sizeof(obs))
        return 0;
    
    if (sizeof(obs) > 1)
        return 0;    
    
    if(!obs[0]->query_prop("_live_i_has_tossed_coin"))
    {
        write(QCTNAME(obs[0])+" hasn't tossed any coin....\n");
        return 1;
    }
    if(obs[0]->query_prop("_live_o_tries_to_catch"))
    {
        write("Somebody is already waiting...\n");
        return 1;
    }

    obs[0]->add_prop("_live_o_tries_to_catch",TP);
    write("You make yourself ready to catch the coin.\n");

    return 1;
}

int
rchecklog(string str)
{
    string data;

    RICH_ACCESS(33);

    if (str == "rich")
    {
        data = read_file("/d/Immortal/rclub/rich.log");
        write(data);
        return 1;
    }
    else if (str == "pier")
    {
        data = read_file("/d/Immortal/gold/gold.log");
        write(data);
        return 1;
    }
    XNF("Rchecklog what?\n");
    return 0;
}

int
rcheckpocket()
{
    RICH_ACCESS(4);
    
    write("You check your pockets for plats.\n");
    TP->add_prop(SET_EMOTE,"searching around for plats");
    say(QCTNAME(TP)+" checks "+HIS_HER(TP)+" pockets for plats.\n");
    return 1;
}

int
rcomfort(string s)
{
    int a;

    RICH_ACCESS(16);
    XNOTHUMBLE;

    a = targ_emote(s, "comfort",
		   "You comfort everybody because they are so poor and "+
		   "you are so rich.",
		   QCTNAME(TP)+" comforts you, since you are so poor "+
		   "and " + HE_SHE(TP) + " is so rich.",

		   "Comfort yourself?",
		   QCTNAME(TP)+" comforts "+HIM_HER(TP)+"self because "+
		   HE_SHE(TP) + " feels so poor.",

		   "You comfort everybody because they are so poor and "+
		   "you are so rich.",
		   QCTNAME(TP)+" comforts you, since you are so poor "+
		   "and " + HE_SHE(TP) + " is so rich.",
                        
		   "You comfort", " because the difference in wealth "+
		   "between you, ie that you are much richer.",
		   " comforts you, since you are so poor and "+
		   HE_SHE(TP)+" is so rich.",
		   "comforts", " because "+HE_SHE(TP)+" is much richer.");

    return a;
}

int
rcompare(string s)
{
    object *a, ob, *obs;
    string str;
    int align, acc1, acc2;

    RICH_ACCESS(16);
    XNOTHUMBLE;

    if (s == "me" || !s || s == "all")
    {
        XNF("Compare with who?\n");
        return 0;
    }

    obs = FIND_STR_IN_OBJECT(s, environment(TP));
    obs = FILTER_OTHER_LIVE(obs);

    XNF("Compare with who?\n");
    if (!sizeof(obs) || sizeof(obs) > 1)
        return 0;
    
    obs[0]->catch_msg(QCTNAME(TP)+" compares "+HIS_HER(TP)+" wealth with yours.\n");
    write("You compare "+QTNAME(obs[0])+"'s wealth with yours.\n");
    tell_room(ENV(TP), QCTNAME(TP)+" compares "+HIS_HER(TP)+" wealth with "+
              QTNAME(obs[0])+
              " trying to figure out who's the richest.\n",({TP, obs[0]}));
    
    acc1 = ((total_account(TP) + r_purc) / 100) * 100;
    acc2 = ((total_account(obs[0]) + (RICHROOM)->query_purchased(obs[0])) / 100) * 100;

    if (acc1 > acc2)
        str = "richer than ";
    else if (acc1 < acc2)
        str = "a poor fella compared to ";
    else
        str = "about as rich as ";
    
    write("You have approx "+acc1+" plats and "+QTNAME(obs[0])+" has "+
          "approx "+acc2+" plats which means that you are "+str+HIM_HER(obs[0])+
          ".\n");
    obs[0]->catch_msg(QCTNAME(TP)+" seems to be "+str+"you.\n");
    tell_room(ENV(TP),QCTNAME(TP)+" seems to be "+str+QTNAME(obs[0])+
              ".\n", ({TP, obs[0]}) );
    
    return 1;
}

int
rconsider(string s)
{
    object *a, ob, *obs;
    string str;
    int align, acc1, acc2;

    RICH_ACCESS(8);
    XNOTHUMBLE;

    if (s == "me" || !s || s == "all")
    {
        XNF("Consider who?\n");
        return 0;
    }

    obs = FIND_STR_IN_OBJECT(s, environment(TP));
    obs = FILTER_OTHER_LIVE(obs);

    XNF("Consider who?\n");
    if (!sizeof(obs) || sizeof(obs) > 1)
        return 0;
    
    obs[0]->catch_msg(QCTNAME(TP)+" gives you a strange look.\n");
    write("You consider "+QTNAME(obs[0])+"'s wealth.\n");
    tell_room(ENV(TP), QCTNAME(TP)+" peers at "+QTNAME(obs[0])+
              " estimating the difference in cash between them.\n",({TP, obs[0]}));
    
    acc1 = total_account(TP) + r_purc;
    acc2 = total_account(obs[0]) + (RICHROOM)->query_purchased(obs[0]);
    if (acc1 > (acc2 + 500))
    {
        write("You are much wealthier than "+QTNAME(obs[0])+".\n");
        TP->command("rc smile2");
    }
    else if (acc1 > acc2)
    {
        write("You are wealthier than "+QTNAME(obs[0])+".\n");
        TP->command("smile");
    }
    else if ((acc1 + 500) < acc2)
    {
        write(QCTNAME(obs[0])+" are much wealthier than you.\n");
        TP->command("grumble pitiful");
    }
    else if (acc1 < acc2)
    {
        write(QCTNAME(obs[0])+" are wealthier than you.\n");
        TP->command("sulk");
    }
    else
    {
        write("You are as wealthy as "+QTNAME(obs[0])+".\n");
        TP->command("shake "+obs[0]->query_name());
    }
    return 1;
}

int
rconvince(string s)
{
    int a;

    RICH_ACCESS(2);
    XNOTHUMBLE;

    a = targ_emote(s, "convince",
		   "You can't convince them all, try one at a time...",
		   0,
			
		   "Convince yourself?",
		   0,

		   "You can't convince them all, try one at a time...",
		   0,
		
		   "You try to convince", " that the only thing that "+
		   "is important is money.",
		   " tries to convince you that the only thing that is "+
		   "important is money.",
		   "tries to convince", " that the only "+
		   "thing that is important is money.");
    
    if (a)  
        TP->add_prop(SET_EMOTE,"trying to convince someone");
  
    return a;
}

int 
rdislike()
{
    RICH_ACCESS(8);
    XNOTHUMBLE;
    
    write("You show, with an evil grin, how much you hate poor and greedy "+
          "people.\n");
    TP->add_prop(SET_EMOTE,"hates poor and greedy people");
    say(QCTNAME(TP)+" shows you how much "+HE_SHE(TP)+" dislikes people as "+
        "poor as you.\n");
    return 1;
}

int
rdisgust(string s)
{
    int a;

    RICH_ACCESS(8);
    XNOTHUMBLE;

    a = targ_emotebb(s, "disgust",
		 "You look at the crowd in disgust, you really hate sniveling "+
		 "beggars!",
		 QCTNAME(TP)+"looks at you and the others with disgust "+
		 "showing what "+HE_SHE(TP)+" thinks of sniveling beggars."

		 "Disgusted of yourself?",
		 0,

		 "You look at the crowd in disgust, you really hate sniveling "+
		 "beggars!",
		 QCTNAME(TP)+" looks at you and the others with disgust "+
		 "showing what "+HE_SHE(TP)+" thinks of sniveling beggars."

		 "You look at", " with disgust, you can't stand sniveling "+
		 "beggars!",
		 " looks at you with disgust, showing what a sniveling "+
		 "beggar you are.",
		 "looks at", " thinks of sniveling beggars.");
   
    return a;
}

int
rdream()
{
    RICH_ACCESS(2);
    
    write("You start to dream about all the fortunes that lies ahead.\n");
    say(QCTNAME(TP)+" starts to dream about all the fortunes that lies ahead.\n");
    return 1;
}

int
rdrop()
{
    object ob;

    RICH_ACCESS(2);
    XNOTHUMBLE;
  
    frompurse(1);
    if (ob = present("copper coin",TP)) /* MAKE SURE YOU DROP A COPPER COIN */
    {
        write("You yawn and drop one copper coin just to make sure the worth "+
              "of money.\n");
        TP->add_prop(SET_EMOTE,"yawning tiredly");
        say(QCTNAME(TP)+" yawns and smiles coldly as "+HE_SHE(TP)+" drops one "+
            "copper coin.\n");
        ob->split_heap(1);
        ob->move(ENV(TP));
        topurse(0);
        return 1;
    }
    topurse(0);
    XNF("You haven't got any coppers!\n");
    return 0;
}

int
rdropall()
{
    object ob;
    RICH_ACCESS(4);
    XNOTHUMBLE;

    frompurse(1);
    ob = present("copper coin", TP);

    XNF("You don't have any coppers to drop.\n");
    if (!ob)
        return 0;
    
    write("You drop all your coppers, because their low value. You like "+
          "_big_ money!\n");
    say(QCTNAME(TP)+" drops all "+HIS_HER(TP)+" coppers, because of their "+
        "low value. "+QCTNAME(TP)+" likes _big_ money!\n");
    ob->move(environment(TP));
    topurse(0);
    return 1;
}

int
revaluate()
{
    RICH_ACCESS(2);
    XNOTHUMBLE;
    
    write("You announce your inner feelings about how you evaluate other "+
	  "people.\n");
    say(QCTNAME(TP)+" announces that the only way to evaluate a person is "+
	"to check that person's bank account!\n");
    return 1;
}

int
rforce()
{
    string s;
    
    RICH_ACCESS(35);
    
    s = (RICHROOM)->force_members();
    write(s);
    return 1;
}

int
rget()
{
    RICH_ACCESS(1);
  
    purse = present("rich_club_obj",TP);
  
    if (present("coin",purse) || present("gem",purse))
    {
        write("You look into your "+query_purse()+" and quickly pick up it's "+
              "contents.\n");
        say(QCTNAME(TP)+" looks into "+HIS_HER(TP)+" "+query_purse()+
            " and quickly picks up it's contents.\n");
        frompurse(0);
    }
    else
    {
        write("You look into your "+query_purse()+" and find out that "+
              "it's empty!\n");
        say(QCTNAME(TP)+" looks into "+HIS_HER(TP)+" "+query_purse()+
            " and finds out that it's empty! What a disaster!\n");
    }
  
    return 1;
}

int
rgreet(string s)
{
    int a;

    RICH_ACCESS(1);
    XNOTHUMBLE;

    a = targ_emote(s, "greet",
	       "You greet everyone even though they are poor and miserable "+
	       "creatures.",
	       " greets you even though "+HE_SHE(TP)+" thinks you are poor "+
	       "compared to "+HIM_HER(TP)+".",

	       "Greet yourself?"
	       QCTNAME(TP)+" greets "+HIM_HER(TP)+"self because "+HE_SHE(TP)+
	       " has to boost "+HIS_HER(TP)+" ego a little.\nIt isn't easy "+
	       "being alone in the world without mommy."

	       "You greet", " even though you think you're much wealthier.",
	       " greets you although "+HE_SHE(TP)+" thinks you are poor "+
	       "and miserable.",
	       "greets", " even though "+HE_SHE(TP)+" thinks "+HE_SHE(TP)+
	       "is wealthier.");
    
    return a;
}

int
rgrin()
{
    RICH_ACCESS(2);
    XNOTHUMBLE;
    
    write("You grin as you think of the amount of money you have.\n");
    TP->add_prop(SET_EMOTE,"showing a wealthy grin");
    say(QCTNAME(TP)+" shows with a wealthy grin that "+HE_SHE(TP)+
        " got lots of plats.\n");
    return 1;
}

int
rhide()
{
    int v;
    
    RICH_ACCESS(1);
    FIXEUID;

    v = (RICHROOM)->query_visible(TP);
    
    if (v)
    {
        write("You hide your "+query_purse()+" so that noone can see "+
              "that you are so wealthy and leave you alone.\n");
        say(QCTNAME(TP)+" hides "+HIS_HER(TP)+" "+query_purse()+" so that "+
            "noone can see it and thereby come running begging.\n");
        (RICHROOM)->set_visible(TP, 0);
        return 1;
    }
    write("You fetch your "+query_purse()+" from somewhere inside your "+
          "clothes and place it so that everyone can see that you are "+
          "so wealthy.\n");
    say(QCTNAME(TP)+" fetches "+HIS_HER(TP)+" "+query_purse()+" from "+
        "somewhere inside the clothes and places it so that everyone can see it.\n");
    (RICHROOM)->set_visible(TP, 1);
    return 1;
}

int
rhold()
{
    RICH_ACCESS(16);
    XNOTHUMBLE;
    
    write("You hold your "+query_purse()+" close to your body, in case "+
          "that someone would make an attempt to steal it from you, and "+
          "all the lovely plats that it holds.\n");
    say(QCTNAME(TP)+" holds "+HIS_HER(TP)+" "+query_purse()+" close to "+
        HIS_HER(TP)+" body, in case someone would try to steal it and its "+
        "contents from "+HIM_HER(TP)+".\n");
    return 1;
}

int
rhope()
{
    RICH_ACCESS(4);
    XNOTHUMBLE;
    
    write("You hope that the future will be filled with good opportunities "+
	  "of making lots of money.\n");
    say(QCTNAME(TP)+" hopes that the future will be filled with good "+
	"opportunities of making lots of money.\n");
    return 1;
}

int
rhumble(string str)
{
    int hum;

    RICH_ACCESS(1);

    FIXEUID;

    hum = r_humb;

    if (str == "on")
    {
        XNF("You're already humble enough!\n");
        if (hum == 1)
            return 0;
        
        write("You feel much more humble now.\n");
        (RICHROOM)->toggle_humble(TP);
        return 1;
    }
    if (str == "off")
    {
        XNF("You're already showing off yer wealth!\n");
        if (hum == 0)
            return 0;
        
        write("You feel like showing off!\n");
        (RICHROOM)->toggle_humble(TP);
        return 1;
    }
    XNF("Rc humble what? On or off?\n");
    return 0;
}

int
richlist()
{
    string s;

    RICH_ACCESS(16);
    FIXEUID;

    s = (RICHROOM)->query_onlogged_members();
    write(s);
    return 1;
}

int
rjump()
{
    RICH_ACCESS(4);
    XNOTHUMBLE;
    
    purse = present("rich_club_obj",TP);
    if (present("platinum coin", purse))
    {
        write("You check your "+query_purse()+" and jump high in pure "+
              "happiness since you find lovely plats in it.\n");
        say(QCTNAME(TP)+" checks "+HIS_HER(TP)+" "+query_purse()+
            " and jumps high in pure happiness.\n");
        return 1;
    }
    write("You sulk when you realize that your "+query_purse()+
          " hasn't got any plats in it.\n");
    say(QCTNAME(TP)+" starts to sulk as "+HE_SHE(TP)+" finds out that "+
        HIS_HER(TP)+" "+query_purse()+"hasn't got any lovely plats.\n");
    return 1;
}

int
rlook()
{
    RICH_ACCESS(1);
    XNOTHUMBLE;
  
    purse = present("rich_club_obj",TP);
  
    TP->add_prop(SET_EMOTE,"looking eagerly into a nice "+query_purse());

    if (!(present("coin",purse) || present("gem",purse)))
    {
        say(QCTNAME(TP)+" looks eagerly into "+HIS_HER(TP)+" "+query_purse()+
            " checking its contents, but it's empty!\n");
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
  
    return 1;
}

int
rloot(string str)
{
    object *ob, ob2;
    int i,j,x,y;
    string *ctypes,*tmp;

    RICH_ACCESS(8);
    XNOTHUMBLE;

    if (!str)
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

    XNF("There's no corpse here!\n");
    if (!sizeof(ob))
        return 0;

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

    XNF("There's no money to loot!\n");
    if (!x)
        return 0;
    
    if (sizeof(ob) > 1)
    {
        write("You look with greed at the corpses, since you can clearly feel the "+
              "smell of money from them.\nYou quickly search the corpses and "+
              "put the money into your "+query_purse()+".\n");
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
    return 1;
}

int
rmembers()
{
    string s;
    RICH_ACCESS(33);

    s = (RICHROOM)->query_member_list();
    write(s);
    return 1;
}

int 
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
        return 1;
    }
    XNF("You can't do that here!\n");
    return 0;
}

int
rnews()
{
    RICH_ACCESS(1);
    FIXEUID;

    write("\n+--------------------------------------------------+\n"+
          "| $             RICH MEN'S CLUB NEWS             $ |\n"+
          "+--------------------------------------------------+\n"+
          "| 'rnews' doesn't work anymore. Use 'rc news'      |\n"+
          "| instead (as if you didn't have to do that to see |\n"+
          "| this :) )                               (970113) |\n"+
          "|                                                  |\n"+
          "|                                            Conan |\n"+
          "+--------------------------------------------------+\n\n");
    (RICHROOM)->clear_news(TP);
    return 1;
}

int
rnote(string str)
{
    RICH_ACCESS(1);
    FIXEUID;

    XNF("Notification on/off?\n");
    if (!str)
        return 0;

    if (str == "on")
    {
        (RICHROOM)->set_notification(TP, 1);
        write("You will now feel the shifts in the market.\n");
        return 1;
    }
    else if (str == "off")
    {
        (RICHROOM)->set_notification(TP, 0);
        write("You will now ignore the shifts in the market.\n");
        return 1;
    }
    XNF("Notification on/off?\n");
    return 0;
}

int
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
        return 1;
    }

    if (s == "me")  
    {
        write("Offer yourself?\n");
        say(QCTNAME(TP)+" offers "+HIM_HER(TP)+"self a loan with no interest.\n");
        return 1;
    }
    
    obs = FIND_STR_IN_OBJECT(s, environment(TP));
    obs = FILTER_OTHER_LIVE(obs);

    XNF("Offer to whom?\n");
    if (!sizeof(obs))
        return 0;
    
    for (i=0; i<sizeof(obs); ++i)  
    {
        obs[i]->catch_msg(QCTNAME(TP)+" offers you a loan with HUGE interest, "+
                          "because "+HE_SHE(TP)+" thinks you need it badly.\n");
    }

    write("You offer "+COMPOSITE_LIVE(obs)+" a loan with HUGE interest. "+
          COMPOSITE_LIVE(obs)+" seems to need it badly.\n");
    tell_room(ENV(TP), QCTNAME(TP)+" offers a loan to "+QCOMPLIVE+
              " to a HUGE interest. "+COMPOSITE_LIVE(obs)+
              " looks happy.\n",({TP})+obs);

    return 1;
}

int
rorder(string str)
{
    RICH_ACCESS(4);

    XNF("Order what?\n");
    if (!str)
        return 0;

    write("You study the prices carefully, and finally decides to "+
          "order "+LANG_ADDART(str)+".\n");
    say(QCTNAME(TP)+" studies the prices carefully, and finally decides "+
        "to order "+LANG_ADDART(str)+".\n");
    frompurse(1);
    TP->command("$order "+str);
    topurse(0);
    return 1;
}

int
rpanic()
{
    RICH_ACCESS(16);
    XNOTHUMBLE;
    
    write("You start to panic as you suddenly get a thought that you have "+
          "lost your "+
          query_purse()+". You start to search fiercly through your pockets and "+
          "with relief you find that it is still there.\n");
    say(QCTNAME(TP)+" suddenly gets panic in "+HIS_HER(TP)+" eyes and starts to "+
        "search fiercly through "+HIS_HER(TP)+" pockets. "+capitalize(HE_SHE(TP))+
        " appearantly found what "+HE_SHE(TP)+" was searching for since "+HE_SHE(TP)+
        " sighs with relief and calms down.\n");
    return 1;
}

int
rpat()
{
    RICH_ACCESS(1);
    XNOTHUMBLE;
  
    write("You pat your "+query_purse()+" lovingly. It looks well filled.\n");
    TP->add_prop(SET_EMOTE,"patting a well filled money purse");
    say(QCTNAME(TP)+" pats "+HIS_HER(TP)+" "+query_purse()+" lovingly. "+
        "It looks well filled.\n");
    return 1;
}

int
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

    XNF("Peer at yourself?\n");
    if (s == "me")
        return 0;

    obs = FIND_STR_IN_OBJECT(s, environment(TP));
    obs = FILTER_OTHER_LIVE(obs);

    XNF("Peer who?\n");
    if (!sizeof(obs))
        return 0;
    {
        for (i=0; i<sizeof(obs); ++i)
        {
            obs[i]->catch_msg(QCTNAME(TP)+" peers at you, obviously disliking "+
                              "the competition.\n");
            write("You peer at "+QTNAME(obs[i])+", disliking the competition.\n");
        }
        tell_room(ENV(TP), QCTNAME(TP)+" peers at "+QCOMPLIVE+
                  ", obviously displeased with the competition.\n",({TP})+obs);
    }
    return 1;
}

int 
rpick()
{
    RICH_ACCESS(2);
    XNOTHUMBLE;
    
    write("You feel the smell from gold and platinum coins here.\n");
    set_alarm(0.0,0.0,"getta_coins",TP);
    TP->add_prop(SET_EMOTE,"smelling the nice smell of gold and platinum");
    say(QCTNAME(TP)+" stops as if "+HE_SHE(TP)+" is smelling something.\n");
    return 1;
}

int
rnudge()
{
    RICH_ACCESS(1);
    XNOTHUMBLE;
    write("You nudge everybody in the room, showing how much joy there is "+
          "in money.\n");
    TP->add_prop(SET_EMOTE,"having very fun with money");
    say(QCTNAME(TP)+" nudges you as "+HE_SHE(TP)+" shows you how much joy "+
        "there is in money.\n");
    return 1;
}

int
rpos()
{
    string s;

    RICH_ACCESS(16);
    FILTHILY;

    s = (RICHROOM)->query_mypos(TP);
    write(s);
    return 1;
}

int
rps(string str)
{
    int i;

    RICH_ACCESS(33);
    FIXEUID;

    write((RICHROOM)->query_pos(str));
    return 1;
}

int
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
        return 1;
    }
    purge = 0;
    players = users();

    write("\n\n<RMC> Starting to purge...\n");
    for (i = 0; i < sizeof(players); i++)
    {
        lvl = (RICHROOM)->query_level(players[i]);
        if (lvl && !present("rich_club_obj",players[i]) &&
            players[i]->query_wiz_level())
        {
            write("<RMC> Purging "+capitalize(players[i]->query_real_name())+".\n");
            (RICHROOM)->purge_member(players[i],TP);
            n++;
        }
    }
    write("<RMC> Done. ");
    if (n)
    {
        write(n);
        write(" members purged.\n\n");
        return 1;
    }
    write("Found not anyone to purge.\n\n");
    return 1;
}

int
rput()
{
    int d;
    
    RICH_ACCESS(1);
  
    d = topurse(0);

    if (d == 0)
    {
        write("You look in your purse and notice some more room for your coins.\n");
        say(QCTNAME(TP)+" looks in "+HIS_HER(TP)+" "+query_purse()+
            " to make sure there is room left.\n");
    }
    else
    {
        write("You look in your purse and notice that it is full.\n");
        say(QCTNAME(TP)+" looks in "+HIS_HER(TP)+" "+query_purse()+
            " to make sure there is room left, which it isn't, because it's full "+
            "of lovely coins.\n");
    }
  
    return 1;
}

int
rscream()
{
    RICH_ACCESS(1);
    XNOTHUMBLE;
    
    write("AAAAARRRRGGGHHHH!!!!!\nYou scream in agony after discovering "+
          "that you have missed an opportunity to make lots of money!\n");
    say(QCTNAME(TP)+" screams high after discovering that "+HE_SHE(TP)+
        " has missed an opportunity to make lots of money!\n");
    return 1;
}

int
rsearch()
{
    RICH_ACCESS(8);
    
    write("You start to turn your "+query_purse()+" inside out realizing "+
          "that you spent way too much "+
          "money at the pub last night.\n");
    TP->add_prop(SET_EMOTE,"is holding a "+query_purse()+" inside out "+
                 "looking really poor");
    say(QCTNAME(TP)+" turns "+HIS_HER(TP)+" "+query_purse()+
        " inside out realizing that "+
        HE_SHE(TP)+" spent way too much money at the pub last night.\n");
    return 1;
}

int
rsell(string str)
{
    RICH_ACCESS(4);

    XNF("Sell what?\n");
    if(!str)
        return 0;
    
    say(QCTNAME(TP)+" decides to increase "+HIS_HER(TP)+" fortune by "+
        "selling some stuff, expensive...\n");
    write("You decide to sell some stuff and increase your wealth.\n");
    TP->command("$sell "+str);
    topurse(1);
    return 1;
}

int
rsetlevel(string str)
{
    string *a, b;
    int c;

    RICH_ACCESS(33);

    FIXEUID;
    
    a = explode(str, " ");

    XNF("(RMC) Error. Not able to set that level\n");
    if (sizeof(a) != 2)
        return 0;
    
    b = a[0];
    c = atoi(a[1]);

    if ((RICHROOM)->set_level(b,c))
    {
        write("(RMC) " + capitalize(b) + " has now level " + c + " in RMC.\n");
        return 0;
    }
    return 0;
}

int
rsetnews()
{
    RICH_ACCESS(33);

    FIXEUID;
    (RICHROOM)->set_all_news();
    write("OK. All members news status have been set.\n");
    return 1;
}

int
rshop()
{
    RICH_ACCESS(2);
    
    write("You laugh at the prices in the store.\n");
    say(QCTNAME(TP)+" laughs at the prices in the store.\n");
    return 1;
}

int
rsing()
{
    RICH_ACCESS(4);
    XNOTHUMBLE;
    
    write("You sing a little song about how fun there is to be wealthy, and "+
          "how boring it is to be poor.\n");
    say(QCTNAME(TP)+" sings a little song about how fun there is to be wealthy, "+
        "and how boring it is to be poor.\n");
    return 1;
}

int
rslip(string s)
{
    object *a,ob, *obs;
    string str;
    int align, i;

    RICH_ACCESS(4);

    XNF("Slip a coin to who?\n");
    if (s == "me" || !s || s == "all")
        return 0;

    obs = FIND_STR_IN_OBJECT(s, environment(TP));
    obs = FILTER_OTHER_LIVE(obs);

    frompurse(1);
    
    XNF("Slip a coin to who?\n");
    if (!sizeof(obs))
        return 0;
    
    for (i=0; i<sizeof(obs); ++i)
    {
        if(present("platinum coin",TP))
        {
            if(random(obs[i]->query_skill(SS_AWARENESS))>=TP->query_skill(SS_SNEAK))
            {
                obs[i]->catch_msg(QCTNAME(TP)+" slips a plat into your pocket.\n");
            }
            write("You slip a plat into "+QTNAME(obs[i])+"'s pocket.\n");
            TP->command("rsmile2");
            tell_room(ENV(TP), QCTNAME(TP)+" slips a plat into "+QTNAME(obs[i])+
                      "'s pocket.\n",({TP,obs[i]}));
            ob = present("platinum coin",TP);
            ob->split_heap(1);
            ob->move(obs[i]);
        }
        else
            write("You have no plats to give "+QTNAME(obs[i])+",\n");
    }
    
    topurse(0);
    return 1;
}

int
rsmile()
{
    RICH_ACCESS(1);
    XNOTHUMBLE;
  
    write("You smile greedily over the big income of yours.\n");
    TP->add_prop(SET_EMOTE,"smiling greedily");
    say(QCTNAME(TP)+" smiles so greedily over "+HIS_HER(TP)+" big income "+
        "that you almost feel sick.\n");
    return 1;
}

int
rsmile2()
{
    RICH_ACCESS(1);
  
    if (r_humb)
    {
        write("You smile generously.\n");
        TP->add_prop(SET_EMOTE,"smiling generously");
        say(QCTNAME(TP)+" smiles generously.\n");
        return 1;
    }
    write("You smile wealthily.\n");
    TP->add_prop(SET_EMOTE,"smiling wealthily");
    say(QCTNAME(TP)+" smiles wealthily.\n");
    return 1;
}

int
rsmirk()
{
    RICH_ACCESS(2);
    XNOTHUMBLE;
    
    write("You smirk wealthily, remembering the struggle from a poor newbie to "+
          "the position you have today.\n");
    say(QCTNAME(TP)+" smirks wealthily, remembering "+HIS_HER(TP)+" struggle "+
        "from poor newbie to the position "+HE_SHE(TP)+" has today.\n");
    return 1;
}

int
rspent()
{
    int hmuch;

    RICH_ACCESS(33);

    seteuid(getuid(TO));

    hmuch = (RICHROOM)->query_howmuch();
    write("\n<RMC> The Mortals has spent ");
    write(hmuch);
    write(" plats on the RMC.\n\n");
    return 1;
}

int
rsponsor(string s)
{
    object *a, ob, ob2, *obs;
    string str;
    int align, i;

    RICH_ACCESS(4);

    XNF("Nah, you don't wanna sponsor the whole world...\n");
    if (!s || s == "all")
        return 0;

    XNF("Sponsor yourself? Strange....\n");
    if (s == "me")  
        return 0;
    
    obs = FIND_STR_IN_OBJECT(s, environment(TP));
    obs = FILTER_OTHER_LIVE(obs);

    XNF("Sponsor who?\n");
    if (!sizeof(obs))
        return 0;    

    for (i=0; i<sizeof(obs); ++i)  
    {
        ob = present("platinum coin",TP);
        ob2 = present("platinum coin",purse);
        if (ob)
        {
            obs[i]->catch_msg(QCTNAME(TP)+" sponsors you with a platinum coin.\n");
            write("You sponsor "+QTNAME(obs[i])+" with a platinum coin.\n");
            tell_room(ENV(TP), QCTNAME(TP)+" sponsors "+QTNAME(obs[i])+
                      " with a platinum coin.\n",({TP, obs[i]}));
            ob->split_heap(1);
            ob->move(obs[i]);
        }
        else if (ob2)
        {
            obs[i]->catch_msg(QCTNAME(TP)+" gets a platinum coin from "+
                              HIS_HER(TP)+" "+ query_purse()+".\n"+QCTNAME(TP)+
                              " sponsors you with a platinum coin.\n");
            write("You get a plat from your "+query_purse()+".\nYou "+
                          "sponsor "+QTNAME(obs[i])+" with a platinum coin.\n");
            tell_room(ENV(TP), QCTNAME(TP)+" gets a platinum coin from "+HIS_HER(TP)+
                      query_purse()+".\n"+QCTNAME(TP)+" sponsors "+
                      QTNAME(obs[i])+" with a platinum coin.\n",({TP, obs[i]}));
            ob2->split_heap(1);
            ob2->move(obs[i]);
        }
        else
            write("You haven't got the money!\n");
    }
    return 1;
}

int
rsulk()
{
    RICH_ACCESS(2);
    
    write("You sulk in the corner since your "+query_purse()+" doesn't carry "+
          "all your platinum coins coins.\n");
    TP->add_prop(SET_EMOTE,"sulking because the "+query_purse()+
                 " is to small for the coins");
    say(QCTNAME(TP)+" sulks in the corner since the purse doesn't carry all "+
        HIS_HER(TP)+" coins.\n");
    return 1;
}

int
rsup()
{
    RICH_ACCESS(16);
    XNOTHUMBLE;
    
    write("You tell everyone how superior to them you are, since you have more "+
          "money on your account than they have, at least you think so.\n");
    say(QCTNAME(TP)+" expresses "+HIS_HER(TP)+" belief that "+HE_SHE(TP)+" is "+
        "superior to you, based on the amount of wealth.\n");
    return 1;
}

int
rtboard()
{
    object ob, *tm, ticket;
    string mt;
    int i;

    RICH_ACCESS(16);
    /*FILTHILY;*/
    XNOTHUMBLE;

    FIXEUID;

    XNF("There is no ship present!\n");
    if (!present("ship",ENV(TP)))
        return 0;

    tm = TP->query_team_others();
    if (!sizeof(tm))
    {
        rboard();
        return 1;
    }
    
    frompurse(1);
    mt = "gold";
    ob = present("gold coin",TP);
    if (!ob)
    {
        mt = "platinum";
        ob = present("platinum coin",TP);

        XNF("You haven't got any lovely money to pay the captain!\n");
        if (!ob)
        {
            topurse(0);
            return 0;
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
    return 1;
}

int
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
    return 1;
  }

  if (s == "me")  
  {
    write("Tease yourself?\n");
    say(QCTNAME(TP)+" teases "+HIM_HER(TP)+"self.\n");
    return 1;
  }
    
  obs = FIND_STR_IN_OBJECT(s, environment(TP));
  obs = FILTER_OTHER_LIVE(obs);

  XNF("Tease who?\n");
  if (!sizeof(obs))
      return 0;    
  
  for (i=0; i<sizeof(obs); ++i)  
  {
      obs[i]->catch_msg(QCTNAME(TP)+" teases you because "+HE_SHE(TP)+" thinks you "+
                        "are poorer than "+HE_SHE(TP)+" is.\n");
  }
  
  write("You tease "+COMPOSITE_LIVE(obs)+" because you think you are richer than "+
        COMPOSITE_LIVE(obs)+".\n");
  tell_room(ENV(TP), QCTNAME(TP)+" teases "+QCOMPLIVE+
            " because "+HE_SHE(TP)+" thinks "+HE_SHE(TP)+" is the richest "+
            "around.\n",({TP})+obs);
  
  return 1;
}

int
rtell(string str)
{
    object *players;
    int i, p, o, l, m;

    RICH_ACCESS(33);

    FIXEUID;
    
    players = users();
    
    for (i = 0; i < sizeof(players); i++)
    {
        p = (RICHROOM)->query_member(players[i]);
        if (p >= 0 && present("rich_club_obj", players[i]) &&
            (RICHROOM)->query_notification(players[i]))
        {
            players[i]->catch_msg("[RMC - "+CQRLNAME(TP)+"] informs you: "+str+"\n");
        }
    }
    write("You have talked to all the members.\n");
    return 1;
}

int
rtitle()
{
    int v;
    string s;

    RICH_ACCESS(16);
    FIXEUID;

    v = r_purc;
    if (v > 2000)
    {
        v -= 2000;
    }
    
    if (v > 2000)
        s = "You'll have to wait to a new title arrives. You have the highest "+
            "already.\n";
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
    return 1;
}

int
rthink()
{
    RICH_ACCESS(4);
    
    write("You think hard about going on a money hunt.\n");
    TP->add_prop(SET_EMOTE,"longing for a money hunt");
    say(QCTNAME(TP)+" looks like "+HE_SHE(TP)+" is thinking hard about going on a money hunt.\n");
    return 1;
}

int
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
            return 1;
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
            return 1;
        }
    }
    topurse(0);
    
    XNF("You haven't got any lovely plats!\n");
    return 0;
}

int
rvars(string str)
{
    int i;

    RICH_ACCESS(33);
    FIXEUID;

    (RICHROOM)->query_member_vars(str , TP);
    return 1;
}

int
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
       return 1;
    }
    write("you fail and full of shame you see the coin fall to the floor.\n");
    say(HE_SHE(TP)+" fails and looks ashamed as the coin fall to the floor.\n");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    ob->split_heap(1);
    ob->move(ENV(TP));
    topurse(0);
    return 1;
  }
  topurse(0);

  XNF("You don't have any plats!\n");
  return 0;
}

int
rwonder(string str)
{
    int diff, ma, oa;
    string me, dfeel;
    
    RICH_ACCESS(16);
    FILTHILY;

    FIXEUID;

    me = TP->query_real_name();
    ma = (RICHROOM)->query_acc(me);
    oa = (RICHROOM)->query_acc(str);

    if (oa < 0)
    {
        write(capitalize(str)+" isn't a member of our distinguished club..."+
              "propably some poor fella running around begging rich people "+
              "like you for cash!\n");
        return 1;
    }
    
    diff = oa - ma + 1;

    if (diff > 2000) dfeel = "terrified";
    else if (diff > 1000) dfeel = "desperate";
    else if (diff > 500) dfeel = "annoyed";
    else if (diff > 250) dfeel = "prosperous";
    else if (diff > 100) dfeel = "excited";
    else if (diff < (-2000)) dfeel = "very secure";
    else if (diff < (-1000)) dfeel = "secure";
    else if (diff < (-500)) dfeel = "a little insecure";
    else if (diff < (-250)) dfeel = "very insecure";
    else if (diff < (-100)) dfeel = "close to ruin";
    else dfeel = "like a poor sod";
    
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
    
    return 1;
}

int
ryawn()
{
    RICH_ACCESS(8);
    XNOTHUMBLE;
    
    write("You yawn, bored by all these poor people.\n");
    say(QCTNAME(TP)+" yawns, appearantly bored by having to listen to all "+
        "these poor people.\n");
    return 1;
}

int
rmc_commands(string str,  int rp, int ra, int rh, int ru, int l)
{
    mapping m;
    string *c, s;
    int i, a;

    r_paid = rp;
    r_acc  = ra;
    r_humb = rh;
    r_purc = ru;
    level  = l;
    
    c = explode(str, " ");
    if (sizeof(c) > 1)
    {
        s = c[1];
        if (sizeof(c) > 2)
        {
            for (i = 2; i < sizeof(c); i++)
                s += " " + c[i];
        }
    }

    m = query_rmc_commands();

    XNF("No such RMC command.\n");

    if (m[c[0]])
    {
        a = call_other(TO, m[c[0]], s);

        if (!a)
            write(xnf);
        
        return 1;
    }

    return 0;
}

/*
 * Example      : actor("You smile at", oblist);
 *                actor("You give", oblist, " a hug.");
 * Example      : target(" hugs you.", oblist);
 * Example      : targetbb(" smiles happily.", oblist);
 * Example      : all(" screams loudly.");
 * Example      : allbb(" smiles happily.");
 * Example      : all2act(" tackles", oblist);
 * Example      : all2actbb(" tackles", oblist);
 */
