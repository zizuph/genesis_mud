// file name:	/d/Avenir/common/village/npc/shawlmaker.c
// creator(s):	Lilith, Lucius
// revisions: 	Lucius Oct 2008
// purpose:          
// note:
// bug(s):           
// to-do:            
#pragma strict_types

#include "../village.h"
inherit BASE_MERCHANT;

static string
my_long(void)
{
    return "She is a clothier of sorts, one who specializes in making "+
	"and selling shawls.\n"+
	"She is wearing a shawl bearing the sigil of her House: a gold "+
	"cup on a field of orange, bordered in green.\n"+
	"She is one of the few dwarven females that can be seen outside "+
	"the Dwarf Soke.\n"+
	"Her short hair forms lustrous ringlets that frame a strong, "+
	"square face.\n"+
	"Her bold chin has the barest hint of fuzz, for she is young yet.\n";
}

static void
create_merchant(void)
{
    set_name("marzil");
    set_living_name("marzil");
    add_name(({"shawlmaker", "merchant", "shawl maker" }));
    set_race_name("dwarf");
    set_gender(1);
    set_title("ini F'niel, the Maker of Shawls");
    set_adj(({"adolescent"}));

    set_act_time(4);
    add_act("emote measures out some fabric.");
    add_act("emote sews some fringe along the edge of a "+
      "cerulean cambric scarf.");
    add_act("emote seems very composed for one so young.");
    add_act("emote looks like she is practicing at being dour.");
    add_act("emote tosses her head a bit, making her curls bounce.");

    set_chat_time(9);
    add_chat("Ae will make su a shawl or wrap.");
    add_chat("Su have but to 'order item' and soon su shall "+
      "have it.");

    add_ask(({"item", "shawl", "wrap", "make", "sell"}), 
      "say Ae make shawls and wraps. If su one, just 'order item' and ae "+
      "will prompt su for the rest.", 1);
    add_ask(({"buy", "purchase", "collect", "retrieve", "pick up", "get item"}), 
      "say If su want your item, su should 'check order' to find out if "+
      "it is ready." ,1);  
    add_ask(({"cancel", "stop"}), 
      "say Su may use 'cancel order'", 1);
    add_ask(({"suggestion", "suggestions"}), "say Please submit an idea report "+
      "on me or my merchandise and hopefully it will be done soon.", 1);

    // possible names for the item sold
    craftsman_set_sold_item_names(({ "shawl", "wrap", "item"}));
}

public void
craftsman_configure_order(int order_id, string arg)
{
    // the file for the item to clone
    craftsman_set_item_file(order_id, V_OBJ + "custom_shawl");

    // time in seconds to complete creation of the item
    craftsman_set_time_to_complete(order_id, 30 + random(35));

    // the cost of an item (in cc)
    craftsman_set_item_cost(order_id, 188 + random(144));

    craftsman_add_attribute(order_id, "style",
      ({ "shawl", "wrap" }));
    craftsman_add_attribute(order_id, "material",
      ({ "cambric", "flannel", "homespun", "lace", "linen", 
	"muslin", "samite", "satin", "silk", "tartan", "tweed", 
	"velvet", "webcloth", "wool"
      }));
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
    craftsman_add_attribute(order_id, "option",
      ({ "abstract", "banded", "beaded", "beautiful", "bold", 
	"boring", "brocaded", "checked", "clean", "cool", "conservative", 
	"crested", "crisp", "cuffed", "distressed", "elegant", "embroidered",
	"exquisite", "faded", "flowered", "flowing", "fringed", "fur-trimmed",
	"gaudy", "gorgeous", "heavy", "heirloom", "hideous", "ironed", "laced", 
	"long", "loose", "loud", "luxurious", "ornate", "opulent", "paisley", 
	"piped", "plain", "pleated", "plush", "pressed", "quilted", "ruffled", 
	"sheer", "short", "simple", "slender", "snug", "sparkling", "striped", 
	"ribbed","rich", "rough", "tasseled", "tasteful", "thin", "unadorned", 
	"ugly", "warm", "wrinkled", "none"
      }));
}

public void
craftsman_configure_item(object ob, mapping attrs, int order_id)
{
    ob->set_style(attrs["style"]);
    ob->set_desc(attrs["option"]);
    ob->set_colour(attrs["colour"]);
    ob->set_fabric(attrs["material"]);

    ob->create_tailored();
    command("say Ae wish su good use of it. Ectios!");
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
	command("say to "+ oname +" Sirli citizen.");
    }
    else
    {
	command("say to "+ oname +
	    " Ae will be happy to make su a shawl.");
	command("say to "+ oname +
	    " If su don't want one would su please move along?");
    }
}
