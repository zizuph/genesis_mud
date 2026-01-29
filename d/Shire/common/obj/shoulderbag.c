/*
 * A simple sack
 * Improved listing added by Rhyn. Thanks Rhyn!!
 * -- Finwe, May 2001
 *
 * 2003/07/16 Last update
 * 2011/08/02 Lavellan - Removed names added by inherited backpack, fixed typo.
 *                     - Fixed keep. Keep in general is a big mess.
 */

inherit "/d/Gondor/common/guild/obj/backpack";
inherit "/d/Shire/lib/box_list";
inherit "/lib/shop";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <money.h>
#include <filter_funs.h>
#include "/d/Shire/common/defs.h"

#define NO_SELL_PROP BSN("You do not want to sell the shoulder bag. Do " + \
    "<keep shoulder bag> to remove the protection.")
#define NO_SELL_VBFC "@@no_sell_vbfc@@"
//   -Igneous-
//  The old _shire_orc_backpack wasn't the subloc name that the file was adding
#define BACKPACK_SUBLOC  "_ranger_backpack"

public void show_list(object for_obj, object *obarr);

void
create_container()
{
    ::create_container();

    add_prop(OBJ_I_VALUE, 100+random(150));
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_WEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 2500);
    add_prop(CONT_I_MAX_WEIGHT, 150000);
    add_prop(CONT_I_MAX_VOLUME, 150000);
    add_prop(CONT_I_REDUCE_VOLUME, 125);

    remove_adj("camouflaged");
    remove_adj("green-coloured");
    remove_name(query_names()[..-1]);
    add_adj(({"light", "brown"}));

    set_short("light brown shoulder bag");
    set_long("@@long_description");
    set_name("shoulder bag");
    set_name("bag");

    config_default_trade();
    }

string
long_description()
{
//    string long_desc = "The shoulder bag is large and able to hold alot of " +
    string long_desc = "The shoulder bag is large and able to hold a lot of " +
        "supplies. It is a common item used by travelling hobbits from " +
        "Frogmorton. A wide strap enables you to wear it over your shoulder " +
        "and across your chest, thus permitting easy access to the bag. " +
        "It is made from brown leather and looks fairly new. <fill " +
        "shoulder bag> will let you put almost everything into the bag " +
//        "except for money and unused containers. <empty shoulder bag> " +
        "except for money and containers. <empty shoulder bag> " +
        "will enable you to retrieve items from the shoulder bag. ";

    if (query_prop_setting(OBJ_M_NO_SELL) == NO_SELL_VBFC)
    {
        long_desc += "The shoulder bag is not protected from being " +
        "sold. <keep shoulder bag> to protect it. ";
    }
    else
    {
        long_desc += "The shoulder bag is protected from being sold. " +
        "<unkeep shoulder bag> will remove this protection. ";
    }

//    return BSN(long_desc);
    return long_desc;
}

public string
show_subloc(string subloc, object on, object for_obj)

{
  string data;

  if(subloc==BACKPACK_SUBLOC)
  {
    if (for_obj != on)
      data = capitalize(on->query_pronoun()) + 
           " is wearing a "+short()+" across " +
           on->query_possessive() + " shoulder and chest.\n";
    else
      data = "You are wearing a "+short()+" across your " +
        "shoulder and chest.\n";
    return data;
  }
}

int
do_keep(string str)
{
    if (!parse_command(str, TP, " [the] [light] [brown] 'shoulder bag' / " +
        "'shoulder bag' / 'bag' "))
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
        write("You may now sell the shoulder bag.\n");
    }
    else
    {
        add_prop(OBJ_M_NO_SELL, NO_SELL_PROP);
        write(BSN("You will now keep the shoulder bag when you are selling " +
            "supplies. To be able to sell it again, just type <keep " +
            "pack> again."));
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

public int
query_unsellable()
{
    if (calling_function() == "keep")
        return 0;
    return ::query_unsellable();
}

public int
set_keep(int keep = 1)
{
    if (query_prop_setting(OBJ_M_NO_SELL) == NO_SELL_VBFC)
        remove_prop(OBJ_M_NO_SELL);
    ::set_keep(keep);
}