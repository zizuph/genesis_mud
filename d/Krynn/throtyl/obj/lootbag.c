/*
 * Lootbag for Throtyl worgs, modified from 
 * /d/Shire/bree/rooms/town/stable/obj/saddlebag.c
 * 
 * Arman, September 2020
 */

inherit "/d/Genesis/std/wearable_pack";
inherit "/d/Shire/lib/box_list";
inherit "/lib/shop";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <money.h>
#include <filter_funs.h>
#include "/d/Krynn/common/defs.h"

#define BACKPACK_SUBLOC  "_throtyl_backpack"

public void     show_list(object for_obj, object *obarr);
public string	query_recover();
public void	init_recover(string arg);

void
create_container()
{
    ::create_container();

    add_prop(OBJ_I_VALUE, 250+random(150));
    remove_pname("backpacks");
    remove_pname("rucksacks");
    remove_pname("knapsacks");
    remove_pname("backpacks");
    remove_pname("packs");
    remove_name("backpack");
    remove_name("pack");
    remove_name("rucksack");
    remove_name("knapsack");
    set_pshort("lootbags");

    add_prop(CONT_I_WEIGHT, 8000);
    add_prop(CONT_I_VOLUME, 8000);
    add_prop(CONT_I_MAX_WEIGHT, 250000);
    add_prop(CONT_I_MAX_VOLUME, 250000);
    add_prop(CONT_I_REDUCE_VOLUME, 125);
    add_prop(OBJ_I_NO_STEAL, 1);
    set_short("leather lootbag");
    set_long("@@long_description");
    set_name("lootbag");
    add_name("bag");
    set_pname("lootbags");

    add_item("tag", "Maybe you should read it.\n");
    add_cmd_item("tag", "read", "@@read_tag@@");
}

string
read_tag()
{
    return "On the tag you read the following:\n\n"+
        "\t+---------------------------------------------+\n"+
        "\t| When strapped on a worg, the following      |\n"+
        "\t| commands are available:                     |\n"+
        "\t|                                             |\n"+
        "\t|      strap lootbag on worg                  |\n"+
        "\t|      unstrap lootbag on worg                /\n"+
        "\t|      fill lootbag on worg                  / \n"+
        "\t|      open lootbag on worg            _____/  \n"+
        "\t|      close lootbag on worg          /\n"+
        "\t|      empty lootbag on worg          |\n"+
        "\t|      raidloot (see lootbag contents) \\___ \n"+
        "\t|                                          \\ \n"+
        "\t| When lootbag is not on a worg, it acts    \\ \n"+
        "\t| like a normal backpack.                    \\\n"+
        "\t|                                             |\n"+
        "\t+---------------------------------------------+\n";
}


string
long_description()
{
    string long_desc = "A large and crudely made bag, stained with " +
        "blood and grime. It has clearly been use to carry " +
        "the spoils of war. A tattered tag has been stitched " +
        "onto it that you could read.";

    if (query_keep())
    {
        long_desc += " For now the lootbag is protected from " +
        "being sold. <unkeep lootbag> will remove this protection.";
    }
    else
    {
        long_desc += " The lootbag is not protected from being " +
        "sold. To protect it, type <keep lootbag>. This " +
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
    if (!parse_command(str, TP, " [the] [leather] 'lootbag' / " +
        "'lootbag' / 'pack' "))
    {
        notify_fail(capitalize(query_verb()) + " what?");
        return 0;
    }

    if (E(TO) != TP)
    {
        notify_fail("You do not have the " + TO->short() + " in your hands.");
        return 0;
    }

    if (query_keep())
    {
        set_keep(0);
        write("You may sell the lootbag now.\n");
    }
    else
    {
        set_keep(1);
        write("You will now keep the lootbag when you are selling " +
            "supplies. To be able to sell it again, just type <keep " +
            "lootbag> again.\n");
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

/*
 * Function name:	query_recover
 * Description	:	check whether pack is recoverable (it is)
 * Returns	:	string -- the recovery string
 */
public string
query_recover()
{
    return MASTER + ":" + query_container_recover() + query_keep_recover();
} /* query_recover */

/*
 * Function name:	init_recover
 * Description	:	set the recovery vars
 * Arguments	:	string arg -- the arguments to parse
 */
public void
init_recover(string arg)
{
    init_keep_recover(arg);
    init_container_recover(arg); 
} /* init_recover */