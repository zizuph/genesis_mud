/* A list of the Neidar emotes 
 *
 * 22.08.2003 Modified by Blizzard:
 *    set_bit(3, 13) for the people given the rune of friendship. 
 */

#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <files.h>
#include <options.h>
#include <cmdparse.h>
#include "guild.h"


#define AXEWIELDER member_array(W_AXE, TP->query_weapon(-1)->query_wt()) < 0
#define CLUBWIELDER member_array(W_CLUB, TP->query_weapon(-1)->query_wt()) < 0


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
      /* Command name : Function name */
      "clanlist" : "clanlist",
      "dappraise": "dappraise",
      "dapp"     : "dappraise",
      "daxe"     : "daxe",
      "dbang"    : "dbang",
      "dclasp"   : "dgreet",
      "dcross"   : "dcross",
      "dcrouch"  : "dcrouch",
      "dcurse"   : "dcurse",
      "dfury"    : "dfury",
      "dgasp"    : "dgasp",
      "dgift"    : "daward", 
      "dgreet"   : "dgreet2",
      "dgrin"    : "dgrin",
      "dgroan"   : "dgroan",
      "dgrunt"   : "dgrunt",
      "dhuff"    : "dhuff",
      "dkender"  : "dkender",
      "dkick"    : "dkick",
      "dlaugh"   : "dlaugh",
      "dlog"     : "dlog",
      "doutrage" : "doutrage",
      "dpick"    : "dpick",
      "drest"    : "drest",
      "dsearch"  : "dsearch",
      "dshake"   : "dshake",
      "dslap"    : "dslap",
      "dsmirk"   : "dsmirk",
      "dsnort"   : "dsnort",
      "dsong"    : "dsong",
      "dstare"   : "dstare",
      "dtear"    : "dtear",
      "dtug"     : "dtug",
      "dwave"    : "dwave",
      "help"     : "help",

    ]);
}

int
is_clan(object ob)
{
    return ob->query_guild_member(GUILD_NAME);
}

/* Function name : clanlist
 *       Lists the clanmembers presently in the game.
 */
int
clanlist(string str)
{
    object *players;
    string txt = "", tmp;
    int i, wwidth = TP->query_option(1);
    int all = 0;

    if(wwidth < 11)
	wwidth = 78;

    if(str && (str == "v" || str == "verbose"))
	all = 1;

    players = filter(users(), "is_clan", this_object());

    write("The following clan members are currently logged on:\n");
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
		    players[i]->query_guild_title_occ()) + "\n",
		  wwidth-10,5)[5..];
	    }
	}
    }
    write(txt);
    return 1;
}

int 
dappraise(string str)
{
    object *oblist, ob, *oblist2 = ({}), *oblist3 = ({});
    int    i, size;
    
    if (!strlen(str) ||
        !parse_command(str, all_inventory(TP), "[the] %i", oblist) ||
        !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)) )
    {
        NF("What do you want to appraise?\n");
        return 0;
    }
    
    for ( i = 0; i < sizeof(oblist); i++)
    {
        ob = oblist[i];
        if ( ob->check_armour() || ob->check_weapon() )
            oblist2 += ({ ob });
    }
    
    if ( !sizeof(oblist2) )
    {
        NF("You can appraise weapons and armours only.\n");
        return 0;
    }
    
    write("You carefully appraise your equipment trying to estimate its " +
        "condition. ");
    allbb(" carefully inspects " + HIS(TP) + " equipment.");
    
    size = sizeof(oblist2);
    
    for ( i = 0; i < size; i++)
    {
        ob = oblist2[i];
        
        if ( ob->check_armour() && 
           ((ob->query_condition() - ob->query_repair()) > 0) )
        {
            oblist3 += ({ ob });
        }
        
        if ( ob->check_weapon() && 
           ((ob->query_dull() - ob->query_repair_dull()) > 0) )
        {
            oblist3 += ({ ob });
        }
    }
    
    if ( !sizeof(oblist3) )
    {
        write("You notice it is in prime condition.\n");
        return 1;
    }
    
    str  = COMPOSITE_DEAD(oblist3);
    size = sizeof(oblist3);
    
    write("You notice that " + str + " " + 
        ((size > 1) ? "require" : "requires") + " some smith's work.\n");
    return 1;
}

int
daxe(string str)
{
    object ob, *wep, weapon, *obj;

    if(!strlen(str))
    {
	notify_fail("Who do you entertain thoughts of putting " +
	  "an axe into?\n");
	return 0;
    }

    obj = parse_this(str, "[at] [the] %l");
    
    if( !sizeof(obj) )
    {
	notify_fail("Who do you entertain thoughts of putting " +
	  "an axe into?\n");
	return 0;
    }

    wep = TP->query_weapon(-1);
    ob = obj[0];
    
    if ( !sizeof(wep) )
    {
        notify_fail("It is a pity you are not wielding any weapon. You " +
            "would gladly smash the skull of " + QTNAME(ob) + ".\n");
        return 0;
    }
    
    weapon = wep[0];
    
    if ( (weapon->query_wt() != W_AXE) && (weapon->query_wt() != W_CLUB) )
    {
        notify_fail("Damn, if only you had an axe or a club!\n");
        return 0;
    }
    
    actor("You entertain thoughts concerning your " + weapon->short() +
      " and", obj, "'s head.");
    target(" entertains thoughts of " +HIS(TP)+ " " + weapon->short() +
      " and your head.", obj);
    all2act(" entertains thoughts of " +HIS(TP)+ " " + weapon->short() +
      " and", obj, "'s head.");
    return 1;
}

int
dbang(string str)
{
    string helm_desc;
    object obj, *ob;

    if(strlen(str))
    {
	ob = parse_this(str, "[at] [the] %l");

	if(!sizeof(ob))
	{
	    notify_fail("Bang your head against what?\n");
	    return 0;
	}

	obj = ob[0];

	if(member_array(A_HEAD, TP->query_armour(-1)->query_at()) < 0)
	{
	    notify_fail("You are not wearing a helm to adjust!\n");
	    return 0;
	}

	helm_desc = TP->query_armour(A_HEAD)->short();

	if(obj->query_race() == "dwarf")
	{
	    TP->catch_msg("You bang your head into " +QTNAME(obj) + "'s head " +
	      "in an attempt to adjust your " +helm_desc+ ". " +QCTNAME(obj)+
	      " grins back at you dwarvishly.\n");
	    obj->catch_msg(QCTNAME(TP)+ " bangs " +HIS(TP)+ " head into " +
	      "your head in an attempt to adjust " +HIS(TP)+ " " +
	      helm_desc+ ". Having a head as hard as stone, you grin " +
	      "dwarvishly back at " +QTNAME(TP) + ".\n");
	    TP->tell_watcher(QCTNAME(TP)+ " bangs " +HIS(TP)+ " head " +
	      " into " +QTNAME(obj)+ "'s head in an attempt to adjust " +
	      HIS(TP)+ " " +helm_desc+ ". " +QCTNAME(obj)+ 
	      " looks unaffected by the blow, and grins dwarvishly " +
	      "back at " +QTNAME(TP)+ ".\n", obj);
	    return 1;
	}

	if(obj->query_race() == "goblin")
	{
	    TP->catch_msg("You bang your head hard into " +QTNAME(obj)+
	      "'s head in an attempt to adjust your " +helm_desc+
	      ". " +QCTNAME(obj)+ " looks somewhat puzzled by the " +
	      "blow, and wobbles unsteadily for a moment much to " +
	      "your amusement.\n");
	    obj->catch_msg(QCTNAME(TP)+ " bangs " +HIS(TP) + " head " +
	      "hard into your head in an attempt to adjust " +HIS(TP)+
	      " " +helm_desc+ ". For a moment the world tilts strangely " +
	      "before you, and you just manage to catch yourself " +
	      "before your legs fall out from beneath you.\n");
	    TP->tell_watcher(QCTNAME(TP)+ " bangs " +HIS(TP)+
	      " head hard into the head of " +QTNAME(obj)+ " in an " +
	      "attempt to adjust " +HIS(TP)+ " " +helm_desc+ ". " +
	      QCTNAME(obj)+ " looks somewhat dazed by the blow, " +
	      "and wobbles unsteadily on his feet for a moment much " +
	      "to " +QTNAME(TP)+ "'s amusement.\n", obj);
	    return 1;
	}
	if(obj->query_race() == "gnome" || obj->query_race() == "hobbit")
	{
	    TP->catch_msg("You bang your head into " +QTNAME(obj)+
	      "'s head in an attempt to adjust your " +helm_desc+ 
	      ". " +QCTNAME(obj)+ " staggers backwards clutching " +
	      HIS(obj)+ " head, and groans in pain.\n");
	    obj->catch_msg(QCTNAME(TP)+ " bangs " +HIS(TP)+ " head into " +
	      "your own head in an attempt to adjust " +HIS(TP)+ " " +
	      helm_desc+ ". The blow makes you stagger backwards, " +
	      "and you groan in pain as you wonder whether a dwarves " +
	      "mentality has anything to do with " +HIS(TP)+ 
	      " rock hard head.\n");
	    TP->tell_watcher(QCTNAME(TP)+ " bangs " +HIS(TP)+ 
	      " head into " +QTNAME(obj)+ "'s head in an attempt to " +
	      "adjust " +HIS(TP)+ " " +helm_desc+ ". " +QCTNAME(obj)+
	      " staggers backwards clutching " +HIS(obj)+ " head, " +
	      "and groans in pain.\n", obj);
	    return 1;
	}

	if(obj->query_race() == "human" || obj->query_race() == "elf")
	{
	    write("Tall folk are no good for adjusting ones helm. Find " +
	      "someone smaller.\n");
	    return 1;
	}

	notify_fail("That isn't good banging material.\n");
	return 0;
    }

    if(member_array(A_HEAD,TP->query_armour(-1)->query_at()) < 0)
    {
	notify_fail("You are not wearing a helm to adjust!\n");
	return 0;
    }

    helm_desc = TP->query_armour(A_HEAD)->short();

    write("You kneel down and bang your head vigorously " +
      "into the ground in an attempt to adjust your " +helm_desc+ ".\n");
    allbb(" kneels down and bangs " +HIS(TP)+ " head vigorously " +
      "into the ground in an attempt to adjust " +HIS(TP)+ " " +helm_desc+ ".");
    return 1;
}

int
dcross(string str)
{

    if(strlen(str))
    {
	return 0;
    }

    write("You cross your arms, stubbornly refusing to cooperate.\n");
    allbb(" crosses " +HIS(TP)+ " arms, stubbornly refusing to cooperate.");
    return 1;
}

int
dcrouch(string str)
{
    if(strlen(str))
	return 0;

    write("You crouch down on your stubby legs into a fighting stance, " +
      "ready for battle!\n");
    allbb(" crouches down on " +HIS(TP)+ " stubby legs into a " +
      "fighting stance, ready for battle!");
    return 1;
}

int
dcurse(string str)
{
    object *ob;
    
    if( !strlen(str) )
    {
        write("You curse the Mountain dwarves to eternal rust and " + 
            "corrosion!\n");
	say(QCTNAME(TP) + " curses the Mountain dwarves to eternal rust and " +
	    "corrosion!\n");
	return 1;
    }

    ob = parse_this(str, "[at] [the] %l");

    if( !sizeof(ob) )
    {
	notify_fail("Curse whom?\n");
	return 0;
    }

    actor("You curse",ob," to eternal rust and corrosion!");
    target(" curses you to eternal rust and corrosion!", ob);
    all2act(" curses",ob," to eternal rust and corrosion!");

    return 1;

}

int
dfury(string str)
{
    if(strlen(str))
    {
	return 0;
    }

    /*If female*/
    if(TP->query_gender() == 1)
    {
	write("Your whiskers quiver in fury!\n");
	allbb("'s whiskers quiver in fury!");
	return 1;
    }

    write("You feel your beard quiver with fury!\n");
    allbb("'s beard quivers in fury!");
    return 1;
}


int
dgasp(string str)
{
    if(strlen(str))
    {
	return 0;
    }

    write("You gasp out in astonishment: By Reorx's grey beard!\n");
    allbb(" gasps out in astonishment: By " +
      "Reorx's grey beard!");
    return 1;
}

int
daward(string str)
{
    object *ob, obj;
    object rune;

    if(strlen(str))
    {
	ob = parse_this(str, "[the] %l");
	if(!sizeof(ob))
	{
	    notify_fail("Gift who with a rune of friendship?\n");
	    return 0;
	}
	obj = ob[0];

	if(TP->test_bit("Ansalon",3,3) && TP->test_bit("Ansalon",3,4))
	{
	    notify_fail("A banished dwarf cannot award " +
	      "a rune of friendship.\n");
	    return 0;
	}

	if(!TP->test_bit("Ansalon",3,3) && !TP->test_bit("Ansalon",3,4))
	{
	    if(TP->query_stat(SS_OCCUP) < 168)
	    {
		notify_fail("Only the Thane, clan chieftains, " +
		  "and clan Elders can gift others with runes of friendship.\n");
		return 0;
	    }
	}

	if(obj->query_guild_member("Dwarven Warriors of the Neidar Clan"))
	{
	    notify_fail("Runes of friendship are for non-clan members.\n");
	    return 0;
	}

	if(obj->query_npc())
	{
	    notify_fail("Runes are for players stupid!\n");
	    return 0;
	}
        
        if ( obj->test_bit("Ansalon", 3, 13) && P("ansalon_rune_object", obj) )
        {
            notify_fail("But that person has been already given the " +
                "rune of friendship.\n");
            return 0;
        }
        
	actor("You solemnly give", ob, " a black obsidian " +
	  "rune of dwarven craftsmanship, a gift of " +
	  "friendship from the Neidar clan.");
	target(" solemnly gives you a black obsidian rune of " +
	  "dwarven craftsmanship that hangs from a silver " +
	  "chain, a gift to symbolise that friendship " +
	  "between you and the dwarven Neidar clan.", ob);
	all2act(" solemnly gives", ob, " a black obsidian rune of dwarven " +
	  "craftsmanship that hangs from a silver " +
	  "chain, a rare gift from the Neidar clan dwarves.");

	setuid();
	seteuid(getuid());
	rune = clone_object("/d/Ansalon/estwilde/obj/dwarf_rune");
	rune->move(obj);

        if ( !obj->test_bit("Ansalon", 3, 13) ) 
    	    obj->set_bit(3, 13);            /* 22.08.2003 added by Blizzard */
	
	log_file(ELDER_LIST, extract(ctime(time()), 4, 15)+ " "+
	  C(TP->query_real_name())+ " awarded a rune of friendship to "+
	  C(obj->query_real_name())+ ".\n", -1);

	return 1;
    }
    notify_fail("Gift whom?\n");
    return 0;
}

int
dgreet(string str)
{
    object *ob;

    if(!strlen(str))
    {
	notify_fail("Greet who?\n");
	return 0;
    }

    ob = parse_this(str, "[at] [the] %l");

    if(!sizeof(ob))
    {
	notify_fail("Greet who?\n");
	return 0;
    }

    actor("You clasp the forearm of",ob," in a traditional dwarven handshake of greetings.");
    target(" clasps your forearm in a traditional dwarven handshake of greetings.", ob);
    all2act(" clasps",ob,"'s forearm in a traditional dwarven handshake of greetings.");
    return 1;
}

int
dgreet2(string str)
{
    object *ob, *wep, weapon;

    if(!strlen(str))
    {
	notify_fail("Greet who?\n");
	return 0;
    }

    ob = parse_this(str, "[at] [the] %l");

    if(!sizeof(ob))
    {
	notify_fail("Greet who?\n");
	return 0;
    }
    
    wep = TP->query_weapon(-1);
    
    if ( !sizeof(wep) )
    {
        actor("You raise your hand in greetings to", ob,".");
        target(" raises " + HIS(TP) + " hand in greetings to you.", ob);
        all2act(" raises " + HIS(TP) + " hand in greetings to", ob, ".");
        return 1;
    }
    
    weapon = wep[0];
            
    actor("You raise your " + weapon->short() + " in greetings to", ob,
        " shouting 'Axes High!'");
    target(" raises " + HIS(TP) + " " + weapon->short() + " in greetings " +
        "to you, shouting 'Axes High!'", ob);
    all2act(" raises " + HIS(TP) + " " + weapon->short() + " in greetings " +
        "to", ob, " shouting 'Axes High!'");
        
    return 1;
}

int
dgrin(string str)
{
    if(strlen(str))
    {
	write("What? You want to grin in more than one way? Bah! You ask too much!\n");
	return 0;
    }

    write("You grin madly, the crazy glint of battlelust shining " +
      "brightly in your eyes.\n");
    allbb(" grins madly, the crazy glint of battlelust " +
      "shining brightly in " +HIS(TP)+ " eyes.");
    return 1;
}

int
dgroan(string str)
{
    if(strlen(str))
    {
	return 0;
    }

    write("You throw your hands into the air, groaning loudly in exasperation.\n");
    allbb(" throws " +HIS(TP)+ " hands into the air, groaning loudly in exasperation.");
    return 1;
}

int
dhuff(string str)
{

    object *ob;

    if(!strlen(str))
    {
	write("You look around increduously and throw yourself " +
	  "onto the ground in a huff, refusing to move.\n");
	all(" looks around increduously, and then throws " +HIM(TP)+
	  "self onto the ground in a huff, refusing to move.");
	return 1;
    }

    ob = parse_this(str, "[at] [the] %l");

    if(!sizeof(ob))
    {
	notify_fail("Have a huff with who?\n");
	return 0;
    }

    actor("You look at", ob, " increduously and throw yourself onto " +
      "the ground in a huff, refusing to move.");
    target(" looks at you increduously, and then throws " +HIM(TP)+
      "self onto the ground in a huff, refusing to move.", ob);
    all2act(" looks at", ob, " increduously, and then throws " +HIM(TP)+
      "self onto the ground in a huff, refusing to move.");
    return 1;
}

int
dgrunt(string str)
{
    if(strlen(str))
    {
	return 0;
    }
    write("You grunt.\n");
    allbb(" grunts.");
    return 1;
}


int
dkender(string str)
{
    if(strlen(str))
	return 0;

    write("Seeing a kender, you quickly secure all your pockets "+
      "and pouches to make sure nothing gets lost.\n");
    say(QCTNAME(TP) +" scowls suspiciously at the sight of a " +
      "kender, and quickly secures all " +HIS(TP)+ " pockets " +
      "and pouches.\n");
    return 1;
}


int
dkick(string str)
{
    object ob = P("corpse",E(TP));
    string corpse_desc;

    if( !str || str != "corpse" )
    {
	notify_fail("Kick what corpse?\n");
	return 0;
    }

    if(ob && E(ob) && E(ob) == E(TP))
    {

	corpse_desc = ob->short();

	write("You give the " +corpse_desc+ " a mighty " +
	  "boot, daring it to get back up and face you, " +
	  "a mighty dwarven warrior!\n");
	say(QCTNAME(TP) + " gives the " +corpse_desc+
	  " a mighty kick, daring it to get back up " +
	  "and face " +HIM(TP)+ ", a mighty dwarven " +
	  "warrior!\n");
	return 1;
    }
    notify_fail("Kick what corpse?\n");
    return 0;
}

int
dlaugh(string str)
{

    object *ob;

    if(!strlen(str))
    {
	write("You slap your knees and roar with laughter.\n");
	all(" slaps " +HIS(TP)+ " knees and roars with laughter.");
	return 1;
    }

    ob = parse_this(str, "[at] [the] %l");

    if(!sizeof(ob))
    {
	notify_fail("Laugh at whom?\n");
	return 0;
    }

    actor("You throw your head back and roar with laughter at", ob, ".");
    target(" throws " +HIS(TP)+ " head back and roars with laughter at you.", ob);
    all2act(" throws " +HIS(TP)+ " head back and roars with " +
      "laughter at", ob, ".");
    return 1;
}

int
dlog(string str)
{
    object ob, *corpse;
    object weapon, *wep;
    string corpse_desc, *adj_list;

    if( !str )
    {
        str = "corpse";
    }

    if ( !parse_command(lower_case(str), E(TP), "[the] %i", corpse) ||
        !sizeof(corpse = NORMAL_ACCESS(corpse, 0, 0)) )
    {
        notify_fail("Log your weapon in what corpse?\n");
        return 0;
    }
    
    ob = corpse[0];
    
    if ( !IS_CORPSE_OBJECT(ob) )
    {
        notify_fail("This ain't a corpse! You can't do that.\n");
        return 0;
    }
    
    wep = TP->query_weapon(-1);
    
    if ( !sizeof(wep) )
    {
        notify_fail("But you are not wielding any weapon to do that.\n");
        return 0;
    }
    
    weapon = wep[0];
    
    if ( ob && E(ob) && E(ob) == E(TP) )
    {

	corpse_desc = ob->short();
        adj_list = ob->query_adjs();
                
        if ( weapon->query_dt() == W_CLUB )
        {
            if ( sizeof(adj_list) && 
                (member_array("headless", adj_list) != -1) )
            {
                write("You take a firm grip on your " + weapon->short() +
                    " and smash it into the " + corpse_desc + 
                    ", to make sure it is dead.\n");
                say(QCTNAME(TP) + " takes a firm grip on " + HIS(TP) +
                    " " + weapon->short() + " and smashes it into the " +
                    corpse_desc + ", to make sure it is dead.\n");

                return 1;
            }
               
            write("You take a firm grip on your " + weapon->short() +
                " and smash it into the head of the " + corpse_desc + 
                ", to make sure it is dead.\n");
            say(QCTNAME(TP) + " takes a firm grip on " + HIS(TP) +
                " " + weapon->short() + " and smashes it into the " +
                "head of the " + corpse_desc + ", to make sure it " +
                "is dead.\n");

            return 1;
        }
        
        if ( sizeof(adj_list) && (member_array("headless", adj_list) != -1) )
        {
            write("You take a firm grip on your " + weapon->short() +
                " and logs it into the " + corpse_desc + 
                ", to make sure it is dead.\n");
            say(QCTNAME(TP) + " takes a firm grip on " + HIS(TP) +
                " " + weapon->short() + " and logs it into the " +
                corpse_desc + ", to make sure it is dead.\n");

            return 1;
        }
        
	write("You take a firm grip on your " + weapon->short() +
	    " and log it into the head of the " + corpse_desc + 
	    ", to make sure it is dead.\n"); 
	say(QCTNAME(TP) + " takes a firm grip on " + HIS(TP) +
	    " and logs it into the head of " + corpse_desc +
	    ", to make sure it is dead.\n"); 

	return 1;
    }

    notify_fail("Log your weapon in what corpse?\n");
    return 0;
}

int
doutrage(string str)
{
    if(strlen(str))
    {
	return 0;
    }

    write("You feel your face turning red in outrage!\n");
    allbb("'s face turns red in outrage!");
    return 1;
}


int
dpick(string str)
{

    string *how = parse_adverb_with_space(str, "idly", 0);
    
    if ( strlen(how[0]) )
    {
        notify_fail("Pick your nose how?\n");
        return 0;
    }

    write("You pick your nose" + how[1] + ".\n");
    allbb(how[1] + " picks " + HIS(TP) + " nose.");

    return 1;
}

int
drest(string str)
{
    string weapon, tmp_str;
    weapon = TP->query_weapon(-1);
  
    if( !strlen(str) ) 
    {
	str = "goblin";
    }
    
    str = lower_case(str);
    if ( sscanf(str, "%s", tmp_str) == 1)
    {
        str = tmp_str;
    }
    
    if ( !parse_command(str, ({}), 
        "'goblin' / 'minotaur' / 'ogre' / 'troll' / 'orc' / 'hobgoblin' / 'giant'") )
    {
        notify_fail("Rest after a long day of bashing what?\n");
        return 0;
    }
        
    if(!sizeof(TP->query_weapon(-1)))
    {
	notify_fail("You have no weapon to lodge into the ground.\n");
	return 0;
    }

    write("You lodge your " +weapon[0]->short()+ " into the ground, " +
      "resting your arms briefly after a long day of " + str + " bashing.\n");
    say(QCTNAME(TP)+ " lodges " +HIS(TP)+ " " +weapon[0]->short()+
      " into the ground, resting " +HIS(TP)+ " arms briefly " +
      "after a long day of " + str + " bashing.\n");

    return 1;
}

int
dsearch(string str)
{
    if( strlen(str) && str != "pockets" && str != "all" )
    {
        notify_fail("Search your pockets?\n");
	return 0;
    }

    write("You search your pockets to see if you have lost anything.\n");
    allbb(" searches " + HIS(TP) + " pockets for something.");
    return 1;
}

int
dshake(string str)
{
    if(strlen(str))
    {
	return 0;
    }

    write("You shake your head stubbornly in refusal.\n");
    allbb(" shakes " +HIS(TP)+ " head stubbornly in refusal.");
    return 1;
}

int
dslap(string str)
{
    object *ob;
    object obj;
    int str_diff;

    if(!strlen(str))
    {
	notify_fail("Who do you want to give a hearty slap on the back?\n");
	return 0;
    }

    ob = parse_this(str, "[at] [the] %l");

    if(!sizeof(ob))
    {
	notify_fail("Who do you want to give a hearty slap on the back?\n");
	return 0;
    }

    obj = ob[0];

    actor("You give", ob, " a hearty slap on the back.");
    target(" gives you a hearty slap on the back.", ob);
    all2act(" gives",ob," a hearty slap on the back.");

    str_diff = TP->query_stat(SS_STR) - obj->query_stat(SS_STR);

    if(str_diff > 60)
    {
	TP->catch_msg(QCTNAME(obj)+ " almost falls over from the blow.\n");
	obj->catch_msg("You almost fall over from the powerful blow.\n");
	TP->tell_watcher(QCTNAME(obj)+ " almost falls over from the blow.\n", obj);
	return 1;
    }
    if(str_diff > 40)
    {
	obj->catch_msg("You stagger forward from the blow.\n");
	obj->tell_watcher(QCTNAME(obj)+ " staggers forward from the blow.\n");
	return 1;
    }
    if(str_diff > 30)
    {
	obj->catch_msg("Your breath is blown out of you from the blow.\n");
	obj->tell_watcher(QCTNAME(obj) + " seems to loose " +HIS(obj)+
	  " breath from the blow.\n");
	return 1;
    }

    if(str_diff > 20)
    {
	obj->catch_msg("You can't help but wince slightly from the blow.\n");
	obj->tell_watcher(QCTNAME(obj) + " can't help but wince slightly " +
	  "from the blow.\n");
	return 1;
    }

    return 1;
}

int
dsmirk(string str)
{
    if(strlen(str))
	return 0;

    write("You smirk at the stupidity of tall folk.\n");
    allbb(" smirks at the stupidity of tall folk.");
    return 1;
}


int
dsnort(string str)
{
    if(strlen(str))
    {
	return 0;
    }

    write("You snort in derision.\n");
    allbb(" snorts in derision.");
    return 1;
}



void
verse_two()
{
    string song;

    song = "\n\nOut of the mountains in the midst of the air,\n"+
    " The axes are dreaming dreaming of rock,\n"+
    "   Of metal alive through the ages of ore,\n" +
    "      Stone on metal metal on stone.\n" +
    " The soldier's heart contains and dreams\n" +
    "              The battlefield.\n" +
    "             Come back in glory\n" +
    "              Or on your shield.\n\n\n";

    write("You continue to sing:" +song);
    TP->tell_watcher(QCTNAME(TP) + " continues to sing:" +song);
}

void
verse_three()
{
    string song;

    song = "\n\n     Red of iron imagined from the vein,\n" +
    "       Green of brass green of copper\n" +
    "  Sparked in the fire the forge of the world,\n" +
    " Consumed in its dream as it dives into the bone.\n" +
    "   The soldier's heart lies down, completes\n" +
    "               The battlefield.\n" +
    "              Come back in glory\n" +
    "               Or on your shield.\n\n\n";

    write("You continue to sing:" +song+
      "\nYour blood stirred by the song, you feel ready for battle.\n");
    TP->tell_watcher(QCTNAME(TP)+ " continues to sing:" +song+
      "\n" +QCTNAME(TP)+ " falls silent, and looks ready for battle.\n");
}

int
dsong(string str)
{
    string song;

    if(strlen(str))
	return 0;

    song = "\n        Under the hills the heart of the axe\n" +
    "    Arises from cinders the still core of the fire,\n" +
    "Heated and hammered the handle an afterthought,\n" +
    "  For the hills are forging the first breath of war.\n" +
    "       The soldier's heart sires and brothers\n" +
    "                   The battlefield.\n" +
    "                  Come back in glory\n" +
    "                   Or on your shield.\n\n\n";

    write("Your deep dwarven voice rises in song:\n" +song);
    TP->tell_watcher(QCTNAME(TP)+ "'s deep dwarven voice " +
      "rises in song:\n" +song);

    set_alarm(3.0, 0.0, "verse_two");
    set_alarm(6.0, 0.0, "verse_three");

    return 1;
}

int
dstare(string str)
{

    object *ob;

    if(!strlen(str))
    {
	write("You stare forward, keeping your face as emotionless as stone.\n");
	all(" stares forward, " +HIS(TP)+ " face so emotionless " +
	  "you would swear it was set in stone.");
	return 1;
    }

    ob = parse_this(str, "[at] [the] %l");

    if(!sizeof(ob))
    {
	notify_fail("Stare at whom?\n");
	return 0;
    }
    actor("You stare at", ob, ", your face set as emotionless as stone.");
    target(" stares at you, " +HIS(TP)+ " face so emotionless you " +
      "would swear it was set in stone.", ob);
    all2act(" stares at", ob, ", " +HIS(TP)+ " face so emotionless you would " +
      "swear it was set in stone.");
    return 1;
}

int
dtear(string str)
{

    if(strlen(str))
    {
	return 0;
    }

    if(TP->query_gender() == 1)
    {
	/*Where the gender is female */
	write("You pull at your whiskers in frustration!\n");
	allbb(" pulls at her whiskers in frustration!");
	return 1;
    }

    write("You tear at your beard in frustration!\n");
    allbb(" tears at " +HIS(TP)+ " beard in frustration!");
    return 1;
}

int
dtug(string str)
{
    if(strlen(str))
    {
	return 0;
    }

    /*If female, they have no beard!*/
    if(TP->query_gender() == 1)
    {
	write("You have no beard to tug on!\n");
	return 1;
    }

    write("You tug at your beard thoughtfully.\n");
    allbb(" tugs at " +HIS(TP)+ " beard thoughtfully.");
    return 1;
}

int
dwave(string str)
{

    object *ob;
    string weapon;

    weapon = TP->query_weapon(-1);

    if(sizeof(TP->query_weapon(-1)))
    {

	if(!strlen(str))
	{
	    write("You raise your " +weapon[0]->short()+ " in farewell, " +
	      "saying: Axes high friend, I go.\n");
	    all(" raises " +HIS(TP)+ " " +weapon[0]->short()+ " in farewell, saying: " +
	      "Axes high friend, I go.");
	    return 1;
	}

	ob = parse_this(str, "[at] [the] %l");
	if(!sizeof(ob))
	{
	    notify_fail("Farewell who?\n");
	    return 0;
	}

	actor("You raise your " +weapon[0]->short()+ " in " +
	  "farewell to", ob, ", saying: Axes high friend, I go.");
	target(" raises " +HIS(TP)+ " " +weapon[0]->short() +
	  " to you in farewell, saying: Axes high friend, I go.", ob);
	all2act(" raises " +HIS(TP)+ " " +weapon[0]->short()+
	  " to", ob, " in farewell, saying: Axes high friend, I go.");
	return 1;
    }

    if(!strlen(str))
    {
	write("You raise a gnarled hand in farewell, saying: Axes high " +
	  "friend, I go.\n");
	all(" raises a gnarled hand in farewell, saying: Axes high friend, I go.");
	return 1;
    }

    ob = parse_this(str, "[at] [the] %l");
    if(!sizeof(ob))
    {
	notify_fail("Farewell who?\n");
	return 0;
    }

    actor("You raise a gnarled hand in farewell to", ob, ", saying: " +
      "Axes high friend, I go.");
    target(" raises a gnarled hand in farewell to you, saying: " +
      "Axes high friend, I go.", ob);
    all2act(" raises a gnarled hand in farewell to", ob, ", saying: Axes " +
      "high friend, I go.");
    return 1;
}



int
help(string str)
{
    string subject, filename;

    if(!str)
	return 0;

    if(sscanf(str, "guild %s", subject) != 1)
	if(sscanf(str, "clan %s", subject) != 1)
	    if(sscanf(str, "dwarves %s") != 1)
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
