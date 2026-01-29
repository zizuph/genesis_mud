// file name:	/d/Avenir/common/village/npc/haberdasher.c
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
    return "She is a haberdasher of sorts, specializing in custom "+
	"neck-wear.\n"+
	"She is wearing a scarf bearing the sigil of her House: a field "+
	"of white and blue diagonal stripes, bordered in crimson.\n"+
	"Her waist-length hair is fastened at her nape with a trefoil "+
	"clasp.\n"+
	"She has a pointed chin and immense brown eyes.\n";
}

static void
create_merchant(void)
{
    set_name("dwinna");
    set_living_name("dwinna");
    add_name(({"haberdasher", "merchant" }));
    set_race_name("half-elf");
    set_gender(1);
    set_title("ini Imsa-sa, the Neckcloth Haberdasher");
    set_adj(({"swan-necked"}));

    set_act_time(4);
    add_act("emote measures out some fabric.");
    add_act("emote sews fine stitches along the edge of a "+
      "gorgeous silk scarf.");
    add_act("emote slides a satin cravat through her fingers "+
      "and sighs contentedly.");
    add_act("emote laces her fingers together and stretches "+
      "her arms above her head.");
    set_chat_time(9);
    add_chat("Ae make many unique items to be worn around the neck.");
    add_chat("Do su have any suggestions as to how ae can "+
      "improve my selection?");

    add_ask(({"item", "cravat", "scarf", "neckcloth", "order", "neckerchief",
	"merchandise", "ascot", "make", "sell"}), 
      "say Ae make neckcloths. If su one, just 'order item' and ae "+
      "will prompt su for the rest.", 1);
    add_ask(({"buy", "purchase", "collect", "retrieve", "pick up", "get item"}), 
      "say If su want your item, su should 'check order' to find out if "+
      "it is ready." ,1);  
    add_ask(({"cancel", "stop"}), 
      "say Su may use 'cancel order'", 1);
    add_ask(({"suggestion", "suggestions"}), "say Please submit an idea report "+
      "on me or my merchandise and hopefully it will be done soon.", 1);

    // possible names for the item sold
    craftsman_set_sold_item_names(({ "cravat", "neckcloth", "neckerchief", 
	"scarf", "item", "neck-wear", "ascot"}));
}

public void
craftsman_configure_order(int order_id, string arg)
{
    // the file for the item to clone
    craftsman_set_item_file(order_id, V_OBJ + "custom_neck");

    // time in seconds to complete creation of the item
    craftsman_set_time_to_complete(order_id, 30 + random(35));

    // the cost of an item (in cc)
    craftsman_set_item_cost(order_id, 188 + random(144));

    craftsman_add_attribute(order_id, "style",
      ({ "ascot", "cravat", "neckcloth", "neckerchief", "scarf" }));
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
	"crested", "crisp", "distressed", "elegant", "embroidered",
	"exquisite", "faded", "flowered", "flowing", "fringed", "gaudy", 
	"gorgeous", "heavy", "heirloom", "hideous", "ironed", "laced", "long",
	"loose", "loud", "luxurious", "ornate", "opulent", "paisley", "piped",
	"plain", "pleated", "plush", "pressed", "quilted", "ruffled", "sheer",
	"short", "simple", "slender", "snug", "sparkling", "striped", "ribbed",
	"rich", "rough", "tasseled", "tasteful", "thin", "unadorned", "ugly", 
	"warm", "wrinkled", "none"
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
	command("say to "+ oname +" Celebrate the Source.");
	command("say to "+ oname +
	    " May ae offer you a cravat, or perhaps a scarf?");
    }
    else
    {
	command("say to "+ oname +
	    " My, my, they sure make them big in the Outlands.");
    }
}
