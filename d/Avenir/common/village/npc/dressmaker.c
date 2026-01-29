// file name:	/d/Avenir/common/village/npc/dressmaker.c
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
    return "He is a clothier who specializes in making women's dresses.\n"+
	"He is wearing an elegant blue ascot with a large pin bearing "+
	"the sigil of his House: "+
	"a white cygnet on a field of blue, bordered in crimson.\n"+
	"His hair is pomaded and combed straight back, falling to just "+
	"above his shoulders.\n"+
	"He wears a mustache and goatee, both trimmed short.\n";
}

static void
create_merchant(void)
{
    set_name("sarnoy");
    set_living_name("sarnoy");
    add_name(({"clothier", "merchant", "dress maker" }));
    set_race_name("human");
    set_gender(0);
    set_title("ini Cimron, of the Clothiers of Cimron");
    set_adj(({"elegant"}));

    set_act_time(4);
    add_act("emote hums to himself while comparing swatches of fabric.");
    add_act("emote adjusts the fit of the elegant blue ascot "+
      "and smoothes it into place.");
    add_act("emote strokes his facial hair while pondering something.");
    add_act("emote looks you up and down as though weighing your fashion sense.");
    add_act("emote runs some fringe through her fingers.");

    set_chat_time(9);
    add_chat("Ae make women look beautiful.");
    add_chat("Ae can make a dress for any occasion.");
    add_chat("Su have but to 'order item' and soon su shall "+
      "have what every woman desires.");

    add_ask(({"item", "make", "sell", "caftan", "chemise", "dress", "frock", 
	"gown", "peignoir", "pinafore", "shift", "smock", "tunic"}), 
      "say Ae make dresses. If su one, just 'order item' "+
      "and ae will prompt su for the rest.", 1);
    add_ask(({"buy", "purchase", "collect", "retrieve", "pick up", "get item"}), 
      "say If su want your item, su should 'check order' to find out if "+
      "it is ready." ,1);  
    add_ask(({"cancel", "stop"}), 
      "say Su may use 'cancel order'", 1);
    add_ask(({"suggestion", "suggestions"}), "say Please submit an idea report "+
      "on me or my merchandise and hopefully it will be done soon.", 1);

    // possible names for the item sold
    craftsman_set_sold_item_names(({ "item", "garment", "caftan", "chemise", 
	"dress", "frock", "gown", "peignoir", "pinafore", "shift", "skirt",
	"smock", "tunic" }));
}

public void
craftsman_configure_order(int order_id, string arg)
{
    // the file for the item to clone
    craftsman_set_item_file(order_id, V_OBJ + "custom_dress");

    // time in seconds to complete creation of the item
    craftsman_set_time_to_complete(order_id, 30 + random(35));

    // the cost of an item (in cc)
    craftsman_set_item_cost(order_id, 788 + random(144));

    craftsman_add_attribute(order_id, "style",
      ({ "caftan", "chemise", "dress", "frock", "gown", "peignoir", "pinafore", 
	"shift", "skirt", "smock", "tunic"
      }));
    craftsman_add_attribute(order_id, "material",
      ({ "cambric", "flannel", "homespun", "lace", "linen", "leather", 
	"muslin", "satin", "silk", "tartan", "velvet", "webcloth"
      }));
    craftsman_add_attribute(order_id, "option",
      ({ "none", "banded", "beaded", "beautiful", "bold", "boring",
	"brocaded", "checked", "clean", "cool", "conservative",
	"crested", "crisp", "cuffed", "diaphanous", "distressed",
	"elegant", "embroidered", "exquisite",
	"faded", "fitted", "flamboyant", "flashy","flowered",
	"flowing", "fringed", "fur-trimmed",
	"gaudy", "glossy", "gorgeous", "heirloom", "hideous", 
	"ironed", "knee-length", "laced", "lacy", "long", "loose",
	"loud", "luxurious", "mini", "ornate", "opulent", "paisley", 
	"piped", "plain", "pleated", "plush", "pressed", "quilted",
	"ruffled", "sheer", "short", "simple", "sparkling", "striped", 
	"ribbed", "rich", "rough", "tasseled", "tasteful", "thin",
        "tight", "unadorned", "ugly", "warm", "wrinkled",
	"dinner", "dressing", "evening", "formal", 
	"morning", "mourning", "night", "wedding"
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
}

public void
craftsman_configure_item(object ob, mapping attrs, int order_id)
{
    ob->set_style(attrs["style"]);
    ob->set_desc(attrs["option"]);
    ob->set_colour(attrs["colour"]);
    ob->set_fabric(attrs["material"]);

    ob->create_tailored();
    command("say Ae do believe you will be pleased with this purchase. Ectios!");
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
	command("say to "+ oname +" Ae will be pleased to serve you.");
	command("say to "+ oname +
	    " Would you like a dress, or perhaps a skirt?");
    }
}
