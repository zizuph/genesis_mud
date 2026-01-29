/* vamp_soul.c created by Shiva@Genesis 8/01/95
 * This is the vampire guild cmdsoul.  A few emotes
 * taken from Mylos' vampyr guild.
 *
 * Reused for the new half-orc guild. Nerull 2022
 */
inherit "/lib/commands";

#pragma save_binary
#pragma no_clone
#pragma strict_types

#include "../guild.h"
#include <cmdparse.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <stdproperties.h>
#include <files.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>



#define SOULDESC(x)  (this_player()->add_prop(LIVE_S_SOULEXTRA, x))
#define POSSTP        this_player()->query_possessive())
#define PROTP        (this_player()->query_pronoun())
#define OBJTP        (this_player()->query_objective()
#define CQV          capitalize(query_verb())
#define TP           this_player()

varargs void
tell_others(string str, object *exclude)
{
    object *players;

    players = all_inventory(environment(this_player())) - exclude;
    players = FILTER_PLAYERS(FILTER_CAN_SEE_IN_ROOM(players));

    if (sizeof(players))
    {
        players->catch_msg(str);
    }
}


public string query_eyes_desc(object player)
{
    string desc=player->query_eyes();
    if (!desc)
    {
        return "eyes";
    }
    return desc+(player->query_eyes_number()==1 ? " eye" : " eyes");
}
    


///////////////////////////////////////////////////

int horoar(string str)
{
    if (strlen(str))
    {
        return 0;
    }

    write("You tilt your head back and let out a terrifying roar.\n");
    allbb(" tilts "+TP->query_possessive()+" head back and let out a terrifying roar.");

    return 1;
}


int holaugh(string str)
{
    if (strlen(str))
    {
        return 0;
    }

    write("You tilt your head back and let out a hearty laugh.\n");
    allbb(" tilts "+TP->query_possessive()+" head back and let out a hearty laugh.");

    return 1;
}


int hostretch(string str)
{
    if (strlen(str))
    {
        return 0;
    }

    write("You stretch your arms over your head one at the "
	+"time and flex your muscles, displaying an impressive physique.\n");
	
    allbb(" stretches "+TP->query_possessive()+" arms over " 
	+TP->query_possessive()+" head one at the time and flexes " 
	+TP->query_possessive()+" muscles, displaying an impressive physique.");

    return 1;
}


int hothink(string str)
{
    if (strlen(str))
    {
        return 0;
    }

    write("You fold your arms across your chest and rest your chin "
	+"in your hand, looking thoughtful as you absentmindedly fondle one of your tusks.\n");
	
    allbb(" folds "+TP->query_possessive()+" arms across "+TP->query_possessive()+" chest and rests " 
	+TP->query_possessive()+" chin in "+TP->query_possessive()+" hand, looking very thoughtful as "
	+this_player()->query_pronoun()+" absentmindedly fondle one of "+TP->query_possessive()+" tusks.\n");

    return 1;
}

///////////////////////////////////////////////////




public int
hoscowl(string str)
{
    object *oblist;
    string his_her;
	
	string eyes=query_eyes_desc(TP);
    
    if (!strlen(str) ||
        sizeof(oblist = parse_this(str, "[at] %l")) != 1)
    {
        notify_fail("Scowl at whom?\n");
        return 0;
    }
  
    his_her = POSS(oblist[0]);
  
    target(" scowls at you with "+TP->query_possessive()+" "
	+eyes+" and bares "+TP->query_possessive()+" teeth while snarling.", oblist);
		   
    actor("You scowl at", oblist, " with your "+eyes+" and "
        +"bare your teeth while snarling.");
		  
		  
    all2actbb(" scowls at", oblist, " with "
	+TP->query_possessive()+" "+eyes+" and bares "
	+TP->query_possessive()+" teeth while snarling.");
  
    return 1;
}


public int
hogreet(string str)
{
    object *oblist;
    string his_her;
	
	string eyes=query_eyes_desc(TP);
    
    if (!strlen(str) ||
        sizeof(oblist = parse_this(str, "[at] %l")) != 1)
    {
        notify_fail("Greet whom?\n");
        return 0;
    }
  
    his_her = POSS(oblist[0]);
  
    target(" grunts and tilts "+TP->query_possessive()
	+" head back in an upwards nod at you.", oblist);
		   
    actor("You grunt and tilt your head back in an upwards nod at", oblist, " in a friendly greeting.");
		  	  
    all2actbb(" grunts and tilts "+TP->query_possessive()
	+" head back in an upwards nod at", oblist,".");
  
    return 1;
}


public int
hoamused(string str)
{
    object *oblist;
    string his_her;
	
	string eyes=query_eyes_desc(TP);
	
	if (!strlen(str))
    {
        write("You snort and grin in amusement.\n");
        allbb(" snorts and grins in apparent amusement.");
        return 1;
    }
    
    if (!strlen(str) ||
        sizeof(oblist = parse_this(str, "[at] %l")) != 1)
    {
        notify_fail("Amused at whom?\n");
        return 0;
    }
  
    his_her = POSS(oblist[0]);
  
    target(" snorts and grins at you in apparent amusement.", oblist);
		   
    actor("You snort and grin in amusement at", oblist, ".");
		  	  
    all2actbb(" snorts and grins in apparent amusement at", oblist,".");
  
    return 1;
}


public int
hofrown(string str)
{
    object *oblist;
    string his_her;
	
	string eyes=query_eyes_desc(TP);
	
	if (!strlen(str))
    {
        write("You wrinkle your nose and grunt in disapproval.\n");
        allbb(" wrinkles "+TP->query_possessive()+" nose and grunts in disapproval.");
        return 1;
    }
    
    if (!strlen(str) ||
        sizeof(oblist = parse_this(str, "[at] %l")) != 1)
    {
        notify_fail("Frown at whom?\n");
        return 0;
    }
  
    his_her = POSS(oblist[0]);
  
    target(" wrinkles "+TP->query_possessive()+" nose and grunts in disapproval at you.", oblist);
		   
    actor("You wrinkle your nose and grunt in disapproval at", oblist, ".");
		  	  
    all2actbb(" wrinkles "+TP->query_possessive()+" nose and grunts in disapproval at", oblist,".");
  
    return 1;
}











