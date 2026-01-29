// The Apothecary Main Shop
// file name:    /d/Avenir/common/bazaar/intr/apoth1.c
// creator(s):   Ilyian, May 1995
// last update:  Lilith, 17Feb97: see below (note)
//
//		     Sirra May 23, 1998: added do_search()
//
// purpose:      Selling miscellaneous objects, some of which might be
//               magical or ingredients for spells, etc.
// note:         Making additions to the Apothecary shop so it isn't
//               just herbs. Herbalist (apoth), Potion shop (apoth2) 
// bug(s):
// to-do:        Open the potion and scroll shop and the healer later.

inherit "/d/Avenir/common/lib/shop";
inherit "/d/Avenir/inherit/room_tell";

#include "/d/Avenir/common/holm/wolf.h"
#include "/d/Avenir/common/bazaar/bazaar.h"
#include "/d/Avenir/include/relation.h"
#include <money.h>

#define NUM           sizeof(MONEY_TYPES)
#define PRICELIST_ID  ({"pricelist", "list", "prices", "menu",})
#define STORE_ROOM    "/d/Avenir/common/bazaar/intr/apostore"
#define MAXLIST       40
#define KEEPER "/d/Avenir/common/bazaar/NPCS/"


/* Prototypes */
string exa_poster();

int found;

void
create_shop()
{
    config_default_trade();
    
    set_shop_name("Bazaar Apothecary Shop");
    set_store_room(STORE_ROOM);
    set_keeper_file("/d/Avenir/common/bazaar/NPCS/apo");
    set_money_greed_buy(150); 
    set_suspected_race(({"hobbit"}));    // No hobbits in Avenir
    set_favoured_race(({"elf", "gnome"}));
    set_short("Apothecary main shop, doorway leading west");
    set_long("A small room, close and dark, with an incense brazier "+
        "in its center pouring scented smoke into the air. Shelves "+
        "line the walls, stock-piled with odd bits of medical and "+
        "magical paraphernalia. This place is festooned with wizened "+
        "animal pelts, reptile skins, and embalmed mice and rat corpses. "+
        "There are dusty bones and withering body parts, henna "+
        "patterns, small sachets in bright greens and pinks, bottles "+
        "of oil, amulets and other curiosities all jumbled together "+
        "in a disturbing and chaotic arrangement.\nThere is a sign "+
        "hanging on the wall.\n");

    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    add_item(({"paraphernalia", "medical paraphernalia", "magical "+
        "paraphernalia"}), "A jumble of ingredients for everything "+
        "from poultices to potions.\n");
    add_item(({"festoon", "pelts", "skins"}), "Some appear fairly "+
        "fresh, while others might have been hanging here for "+
        "decades.\n");
    add_item(({"mice", "rat", "corpses", "body parts", "parts"}),
        "They are what they appear to be, and must have some use, or "+
        "they wouldn't be cluttering this place.\n");
    add_item(({"bones", "bone", "dusty bones", "pile of bones"}), 
	  ("Yellowish with age and dirt, they "
	  + "sit collected in a dry, forgotten heap along the shelf.\n"));
    add_item(({"shelf", "shelves", "wall", "walls"}),
        "Wooden shelves cover all the walls of this room, and they "+
        "fairly groan under the weight of the paraphernalia piled "+
        "upon them.\n");
    add_item(({"brazier", "fire", "tripod"}),"The brazier "+
        "rests on a tripod in the center of the room. The smoke is "+
        "thick and heavily-scented, probably to cover the smell "+
        "of decaying flesh.\n");
    add_item(({"air", "smoke", "haze"}), "The air is thick with "+
        "heavily-scented smoke, creating a haze.\n");
    add_cmd_item(({"air", "smoke", "incense"}), ({"smell", "sniff"}),
        "It smells of pine-needles, lemon, and sandalwood.\n");
    add_cmd_item(({"parphernalia", "medical paraphernalia", "magical "+
        "paraphernalia", "corpses", "rat", "mice", "pelts", "skins",
        "bones", "body parts", "parts", "henna patterns", "sachets",
        "bottles", "amulets", "curiosities"}), ({"get", "take"}), 
        "On second thought...maybe you'd better pay for it first.\n");
    add_item("poster","It has readable words on it.\n");
    add_cmd_item(({"sign", "poster","list","prices"}), "read", exa_poster());
    add_item(({"sign", "wall"}), "The sign hanging on the wall has "+
        "writing on it.\n");
    set_tell_time(100);
      add_tell("Smoke from the incense brazier curls upward.\n");
      add_tell("The scent of herbs is carried in on a puff of "+
          "wind.\n");
      add_tell("A puff of wind sets a wizened animal pelt into motion.\n");
      add_tell("The smoke causes your eyes to burn and water.\n");
      add_tell("The smell of decaying flesh is suddenly, pungently "+
          "in the air.\n");
      add_tell("There is a clatter as a small pile of bones collapses "+
          "in on itself.\n");

    found = 20;
			//It is referenced in do_search(). 

	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.

    add_exit(INTR + "apoth",  "west",0);
//    add_exit(INTR + "p&s_shop", "down", 0);
//    add_exit(INTR + "infirm", "south", 0);
}

string
exa_poster()
{
    return "\n"
      + "Welcome to " + shop_name + "!\n"
      + "   Here we buy and sell all manner of curiosities\n"
      + "   and medicinal and magical supplies.\n\n"     
      +"    Expect us to expand to include an Alchemist and a\n"
      +"    Healer on our staff shortly.\n"
//      + "   If you seek to trade in potions or scrolls, see\n"
//      + "   the Alchemist in the room below.\n\n"
//      + "   If you seek medical attention, the infirmary is\n"
//      + "   south of here.\n\n"
      + "\n";
}

int
do_buy(string args)
{
    if (IS_INFIDEL(this_player()))
    {
        tell_object(this_player(), "The apothecarist refuses to "+
           "trade with you.\n");
        return 1;
    }

    if (check_keeper()) return ::do_buy(args);
    return 0;
}

int
do_value(string args)
{
  if (check_keeper()) return ::do_value(args);
  return 0;
}

int
do_sell(string args)
{
    if (IS_INFIDEL(this_player()))
    {
        tell_object(this_player(), "The apothecarist refuses to "+
           "trade with you.\n");
        return 1;
    }

    if (check_keeper()) return ::do_sell(args);
    return 0;
}

int
do_list(string args)
{
  if (check_keeper()) return ::do_list(args);
  return 0;
}

mixed
shop_hook_filter_sell(object ob)
{

    if (weapon_filter(ob) || armour_filter(ob))
        return "The shopkeeper says: I deal in curiosities, medicinal "+
               "and magical objects, not anything so mundane as weapons "+
               "and armours!\n"; 
    else
      return 0;
}

string
do_search(object player, string str)
{
	
	if(!str)
	return 0;

	if(str != "bones" && str != "bone" && str != "pile of bones"
	&& str != "dusty bones" && str != "small pile of bones")
	return 0;

/*
	if(present("KEEPER + apo.c", environment(this_object()) ))
	//&& CAN_SEE(TO, TP)
	{
		tell_room("The shopkeeper slaps "
		+ QCTNAME(this_player())
		+ "'s hand!\n", this_player());

		return "The shopkeeper slaps your hand!\n";		
	}
*/

	found--;

	tell_room(QCTNAME(player)
	+ " finds something in the bones!\n", player);		

        clone_object(WOLF_BONE + "redherring.c")
	->move(this_player(), 1 );

        return "You found a bone!\n";
}


/* Start the room tells as soon as someone enters the room */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
      start_room_tells();
}
