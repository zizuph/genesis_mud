/*
 * - saddlebag.c
 *
 * Saddlebag object for use with steeds.
 * 
 * Modified for Rivendell steeds 
 * -- Finwe, February 2002
 */
#pragma strict_types
inherit "/d/Gondor/common/guild/obj/backpack";
inherit "/d/Shire/lib/box_list";
inherit "/lib/shop";


#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include "/d/Genesis/steed/new/steed.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <money.h>
#include <filter_funs.h>

#define NO_SELL_PROP BSN("You do not want to sell the backpack. Do " + \
    "<keep backpack> to remove the protection.")
#define NO_SELL_VBFC "@@no_sell_vbfc@@"
#define BACKPACK_SUBLOC  "_ranger_backpack"

static object   steed;
static int	pack_size;

public void show_list(object for_obj, object *obarr);

public nomask int
query_steed_pack()	{ return 1; }

public nomask void
set_pack_size(int i)	{ pack_size = i; }

public nomask int
query_pack_size()	{ return pack_size; }

public void
create_saddlebag()
{
}

public nomask void
create_container()
{
    ::create_container();


// remove names from backpack
    remove_name("backpack");
    remove_name("pack");
    remove_name("rucksack");
    remove_name("knapsack");

    remove_pname("backpacks");
    remove_pname("packs");
    remove_pname("rucksacks");
    remove_pname("knapsacks");

    set_name("saddlebag");
    add_name(({"light saddlebag", "large gray saddlebag"}));
    set_short("light gray saddlebag");
    set_long("This is a light gray saddlebag made of some gray " +
        "material. It was expertly crafted by elves and is " +
        "designed to be draped over their steeds. The saddlebag " +
        "has two large pouches which can hold many supplies when " +
        "travelling. There is a small tag sticking out from under " +
        "one of the pouches.\n");

    add_prop(CONT_I_WEIGHT,	3000);
    add_prop(CONT_I_MAX_WEIGHT,	100000);
    add_prop(CONT_I_MAX_VOLUME,	100000);

    add_item("tag", "Maybe you should read it.\n");
    add_cmd_item("tag", "read", "@@read_tag@@");


    set_mass_storage(1);
    set_pack_size(STEED_NORMAL);

    create_saddlebag();
}

public int
drape_me_pack(string str)
{
    object pack, *tmp;

    if (!str)
    {
	notify_fail("Drape what?\n");
	return 0;
    }

    tmp = filter(all_inventory(this_player()), &->query_steed_pack());
    tmp += filter(all_inventory(environment(this_player())),
			&->query_valid_steed());

    if (!parse_command(str, tmp, "[the] %o [on] [the] %o", pack, steed))
    {
	notify_fail("Drape what on what ?\n");
	return 0;
    }

    if (!pack->query_steed_pack() || !steed->query_valid_steed())
    {
        notify_fail("Drape what on what?\n");
        return 0;
    }

    if (!present(pack, this_player()))
    {
	notify_fail("You do not have any " + pack->short() + ".\n");
	return 0;
    }

    if ((pack_size != STEED_ALL) && 
	(pack_size != steed->query_steed_size()))
    {
	write("The " + pack->short() + " was not designed to fit " +
	    "the " + steed->short_old() + ".\n");
	return 1;
    }

    if (pack->move(steed))
    {
	write("The " + pack->short() + " seems to be too heavy for the "+
	  steed->short_old()+" to carry.\n");
	return 1;
    }

    write("You drape the "+pack->short()+" over the "+
      steed->short_old()+"'s back.\n");

    say(QCTNAME(this_player())+" drapes a "+pack->short()+ 
	" over the back of the "+steed->short_old()+".\n");

    steed->set_steed_saddlebag(pack);
    return 1;
}

public void
undrape_me_pack(string str)
{
    object pack, *tmp;

    if (!parse_command(str, tmp, "[the] %o [on] [the] %o", pack, steed))
    {
	notify_fail("Undrape what on what ?\n");
	return 0;
    }

    if (!pack->query_steed_pack() || !steed->query_valid_steed())
    {
        notify_fail("Undrape what on what?\n");
        return 0;
    }


    if (move(this_player()))
    {
	write("You untie the straps of the "+short()+", letting it " +
        "drop heavily to the ground.\n");

	say(QCTNAME(this_player())+" unties the straps of the " +
	   steed->short_old()+"'s "+short()+", letting it fall heavily to"+
	  "the ground.\n");

	move(environment(steed));
    }
    else
    {
	write("You remove the "+short()+" from the "+
	  steed->short_old()+"'s back.\n");

	say(QCTNAME(this_player())+" removes a "+short()+ 
	  " from the back of the "+ steed->short_old()+".\n");
    }

    steed->set_steed_saddlebag(0);
    steed = 0;
}

public void
open_me_pack()
{
    if (!query_prop(CONT_I_CLOSED))
    {
	write("The "+short()+" is already open!\n");
	return;
    }

    remove_prop(CONT_I_CLOSED);

    write("You open the "+short()+" on the "+
      steed->short_old()+"'s back.\n");

    say(QCTNAME(this_player())+" opens the "+short()+" on the "+
      steed->short_old()+"'s back.\n");
}

public void
close_me_pack()
{
    if (query_prop(CONT_I_CLOSED))
    {
	write("The "+short()+" is already closed!\n");
	return;
    }

    add_prop(CONT_I_CLOSED, 1);

    write("You close the "+short()+" on the "+
      steed->short_old()+"'s back.\n");

    say(QCTNAME(this_player())+" closes the "+short()+" on the "+
      steed->short_old()+"'s back.\n");
}

public int
pack_fill_fail()
{
    if (!steed && (environment(this_object()) != this_player()))
    {
        write("You need to get the " + short() + " first.\n");    
        return 1;
    }
    
    if (query_prop(CONT_I_CLOSED))
    {
        write("The " + short() + " is closed.\n");
        return 1;
    }

    return 0;
}

public int
pack_empty_fail()
{
    if (!steed && (environment(this_object()) != this_player()))
    {
        write("You need to get the " + short() + " first.\n");    
        return 1;
    }
    
    if (query_prop(CONT_I_CLOSED))
    {
        write("The " + short() + " is closed.\n");
        return 1;
    }
  
    return 0;
}

public void
appraise_me_pack()
{
    appraise_object(0);
}

public void
init()
{
    ::init();
    add_action( drape_me_pack, "drape" );
}

string
read_tag()
{
    return "On the tag you read the following:\n"+
        "\tWhen draped on a steed, the following commands are available:\n\n"+
        "\tdrape saddlebag on horse  - puts saddlebag on steed\n"+
        "\tremove saddlebag from horse - takes saddlebag off steed\n"+
        "\tfill saddlebag on horse   - puts only weapons and armours " +
            "in saddlebag\n"+
        "\tget all from saddlebag    - gets supplies from saddlebag\n\n"+
        "\tWhen saddlebag is not on horse, it acts like a normal backpack.\n\n";
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
