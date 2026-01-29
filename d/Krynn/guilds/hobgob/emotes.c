/* A list of the hobgoblin raider emotes 
 *
 */

#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <files.h>
#include <options.h>
#include <cmdparse.h>
#include <language.h>
#include <adverbs.h>
#include <login.h>
#include "guild.h"

/*
 * Function name: emote_cmdlist
 * Description:   Get the emotes available on this soul and
 *                their corresponding function names.
 * Returns:       mapping - a mapping that maps command names
 *                          to function names.
 */
mapping
emote_cmdlist()
{
    return ([
      /* Emotes */
      "rboast"        : "rboast",
      "rcircle"       : "rcircle",
      "rcompare"      : "rcompare",
      "rgrowl"        : "rgrowl",
      "rplunder"      : "rplunder",
      "rshake"        : "rshake",
      "rsniff"        : "rsniff",
      "rstare"        : "rstare",

      /* Command name : Function name */
      "raiderlist"    : "raiderlist",
      "help"          : "help",

    ]);
}

public int
rboast(string str)
{
    int loot_rank = RAIDERS_STAT_FORMULA(TP);
    int loot_amount;
    string loot_title, loot_str;

    if(str)
    {
        notify_fail("Just boast! No need to add context!\n");
        return 0;
    }

    switch(loot_rank)
    {
        case 0..32:  // SD_AV_BEGINNER
            loot_title = "novice";
            str = "embarrass";
            break;
        case 33..52: // SD_AV_WANDERER
            loot_title = "inexperienced";
            str = "unconvincingly";
            break;
        case 53..63: // SD_AV_ADVENTURER
            loot_title = "enthusiastic";
            str = "wildly";
            break;
        case 64..86: // SD_AV_GREAT_ADVENTURER
            loot_title = "experienced";
            str = "uproariously";
            break;
        case 87..98: // SD_AV_VETERAN
            loot_title = "veteran";
            str = "shamelessly";
            break;
        case 99..111: // SD_AV_EXPERT
            loot_title = "expert";
            str = "strongly";
            break;
        case 112..139: // SD_AV_HERO
            loot_title = "fearsome";
            str = "savagely";
            break;
        case 140..169: // SD_AV_CHAMPION
            loot_title = "formidable";
            str = "ruthlessly";
            break;
        case 170..189: // SD_AV_LEGEND
            loot_title = "legendary";
            str = "murderously";
            break;
        default:
            loot_title = "mythical";
            str = "triumphantly";
            break;
    }

    // convert to steel coins
    // loot_amount = TP->query_skill(SS_RAIDERS_LOOT_VALUE) / 5000;
    loot_amount = TP->query_skill(SS_RAIDERS_LOOT_VALUE) / 1000;

    if(loot_amount > 1)
        loot_str = ", having pillaged " +LANG_NUM2WORD(loot_amount)+ 
            " steel coins for the Throtyl Raiders";
    else
        loot_str = " of the Throtyl Raiders";

    string how = FULL_ADVERB(str);

    write("You boast " +how+ " about your prowess as " +
        LANG_ADDART(loot_title)+ " looter" + loot_str + ".\n");
    allbb(" boasts " +how+ " about " +HIS(TP)+ " prowess as " +
        LANG_ADDART(loot_title)+ " looter" + loot_str + ".");
    return 1;
}

public int
rcircle(string str)
{
    object *oblist;
    object steed;

    if (!TP->query_steed())
    {
        notify_fail("You need to be mounted on a worg " +
            "to circle someone.\n");
        return 0;
    }

    steed = TP->query_steed();

    if (!steed->query_throtyl_worg())
    {
        notify_fail("You need to be mounted on a worg " +
            "from the Stormshire Forest to circle someone.\n");
        return 0;
    } 
    
    if (!strlen(str))
    {
        notify_fail("Circle whom with your worg?\n");
        return 0;
    }
    
    oblist = parse_this(str, "[at] [the] %l");
    oblist = oblist - ({ this_player() });
    
    if (!sizeof(oblist))
    {
        notify_fail("Circle whom?\n");
        return 0;
    }     
   
    if (sizeof(oblist) > 1)
    {
        notify_fail("Who do you specifically want to circle?\n");
        return 0;
    } 

    object ob = oblist[0];

    actor("You circle", oblist, " on your " +steed->steed_short()+
        ". The " +steed->steed_short()+ " growls menacingly.");
    target(" circles around you on " +HIS(TP)+ " " +steed->steed_short()+ 
        ". The " +steed->steed_short()+ " growls menacingly.", oblist);
    all2actbb(" circles", oblist, " on " +HIS(TP)+ " " +steed->steed_short()+
        ". The " +steed->steed_short()+ " growls menacingly.");
        
    return 1;
}


public int
rcompare(string str)
{
    object *oblist;
    int loot, target_loot, loot_dif;
    string * compare_msg;
    
    if (!strlen(str))
    {
        notify_fail("Compare loot with whom?\n");
        return 0;
    }
    
    oblist = parse_this(str, "[at] [the] %l");
    oblist = oblist - ({ this_player() });
    
    if (!sizeof(oblist))
    {
        notify_fail("Who do you want to compare your loot with?\n");
        return 0;
    }     
   
    if (sizeof(oblist) > 1)
    {
        notify_fail("Who do you specifically want to compare your " +
                    "loot with?\n");
        return 0;
    } 

    object ob = oblist[0];

    if (!MEMBER(ob))
    {
        notify_fail(ob->query_The_name(TP) + " is not a Throtyl Raider. " +
            "You can't compare loot gathered with them.\n");
        return 0;
    }

    loot = RAIDERS_STAT_FORMULA(TP);
    target_loot = RAIDERS_STAT_FORMULA(ob);

    loot_dif = loot - target_loot;

    switch(loot_dif)
    {
        case -500..-50:
            compare_msg = ({ "You look in awe at " +ob->query_the_name(TP)+
                ", whose pillaging and raiding feats far surpass your " +
                "own.", " looks upon you in awe, " +
                "marvelling at your feats of pillaging and raiding.",
                " looks upon " +ob->query_the_name(TP)+ " with awe, " +
                "marvelling at " +HIS(ob)+ " feats of pillaging and " +
                "raiding." });
            break;
        case -49..-10:
            compare_msg = ({ "You look in respect at " +ob->query_the_name(TP)+
                ", whose pillaging and raiding feats exceed your " +
                "own.", " looks upon you with respect, " +
                "appreciating your feats of pillaging and raiding.",
                " looks upon " +ob->query_the_name(TP)+ " with respect, " +
                "appreciating " +HIS(ob)+ " feats of pillaging and " +
                "raiding." });
            break;
        case -9..9:
            compare_msg = ({ "You note " +ob->query_the_possessive_name(TP)+
                " pillaging and raiding feats are roughly on par with your " +
                "own.", " notes that your feats of pillaging and raiding " +
                "are on par with " +HIS(TP)+ " own.",
                " notes " +ob->query_the_possessive_name(TP)+ " pillaging " +
                "and raiding feats are on par with " +HIS(TP)+ " own." });
            break;
        case 10..50:
            compare_msg = ({ "You smugly observe that your feats of pillaging " +
                " and raiding is superior to " +ob->query_the_possessive_name(TP)+
                ".", " smugly observes that " +HIS(TP)+ " feats of pillaging " +
                "and raiding are superior to your own.",
                " smugly observes that " +HIS(TP)+ " feats of pillaging " +
                "and raiding are superior to " +
                ob->query_the_possessive_name(TP)+ "." });
            break;
        default:
            compare_msg = ({ "You openly deride " +ob->query_the_possessive_name(TP)+ 
                " pathetic " +
                "history of raiding and looting compared to your own.", 
                " openly derides your history of raiding and looting as " +
                "pathetic compared to " +HIS(TP)+ " own.",
                " openly derides " +ob->query_the_possessive_name(TP)+ 
                " history of raiding and " +
                "looting as pathetic compared to " +HIS(TP)+ " own." });
            break;

    }

    write(compare_msg[0] + "\n");
    ob->catch_tell(TP->query_The_name(ob) + compare_msg[1] + "\n");
    tell_room(environment(TP), TP->query_The_name(ob) + compare_msg[2]+ "\n",
	    ({ TP, ob }), TP);
              
   return 1;
}

public int
rgrowl(string str)
{
    object *oblist;
    object steed;

    if (!TP->query_steed())
    {
        notify_fail("You need to be mounted on a worg " +
            "to make it growl.\n");
        return 0;
    }

    steed = TP->query_steed();

    if (!steed->query_throtyl_worg())
    {
        notify_fail("You need to be mounted on a worg " +
            "from the Stormshire Forest to make it growl.\n");
        return 0;
    } 
    
    if (!strlen(str))
    {
        notify_fail("Growl at whom with your worg?\n");
        return 0;
    }
    
    oblist = parse_this(str, "[at] [the] %l");
    oblist = oblist - ({ this_player() });
    
    if (!sizeof(oblist))
    {
        notify_fail("Growl at whom?\n");
        return 0;
    }     
   
    if (sizeof(oblist) > 1)
    {
        notify_fail("Who do you specifically want your worg to growl at?\n");
        return 0;
    } 

    object ob = oblist[0];

    actor("Your " +steed->steed_short()+ " growls at", oblist, ".");
    ob->catch_msg("The " +steed->steed_short()+ " " +QTNAME(TP)+ " is " +
        "mounted on growls at you.\n");
    tell_room(environment(TP), "The "+steed->steed_short()+ " " +QTNAME(TP)+ " is " +
        "mounted on growls at " +QTNAME(ob)+ ".\n", ({ TP, ob}), TP);
        
    return 1;
}

public int
rplunder(string str)
{
    if(!str)
      str = "bloodthirstily";

    if (FULL_ADVERB(str) == "")
    {
        notify_fail("Think about plundering in what way?\n");
        return 0;
    }

    string how = FULL_ADVERB(str);

    write("You stare " +how+ " into the distance, impatient to " +
        "raid and plunder the sheep of the world.\n");
    allbb(" stares " +how+ " into the distance, impatient to raid " +
        "and plunder the sheep of the world.");
    return 1;
}

public int
rshake(string str)
{
    object *oblist;

    object *weapon;
    weapon = this_player()->query_weapon(-1);

    if ((!sizeof(weapon)))
    {
	notify_fail("You are not wielding a weapon to shake!\n");
        return 0;
    }
    
    if (!strlen(str))
    {
        write("You shake the blood and gore from your " +weapon[0]->short()+
            ".\n");
        allbb(" shakes the blood and gore from " +HIS(TP)+ " " +
            weapon[0]->short()+ ".");
        return 1;
    }
    
    oblist = parse_this(str, "[at] [the] %l");
    oblist = oblist - ({ this_player() });
    
    if (!sizeof(oblist))
    {
        notify_fail("Shake your " +weapon[0]->short()+ " at whom?\n");
        return 0;
    }     
   
    if (sizeof(oblist) > 1)
    {
        notify_fail("Who do you specifically want to shake your " +
                    "weapon at?\n");
        return 0;
    } 

    object ob = oblist[0];
    int dodge = random(TP->query_stat(SS_DEX)) - ob->query_stat(SS_DEX);
    string * splatter_msg;

    if(dodge > 0)
        splatter_msg = ({ C(HE(ob))+ " is splattered with blood and gore.",
            "You are splattered with blood and gore." });
    else
        splatter_msg = ({ C(HE(ob))+ " steps out of the way " +
            "and avoids getting splattered with blood and gore.",
            "You step out of the way and avoid getting " +
            "splattered with blood and gore." });

    actor("You shake your " +weapon[0]->short()+ " towards", 
          oblist, ". " +splatter_msg[0]);
    target(" shakes " +HIS(TP)+ " " +weapon[0]->short()+ " towards you. "+ 
           splatter_msg[1], oblist);
    all2actbb(" shakes " +HIS(TP)+ " " +weapon[0]->short()+ " towards", oblist,
              ". " +splatter_msg[0]);
        
        
   return 1;
}

public int
rsniff(string str)
{
    object *oblist;
    object steed;

    if (!TP->query_steed())
    {
        notify_fail("You need to be mounted on a worg " +
            "to make it sniff someone.\n");
        return 0;
    }

    steed = TP->query_steed();

    if (!steed->query_throtyl_worg())
    {
        notify_fail("You need to be mounted on a worg " +
            "from the Stormshire Forest to make it sniff someone.\n");
        return 0;
    } 
    
    if (!strlen(str))
    {
        notify_fail("Sniff at whom with your worg?\n");
        return 0;
    }
    
    oblist = parse_this(str, "[at] [the] %l");
    oblist = oblist - ({ this_player() });
    
    if (!sizeof(oblist))
    {
        notify_fail("Sniff at whom?\n");
        return 0;
    }     
   
    if (sizeof(oblist) > 1)
    {
        notify_fail("Who do you specifically want your worg to sniff?\n");
        return 0;
    } 

    object ob = oblist[0];

    actor("Your " +steed->steed_short()+ " sniffs", oblist, " curiously.");
    ob->catch_msg("The " +steed->steed_short()+ " " +QTNAME(TP)+ " is " +
        "mounted on sniffs you curiously.\n");
    tell_room(environment(TP), "The "+steed->steed_short()+ " " +QTNAME(TP)+ " is " +
        "mounted on sniffs " +QTNAME(ob)+ " curiously.\n", ({ TP, ob}), TP);
        
    return 1;
}


public int
rstare(string str)
{
    object *oblist;
    
    if (!strlen(str))
    {
        notify_fail("Stare at whom?\n");
        return 0;
    }
    
    oblist = parse_this(str, "[at] [the] %l");
    oblist = oblist - ({ this_player() });
    
    if (!sizeof(oblist))
    {
        notify_fail("Stare at whom?\n");
        return 0;
    }     
   
    if (sizeof(oblist) > 1)
    {
        notify_fail("Who do you specifically want to stare at?\n");
        return 0;
    } 

    object ob = oblist[0];

    actor("You stare balefully at", oblist, " as you consider what you " +
        "could loot from " +HIS(ob)+ " corpse.");
    target(" stares balefully at you as " +HE(TP)+ " considers what "+ 
        HE(TP)+ " could loot from your corpse.", oblist);
    all2actbb(" stares balefully at", oblist, " as " +HE(TP)+
        " considers what " +HE(TP)+ " could loot from " +HIS(ob)+
        " corpse.");
        
   return 1;
}


int
is_raider(object ob)
{
    return ob->query_guild_member(GUILD_NAME);
}

/* Function name : raiderlist
 *       Lists the hobgoblin raiders presently in the game.
 */


int
raiderlist(string str)
{
    object *players;
    string txt = "", tmp;
    int i, wwidth = TP->query_option(1);
    int all = 0;

    if(wwidth < 11)
	wwidth = 78;

    if(str && (str == "v" || str == "verbose"))
	all = 1;

    players = filter(users(), "is_raider", this_object());

    write("The following Throtyl Raiders are currently logged on:\n");
    for(i = 0; i < sizeof(players); i++)
    {
	if(players[i]->query_invis() == 0)
	{
	    if(all)
		txt += break_string(players[i]->query_name() + " " +
		  players[i]->query_title() + "\n",wwidth-10,5)[5..];
	    else
	    {
		tmp = players[i]->query_guild_title_race();
		if(players[i]->query_wiz_level())
		    tmp = "";
		txt += break_string(players[i]->query_name() + " " +
		  (tmp && stringp(tmp) && strlen(tmp) ? tmp +
		    ", " : "") +
		  (players[i]->query_wiz_level() ? players[i]->query_title() : "the " +
		    players[i]->query_guild_title_lay()) + "\n",
		  wwidth-10,5)[5..];
	    }
	}
    }
    write(txt);
    return 1;
}



int
help(string str)
{
    string subject, filename;

    if(!str)
	return 0;

    if(sscanf(str, "hobgoblin %s", subject) != 1)
	if(sscanf(str, "raiders %s", subject) != 1)
	    if(sscanf(str, "raider %s", subject) != 1)
		return 0;

    filename = HELP_DIR + subject;
    if(file_size(filename) > 0)
    {
	setuid();
	seteuid(getuid());
	cat(filename);
	return 1;
    }

    NF("No help on that subject I'm afraid.\n");
    return 0;
}
