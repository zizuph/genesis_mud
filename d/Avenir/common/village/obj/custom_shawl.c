// -*-C++-*-
// file name: 	  /d/Avenir/common/village/obj/custom_shawl.c
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

mapping style_desc = ([    
   "shawl" : ({ "shawl",
	"This particular style of shawl is a large "+
	"square of fabric, generally worn folded as into a "+
	"triangle with the base draped over the shoulders and "+
	"arms. As an outer garment it is a lightweght altern"+
	"ative to a cloak or mantle."
   }),
   "wrap"  : ({ "wrap",
	"Wraps are a common form of outer garment "+
	"usually used by women wanting to cover their necks "+
	"and shoulders for warmth or modesty. Wraps are much "+
	"lighter and use less material than cloaks and mantles."
   }),
]);

public string
tag_item(void)
{
    return "When worn, you can use 'shawlfuss' and "+
	"'shawlslip' emotions. When not worn, you can use "+
	"'shawldance'. Repeat it as often as you like, "+
	"there are several dance moves available.\n";
}

private string
long_desc(void)
{
    return "The "+ style +" has been cut from "+ fabric_type[fabric][1] +
	" and dyed "+ colour +". "+ style_desc[style][1] +" "+
	fabric_type[fabric][2] +" This "+ short() +" is an example of "+
	"fine sybarite craftsmanship. An unobtrustive tag supplies "+
	"instructions for using this "+ style +".\n";
}

public void
create_tailored(void)
{
    ::create_tailored();
    set_adj(({ desc, colour, fabric }));        
    add_name(({ style, style_desc[style][1] }));     
}
  
public void
create_object(void)
{
    ::create_object();
    config_wearable_item(A_SHOULDERS, 1, 15, this_object());
    add_item("tag", "@@tag_item");
    add_cmd_item("tag", "read", "@@tag_item");
}

/*
 * Add/mask emotions to make them more fun!
 * fuss / adjust
 */
public int
do_fuss(string str)
{
    if (!query_worn())
	return notify_fail("You need to be wearing the "+ short() +".\n");

    if (strlen(str))
	return notify_fail("No arguments are needed.\n");

    write("You fuss with the way the "+ short() +
	" drapes across your shoulders and down your back.\n");
    allbb(" fusses a bit with "+ POSSESS(TP) + " "+ short() +".");

    return 1;
}

public int
do_slip(string str)
{
    if (!query_worn())
	return notify_fail("You need to be wearing the "+ short() +".\n");

    string *how = parse_adverb_with_space(str, "idly" , 0);

    if (strlen(how[0]))
	return notify_fail("Only adverbs may be specified.\n");

    write("You" + how[1] + " let your "+ short() +" slip off "+
	"your shoulders, tucking it into the crook of your arms.\n");
    allbb("'s "+ short() +" slips down off "+ POSSESS(TP) +" "+
	"shoulders and comes to rest in the crook of "+ POSSESS(TP) +
	" arms.", how[1]);

    return 1;
}

private static int dint;

public int
do_ndance(string str)
{
    if (query_worn())
    {
        notify_fail("You cannot do that while wearing it.\n");
        return 0;
    }
  
    if (dint > 5)
        dint = 0;

        switch (dint)
        {
            case 0:
            { 
                write("You raise the "+ short() +" above your head and "+
                    "shimmy to the left.\n");
                all(" raises "+ POSSESS(TP) +" "+ short() +" above "+
                    POSSESS(TP) +" head and shimmies to the left.");
                break;
            }
            case 1:
            { 
                write("You wave the "+ short() +" above your head and "+
                    "shimmy to the right.\n");
                all(" waves "+ POSSESS(TP) +" "+ short() +" above "+
                    POSSESS(TP) +" head and shimmies to the right.");
                break;
            }
            case 2:
            { 
                write("You shake your shoulders and toss your head first "+
                    "right, then left, making the "+ short() +" ripple "+
                    "and snap.\n");
                all(" shakes "+ POSSESS(TP) +" shoulders and tosses "+
                    POSSESS(TP) +" head first right, then left, making "+
                    "the "+ short() +" ripple and snap.\n");
                break;
            }
            case 3:
            { 
                write("You twirl around and around, the "+ short() +
                    " flowing about you like a streamer in the wind.\n");
                all(" twirls around and around, the "+ short() +
                    " flowing about "+ OBJECTIVE(TP) +" like a streamer "+
                   "in the wind.\n");
                break;
            }
            case 4:
            { 
                write("You run the "+ short() +" through your fingers and "+
                   "leap into the air.\n");
                all(" runs the "+ short() +" through "+ POSSESS(TP) +
                   " fingers and leaps into the air.");              
                break;
            }
            case 5:
            { 
                write("You stamp your feet and sway to a primitive rhythm "+
                   "that drives you onward, flicking the "+ short() +
                   " rapidly.\n");
                all(" stamps "+ POSSESS(TP) +" feet and sways to a primitive "+
                   "rhythm, flicking the "+ short() +" rapidly around "+
                   OBJECTIVE(TP)+".");              
                break;
            }
        }             
        dint++;              
        return 1;
}

public void
init(void)
{
    ::init();
   
   if (environment() != this_player())
       return;

    add_action(do_fuss,"shawlfuss");
    add_action(do_slip, "shawlslip");
    add_action(do_ndance, "shawldance");
}
