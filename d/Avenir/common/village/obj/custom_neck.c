// -*-C++-*-
// file name: 	  /d/Avenir/common/village/obj/custom_neck.c
// creator(s):	  Lilith Jan 2004
// last update:	  
// 		Lucius Oct 2008: Massive cleanup / rewrite.
//
// purpose:         
// note:      
// bug(s):
// to-do:  dance with scarves
#pragma strict_types

#include "custom.h"
inherit CUSTOM_BASE;

mapping style_desc = ([       
   "ascot"       : ({ "ascot",
	"This is a form of cravat or neck scarf knotted "+
	"so that its wide, square ends lie flat, one upon the "+
	"other, secured in place with a small pearlescent pin."
   }),
   "cravat"      : ({ "cravats",
	"This is a formal style of neckwear worn "+
	"in a slipknot with long ends overlapping vertically "+
	"in front, producing the effect of a cascade of cloth."
   }),
   "neckcloth"   : ({ "neckcloths",
	"This is a rectangular piece of finest "+
	"fabric, worn wrapped entirely about the neck with "+
	"the ends tucked out of sight."
   }),
   "neckerchief" : ({ "neckerchiefs",
	"This is a square of fine fabric, folded "+
	"into a triangle and worn casually tied about the neck "+
	"with the ends entending out from the knot."
   }),
   "scarf"       : ({ "scarves",
	"This article of dress is of a light and "+
	"decorative character, worn loosely about the neck and "+
	"turned so that it drapes the back, shoulder or breast."
   }),
]);

public string
tag_item(void)
{
    string str = "When worn, you can use 'neckfuss' and "+
	"'neckadjust' emotions. When not worn, you can use "+
	"'necktie' to tie someone's hands, feet, eyes, or mouth, "+
	"or to simply tie it around someone's neck.\n";

    if (style == "scarf")
    {
	str += "\nAs a special treat you can also do 'neckdance'. "+
	    "Repeat it as often as you like, there are several "+
	    "dance moves available.\n";
    }

    return str;
}

private string
long_desc(void)
{
    return "This "+ short() +" is an example of fine sybarite "+
	"craftsmanship. The "+ style +" has been cut from "+
	fabric_type[fabric][1] +" and dyed "+ colour +". "+
	style_desc[style][1] +" "+ fabric_type[fabric][2] +
	" An unobtrustive tag supplies instructions for  "+
	"using this "+ style +".\n";
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
    config_wearable_item(A_NECK, 1, 15, this_object());
    set_name("neckcloth");

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

    write("You fuss with the fit of the "+ short() +
	" around your neck.\n");
    allbb(" fusses a bit with "+ POSSESS(TP) +
	" "+ short() +".");

    return 1;
}

public int
do_adj(string str)
{
    if (!query_worn())
	return notify_fail("You need to be wearing the "+ short() +".\n");

    string *how = parse_adverb_with_space(str, "idly" , 0);

    if (strlen(how[0]))
	return notify_fail("Only adverbs may be specified.\n");

    write("You" + how[1] + " adjust the way your "+ short() +
	" drapes around your neck, smoothing it into place.\n");
    allbb(how[1] + " adjusts the way "+ POSSESS(TP) +" "+
	short()+" is draped around "+ POSSESS(TP) +" neck, "+
	"smoothing it into place.", how[1]);

    return 1;
}

public int
do_tie(string str)
{
    object *oblist;
    string *zones;
    string *parts;
    int    size;
    string location;

    if (query_worn())
    {
        notify_fail("You cannot do that while wearing it.\n");
        return 0;
    }

    zones = ({ "hands", "wrists", "feet", "ankles", "mouth", "neck", "eyes" });

    str = (strlen(str) ? lower_case(str) : "neck");
    if (member_array(str, zones) != -1)
    {
        write("You tie the "+ short() +" around your "+ str + ".\n");
        all(" ties "+ this_player()->query_possessive() +" "+ short() + 
            "around "+ this_player()->query_possessive() + " " + str + ".",
           "");
        this_player()->command("$wear neckcloth");
        return 1;
    }

    parts = explode(str, " ");
    if ((size = sizeof(parts)) > 1)
    {
        if (member_array(parts[size - 1], zones) != -1)
        {
            location = parts[size - 1];
            str = implode(parts[..(size - 2)], " ");
        }
    }

    /* When tying it on someone else, tie on the neck by default. */
    if (!stringp(location))
    {
        location = "neck";
    }

    oblist = parse_this(str, "[the] %l [on] [his] / [her]");
    if (!sizeof(oblist))
    {
        notify_fail("Tie [whom] [where]?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You may only do that to a single target.\n");
        return 1;
    }

    actor("You tie", oblist, "'s "+ location +" up with the "+ short() +".");
    all2act(" ties", oblist, "'s "+ location +" up with the "+ short() +".");
    target(" ties your " + location + " up with "+ POSSESS(TP) +" "+ short() +
        ".", oblist, "");

    this_object()->move(oblist[0], 1);
    return 1;
}

private static int dint;

public int
do_ndance(string str)
{
    if (query_worn())
    {
	notify_fail("You cannot do that while wearing the "+ short() +".\n");
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

    add_action(do_fuss,"neckfuss");
    add_action(do_adj, "neckadjust");
    add_action(do_tie, "necktie");
    
    if (style == "scarf")
        add_action(do_ndance, "neckdance");
}
