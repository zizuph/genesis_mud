/* A green ointment - Coded 29/09/95 by Tulix III */

inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Emerald/tulix/t_defs.h"

#pragma strict_types

/* Prototype functions */
public int rub_ointment(string str);

public void
create_object()
{
    set_name("ointment");
    set_pname("ointments");
    set_adj("green");
    add_adj("emerald");

    set_short("green ointment");
    set_pshort("green ointment");
    set_long("It is a green ointment, which contains something extracted " +
        "from emeralds, judging by the colour. It does not smell too bad, " +
        "and is cool to touch.\nThere is a slight hint of " +
        "magic about it too.....\n");

    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_VOLUME, 30);
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VALUE, 500);

    add_prop(MAGIC_AM_ID_INFO, ({ 
        "The ointment appears to be magical.\n", 0,
        "The ointment will transform some living beings.\n", 20,
        "The ointment seems to contain some emerald extract.\n" +
        "The ointment is used to transform aquatic beings, possibly.\n", 40,
        "This ointment is derived from emerald extract fortified with " +
        "a smattering of platinum. It could be used to transform cursed " +
        "aquatic beings back into their normal form.\n", 80 }) );
    
    add_prop(OBJ_S_WIZINFO, "This ointment is needed to "
        + "complete a certain quest.\n"
        + "Ask Tulix for more details.\n");
}

public void
init()
{
    ::init();
    add_action(rub_ointment, "rub");
    add_action(rub_ointment, "apply");
}

public int
rub_ointment(string str)
{
    object rubbed, target;
    string desc;
    
    /* Is this object the one being rubbed? */
    if (!strlen(str))
    {
        notify_fail("What do you want to do?\n");
        return 0;
    }

    /*  use parse_command to check what player wants to rub ointment onto. */
    parse_command(str, ENV(this_player()) ,
        "[the] %o [onto] [on] [to] [over] [the] %o", rubbed, target);
    
    /* Is this object the one being rubbed? */
    if (rubbed != TO)
    {
        notify_fail("What do you want to do to what, exactly?\n");
        return 0;
    }

    if (!target)
    {
        notify_fail("What do you wish to apply the ointment to?\n");
        return 0;
    }

    if (target->query_npc())
    {
        desc = QTNAME(target);
        this_player()->catch_msg("You try to apply the ointment to " + 
            desc + ".\n");

        if (this_player()->query_base_stat(SS_DEX) >= 100)
        {
            this_player()->catch_msg("You succeed in rubbing ointment over " +
                desc + ".\n");
            target->apply_ointment(this_player());
            this_object()->remove_object();
            return 1;
        }
        else
        {
            tell_room(ENV(this_player()), QCTNAME(this_player()) + 
                " tries to rub ointment over " + desc + ", but fails.\n",
                this_player() );
            this_player()->catch_msg("It seems that " + desc +
                " is too quick for you!\n");
            return 1;
        }
    }
    
    if (living(target))
    {
        desc = QTNAME(target);
        this_player()->catch_msg("You try to apply the ointment to " + 
            desc + ".\n");

        if (this_player()->query_base_stat(SS_DEX) >=
            target->query_base_stat(SS_DEX) )
        {
            this_player()->catch_msg("You succeed in rubbing ointment over " +
                desc + ".\n");
            target->catch_msg(QCTNAME(this_player()) + " rubs a green " +
                "ointment over you.\n");
            this_object()->remove_object();
            return 1;
        }
        else
        {
            tell_room(ENV(this_player()), QCTNAME(this_player()) + 
                " tries to rub ointment over " + desc + ", but fails.\n",
                this_player() );
            this_player()->catch_msg("It seems that " + desc +
                " is too quick for you!\n");
            return 1;
        }
    }
    else
    {
        desc = target->query_short(this_player());
        this_player()->catch_msg("You rub the ointment over the " + desc +
            ".\n"); 
        write("Nothing much seems to happen though.\n");
        
        this_object()->remove_object();
        return 1;
    }
}

