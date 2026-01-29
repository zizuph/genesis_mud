inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include <money.h>
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("jomo");
    add_name("retired sea captain");
    add_name("master of advice");
    add_name("retired captain");
    add_name("sea captain");
    add_name("captain");
    add_name("master");
    add_name("retired pirate");
    add_name("pirate");
    set_race_name("human");
    set_adj("knowledgeable");
    add_adj("friendly");
    set_short("retired pirate");
    set_long("This untrustworthy-looking individual looks surprisingly like "+
      "the stereotypical pirate, so complete is his attire that you can't "+
      "help but wonder if he really is a pirate.\n");
    set_stats(({75,85,80,70,70,80}));
    set_alignment(50);
    set_skill(SS_UNARM_COMBAT,90);
    set_skill(SS_BLIND_COMBAT,90);
    set_skill(SS_DEFENCE,90);
    set_skill(SS_AWARENESS,60);
    set_act_time(6);
    add_act("wink");
    add_act("grin happily");
    add_act("say It be a fine day fer sailin, mate.");
    add_act("dance");
    add_act("emote dances a jig.");
    add_act("bow all");
    add_act("shake all");
    add_act(({"burp","say Pardon me."}));
    add_act("stretch");
    add_act("say I'm thee most knowledgeable mate in these here parts.");
    add_act("say I betcha I can answer any question!");
    set_cact_time(3);
    add_cact("scream");
    add_cact("shout Bloody sea storms! I'm under attack!");
    add_cact("emote looks real angry!");
    add_speak("I'm tellin ya matey, I am thee master of advice in these "+
      "here parts. Go ahead, ask me anything.\n");
    set_title("the Retired Sea Captain, and Master of Advice");
    set_knight_prestige(-1);
    add_prop(LIVE_I_NO_CORPSE,1);
    set_default_answer("The retired pirate says: Aye mate, that ain't "+
      "worth answering.\n");
    add_ask(({"seahawk"}),"The retired pirate says: She's the grandest "+
      "ship that ever sailed the Kaladian Sea...such a pity that she can't "+
      "roam anymore. Rumours have it that the lower portions of the ship "+
      "are still inhabited...but that'd be silly. Who'd wanna live on a docked "+
      "boat?\n");
    add_ask(({"eban"}),"The retired pirate says: Hmm, that'd be the "+
      "scraggly little whelp wanderin the streets, I betcha.\n");
    add_ask(({"delbin"}),"The retired pirate says: Ahh...the guardsman, "+
      "I think he's lookin for his knife, why don't ya give him a hand?\n");
    add_ask(({"beer"}),"The retired pirate says: Aye mate! I loves my "+
      "beer! I usually drop by the Liquid Booty for some good ol sea dog "+
      "liquor. When i'm a lookin for a real drink, I go over to the Halfing "+
      "Brewery...best damn beer I ever tasted!\n");
    add_ask(({"warehouse","warehouses"}),"The retired pirate says: They're "+
      "all guarded by the militiamen. But they're all greedy folks, and "+
      "aren't too reliable...if ya get my meanin.\n");
    add_ask(({"thanar"}),"The retired pirate spits on the ground in disgust.\n"+
      "The retired pirate says: Don't be askin me anymore question about "+
      "that damned lot!\n");
    add_ask(({"regis"}),"The retired pirate says: That'd be the manager of the "+
      "ol brewery, fattest damn halfing I've ever seen.\n");
    add_ask(({"entreri"}),"The retired pirate says: Hmm...last I heard, "+
      "he was head of the Trading Company, up in the city.\n");
    add_ask(({"kabal","city"}),"The retired pirate says: Are ye daft?!? "+
      "What city do ye think yer in?\n");
    add_ask(({"kalad"}),"The retired pirate says: That's this land, of "+
      "course!\n");
    add_ask(({"trading company","company"}),"The retired pirate says: Be "+
      "careful around them, mates. They don't take kindly ta overly curious "+
      "tourists...if ya get my meanin.\n");
    add_ask(({"anything"}),"The retired pirate says: Why don'y ya ask me "+
      "somethin more specific?\n");
    add_ask(({"shipwright"}),"The retired pirate says: Yes, that'd be "+
      "ol Bassil, some say he's over five hunnerd years old! Oh yeah, I "+
      "think he's needin some help, what with that ship he's been workin on.\n");
    add_ask(({"quest"}),"The retired pirate says: Figure that out fer "+
      "yerself!\n");
    add_ask(({"ledger"}),"The retired pirate says: Hmm, what about it?\n");
    add_ask(({"key"}),"The retired pirate says: That's what you use to "+
      "open locked doors.\n");
    add_ask(({"ship","ships"}),"The retired pirate says: Eh? You mean the "+
      "Seahawk?\n");
    add_ask(({"doors","door"}),"The retired pirate says: Hmm...Aren't "+
      "those things that keep people in, or out of some place?\n");
    add_ask(({"prisoner"}),"The retired pirate says: I hear rumours of "+
      "one in the Seahawk...\n");
    add_ask(({"tar"}),"The retired pirate says: I believe there be a shop that "+
      "sells some of the black, gooey stuff, right here in the port.\n");
    add_ask(({"sail","sails"}),"The retired pirate says: Aye, that's what ships "+
      "use to move along the sea, unless of course, ye have rowers. If ye're "+
      "interested, there be a sailmaker in these here parts.\n");
    add_ask(({"task","assignment"}),"The retired pirate says: Well now..."+
      "thar be many different things ta do here in this port...it might "+
      "do ye some good if ye asked lotsa questions to tha peoples ye meet, "+
      "and of course, if ye just speak wit em.\n");
    add_ask(({"sea"}),"The retired pirate says: Its that big blue thing "+
      "out yonder.\n"+
      "The retired pirate waves his hand vaguely to the south.\n");
    add_ask(({"brewery"}),"The retired pirate says: They have good beer!\n");
    add_ask(({"slaves","slave"}),"The retired pirate says: Aye mate, there "+
      "be a bunch of them up in the Caravan District.\n");
    add_ask(({"district","districts"}),"The retired pirate says: Hmm, there be "+
      "six of them in this here city.\n");
    add_ask(({"bloody steel axe"}),"The retired pirate says: Aye! I don't knowa "+
      "thing about that wepun. Why don't ya ask ol Gurden the dwarf up in "+
      "tha mountains.\n");
    add_ask(({"gurden"}),"The retired pirate says: He be yer best bet "+
      "fer findin info on the bloody steel axe.\n");
    add_ask(({"horace"}),"The retire pirate says: Ack! Don't be talkin "+
      "bout him!\n");
    add_ask(({"mountains","mountain","hespyre mountains"}),"The retired "+
      "pirate says: Why, there be some mighty large mountains just north "+
      "of this here city.\n");
    set_alarm(1.0,0.0,"my_stuff");
}
void
my_stuff()
{
    object item;
    seteuid(getuid(TO));
    item = clone_object("/d/Kalad/common/port/obj/eye_patch");
    item -> move(TO);
    command("grin happily");
    MONEY_MAKE_GC(random(3))->move(TO,1);
}
do_die(object killer)
{
    object corpse;
    if(query_hp() > 0) return;
    corpse = clone_object("/d/Kalad/common/port/obj/jomocorpse");
    corpse -> move(environment(TO));
    ::do_die(killer);
}
