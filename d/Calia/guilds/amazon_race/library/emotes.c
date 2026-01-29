/*
 *    emotes.c  
 *
 * Guild emotes for the Amazon racial guild
 *
 * Baldacin@Genesis, Nov 2003   
 *
 */
 
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include "../defs.h"

int
amhelp(string str = "")
{
    string document;
    
    setuid();
    seteuid(getuid());
    
    switch(lower_case(str))
    {
        case "token": 
            document = "token.help";
            break;

        case "emotes": 
            document = "emotes.help";
            break;

        case "titles": 
            document = "titles.help";
            break;

        default:
            document = "index.help";
            break;
    }
    
    write(read_file(DOC + document)+"\n");
    return 1;
}

int
amlist()
{
   setuid();
   seteuid(getuid());
   write("The following Amazons are currently active.\n\n");
   SERVER->list_members();
   return 1;
}

int
amscan()
{
    write("With a sudden effecient motion you scan the area thoroughly.\n");
    say("With a sudden effecient motion "+QCTNAME(TP)+" thoroughly "+
      "scans the area.\n");
    return 1;
}

int
amgrin()
{
    write("A wild grin spreads over your face.\n");
    say("A wild grin spreads over "+QTPNAME(TP)+" face.\n");
    return 1;
}

int
amhungry()
{
    write("Your stomach goes 'Brrooooooaawww'.\nYou got to be hungry!\n");
    say(QCTPNAME(TP)+" stomach goes 'Brrooooooaawww'.\n"+capitalize(HE(TP))+
      " must really be hungry!\n");
    return 1;
}

int
amblaze(string str)
{
    object *livings;
    notify_fail("Blaze whom?\n");
    
    if(!strlen(str))
	return 0;

    if (parse_command(str, all_inventory(environment(TP)),
	"[the] %l", livings))       
    {
	livings = NORMAL_ACCESS(livings, 0, 0);
	if (!sizeof(livings))
	    return 0;

	this_player()->catch_msg("Eyes ablaze you point at "+
	  QTNAME(livings[0]) +", uttering ancient words of vengeance.\n");

	say("Eyes blazing, "+QTNAME(TP) + " points at "+ QTNAME(livings[0]) +
	   ", uttering ancient words of vengeance.\n", ({TP, livings[0]}));

	livings[0]->catch_msg("Eyes blazing, "+QTNAME(TP) + " points at you, "+
	   "uttering ancient words of vengeance.\n");

	return 1;
    }
    return 0;
}

int
amconcern(string str)
{    
    object *livings;

    notify_fail("Show concern to whom?\n");
    if(!strlen(str))
	return 0;

    if (parse_command(str, all_inventory(environment(TP)),
	"[the] %l", livings))       
    {
	livings = NORMAL_ACCESS(livings, 0, 0);

	if (!sizeof(livings))
	    return 0;

	this_player()->catch_msg("You look at "+ QTNAME(livings[0]) +
	  " with concern.\n");

	say(QCTNAME(TP) + " looks at "+ QTNAME(livings[0]) +
	  " with concern.\n",({TP, livings[0]}));

	livings[0]->catch_msg(QCTNAME(TP) + " looks at "+
	  "you with concern.\n");

	return 1;
    }
    return 0;
}

int
amnod(string str)
{
    object *livings;
    
    notify_fail("Nod at whom?\n");
    if(!strlen(str))
    {

        write("You make a slight nod with your head.\n");
        say(QCTNAME(TP)+" makes a slight nod with "+HIS(TP)+
          " head.\n");
        return 1;
    }

    if (parse_command(str, all_inventory(environment(TP)),
	"[at] [the] %l", livings))       
    {
	livings = NORMAL_ACCESS(livings, 0, 0);
	if (!sizeof(livings))
	    return 0;

	TP->catch_msg("You give "+QTNAME(livings[0])+" a slight nod with "+
	  "your head.\n");

	say(QCTNAME(TP) + " gives "+QTNAME(livings[0])+" a slight nod "+
	  "with "+HIS(TP)+" head.\n",({TP, livings[0]}));

	livings[0]->catch_msg(QCTNAME(TP) + " gives you a slight nod with "+
	  HIS(TP)+" head.\n");

	return 1;
     }
     return 0;
}

int
amlisten(string str)
{
    object *exits;
    
    notify_fail("Listen in what direction?\n");
    if(!strlen(str))
    {

        write("You place your hand around your right ear, listening "+
          "carefully.\n");
        say(QCTNAME(TP)+" places "+HIS(TP)+" hand around "+HIS(TP)+
          " right ear, listening carefully.\n");
        return 1;
    }
    
    exits = environment(TP)->query_non_obvious_exits() +
            environment(TP)->query_obvious_exits();
    
    if (member_array(lower_case(str), exits) != -1)       
    {

	TP->catch_msg("You place your hand around your right ear, listening "+
          "carefully to the "+lower_case(str)+".\n");
        
        say(QCTNAME(TP) + " places "+HIS(TP)+" hand around "+HIS(TP)+
          " right ear, listening carefully to the "+lower_case(str)+".\n",({TP}));

	return 1;
     }     
     return 0;
}

int
ampresent(string str)
{
    object *livings;

    notify_fail("Present <whom> with a token?\n");
    if(!strlen(str))
	return 0;

    if (parse_command(str, all_inventory(environment(TP)),
	"%l [with] [a] [token]", livings))       
    {
	livings = NORMAL_ACCESS(livings, 0, 0);

	if (!sizeof(livings))
	    return 0;

	setuid();
        seteuid(getuid());
        
        if (present("amazon_race_token", livings[0]))
        {
            TP->catch_msg(QCTNAME(livings[0])+" already have a token!\n");
            return 1;
        }
 
        if (livings[0]->query_gender() != G_FEMALE)
        {
            TP->catch_msg(QCTNAME(livings[0])+" is not a female!\n");
            return 1;
        }

		if (livings[0]->query_race_name() != "human")
        {
            TP->catch_msg(QCTNAME(livings[0])+" is not a human!\n");
            return 1;
        }
        
        clone_object(OBJ + "token")->move(livings[0], 1);
        
	TP->catch_msg("You present "+ QTNAME(livings[0]) +
	  " with a token.\n");

	say(QCTNAME(TP) + " presents "+ QTNAME(livings[0]) +
	  " with a token.\n",({TP, livings[0]}));

	livings[0]->catch_msg(QCTNAME(TP) + " presents you with "+
	  "a token.\n");
	  
	return 1;
    }
    return 0;
}

int
ampresent2(string str)
{
    object *livings;

    notify_fail("Present <whom> with a token?\n");
    if(!strlen(str))
	return 0;

    if (parse_command(str, all_inventory(environment(TP)),
	"%l [with] [a] [token]", livings))       
    {
	livings = NORMAL_ACCESS(livings, 0, 0);

	if (!sizeof(livings))
	    return 0;

	setuid();
        seteuid(getuid());
        
        if (present("amazon_race_token", livings[0]))
        {
            TP->catch_msg(QCTNAME(livings[0])+" already have a token!\n");
            return 1;
        }
 
        if (livings[0]->query_gender() != G_FEMALE)
        {
            TP->catch_msg(QCTNAME(livings[0])+" is not a female!\n");
            return 1;
        }

		if (livings[0]->query_race_name() != "human")
        {
            TP->catch_msg(QCTNAME(livings[0])+" is not a human!\n");
            return 1;
        }
        
        clone_object(OBJ + "token")->move(livings[0], 1);
        
	TP->catch_msg("You present "+ QTNAME(livings[0]) +
	  " with a token.\n");

	say(QCTNAME(TP) + " presents "+ QTNAME(livings[0]) +
	  " with a token.\n",({TP, livings[0]}));

	livings[0]->catch_msg(QCTNAME(TP) + " presents you with "+
	  "a token.\n");
	VOTING->create_new_vote(livings[0], TP);
	return 1;
    }
    return 0;
}