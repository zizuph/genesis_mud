#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";
inherit "/cmd/std/command_driver";
inherit "/d/Genesis/lib/multi_alarm";
inherit "/d/Cirath/guilds/barbarians/attack/slayattack.c";
inherit "/d/Cirath/guilds/barbarians/attack/stabattack.c";

#include "defs.h"
#include <cmdparse.h>
#include <wa_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include "/std/combat/combat.h"
#include <macros.h>

string
get_soul_id()
{
    return "The Barbarian Herd";
}

int
query_cmd_soul()
{
    return 1;
}

/* **********************************************************************
 * The list of verbs and functions. Please add new in alphabetical order.
 */
mapping
query_cmdlist()
{
    return ([
      /* ************** COMMANDS ************** */
     	"bl"	   	:"barblist",
     	"bcheck"	:"bcheck",
    // 	"bchop"       	:"bchop",
      	"bconvert"    	:"bconvert",
      	"bel"		:"belderlist",
     	"bbonk"    	:"bbonk",
      	"bhelp"    	:"bhelp",
  //	"bscream"     	:"bscream",
     	"slay"       	:"slayattack",
     	"stab"       	:"stabattack",
      
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

void
create()
{
    seteuid(getuid());
}

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

string
query_clan_name(object ob)
{
  if(ob->query_skill(SS_BARB_SCORE) == 1)      return "White Eagle Clan";
  else if(ob->query_skill(SS_BARB_SCORE) == 2) return "Mammoth Clan";

  return "";
}

int
query_clan_number(object ob)
{
  int sc,eld,clan;

  sc = ob->query_skill(SS_BARB_SCORE);

  eld = sc / 10;
  clan = sc - (eld * 10);

  return clan;
}

/* ******************* emotes begin here ********************* */

int
bbanger(string str)
{
    	object *oblist;

    	if(!strlen(str))
    	{
		write("YAAAAAAAAARRRRRRGGGGGHHHHHH!!!!!!!!!!!!!\n");
		allbb(" screams loudly in anger of being neglected to have the kill!");
		return 1;
    	}

	NF("What?\n");
	return 0;   
}

int
bcrom(string str)
{
    	object *oblist;

    	if(!strlen(str))
    	{
		write("CROM!!\n");
		allbb(" goes CROM!!");
		return 1;
    	}

	NF("What?\n");
	return 0;   
}

int
bcry(string str)
{
    	object *oblist;

    	if(!strlen(str))
    	{
		write("You raise your voice to a bloodfreezing combat cry.\n");
		allbb(" raises " + HISHER + " voice to a bloodfreezing combat cry.");
		return 1;
    	}

    	if(!sizeof(oblist = parse_this(str, "%l")))
    	{
		write("You raise your voice to a combat cry saying:\n" + str + "!\n");
		allbb(" raises " + HISHER + " voice to a combat cry:\n" + str + "!");
		return 1;
    	}

    	target(" raises " + HISHER + " voice at you in a bloodfreezing combat cry.", oblist);
    	actor("You raise your voice at",oblist, " in a bloodfreezing combat cry.");
    	all2act(" raises" + HISHER + " voice at ",oblist, " in a bloodfreezing combat cry.");
    	return 1;
}

int
bdislike(string str)
{
    	object *oblist;

    	if(!strlen(str))
    	{
		NF("Dislike who?\n");
		return 0;
    	}

    	if(!sizeof(oblist = parse_this(str, "%l")))
    	{
		NF("Dislike who?\n");
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
    	object *oblist;

    	if(!strlen(str))
    	{
		write("You slime! You drool on all over yourself!\n");
		allbb(" drools all over "+HIMHER+"self.");
		return 1;
    	}

    	if(!sizeof(oblist = parse_this(str, "%l")))
    	{
		NF("Drool on whom?\n");
		return 0;
    	}

    	target(" starts to drool all over you.", oblist);
    	actor("You start to drool all over",oblist);
    	all2act(" starts to drool all over",oblist);
    	return 1;
}

int
bfist(string str)
{
  	object *oblist;

    	if(!strlen(str))
    	{
		write("Raise your fist towards yourself? You're nuts!\n");
		return 1;
    	}  
  
  	if(!sizeof(oblist = parse_this(str, "%l")))
    	{
		NF("Raise your fist at who?\n");
		return 0;
    	}

    	target(" raises " + HISHER + " huge fist at you! You feel threatened.", oblist);
    	actor("You raise your fist towards", oblist, " in a rather threatening way.");
    	all2act(" raises " + HISHER + " huge fist towards ", oblist, "in a threatening way.");
    	return 1;
}
  
int
bgaze(string str)
{
  	object *oblist;  	
  	string gazestr;

  	if(!strlen(str))
    	{    		
      		write("You gaze suspiciously at your companions. They look nasty.\n");
		allbb(" gazes at you suspiciously. You feel uneasy.");
		return 1;		
      	}
      	
      	if(!sizeof(oblist = parse_this(str, "%l")))
    	{
		NF("Gaze at who?\n");
		return 0;
    	}
    	
      	gazestr = HE_SHE(oblist[0]);
      
      	{
      	target(" gazes at you. You feel uneasy.", oblist);
    	actor("You gaze suspiciously at", oblist, ", " + gazestr + " looks like a whimp.");
    	all2act(" gazes suspiciously at", oblist, ", sure that " + gazestr + " is a whimp.");
    	return 1;
      	}      	 
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

/* ******************** emotes end here ********************* */

/* ****************** commands begin here ********************* */

int
barblist(string str)
{
  	object *players;
  	string cnam;
  	int i;

  	players = users();
  	write("\nThese are the mighty Barbarians that stalks Genesis:\n");
  	write("----------------------------------------------------\n");
  	for (i = 0; i < sizeof(players); i++)
   	{
      		if (players[i]->query_guild_member("The Barbarian Herd"))
      		{
        	 	cnam = query_clan_name(players[i]);
         		write("- " + players[i]->query_name() + " " +
         		players[i]->query_title() + " - " + cnam +"\n");
      		}
    	}

    	write("\n");
    	return 1;
}

int
bhelp(string str)
{
  	string clan;
  	int no;

  	if(str=="emotes")
  	{
    	write("\nBARBARIAN EMOTES                                         (941010)\n"+
          "----------------\n\n"+
          "bbanger                 - scream in anger over a lost kill.        \n"+
          "bcrom                   - say CROM!, as you're impressed/surprised \n"+
          "bcry <person or string> - raise a combat cry.                      \n"+
          "bdislike <person>       - dislike somebody 		              \n"+
          "bdrool <person>         - start drooling in exitement.             \n"+
          "bfist <person>          - raise your fist towards somebody.        \n"+
          "bgaze <person>          - gaze at somebody.                        \n"+
          "bgrin                   - grin in a brutal way.                    \n"+
          "bhail <person>          - hail a fellow barbarian.                 \n"+
          "bhmpf                   - if somebody says anything against you.   \n"+
          "bhug <person>           - hug somebody the barbarian way.          \n"+
          "bimpress <person>       - impress somebody                         \n"+
          "bjoy                    - reveal how much joy you have in killing. \n"+
          "bkiss <person>          - kiss somebody the barbarian way.         \n"+
          "blaugh                  - laugh and laugh and laugh.               \n"+
          "blick                   - lick your lips in excitement.            \n"+
          "bpeer <person>          - peer at somebody.                        \n"+
          "bpray                   - pray to your mighty wargod, Crom.        \n"+
          "bpunch                  - punch someone                            \n"+
          "bshake		   - shake for something to kill              \n"+
          "bsmile                  - smile the barbarian way.                 \n"+
          "bsniff                  - sniff your armpit.                       \n"+
          "bstomp                  - stomp in the ground.                     \n"+
          "bsulk                   - sulk like a spoiled child.               \n"+
          "btrack                  - search for tracks of slayable enemies.   \n"+
	  "\n\n");
       	return 1;
  	}
  
   	if(str=="commands")
  	{
    	write("\nBARBARIAN COMMANDS\n"+
          "----------------\n\n"+
          "bblock			- Try to block someones move.             \n"+
          "bchop			- Chop someones head off.                 \n"+
          "bconvert			- Leave the herd                          \n"+
          "bheadbut			- Bonk someone in the head.               \n"+
          "bhelp <topic>		- Help files                              \n"+
          "bl				- Herd list                               \n"+
          "bscream <person> <msg>	- Scream something over distances         \n"+
	  "bslay			- Slay someone                            \n"+
          "bstab			- Stab someone                            \n"+
          "byell			- Try to scare someone with a yell.       \n"+
	  "\n\n");
    	return 1;
	}

   	if(str=="barbarians")
  	{
    	write("\nBARBARIAN HELP\n"+
          "----------------\n\n"+
          "emotes                  - bhelp emotes                       \n"+
          "clans                   - bhelp clans                        \n"+
          "commands                - bhelp commands                     \n"+
          "elder commands          - bhelp elder                        \n"+
          "levels                  - bhelp levels                       \n"+
	  "\n\n");
    	return 1;
  	}
  
  	if(str=="levels")
  	{
    	write("\nBARBARIAN LEVELS\n"+
          "----------------\n\n"+
          "newbie, puny, lousy, harmless, weak, poor, amateurish, average,  \n"+
          "known, good, well-known, brutal, feared, champion, excellent,    \n"+
          "genocidal, master, greater master, legend and guru.\n\n");
    	return 1;
  	}
 
  	if(str=="clans")
  	{
    	clan = query_clan_name(TP);
    	no = query_clan_number(TP);

    	write(clan + " Emotes\n\n");
    	if(no == 1)
    		{
      		write("eaglepride\n"+
            	"eaglehail\n"+
           	"eaglebow\n"+
            	"eagleswing\n"+
            	"\n");
      		return 1;
    		}
   	}
          
	if(str=="elder");
	{
		write("\nELDER COMMANDS\n"+
		"--------------\n\n"+
		"vote <option>      - place your vote (yes/no/blanc)\n"+
		"voteresult         - the result of the voting\n"+
		"votesubject        - what to vote about\n\n");
		if(TP->query_skill(SS_BARB_SCORE)>19)
	  write("accept             - accept a player to join the clan\n"+
		"bcheck             - check applicants and clan members\n"+
		"reject             - reject a players application to the clan\n\n");
		if(TP->query_skill(SS_BARB_SCORE)>29)
	  write("demote <player>    - demote an elder or a player\n"+
		"endvote            - end voting session\n"+
		"newvote <subject>  - new voting session\n"+
		"promote <elder>    - promote an elder\n\n");
	return 1;
	}

    	if(!strlen(str))
    	{
    		NF("Sorry, but you must pick a valid topic.\n");
      	return 0;
	}

      	NF("Sorry, but your clan leader have been too lazy to do "+
          	"anything...\n(Propably been out drinking ale instead *nudge* *nudge*)\n");
      	return 0;
}











/* *********************** leave **************************** */
int
bconvert(string str)
{
	
	NF("Convert to what?\n");
    	if (str != "to whimp") return 0;

    	if (!TP->query_prop(BARB_LEAVE))
    	{
		write("To reject being a true barbarian is to be whimpie.\nIf you are "+
	  		"a true whimp type 'bconvert to whimp' again.\n");
		TP->add_prop(BARB_LEAVE, 1);
		return 1;
    	}
    	TP->kick_out_barb();
    	return 1;
}

int
bcheck(string str)
{
  int pclan,clan,align,brute,i;
  string cname,str1,str2;
  object *players;

  if(TP->query_skill(SS_BARB_SCORE)>19 && str=="clan")
  {
    clan = query_clan_number(TP);
    cname = query_clan_name(TP);

    players = users();
    write("\n"+cname+" List\n\n");
    for (i = 0; i < sizeof(players); i++)
    {
      pclan = query_clan_number(players[i]);

      if (players[i]->query_guild_member("The Barbarian Herd") &&
         pclan == clan)
      {
         brute = query_brutelevel(players[i]);
         align = players[i]->query_align();

         if(brute == 2) str1="BRUTAL";
         else str1="WIMP";

         if(align < -550) str2="EVIL";
         else if(align > 550) str2="GOOD";
         else str2="NEUTRAL";

         write("- " + players[i]->query_name() + " " +
         players[i]->query_title() + " - " + str1 +" - " + str2 +"\n");
      }
    }

    write("\n");
    return 1;
  }
  else
  if(TP->query_skill(SS_BARB_SCORE)>29 && str=="members")
  {
    write("\nBarbarian Check List\n\n");

    for (i = 0; i < sizeof(players); i++)
    {
      if (players[i]->query_guild_member("The Barbarian Herd"))
      {
         brute = query_brutelevel(players[i]);
         align = players[i]->query_align();

         if(brute == 2) str1="BRUTAL";
         else str1="WIMP";

         if(align < -550) str2="EVIL";
         else if(align > 550) str2="GOOD";
         else str2="NEUTRAL";

         write("- " + players[i]->query_name() + " " +
         players[i]->query_title() + " - " + str1 +" - " + str2 +"\n");


      }
    }

    write("\n");
    return 1;
  }
  else
  if(TP->query_skill(SS_BARB_SCORE)>29 && str=="bracelets")
  {
    players = users();
    write("\nBracelet owners onlogged\n");
    write("------------------------\n");
    for (i = 0; i < sizeof(players); i++)
    {
      if (present("barb_brac",players[i]))
      {
         write("- " + players[i]->query_name() + " " +
         players[i]->query_title() + "\n");
      }
    }

    write("\n");
    return 1;
  }

  NF("What?\n");
  return 0;
}

/* ********************** Updating ********************** */
/* 
 * Call update_nice to update the soul in a friendly way.
 * If there are any alarms present in the soul, it waits.
 */
static void
update_nice_retry(object caller, int n)
{
    int t, rep;
    float max = 0.0;
    mixed alarms;

    if (n > 10)
    {
	caller->catch_tell("Tried 10 times! Bailing out!");
	return;
    }

    alarms = get_all_alarms();
    if (sizeof(alarms) != 0)
    {
	for (t = 0; t < sizeof(alarms); t++)
	{
	    if (alarms[t][2] > max)
		max = alarms[t][2];
	    if (alarms[t][3] != 0.0)
		rep = 1;
	}
	caller->catch_tell("Longest alarm present: " + ftoa(max) + "\n");
	if (rep)
	{
	    caller->catch_tell("Repeating alarm! Bailing out!");
	    return;
	}
	set_alarm(max + 0.5, 0.0, &update_nice_retry(caller, n + 1));
	return;
    }
    caller->catch_tell("Updating the soul.\n");
    destruct();
}

void
update_nice()
{
    int t, rep;
    float max = 0.0;
    mixed alarms = get_all_alarms();

    if (sizeof(alarms) != 0)
    {
	for (t = 0; t < sizeof(alarms); t++)
	{
	    if (alarms[t][2] > max)
		max = alarms[t][2];
	    if (alarms[t][3] != 0.0)
		rep = 1;
	}
	write("Longest alarm present: " + ftoa(max) + "\n");
	if (rep)
	{
	    write("Repeating alarm! Bailing out!");
	    return;
	}
	set_alarm(max + 0.5, 0.0, &update_nice_retry(this_player(), 0));
	return;
    }
    write("Updating the soul.\n");
    destruct();
}

