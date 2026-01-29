/* Herbgarden outside of VKeep
 * Aridor 09/95
* modified slightly for new VK by Teth Jan 97
* modified a bit more by Auberon, April 2001,
* after it was concluded that major monuments
* to wizards, particularly those who had again
* become mortal using their wizard name, were
* not really appropriate.
 */

#include "../../local.h"
#include <macros.h>
#include <ss_types.h>

inherit OUT_BASE;

inherit HERBSEARCHNEW
string *herbs = HERB_MASTER->query_herbs( ({"garden",}) );

public void
reset_vin_room()
{
    set_searched(-5);
}

public void
create_vin_room()
{
    object weapon;

    set_short("The Garden of Vingaard Keep");
    set_long("@@long_desc");

    AE(VROOM + "ws1", "southeast");

    AI("paths","You can walk on them to keep clear of the mud " +
      "in the garden.\n");
    ACI("paths",({"walk","walk on"}),"You walk through the garden " +
      "on the paths.\n");
    AI(({"bushes","plants","greenery"}),"These are the plants of " +
      "a typical garden on Ansalon.\n");
    AI("path","This specific path leads out of the garden to the " +
      "southeast.\n");
    AI("garden","A typical Ansalonian garden, with plants in " +
      "various stages of growth and decay.\n");
    AI(({"ground","grass"}),"In some places, the ground is covered " +
      "with a fine grass.\n");
    AI("walls","The walls of Vingaard Keep afford this place much " +
      "protection.\n");
    AI(({"fountain", "water fountain"}), "The large, white marble "+
      "fountain encircles a stone pedestal, into which a lance is thrust. "+
      "Two statues loom opposite each other, on either side of the "+
      "fountain. The edge of the fountain has been inscribed upon, in "+
      "what looks to be old Solamnian script.\n");
    AI(({"pool", "water"}), "The water in the pool has small ripples "+
      "in it always, yet you feel no shaking of the ground.\n");
    AI("pedestal", "The stone pedestal rises from the center of the "+
      "pool, and a sleek silver lance is thrust into the center of it.\n");
    AI("statues", "Two majestic statues stand facing each other over "+
      "the fountain in the center of the garden. You notice, at a glance, "+
      "that the statues depict two Knights of Solamnia.\n"); 
    AI("statue", "Examine which statue? The first or second?\n");
    AI("first statue", "@@teth_desc");
    AI("second statue", "@@morrigan_desc");
    AI(({"inscription", "script"}), "@@script");
    ACI(({"inscription", "script"}), ({"decipher", "read"}), "@@script");

    weapon = clone_object(VOBJ + "dragonlance");
    clone_object(SHADOWS + "lance_shadow")->shadow_me(weapon);
    weapon->set_depth(500);
    weapon->add_prop(OBJ_M_NO_GET, "The lance cannot be removed, it is "+
      "firmly lodged in the pedestal.\n");
    weapon->setup_things();
    weapon->move(TO);

    reset_room();
    seteuid(getuid(TO));
    set_up_herbs(({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
	ONE_OF(herbs) }), ({"garden","bushes","ground","grass",}), 2);
}

string
long_desc()
{
    return tod()+season()+"You have entered a small comfortable " +
    "garden within the walls of Vingaard Keep. It consists of many " +
    "bushes and other such greenery. There are a few paths in it to "+
    "walk on. To the southeast, the garden leads back to the " +
    "street. There is a fountain in the center of the garden, as well "+
    "as two statues which face each other on either side of it.\n";
}

string teth_desc()
{
    string s="This Knight is resplendant in gleaming, silver Solamnic platemail. "+
    "The visor on his great helm has been raised, revealing a solemn face "+
    "adorned by two ocean blue eyes and a flowing, grand moustache. Worn upon "+
    "his left arm is a magnificent shield, decorated with a crest of a "+
    "silver tear against a royal blue background. Clutched in his right fist "+
    "is an ornate longsword, angled towards the ground. His breastplate has "+
    "been engraved with the symbol of the Triumvirate. At the base of the "+
    "statue, a plaque ";

    /* if (TP->query_skill(SS_LANGUAGE) < 25) */
	return s + "has a few unrecognizable words painted on it.\n";
	/*
    return s + "reads 'Teth Dallyon of Ergoth, Knight of the Sword' in old "+
    "Solamnian.\n";
	*/
}

string morrigan_desc()
{
    string s = "This Knight is dressed in dark grey platemail and wears no helmet. "+
    "A great two-handed sword, with it's tip thrust into the ground, rests "+
    "in front of him, with his hands set casually on the hilt. A long, deep "+
    "crimson cape flutters behind him, decorated with a crest of a full moon "+
    "setting over a dark citadel. His expression is nonchalant; a lopsided "+
    "cynical grin plays across his lips. Wavy, black hair falls around his "+
    "shoulders, and icy blue eyes stare coolly at the opposing statue. At the "+
    "base of the statue, a plaque ";

    /* if (TP->query_skill(SS_LANGUAGE) < 25) */
	return s + "has a few unrecognizable words painted on it.\n";
	/*
    return s + "reads 'Morrigan uth Matar, Knight of the Crown' in old "+
    "Solamnian.\n";
	*/
}

string script()
{
    /* if (TP->query_skill(SS_LANGUAGE) < 41) */
	return "The script is beyond your comprehension, all you can determine "+
	"is that it is written in old Solamnian, and that the writing is too "+
    "weathered to read anymore.\n";
	/*
    return "In ages past, during times dark and troubled, the mighty gates of "+
    "Vingaard were closed. The Knighthood was perilously close to collapse "+
    "upon itself, and two Knights vanished from the land of Krynn. Their "+
    "return brought with it hope, in the form of vision. The vision called "+
    "for the reconstruction of the Knights of Solamnia, and three and nine "+
    "Knights were chosen to see this vision through. The three were to "+
    "head the Orders of the Knighthood, and they were called Kayen "+
    "Makalis of the Rose, Bayerd Brightblade of the Sword, and Ashlar "+
    "Donnelaith of the Crown. The nine served under these three, and they "+
    "were known as Carridin Whiteguard, Croft MarKenin, Danov of House Beor, "+
    "Elgarhad Anvareth, Finglas of House Haladin, Katanga Dragonbane, "+
    "Korlis Amrisha, Mathrim Rhodrune, and Ruskin di Caela. The two Knights "+
    "had fulfilled their calling, and had no place among the chosen.\n";
	*/
}


