// file name:	/d/Avenir/common/village/npc/furrier.c
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
    return "He is a furrier. He has made himself and his House quite "+
	"wealthy selling fur garments to anyone who can afford them.\n"+
	"He is wearing a brooch bearing the sigil of his House: a gold "+
	"cat on a field of brown, bordered in green.\n"+
	"His long, wavy hair hangs loose and unrestrained, framing "+
	"a gaunt face with rounded cheeks and astute eyes.\n"+
	"His beard is parted and tied in two braids, revealing an "+
	"ornate cravat tied around his neck.\n";
}

static void
create_merchant(void)
{
    set_name("charbuno");
    set_living_name("charbuno");
    add_name(({"furrier", "merchant", "fur seller" }));
    set_race_name("gnome");
    set_gender(0);
    set_title("icu Vyis, the Master Furrier");
    set_adj(({"wealthy"}));

    set_act_time(4);
    add_act("emote strokes a mink stole.");
    add_act("emote smoothes the braids of his beard.");
    add_act("emote ");
    add_act("emote ");
    add_act("emote ");

    set_chat_time(9);
    add_chat("Ae will make su a fur coat.");
    add_chat("Su have but to 'order item' and soon su shall "+
      "have it.");
    add_chat("If su want to collect you purchase, simply "+
      "'check order' and if it is ready su shall have it.");
    add_chat("Most of our furs are from northern Terel. "+
      "The forests and snow fields are excellent sources "+
      "of quality pelts.");

    add_ask(({"item", "coat", "jacket", "tippet", "stole", "boa"}), 
      "say Ae make fur outer-garments. If su one, just 'order item' and ae "+
      "will prompt su for the rest.", 1);
    add_ask(({"buy", "purchase", "collect", "retrieve", "pick up", "get item"}), 
      "say If su want your item, su should 'check order' to find out if "+
      "it is ready." ,1);  
    add_ask(({"cancel", "stop"}), 
      "say Su may use 'cancel order'", 1);
    add_ask(({"suggestion", "suggestions"}), "say Please submit an idea report "+
      "on me or my merchandise and hopefully it will be done soon.", 1);

    // possible names for the item sold
    craftsman_set_sold_item_names(({ "item", "coat", "jacket", "tippet", 
	"stole", "robe", "boa"}));
}

public void
craftsman_configure_order(int order_id, string arg)
{
    // the file for the item to clone
    craftsman_set_item_file(order_id, V_OBJ + "custom_fur");

    // time in seconds to complete creation of the item
    craftsman_set_time_to_complete(order_id, 30 + random(35));

    // the cost of an item (in cc)
    craftsman_set_item_cost(order_id, 1880 + random(1440));

    craftsman_add_attribute(order_id, "style",
      ({ "boa", "coat", "jacket", "robe", "stole", "tippet" }));
    craftsman_add_attribute(order_id, "fur",
      ({ "beaver", "chinchilla", "ermine", "fitch", "fox", "lamb", "lynx",
	"mink", "ondatra", "rabbit", "sable", "sheepskin", "weasel", "wolf"
      }));
    craftsman_add_attribute(order_id, "colour",
      ({ "black", "gray", "silver", "white", "cream", "ivory", "tan", 
	"tawny", "beige", "golden", "amber", "blue", "orange", "red", "copper", 
	"russet", "chestnut", "brown", "chocolate", "fawn", "mahogany", 
	"umbre"
      }));
    craftsman_add_attribute(order_id, "trim",
      ({ "beads", "brocade", "embroidery", "fringe", "tassels", 
	"satin", "silk", "samite", "velvet",
	"beaver", "chinchilla", "ermine", "fitch", "fox", "lamb", "lynx",
	"mink", "ondatra", "rabbit", "sable", "sheepskin", "vair",
	"weasel", "wolf", "none"
      }));
    craftsman_add_attribute(order_id, "colour2",
      ({ "black", "gray", "silver", "white", "cream", "ivory", "tan", 
	"tawny", "beige", "golden", "amber", "blue", "orange", "red", "copper", 
	"russet", "chestnut", "brown", "chocolate", "fawn", "mahogany", 
	"umbre", "brindle", "none"
      }));
}

public void
craftsman_configure_item(object ob, mapping attrs, int order_id)
{
    ob->set_style(attrs["style"]);
    ob->set_fur(attrs["fur"]);
    ob->set_colour(attrs["colour"]);
    ob->set_trim(attrs["trim"]);
    ob->set_col2(attrs["colour2"]);

    ob->create_tailored();
    command("say Ae think su will be very pleased with your purchase "+
      "of "+ ob->short() +". Pashat!");
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
	    " Would su like a fur coat? Or a robe, perhaps?");
    }
}
