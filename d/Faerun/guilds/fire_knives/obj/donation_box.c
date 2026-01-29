/* Stralle @ Genesis 010727
 *
 * A donation box
 */

#pragma strict_types

inherit "/d/Faerun/guilds/fire_knives/obj/rack";

#include <macros.h>
#include <files.h>
//#include "../guild.h"

#define FK_DONATION_TAG "_fk_donation_tag"

void
create_rack()
{
    set_name("box");
    set_adj("secure");
    add_adj("black");
    
    set_short("secure black box");
    set_long("This box looks extremely secure. Pristinely "
    +"polished black, it looks immaculate. You can see "
    +"an image of a flaming dagger carved into it. When "
    +"you try to peer inside, you can see nothing but "
    +"inky darkness. You think if you put anything in this "
    +"box, you would not be able to retrieve it again.\n");
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
    
    ob->add_prop(FK_DONATION_TAG, from->query_real_name());
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    remove_rack_entry(ob);
    if (!objectp(to)
        || !IS_PLAYER_OBJECT(to) 
        || !strlen(ob->query_prop(FK_DONATION_TAG)))
    {
        return;
    }
        
    string donator = "yourself";
    if (to->query_real_name() != ob->query_prop(FK_DONATION_TAG))
    {
        donator = capitalize(ob->query_prop(FK_DONATION_TAG));
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

    /*if (((guard = present("guard", environment(this_object()))) ||
        (guard = present("priest", environment(this_object())))) &&
        pl->query_guild_name_occ() != GUILD_NAME && CAN_SEE(guard, pl))
    {
        pl->catch_msg(QCTNAME(guard) + " stops you from picking that.\n");
        return 1;
    }*/
    
    if (pl->query_guild_name_occ() != "Fire Knives")
    {
        pl->catch_msg("Uhm, no. You don't think it's a good idea "
        +"to steal items donated from this box, considering it's "
        +"branded by the mark of an assassination outfit.\n");
        return 1;
    }
    
    return 0;
}        
