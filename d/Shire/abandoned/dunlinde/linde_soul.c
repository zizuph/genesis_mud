/* This file is /d/Shire/guild/dunlinde/linde_soul.c 
 *
 *   Intended for use by the Dunlinde in
 *   The Shire domain in Genesis.
 *   Jaypeg, June 1999
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";
#include <macros.h>
#include <formulas.h>
#include "/d/Shire/sys/defs.h"
#include "dunlinde.h"
#include <stdproperties.h>
#include <composite.h>

#define MORE(x)    this_player()->more(read_file(x, 2))

// Prototypes
void sing_song(object player, int stage);

string
get_soul_id()
{
    return "Dunlinde";
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
      "help"        :    "help",
      "lbless"      :    "lbless",
      "lcurse"      :    "lcurse",
      "ldeclare"    :    "ldeclare",
      "lfortify"    :    "lfortify",
      "lhail"       :    "lhail",
      "lstraighten" :    "lstraighten",
      "lprepare"    :    "lprepare",
      "lpity"       :    "lpity",
      "lrecall"     :    "lrecall",
      "lsong"       :    "lsong",
      "lwarn"       :    "lwarn"
    ]);
}

int
help(string str)
{
    setuid(); seteuid(getuid());
    switch (str)
    {
    case "herald":
	MORE(LINDE_HELP + "general");
	TP->catch_tell("And please report any problems you may encounter "+
	  "with the "+LINDE_GUILD_NAME+" to "+ 
	  COMPOSITE_WORDS(map(LINDE_GUILD_MASTER, capitalize)) + ".\n");
	break;
    case "herald guild":
	MORE(LINDE_HELP + "guild");
	break;
    case "dunlinde emotes": 
    case "dunlinde emotions":
	MORE(LINDE_HELP + "emotes");
	break;
    case "dunlinde spells":
	MORE(LINDE_HELP + "spells");
	break;
    case "dunlinde titles":
	MORE(LINDE_HELP + "titles");
	break;
    case "dunlinde news":
	MORE(LINDE_HELP + "news");
	break;
    default:
	return 0;
    }
    return 1;
}

int
lbless(string str)
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
    all2act("blesses",oblist," in the name of Eru Illuvatar.");
    return 1;
}

int
lcurse()
{
    write("You forcefully utter: Get thee back to thy Dark master "+
      "or I will smite thee.\n");
    all(" utters: Get thee back to thy Dark master or I will "+
      "smite thee!\n");
    return 1;
}


int
ldeclare()
{
    write("You resolutely declare: I am a servant of the Secret Fire. "+
      " You cannot pass.\n");
    say(QCTNAME(TP) + " forcefully declares: I am a servant of the "+
      "Secret Fire.  You cannot pass.\n");
    return 1;

}

int
lhail(string str)
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
    all2act("bows, hailing",oblist," in the name of Manwe Sulimo.\n");
    return 1;
}

int
lfortify(string str)
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
    all2act(" fortifies "+HIM_HER(TP)+"self against the dangers of",oblist,".");
    return 1;
}

int
lpity()
{
    write("You pity the Discord of Morgoth and the marring of Arda.\n");
    all(" pities the Discord of Morgoth and the marring of Arda.\n");
    return 1;
}

int
lprepare()
{
    write("You check your components absently, mindful of what is to come.\n");
    all(" checks "+HIS_HER(TP)+" components carefully, mindful of what "+
      "is to come.\n");
    return 1;
}

int
lrecall(string str)
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
lsong()
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
	write("Images of flowers and jewels dance on edges of your vision,"+ 
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
lwarn()
{
    write("You remind everyone that the West is still very powerful.\n");
    say(QCTNAME(TP) + " reminds you that the West is still very powerful.\n");
    return 1;
}

