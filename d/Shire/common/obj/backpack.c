/*
 * A backpack for the bree-landers. Same code as the shoddy backpacks
 * found in the orc camp. Thanks to Gondor for letting us use the code!
 * -- Finwe
 *
 * Improved listing added by Rhyn. Thanks Rhyn!!
 * -- Finwe, May 2001

 */

inherit "/d/Gondor/common/guild/obj/backpack";
// inherit "/d/Shire/lib/box_list";
inherit "/d/Faerun/lib/pack_list.c";

inherit "/lib/shop";
inherit "/lib/keep";
inherit "/d/Shire/common/lib/parse";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <money.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include "/d/Shire/common/defs.h"

#define NO_SELL_VBFC "@@no_sell_vbfc@@"
#define BACKPACK_SUBLOC  "_shire_backpack"
#define IM_PARSE_FILE   "/d/Shire/common/lib/parse"
#define INV(x) all_inventory(x)

public void show_list(object for_obj, object *obarr);

static string pack_name = "backpack";

void
create_container()
{
    ::create_container();

    add_prop(OBJ_I_VALUE, 250+random(150));
    remove_adj("camouflaged");
    remove_adj("green-coloured");
    add_adj(({"weather-worn", "leather"}));

    add_prop(CONT_I_WEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 2000);
    add_prop(CONT_I_MAX_WEIGHT, 150000);
    add_prop(CONT_I_MAX_VOLUME, 150000);
    add_prop(CONT_I_REDUCE_VOLUME, 125);

    set_short("weather-worn leather backpack");
    set_long("@@long_description");
    set_name("backpack");

    add_item("tag", "There are some instructions on it. You should " +
        "probably read the tag.\n");
    add_cmd_item("tag", "read", "@@read_tag@@");
}

string
long_description()
{
    string long_desc = "The backpack is large and looks like it is able " +
        "to hold quite a few supplies. It is the kind favored by " +
        "travellers of Bree, and is made of leather. The backpack " +
        "looks like it has been used.\n";

//    if (query_prop_setting(OBJ_M_NO_SELL) == NO_SELL_PROP)
    if (query_keep())
    {
        long_desc += "\nThe backpack is protected from " +
        "being sold. <unkeep backpack> will remove this protection.\n\n";
    }
    else
    {
        long_desc += "\nThe backpack is not protected from being " +
        "sold. To protect it, type <keep backpack>. This " +
        "will not protect it from thieves, though.\n\n";
    }

    return long_desc + "A leather tag hangs from the backpack with " +
        "some instructions.\n";
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

// packloot routines
init()
{
    ::init();
    add_action("do_loot", "packloot");
    add_action("do_loot", "pl");
}


int is_corpse(object what)

{
    return !living(what) && what->query_prop(CONT_I_IN);
}

int
is_backpack(object what)
{
    return what->id(BACKPACK_SUBLOC);
}

int
do_loot(string arg)
{
    mixed  *obs;
    object *loot;
    string rest;
    object pack;

    FIXEUID;

    notify_fail("Usage: " + query_verb() +" <corpse> [with <" + pack_name + ">]\n");
/*
    if (ETO != TP)
    return notify_fail("You must wear the " + pack_name + " to loot corpses.\n");
*/
    if (!strlen(arg))
        arg = "corpse";

    if (parse_command(arg, INV(ENV(TP)),
               "%i 'in' / 'into' / 'with' / 'using' [the] %s",
              obs, rest))
    {
        loot = VISIBLE_ACCESS(obs, "is_corpse", TO);
        if (!parse_command(rest, INV(TP), "[the] %i", obs))
            return notify_fail("Loot it into which " + pack_name + "?\n");
        obs = VISIBLE_ACCESS(obs, BACKPACK_SUBLOC, TO);
        if (!sizeof(obs))
            return notify_fail("Which " + pack_name + " are you referring to?\n");
        if (sizeof(obs) > 1)
            return notify_fail("You may only use one " + pack_name + " at a time\n");
        pack = obs[0];
        return pack->do_loot_one(loot, rest);
    }
    else {
    loot = IM_PARSE_FILE->parse_environment_items(arg, "");
    if (!sizeof(loot))
        return 0;
    loot = filter(loot, "is_corpse", TO);
    if (!sizeof(loot))
        return 0;
    return TO->do_loot_one(loot, "loot pack");
    }
}

int move_to(object what)
{
    if (!objectp(what))
      return 0;
    if( what->move(TO) != 0 )
      return 0;

    return 1;
}

int
do_loot_one(object *loot, string name)
{
    int i, j;
    object *thing;
    object *got;

    if (query_prop(CONT_I_CLOSED))
    return notify_fail("Perhaps open the " + name + " first?\n");

    i=sizeof(loot);

    if (!i)
    return 0;

    write("You loot " + COMPOSITE_DEAD(loot) + " using your "+name+".\n");
    say(QCTNAME(TP) + " starts looting " + QCOMPDEAD + ".\n");

    while (i--) {
    if (!objectp(loot[i]))
        continue;

    thing = all_inventory(loot[i]);
    j = sizeof(thing);

    if (!j) {
        write("The " + loot[i]->short() + " is empty.\n");
        continue;
    }

    got = filter(thing, "move_to", TO);

    if (!sizeof(got))
        write("You couldn't loot anything from the " + loot[i]->short() + ".\n");
    else {
        write("You loot " + COMPOSITE_DEAD(got) + " from the " +
          loot[i]->short() + " into " + name + ".\n");
        say(QCTNAME(TP) + " loots " + QCOMPDEAD + " from the " +
        loot[i]->short() + ".\n");
    }
    }
    return 1;
}


string read_tag()
{
    return "\n\n" +
        "    +-------------------------------------------------------+\n" +
        "    |   Backpack Commands                                   |\n" +
        "    |   -----------------                                   |\n" +
        "    |   <fillpack> - Put unused items, except money, gems,  |\n" +
        "    |   herbs, worn and wielded items, and empty containers,|\n" +
        "    |   into the backpack                                   |\n" +
        "    |                                                       |\n" +
        "    |   <emptypack> - Remove everything excempt for money   |\n" +
        "    |   and gems from the backpack                          |\n" +
        "    |                                                       |\n" +
        "    |   <packloot corpse[s]> - Lets you loot one or more    |\n" +
        "    |   corpses and fill the backpack. <pl> is a shortcut   |\n" +
        "    |   for <packloot>                                      |\n" +
        "    |                                                       |\n" +
        "    |   <get all from pack> - Get everything from the pack, |\n" +
        "    |   if you are able to hold it all                     |\n" +
        "    +-------------------------------------------------------+\n\n";
}
