/*
 *  wrap.c
 *
 *  A herb bundle that increases in size over time, it is
 *  cloned on the druid in the temple.
 *
 *  Created by Carnak, January 2016
 */
#pragma save_binary

inherit "std/object.c";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <files.h>
#include <composite.h>

#include "../local.h"

#define HERB_MASTER "/d/Krynn/common/herbs/herb_master"

int wrap, decay;
string *inside = ({});
string *herbs; /* Loads herbs from Krynn */


#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

int
query_wrap()
{
    return wrap;
}

int
set_wrap(int i)
{
    wrap = i;
}

/*
 * Function     : query_inside
 * Description  : Returns the number of herbs inside
 */
int
query_inside()
{
    if (!pointerp(inside))
        return 0;

    return sizeof(inside);
}

varargs void
set_inside(mixed ins)
{
    if (!pointerp(inside))
        inside = ({ }) + ins;

    inside = ({ins}) + inside;
}

/*
 * Function     : query_herb_list
 * Description  : Returns an array list of the herbs inside
 */

object *
query_herb_list()
{
    if (!pointerp(inside))
        return 0;

    return inside + ({});
}

/*
 * Function     : adjust_weight
 * Description  : This will add or remove weight depending on
 *                the amount of herbs in the 'inside' array
 * Returns      : nothing
 */

void
adjust_weight()
{
    if (!query_wrap())
    {
        add_prop(OBJ_I_WEIGHT, 50);
        add_prop(OBJ_I_VOLUME, 50);
        return;
    }

    add_prop(OBJ_I_WEIGHT, (query_inside()*4)+50);
    add_prop(OBJ_I_VOLUME, (query_inside()*4)+50);
}

void
start_decay()
{
    if (!query_wrap())
        return;

    if (!query_inside())
    {
        write("The herb bundle has decayed.\n");
        set_wrap(0);
        remove_adj("decaying");
        add_adj("decayed");
        return;
    }

    if (environment(this_object())->query_prop(LIVE_I_IS) ||
       !environment(this_object())->query_prop(ROOM_I_INSIDE))
    {
        if (!random(100) && decay)
        {
            decay = 0;
            this_object()->reset_wrap();
            write("The herb bundle has recovered from previous decay "+
            "due to the environment.\n");
            remove_adj("decaying");
            return;
        }
    }

    if (!decay)
    {
        decay = 1;
        write("The herb bundle has begun decaying.\n");
        add_adj("decaying");
    }

    inside = exclude_array(query_herb_list(), 0, 0);
    set_alarm(itof(300-query_inside()), 0.0, &start_decay());
}

/*
 * Function     : reset_wrap
 * Description  : This will increment the herbs, it is called
 *                from the npc this item spawns with
 * Returns      : nothing
 */
void
reset_wrap()
{
    if (!query_wrap() || decay)
        return;

    if (query_inside() > 200)
        return;

    string *newHerbs = ({});


    if (!environment(this_object())->query_prop(LIVE_I_IS) ||
         environment(this_object())->query_prop(ROOM_I_INSIDE))
    {
        if (!random(20000 / (query_inside()+1)))
        {
            start_decay();
            return;
        }
    }

    if (!pointerp(herbs))
        herbs = ({});

    if (!sizeof(herbs))
    {
        /* This uses query_herb_value to sort out poor quality herbs */
        foreach(string h: HERB_MASTER->query_herbs())
        {
            if (h->query_herb_value() > 350 + random(100))
            {
                if (!pointerp(newHerbs))
                    newHerbs = ({ h });

                newHerbs = ({ h }) + newHerbs;
            }
        }

        if (!pointerp(newHerbs))
            herbs = HERB_MASTER->query_herbs();
        else
            herbs = newHerbs;
    }

    set_inside(ONE_OF(herbs));
    set_alarm(itof((query_inside()*5)+10), 0.0, &reset_wrap());
    adjust_weight();
}

void
create_object()
{
    set_name("bundle");
    set_short("@@query_short");
    set_long("@@query_long");
    add_adj("herb");

    set_wrap(1);

    set_no_show;

    add_cmd_item(({"bundle","herb bundle"}),"unwrap",
    "@@unwrap_bundle");

    add_cmd_item(({"bundle","herb bundle"}),"wrap",
    "@@wrap_bundle");

    add_cmd_item(({"bundle","herb bundle"}),"discard",
    "@@disard_bundle");
}

/*
 * Function     : unwrap_bundle
 * Description  : This will move the herbs from the 'inside'
 *                array into the players inventory, turning
 *                the bundle into a useless item.
 * Returns      : nothing
 */

int
unwrap_bundle()
{
    if (!query_wrap())
    {
        write("There is no herb bundle to unwrap.\n");
        return 1;
    }

    string str;
    switch(query_inside())
    {
        case 1:
        str = "You find a herb inside.";
            break;
        case 2..10:
        str = "You find a few herbs inside.";
            break;

        case 11..50:
        str = "You find a fair amount of herbs inside.";
            break;

        case 51..150:
        str = "The core is filled to the brim with herbs.";
            break;

        case 151..201:
        str = "As you open the bundle, a myriad of herbs "+
        "burst out.";
            break;

        default:
        str = "You find no herbs inside.";
            break;
	}

    foreach(string h: inside)
    {
        object herb;
        herb = clone_object(h);
        herb->move(environment(this_object()));
    }

    write("You unwrap the "+query_short()+", tearing "+
    "the stiff leaves in an attempt to reach its core. "+
    str+"\n");
    set_wrap(0);
    adjust_weight();
    add_adj("torn");
    return 1;
}

int
wrap_bundle()
{
    if (query_wrap())
    {
        return 1;
    }

    write("The leaf that was once a herb bundle is torn, "+
    "and no longer growing, you should probably 'discard' "+
    "it.\n");
    return 1;
}

/*
 * Function     : discard_bundle
 * Description  : This will remove the remaining object.
 * Returns      : nothing
 */
int
discard_bundle()
{
    if (query_wrap())
    {
        write("You decide not to discard it as there are "+
        "still herbs inside it.\n");
        return 1;
	}

    write("You discard the "+query_short()+".\n");
    set_alarm(0.0, 0.0, remove_object);
}

string
query_short()
{
    if (!query_wrap())
    {
        if (decay)
            return "decayed herb bundle";
        return "torn herb bundle";
    }
    else
    {
        if (decay)
            return "decaying herb bundle";
        return "herb bundle";
    }
}
/*
 * Function     : query_long
 * Description  : This allows the item to grow in appearance as
 *                the herbs increase
 * Returns      : The long description of the item.
 */
string
query_long()
{
    string str;
    switch(query_inside())
    {
        case 0..50:
        str = "The bundle is still just a baby seed, it has "+
        "not yet reached maturity. You could 'unwrap' it, if "+
        "you are too impatient to wait.\n";
        break;

        case 51..150:
        str = "The seed has grown into a sizeable bundle, "+
        "you should probably wait a while longer before "+
        "you 'unwrap' it.\n";
        break;

        case 151..199:
        str = "The bundle has nearly reached maturity, no "+
        "longer increasing in size, it will soon be time "+
        "to 'unwrap' it.\n";
        break;

        default:
        str = "The bundle has reached maturity, you should "+
        "'unwrap' it to find what treasures it may hold.\n";
	}

    if (decay)
        str = "The bundle has begun decaying due to improper "+
        "care or a harmful environment.\n";

    if (!query_wrap())
    {
        if (decay)
            return "This herb bundle was once lush and vibrant "+
            "with life, but inproper care has caused it to decay.\n";

        return "This is a torn herb bundle, which once "+
        "housed a variety of herbs, increasing in size "+
        "until it reached maturity.\n";
    }
	else
    {
        return "This is a herb bundle, wrapped in stiff "+
        "leaves to protect its core which is filled to "+
		"the brim with herbs. " + str;
    }
}
