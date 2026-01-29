/*
   Knight Spur.

     museum.c
   ------------

   Coded ........: 12/96
   By ...........: Kentari

   Latest update : 12/96
   By ...........: Kentari
*/

#include "/d/Krynn/solamn/hctower/spur/local.h"
#include "/d/Krynn/common/defs.h"
inherit SPURRM;

#define MCURATOR "/d/Krynn/kentari/mnstrs/curator.c"

object curator;

create_spur_room()
{

   SHORT("Museum of the Knighthood");
   LONG("This sacred place is where the memorabilia of the Knighthood " +
      "is kept. Items from long ago and paintings of some of the outdated " +
      "techniques employed by the Knights are displayed and perserved " +
      "here. As you look upon the wonders of the Knighthood, you can't " +
      "help but feel the deep history of the oldest 'Brotherhood' " +
      "the world has known. Explore the past of the Knighthood, and in " +
      "doing so, gain appreciation of this land and its people.\n");

   INSIDE;
   LIGHT;
   
   AE(ROOM + "tunnele", "up", 0);

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
    AI(({"steel equipment rack","rack","equipment rack","steel rack"}),
	 "This rack, while not the most eye-catching piece in the room, " +
	 "is definately one of the most famous. This a the rack of the " +
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
	"gifts, or at least, the best reflective or their purpose.\n");
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
	"and looking calmly and cofidently into the face of the danger. " +
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
   reset_spur_room();
}

reset_spur_room()
{
   if (!curator)
     (curator = clone_object(MCURATOR))->move_living(0,this_object());
}
