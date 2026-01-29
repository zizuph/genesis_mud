/*
 * treasure.c
 * By Skippern
 */
#pragma strict_types

#include "../erech.h"

//inherit "/d/Gondor/common/lib/area_room";
//inherit "/d/Gondor/std/room";

inherit E_STD + "path.c";
inherit "/lib/unique.c";

#include <money.h>
#include <stdproperties.h>

#include "../lib/gwaedhil.h"

#include TERRAIN_TYPES

/* Prototypes */
public void      create_gondor();
public void      make_treasure();
public string    show_statues();

object ob;

/*
 * Function name:    create_gondor()
 * Definition   :    Creates the room.
 */
public void
create_gondor()
{
    set_short("Inside a small chamber.");
    set_long("You are inside a chamber. The air feels very dense here. The " +
	"walls are richly decorated with carvings of old Gondorian " +
	"tales. In each of the eight corners of the room there are " +
	"statues symboling valar. In the middle of the room a broken " +
	"chest and three broken barrels are placed. On the south wall " +
	"an old armor rack stands empty, like somebody forgot to " +
	"return the chain mail shirt they borrowed, and on the north " +
	"wall a weapon rack stands in the same condition. A painting " +
	"adores the east wall while a door is on the west wall. The " +
	"rest of the walls are naked and empty.\n");

    add_item( ({ "corners", "corner" }), "In each corner a statue is " +
	"erected. The statues shows both male and female valar.\n");
    add_item("ground", "The ground is made of tiled rocks in various " +
	     "shape and size. Most of the rocks are gray, but some " +
	     "coloured rocks are found aswell.\n");
    add_item( ({ "statues", "statue", "valar", "statues of valar", 
		   "statues of the valar"}), &show_statues());
    add_item( ({ "rack", "racks" }), "Do you want to examine the armour " +
	      "rack or the weapon rack?\n");
    add_item("weapon rack", "This is an old weapon rack, with space for " +
	     "six swords. Time have marked the rack well over the years. " +
	     "The rack is curently empty.\n");
    add_item("north wall", "The north wall is gray, and it looks like " +
	     "somebody have carved something in there. Looking closer " +
	     "it looks like a large tree filled with starshaped flowers " +
	     "and seven stars in an arch over it. An empty weapon rack " +
	     "stands on the middle of the wall.\n");
    add_item("armour rack", "This is an old armour rack, with space for " +
	     "one full armour and two chain shirts. The rack is made to " +
	     "look like three guards standing watch. The rack is curently " +
	     "empty.\n");
    add_item("south wall", "The south wall is gray, and it looks like " +
	     "somebody have carved something in there. Looking closer " +
	     "it looks like a fleet anchoring up in a large bay. An " +
	     "empty armour rack stands on the middle of the wall.\n");
    add_item("west wall", "The west wall is gray, and it looks like " +
	     "somebody have carved something there. Looking closer it " +
	     "looks like a mounted army riding to battle with banners " +
	     "flying. On the middle of the wall a door leads to the " +
	     "tunnel.\n");
    add_item( ({ "painting", "east wall", "old painting", 
		   "painting on east wall", "old painting on east wall" }),
	     "This old painting is very dusty, but under the dust you " +
	     "manages to make out a portrait of a man in a black chain " +
	     "shirt. Under the painting a brass sign reads: Morthec.\n");
    add_item("northwest wall", "The northwest wall is gray, and it looks " +
	     "like somebody have carved something int there. Looking " +
	     "closer it looks like a battlefield. In the foreground you " +
	     "see a fallen man holding a banner.\n");
    add_item("northeast wall", "The northeast wall is gray, and it looks " +
	     "like somebody have carved something in there. Looking " +
	     "closer it looks like an elven king offering a gift to the " +
	     "king. The gift consists of a sword and a spear.\n");
    add_item("southeast wall", "The southeast wall is gray, and it looks " +
	     "like somebody have carved something in there. Looking " +
	     "closer it looks like an oliphant crushing through a forest " +
	     "with a cage on its back.\n");
    add_item("southwest wall", "The southwest wall is gray, and it looks " +
	     "like somebody have carved something in there. Looking " +
	     "closer it looks like a city with a tall spear in the center " +
	     "of several circular walls.\n");
    add_item( ({ "walls", "wall" , "carving", "carvings" }), "The walls " +
             "are filled with carvings from Gondorian tales, you can " +
             "look closer at each of the eight walls.\n");

    add_prop(ROOM_I_LIGHT, -3);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_DARK_LONG, DARK_ROOM_LONG);
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_TUNNEL);

    reset_room();
    make_treasure();

    clone_object(E_OBJ + "pdoor2.c")->move(this_object());
}

/*
 * Function name: reset_room()
 */
public void
reset_room()
{
    if (!present ("sword"))
    {
        ob=clone_unique(E_OBJ + "gwaedhel-sword.c", 1, 
	    E_OBJ + "g_sword_rand.c", 1, 100);
	ob->move(this_object());
    }
}

public void
make_treasure()
{
    MONEY_MAKE_CC(150)->move(this_object());
    MONEY_MAKE_SC(100)->move(this_object());
    MONEY_MAKE_GC(50)->move(this_object());
    MONEY_MAKE_PC(1)->move(this_object());
}

public string
show_statues()
{
    string text;
    object tp = this_player();
    string race, rguild, lguild, oguild;
    int i = 0;

    race = tp->query_race_name();
    rguild = tp->query_guild_name_race();
    lguild = tp->query_guild_name_lay();
    oguild = tp->query_guild_name_occ();

    if (lguild == HERALD)
    {
        text = "Eight statues are placed one in each corner. They " +
	  "all shows one of the valar.\n" +
	  "   The most dominant of the statues are a tall figure " +
	  "in a blue material. He is sitting in a throne with a septer " +
	  "in his right hand, and a crown on his head. In his left hand " +
	  "he holds a wand. This is Manwe, the King of Valinor.\n" +
	  "   Opposite of Manwe a female figure in pure white stands. " +
	  "She holds a spyglass in her right hand and gazes up towards " +
	  "the stars. She is Varda, wife of Manwe and Queen of Valinor.\n" +
	  "   To the left of Manwe a tall mounted figure stands clad in " +
	  "silver. He wields a composite bow and scouts out for prays. " +
	  "This is Orome, the hunter.\n" +
	  "   Opposite of Orome a female person stands holding her lut " +
	  "like she playes on it. She wears an orange colored dress and " +
	  "have a joyfull look on her face. This is Nessa, the Mistress " +
	  "of Celebrations.\n" +
	  "   On Manwe's right hand a tall figure with a large blacksmith " +
	  "hammer in his right hand. It looks like he is forging " +
	  "something. This is Aule, the Smith.\n" +
	  "   Opposite of Aule a beautifull female stands wearing a green " +
	  "dress, she have flowers in her hair. This is Yavannah, Mistress " +
	  "of Living Earth.\n" +
	  "   Between Nessa and Aule a male figure in a deep blue robe " +
	  "stands. At first it is hard to see his face, but when you look " +
	  "closer you can see a face consentrating with something. He holds " +
	  "an open book in his right hand. This is Irmo, the seer of " +
	  "Valinor and Dream Master.\n" +
	  "   Opposite of Irmo a tall warrior stands with armour of " +
	  "reddish gold. He wields a large battle axe as if he was " +
	  "swinging it at somebodys head. This is Tulkas, the Champion of " +
	  "Valinor.\n";
        return text;
    }

    if (race == "elf")
    {
	if (rguild == DROW)
	    i = -1;
	else
	    i = 1;
    }

    if (rguild == DUNEDAIN)
        i = 3;
    if (rguild == HOBBIT)
        i = 2;
    if (rguild == NOLDOR)
        i = 3;
    if (rguild == ROCKFRIEND)
        i = 2;

    if (oguild == MM)
        i = i + 1;
    if (oguild == RANGER)
        i = i + 1;

    switch(i)
    {
    case -1:
      text = "Eigth statues is placed one in each corner of the room. They " +
	"show various human like figures, listing clockwise; a female " +
	"astrologer, a female bard, a seer, a blacksmith, a king, a hunter, " +
	"a warrior, and a female animist. You supose these are the dieties " +
	"of those creating the statues.\n";
      break;
    case 0:
      text = "Eigth statues is placed one in each corner of the room. They " +
        "show various human like figures, listing clockwise; a female " +
        "astrologer in a white dress, a female bard in an orange dress, " +
	"a seer in a deep blue robe, a blacksmith, a king, a hunter clad in " +
	"silver, a warrior with a reddish golden armour, and a female " +
	"animist in a green dress. You supose these are the dieties " +
        "of those creating the statues.\n";
      break;
    case 1:
      text = "Eigth statues is placed one in each corner of the room. They " +
        "show various human like figures, listing clockwise; a female " +
        "astrologer in a white dress, a female bard in an orange dress, " +
        "a seer in a deep blue robe, a blacksmith, a king, a hunter clad in " +
        "silver, a warrior with a reddish golden armour, and a female " +
        "animist in a green dress. You guess these are the Valar.\n";
      break;
    case 2:
      text = "Eight statues are placed one in each corner. They " +
	"all shows one of the valar.\n" +
	"   The most dominant of the statues are a tall figure " +
	"in a blue material. He is sitting in a throne with a septer " +
	"in his right hand, and a crown on his head. In his left hand " +
	"he holds a wand.\n" +
	"   To the left a tall mounted figure stands clad in " +
        "silver. He wields a composite bow and scouts out for prays.\n" +
        "   To the left a tall warrior stands with armour of " +
        "reddish gold. He wields a large battle axe as if he was " +
        "swinging it at somebodys head.\n";
        "   To the left a beautifull female stands wearing a green " +
        "dress, she have flowers in her hair.\n" +
        "   To the left a female figure in pure white stands. " +
        "She holds a spyglass in her right hand and gazes up towards " +
        "the stars.\n" +
        "   To the left a female person stands holding her lut " +
        "like she playes on it. She wears an orange colored dress and " +
        "have a joyfull look on her face.\n" +
        "   To the left a male figure in a deep blue robe " +
        "stands. At first it is hard to see his face, but when you look " +
        "closer you can see a face consentrating with something. He holds " +
        "an open book in his right hand.\n" +
        "   The last statue is a tall figure with a large blacksmith " +
        "hammer in his right hand. It looks like he is forging " +
        "something.\n";
      break;
    case 3:
      text = "Eight statues are placed one in each corner. They " +
	"all shows one of the valar.\n" +
	"   The most dominant of the statues are a tall figure " +
	"in a blue material. He is sitting in a throne with a septer " +
	"in his right hand, and a crown on his head. In his left hand " +
	"he holds a wand. This is Manwe.\n" +
	"   Opposite of Manwe a female figure in pure white stands. " +
	"She holds a spyglass in her right hand and gazes up towards " +
	"the stars. She is Varda.\n" +
	"   To the left of Manwe a tall mounted figure stands clad in " +
	"silver. He wields a composite bow and scouts out for prays. " +
	"This is Orome.\n" +
	"   Opposite of Orome a female person stands holding her lut " +
	"like she playes on it. She wears an orange colored dress and " +
	"have a joyfull look on her face. This is Nessa.\n" +
	"   On Manwe's right hand a tall figure with a large blacksmith " +
	"hammer in his right hand. It looks like he is forging " +
	"something. This is Aule.\n" +
	"   Opposite of Aule a beautifull female stands wearing a green " +
	"dress, she have flowers in her hair. This is Yavannah.\n" +
	"   Between Nessa and Aule a male figure in a deep blue robe " +
	"stands. At first it is hard to see his face, but when you look " +
	"closer you can see a face consentrating with something. He holds " +
	"an open book in his right hand. This is Irmo.\n" +
	"   Opposite of Irmo a tall warrior stands with armour of " +
	"reddish gold. He wields a large battle axe as if he was " +
	"swinging it at somebodys head. This is Tulkas.\n";
      break;
    case 4:
      text = "Eight statues are placed one in each corner. They " +
	"all shows one of the valar.\n" +
	"   The most dominant of the statues are a tall figure " +
	"in a blue material. He is sitting in a throne with a septer " +
	"in his right hand, and a crown on his head. In his left hand " +
	"he holds a wand. This is Manwe, the King of Valinor.\n" +
	"   Opposite of Manwe a female figure in pure white stands. " +
	"She holds a spyglass in her right hand and gazes up towards " +
	"the stars. She is Varda, wife of Manwe and Queen of Valinor.\n" +
	"   To the left of Manwe a tall mounted figure stands clad in " +
	"silver. He wields a composite bow and scouts out for prays. " +
	"This is Orome, the hunter.\n" +
	"   Opposite of Orome a female person stands holding her lut " +
	"like she playes on it. She wears an orange colored dress and " +
	"have a joyfull look on her face. This is Nessa, the Mistress " +
	"of Celebrations.\n" +
	"   On Manwe's right hand a tall figure with a large blacksmith " +
	"hammer in his right hand. It looks like he is forging " +
	"something. This is Aule, the Smith.\n" +
	"   Opposite of Aule a beautifull female stands wearing a green " +
	"dress, she have flowers in her hair. This is Yavannah, Mistress " +
	"of Living Earth.\n" +
	"   Between Nessa and Aule a male figure in a deep blue robe " +
	"stands. At first it is hard to see his face, but when you look " +
	"closer you can see a face consentrating with something. He holds " +
	"an open book in his right hand. This is Irmo, the seer of " +
	"Valinor and Dream Master.\n" +
	"   Opposite of Irmo a tall warrior stands with armour of " +
	"reddish gold. He wields a large battle axe as if he was " +
	"swinging it at somebodys head. This is Tulkas, the Champion of " +
	"Valinor.\n";
      break;
    default:
      text = "This text should never occure, check the code.\n";
      break;
    }

    return text;
}
