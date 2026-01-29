/*
 * This is the emote file for the Imladris guild.
 * It should be included by the soul-file for the 'Healers'
 * as they were called when this file was created.
 *
 * File: /d/Shire/imladris/guild/songs.h
 * Please add comments as you modify this file.
 *
 * Nov. 11 1994
 * Sir Odin.
 *
 *  Modify the soul so it used query_option instead of query_get_echo
 *  -Igneous-
 */

inherit "/cmd/std/command_driver";

#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include <options.h>

#include "/d/Shire/defs.h"
//#include "/d/Shire/imladris/guild/lib/rsongs.h"
#include "/d/Shire/imladris/guild/lib/songs.h"

#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))

/*
 * Here is the soul identification and autoloading 
 */

string get_soul_id()
{
	return "testsoul";
}

int 
query_cmd_soul()
{
	return 1;
}

/*
 * Here follows the functions. Please add new in alphabetical order!
 * Add like this;	Verb	:	function
 */

mapping
query_cmdlist()
{
	return ([
		"approve"	:	"approve",
		"ibless"	:	"ibless",
		"disapprove"	:	"disapprove",
	 	"disapp"	:	"disapprove",
	 	"hail"		:	"ihail",
		"ichant"	:	"ichant",
		"flex"		:	"do_flex",
		"iremember"	:	"iremember",
		"sing"		:	"do_song",
		"powers"	:	"powers"
		   ]);
}

int
approve(string str)
{
	object *ob;

	if (!str)
	{
		write("You approve the idea.\n");
		all(" approves the idea after some consideration.");
		return 1;
	}

	ob = parse_this(str, "[with] %l");
	if (!sizeof(ob))
	{
	    NF("Approve who's idea?\n");
	    return 0;
	}
	
	actor("You give your approval to", ob, "'s idea.");
	target(" gives "+HIS_HER(TP)+" approval of your idea.", ob);
	all2act("  gives "+HIS_HER(TP)+" approval of", ob, "'s idea.");
	return 1;
}

int
ibless(string str)
{
	object *ob;
	
	SOULDESC("blessing in the name of the Valar");
	 
	if(!strlen(str))
	{
	    write("You bless the Valar for the powers they have granted you.\n");
	    all(" blesses the Valar gods for granting "+HIM_HER(TP)+" such magnificent powers.");
	    return 1;
	}
	
	ob = parse_this(str, "[the] %l");	

	if (!sizeof(ob))
	{
	    NF("Bless whom?\n");
	    return 0;
	}
	actor("You bless", ob, " gracefully with the powers the Valar.");
	target(" blesses you gracefully with the powers of the Valar.", ob);
	all2act(" blesses", ob, " with some divine powers!");
	return 1;
}

int
disapprove(string str)
{
	object *ob;
	
	if (!str)
	{
		write("You disapprove the idea and find it rather bad.\n");
		all(" disapproves with the idea, finding it rather bad.");
		return 1;
	}	

	ob = parse_this(str, "[with] %l");

	if (!sizeof(ob))
	{
		NF("Disapprove with whom?\n");
		return 0;
	}

	actor("You disapprove the idea of", ob, ", shaking your head.");
	target(" disapproves with your idea, shaking "+HIS_HER(TP)+" head.", ob);
	all2act("  disapproves with", ob, "'s idea, shaking "+HIS_HER(TP)+" head.");
	return 1;
}

int
ihail(string str)
{
    object *ob;
    int r;
    string who;
    who = "";
    r = random(8);
    
    switch(r)
    {
    case 0: who = "Gil-galad"; break;
    case 1: who = "Galadriel"; break;
    case 2: who = "Feanor"; break;
    case 3: who = "Earendil"; break;
    case 4: who = "Cirdan"; break;
    default: who = "Elrond o Imladris"; break;
    }
        
    if (!strlen(str))
    {
    	write("You greet everyone in the name of "+who+".\n");
    	all(" smiles happily, saying: Ai "+who+"! Ar  mae govannen meldir!");
    	return 1;
    }
    
    ob = parse_this(str, "[the] %l");
    
    if (!sizeof(ob))
    {
    	NF("Hail who?\n");
    	return 0;
    }
    
    actor("You hail", ob, " in the name of "+who+".");
    target(" bows before you, saying: Ai na vedui fedhin! Mae govannen!", ob);
    all2act("  bows before", ob, ", saying: Ai na vedui! Mae govannen!");
    return 1;
}

    

 

int
iremember(string str)
{
    write("You look towards Imladris and remember the days of the Great\n");
    write("Battle in the first age when Melkor was utterly destroyed.\n");
    all(" turns to the north, as if thinking of something  that has happened.");
    all(" smiles happily thinking of the Great Battle of the First age.");
    return 1;
}
/*

int
powers(string str)
{


	
*/



int
ichant(string str)
{
	object	*oblist, *members, *others;
	string	*how;

	how = parse_adverb_with_space(str, "quietly", 0);
	SOULDESC("chanting" + how[1]);

	if (!strlen(how[0]))
	{
	write("You chant" + how[1] + " in Sindarin.\n");
	all(" chants" + how[1] + " in a long forgotten elven language.\n");
	return 1;
	}

	oblist = parse_this(how[0], "[at] [the] %l");

	if (!sizeof(oblist))
	{
		oblist = FILTER_LIVE(all_inventory(ENV(TP)));
                if(TP->query_option(OPT_ECHO))
			write("You chant: "+ str +"\n");
		else
			write("Ok.\n");
		members = find_player("odin") && filter(oblist, "member_filter", this_object());
		others = oblist - members;
		target(" chants: " + str, members - ({TP}));
		target(" chants in some weird language, completely unknown to you.", others);
		return 1;
	}
	
	target(" chants" + how[1] + " at you.", oblist);
	actor("You chant" + how[1] + " at", oblist, ".");
	all2act("  chants" + how[1] + " at", oblist, ".");
	return 1;
}

int
do_flex(string arg)
{
    int str;
    object *ob, tp = TP, *lower_str, *higher_str, *same_str;
 
    seteuid(getuid());
                    
    /*if (TP->query_ghost())
  	return fail_ghost();
    */    
    
    ob = parse_this(arg, "[to] [the[ %l");
    
    if (!strlen(arg))
    {
    	write("You flex your muscels to impress everyone.\n");
    	all(" flexes "+HIS_HER(tp)+" muscels.\nYou watch, rather untouched by the performance.");
    	SOULDESC("flexing "+HIS_HER(tp)+" muscels");
    	return 1;
    }

    if (!sizeof(ob))
    {
    	NF("Flex your muscels to whom?\n");
    	return 0;
    }

    str = tp->query_stat(SS_STR);

    higher_str  = filter(ob, "f_higher_str", TO, str);
    lower_str   = filter(ob, "f_lower_str", TO, str);
    same_str    = ob - higher_str - lower_str;
                                
    if (sizeof(higher_str))
    {
     	target(" flexes "+HIS_HER(tp)+" muscels very impressingly. You watch "+
             "astonished and aknowledges "+HIS_HER(tp)+" imense strength.", higher_str );
        write(CAP(COMPOSITE_LIVE(higher_str)) +" is impressed by your muscel-show.\n");
        say(CAP(COMPOSITE_LIVE(higher_str)) +" is impressed by "+QTNAME(tp)+"'s muscel-show.\n",
        higher_str + ({tp}));
        return 1;
    }
    if (sizeof(lower_str))
    {
    	actor("You flex your muscels to impress", lower_str);
   	target(" flexes "+HIS_HER(tp)+" muscels to impress you. You watch rather bored.", lower_str);
    	all2act(" flexes "+HIS_HER(tp)+" muscels to impress", lower_str, ". "+HE_SHE(lower_str)+" looks rather bored.");
    	SOULDESC("flexing "+HIS_HER(tp)+" muscels");
    	return 1;
    }
    if (sizeof(same_str))
    {
    	actor("You flex your muscels to impress", same_str);
    	target(" flexes "+HIS_HER(tp)+" muscels to impress you.\nSomehow you know you have seen that before.", same_str);
    	all2act(" flexes "+HIS_HER(tp)+" muscels to impress", same_str, ", but without luck.");
        return 1;
    }
    return 1;
}
