// file name:	/d/Avenir/common/village/npc/vestier.c
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
    return "He is a tailor, specializing in vests and waist-coats.\n"+
	"He is wearing a waist-coat embroidered with the sigil of "+
	"his House: blue flame on a field of white, bordered in green.\n"+
	"His long, thick hair is tied back with a thong, revealing "+
	"a broad forehead and throughful, dark eyes.\n";
}

static void
create_merchant(void)
{
    set_name("bruk");
    set_living_name("bruk");
    add_name(({"vestier", "merchant", "tailor" }));
    set_race_name("human");
    set_gender(0);
    set_title("icu Wer'a, the Vestmaker");
    set_adj(({"solemn"}));

    set_act_time(4);
    add_act("emote fingers some stitching on a fine waist-coat.");
    add_act("emote flicks dark eyes in your direction.");
    add_act("emote closes his eyes and turns his face up to the "+
      "Source, as if basking in its light.");
    add_act("emote runs some fabric through his fingers.");
    add_act("emote frowns throughfully.");

    set_chat_time(9);
    add_chat("Ae will make su a waist-coat in any colour.");
    add_chat("Su have but to 'order item' and soon su shall "+
      "have it.");
    add_chat("If su want to collect you purchase, simply "+
      "'check order' and if it is ready su shall have it.");
    add_chat("I use the finest fabrics available.");
    add_chat("Every gentleman of rank wears a waist-coat.");

    add_ask(({"item", "waist-coat", "vest", "singlet", "garment"}), 
      "say Ae make waist-coats, vests and singlets. If su one, "+
      "just 'order item' and ae will prompt su for the rest.", 1);
    add_ask(({"buy", "purchase", "collect", "retrieve", "pick up", "get item"}), 
      "say If su want your item, su should 'check order' to find out if "+
      "it is ready." ,1);  
    add_ask(({"cancel", "stop"}), 
      "say Su may use 'cancel order'", 1);
    add_ask(({"suggestion", "suggestions"}), "say Please submit an idea report "+
      "on me or my merchandise and hopefully it will be done soon.", 1);

    // possible names for the item sold
    craftsman_set_sold_item_names(({
	"item", "waist-coat", "vest", "singlet", "garment"}));
}

public void
craftsman_configure_order(int order_id, string arg)
{
    // the file for the item to clone
    craftsman_set_item_file(order_id, V_OBJ + "custom_vest");

    // time in seconds to complete creation of the item
    craftsman_set_time_to_complete(order_id, 30 + random(35));

    // the cost of an item (in cc)
    craftsman_set_item_cost(order_id, 120 + random(100));

    craftsman_add_attribute(order_id, "style",
      ({ "singlet", "waist-coat", "vest"}));
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
	"checked", "clean", "cool", "conservative", "crested", "crisp", 
	"cuffed", "distressed", "elegant", "embroidered", "exquisite", 
	"faded", "flamboyant", "flashy", "flowered", "flowing", "fringed", 
	"fur-trimmed", "gaudy", 
	"glossy", "gorgeous", "heirloom", "hideous", "ironed", "laced", "lacy",
	"loud", "luxurious", "ornate", "opulent", "paisley", 
	"piped", "plain", "pleated", "plush", "pressed", "quilted", "ruffled", 
	"sheer", "short", "simple", "snug", "sparkling", "striped", 
	"ribbed", "rich", "rough", "tasseled", "tasteful", "thin", "unadorned", 
	"ugly", "warm", "wrinkled", "none"
      }));
}

public void
craftsman_configure_item(object ob, mapping attrs, int order_id)
{
    ob->set_style(attrs["style"]);
    ob->set_fabric(attrs["material"]);
    ob->set_colour(attrs["colour"]);
    ob->set_desc(attrs["option"]);

    ob->create_tailored();
    command("say Ae think su will be very pleased with your purchase "+
      "of "+ ob->short() +".");
    command("say Pashat!");
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
	command("say to "+ oname +" Quansu citizen.");
    }
    else
    {
	command("say to "+ oname +
	    " Would su like vest or waist-coat perhaps?");
    }
}
