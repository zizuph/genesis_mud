/*
 * A backpack found on travelling orcs in the Shire.
 * Thanks to Mercade and Elessar, who I borrowed the code from.
 * Mayhem, August 1994.
 *
 * Added new and improved pack listing
 * -- Finwe, May 2001
 */



inherit "/d/Gondor/common/guild/obj/backpack";
inherit "/d/Shire/lib/box_list";
inherit "/lib/shop";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <money.h>
#include <filter_funs.h>

#include "/d/Shire/common/defs.h"

#define NO_SELL_PROP BSN("You do not want to sell the backpack. Do " + \
    "<keep backpack> to remove the protection.")
#define NO_SELL_VBFC "@@no_sell_vbfc@@"
//   -Igneous-
//  The old _shire_orc_backpack wasn't the subloc name that the file was adding
#define BACKPACK_SUBLOC  "_ranger_backpack"

public void show_list(object for_obj, object *obarr);

void
create_container()
{
    ::create_container();

    add_prop(OBJ_I_VALUE,             432);
    remove_adj("camouflaged");
    remove_adj("green-coloured");
    add_adj(({"black", "shoddy"}));

    set_short("shoddy black backpack");
    set_long("@@long_description");
    set_name("backpack");
}

string
long_description()
{
    string long_desc = "The backpack is fairly large and poorly made, "+
 "with scraps of various black materials carelessly stitched together. "+
	"If you type 'fillpack' you can put all unequipped items, except "+
	"money and containers into the backpack. And if you type 'emptypack' "+
	"you fetch all the items from the backpack again. ";

    if (query_prop_setting(OBJ_M_NO_SELL) == NO_SELL_PROP)
    {
        long_desc += "Presently, the backpack is protected so you " +
            "will not sell it when selling equipment. Do <keep backpack> to " +
            "remove the protection.";
    }
    else
    {
        long_desc += "Whenever you sell equipment, you might sell the " +
            "backpack. To prevent yourself from selling it you may <keep " +
            "backpack> to protect it.";
    }

    return BSN(long_desc);
}

public string
show_subloc(string subloc, object on, object for_obj)

{
  string data;

  if(subloc==BACKPACK_SUBLOC)
  {
    if (for_obj != on)
      data = capitalize(on->query_pronoun()) + 
           " is wearing a "+short()+" on " +
           on->query_possessive() + " back.\n";
    else
      data = "You are wearing a "+short()+" on your back.\n";
    return data;
  }
}

int
do_keep(string str)
{
    if (!parse_command(str, TP, " [the] [large] [black] [shoddy] 'backpack' / " +
        "'backpack' / 'pack' "))
    {
        NFN0(CAP(query_verb()) + " what?");
    }

    if (ENV(TO) != TP)
    {
        NFN0("You do not have the " + TO->short() + " in your hands.");
    }

    if (query_prop_setting(OBJ_M_NO_SELL) == NO_SELL_PROP)
    {
        add_prop(OBJ_M_NO_SELL, NO_SELL_VBFC);
        write("You can sell the backpack now.\n");
    }
    else
    {
        add_prop(OBJ_M_NO_SELL, NO_SELL_PROP);
        write(BSN("You will now keep the backpack when you are selling " +
            "equipment. To be able to sell it again, just type <keep " +
            "backpack> again."));
    }
    return 1;
}

/*
 * Function name: describe_contents
 * Description:   Give a description of items in this container
 * Arguments:     object for_obj - To whom to give the description
 *                object *obarr  - The items to describe
 */
public void
describe_contents(object for_obj, object *obarr)
{
    for_obj->catch_tell(show_sublocs(for_obj));

    if (this_object()->query_prop(CONT_I_ATTACH))
    {
        if (sizeof(obarr) > 0)
        {
            for_obj->catch_tell(capitalize(COMPOSITE_DEAD(obarr)) + 
                (sizeof(obarr) > 1 ? " are" : " is") + " on the " +
                this_object()->short() + ".\n");
        }
        else
        {
            for_obj->catch_tell("There is nothing on the " + 
                this_object()->short() + ".\n");
        }
    }
    else if (sizeof(obarr) > 0)
    {
        show_list(for_obj, obarr);
    }
    else
    {
        for_obj->catch_tell("  " + "The " + this_object()->short() +
            " is empty.\n");
    }
}

public void
show_list(object for_obj, object *obarr)
{
    int i, price;

    obarr = FILTER_DEAD(obarr);
    obarr = unique_array(obarr, "short", 0);
    obarr = sort_array(obarr, "sort_objects_to_list", this_object());

    for_obj->catch_tell(print_shop_list(obarr));
}
