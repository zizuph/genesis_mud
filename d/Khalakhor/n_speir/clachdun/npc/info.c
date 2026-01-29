/*
 * Info_npc.c
 *
 * An inertable file which contains all the "common" information
 * for a city which Npcs should know.  Such as improtant people, places
 * a General History of the area, and any other common knowledge I can 
 * think of.
 *
 * Igneous August 2004
 */

inherit "/d/Khalakhor/lib/knowledge_base";

#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"

void
my_answer(string question)
{
    switch(random(10, str2val(OB_NUM(TO))))
    {
    case 0..2:
	command("emote shrugs "+HIS_HER(TO)+" shoulders.");
	break;
    case 3..5:
	my_communicate("I have no idea what your talking about "+
	  (!TP->query_gender() ? "lad" : "lass") + ".");
	break;
    case 6:
	command("think");
	my_communicate("Sorry I can not help ye there.");
	break;
    case 7:
	my_communicate("Sorry, I have no information about "+question+".");
	break;
    case 8:
	command("scratch head");
	my_communicate("I do remember someone asking about "+question+
	  ", but I don't have a blasted idea what it means.");
	break;
    case 9:
	my_communicate("Why do ye find that so interesting?");
	my_communicate("I have never heard of such a thing.");
	break;
    }
}

void
clachdun_history()
{
    switch(random(4, str2val(OB_NUM(TO))))
    {
    case 0:
	my_communicate("Clach Dun is a mighty fortress is it not?");
	my_communicate("After the last Great War when the Humans and the " +
	  "Dwarves pushed back the Golbins Hoards back into the "+
	  "Great Waste.");
	my_communicate("We came together afterwards and constructed "+
	  "this Fort within Godsbreath Pass.");
	my_communicate("No way can any army from the Great Waste invade the "+
	  "Southlands without first passing through here.");
	my_communicate("And we be quite ready for them gobbers if they do "+
	  "ever crawl out of the Waste.");
	command("grin .");
	break;
    case 1:
	my_communicate("Want to know more about Clach Dun do ye?");
	my_communicate("Well after we drove them gobbers away, back "+
	  "to the Greate Waste.");
	my_communicate("The human and dwarven clans stayed behind here "+
	  "and built this grand fortress you see here within "+
	  "the Stonebark Moutains.");
	my_communicate("This is our first line of defense agains the hordes "+
	  "of evil things which dwel in the Waste.");
	my_communicate("Tis every clans duty to send warriors to this place "+
	  "so that they may take the Stone Warder's Oath.");
	my_communicate("An Ooath in which one puts the Duties of a Stone Warder "+
	  "above the interests of oneself and ye own Clan.");
	my_communicate("There be no Clans here in Clach Dun has been that way "+
	  "since the first Stone Warders made the Oath under the "+
	  "Banner of Kaltyn of Loren.");
	break;
    case 2:
	my_communicate("The History of this place is strange one.");
	my_communicate("The best warriors from all the Clans come here "+
	  "and make the Oath to protect the Stone Fortress above "+
	  "all else.  Even yer own Clan.");
	my_communicate("Clach Dun was built by all the Clans after the "+
	  "last Horde of Chaos was banished back the the Great "+
	  "Waste and now we sit here awaiting at the front "+
	  "lines for the next great war.");
	my_communicate("The Light Talon also has been placed within these "+
	  "here walls, part of our Oath is to protect it "+
	  "till the return of Kaltyn of Loren.");
	my_communicate("Surely he must be dead by now it has been ages since "+
	  "he was last seen within the civilized lands of "+
	  "Khalakhor.");
	break;
    case 3:
	my_communicate("Clach Dun was forged my a mix of magic and might.");
	my_communicate("The walls here can not be harmed save for the "+
	  "strongest magics.");
	my_communicate("Since this fortress was build by the Clans and "+
	  "it's walls enhanced by the Wise after the last "+
	  "Great War.");
	my_communicate("None have been able to defeat the Stone Warders "+
	  "which protect it.");
	my_communicate("You'll notice a crest on the breast plates and shields "+
	  "the guardians of Clach Dun wear.");
	my_communicate("The clenched plated fist is a symbol of our definance "+
	  "and our unity in the defence of these walls.");
	my_communicate("The blood red border is to remind of blood which "+
	  "would be split in the Southlands if the Horde "+
	  "ever breached the walls of Clach Dun.");
	my_communicate("We are The Shield of Khalakhor and must always be up to the "+
	  "task that the Oath of the Stone Warders has "+
	  "placed upon us.");
	break;
    }
}

void
clachdun_steward()
{
    switch(random(5, str2val(OB_NUM(TO))))
    {
    case 0..2:
	my_communicate("Gulnar be the Steward of Clach Dun.");
	my_communicate("He rules with a steady hand.");
	my_communicate("Must be hard to hold the responsibility "+
	  "of the front line of defense against the "+
	  "Horde of the Waste.");
	my_communicate("He seems to have a troubled look on his "+
	  "face of late.");
	my_communicate("I hope it not be anything serious.");
	break;
    case 3:
	my_communicate("That Gulnar has been acting like a "+
	  "jammy bastard of late.");
	my_communicate("Ordering the boys to lay off the ale and "+
	  "giving us extra shifts of guard duty.");
	my_communicate("It's just not right...  something must "+
	  "be bothering him or there be trouble a "+
	  "brewin'.");
	my_communicate("I bet it has something todo with this "+
	  "blasted weather.");
	break;
    case 4:
	my_communicate("Gulnar is the Steward of Clach Dun and the "+
	  "leader of the Stone Warders.");
	my_communicate("He was well known for his exploits on the "+
	  "battlefield.");
	my_communicate("They say his Pole-hammer is one that slays "+
	  "goblin kind and that he once took down an "+
	  "entire goblin divison of fourty some odd "+
	  "gobbers single handedly.");
	my_communicate("I'm sure that has been exaggerated over time.");
	command("chuckle .");
	my_communicate("Feel free to ask him about it, he does enjoy "+
	  "telling that tale.");
	break;
    }
}

void
clachdun_blademistress()
{
    switch(random(5, str2val(OB_NUM(TO))))
    {
    case 0..2:
	my_communicate("That Alasia is an odd sort.");
	my_communicate("Always around the Advisor like they "+
	  "were joined at the hip.");
	my_communicate("She sure is beautiful...   I wonder if "+
	  "all elves are look like that.");
	my_communicate("We rarely see any of the elves here in "+
	  "Clach Dun");
	break;
    case 3:
	my_communicate("Mmm...  I've heard that Alasia belongs "+
	  "some sort of warrior order.");
	my_communicate("The Cuallach Dreugan I believe was the "+
	  "name.");
	my_communicate("She sure knows how to fight too!!");
	my_communicate("Best darn defensive fighter I've seen, "+
	  "rarely does she leave you the smallest "+
	  "opening to strike at her and often when "+
	  "you do it was just a feight to break "+
	  "your guard.");
	my_communicate("By the time to notice the counter attack "+
	  "she has smacked you upside the head with "+
	  "the flat of her sabre and your sparing "+
	  "session with her is over.");
	break;
    case 4:
	my_communicate("Yeah I know that Alasia.");
	my_communicate("She's the only elf you can find here "+
	  "within the walls of Clach Dun.");
	my_communicate("Always with that F'yar fellow...  I don't "+
	  "think I've ever seen them apart from "+
	  "one another.");
	my_communicate("You'd swear they were married or something, "+
	  "but that can't be true.");
	my_communicate("Most married couples that spend the amount "+
	  "of time they do together would have killed "+
	  "one another by now.");
	command("grin .");
	my_communicate("Must have something todo about that strange "+
	  "Order she belongs to...  the Cuallach Dreugan.");
	my_communicate("I think that means Dragon Society.");
	break;
    }
}

void
clachdun_advisor()
{
    switch(random(5, str2val(OB_NUM(TO))))
    {
    case 0..2:
	my_communicate("Oh that F'yar fellow is the new 'Advisor' "+
	  "here.");
	my_communicate("Member of the Wise, a Clan on Wizards and "+
	  "Sorcerors they be.");
	my_communicate("He and that elf have only been here a few "+
	  "weeks and strange things have been "+
	  "happening ever since.");
	my_communicate("Gulnar never needed an Advisor before "+
	  "this F'yar fellow showed up.");
	command("hmm");
	my_communicate("Wonder why he was promoted to this position "+
	  "of power so swiftly.");
	my_communicate("It doesn't quite sit right with me...  tis "+
	  "strange times indeed here in Clach Dun.");
	break;
    case 3:
	my_communicate("Oh the Advisor to the Steward would "+
	  "be that F'yar fellow from the Order of "+
	  "the Wise.");
	my_communicate("He be a powerful mage that controls the "+
	  "powers of ice and light.");
	my_communicate("I've seen him waggle thoose fingers of "+
	  "his and the darkess room lights up.");
	my_communicate("And his cloak is one of the most "+
	  "interesting thing I have ever seen!!");
	my_communicate("It seems to shift and move about like "+
	  "a bloody blizzard over his shoulders.");
	command("shiver");
	break;
    case 4:
	my_communicate("Oh that F'yar be one of thoose Wise Folk.");
	my_communicate("Legend says the Wise were once a number "+
	  "of different orders of magic users that "+
	  "united during the first Great War to push "+
	  "back the tide of Chaos.");
	my_communicate("You don't see very many of them now a days.");
	my_communicate("Many common folk are none too pleased when "+
	  "they see one of them Wise come to their "+
	  "village.");
	my_communicate("They always seem to bring trouble with them "+
	  "where ever they go.");
	my_communicate("Or maybe they just go to where the trouble be?");
	command("shrug");
	my_communicate("Oh please don't mention to F'yar that I "+
	  "said thoose things...");
	my_communicate("That man gives me the willies");
	command("shiver uncontrollably");
	break;
    }
}

void
lighttalon()
{
    switch(random(4, str2val(OB_NUM(TO))))
    {
    case 0..2:
	my_communicate("The Light Talon is the Claymore of "+
	  "Kaltyn of Loren.");
	my_communicate("It is embedded within the Stone Keep and "+
	  "Warded with powerful magics so that only "+
	  "He or the Heir to his legacy can "+
	  "remove it; so says the legend.");
	break;
    case 3:
	my_communicate("I heard once a thief tried to steal "+
	  "the Claymore of Kaltyn of Loren.");
	my_communicate("Pathetic little bugger didn't get very "+
	  "far with his attempt.");
	my_communicate("Oh we was smart nuff to get past the "+
	  "guards roaming around the Stone Keep.");
	my_communicate("But the magics guarding the Light Talon "+
	  "nearly blasted him to a crisp.");
	my_communicate("The guards found him face down in a "+
	  "puddle of his own drool he was so stunned.");
	my_communicate("They say two days later he finally snapped "+
	  "out of it and found himself in the prison.");
	command("chuckle");
	break;
    }
}

void
weather()
{
    switch(random(5, str2val(OB_NUM(TO))))
    {
    case 0..2:
	my_communicate("Blasted weather has been horrible for days.");
	my_communicate("Tis almost unnatural!!");
	my_communicate("This must be a sign that foul deeds "+
	  "be brewing here in Clach Dun.");
	my_communicate("I can not wait till my shift be over so "+
	  "I can warm myself up with some nice "+
	  "warm ale!");
	break;
    case 3:
	my_communicate("I still can not believe the way the "+
	  "weather has been the last couple "+
	  "weeks.");
	my_communicate("Seems like there be a lightning storm "+
	  "everyday!");
	my_communicate("I heard some unlucky traveller was hit by "+
	  "lightning in the very streets of Clach Dun.");
	my_communicate("I swear this can not be natural... the "+
	  "odds of a storm lasting this long are "+
	  "nearly impossible!");
	break;
    case 4:
	my_communicate("Crazy weather we've been getting lately.");
	my_communicate("I'm hearing rumours that a powerful mage "+
	  "be controling it.");
	my_communicate("But our searches have come up with nothing!");
	my_communicate("If this blasted storm does not pass soon, "+
	  "my armour is gonna turn to rust!");
	break;
    }
}

void
answer_human()
{
    switch(this_object()->query_race_name())
    {
    case "human":
	switch(random(5, str2val(OB_NUM(TO))))
	{
	case 0..2:
	    my_communicate("Ye wish to know more about the humans, eh?");
	    my_communicate("Well we are divided up into many Clans and "+
	      "rule most of Khalakhor along with the Dwarven Clans.");
	    break;
	case 3:
	    my_communicate("Our Clans rule most of Khalakhor.");
	    my_communicate("Although it is rare that the Clans ever agree "+
	      "with each other.");
	    my_communicate("Only thing all the Clans can seem to agree on is "+
	      "that the walls of Clach Dun need to be protected, and thus send "+
	      "thier best warriors here to defend it.");
	    break;
	case 4:
	    my_communicate("Curious about us humans, eh?");
	    my_communicate("Not a whole lot to tell ye about us.");
	    command("shrug");
	    break;
	}
	break;
    case "dwarf":
	switch(random(5, str2val(OB_NUM(TO))))
	{
	case 0..2:
	    my_communicate("You want to know more about the humans do ye?");
	    my_communicate("They are pretty similar in alot of ways to us "+
	      "dwarves.");
	    my_communicate("They are greater in number than us dwarves and "+
	      "their Clans rule most of Khalakhor along with our Clans.");
	    break;
	case 3:
	    my_communicate("Humans usually can not stomach our good "+
	      "stout whiskey.");
	    my_communicate("Weak bellies they have.");
	    command("burp");
	    my_communicate("Oh pardon me manners.");
	    command("hiccup");
	    break;
	case 4:
	    my_communicate("I never seen many humans till I started my "+
	      "service here in Clach Dun.");
	    my_communicate("They seem like an okay bunch.");
	    break;
	}
	break;
    }
}

void
answer_elf()
{
    switch(this_object()->query_race_name())
    {
    case "human":
	switch(random(5, str2val(OB_NUM(TO))))
	{
	case 0..2:
	    my_communicate("Oh the elves!");
	    my_communicate("They are certain a rare sight around Khalakhor.");
	    my_communicate("Most of them can be found in the company of the "+
	      "remains of the Wise.");
	    my_communicate("They seem to be bonded in some service with them "+
	      "ever since their Great Sacrifice during the last war we had with "+
	      "the goblin hordes.");
	    break;
	case 3:
	    command("think");
	    my_communicate("I've only seen one elf personally, her name be "+
	      "Alasia, and she is always seen in the company of that F'yar fellow.");
	    break;
	case 4:
	    my_communicate("Most of the elves I've seen belong to their "+
	      "Cuallach Dreugan.");
	    my_communicate("That roughly translates to the Dragon Society fer "+
	      "thoose of you not from around here.");
	    my_communicate("Ye may wish to ask Alasia more about it, cuz I don't "+
	      "have the faintest idea what the Cuallach Dreugan is all about.");
	    break;
	}
	break;
    case "dwarf":
	switch(random(5, str2val(OB_NUM(TO))))
	{
	case 0..2:
	    command("sigh");
	    my_communicate("Brave and valliant warriors them Elves.");
	    my_communicate("Tis a shame they near rendered themselves extinct " +
	      "during the last war.");
	    my_communicate("Now a days you only see them in the company "+
	      "of a mage since they rarely venture from their villages "+
	      "alone.");
	    my_communicate("Except for that Alasia, she lives here with "+
	      "the Stewards Advisor.");
	    break;
	case 3:
	    my_communicate("Dem elves are a strange race.");
	    command("hiccup");
	    my_communicate("We owes them big time for thier sacrifice during "+
	      "da last war with..");
	    command("burp");
	    my_communicate("Oh excuse me.  Where was I?");
	    my_communicate("Oh yeah.. so I tolds da guy hes better leave me alone before "+
	      "I kicks his arse..."); 
	    break;
	case 4:
	    command("sratch head");
	    my_communicate("Legend says they were the first race to evolve here "+
	      "on Khalakhor.");
	    my_communicate("They once be the rulers here, but the last clash with "+
	      "thoose gobbers nearly wiped em out.");
	    my_communicate("They did save our arses, but paid a terrible price for "+
	      "our freedom, for that we are in debt to their noble race.");
	    break;
	}
	break;
    }
}

void
answer_dwarf()
{
    switch(this_object()->query_race_name())
    {
    case "human":
	switch(random(5, str2val(OB_NUM(TO))))
	{
	case 0..2:
	    my_communicate("Ahh the dwarves.");
	    my_communicate("They are a fine people, and excellent smiths!");
	    my_communicate("Along with our Clans we rule Khalakhor together with "+
	      "their clans.");
	    break;
	case 3:
	    my_communicate("Fearsome fighters they be, that show "+
	      "no fear on the battlefield.");
	    my_communicate("I bet it has something to do with the amount of "+
	      "whiskey they drink before they do battle.");
	    command("grin .");
	    break;
	case 4:
	    my_communicate("I don't know much about them personally.");
	    my_communicate("Every time I ask one about their race, they "+
	      "tell be to mind my own business, so I stopped asking.");
	    command("shrug");
	    break;
	}
	break;
    case "dwarf":
	switch(random(5, str2val(OB_NUM(TO))))
	{
	case 0..2:
	    my_communicate("My we certainly are nosey aren't we?");
	    my_communicate("We are a proud people who don't like "+
	      "strangers prying into our business.");
	    break;
	case 3:
	    my_communicate("Nuffin much to tell ye about us dwarves.");
	    command("hiccup");
	    my_communicate("Besides mining and smithing we enjoy a good "+
	      "fight!");
	    my_communicate("Oh and a good stout whiskey.");
	    command("smile drunken");
	    break;
	case 4:
	    my_communicate("We dwarves pride ourselves on our crafting ability.");
	    my_communicate("The best weapons and armours in Khalakhor are made "+
	      "by us dwarves.");
	    my_communicate("We spend alot of our time mining and searching for "+
	      "othuer materials used in smithing.");
	    my_communicate("Dere is this strange mineral we've discovered here in "+
	      "da Wastes called Cuirpidh Artan, I am sure any dwarven smith would "+
	      "pay ye handsomely fer some."); 
	    break;
	}
	break;
    }
}

void
answer_goblin()
{
    object goblin;

    if (TP->query_race_name() == "goblin")
    {
	switch(5, str2val(OB_NUM(TO)))
	{
	case 0..2:
	    my_communicate("I still do not like the idea of "+
	      "letting goblins not wearing the banner of "+
	      "the Horde within Clach Dun.");
	    my_communicate("I swear your kind here are just spies "+
	      "for the Horde");
	    my_communicate("I'll be watching ye extra closely so best not "+
	      "to try and pull anything funny!!");
	    break;
	case 3:
	    my_communicate("A few of your kind have proven themselves "+
	      "worthy of our trust.");
	    my_communicate("I would make sure you be on your best "+
	      "behavior while within these walls.");
	    my_communicate("One wrong look or outburst and I'm "+
	      "sure some fool guard will try and "+
	      "teach how to behave here.");
	    break;
	case 4:
	    my_communicate("Your kind be tolerated here if you not "+
	      "be associated with the Horde.");
	    my_communicate("If ye be travelers from a distant land "+
	      "Welcome to Clach Dun.");
	    my_communicate("If ye be here to spy on us or cause trouble...");
	    my_communicate("Turn around now and leave while you still can.");
	    break;
	}
	return;
    }
    switch(this_object()->query_race_name())
    {
    case "human":
	switch(random(5, str2val(OB_NUM(TO))))
	{
	case 0..2:
	    my_communicate("Goblins!!  They generally be a foul race.");
	    my_communicate("They smell, they lust for power and "+
	      "dominance over our Clans.");
	    my_communicate("The only good goblin I ever met...");
	    my_communicate("Was a dead one.");
	    break;
	case 3:
	    my_communicate("You can smell one a least a league away!");
	    my_communicate("They loves living in their own filth!");
	    my_communicate("If you ever get wounded badly by one; best "+
	      "check your wounds.");
	    my_communicate("They often cover their weapons with thier own "+
	      "dung, which will fester and infect the wounds.");
	    command("shiver");
	    break;
	case 4:
	    my_communicate("They live mainly in the Wastes and tis the job "+
	      "of Clach Dun to ensure that they stay there!");
	    my_communicate("After the last war with them their numbers were "+
	      "pretty decimated, but they breed like rats!");
	    my_communicate("Before ye know it a horde of them with a thousand "+
	      "warriors within the ranks are besieging the walls.");
	    break;
	}
	break;
    case "dwarf":
	switch(random(5, str2val(OB_NUM(TO))))
	{
	case 0..2:
	    my_communicate("How dare you speak of them here!");
	    my_communicate("They are the lowest form of life here on "+
	      "Khalakhor.");
	    my_communicate("I would think twice about stepping on an ant, but never "+
	      "would I think twice before putting my boot down some "+
	      "gobbers throat.");
	    break;
	case 3:
	    my_communicate("Goblins from the Horde?? Where be they?");
	    my_communicate("I can't wait till I shove me "+(sizeof(TO->query_weapon(-1))
		? TO->query_weapon(-1)[0]->short() : "fist")+" into its belly!");
	    command("grin drunkenly"); 
	    break;
	case 4:
	    my_communicate("Foul beasties they be.");
	    my_communicate("Dey be more clever than most people give em credit.");
	    my_communicate("I heard a rumour that there be gobbers from the Horde "+
	      "hidden somewhere in Clach Dun.");
	    command("laugh uproar");
	    my_communicate("Whoever made that one up obviously has been touching "+
	      "the whiskey a mite too often.");
	    break;
	}
    }
}

public void
new_answer_question(string question)
{

    question = lower_case(question);
    if (parse_command(question, TP, "[the] 'human' / 'humans'"))
    {
	answer_human();
    }
    else if (parse_command(question, TP, "[the] 'dwarf' / 'dwarves'"))
    {
	answer_dwarf();
    }
    else if (parse_command(question, TP, "[the] 'elf' / 'elves'"))
    {
	answer_elf();
    }
    else if (parse_command(question, TP, "[the] 'goblin' / 'goblins' / 'horde'"))
    {
	answer_goblin();
    }
    else if (parse_command(question, TP, "[the] 'history' / 'creation' "+
	"[of] [clach] [dun]"))
    {
	clachdun_history();
    }
    else if (parse_command(question, TP, "[the] 'ruler' / 'steward' / 'gulnar' "+
	"'stone warder' [of] [clach] [dun]"))
    {
	clachdun_steward();
    }
    else if (parse_command(question, TP, "[the] 'blademistress' / 'alasia' "+
	"'cuallach dreugan' [of] [clach] [dun]"))
    {
	clachdun_blademistress();
    }
    else if (parse_command(question, TP, "[the] 'advisor' / 'mage' / "+
	"'wise' / 'f'yar' [of] [clach] [dun]"))
    {
	clachdun_advisor();
    }
    else if (parse_command(question, TP, "[the] 'light talon' / 'stone weapon' "+
	"[of] [clach] [dun]"))
    {
	lighttalon();
    }
    else if (parse_command(question, TP, "[the] [strange] 'weather'"))
    {
	weather();
    }
    else if (TO->query_default_answer())
    {
	command("say to "+TP->query_real_name()+" "+ TO->query_default_answer());
    }
    else
	my_answer(question);
}
