// file name:	/d/Avenir/common/village/npc/cobbler.c
// creator(s):	Lilith, Lucius
/* Revisions:
 * 	Lucius, Oct 2008: Updates for new merchant area and Avenir craftsman.
 * 	Lucius, Apr 2018: Item enhancements.
 */
#pragma strict_types

#include "../village.h"
inherit BASE_MERCHANT;

static string
my_long(void)
{
    return "He makes a good living as a cobbler, for his custom-made "+
	"shoes are in high demand, and his stooped stature is proof "+
	"of his dedication to his craft.\n"+
	"He is wearing a brooch bearing the sigil of his House: a "+
	"black lily on a field of yellow, bordered in crimson.\n"+
	"He has a strong, square jaw and peaked eyebrows over "+
	"prominent gray eyes.\n"+
	"His shoulder-length hair is tied back with a ribband.\n";
}

static void
create_merchant(void)
{
    set_name("bartol");
    set_living_name("bartol");
    add_name(({"cobbler", "merchant", "shoemaker", "shoe maker" }));
    set_race_name("human");
    set_gender(0);
    set_title("ini Llin, Master Cobbler of Sybarus");
    set_adj(({"stooped"}));

    set_act_time(3);
    add_act("emote measures out some fabric.");
    add_act("emote cuts some thick leather to make the sole of a shoe.");
    add_act("emote takes a moment to stretch his tired back.");
    set_chat_time(7);
    add_chat("Ae make shoes to order.");
    add_chat("Ae am always looking for new styles of shoes to make. "+
      "Do su have any suggestions?");

    add_ask(({"shoes", "order", "merchandise", "item", "items"}), 
      "say Ae make shoes. If su want a pair, just 'order shoes' and ae "+
      "will prompt su for the rest.", 1);
    add_ask(({"buy", "purchase", "collect", "retrieve", "pick up", "get shoes"}), 
      "say If su want your shoes, su should 'check order' to find out if "+
      "it is ready." ,1);  
    add_ask(({"cancel", "stop"}), 
      "say If su do not want shoes, su may 'cancel order'", 1);
    add_ask(({"suggestion", "suggestions"}), "say Please submit an idea report "+
      "on me or my shoes and hopefully it will be done soon.", 1);

    // possible names for the item sold
    craftsman_set_sold_item_names(({ "shoes", "sandals", "shoes", "slippers", 
	"mules", "moccasins", "clogs", "boots", "loafers", "heels", "item" }));
}

public string *
merchant_descs(int id, string name, mapping order)
{
    switch(order["style"])
    {
    case "boots":
	return ({ "none", "low", "tall", "knee-high", "thigh-high" });
    default:
	return ({ });
    }
}

public void
craftsman_configure_order(int order_id, string arg)
{
    // the file for the item to clone
    craftsman_set_item_file(order_id, V_OBJ + "custom_shoes");

    // time in seconds to complete creation of the item
    craftsman_set_time_to_complete(order_id, 30 + random(35));

    // the cost of an item (in cc)
    craftsman_set_item_cost(order_id, 288 + random(144));

    craftsman_add_attribute(order_id, "style",
      ({ "sandals", "shoes", "slippers", "mules", "moccasins", 
	"clogs", "boots", "loafers", "heels" }));

    craftsman_add_attribute(order_id, "desc", merchant_descs);

    craftsman_add_attribute(order_id, "material",
      ({ "chamois", "leather", "suede", "silk", "satin", "velvet", 
	"wooden" }));

    craftsman_add_attribute(order_id, "colour",
      ({ "black", "dark", "ebony", "charcoal", "gray", 
	"silvery",  "white", "light", "pale", "cream", "ivory", "buff", 
	"beige", "ecru", "golden", "yellow", "tawny", "saffron", 
	"amber", "chartreuse", "green", "emerald", "viridian", "olive", 
	"khaki", "jade", "aquamarine", "teal", "blue", "azure", 
	"cerulean", "sapphire", "turquoise", "indigo", "orange",
	"apricot", "coral", "peach", "pink", "fuschia", "scarlet", 
	"rose", "red", "blood-red", "burgundy", "cerise", "crimson", "ruby", 
	"magenta", "maroon", "russet", "vermillion", "purple", "amethyst",
	"lavender", "lilac", "mauve", "plum", "violet", "brown",
	"coppery", "chocolate", "fawn", "mahogany", "ochre", 
	"sable", "sepia", "tan", "umbre"
      }));
}

/*
 * check_meet enables the npc to greet players it
 * comes into contact with, according to guild.
 */
static void
check_meet(object who, string oname, int sybarite)
{
    if (sybarite)
    {
	command("say to "+ oname +
	    " Celebrate the Source.");
	command("say to "+ oname +
	    " May ae make su a pair of shoes?");
    }
    else
    {
	command("say to "+ oname +
	    " Greetings Outlander. Are su here to order shoes made?");
    }
}

public void
craftsman_configure_item(object ob, mapping attrs, int order_id)
{
    ob->set_style(attrs["style"]);
    ob->set_desc(attrs["desc"]);
    ob->set_colour(attrs["colour"]);
    ob->set_fabric(attrs["material"]);

    ob->create_tailored();
    command("say Enjoy your new shoes.");
}
