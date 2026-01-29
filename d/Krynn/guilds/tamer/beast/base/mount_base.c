#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/steed/new/steed";

#include "/d/Genesis/steed/new/steed.h"

#include <ss_types.h>
#include <macros.h>
#include "defs.h"

#include "genus.c"
//#include "emote.c"

// Global Variables
static status   gIsMountable;

public void
create_mount()
{
    gIsMountable = 1;
}

public int
query_mountable_size()
{
    string  size_desc = MANAGER->query_pet_size(query_tamer_name());
    mixed  *size_val;
    int     height;

    if (sizeof(size_val = GENUS->query_genus_sizes(size_desc)))
    {
        height = GENUS->query_height(query_genus(), query_race_name());
        height = ((height * size_val[0] / 100) * query_maturity()) / 8;
        
        return height;
    }

    return 50;
}
/* 
 * Function name: create_steed
 * Description:   Creation function of the steed
 */
public nomask void
create_steed()
{
    create_mount();
    setuid();
    seteuid(getuid());
    
    auto_mount      = 1;
    auto_dismount   = 1;
    allow_mounted_combat(1);
    set_no_trans(0);

    add_prop(CONT_I_HEIGHT, &query_mountable_size());
} /* create_steed */

/*
 * Function name: handle_mount_status
 * Description:   handle mount status in order to give appropriate messages.
 * Arguments:     int status - see steed.h
 *                object living
 * Returns:       void
 */
public void
handle_mount_status(int sts, object living)
{
    if (sts == STEED_STS_CANNOT_BE_MOUNTED)
    {
        if (!GENUS->query_genus_rideable(this_object()))
        {
            living->catch_msg(QCTNAME(this_object()) + " is not suitable for "
            + "riding.\n");
            return;
        }
        
        if (!MANAGER->query_pet_rideable(query_tamer_name(), this_object()))
        {
            living->catch_msg(QCTNAME(this_object()) + " is too small for "
            + "you to be able to mount " + query_objective() + ".\n");
            return;
        }
        
        if (living->query_real_name() != query_tamer_name())
        {
            living->catch_msg("The " + QTNAME(this_object()) + " refuses to "
            + "let you mount " + this_object()->query_objective() + ".\n");
            return;
        }
        
        if (living->has_tamer_maneuver_shadow())
        {
            living->catch_msg("You cannot ride " + QTNAME(this_object()) + " "
            + "while it is maneuvered to intercept your enemies.\n");
            return;
        }
    }
    
    return ::handle_mount_status(sts, living);
}

public int
can_mount(object living)
{
    if (!gIsMountable)
        return STEED_STS_CANNOT_BE_MOUNTED;
    
    if ((int)call_self("query_unconscious"))
    {
        living->catch_msg("The " + short() + " is unconscious.\n");
        return STEED_STS_CANNOT_BE_MOUNTED;
    }

    if (MANAGER->query_pet_rideable(query_tamer_name(), this_object()) &&
        living->query_real_name() == query_tamer_name())
    {
        if (!GENUS->query_genus_rideable(this_object()))
            return STEED_STS_CANNOT_BE_MOUNTED;
            
        if (living->has_tamer_maneuver_shadow())
            return STEED_STS_CANNOT_BE_MOUNTED;
        
        if (living->query_skill(SS_RIDING) < 30)
        {
            living->catch_msg("You lack the proper skills to ride "
            + QTNAME(this_object()) + ".\n");
            return STEED_STS_SKILL_TOO_LOW;
        }
    
        return ::can_mount(living);
    }
    
    return STEED_STS_CANNOT_BE_MOUNTED;
}

public int
follow_leader_test(mixed dest)
{
    if ((int)call_self("query_unconscious"))
        return -3;
    
    if (MANAGER->query_pet_stay(query_tamer_name()))
        return -2;
    
    if (environment(this_object())->query_pet_house())
        return -1;
    
    if (environment(this_object()) == dest)
        return 0;
    
    if (stringp(dest))
    {
        if (IN_ARRAY(dest, ({"X", "M"})))
        {
            object tamer;
            
            if (objectp(tamer = query_tamer()) && environment(tamer))
                return move_living(dest, environment(tamer));
            
            return 2;
        }
        
        this_object()->command("$" + dest);
        return 1;
    }
    
    return 0;
}

public int
follow_leader(mixed dest)
{
    int     test;
    object  tamer;
    
    test    = follow_leader_test(dest);
    
    // Test was successful but movement wasnt, lets just move the pet
    if (test > 0 && objectp(tamer = query_tamer()) &&
        environment() != environment(tamer))
    {
        tell_room(environment(), QCTNAME(this_object()) + " " + query_mm_out()
        + "\n");
        tell_room(environment(tamer), QCTNAME(this_object()) + " "
        + query_mm_in() + "\n");
        follow_leader_test("M");
    }
    
    return test;
}

public varargs int dismount_lead_move(object living, string how, 
                                      mixed to_dest, int dont_follow,
                                      int no_glance)
{
    living->catch_msg("You are unable to proceed while mounted, you " +
    "dismount the " + short() + ".\n");
    MANAGER->add_achievement(query_tamer_name(), CANNOT_RIDE);
    
    if (auto_dismount)
    {
        do_dismount(living);
        return living->move_living(how, to_dest, dont_follow, no_glance);
    }
    
    return 7;
}

public int unlead_and_mount_pet(object player, int move_result)
{
    if (auto_mount && (!objectp(player->query_steed()) ||
        !objectp(player->query_prop(LIVE_O_STEED))))
        do_mount(player);
    
    return move_result;
}

public int
check_unmounted_destination(object to_dest)
{
    return STEED_STS_OK;
}

void
fail_mount_hook(object rider)
{
}

public int
lead(string s)
{
    return 0;
}

public int
unlead(string s)
{
    return 0;
}