// file name:	/d/Avenir/common/village/npc/shirtmaker.c
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
    return "She is a clothier who specializes in making women's blouses "+
	"and undergarments.\n"+
	"She is wearing a shawl bearing the sigil of her House: "+
	"a white cygnet on a field of blue, bordered in crimson.\n"+
	"Her hair is braided and pinned atop her head, displaying "+
	"her graceful neck.\n"+
	"Her round chin has a small cleft to go with the dimples "+
	"in her cheeks.\n";
}

static void
create_merchant(void)
{
    set_name("pikkara");
    set_living_name("pikkara");
    add_name(({"clothier", "merchant", "shirt maker" }));
    set_race_name("human");
    set_gender(1);
    set_title("ini Cimron, of the Clothiers of Cimron");
    set_adj(({"dimpled"}));

    set_act_time(4);
    add_act("emote measures out some fabric.");
    add_act("emote holds a gray velvet cholie up and looks at it thoughtfully.");
    add_act("emote smiles very prettily, flashing her dimples.");
    add_act("emote pats the crown of braids atop her head.");
    add_act("emote runs some fringe through her fingers.");

    set_chat_time(9);
    add_chat("Ae make women's shirts and undergarments.");
    add_chat("Ae think fine undergarments make the woman.");
    add_chat("Su have but to 'order item' and soon su shall "+
      "have what you desire.");

    add_ask(({"item", "make", "sell", "bandeau", "blouse", "bodice",
	"cholie", "camise", "camisole", "shirt", "shirtwaist", "underbodice"}), 
      "say Ae make shirts and undergarments. If su one, just 'order item' "+
      "and ae will prompt su for the rest.", 1);
    add_ask(({"buy", "purchase", "collect", "retrieve", "pick up", "get item"}), 
      "say If su want your item, su should 'check order' to find out if "+
      "it is ready." ,1);  
    add_ask(({"cancel", "stop"}), 
      "say Su may use 'cancel order'", 1);
    add_ask(({"suggestion", "suggestions"}), "say Please submit an idea report "+
      "on me or my merchandise and hopefully it will be done soon.", 1);

    // possible names for the item sold
    craftsman_set_sold_item_names(({ "bandeau", "blouse", "bodice",
	"cholie", "camise", "camisole", "shirt", "shirtwaist", 
	"underbodice", "item", "garment"}));
}

public void
craftsman_configure_order(int order_id, string arg)
{
    // the file for the item to clone
    craftsman_set_item_file(order_id, V_OBJ + "custom_cholie");

    // time in seconds to complete creation of the item
    craftsman_set_time_to_complete(order_id, 30 + random(35));

    // the cost of an item (in cc)
    craftsman_set_item_cost(order_id, 188 + random(144));

    craftsman_add_attribute(order_id, "style",
      ({ "bandeau", "blouse", "bodice", "cholie", "camise", "camisole", 
	"shirt", "shirtwaist", "underbodice"
      }));
    craftsman_add_attribute(order_id, "material",
      ({ "cambric", "flannel", "homespun", "lace", "linen", "leather", 
	"muslin", "satin", "silk", "tartan", "velvet", "webcloth"
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
	"faded", "fitted", "flamboyant", "flashy", "flowered", "flowing",
      	"fringed", "fur-trimmed", "gaudy", 
	"glossy", "gorgeous", "heirloom", "hideous", "ironed", "laced", "lacy",
	"loud", "luxurious", "ornate", "opulent", "paisley", 
	"piped", "plain", "pleated", "plush", "pressed", "quilted", "ruffled", 
	"sheer", "short", "simple", "slender", "snug", "sparkling", "striped", 
	"ribbed", "rich", "rough", "tailored", "tasseled", "tasteful", "thin",
      	"unadorned", "ugly", "warm", "wrinkled", "none",
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
    command("say Ae hope your "+ ob->short() +" brings pleasure. Ectios!");
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
	command("say to "+ oname +" Intios citizen.");
    }
    else
    {
	command("say to "+ oname +
	    " Ae will be pleased to serve you. Would you like a shirt?");
    }
}
