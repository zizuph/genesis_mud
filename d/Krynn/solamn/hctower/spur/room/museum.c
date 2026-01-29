/*
   Knight Spur.

     museum.c
   ------------

   Coded ........: 12/96
   By ...........: Kentari

   Latest update : 03/16
   By ...........: Arman
*/

#include "../local.h"
#include "/d/Krynn/common/defs.h"
inherit SPURRM;

#define MCURATOR "/d/Krynn/solamn/hctower/spur/npc/curator.c"
#define SOHM_MANAGER       "/d/Krynn/guilds/sohm/lib/sohm_manager"

object curator;

create_spur_room()
{

    SHORT("Museum of the Knighthood");
    LONG("Lined with grand tapestries, this sacred room is where the memorabilia of the Knighthood "+
      "is kept. Items from long ago and paintings of some of the outdated " +
      "techniques employed by the Knights are displayed and preserved " +
      "here. As you look upon the wonders of the Knighthood, you can't " +
      "help but feel the deep history of the oldest 'Brotherhood' " +
      "the world has known. Explore the past of the Knighthood, and in " +
      "doing so, gain appreciation of this land and its people. There " +
      "is a small platinum plaque hanging on the wall.\n");

    add_prop(ROOM_M_NO_ATTACK, 1);
    INSIDE;
    LIGHT;

    AE(ROOM + "tunnel3", "up", 0);

    AI(({"torch","torches"}),
      "The torches burn brightly, their flames dancing in the air, " +
      "making shadowy figures on the walls.\n");
    AI(({"memorabilia","display"}),
      "You see multiple treasures and paintings, all of great interest.\n");
    AI(({"treasures","treasure","under cases","multiple treasures"}),
      "You see a replica of a broken dragonlance, " +
      "a prayerbook to Paladine, and various objects from the " +
      "knighthood of old, all under glass cases, and a steel " +
      "equipment rack.\n");
    AI(({"replica","dragonlance","lance","broken dragonlance","broken lance"}),
      "This lance of purest silver is a famed dragonlance, used in the " +
      "Dragon Wars during the time of Huma Dragonbane. It was, and " +
      "forever shall be a symbol for all the Knighthood stands for " +
      "and a demonstration of the favor of Paladine to those comitted " +
      "to the cause of justice and good.\n");
    AI(({"prayerbook","book","holy book","prayerbook to Paladine"}),
      "This holy book, covered in a humble silver cloth, is where " +
      "Knights would keep their clerical spells and most sacred " +
      "prayers to Paladine and his sons before the Cataclysm. A " +
      "Knight's prayerbook was one of their most valued teachers, " +
      "and were always kept with the shrines to the Patron gods.\n"); 
    AI(({"various objects","objects","objects from Knighthood of old"}),
      "Miscellaneous items adorn the cases and give flavour and " +
      "history to the Knights of Solamnia.\n");
    AI(({"glass","glass cases","cases"}),
      "These clear glass cases are held together by a silver steel " +
      "alloy, which are most likely magically strengthened for " +
      "security, and possibly Kender fingers. The glass itself is of " +
      "excellent quality and you can easily examine anything beneath " +
      "it.\n");
    AI(({"plaque","platinum plaque","small plaque"}),
      "This plaque is engraved in clear legible writing.\n");
    ACI(({"plaque", "platinum plaque","small plaque"}), ({"read"}),
      "This museum is humbly dedicated to the Knights of Solamnia by Kentari " +
      "Dragonbane, Knight of the Rose, in thanks for teaching the " +
      "true meaning of Honor.\n");
    AI(({"steel equipment rack","rack","equipment rack","steel rack"}),
      "This rack, while not the most eye-catching piece in the room, " +
      "is definitely one of the most famous. This a the rack of the " +
      "High Armoury of the Knights of Solamnia. Used to hold the " +
      "most valuable equipment of the realm, this rack (though it " +
      "is the old one, they've gotten a new one with the new keep) " +
      "is known across the realms for the treasure it once kept " +
      "within.\n");

    AI(({"paintings","painting","techniques","multiple paintings"}),
      "Paintings demonstrating: old Solamnian fighting techniques (2), " +
      "Pre-Cataclysmic clerical spells (6), and Knighting Ceremonies " +
      "are shown.\n");
    AI(({"techniques","fighting techniques","fighting","old techniques"}),
      "There are two paintings showing different ways the Knights " +
      "used to overcome there opponents. Would you like to look at " +
      "the first technique or the second technique illustrated?\n");
    AI(({"first technique","first fighting technique","first fighting"}),
      "This colorful portrait displays a Knight delivering a crushing " +
      "combative kick to their opponent. Wearing sturdy boots of " +
      "steel, Knights would train themselves to strike out with their " +
      "feet when an opening in enemy defenses became available.\n" +
      "The focus of the Combat Kick technique is now set upon striking " +   
      "with the pommel of the sword or incorporating one's weapon into " +
      "weaknesses in an enemies' defenses.\n");
    AI(({"second technique","second fighting technique","second fighting"}),
      "A sharp image of a Knight powerfully bashing their opponent with " +
      "their shield is shown. Though possible to do without a shield, " +
      "the bash is portrayed here by a Knight using a large shield with " +
      "the crest of the Triumverate upon it.\n" +
      "The Bash technique, while not specifically practiced anymore, " +
      "gives basis to the overwhelming style that Knights often " +
      "employ in their battles and was a crude, yet effective catalyst " +
      "in the development of the successful style of fighting they " +
      "use today.\n");

    AI(({"spells","clerical spells","pre-cataclysmic spells"}),
      "There are six paintings demonstrating different clerical spells " +
      "that the Knights were entrusted with by the benevolence of " +
      "Paladine and his sons before the Cataclysm shook the foundation " +
      "of the world. Would you like to look at the first, " +
      "second, third, fourth, fifth, or sixth spell shown?\n"); 	
    AI(({"first spell","first clerical spell","first clerical"}),
      "The portrait shows a Knight gripping their glowing medal of " +
      "Paladine and magically reviving wounded back to health. Through " +
      "the divinely enhanced kindness of their hearts, the Knights " +
      "were able to heal others, and themselves, from wounds and " +
      "sicknesses found from within battle and without. The ability " +
      "to revive others was perhaps the most powerful of a Knights' " +
      "gifts, or at least, the best reflective of their purpose.\n");
    AI(({"second spell","second clerical spell","second clerical"}),
      "Displaying a Knight donning mystical armour of pure magic, this " +
      "painting symbolizes how a Knight could magically fortify " +
      "themselves in battle with the protection of their deity. " +
      "Loyalty to one another wasn't just among the Knights, but " +
      "apparently included the Solamnian gods being loyal to their " +
      "followers as well.\n");
    AI(({"third spell","third clerical spell","third clerical"}),
      "This portrait presents a Knight, surrounded by dark and " +
      "intimidating foes, holding his softly glowing Solamnic medallion " +	
      "and looking calmly and confidently into the face of the danger. " +
      "By reaching deep within themselves, Knights were able to " +
      "encourage themselves into fighting the fear that grips every " +
      "warrior at one time or another, and calmly facing their " +
      "enemies with the warm glow of Paladine to strengthen them.\n");
    AI(({"fourth spell","fourth clerical spell","fourth clerical"}),
      "Portraying a Solamnic Knight holding up a powerful weapon " +
      "to the heavens as if in offering with the heavens filled with " +
      "images of dying dragons and strengthened warriors, this picture " +
      "represents a Knights ability to perceive attributes of powerful " +
      "artifacts through divination. For a brief moment, Knights could " +
      "become privy to the knowledge of the gods concerning items worth " +
      "their notice.\n");
    AI(({"fifth spell","fifth clerical spell","fifth clerical"}),
      "A bright painting, this shows a Knight making their way through " +
      "a dark passage with the soft white radiance of their Solamnic medal " +
      "to guide them. For those truly devoted, the light of Paladine " +
      "shined upon their path, literally.\n");
    AI(({"sixth spell","sixth clerical spell","sixth clerical"}),
      "This grim picture shows evil minions of Takhisis being blown to " +
      "bits by severe strikes of lighting from a large black cloud. " +
      "Perhaps the Knights' most devastating spell, they were able to " +
      "summon a mystical storm above the battlefield that would " +
      "strike-out at any and all those with evil in their hearts and " +
      "punish them accordingly. Justice was well served as the more " +
      "black one's heart was, the more severe the penalty dished out " +
      "by Paladine and his sons.\n");

    AI(({"knighting","ceremonies","knighting ceremonies"}),
      "Showing a squire in a long flowing robe, after spending a " +
      "day and night in meditation, fasting, and prayer, he is " +
      "being inducted into the Rose Order of Knights by the High " +
      "Justice, with his sponsor at his side.\n" +
      "Squires used to be able to join any order they liked, " +
      "directly from Squirehood. The Conclave has deemed it " +
      "necessary for Knights to experience all the ranks of the " +
      "Knighthood, working up from Squire, to Crown, to Sword, to Rose.\n");

    add_item(({"dusty display case","dusty case"}),
      "@@exa_display_case");
    add_item(({"burnt remains","remains of spellbook","remains of a spellbook",
      "burnt remains of a spellbook","spellbook","words of magic",
      "arcane words of magic"}),"@@exa_spellbook");
    add_cmd_item(({"burnt remains","remains of spellbook","remains of a spellbook",
      "burnt remains of a spellbook","spellbook","words of magic","burnt spellbook",
      "arcane words of magic"}), ({"study","decypher"}),"@@learn_trothdraconis");

    clone_object(SOBJ + "museum_tree")->move(TO,1);

    reset_spur_room();
}

reset_spur_room()
{
    if (!curator)
	(curator = clone_object(MCURATOR))->move_living(0,this_object());
}

string
exa_display_case()
{
    if(this_player()->query_guild_name_occ() == "School of High Magic" &&
       !SOHM_MANAGER->query_scribed_spell(this_player(),"trothdraconis"))
    {
    return "This display case is similar to the other glass cases, except " +
      "it is caked in years of dust and has clearly been neglected by the " +
      "curator. Examining the contents of the case you can see why - it " +
      "contains items of the famous war wizard Magius, companion to the " +
      "Knight of the Crown Huma Dragonbane, the heroic individual who banished " +
      "the Queen of Darkness from the realms during the Third Dragon War.\n"+
      "Examining the relics closely, you notice the burnt remains of a " +
      "spellbook, its cover torn off revealing arcane words of magic.\n";
    }

    return "This display case is similar to the other glass cases, except " +
      "it is caked in years of dust and has clearly been neglected by the " +
      "curator. Examining the contents of the case you can see why - it " +
      "contains items of the famous war wizard Magius, companion to the " +
      "Knight of the Crown Huma Dragonbane, the heroic individual who banished " +
      "the Queen of Darkness from the realms during the Third Dragon War.\n"+
      "Knowing how the knighthood currently regard magic users - with " +
      "disdain - you can understand why this display has been left unattended.\n";
}

string
exa_spellbook()
{
    if(this_player()->query_guild_name_occ() == "School of High Magic" &&
       !SOHM_MANAGER->query_scribed_spell(this_player(),"trothdraconis"))
    {
    return "An ancient spellbook of Magius! Priceless, yet frustratingly " +
       "the security of the display case - both mechanical and magical - " +
       "mean there is no chance you can obtain it. However with the cover " +
       "burnt off, you can make out arcane words of magic that you may " +
       "be able to study and decypher.\n";
    }

    return "The burnt remains of an ancient spellbook, once owned by the " +
        "war wizard companion of Huma, sits securely behind the glass of " +
        "a dusty display cabinet.\n";
}

string
learn_trothdraconis()
{

    if(this_player()->query_guild_name_occ() != "School of High Magic") 
    {
        write("You try a decypher what the arcane words of magic mean, " +
           "however all it does is give you a headache.\n");
        return "";
    } 

    if(!this_player()->query_prop("_sohm_read_magic_active")) 
    {
        write("You are not mentally focused enough to decypher the arcane words of " +
           "the burnt spellbook.\n");
        return "";
    }

    if(SOHM_MANAGER->query_scribed_spell(this_player(),"trothdraconis"))
    {
        write("You quickly scan over the arcane words of magic in the burnt " +
          "remains of the spellbook and realise you already know this " +
          "spell - a protection from dragon fear.\n");
        return "";
    }

    if(!SOHM_MANAGER->query_scribed_spell(this_player(),"trothdraconis"))
    {
    write("You read over the visible arcane words of the burnt spellbook, deciphering " +
       "that the runes describe an ancient spell of protection that makes the target " +
       "immune to dragon fear! Once comprehended, you swiftly copy the spell " +
       "'Troth Draconis' in to your spellbook.\n");
    say(QCTNAME(this_player())+ " clears away the dust of a display case and carefully " +
        "studies the burnt remains of a spellbook within, noting what " +HE(this_player())+
        " learns into " + HIS(this_player()) + " spellbook.\n");
    
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(),"trothdraconis");

        return "";
    }

    return "";
}
