/*
 * Basic backpack for Faerun. Based on the Shire packs
 * -- Finwe, May 2006
 */

inherit "/d/Shire/common/obj/backpack";
//inherit "/d/Faerun/obj/backpack";
inherit "/d/Faerun/lib/pack_list";
inherit "/lib/shop";
inherit "/lib/keep";

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <money.h>
#include <filter_funs.h>


//#define NO_SELL_PROP BSN("You do not want to sell the backpack. Do " + \
//    "<keep backpack> to remove the protection.")
#define NO_SELL_VBFC "@@no_sell_vbfc@@"
//   -Igneous-
//  The old _shire_orc_backpack wasn't the subloc name that the file was adding
#define BACKPACK_SUBLOC  "_faerun_backpack"
public void show_list(object for_obj, object *obarr);


void
create_container()
{
    ::create_container();

    add_prop(OBJ_I_VALUE, 250+random(150));
    remove_adj("camouflaged");
    remove_adj("green-coloured");
    remove_adj("weather-worn");
    remove_adj("leather");
    add_adj(({"travel-stained", "canvas"}));

    add_prop(CONT_I_WEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 2000);
    add_prop(CONT_I_MAX_WEIGHT, 150000);
    add_prop(CONT_I_MAX_VOLUME, 150000);
    add_prop(CONT_I_REDUCE_VOLUME, 135);

    set_short("travel-stained canvas backpack");
    set_long("@@long_description");
    set_name("backpack");
}

string
long_description()
{
    string long_desc = "The " + short() + " is large and made of heavy " +
        "canvas. It looks large enough to hold many supplies. You may " +
        "<fillpack> to put items in it except money and unused containers. " +
        "<emptypack> will let you empty your backpack.";

//    if (query_prop_setting(OBJ_M_NO_SELL) == NO_SELL_PROP)
    if (query_keep())
    {
        long_desc += "\n  The " + short() + " is protected from being sold. " +
        "Use <unkeep backpack> to sell it.";
    }
    else
    {
        long_desc += "\n  The " + short() + " is not protected from being " +
        "sold. <keep backpack> will protect it, but not from thieves or " +
        "cutthroats.";
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
    if (!parse_command(str, TP, " [the] [travel-stained] [canvas] 'backpack' / " +
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
        write("You may sell the " + short() + " now.\n");
    }
    else
    {
//        add_prop(OBJ_M_NO_SELL, NO_SELL_PROP);
        set_keep(1);
        write("You will now keep the " + short() + " when you are selling " +
            "supplies. To be able to sell it again, type <keep backpack>.\n");
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
        for_obj->catch_tell("  " + "The " + short() + " is empty.\n");
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

void
init()
{
    ::init();

    add_action("do_list", "plist");
}
