// file name:	/d/Avenir/common/village/npc/pantmaker.c
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
	"and selling trousers.\n"+
	"She is wearing a scarf bearing the sigil of her House: a gold "+
	"cup on a field of orange, bordered in green.\n"+
	"Her long, way hair is swept away from her face by two braids "+
	"fastened at her nape in a serpentine knot.\n"+
	"She has a small, stubborn chin and assessing dark eyes.\n";
}

static void
create_merchant(void)
{
    set_name("semmee");
    set_living_name("semmee");
    add_name(({"pantmaker", "merchant", "pant maker",
	"clothier", "trouser seller" }));
    set_race_name("gnome");
    set_gender(1);
    set_title("ini F'niel, the Trouser Seller");
    set_adj(({"dark-eyed"}));

    set_act_time(4);
    add_act("emote measures out some fabric.");
    add_act("emote sews some fringe along the hem of a "+
      "pair of bloomers.");
    add_act("emote regards you with knowing eyes.");
    add_act("emote pats her braids.");
    add_act("emote smoothes a pair of black velvet pantaloons.");

    set_chat_time(9);
    add_chat("Ae will make su a pair of pants.");
    add_chat("Su have but to 'order item' and soon su shall "+
      "have it.");

    add_ask(({"item", "make", "sell", "bloomers", "drawers", "harem","harem pants", 
	"jodhpurs", "knickers", "pants", "pantaloons", "slacks", "trousers"}), 
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
    craftsman_set_sold_item_names(({ "item", "bloomers", "drawers", "harem",
	"harem pants", "jodhpurs", "knickers", "pants", "pantaloons", "slacks", 
	"trousers"}));
}

public void
craftsman_configure_order(int order_id, string arg)
{
    // the file for the item to clone
    craftsman_set_item_file(order_id, V_OBJ + "custom_pants");

    // time in seconds to complete creation of the item
    craftsman_set_time_to_complete(order_id, 30 + random(35));

    // the cost of an item (in cc)
    craftsman_set_item_cost(order_id, 188 + random(144));

    craftsman_add_attribute(order_id, "style",
      ({ "bloomers", "drawers", "harem", "jodhpurs", "knickers", "pants", 
	"pantaloons", "slacks", "trousers"
      }));
    craftsman_add_attribute(order_id, "material",
      ({ "cambric", "chamois", "flannel", "homespun", "lace", "linen", 
	"leather", "muslin", "samite", "satin", "silk", "suede", "tartan", 
	"tweed", "velvet", "webcloth", "wool"
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
      ({ "banded", "beaded", "beautiful", "bold", "boring", "brocaded", 
	"checked", "clean", "cool", "conservative", "crested", "crisp", "cuffed",
	"diaphanous", "distressed", "elegant", "embroidered", "exquisite", 
	"faded", "flamboyant", "flashy", "flowered", "flowing", "fringed", 
	"fur-trimmed", "gaudy", 
	"glossy", "gorgeous", "heirloom", "hideous", "ironed", "laced", "lacy",
	"loud", "luxurious", "ornate", "opulent", "paisley", 
	"piped", "plain", "pleated", "plush", "pressed", "quilted", "ruffled", 
	"sheer", "short", "simple", "slender", "snug", "sparkling", "striped", 
	"ribbed", "rich", "rough", "tasseled", "tasteful", "thin", "unadorned", 
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
    command("say Ae wish su good use of it. Pashat!");
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
	    " Ae will be happy to make su a pait of pants.");
    }
}
