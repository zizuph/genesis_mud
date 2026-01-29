/*
 * Trinket given to Abeni by Finwe as a wedding gift. 
 * Approved by Tomas, the AoD
 */


inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/cmd/std/command_driver";

#include "/d/Shire/sys/defs.h"
#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <options.h>
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

#define BRACELET_SUBLOC "_bracelet_subloc_"
 
//public int send_msg(string str);

 
public void
create_object(){
    set_name("bracelet");
    add_adj(({"priceless", "silver"}));
    set_short("priceless silver bracelet");
    set_long("This is a beautiful priceless silver bracelet, composed " +
        "of many small square segments. Each segment holds a small " +
        "diamond which catch the light, creating a dazzling light display " +
        "around each stone. The braclet seems to glow with a halo of " +
        "white light. A tiny tag hangs from the bracelet.\n");
    add_item(({"small diamonds", "small diamonds"}),
        "The small diamonds are perfectly cut and multi-faceted. " +
        "Each is set in the center of a segment and polished to a " +
        "brilliant luster. They catch light and refract it around " +
        "the stone, creating a halo of white light. The center of " +
        "each gem seems to glow with a life all its own.\n");
    add_item(({"segment", "segments", "square segment", "square segments", 
            "small square segments", "small segments", 
            "small square segment", "small segment"}),
        "Each square segment is made of pure silver. They are " +
        "polished individually and sparkle in the light. Set in " +
        "the center of each segment is a small diamond.\n");
    add_item("tag", "It is small and rectangular. On the tag you read:\n" +
        "\tbshake - Shake wrist\n"+
        "\tbtoss  - Toss bracelet in the air\n");
 
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
 
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_WEIGHT);

    set_slots(A_R_HAND);
    set_layers(0);
    set_looseness(0);

}
 
 
public string
query_auto_load()
{
    return MASTER + ":";
}
 
public string
query_recover()
{
    return 0;
}

void init() 
{
    add_action("bshake","bshake");
    add_action("btoss", "btoss");
}

int bshake(string str)
{
    if(!query_worn())
    {
		TP->catch_msg("You must be wearing the bracelet.\n");
        return 1;
    }
    say(QCTNAME(TP) + " shakes" + HIS_HER(TP) + " wrist a little, causing "+ 
        HIS_HER(TP)+" " + short() + " to rattle slightly and musically.\n"); 
    TP->catch_msg("You shake your wrist a little, causing the " + short() + 
        " to rattle slightly and musically. \n");
    return 1;
}                 

int btoss(string str)
{
    if(query_worn())
    {
        TP->catch_msg("You must remove the bracelet first.\n");
        return 1;
    }
    say(QCTNAME(TP) + " tosses " + HIS_HER(TP) + " up in the air. The " +
        "diamonds glitter in the light, then fall lightly into " + 
        HIS_HER(TP) + " hand.\n"); 
    TP->catch_msg("You toss the " + short() + " into the air. The diamonds " +
        "glitter in the air, then fall lightly into your hand.\n");
    return 1;
}                 


/*
 * Function name: wear
 * Description  : This function is called when someone tries to wear
 *                this item. 
 * Arguments    : object obj - The armour we want to wear.
 * Returns      : int  0 - The item can be worn normally.
 *                     1 - The item can be worn, but print no messages.
 *                    -1 - The item can't be worn, use default messages.
 *                string - The item can't be worn, use this message.
 */
public mixed
wear(object obj)
{
    if (wearer != environment(this_object()))
    {
        return 0;
    }

    write("You slide the " + short() + " onto your right wrist and shake " +
        "your hand slightly.\n");
    say(QCTNAME(this_player()) + " slides a " + short() + " onto  " +
        this_player()->query_possessive() + " right wrist and shakes " +
        "it slightly.\n");

    this_player()->add_subloc(BRACELET_SUBLOC, this_object());
    return 1;
}


 /*
 * Function name: remove
 * Description  : This function is called when someone tries to remove
 *                this item.
 * Arguments    : object obj - The item to remove.
 * Returns      : int  0 - Remove the item normally.
 *                     1 - Remove the item, but print no messages.
 *                    -1 - Do not remove the item, print default message.
 *                string - Do not remove the item, use this message.
 */
public mixed
remove(object obj)
{
    if (wearer != environment(this_object()))
    {
        return 0;
    }

    wearer->catch_msg("You remove the "+short()+" from wrist.\n");
    tell_room(environment(wearer), QCTNAME(wearer) + " removes a " + short() + 
        " from "+wearer->query_possessive()+" wrist.\n", wearer);

    this_player()->remove_subloc(BRACELET_SUBLOC, TO);
    return 1;
}

/*
 * Function name: show_subloc
 * Description  : Shows the specific sublocation description for a living.
 * Arguments    : string subloc  - the subloc to display.
 *                object on      - the object to which the subloc is linked.
 *                object for_obj - the object that wants to see the subloc.
 * Returns      : string - the subloc description.
 */
public string
show_subloc(string subloc, object on, object for_obj)
{
    if ((on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS)) ||
      (subloc != BRACELET_SUBLOC))
    {
	return TP->show_subloc(subloc, on, for_obj);
    }

    return (((for_obj == on) ? "You are" :
	(capitalize(on->query_pronoun()) + " is")) + " wearing a " + short() + 
        ". It shakes and shimmers with every movement.\n");
}

string read_tag()
{
    return "On the tag you read:\n\n " +
    "bshake - Shake wrist\n"+
    "btoss  - Toss bracelet in the air\n";
}