/*
 *  Trashcan borrowed from the Shire, per Finwe's
 *  permission--for use in ranger guilds, to get
 *  rid of extra junk
 *  Tigerlily--Nov. 2004
 */

#pragma save_binary
#pragma strict_types

inherit "/std/container";
inherit "/d/Shire/lib/box_list";
inherit "/lib/shop";
//#include "defs.h"
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <money.h>
#include <filter_funs.h>

public void show_list(object for_obj, object *obarr);

void
create_container()
{
    set_name(({"chute", "RA_trash", "hole"}));
    set_adj(({"rock", "trash"}));
    set_short("trash chute");
    set_long("This is hole carved into the rock that seems to go down " +
        "to some fathomless depth. It has been set here so that rangers " +
        "can dispose of their trash and not dirty the area. Periodically " +
        "it is emptied by some sort of vacuum force from below. There " +
        "is a sign on it.\n");
    add_item("sign", "The sign reads:\nFor trash only! Don't put " +
        "anything in here that you want to keep!\n\n");
    add_cmd_item( ({ "sign", }), ({"read", }), 
        "The sign reads:\n\nFor trash only! Don't put " +
        "anything in here that you want to keep!\n\n");
    /* Some properties of this thrashcan */
    add_prop(OBJ_I_NO_GET, 1);          /* Not gettable       */
    add_prop(CONT_I_LIGHT, 1);
    add_prop(CONT_I_IN,1);              /* It's a container!  */
    add_prop(CONT_I_RIGID,1);           /* A rigid object     */
    add_prop(CONT_I_TRANSP,0);          /* Not transparant    */
    add_prop(CONT_I_MAX_VOLUME,200000); /* Can contain 20 Ltr */
    add_prop(CONT_I_MAX_WEIGHT,200000); /* Can contain 20 Kg */
    

    add_prop(OBJ_S_WIZINFO,
             "A rock disposal chute, set in the ranger hideout. Will " +
             "destroy things after they're tossed in the chute.\n");

}

public void
dump_trash(object ob)
{
    setuid();
    seteuid(getuid(this_object()));
    if (environment(ob) == this_object())
        ob->remove_object();
    tell_room(environment(this_object()), "The trash suddenly disappears " +
        "down the chute with a WHOOOOSH sound!\n");
}


mixed 
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);

   if (living(ob)) 
       return;

// dumps trash 
   set_alarm(120.0, 0.0, &dump_trash(ob));


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
prevent_enter(object ob)
{
    if (living(ob))
    {   
        write("You can't put " + LANG_THESHORT(ob) + " in " +
            "the chute.\n");
        return 1;
    }
    // else
    return 0;
}
