/*
 * The storage room of the Solamnian shop, made by Nick
 * modified for the thieves fence by Aridor.
 *
 * Modified to offer samples of goods sold in Palanthas
 * to replace the old junk gear known throughout the realms
 * as coming from this shop alone.
 *
 * Mortis 06.2006
 *
 */

inherit "/std/room";
inherit "/lib/store_support";

#include "guild.h"
#include <stdproperties.h>

#define TORCH 	"thief_shop_torch"
#define BAG		"thief_shop_bag"
#define SCARF   "thief_shop_scarf"
#define SHIRT   "thief_shop_shirt"
#define KNIFE   "thief_shop_knife"
#define MERCH	PARENT + "palanthas/merchants/"
#define NOBLE	PARENT + "palanthas/nobles/"
#define MONKS	PARENT + "palanthas/aesthetics/"
#define DCLOTH	NOBLE + "arms/parmour"

/*Prototype*/
void reset_room();
string set_up_bag();
string random_clothes(string insurance_shirt);
string set_up_knife();

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
create_room()
{
    set_short("The fence's store room");
    set_long("This is the store room of the fence.\n");

    add_exit(GUILDR + "shop", "up");

    INSIDE
    reset_room();
}

void
reset_room()
{
    object ob;

    if (!P(TORCH, TO))
    {
		seteuid(getuid(TO));

		ob = clone_object(MONKS + "obj/ptorch");
		ob->add_name(TORCH);
		ob->move(TO);

		ob = clone_object(MONKS + "obj/ptorch");
		ob->add_name(TORCH);
		ob->move(TO);

		ob = clone_object(MONKS + "obj/ptorch");
		ob->add_name(TORCH);
		ob->move(TO);
    }
    if (!P(BAG, TO))
    {
		seteuid(getuid(TO));

		ob = clone_object(MERCH + "obj/lgeneral");
		ob->set_general_data(set_up_bag() + "lootsack");
		ob->add_name(BAG);
		ob->move(TO);

		ob = clone_object(MERCH + "obj/lgeneral");
		ob->set_general_data(set_up_bag() + "sack");
		ob->add_name(BAG);
		ob->move(TO);
    }

    if (!P(CHALK, TO))
    {
		seteuid(getuid(TO));

		ob = clone_object(MONKS + "obj/mchalk");
		ob->add_name(CHALK);
		ob->move(TO);
    }

    if (!P(SHIRT, TO))
    {
		seteuid(getuid(TO));

		ob = clone_object(DCLOTH);
		ob->set_armour_data(random_clothes("yes"));
		ob->add_name(SHIRT);
		ob->move(TO);
		ob = clone_object(DCLOTH);
		ob->set_armour_data(random_clothes("yes"));
		ob->add_name(SHIRT);
		ob->move(TO);

		ob = clone_object(DCLOTH);
		ob->set_armour_data(random_clothes("yes"));
		ob->add_name(SHIRT);
		ob->move(TO);

		ob = clone_object(DCLOTH);
		ob->set_armour_data(random_clothes("no"));
		ob->add_name(SHIRT);
		ob->move(TO);

		ob = clone_object(DCLOTH);
		ob->set_armour_data(random_clothes("no"));
		ob->add_name(SHIRT);
		ob->move(TO);

		ob = clone_object(DCLOTH);
		ob->set_armour_data(random_clothes("no"));
		ob->add_name(SHIRT);
		ob->move(TO);

		ob = clone_object(DCLOTH);
		ob->set_armour_data(random_clothes("no"));
		ob->add_name(SHIRT);
		ob->move(TO);

		ob = clone_object(DCLOTH);
		ob->set_armour_data(random_clothes("no"));
		ob->add_name(SHIRT);
		ob->move(TO);

		ob = clone_object(DCLOTH);
		ob->set_armour_data(random_clothes("no"));
		ob->add_name(SHIRT);
		ob->move(TO);

		ob = clone_object(DCLOTH);
		ob->set_armour_data(random_clothes("no"));
		ob->add_name(SHIRT);
		ob->move(TO);

		ob = clone_object(DCLOTH);
		ob->set_armour_data(random_clothes("no"));
		ob->add_name(SHIRT);
		ob->move(TO);

		ob = clone_object(DCLOTH);
		ob->set_armour_data(random_clothes("no"));
		ob->add_name(SHIRT);
		ob->move(TO);
    }

    if (!P(KNIFE, TO))
    {
		seteuid(getuid(TO));

		ob = clone_object(MERCH + "arms/smith_knife");
		ob->set_weapon_data(set_up_knife());
		ob->add_name(KNIFE);
		ob->move(TO);

		ob = clone_object(MERCH + "arms/smith_knife");
		ob->set_weapon_data(set_up_knife());
		ob->add_name(KNIFE);
		ob->move(TO);

		ob = clone_object(OBJ + "dudgeon");
		ob->add_name(KNIFE);
		ob->move(TO);

		ob = clone_object(OBJ + "knife");
		ob->add_name(KNIFE);
		ob->move(TO);
    }
}

string
set_up_bag()
{
	string bag_style = one_of_list(({"dark", "flat", "fur-trimmed",
	"glistening", "light", "noble", "ornate", "plain", "rich", "supple",
	"thin"}));

	string bag_colour = one_of_list(({"black", "white", "charcoal", "grey",
	"brown", "mottled-brown", "crimson", "maroon", "yellow", "forest-green",
	"mottled-green", "olive-green", "blue", "raven-blue", "purple",
	"silvery"}));

	string bag_material = one_of_list(({"hard", "hide", "leather", "soft",
	"studded", "suede"}));

	return bag_style + "&&" + bag_colour + "&&" + bag_material + "&&";
}

string
random_clothes(string insurance_shirt)
{
	string for_whom = one_of_list(({"Marley", "Megas", "Antonin", "Noz",
	"Sworden", "Axor", "Hazor", "Brimbrum", "Bloodman", "Freyd", "Raysos",
	"Galyo", "Zimbal", "Bupu"}));

	string clo_custom = one_of_list(({"alluring", "billowing",
	"buttoned", "checkered", "cuffed", "custom-fitted", "debonair",
	"enchanting", "formal", "fur-trimmed", "gleaming", "heavy", "jaunty", 
	"knitted", "laced", "light", "long", "loose", "low-cut", "noble", "plain",
	"pleated", "rugged", "soft", "shaded", "sharp", "short", "striped",
	"tailored", "tassled", "thick", "thin", "tight", "translucent",
	"unbuttoned", "unlaced"}));

	string clo_colour = one_of_list(({"black", "white", "crimson", "maroon",
	"pink", "dark-orange", "orange", "pale-yellow", "yellow", "forest-green",
	"dark-green", "blue", "pale-blue", "raven-blue", "indigo", "purple",
	"royal-purple", "charcoal", "grey", "brown", "dark-brown", "beige", "tan",
	"coppery", "silvery", "golden"}));

	string clo_material = one_of_list(({"arrasene", "burlap", "cashmyr",
	"cotton", "hemp", "linen", "organdie", "messaline", "sackcloth", "silk",
	"suede", "wool"}));

	string clo_article = one_of_list(({"bathrobe", "vest", "dress", "frock",
	"gown", "muumuu", "shift", "baggy-pants", "capris", "kilt", "lederhosen",
	"pantaloons", "pants", "skirt", "slacks", "stockings", "bodice", "blouse",
	"puffy-shirt", "pullover", "shirt", "sleeveless-shirt", "sweater",
	"gloves", "long-gloves", "scarf"}));

	string clo_article2 = one_of_list(({"puffy-shirt", "pullover", "shirt",
	"sleeveless-shirt", "sweater"}));

	if (insurance_shirt == "yes")
		return for_whom + "&&" + clo_custom + "&&" + clo_colour + "&&"
		+ clo_material + "&&" + clo_article2;

	return for_whom + "&&" + clo_custom + "&&" + clo_colour + "&&"
	+ clo_material + "&&" + clo_article;
}

string
set_up_knife()
{
	string knife_adj1 = one_of_list(({"blackened", "curved",
	"folded-steel", "heavy", "light", "long", "polished", "serrated",
	"shining", "short", "thin", "throwing", "wide"}));

	string knife_adj2 = one_of_list(({"blackened", "curved",
	"folded-steel", "heavy", "light", "long", "polished", "serrated",
	"shining", "short", "thin", "throwing", "wide"}));

	string tknife = one_of_list(({"dagger", "flatknife", "knife", "kukri",
	"machete", "shank", "shiv", "stiletto"}));

	return knife_adj1 + "&&" + knife_adj2 + "&&" + tknife;
}

void
remove_items()
{
    int i;

    for (i=0 ; i<sizeof(remove_list) ; i++)
	if (remove_list[i] && present(remove_list[i]) &&
	  !remove_list[i]->id(KNIFE) &&
	  !remove_list[i]->id(SCARF) &&
	  !remove_list[i]->id(SHIRT) &&
	  !remove_list[i]->id(TORCH) &&
	  !remove_list[i]->id(BAG))
	    remove_list[i]->remove_object();
    remove_list = ({ });
}

