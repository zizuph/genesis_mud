/* This file is /d/Shire/herald/herald_soul.c 
 *
 *   Intended for use by the Heralds of the Valar in
 *   The Shire domain in Genesis.
 *   Apologies to Elessar of Gondor for shamelessly stealing
 *   his rangersoul. *grin*
 *
 *   Dunstable, March 26, 1995
 *
 *
 *   Some minor updates, and cleaned up the soul.
 *   Igneous, Feb 1998
 *
 *   hgather added so Heralds can collect stones anywhere. Indoors 
 *   they will gather less stones. Concept borrowed from Kender, and
 *   a big thanks to Gwyneth!!
 *   -- Finwe, May 2004
 */

#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";
#include <macros.h>
#include <formulas.h>
#include "/d/Shire/sys/defs.h"
#include "herald.h"
#include <stdproperties.h>
#include <composite.h>

#define MORE(x)    this_player()->more(read_file(x, 2))
#define SHIRE_ROCKS_FOUND   "_shire_rocks_found"


// Prototypes
void sing_song(object player, int stage);
void do_first(object player);
void do_second(object player);
void do_third(object player);
void do_fourth(object player);

string
get_soul_id()
{
    return "Heralds of the Valar";
}

int
query_cmd_soul()
{
    return 1;
}

mapping
query_cmdlist()
{
    setuid();
    seteuid(getuid());

    return ([
      "help"        :   "help",
      "hbless"      :   "hbless",
      "hbattle"     :   "hbattle",
      "hconcern"    :   "hconcern",
      "hconsider"   :   "hconsider",
      "hcurse"      :   "hcurse",
      "hdeclare"    :   "hdeclare",
      "hfortify"    :   "hfortify",
      "hgather"     :   "hgather",
      "hhail"       :   "hhail",
      "hstraighten" :   "hstraighten",
      "hprepare"    :   "hprepare",
      "hpity"       :   "hpity",
      "hrecall"     :   "hrecall",
      "hsong"       :   "hsong",
      "htrace"      :   "htrace",
      "hwarn"       :   "hwarn",
      "hworship"    :   "hworship"
    ]);
}

int
help(string str)
{
    setuid(); seteuid(getuid());
    switch (str)
    {
    case "herald":
	MORE(HERALD_HELP + "general");
	TP->catch_tell("And please report any problems you may encounter "+
	  "with the "+HERALD_GUILD_NAME+" to "+ 
	  COMPOSITE_WORDS(map(HERALD_GUILD_MASTER, capitalize)) + ".\n");
	break;
    case "herald guild":
	MORE(HERALD_HELP + "guild");
	break;
    case "herald emotes": 
    case "herald emotions":
	MORE(HERALD_HELP + "emotes");
	break;
    case "herald spells":
	MORE(HERALD_HELP + "spells");
	break;
    case "herald titles":
	MORE(HERALD_HELP + "titles");
	break;
    case "herald news":
	MORE(HERALD_HELP + "news");
	break;
    default:
	return 0;
    }
    return 1;
}

int
hbattle(string str)
{
    write("You prepare for battle, calling upon Orome for guidance.\n");
    all(" calls upon Orome for aid in battle.");
    return 1; 
}

int
hbless(string str)
{
    object *oblist;

    if (!strlen(str)) /* no string supplied */
    {
	    write("You bless everyone in the name of Eru Illuvatar.\n");
	    all(" blesses everyone in the name of Eru Illuvatar.");
	    return 1;
    }
    
    oblist = parse_this(str, "[the] %l");
    
    if (!sizeof(oblist))
    {
	    NF("Bless whom?\n");
	    return 0;
    }

    actor("You bless",oblist," in the name of Eru Illuvatar.");
    target(" blesses you in the name of Eru Illuvatar.",oblist);
    all2act(" blesses",oblist," in the name of Eru Illuvatar.");
    return 1;
}

int
hconcern(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	    write("You express concern for the fate of Middle Earth.\n");
    	all(" expresses "+HIS_HER(TP)+" concern for the fate of Middle Earth.");
	    return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
	    NF("Be concerned for whom?\n");
    	return 0;
    }
    
    actor("You show concern for",oblist);
    target(" expresses "+HIS_HER(TP)+" concern for your safety.",oblist);
    all2act(" shows concern for the safety of",oblist,".");
    return 1;
}

int
hconsider(string str)
{
    object *oblist;

    if (!strlen(str)) /* no string supplied */
    {
	    write("You halt suddenly, uncertain of your next action.\n");
    	all(" halts suddenly, considering "+HIS_HER(TP)+" next action.");
	    return 1;
    }

    oblist = parse_this(str, "[the] %l");
    
    if (!sizeof(oblist))
    {
	    NF("Consider whom?\n");
    	return 0;
    }
    
    actor("You consider",oblist," carefully, looking for signs of evil.");
    target(" considers you carefully, looking for something.",oblist);
    all2act("  considers",oblist," carefully, looking for something within.");
    return 1;
}


int
hcurse(string str)
{
    object *oblist;
    if(!strlen(str))
    {
        write("You forcefully utter: Get thee back to thy dark master "+
            "or I will smite thee.\n");
        all(" utters: Get thee back to thy dark master or I will "+
            "smite thee!\n");
        return 1;
    }
        oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
	    NF("Curse whom?\n");
    	return 0;
    }

    actor("You forcefully utter to",oblist,": Get thee back to thy " +
        "dark master or I shall smite thee!");
    target(" forcefully utters to you: Get thee back to thy " +
        "dark master or I shall smite thee!",oblist);
    all2act(" forcefully utters to",oblist,": Get thee back to " +
        "thy dark master or I shall smite thee!");
    return 1;
}


int
hdeclare(string str)
{
    object *oblist;
    if (!strlen(str))
    {
        write("You resolutely declare: I am a servant of the Secret " +
            "Fire. You cannot pass!\n");
        say(QCTNAME(TP) + " forcefully declares: I am a servant of the " +
            "Secret Fire. You cannot pass!\n");
        return 1;
    }
        oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
	    NF("Declare to whom?\n");
    	return 0;
    }

    actor("You resolutely declare to",oblist,": I am a servant of " +
        "the Secret Fire. You cannot pass!");
    target(" resolutely declares to you: I am a servant of the " +
        "Secret Fire. You cannot pass!",oblist);
    all2act(" resolutely declares to",oblist,": I am a servant " +
        "of the Secret Fire. You cannot pass!");
    return 1;

}

int
hhail(string str)
{
    object *oblist;

    if (!strlen(str)) /* no string supplied */
    {
	write("You hail everyone in the name of Manwe Sulimo.\n");
	all(" bows, hailing everyone in the name of Manwe Sulimo.");
	return 1;
    }
    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist))
    {
	NF("Bless whom?\n");
	return 0;
    }
    actor("You hail",oblist," in the name of Manwe Sulimo.");
    target(" bows, hailing you in the name of Manwe Sulimo.",oblist);
    all2act(" bows, hailing",oblist," in the name of Manwe Sulimo.\n");
    return 1;
}

int
hfortify(string str)
{
    object *oblist;

    if (!strlen(str)) /* no string supplied */
    {
	write("You fortify yourself against the danger yet to come.\n");
	all(" fortifies "+HIM_HER(TP)+"self against the danger yet to come.");
	return 1;
    }
    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist))
    {
	NF("Fortify against whom?\n");
	return 0;
    }
    actor("You fortify yourself against the dangers of",oblist);
    target(" fortifies "+HIM_HER(TP)+"self against you.",oblist);
    all2act("  fortifies "+HIM_HER(TP)+"self against the dangers of",oblist,".");
    return 1;
}

int
hgather(string str)
{
    object pebble, collector;
    int collected, t;
    collector = this_player();
    t = time();

    /* Query the prop that is set in the room when pebbles are collected. */
    collected = (environment(collector)->query_prop(SHIRE_ROCKS_FOUND));

    if ((str == "rock") || (str == "rocks")) 
    {
        if (collected > (t - 600) && (collected != 0))
        {
            notify_fail("You didn't find any rocks.\n");
            return 0;
        }

        /* Only allow mass collecting in outside rooms. */
        if (environment(collector)->query_prop(ROOM_I_INSIDE))
        {
            setuid();
            seteuid(getuid());
            pebble = clone_object(COMMON_OBJ + "rock");
            pebble->set_heap_size();
            pebble->move(collector);

            write("You find some rocks and pick them up.\n");

            /* Add prop to the room to keep track of how     */
            /* many pebbles have been collected in the room. */
            environment(collector)->add_prop(SHIRE_ROCKS_FOUND, t);
            return 1;
        }

        /* Clone the pebbles and give the message. */
        setuid();
        seteuid(getuid());
        pebble = clone_object(COMMON_OBJ + "rock");
        pebble->set_heap_size(7);
        pebble->move(collector);

        write("You find some rocks and pick them up.\n");

        /* Add prop to the room to keep track of how     */
        /* many rocks have been collected in the room. */
        environment(collector)->add_prop(SHIRE_ROCKS_FOUND, t);
        return 1;
    }

    notify_fail("Gather what?\n");
    return 0;
}


int
hpity()
{
    write("You pity the Discord of Morgoth and the marring of Arda.\n");
    all(" pities the Discord of Morgoth and the marring of Arda.\n");
    return 1;
}

int
hprepare()
{
    write("You check your components absently, mindful of what is to come.\n");
    all(" checks "+HIS_HER(TP)+" components carefully, mindful of what "+
      "is to come.\n");
    return 1;
}

int
hrecall(string str)
{
    if (!strlen(str))
    {
	write("Recall what? Possible topics are:\n"+
	  "light or lamps, majesty, Manwe or Manwe Sulimo, "+
	  "beauty, Varda or Elbereth, kindness, Ulmo, or sea.\n");
	return 1;
    }

    if (str == "light" || str == "lamps")
    {
	write("You sigh, recalling the beauty of the lamps of Valinor.\n");
	say(QCTNAME(TP) + " sighs while recalling the beauty of the lamps of "+
	  "Valinor and the Light there.\n");
	return 1;
    }

    if (str == "majesty" || str == "manwe" || str == "manwe sulimo")
    {
	write("You recall the majesty and splendor of Manwe Sulimo, "+
	  "Lord of the West.\n");
	say(QCTNAME(TP) + " recalls with joy the majesty and splendor of "+
	  "Manwe Sulimo, Lord of the West.\n");
	return 1;
    }

    if (str == "beauty" || str == "varda" || str == "elbereth")
    {
	write("You smile whilst recalling the beauty of Varda, Queen of the "+
	  "stars.\n");
	say(QCTNAME(TP)+" smiles while recalling the beauty of Varda, Queen "+
	  "of the stars.\n");
	return 1;
    }

    if (str == "kindness" || str == "ulmo" || str == "sea")
    {
	write("You recall the kindness of Ulmo, King of the Sea, who has "+
	  "saved Middle Earth many times from Darkness.\n");
	say(QCTNAME(TP)+" recalls the kindness of Ulmo, King of the Sea.\n");
	return 1;
    }
    write("You don't know much about "+str+" so you decide not to speak about it.\n");
    return 1;
}

int
hsong()
{
    if (TP->query_prop("_live_i_am_singing"))
    {
	NF("But you are already in a middle of a song.\n");
	return 0;
    }
    TP->add_prop("_live_i_am_singing", 1);
    write("You compose yourself and prepare to sing a holy song.\n");
    say(QCTNAME(TP)+ " raises "+HIS_HER(TP)+" eyes to the heavens and "+
      " begins to sing.\n",TP);
    set_alarm(5.0,0.0, &sing_song(TP, 1));
    return 1;
}

void
sing_song(object player, int stage)
{
    float time;

    set_this_player(player);
    switch (stage)
    {
    case 1:
	write("Images of flowers and jewels dance on edges of your vision, "+ 
	  "shimmering in some whiter-than-white light, strong and powerful.\n");
	say(QCTNAME(TP)+ " sings on, and images of flowers and jewels dance "+
	  "before you, just out of reach.\n",TP);
	time = 2.5;
	break;
    case 2:
	write("Two tall, slender trees appear, glowing in silver and gold.\n");
	say("As "+HE_SHE(TP)+" sings on, two tall, slender trees appear, "+
	  "glowing with silver and gold auras.\n",TP);
	time = 3.5;
	break;
    case 3:
	write("Starlight falls on a mountain pass, glittering upon the walls of a "+
	  "silver city.\n");
	say("As the holy song continues, you see starlight falling on a mountain pass, "+
	  "glittering upon the walls of a silver city.\n",TP);
	time = 2.5;
	break;
    case 4:
	write("Swanlike ships glide up to a city of pearl, the sunlight "+
	  "flashing off their sails as a warm flame.\n");
	say("You see swan-ships gliding up to a pearl-city, sunlight flashing off "+
	  "their sails as a warm flame.\n",TP);
	time = 1.0;
	break;
    default:
	write("Slowly, you cease your song, and the images disappear.\n"+
	  "You feel the world grow dim, and then return to normal.\n");
	say("Slowly, "+QCTNAME(TP)+" drifts to an end, and the images wink out.\n"+
	  "You feel the world grow dim, then return to normal.\n",TP);
	TP->remove_prop("_live_i_am_singing");
	return;
    }
    set_alarm(time, 0.0, &sing_song(player, ++stage));
}

int
hstraighten()
{
    write("You straighten your flawless flowing white robe.\n");
    say(QCTNAME(TP) + " straightens "+HIS_HER(TP)+" flawless flowing "+
      "white robe.\n");
    return 1;
}

int
htrace()
{
    write("You reverently trace your fingers across your leather-bound prayer book.\n");
    say(QCTNAME(TP) + " reverently traces "+HIS_HER(TP)+" fingers across "+
      HIS_HER(TP) + " leather-bound prayer book.\n");
    return 1;
}

int
hwarn()
{
    write("You remind everyone that the West is still very powerful.\n");
    say(QCTNAME(TP) + " reminds you that the West is still very powerful.\n");
    return 1;
}

int
hworship()
{
    if (environment(TP)->query_prop(ROOM_I_INSIDE))
    {
	write("Worship to Illuvatar must be done out of doors.\n");
	return 1;
    }

    write("You fall on your knees in reverence to Eru Illuvatar.\n");
    say(QCTNAME(TP)+ " falls on "+HIS_HER(TP)+" knees in reverence.\n",TP);
    set_alarm(5.0,0.0, &do_first(TP));
    return 1;
}

void
do_first(object player)
{
    player->catch_tell("You pray to the One.\n");
    tell_room(ENV(player), QCTNAME(player)+ " mumbles a prayer to the "+
      "One.\n", ({player}));
    set_alarm(2.0,0.0, &do_second(player));
}

void
do_second(object player)
{
    object acorn;

    FIXEUID;

    acorn = clone_object(HERALD_DIR + "acorn");
    acorn->move(environment(player),1);

    player->catch_tell("You place an acorn carefully on the ground.\n");
    tell_room(ENV(player), QCTNAME(player)+ " gingerly puts an acorn on "+
      "the ground.\n", ({player}));
    set_alarm(0.5,0.0,&do_third(player));
}

void
do_third(object player)
{
    player->catch_tell("You look upwards to the sky while lighting the acorn.\n");
    tell_room(ENV(player), QCTNAME(player)+ " looks at the sky while "+
      "lighting the acorn.\n", ({player}));
    set_alarm(1.0, 0.0, &do_fourth(player));
}

void
do_fourth(object player)
{
    object acorn;
    acorn = present("acorn",environment(TP));
    acorn->remove_object();
    tell_room(ENV(player),"The acorn burns quickly, releasing pure white "+
      "smoke which soon rises high into the air. \nThe acorn crumbles "+
      "into ashes, which disperse with a sudden breeze.\n");
}
