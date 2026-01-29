/*
 * /d/Gondor/project/ambassador.c
 *
 * The Gondorian ambassador to Sparkle
 *
 * Etwere = Outbond (from Dorsai, Padma et al, Outbond of the Exotics)
 * et-were: Quenya
 * et-                  forth, out PREP (with ablative in LOTR) {et} (ETYM)
 * weere                bond(=promise), troth, compact, oath {wed} (ETYM)
 *
 * Olorin, December 1996
 *
 * Copyright (c) 1996 by Christian Markus
 *
 * Modification Log:
 * 
 */
#pragma strict_types

inherit "/d/Gondor/common/dunedain/npc/npc_dunadan.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define WEP1            (WEP_DIR + "lsword")
#define ARM1            (ARM_DIR + "studl")
#define OFFICE		(GONDOR_DIR + "domain_office")
#define OSG_BRIDGE      (ANO_DIR + "osgiliath/wbridge1")

/*
 * Temporary definitions until the 'say to <target>' has been added
 * to the mudlib for npcs, too.
 */
#define NEW_SAY_TO	"say to "+name
#define SAY_TO		"say"

/*
 *  Prototypes
 */

/*
 *  Global variables
 */

public void
create_dunadan()
{
    int     rnd1 = random(21),
            rnd2 = random(21);

    set_living_name("etwere");
    set_title("Envoy of Gondor");
    set_name("etwere");
    add_name(({"ambassador", "envoy", }));
    set_dunedain_house("Belecthor");
    set_race_name("human");
    set_adj("dark-haired");
    set_adj("green-eyed");
    set_long("This green-eyed and dark-haired dunadan is His Excellency, "
      + "the noble Etwere of the House of Belecthor, Envoy of the Steward "
      + "of Gondor to Sparkle. At first glance, he appears to be quite "
      + "young for the important post he is holding, but a look at his eyes "
      + "shows experience and wisdom far beyond his apparent age.\n");

    default_config_npc(55 + rnd1 + rnd2);

    set_skill(SS_WEP_SWORD, 70 + rnd1);
    set_skill(SS_2H_COMBAT, 50 + rnd2);
    set_skill(SS_PARRY,     70 + rnd1);
    set_skill(SS_DEFENCE,   80 + rnd2);
    set_skill(SS_AWARENESS, 80 + rnd1);

    set_equipment( ({ WEP1, ARM1, }) );

    set_alignment(600);

    set_chat_time(7);
    add_chat("I am the Envoy of the Steward of Gondor to Sparkle.");
    add_chat("Can I help you?"); 
    add_chat("The realm of Gondor is beautiful.");
    add_chat("Ithilien is beautiful.");
    add_chat("Rumour have it that the Dark Lord is preparing for war.");
    add_chat("Beware of orcs! They have been spotted growing in numbers.");
    add_chat("Rangers have reported that Haradrim are gathering to the Dark Tower.");

    add_cchat("Alarm!");
    add_cchat("Help! I'm being attacked by a maniac!");
    add_cchat("I will make you pay for this, you fool!");
    add_cchat("We won't give in to the enemy, killing me won't help!");
    add_cchat("You won't get away with this!");
    add_cchat("You will regret this when you are lying in chains in the "
      + "prison!");

    set_default_answer(VBFC_ME("default_answer"));
    add_ask( ({ "wizard", "wizards", "project", "projects", }),
        VBFC_ME("ask_wizard"));

    add_ask( ({"help", "for help", "about information", "information", }),
	VBFC_ME("ask_help"));
    add_ask(({"about ithilien","ithilien"}), VBFC_ME("ask_ithilien"));
    add_ask(({"osgiliath", }),    VBFC_ME("ask_osgiliath"));
    add_ask( ({ "anorien", }), 
	QCTNAME(TO) + " says: Anorien is the part of Gondor "
        + "south and west of the Anduin and north of the Misty "
        + "Mountains.\n" +
        QCTNAME(TO) + " says: Close to the river, the land is mostly fertile "
        + "farmland, while in the south are many forests.\n" +
        QCTNAME(TO) + " says: Minas Tirith and the Fields of "
	+ "Pelennor lie in Anorien, too.\n"); 
    add_ask(({"about rohan","rohan","about edoras","edoras"}),
        VBFC_ME("ask_rohan"));
    add_ask( ({ "meduseld", "golden hall", }), 
	QCTNAME(TO) + " says: Meduseld, the Golden Hall in Edoras, " +
            "is where Theoden King resides.\n" +
	QCTNAME(TO) + " says: It was built by Brego, son of Eorl, " +
            "one year before he died.\n");
    add_ask( ({ "isengard", }),   VBFC_ME("ask_isengard"));
    add_ask( ({"lossarnach", }), 
        QCTNAME(TO) + " says: Lossarnach is an area in Gondor.\n" +
	QCTNAME(TO) + " says: It comprises the mountain-valleys "
	    + "just southwest of Minas Tirith.\n" +
        QCTNAME(TO) + " says: You can reach it from the road " 
	    + "running from the Harlond to Pelargir.\n");

    add_ask( ({"gondor", "about gondor", "information about gondor", }),       
	VBFC_ME("ask_gondor"));
    add_ask( ({ "way", "the way", "about the way", "way to gondor", 
		"for way", "for the way", 
		"ship", "to go to gondor", "route", "where is gondor", }),
	VBFC_ME("ask_way"));
    add_ask(({"minas tirith", }), VBFC_ME("ask_minas_tirith"));
    add_ask(({"steward", }),      VBFC_ME("ask_steward"));
    add_ask(({"minas morgul", "morgul", }),
        VBFC_ME("ask_minas_morgul")); 
    add_ask( ({ "angmar", }),     VBFC_ME("ask_angmar"));
    add_ask(({"pelargir", "harbour", "port", "sea port", }),
        VBFC_ME("ask_pelargir"));
    add_ask( ({ "fornost", }), 
	QCTNAME(TO) + " says: Fornost was the capital of the North "
            + "Kingdom.\n" +
        QCTNAME(TO) + " says: It was captured by the Witchking of "
            + "Angmar more than one thousand years ago.\n" +
        QCTNAME(TO) + " says: It lies on the North Downs far from "
            + "Gondor in Eriador.\n");
    add_ask(({"dark lord", "enemy", "sauron", }), 
        VBFC_ME("ask_enemy"));
    add_ask( ({ "mordor", }),     VBFC_ME("ask_mordor"));
    add_ask( ({ "barad dur", "barad-dur", "dark tower", }),
	QCTNAME(TO) + " says: Barad Dur is the Dark Tower of the " +
            "Enemy in Mordor.\n" +
	QCTNAME(TO) + " says: We men of Gondor do not speak of it " +
            "without need.\n" + 
	QCTNAME(TO) + " says: None have seen it and returned to " +
            "Gondor since the Enemy returned to Mordor and took " +
            "residence there again.\n");
    add_ask(({"task", "job", "quest", "assignment", }),
        VBFC_ME("ask_task")); 
    add_ask( "quests", 
	QCTNAME(TO) + " says: I can give you no information on " +
        "quests in Gondor.\n");
    add_ask( ({ "dunedain", "houses of the dunedain", }),
        VBFC_ME("ask_dunedain")); 
    add_ask(({"rockfriends", "rock friends", }),
        VBFC_ME("ask_rockfriends"));
    add_ask(({"militia", "thornlin militia", "thornlin"}), "say In " +
        "the small town of Thornlin, a group of people have gathered " +
        "together to protect the town from invading orcs, goblins and " +
        "wolves, which seem more numerous every day.", 1);
    add_ask(({"rangers", }),      VBFC_ME("ask_rangers"));
    add_ask(({"mages", "morgul mages", "society", }),
        VBFC_ME("ask_mages"));
    add_ask( ({ "nazgul", "ringwraiths", "nine", "the nine", }), 
	VBFC_ME("ask_nazgul") );
    add_ask( ({ "guild", "guilds", }),
        VBFC_ME("ask_guilds"));
    add_ask("carastur", 
	QCTNAME(TO) + " says: Carastur is the Lord Councillor or "
        + "Pelargir.\n" +
        QCTNAME(TO) + " says: If you are looking for a job, he "
	+ "may be able to help you.\n" +
        QCTNAME(TO) + " says: You can find him in the council " 
	+ "office in the city hall of Pelargir.\n"); 
    add_ask("hunthor", 
	QCTNAME(TO) + " says: Hunthor is the Master of Advice in Minas "
        + "Tirith.\n" +
        QCTNAME(TO) + " says: If you are looking for a job, he may be able to help "
        + "you.\n" +
        QCTNAME(TO) + " says: You can find him in the Adminstration Office in the "
        + "Third Circle of Minas Tirith.\n");
    add_ask( ({ "dol amroth", }), 
	QCTNAME(TO) + " says: Dol Amroth is a city in southern Gondor, on the coast.\n");
    add_ask( ({ "rhovanion", "mirkwood", }),
	QCTNAME(TO) + " says: The lands north of Gondor and east of " +
            "the mountains are called Rhovanion.\n" +
        QCTNAME(TO) + " says: It is a wild and sparsely settled " +
            "land, with the Vales of the Anduin in the west, and " +
            "dark Mirkwood east of them.\n" +
        QCTNAME(TO) + " says: In the north lies the kingdom of the " +
            "woodelves, and Erebor, the Lonely Mountain with the " +
            "Long Lake and Esgaroth.\n" +
        QCTNAME(TO) + " says: But we in Gondor know little of the " +
            "land.\n" +
        QCTNAME(TO) + " says: Long ago there lived peoples whom we " +
            "in Gondor called the Northmen.\n" +
        QCTNAME(TO) + " says: The Northmen were descended of the " +
            "Edain, like the Numenoreans, but they did not come to " +
            "Numenor at the end of the First Age.\n" +
        QCTNAME(TO) + " says: Now, the Northmen are few in number, " +
            "and in Rhovanion, there live Easterlings, who came to " +
            "Rhovanion from the lands east of the Sea of Rhun.\n");
    add_ask( ({ "lorien", "lothlorien", }),
        QCTNAME(TO) + " says: Lorien is a charmed land.\n" +
        QCTNAME(TO) + " says: Little is known about it in Gondor, " +
            "save that elves live there.\n" +
        QCTNAME(TO) + " says: People say it is dangerous to go to " +
            "Lorien, and that it is protected by powerful forces.\n" +
        QCTNAME(TO) + " says: But no-one has come from there to " +
            "Gondor for long years.\n" +
        QCTNAME(TO) + " says: And none who travelled there have " +
            "returned.\n");
    add_ask( ({ "thranduil", }), 
	QCTNAME(TO) + " says: Thranduil is the King of the woodelves " +
	    "in northern Mirkwood.\n" +
        QCTNAME(TO) + " says: We of Gondor have little business with " +
	    "him, as his realm is far distant.\n");
    add_ask( ({ "imladris", "rivendell", }), 
	QCTNAME(TO) + " says: Rivendell or Imladris is said to be " +
	    "the home of Elrond Half-Elven.\n" +
	QCTNAME(TO) + " says: It lies just west of the High Pass over " +
	    "the Hithaeglir, the Misty Mountains, in the north of " +
	    "Anorien.\n" +
	QCTNAME(TO) + " says: But as far as I know, in this age of the " +
	    "world, no one from Minas Tirith has ever travelled thence.\n");
    add_ask( ({ "shire", "the shire", }),
        QCTNAME(TO) + " say: The Shire?\n" +
        QCTNAME(TO) + " say: What is that? I do not know of any Shire.\n");
    add_ask( ({ "fornost", "fornost erain", }), 
	QCTNAME(TO) + " say: Fornost Erain, or Norbury of the Kings, was " +
	    "one of the principal towns of the North Kingdom.\n" +
	QCTNAME(TO) + " say: It lay in a dell of the North Downs,\n" +
	QCTNAME(TO) + " say: But it has been destroyed by the servants " +
	    "of the Enemy long ago, in the war in which the North " +
	    "Kingdom came to an end.\n");	    
}

public varargs void
arm_me(int mt_equip = 0)
{
    ::arm_me(0);
    set_alarm(5.0, 0.0, do_intro);
}

public void
ask_gondor2()
{
    command("say What more can I say?");
    command("say Gondor is one of the two Realms in Exile founded by "
          + "Elendil and his sons, Isildur and Anarion.");
    command("say Gondor stretches on both sides of the great river Anduin, "
	  + "and south and east of the Ered Nimrais, the White "
	  + "Mountains.");
    command("say Many lands and peoples have acknowledged the "
	  + "authority of the heirs of Anarion of old, but the might "
	  + "of Gondor has fallen since its greatest days.");
    command("say The furthest bounds of Gondor during the reign of "
	  + "Sea-Kings included Umbar in the South, extended to "
	  + "Tharbad in the west, to Mirkwood in the north, and "
	  + "almost to the Sea of Rhun in the east.");
    command("say The capital of Gondor is Minas Tirith, the Tower "
	  + "of Guard, which once was called Minas Anor, Tower of "
	  + "the Setting Sun.");
    command("say When you come there, you can learn more about "
	  + "Gondor.");
    command("say Other cities of the realm are Minas Ithil, which "
	  + "is now called Minas Morgul, Pelargir, the sea-port "
	  + "of Gondor, and Edoras, capital of the Kingdom of "
	  + "Rohan.");
    command("say If you wish to visit Gondor, just ask me for the way.");
    command("smile happily at " + TP->query_real_name());
}

public string
ask_gondor()
{
    command("sigh");
    command("emote sings: Gondor! Gondor, between the Mountains and the Sea!");
    command("emote sings: West Wind blew there; the light upon the Silver Tree");
    command("emote sings: Fell like bright rain in gardens of the Kings of old.");
    command("emote sings: O proud walls! White towers! O winged crown and throne of gold!");
    command("emote sings: O Gondor, Gondor! Shall Men behold the Silver Tree,");
    command("emote sings: or West Wind blow again between the Mountains and the Sea?");
    command("smile");
    set_alarm(5.0, 0.0, ask_gondor2);
    return "";
}

public string
ask_ithilien()
{
    command("say Ithilien once was the garden of Gondor.");
    command("say It lies east of the Anduin, between the river and "
	  + "the Ephel Duath, the Mountains of Shadow."); 
    command("say Since the armies of the Evil One reign in Ithilien, "
	  + "no one may enter or cross the Anduin, save by leave of the "
          + "Steward.");
    command("say Travel to Minas Tirith to learn more about Ithilien "
	  + "or to obtain the leave of the Steward to go there.");
    return "";
}
 
public string
ask_osgiliath()
{
    command("say Osgiliath once was the capital of Gondor.");
    command("say But Osgiliath has fallen into ruins long ago.");
    command("say The centre of the city lies on an island in the "
	  + "river Anduin.");
    command("say When Gondor was young, the road from Minas Anor "
          + "to Minas Ithil crossed the Anduin over the bridge of "
	  + "Osgiliath.");

    if (OSG_BRIDGE->query_bridge_broken())
    {
        command("say That bridge was the only way that crossed the Anduin "
	  + "between the Falls of Rauros and the sea.");
        command("say We had a small force holding a bridge head on "
          + "the eastern bank of the Anduin.");
        command("say But in the last attack that came out of Mordor, "
          + "our troops were driven back over the bridge. They just "
          + "barely managed to destroy it, to prevent the enemy from "
          + "using it.");
    }
    else
    {
        command("say That bridge is the only way to cross the Anduin "
	  + "between the Falls of Rauros and the sea.");
        command("say We still hold the city, and we even have a small "
          + "force holding a bridge head on the east bank of the Anduin.");
    }
    return "";
}

public string
ask_rohan()
{
    command("say The Rohirrim, the Horselords, of Rohan, are the "
	  + "staunchest allies of Gondor in its fight against the "
	  + "Dark Lord.");
    command("say The Eorlingas, as the Rohirrim call themselves, "
	  + "came out of the north to assist Gondor in war more "
	  + "than five centuries ago.");
    command("say In gratitude and to strengthen the bonds of "
	  + "friendship with the people of Eorl, Cirion, then "
	  + "Steward of Gondor, gave Calenardhon to the Rohirrim "
	  + "so they could settle there.");
    command("say The Rohirrim renamed the land to Rohan, and "
	  + "ever since the times of Eorl the Young and Cirion, "
	  + "there has been friendship between Gondor and Rohan.");
    command("say Edoras is the capital of Rohan, and there in the "
	  + "Golden Hall Meduseld is the court of Theoden King, son "
	  + "of Thengel, Lord of the Mark of Rohan.");
    command("say I am acting as Envoy of the Court of Edoras here "
	  + "in Sparkle, too.");
    return "";
}

public string
ask_pelargir()
{
    command("say Pelargir is the sea-port of Gondor.");
    command("say It lies on the west bank of the Anduin just north of the "
	  + "Ethir Anduin, the Mouths of the Anduin, where the Anduin runs "
	  + "into the Sea.");
    command("say You can reach it if you take passage with Dirhavel from Sparkle.");
    return "";
}

public string
ask_minas_tirith2()
{
    command("say Minas Tirith lies on the west bank of the Anduin.");
    command("say From Pelargir, you can reach it by following the road "
	  + "running north from Pelargir through Lebennin.");
    command("say If you do not wish to use the road, you can also go by "
          + "boat upriver on the Anduin from the harbour of Pelargir to "
          + "the Harlond, the harbour of Minas Tirith.");
    return "";
}

public string
ask_minas_tirith()
{
    command("say Minas Tirith is the capital of Gondor.");
    command("say It was founded by Anarion, the younger son of Elendil, "
	  + "as Minas Anor, Tower of the Setting Sun, at the end of the "
	  + "Second Age.");
    command("say After the ruin of Osgiliath during the years of the "
	  + "Kinstrife, it became capital of Gondor and the Kings took "
	  + "residence there.");
    command("say When Minas Ithil fell to the Lord of the Ringwraiths, "
	  + "Minas Anor was renamed to Minas Tirith, Tower of the Guard.");
    set_alarm(5.0, 0.0, ask_minas_tirith2);
    return "";
}

public string
ask_minas_morgul2()
{
    command("say Long ago, before this age of the world began, the city "
	  + "was founded under the name of Minas Ithil, Tower of the "
	  + "Rising Moon, by Isildur, eldest son of Elendil.");
    command("say It was there that Isildur planted the scion of Nimloth, "
	  + "the tree that grew in the court of Armenelos on Numenor.");
    command("say But more than one thousand years ago, the city fell to "
	  + "the army of the Lord of the Ringwraiths, who know calls "
	  + "himself King of Minas Morgul.");
    command("say It was then that the city was renamed.");
    command("say But I will not speak more of it.");
    command("say The men of Gondor do not speak about the Dark Lord or "
	  + "his minions without need.");
    return "";
}

public string
ask_minas_morgul()
{
    command("shiver");
    command("say That is verily a horrible place!");
    command("say Minas Morgul, the Tower and city of Dark Sorcery is "
	  + "the home of the Ringwraiths and the residence of their "
	  + "terrible King.");
    command("say Do not go there if you value your life!");
    command("say Death is not the greatest danger awaiting the traveller in "
	  + "that place!");
    set_alarm(5.0, 0.0, ask_minas_morgul2);
    return "";
}

public string
ask_enemy()
{
    command("say The Enemy of Gondor and of all the Free Peoples is the "
	  + "Dark Lord, he who dwelleth in Barad-Dur in the land of Mordor.");
    command("say His name is Sauron, and in the Elder Days, he was but a "
	  + "Lieutenant of Morgoth.");
    command("say His most terrible servants are the nine Ringwraiths.");
    command("say But I will not speak more of this.");
    return "";
}

public string
ask_steward()
{
    command("say When the last King of Gondor, Earnur II, died without "
	  + "leaving an heir, his Steward, Mardil Voronwe, of the House "
	  + "of Hurin, ruled in his stead.");
    command("say Since that day, the Stewards have governed Gondor in "
	  + "the name of the Kings.");
    command("say The present Steward of Gondor, the twenty sixth Ruling "
	  + "Steward since Earnur II, is Denethor, son of Ecthelion.");
    return "";
}

public string
default_answer()
{
    string  name = TP->query_real_name(),
            question = query_question();

    command(SAY_TO + " I do not know what you are talking about!");

    FIX_EUID
    log_file("etwere", CAP(name) + ": " + question + " (" + ctime(time()) + ").\n");
    return "";
}

public string
ask_wizard()
{
    command("point plaque");
    command("say Please read the plaque!");

    return "";
}

public string
ask_help()
{
    string  name = TP->query_real_name();

    command(SAY_TO + " Help? You want help with what?");
    command(SAY_TO + " Perhaps you wish some information about Gondor?");
    command(SAY_TO + " If so, then ask me about it.");
    return "";
}

public string
ask_task()
{
    string name = TP->query_real_name(),
           q = query_question();

    command("peer " + name);
    command("say You are looking for " + LANG_ADDART(q) + "?");
    command("say I cannot help you with that, but why don't you visit "
	  + "Carastur in Pelargir and Hunthor in Minas Tirith?");
    return "";
}

public string
ask_dunedain()
{
    command("say The Dunedain are the descendants of the Numenoreans who "
	  + "came to Middle Earth in the Second Age of the Sun.");
    command("say The Dunedain, in the following of Elendil, founded the two "
	  + "Realms in Exile, Gondor and Arnor.");
    command("say Today there remain few true Dunedain, even in Gondor, and "
	  + "Arnor was destroyed centuries ago.");
    command("say If you visit Pelargir, you can find the Houses of the " 
      + "Dunedain. There a remnant of the Men of the West preserve the "
      + "history of their people.");
    return "";
}

public string
ask_rockfriends()
{
    command("say The Rockfriends are a group of Durin's People, the Dwarves, "
	  + "who live in the Blue Mountains, the Ered Luin, close to the "
	  + "Greyhavens in the west of Eriador.");
    return "";
}

public string
ask_rangers()
{
    command("say The Rangers of the Westlands fight together with the "
	  + "soldiers of Gondor against the minions of the Enemy whereever "
	  + "they find them.");
    command("say But the rangers are not soldiers themselves.");
    command("say They fight less openly and more stealthily than soldiers.");
    command("say Little is known about them among strangers.");
    command("say If you wish to learn more about them, you will have to "
	  + "find some of their number and talk to them.");
    return "";
}

public string
ask_mages()
{
    command("say The mages of the Society of Morgul Mages serve the Dark Lord.");
    command("say The nine Ringwraiths are the leaders of the Society, and the "
	  + "King of Minas Morgul is the head of their order.");
    command("say The Dark Lord has bestowed powers onto them by which they "
	  + "can instill fear and terror in the hearts of their opponents.");
    command("say But the cost they have to pay for these powers is still more "
	  + "terrible.");
    command("say No living creature can belong to the Society.");
    command("say But I will say no more about them.");
    return "";
}

public string
ask_angmar()
{
    command("say Angmar? That is a name out of the tales of history.");
    command("say More than a thousand years ago, there was a realm called " +
	    "Angmar in the north of Eriador.");
    command("say It was rules by the Witchking of Angmar, and was in " + 
	    "constant war with the dunedain kingdoms of the North.");
    command("say But that was long ago, and the realms of Angmar has " +
	    "in a terrible battle fought in 1975, together with what " +
	    "remained of the dunedain of Arnor.");
    command("say Since then, only Gondor has remained of the Realms in " +
	    "Exile.");
    return "";
}

public string
ask_nazgul()
{
    command("emote shivers at the thought.");
    command("say The Nine are the most powerful servants of the Enemy.");
    command("say He controls them through the power of their Rings, " +
	    "which He forged more than an age ago.");
    command("say The Ringwraiths are terrible to behold and even the " +
	    "orcs who serve Him fear them.");
    command("say The Lord of the Nazgul, who of old was the Witchking " +
	    "of Angmar dwells in Minas Morgul.");
    command("say But let us not speak more of this.");

    return "";
}

public string
ask_guilds()
{
    command("say These are the guilds you can find in the domain Gondor:");
    command("say Living hidden in the Wilderness live the Rangers of "
	  + "the Westlands.");
    command("say In Minas Morgul, the city of the Ringwraiths, you can find "
	  + "the Society of Morgul Mages.");
    command("say In Minas Tirith, there are the Houses of the Dunedain.");
    command("say Close to Mithlond, in the far west of Eriador, in the Blue "
	  + "Mountains the Dwarves calling themselves the Rockfriends have "
	  + "their home.");
    command("say In the small town of Thornlin, a group of people have " +
        "gathered together to protect the town from invading orcs, goblins " +
        "and wolves, which seem more numerous every day.");
    return "";
}

public string
ask_mordor()
{
    command("shiver");
    command("say Mordor, the Black Land, is the land of the Enemy.");
    command("say It lies east of Gondor, beyond the Mountains of "
        + "Shadow.");
    command("say No-one can enter there unless he be a servant of "
        + "the Enemy, as all ways leading into Mordor are well "
        + "guarded.");
    command("say In Mordor stands the tower Barad-Dur, the fortress "
        + "of the Enemy, but since his return, none have seen it.");
    command("say In Mordor is also Orodruin, the Fiery Mountain.");
    return "";
}

public string
ask_isengard()
{
    command("say Isengard was one of the mightiest fortresses of "
        + "Gondor.");
    command("say It lies in a valley north of the Gap of Rohan.");
    command("say Alas, we were forced to abandon the fortress, as "
        + "Gondor has grown too weak in her wars with the Enemy to "
        + "be able to garrison a fortress so far in the west of the "
        + "realm.");
    command("say Beren, the nineteenth Ruling Steward of Gondor, "
        + "gave Isengard and the tower Orthanc to one of the Wise.");
    command("say Saruman is his name.");
    command("say He is now holding the fortress by leave and "
        + "command of the Steward, in exchange for his help should "
        + "Gondor require it.");
    
    return "";
}
    
public string
ask_way()
{
    command("say You want to go to Gondor?");
    command("smile happily at " + TP->query_real_name());
    command("say Just go to the docks here in Sparkle.");
    command("say Look for Dirhavel the Seafarer and his ship.");
    command("say I believe he usually lands at berth 2.");
    command("say Dirhavel travels from Sparkle to Pelargir, the " +
	    "seaport of Gondor.");
    command("say Or you can take the Circle Line, which departs " +
	    "from berth 4.");
    command("say It is a little slow and will stop at the Grey " +
	    "Havens first, but from there it goes to Pelargir, too.");
    return "";
}

public void
init_living()
{
    ::init_living();

    if (TP->query_met(query_name()))
	return;
    if (strlen(TP->query_dunedain_house()))
    {
	set_alarm(2.0, 0.0, &command("wellmet " + TP->query_real_name()));
    }
}

public void
emote_hook(string emote, object actor, string adverb = 0)
{
    if (!interactive(actor))
	return;

    switch (emote)
    {
    case "smile":
	set_alarm(2.0, 0.0, &command("smile at " + 
				     actor->query_real_name()));
	break;
    case "wave":
	set_alarm(2.0, 0.0, &command("farewell " + 
				     actor->query_real_name()));
	break;
    case "farewell":
	set_alarm(2.0, 0.0, &command("wave goodbye at " + 
				     actor->query_real_name()));
	break;
    case "sigh":
	set_alarm(2.0, 0.0, &command("comfort " +
				     actor->query_real_name()));
	break;
    }
}
