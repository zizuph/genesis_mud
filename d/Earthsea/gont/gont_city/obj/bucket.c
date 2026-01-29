/* Coded by Ckrik June 1998
 * For Clam Quest in Gont City, Earthsea
 */

#pragma strict_types

inherit "/std/container";

#include "/d/Earthsea/sys/terrain_types.h"
#include "/d/Earthsea/sys/properties.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <composite.h>

#define CONTAIN_WATER "_contain_water"

public void
create_container()
{
    set_name("bucket");
    set_pname("buckets");
    set_adj("wooden");
    set_short("wooden bucket");
    set_pshort("wooden buckets");
    set_long("A wooden bucket. This bucket can be used to " +
        "hold water and many other things.\n");
    add_prop(CONT_I_WEIGHT, 1000);
    add_prop(CONT_I_MAX_WEIGHT, 6000);
    add_prop(CONT_I_VOLUME, 700);
    add_prop(CONT_I_MAX_VOLUME, 3000);
    add_prop(OBJ_I_VALUE, 100);
}

public int
query_bucket_full()
{
    int clams_in_bucket = 0;
    object* inv;
    int i = 0;

    inv = FILTER_LIVE(all_inventory(this_object()));

    for(i = 0; i < sizeof(inv); i++)
    {
        if(inv[i]->query_real_name() == "clam")
        {
            clams_in_bucket++;
        }
    }

    return (clams_in_bucket >= 10);
}

public int
dump_bucket(string str)
{
    object* inv;
    int i = 0;

    notify_fail("Dump what? The water?\n");

    if(str == "bucket" || str == "water")
    {
        if(query_prop(CONTAIN_WATER) != 1)
        {
            write("There is no water in the bucket.\n");
        } else {
            add_prop(CONTAIN_WATER, 0);
            write("You dump the water in the bucket onto the ground.\n");
            inv = FILTER_LIVE(all_inventory(this_object()));

            for(i = 0; i < sizeof(inv); i++)
            {
                if(inv[i]->query_real_name() == "clam")
                {
                    inv[i]->set_death_count();
                }
            }
        }

        return 1;
    }

    return 0;
}

public int
fill_bucket(string str)
{
    object room = environment(this_player()), *inv;
    int i = 0;

    if(!str)
        return notify_fail("Fill what? The bucket?\n");

    if(str == "bucket")
    {
        write("Fill the bucket with what? Water?\n");
        return 1;
    } else if(parse_command(str, environment(), 
        "[the] 'bucket' [with] [sea] [water]")
    ) {
        if(room->query_prop(ROOM_I_TERRAIN_TYPE) == 874857472)
        {
            if(query_prop(CONTAIN_WATER) == 0)
            {
                add_prop(CONTAIN_WATER, 1);
                write("You fill the bucket with water from " +
                    "the sea.\n");
            } else {
              write("You dump the water in the bucket " +
                  "and fill the bucket with new water " +
                  "from the sea.\n");
            }

            inv = FILTER_LIVE(all_inventory(this_object()));

            for(i = 0; i < sizeof(inv); i++)
            {
                if(inv[i]->query_real_name() == "clam")
                {
                    inv[i]->remove_death_count();
                }
            }

            return 1;
        } else {
            write("Somehow you think this is not the " +
                "right place to do that.\n");
            return 1;
        }
    } 

    return notify_fail("Fill what? The bucket?\n");
}

public void
describe_contents(object for_obj, object *obarr)
{
    string myshort = short();

    if(query_prop(CONTAIN_WATER) == 1)
    {
        myshort += " filled with water";
    }

    for_obj->catch_tell(show_sublocs(for_obj));

    if(query_prop(CONT_I_ATTACH))
    {
        if(sizeof(obarr) > 0)
        {
            for_obj->catch_tell(capitalize(COMPOSITE_DEAD(obarr)) + 
                (sizeof(obarr) > 1 ? " are" : " is") + " on the " +
                myshort + ".\n");
        } else {
            for_obj->catch_tell("There is nothing on the " + 
                myshort + ".\n");
        }
    } else if(sizeof(obarr) > 0) {
        for_obj->catch_tell("The " + myshort + " contains " + 
            COMPOSITE_DEAD(obarr) + ".\n");
    } else {
        for_obj->catch_tell("  " + "The " + myshort +
            " is empty.\n ");
    }
}

public void
init()
{
    ::init();
    add_action(fill_bucket, "fill");
    add_action(dump_bucket, "dump");
}
