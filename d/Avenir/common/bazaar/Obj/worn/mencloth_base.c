// -*-C++-*-
// file name: 	  /d/Avenir/common/bazaar/Obj/cloak/cloth_base.c
// creator(s):	  Lilith Aug 1997
// last update:	  
// 		  Lucius May 2007: Cleanups and fixes
// 		  Lucius Oct 2008: More cleanups / refactoring.
// 		  Lucius Jun 2017: Add some new colours.
//        Lilith May 2022: converted to item_expiration.
//
// purpose:         Keep the mappings and arrays seperate.
// note:      
// bug(s):
// to-do:
// XXXXXXXXXXXXX  Fix intr/mens_shop to use variables without inherit.
#pragma strict_types

#include "mencloth.h"

inherit "/std/object";
inherit "/lib/commands";
inherit "/lib/wearable_item";

public static string desc, type, style, substyle, colour;

public mapping fabric_type = ([
   "chamois"  : ({ 5, "chamois",
		"The chamois is a very soft, pliable leather dressed "+
		"with expensive, scented oils that lend a water-"+
		"resistent quality."
   }),
   "linen"    : ({ 2, "linen",
		"This simple yet elegant fabric is made from spun "+
		"flax-fiber woven very fine. It is a very comfortable, "+
		"if easily wrinkled, garment."
   }),
   "leather"  : ({ 10, "leather",
		"This leather comes from the tiny deer native to the "+
		"Sybarus Holm. It has been tanned to bring out the fine "+
		"grain, texture and suppleness of the skin."
   }),
   "samite"   : ({ 9, "samite",
		"This samite cloth is composed of very heavy silk "+
		"fibers interwoven with strands of silver."
   }),
   "satin"    : ({ 3, "satin",
		"Perfect, glossy satin made with painstakingly-woven "+
		"silker threads."
   }),
   "silk"     : ({ 2, "silk",
		"The luxury of silk is unsurpassed by any other "+
		"fabric. This particular cloth is of the highest-"+
		"quality weave, making it both lustrous and durable."
   }),
   "suede"    : ({ 9, "suede",
		"The suede is made from kid leather of the highest "+
		"quality that has been carefully abraded so as to "+
		"raise a fine, soft nap on the material."
   }),
   "velvet"   : ({ 5, "velvet",
		"This velvet is very plush, and so carefully woven "+
		"that you are unable to see the individual loops "+
		"of silk which form the soft, slightly napped surface."
   }),
   "webcloth" : ({ 15, "webcloth",
		"The webcloth material has the appearance and "+
		"lightness of silk, but is very strong and resistant "+
		"to tearing. It is known to be an extremely rare and "+
		"thus rather expensive material."
   }),
   "wool"     : ({ 12, "wool",
		"This cloth is made of finely spun wool from the "+
		"sybarun goat, whose fleece is long and silky soft."
   }),
]);  

public string *colours = ({
	"azure", "beige", "black", "blue", "charcoal", "cream",
	"crimson", "cyan", "gold", "green", "gray",
	"ivory", "orange", "pink", "purple", "red", "rose",
	"silver", "teal", "violet", "white", "yellow",
});
public string * query_colours(void)	{ return colours; }

public string *descs = ({
	"brocaded", "crested", "distressed", "elegant", "faded",
	"flowing", "gaudy", "heavy", "laced", "light", "long", "loose",
	"luxurious", "ornate", "plush", "quilted", "sheer", "simple",
	"short", "snug", "tasteful", "unadorned", "thin", "warm"
});
public string * query_descs(void)	{ return descs; }

public string *styles = ({ "pants", "shirts", "cloaks" });
public string * query_styles(void)	{ return styles; }

public string *pants  = ({ "breeches", "bottoms", "leggings",
			   "pants", "tights", "trousers" });
public string * query_pants(void)	{ return pants; }

public string *shirts = ({ "blouse", "poet blouse", "shirt" });
public string * query_shirts(void)	{ return shirts; }

public string *cloaks = ({ "cape", "cloak", "mantle", "robe" });
public string * query_cloaks(void)	{ return cloaks; }

public string *types = m_indices(fabric_type);
public string * query_types(void)	{ return types; }

static string
mystr(string str)	{ return (str == "none" ? "" : str);    }

public void set_desc(string str)     {  desc = mystr(str);      }
public void set_type(string str)     {  type = mystr(str);      }
public void set_style(string str)    {  style = mystr(str);     }
public void set_substyle(string str) {  substyle = mystr(str);  }
public void set_colour(string str)   {  colour = mystr(str);    }

public string query_desc()           {  return desc;            }
public string query_type()           {  return type;            }
public string query_style()          {  return style;           }
public string query_substyle()       {  return substyle;        }
public string query_colour()         {  return colour;          }

public mapping
query_fabric_map(void)	{ return fabric_type; }

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

public void
leave_env(object dest, object old)
{
    ::leave_env(dest, old);
    wearable_item_leave_env(dest, old);    
}

static string long_desc(void)	{ }
static string short_desc(void)	{ }

public void
create_tailored(void)
{
    if (!strlen(desc))
	desc = "";

    if (!strlen(type))
        type = one_of_list(types);

    if (!strlen(colour))
        colour = one_of_list(colours);

    set_adj(colour);
    if (strlen(desc))
        set_adj(desc);

    set_name(substyle);
    add_name(fabric_type[type][1]);

    set_short(short_desc);
    set_long(long_desc);
    
    add_prop(OBJ_I_VALUE,
	(fabric_type[type][0] * 10) + 200 + random(100));
}

public void
create_object(void)
{
    set_name("garment");
    add_pname(({"clothes", "clothing"}));
    add_adj(({"custom", "sybarun", "sybarite"}));

    add_item(({ "plate", "copper plate", "inseam" }), 
        "It is a polished copper plate that has been riveted "+
        "to the inseam in an unobtrusive place.\n");
    add_cmd_item(({ "plate", "copper plate", "inseam", "engraving",
        "words", "letters" }), "read",
	"It is a polished copper plate with the words:\n"+
	"    Hand tailored by Emarus the Tailor of Sybarus.\n");
    add_item(({"rivet", "rivets"}), "There are two small "+
        "rivets fastening the copper plate to the inseam "+
        "of the "+ short() +".\n");

    add_prop(OBJ_I_WEIGHT, 200 + random(200));
    add_prop(OBJ_I_VOLUME, 400 + random(100));
    add_prop(OBJ_M_NO_SELL, "It is of purely sentimental value.\n");

    set_looseness(20);
    set_layers(2);
	
    if (IS_CLONE)
      set_item_expiration();  	
}

public void
init_recover(string arg)
{
    string foo;
    sscanf(arg, "%s#SUBSTYLE#%s#TYPE#%s#COLOUR#%s#DESC#%s#%s",
	arg, substyle, type, colour, desc,foo);

    create_tailored();
    init_item_expiration_recover(foo);
}

public string
query_recover(void)
{
    return MASTER + ":#SUBSTYLE#" + substyle + 
                         "#TYPE#" + type     + 
                       "#COLOUR#" + colour   + 
                         "#DESC#" + desc +
                         "#" + query_item_expiration_recover();
}

