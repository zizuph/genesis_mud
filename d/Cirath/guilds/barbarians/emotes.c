/*
 * List of basic barbarian emotes
 */

#include <macros.h>
#include <composite.h>
#include <files.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <options.h>
#include <cmdparse.h>
#include <adverbs.h>

#include "guild.h"

/*
 * List of commands
 * Add new in alphabetic order
 */
 
int
query_brutelevel(object tp)
{
  int cxp,qxp,txp;

  cxp = tp->query_exp_combat();
  txp = tp->query_exp();
  qxp = txp - cxp;

  if (cxp > 2*qxp) return 2;

  return 1;
}
 
mapping
emotes_cmdlist()
{
    return ([
    /* ************** EMOTES **************** */
        "bbanger"	:"bbanger",
      	"bcrom"		:"bcrom",
        "bcry"		:"bcry",
        "bdislike"	:"bdislike",
      	"bdrool"      	:"bdrool",
  	"bfist"       	:"bfist",
  	"bgaze"		:"bgaze",
  	"bgrin"       	:"bgrin",
  	"bhail"       	:"bhail",
  	"bhmpf"		:"bhmpf",
  	"bhug"        	:"bhug",
  	"bimpress"     	:"bimpress",
  	"bjoy"     	:"bjoy",
  	"bkiss"       	:"bkiss",
  	"blaugh"      	:"blaugh",
  	"blick"       	:"blick",
  	"bpeer"       	:"bpeer",
  	"bpray"       	:"bpray",
  	"bpunch"      	:"bpunch",  
  	"bshake"      	:"bshake",
  	"bsmile"      	:"bsmile",
  	"bsniff"      	:"bsniff",
  	"bstomp"      	:"bstomp",
  	"bsulk"       	:"bsulk",
  	"btrack"      	:"btrack",      	
    ]);
}

int
bbanger(string str)
{
    	object *oblist;

    	if(!strlen(str))
    	{
		write("YAAAAAAAAARRRRRRGGGGGHHHHHH!!!!!!!!!!!!!\n");
		all2act(" screams loudly in anger of being neglected to have the kill!",oblist);
		return 1;
    	}
	
	return 0;   
}

int
bcrom(string str)
{
    	if(strlen(str))
		return 0;
		
	write("CROM!!\n");
	all2act(" goes CROM!!");
	return 1;    	
}

int
bcry(string str)
{
    	if(strlen(str))
		return 0;

    	write("You raise your voice, shouting: Victory for the Herders!\n");
    	all2act(" raises" + HISHER + " voice, shouting: Victory for the Herders!");
    	return 1;  
}

int
bdislike(string str)
{
    	object *oblist;

    	if(!strlen(str) || !sizeof(oblist = parse_this(str, "[the] %l")))
    	{
		NF("Greet whom?\n");
		return 0;
    	}

    	target(" shows with a vomitous grimace what " + HESHE+ " thinks of you.", oblist);
    	actor("You show with a vomitous grimace what you think of",oblist);
    	all2act(" shows with a vomitous grimace what " + HESHE+ " thinks of",oblist);
    	return 1;
}

int
bdrool(string str)
{
    	object *ob;

    	if(!strlen(str))
    	{
		write("You slime! You drool on all over yourself!\n");
		allbb(" drools all over "+HIMHER+"self.");
		return 1;
    	}

    	ob = parse_this(str, "[at] [the] %l");
    	if(!sizeof(ob))
    	{
		NF("Drool on whom?\n");
		return 0;
    	}

    	targetbb(" starts to drool all over you.", ob);
    	actor("You start to drool all over",ob);
    	all2actbb(" starts to drool all over",ob);
    	return 1;
}

int
bfist(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "angrily", 0);

    if (!strlen(how[0]))
    {
	write("Your raise your fist" + how[1] + ".\n");
	allbb("raises " + HISHER + " huge fist" + how[1] + ".");
	return 1;
    }
    oblist = parse_this(how[0], "[at] [the] %l");
    if (!sizeof(oblist))
    {
	NF("Raise your fist [at whom]?\n");
	return 0;
    }

    actor("You raise your fist"+how[1]+" at", oblist,".");
    targetbb(how[1]+"raises " + HISHER + " huge fist at you! You feel threatened.", oblist);
    all2actbb(how[1]+" raises " + HISHER + " huge fist towards ", oblist," in a threatening way.");
    return 1;
}

int
bgaze(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "evilly", 0), gazestr;

    if (!strlen(how[0]))
    {
	write("You gaze"+how[1]+" at your companions. They look nasty.\n");
	allbb(" gazes at you"+how[1]+". You feel uneasy.");
	return 1;
    }
    oblist = parse_this(how[0], "[at] [the] %l");
    if (!sizeof(oblist))
    {
	NF("Gaze how [at whom]?\n");
	return 0;
    }

	gazestr = HE_SHE(oblist[0]);

   	targetbb(" gazes at you"+how[1]+". You feel uneasy.", oblist);
    	actor("You gaze "+how[1]+" at", oblist, ", " + gazestr + " looks like a whimp.");
    	all2actbb(" gazes "+how[1]+" at", oblist, ", sure that " + gazestr + " is a whimp.");
    return 1;
}

int
bgrin(string str)
{
	object *oblist;

    	if(!strlen(str))
    	{
		write("You show your sharpened teeth in a vicious grin.\n");
		allbb(" shows " + HISHER + " sharpened teeth in a vicious grin.");
		return 1;
    	}  
  
  	if(!sizeof(oblist = parse_this(str, "%l")))
    	{
		NF("Raise your fist at who?\n");
		return 0;
    	}

    	target(" grins viciously at you. Showing " + HISHER + " sharpened teeth.", oblist);
    	actor("You grins viciously at", oblist, ". Showing your sharpened teeth.");
    	all2act(" grins viciously at", oblist, ". Showing " + HISHER + " sharpened teeth.");
    	return 1;
}

int
bhail(string str)
{
    	object *oblist;

    	if(!strlen(str))
    	{
		write("Hail who?\n");
		return 1;
    	}  
  
  	if(!sizeof(oblist = parse_this(str, "%l")))
    	{
		NF("Hail who?\n");
		return 0;
    	}

    	target(" hails you in the name of Crom.", oblist);
    	actor("You hail", oblist, " in the name of Crom.");
    	all2act(" hails", oblist, " in the name of Crom.");
    	return 1;
}

int
bhmpf(string str)
{
    	object *oblist;

    	if(!strlen(str))
    	{
		write("Hmpf!!\n");
		allbb(" goes hmpf!!");
		return 1;
    	}

	NF("What?\n");
	return 0;   
}

int
bhug(string str)
{
  	object *oblist;
  	int brute;

  	brute = query_brutelevel(TP);

  	if(!strlen(str))
    	{
      		write("Hug yourself? Perhaps you need a teddy bear?\n");
		return 1;
      	}
      	
      	if(!sizeof(oblist = parse_this(str, "%l")))
    	{
		NF("Hug who?\n");
		return 0;
    	}
      	
      	if (brute == 2)
      	{
      	target(" hugs you the barbarian way. It hurts!", oblist);
    	actor("You hug", oblist, " the barbarian way. Hard and brutal!");
    	all2act(" hugs", oblist, " the barbarian way. Hard and brutal!");
    	return 1;
      	}
      	      	
      	target(" hugs you softly. The way wimpies do.", oblist);
    	actor("You hug", oblist, " soft and gentle. Like a whimp.");
    	all2act(" hugs", oblist, " the whimpy way. Soft and gentle.");
    	return 1;
}

int
bimpress(string str)
{
  	object *oblist;
  	int brute, tpcon, obcon;

  	brute = query_brutelevel(TP);

  	if(!strlen(str))
    	{
      		write("You look at you big biceps and impress yourself.\n");
		allbb(" looks at " + HISHER + " big biceps and impresses " + HIMHER + "self.");
		return 1;
      	}
      	
      	if(!sizeof(oblist = parse_this(str, "%l")))
    	{
		NF("Impress who?\n");
		return 0;
    	}
    	
      	tpcon = TP->query_stat(SS_CON);
  	obcon = oblist[0]->query_stat(SS_CON);
  	
      	if (brute == 2)
      	{
      		if(tpcon>obcon)
    		{
      	target("  tries to impress you by showing " + HISHER + " biceps, "
      			+ HESHE + " succeeds. You are impressed.", oblist);
    	actor("You try to impress", oblist, " by showing your biceps. You succeed.");
    	all2act(" tries to impress", oblist, " by showing " + HISHER + " biceps, " 
    	+ HESHE +" seems to succeed, because ", oblist, " looks very impressed by the view.");
    	return 1;
      		}
      	}
      	target(" tries to impress you by showing" + HISHER + "biceps,"
      		+ HESHE + " failed. You just laugh at " + HISHER + " puny muscles.", oblist);
    	actor("You try to impress", oblist, " by showing your biceps. You failed.");
    	all2act(" tries to impress", oblist, " by showing " + HISHER + " biceps, "
    		+ "but " + HESHE + " has puny muscles.");
    	return 1;    	
}     

int
bjoy(string str)
{
    	object *oblist;

    	if(!strlen(str))
    	{
		write("You smile with all your face, showing how much joy there is in killing\n");
		allbb(" smiles with all " + HISHER + " face, revealing how much joy there is in killing.");
		return 1;
    	}

	NF("What?\n");
	return 0;   
}

int
bkiss(string str)
{
  	object *oblist;
  	int brute;

  	brute = query_brutelevel(TP);

  	if(!strlen(str))
    	{
      		write("Kiss yourself. You're STUPID!!!\n");
		return 1;
      	}
      	
      	if(!sizeof(oblist = parse_this(str, "%l")))
    	{
		NF("Hug who?\n");
		return 0;
    	}
      	
      	if (brute == 2)
      	{
      	target(" kisses you hard and intesive. You're chocked by " + HISHER + " barbarian behaviour.", oblist);
    	actor("You kiss", oblist, " like a true barbarian. Hard and intensive.");
    	all2act(" kisses", oblist, " like a true barbarian. Hard and intensive.");
    	return 1;
      	}
      	      	
      	target(" kisses your cheek very gentle. The whimpy way of kissing.", oblist);
    	actor("You kiss", oblist, " very gentle on the cheek, like the whimp you are.");
    	all2act(" kisses", oblist, " gently on the cheek, like the whimp " + HESHE + " is.");
    	return 1;
}

int
blaugh(string str)
{
	object *oblist;

    	if(!strlen(str))
    	{
		write("You start to laugh and it seems you can not stop doing it.\n");
		allbb(" starts to laugh, louder and louder.");
		return 1;
    	}  
  
  	if(!sizeof(oblist = parse_this(str, "%l")))
    	{
		NF("Laugh at who?\n");
		return 0;
    	}

    	target(" starts to laugh at you. Getting louder by the second.", oblist);
    	actor("You start to laugh at", oblist, ". Getting louder by the second.");
    	all2act(" starts to laugh at", oblist, ". Getting louder by the second.");
    	return 1;
} 

int
blick(string str)
{
	object *oblist;

    	if(!strlen(str))
    	{
		write("You start to lick your lips in pure exitement of possibilities of "+
    			"unlimited slaying.\n");
		allbb(" starts to lick " + HISHER + " lips in excitement over the "+
   			"possibilities of unlimited slaying.");
		return 1;
    	}  
  
  	if(!sizeof(oblist = parse_this(str, "%l")))
    	{
		NF("Lick who?\n");
		return 0;
    	}

    	target(" considers licking you, but decides not to.", oblist);
    	actor("You consider licking", oblist, ", but then decide not to.");
    	all2act(" considers licking", oblist, ", but decides not to.");
    	return 1;
} 

int
bpeer(string str)
{
	object *oblist;

    	if(!strlen(str))
    	{
		write("You peer into the sky hoping for something to attack you.\n");
		allbb(" peers into the sky hoping for something to attack " + HIMHER + ".");
		return 1;
    	}  
  
  	if(!sizeof(oblist = parse_this(str, "%l")))
    	{
		NF("Peer at who?\n");
		return 0;
    	}

    	target(" peers at you. You think " + HESHE + " is considering attacking you!", oblist);
    	actor("You peer at", oblist, ", considering your attack options.");
    	all2act(" peers at", oblist, ", considering an attack.");
    	return 1;
} 

int
bpray(string str)
{	
  	if(!strlen(str))
	{   	
		write("You kneel down and pray to your mighty warlord, Crom.\n");
		allbb(" kneels down and prays to " + HISHER + " mighty warlord, Crom.");
		return 1;
    	}	
    	NF("What?\n");
	return 0;   
}

int
bpunch(string str)
{
  	object *oblist;
  	int brute;

  	brute = query_brutelevel(TP);

  	if(!strlen(str))
    	{
      		write("Punch yourself out?\n");
		return 1;
      	}
      	
      	if(!sizeof(oblist = parse_this(str, "%l")))
    	{
		NF("Punch who?\n");
		return 0;
    	}
      	
      	if (brute == 2)
      	{
      	target(" punches you the barbarian way. It hurts!", oblist);
    	actor("You punch", oblist, " the barbarian way, painfully!");
    	all2act(" punches", oblist, " the barbarian way, painfully!");
    	return 1;
      	}
      	      	
      	target(" punches you softly. The way wimpies do.", oblist);
    	actor("You punch", oblist, " softly like a whimp.");
    	all2act(" punches", oblist, " the way wimpies do.");
    	return 1;
}

int
bshake(string str)
{
  	object *oblist;
  	int brute;

  	brute = query_brutelevel(TP);

  	if(!strlen(str))
    	{
    		if (brute == 2)
    		{
      		write("You shake violently! Looking for something else to kill.\n");
		allbb(" shakes violently! Looking for something to kill.");
		return 1;
		}
		write("You start to tremble and hope nothing sees you!\n");
		allbb(" starts to tremble and looks for a place to hide.");
		return 1;
      	}
      	
      	if(!sizeof(oblist = parse_this(str, "%l")))
    	{
		NF("Shake who?\n");
		return 0;
    	}
      	
      	if (brute == 2)
      	{
      	target(" shakes your hand in a barbarian greeting. It hurts!", oblist);
    	actor("You shake hands with", oblist, " squeezing hard, the barbarian way.");
    	all2act(" shakes hands with", oblist, " in a barbarian greeting.");
    	return 1;
      	}
      	      	
      	target(" shakes your hand in a barbarian greeting. It should hurt but it doesn't!", oblist);
    	actor("You shake hands with", oblist, " squeezing softly, like a whimp!");
    	all2act(" looks like a whimp shaking hands with", oblist);
    	return 1;
}

int
bsmile(string str)
{
  	object *oblist;
  	int brute;
  	string smilestr;

  	brute = query_brutelevel(TP);

  	if(!strlen(str))
    	{
    		if (brute == 2)
    		{
      		write("You smile in a true brutal way. You look dangerous.\n");
		allbb(" smiles in a true brutal way. " + HESHE + " looks dangerous.");
		return 1;
		}
		write("You to embarrased to smile!\n");
		allbb(" starts to smile but now looks embarrased.");
		return 1;
		
      	}
      	
      	if(!sizeof(oblist = parse_this(str, "%l")))
    	{
		NF("Smile at who?\n");
		return 0;
    	}
    	
      	smilestr = HE_SHE(oblist[0]);
      	
      	if (brute == 2)
      	{
      	target(" smiles at you in a true brutal way. " + HESHE + " looks dangerous.", oblist);
    	actor("You smile at ", oblist, " in a true brutal way. You look dangerous.");
    	all2act("  smiles at", oblist, " in a true brutal way. " + HESHE + " look dangerous.");
    	return 1;
      	}
      	      	
      	target(" starts to look at you but is embarrassed.", oblist);
    	actor("You try to smile at", oblist, ". But " + smilestr + " laughes at you.");
    	all2act(" starts to look at", oblist, ". But " + smilestr + " laughes at " + HIMHER + ".");
    	return 1;
}

int
bsniff(string str)
{
  	object *oblist;
  	int brute;
  	
  	brute = query_brutelevel(TP);

  	if(!strlen(str))
    	{
    		if (brute == 2)
    		{
      		write("You raise your arm and sniff in your armpit. It smells lovely.\n");
		allbb(" sniffs in " + HISHER + " armpit and looks pleased with the smell.");
		return 1;
		}
		write("You raise your arm and sniff in your armpit. It smells bad!\n");
		allbb(" sniffs in "+ HISHER +" armpit, "+ HESHE +" looks disgusted.");
		return 1;
		
      	}
      	
      	if(!sizeof(oblist = parse_this(str, "%l")))
    	{
		NF("Sniff who?\n");
		return 0;
    	}
      	
      	
    	NF("You decide not to be so obvious with your fantasies.\n");
    	return 0;      	
}

int
bstomp(string str)
{
    	object *oblist;

    	if(!strlen(str))
    	{
		write("STOMP!!!\n");
		allbb(" stomps hard in the ground causeing it to rumble.");
		return 1;
    	}

	NF("You prefer to stomp your feet.\n");
	return 0;    	
}

int
bsulk(string str)
{
    	object *oblist;

    	if(!strlen(str))
    	{
		write("You get so disappointed not getting what you want and start to sulk like a spoiled child.\n");
		allbb(" starts acting like a spoiled child and sulks because " + HESHE + " didn't "+
    		"get what "+Q_PR(TP)+" wanted.");
		return 1;
    	}

	NF("You decide not to.\n");
	return 0;    	
}

int
btrack(string str)
{
    	object *oblist;

    	if(!strlen(str))
    	{
		write("You search the ground for tracks of slayable enemies.\n");
		allbb(" starts to search the ground for tracks of slayable enemies.");
		return 1;
    	}

	NF("Track what?\n");
	return 0;   
}

