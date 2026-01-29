/* Stralle @ Genesis 010727
 *
 * A donation box
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/obj/rack";

#include <macros.h>
#include <files.h>
#include "../guild.h"

#define POT_DONATION_TAG "_pot_donation_tag"

void
create_rack()
{
    set_name("box");
    set_long("It is a box where items can be donated.\n");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    add_rack_entry(ob);
    
    if (!objectp(from) || !IS_PLAYER_OBJECT(from))
    {
        return;
    }
    
    ob->add_prop(POT_DONATION_TAG, from->query_real_name());
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    remove_rack_entry(ob);
    if (!objectp(to)
        || !IS_PLAYER_OBJECT(to) 
        || !strlen(ob->query_prop(POT_DONATION_TAG)))
    {
        return;
    }
        
    string donator = "yourself";
    if (to->query_real_name() != ob->query_prop(POT_DONATION_TAG))
    {
        donator = capitalize(ob->query_prop(POT_DONATION_TAG));
    } 
    to->catch_tell("The " + ob->short() + " was donated by " + donator
        + ".\n");
}

int
prevent_leave(object ob)
{
    object guard, pl = previous_object(-4);
    int x;

    switch (query_verb())
    {
        case "take":
        case "get":
        case "pick":
        case "steal":
        case "borrow":
            break;
        default:
            return 0;
    }

    if (((guard = present("guard", environment(this_object()))) ||
        (guard = present("priest", environment(this_object())))) &&
        pl->query_guild_name_occ() != GUILD_NAME && CAN_SEE(guard, pl))
    {
        pl->catch_msg(QCTNAME(guard) + " stops you from picking that.\n");
        return 1;
    }
    
    return 0;
}        
