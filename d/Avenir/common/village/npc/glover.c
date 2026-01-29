// file name:	/d/Avenir/common/village/npc/glover.c
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
    return "She is a glover well-known for the quality and variety "+
	"of gloves that she produces.\n"+
	"She is wearing a brooch bearing the sigil of her House: a "+
	"fire lizard on a field of black, bordered in green.\n"+
	"Her long hair is held away from her face by two braids "+
	"fastened at her nape in a serpentine knot.\n"+
	"She has a small, dimpled chin and warm hazel eyes.\n";
}

static void
create_merchant(void)
{
    set_name("eramia");
    set_living_name("eramia");
    add_name(({"glover", "merchant" }));
    set_race_name("gnome");
    set_gender(1);
    set_title("icu Ra'let, of the Glovers of Ra'let");
    set_adj(({"delicate"}));

    set_act_time(4);
    add_act("emote measures out some fabric.");
    add_act("emote sews fine stitches into a black lace glove.");
    add_act("emote smiles dreamily as she rubs a piece of satin "+
      "between her fingertips.");
    add_act("emote laces her fingers together and stretches "+
      "her arms above her head.");
    set_chat_time(9);
    add_chat("Ae make gloves specially for each customer.");
    add_chat("Ae am always looking for suggestions on how ae can "+
      "improve my selection.");

    add_ask(({"gloves", "order", "merchandise"}),
      "say Ae make gloves. If su want a pair, just 'order gloves' and ae "+
      "will prompt su for the rest.", 1);
    add_ask(({"buy", "purchase", "collect", "retrieve", "pick up", "get gloves"}),
      "say If su want your gloves, su should 'check order' to find out if "+
      "it is ready." ,1);
    add_ask(({"cancel", "stop"}),
      "say If su do not want gloves, su may 'cancel order'", 1);
    add_ask(({"suggestion", "suggestions"}), "say Please submit an idea report "+
      "on me or my gloves and hopefully it will be done soon.", 1);

    // possible names for the item sold
    craftsman_set_sold_item_names(({ "gloves", "mittens", "item" }));
}

public void
craftsman_configure_order(int order_id, string arg)
{
    // the file for the item to clone
    craftsman_set_item_file(order_id, V_OBJ + "custom_gloves");

    // time in seconds to complete creation of the item
    craftsman_set_time_to_complete(order_id, 30 + random(35));

    // the cost of an item (in cc)
    craftsman_set_item_cost(order_id, 188 + random(144));

    craftsman_add_attribute(order_id, "style",
      ({ "gloves", "mittens" }));
    craftsman_add_attribute(order_id, "material",
      ({ "cambric", "chamois", "flannel", "homespun", "lace", "leather",
	"linen", "muslin", "samite", "satin", "silk", "suede", "velvet",
	"webcloth", "wool"
      }));
    craftsman_add_attribute(order_id, "size",
      ({ "small", "large", "medium", "long", "short", "high", "low", "none" }));
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
    ob->set_size(attrs["size"]);
    ob->set_colour(attrs["colour"]);
    ob->set_fabric(attrs["material"]);

    ob->create_tailored();
    command("say Pashat your new gloves.");
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
	command("say to "+ oname +" Intios, citizen.");
	command("say to "+ oname +
	    " May ae make su a pair of gloves?");
    }
    else
    {
	command("say to "+ oname +
	    " Greetings Outlander. Are su here to order gloves made?");
    }
}
