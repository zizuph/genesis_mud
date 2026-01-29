/*
 * A backpack for the bree-landers. Same code as the shoddy backpacks
 * found in the orc camp. Thanks to Gondor for letting us use the code!
 * -- Finwe 
 *
 * Improved listing added by Rhyn. Thanks Rhyn!!
 * -- Finwe, May 2001

 */

inherit "/d/Gondor/common/guild/obj/backpack";
inherit "/d/Shire/lib/box_list";
inherit "/lib/shop";
inherit "/lib/keep";
inherit "/d/Shire/common/obj/pack_loot";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <money.h>
#include <filter_funs.h>
#include "/d/Shire/common/defs.h"

//#define NO_SELL_PROP BSN("You do not want to sell the backpack. Do " + \
//    "<keep backpack> to remove the protection.")
#define NO_SELL_VBFC "@@no_sell_vbfc@@"
//   -Igneous-
//  The old _shire_orc_backpack wasn't the subloc name that the file was adding
#define BACKPACK_SUBLOC  "_shire_backpack"
public void show_list(object for_obj, object *obarr);


void
create_container()
{
    ::create_container();

    add_prop(OBJ_I_VALUE, 250+random(150));
    remove_adj("camouflaged");
    remove_adj("green-coloured");
    add_adj(({"soft", "grey"}));

    add_prop(CONT_I_WEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 2000);
    add_prop(CONT_I_MAX_WEIGHT, 150000);
    add_prop(CONT_I_MAX_VOLUME, 150000);
    add_prop(CONT_I_REDUCE_VOLUME, 125);

    set_short("soft grey backpack");
    set_long("@@long_description");
    set_name("backpack");
    add_name("pack");
}

string
long_description()
{
    string long_desc = "The " + short() + " is large and looks like it " +
        "is able to hold quite a few supplies. It is made strong canvas " +
        "stitched together with heavy threads. <fillpack> will put all " +
        "your unused supplies except money and unused containers into " +
        "the backpack. <packloot corpses> enables you to loot multiple " +
        "corpses.";

//    if (query_prop_setting(OBJ_M_NO_SELL) == NO_SELL_PROP)
    if (query_keep())
    {
        long_desc += "\nYour backpack is protected from " +
        "being sold. <unkeep backpack> will remove this protection.";
    }
    else
    {
        long_desc += "\nThe backpack is not protected from being " +
        "sold. To protect it, type <keep backpack>. This " +
        "will not protect it from thieves, though.";
    }

    return long_desc+"\n";
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
    if (!parse_command(str, TP, " [the] [weather-worn] [leather] 'backpack' / " +
        "'backpack' / 'pack' "))
    {
        NFN0(CAP(query_verb()) + " what?");
    }

    if (ENV(TO) != TP)
    {
        NFN0("You do not have the " + TO->short() + " in your hands.");
    }

//    if (query_prop_setting(OBJ_M_NO_SELL) == NO_SELL_PROP)
    if (query_keep())
    {
//        add_prop(OBJ_M_NO_SELL, NO_SELL_VBFC);
        set_keep(0);
        write("You may sell the backpack now.\n");
    }
    else
    {
//        add_prop(OBJ_M_NO_SELL, NO_SELL_PROP);
        set_keep(1);
        write("You will now keep the backpack when you are selling " +
            "supplies. To be able to sell it again, just type <keep " +
            "backpack> again.\n");
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
