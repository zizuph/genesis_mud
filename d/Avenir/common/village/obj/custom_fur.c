// -*-C++-*-
// file name: 	  /d/Avenir/common/village/obj/custom_fur.c
// creator(s):	  Lilith Jan 2004
// last update:	  
// 		Lucius Oct 2008: Massive cleanup / rewrite.
//
// purpose:         
// note:      
// bug(s):
// to-do:  
#pragma strict_types

#include "custom.h"
inherit CUSTOM_BASE;

public static string fur, trim, colour2;

public void set_fur(string str)      { fur = mystr(str);     }
public void set_trim(string str)     { trim = mystr(str);    }
public void set_col2(string str)     { colour2 = mystr(str); }
public string query_fur(void)        { return fur;           }
public string query_trim(void)       { return trim;          }
public string query_col2(void)       { return colour2;       }

mapping style_desc = ([    
   "stole"  : ({ "stoles",
	"This stole is very like a scarf, in "+
	"that it is a very loose-fitting and flowing garmet. "+
	"It is, however, made from fur, and thus much thicker "+
	"and more luxurious than a scarf would be."
   }),
   "jacket" : ({ "jackets",
	"This fur jacket is an outer garment "+
	"with long sleeves that covers the body from the "+
	"shoulders to the upper thigh. It is lighter-weight "+
	"than a coat, but still significantly heavy. It "+
	"is lined with velvet."
   }),
   "coat"   : ({ "coats",
	"This fur coat is an outer garment with "+
	"long sleeves that covers the body from shoulder "+
	"to ankle. It is heavy and extremely luxurious, "+
	"being lined on the inside with satin."
   }),
   "boa"    : ({ "boas",
	"This fur boa is a very long, thin form of "+
	"scarf used as a luxury fashion accessory."
   }),
   "tippet" : ({ "tippets",
	"This tippet is a fur shoulder cape with "+
	"long ends that hang in the front. It is lined with "+
	"webcloth, which resembles silk in appearance and "+
	"luxury."
   }),
   "robe"   : ({ "robes",
	"This robe is an ankle-length, loose, flowing "+
	"outer garment with wide, three-quarter sleeves. It "+
	"is lined with highest-quality satin for the "+
	"ultimate in luxurious comfort."
   }),
]);  

mapping fur_desc = ([
   "beaver"     : ({ "beaver",
	"The beaver fur has been sheared to expose "+
	"the soft, velvety texture of the underfur. This part"+
	"iclar type of fur is very durable, holding its plush "+
	"even with hard use."
   }),
   "chinchilla" : ({ "chinchilla",
	"A short, dense, soft fur with lustrous "+
	"guard hairs and dark underfur, chinchilla fur is rarer "+
	"than sable and softer to the touch than any other "+
	"fur that is used in garments."
   }),
   "ermine"     : ({ "ermine",
	"The guard hairs of ermine are very silky, "+
	"while the underfur is extremely dense. The animal "+
	"this fur comes from turns white in the winter, except "+
	"for the tip of the tail, which is black."
   }),
   "fitch"      : ({ "fitch",
	"Fitch is a beautiful fur. In its natural "+
	"state the colour ranges from pale beige to orange tones, "+
	"with black markings. Very similar to mink, it has "+
	"long guard hairs over lighter colored underfur."
   }),
   "fox"        : ({ "fox ",
	"Fox comes in the widest range of natural colors "+
	"of any fur except mink. It has long, lustrous guard "+
	"hairs with a thick, soft underfur."
   }),
   "lamb"       : ({ "lamb",
	"The flashiest of furs, sybarun lamb is the only "+
	"long-haired fur that is curly. It has very long, wavy, "+
	"silky guard hairs. It's natural color is off-white, "+
	"but it is often dyed."
   }),
   "lynx"       : ({ "lynx",
	"This is the fur from the short-tailed wildcat "+
	"known as a lynx. This is perhaps the longest-haired "+
	"fur in use for garments, having an underfur that is "+
	"longer than the guard hairs of most others. Wearing "+
	"lynx is known to make people feel very feline, slinky, "+
	"and spoiled."
   }),
   "mink"      : ({ "mink",
	"The most popular of all furs, mink is soft "+
	"and lightweight, with lustrous guard hairs and dense, "+
	"soft underfur. Female pelts are smaller in size and "+
	"have a softer, silkier feel than the larger male pelts."
   }),
   "ondatra"   : ({ "ondatra",
	"This fur is full and thick, with a black "+
	"stripe and a pale beige side. The underfur of the "+
	"ondatra is nearly as long as the guard hairs are."
   }),
   "rabbit"    : ({ "rabbit",
	"Rabbit fur is generally formed of medium "+
	"length guard hairs in a variety of natural colors. "+
	"It is not very durable, and sheds easily."
   }),
   "sable"     : ({ "sable",
	"Sable has long, luxurious guard hairs with "+
	"dense underfur, yet it is very lightweight. Its silky "+
	"quality and the silver-tinted guard hairs makes this "+
	"a much sought-after fur."
   }),
   "sheepskin" : ({ "sheepskin",
	"This is the tanned skin of a sheep with "+
	"the fleece left on. It has been sheared close to reduce "+
	"its weight.  Sheepskin is perhaps the most durable of "+
	"all pelts in use for garments today."
   }),
   "vair"      : ({ "vair",
	"This is the fur of the squirrel, much used since "+
	"ancient times as the trim on garments, particularly "+
	"the raiment of kings and nobles. Vair has a short under"+
	"fur in a range of colours, with longer, pale guard hairs."
   }),
   "weasel"    : ({ "weasel",
	"The pelt of the weasel looks very similar "+
	"to mink, with short guard hairs and a semi-dense "+
	"underfur. It is also known as Terel mink."
   }),
   "wolf"      : ({ "wolf",
	"The wolf's pelt is a long-haired fur, often "+
	"pale gray or tan in color, with thick, soft underfur. "+
	"It is very durable. It is used often in men's garments "+
	"or as an accent fur for cuffs, collars, and hoods."
   }),
]);  


public static string *furs   = m_indices(fur_desc);
public static string *styles = m_indices(style_desc);


private string
long_desc(void)
{
    string str = " This "+ short() +" is an example of fine sybarite "+
	"craftsmanship. The "+ style +" is made of "+ colour +" "+
	fur +". "+ fur_desc[fur][1] +" "+ style_desc[style][1];

    if (strlen(trim))
    {
	str += " The sheer opulence of the "+ style +" is "+
	    "enhanced even further by the "+ trim +" added to the trim.";
    }

    return str +"\n";
}

private string
short_desc(void)
{
    string str = colour +" "+ fur +" "+ style;

    if (!strlen(trim))
	return str;
    if (!strlen(colour2))
	return str +" trimmed in "+ trim;
    else
        return str +" trimmed in "+ colour2 +" "+ trim;
}

public void
create_tailored(void)
{
    ::create_tailored();

    set_adj(({ colour, fur, colour2, trim }));        
    add_name(({ style, style_desc[style][1] }));     
    set_pname(style_desc[style][0]);
    remove_pname(style);

    add_item(fur, fur_desc[fur][1] +"\n");
    add_item(({"guard hairs", "guard hair"}), 
       "Guard hairs are the longer hairs on top of the fur.\n");
    add_item(({"underfur", "under fur" }),
        "Underfur is the thick lower layer of the fur.\n");

    switch (style)
    {
        case "boa":
            config_wearable_item(A_NECK, 1, 15, this_object());
            break;
        case "stole":
            config_wearable_item(A_SHOULDERS, 1, 15, this_object());
            break;
        case "tippet":
            config_wearable_item(A_SHOULDERS, 1, 15, this_object());
            break;
        case "jacket":
            config_wearable_item(A_ROBE, 1, 15, this_object());
            break;
        case "coat":
            config_wearable_item(A_ROBE, 1, 15, this_object());
            break;
        case "robe":
            config_wearable_item(A_ROBE, 1, 15, this_object());
            break;
    }

    switch (trim)
    {
        case "beaver":
        case "chinchilla":
        case "ermine":
        case "fitch":
        case "fox":
        case "lamb":
        case "lynx":
        case "mink": 
        case "ondatra": 
        case "rabbit": 
        case "sable": 
        case "sheepskin":
        case "weasel":
        case "wolf": 
            add_item(trim, fur_desc[trim][1] +
                " It has been artfully added as trim, "+
                "contributing to the overall luxury and aesthetic "+
                "value of the garment.\n");
            break;
        default:
            add_item(trim, "It has been artfully added as trim, "+
                "contributing to the overall luxury and aesthetic "+
                "value of the garment.\n");
            break;
    }
}
  
public void
create_object(void)
{
    ::create_object();
    config_wearable_item(A_TORSO, 1, 15, this_object());
    set_name("fur");
}

public void
custom_recover(string arg)
{
    string foobar;
    sscanf(arg, "#T#%s#F#%s#C2#%s#s",
	trim, fur, colour2, foobar);
}

public string
query_custom_recover(void)
{
    return "#T#"  + trim +
	   "#F#"  + fur +
	   "#C2#" + colour2 + "#";
}
