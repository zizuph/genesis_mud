// file name:	/d/Avenir/common/village/npc/hosier.c
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
    return "She is a clothier who specializes in making hosiery.\n"+
	"She is wearing a scarf bearing the sigil of her House: "+
	"a white cygnet on a field of blue, bordered in crimson.\n"+
	"Her hair is combed back and twisted into an elegant knot, "+
	"revealing pointed ears.\n"+
	"Her wide, dark eyes speak volumes about her sensitive nature.\n";
}

static void
create_merchant(void)
{
    set_name("gilibeth");
    set_living_name("gilibeth");
    add_name(({"hosier", "merchant", "hose maker" }));
    set_race_name("half-elf");
    set_gender(1);
    set_title("ini Cimron, of the Hosiers of House Cimron");
    set_adj(({"sensitive"}));

    set_act_time(4);
    add_act("emote measures out some fabric.");
    add_act("emote darns the heel of a stocking.");
    add_act("emote moves about with unconscious grace.");
    add_act("emote smiles shyly, keeping her eyes lowered modestly.");
    add_act("emote tucks a stand of hair behind her ear.");

    set_chat_time(9);
    add_chat("Ae can make hose, stockings, tights, and socks.");
    add_chat("Su have but to 'order item' and soon su shall "+
      "have what su desire.");
    add_chat("Su may 'check order' any time to find out if it is ready.");

    add_ask(({"item","stockings","tights","socks","hose","hosiery","sell","make"}), 
      "say Ae make hosiery. If su some made, just 'order item' and ae "+
      "will prompt su for the rest.", 1);
    add_ask(({"buy", "purchase", "collect", "retrieve", "pick up", "get item"}), 
      "say If su want your item, su should 'check order' to find out if "+
      "it is ready." ,1);  
    add_ask(({"cancel", "stop"}), 
      "say Su must use 'cancel order'", 1);
    add_ask(({"suggestion", "suggestions"}), "say Please submit an idea report "+
      "on me or my merchandise and hopefully it will be done soon.", 1);

    // possible names for the item sold
    craftsman_set_sold_item_names(({ "item","stockings","tights","socks",
	"hose","hosiery"}));
}

public void
craftsman_configure_order(int order_id, string arg)
{
    // the file for the item to clone
    craftsman_set_item_file(order_id, V_OBJ + "custom_hosiery");

    // time in seconds to complete creation of the item
    craftsman_set_time_to_complete(order_id, 30 + random(35));

    // the cost of an item (in cc)
    craftsman_set_item_cost(order_id, 144 + random(24));

    craftsman_add_attribute(order_id, "style",
      ({ "stockings", "tights", "socks", "hose" }));
    craftsman_add_attribute(order_id, "material",
      ({ "lace", "linen", "satin", "silk", "webcloth", "wool" }));
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
	command("say to "+ oname +" Ae am pleased to see you.");
    }
}
