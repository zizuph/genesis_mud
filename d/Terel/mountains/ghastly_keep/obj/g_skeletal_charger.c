/*
 *  /d/Raumdor/steeds/skeletal_steed.c
 *
 *  An undead skeletal steed.
 *
 *  Based on a steed by Deagol, Middle Earth
 *  Nerull. 2010
 *
 *
 *  Relase date:
 *
 *
 *  Date:                      What is done:                           By whom:            
 *  ---------------------------------------------------------------------------
 *  20/04-17                   Language tweak complete                  Gorboth  
 *  27/04-17                   Alter to make it weak in combat         Znagsnuf
 *  27/09-17     Made the steed a bit better with auto mount/dismount  Znagsnuf
 *  02/11-17       Borrowed some code from Zignur so make it usable    Znagsnuf
 */

inherit "/d/Genesis/steed/new/steed";
inherit "/std/act/action";
inherit "/std/act/chat";
inherit "/lib/commands";
inherit "/std/shadow";

#include "defs.h"
#include <adverbs.h>
#include <const.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Genesis/steed/new/steed.h"

void    do_fatigue();
int     can_attack();

string    ghastly_owner;

void
create_steed()
{

    setuid();
    seteuid(getuid());

    set_name( ({ "charger", "steed" }) );
    set_pname( ({ "chargers", "steeds" }) );
    add_name("_ghastly_skeletal_steed");
    set_adj( ({ "ghastly", "skeletal" }) );
    set_gender(G_MALE);
    
    set_stats(({180, 150, 300, 40, 40, 150}));

    set_short("ghastly skeletal charger");
    set_long("Sleekly beautiful muscles that roll underneath a supple "
            + "coat hanging majestically on its frame; a flowing mane "
            + "that unfurls and whips as the wind calls it; feet that "
            + "pound the ground with a natural canter and gait; quivering "
            + "powerful haunches with mighty speed; a tossing head "
            + "with eyes rolling backward - big, genuine eyes that saw "
            + "through and with you. So was this horse - who founded "
            + "exploration throughout Terel on his burly shoulders. "
            + "But that was in another lifetime. An eerie blue aura "
            + "now surrounds him, making him the most ghastly creature you "
            + "have ever laid your eyes upon. His massive skeletal ribcage "
            + "doesn't allow room for a saddlebag.\n"
            + "His flowing mane is covered with unfolding shadows.\n"
            + "He has glowing icy blue eyes.\n");

    add_prop(OBJ_S_WIZINFO, "This horse has been running around in "
        + "Terel longer than others, making him immune to fatigue "
        + "drain while in the domain. This steed doesn't allow any "
        + "saddlebag for balance reasons.\n");

    set_hitloc_unarmed(1, 40, 15, "skeletal head");
    set_hitloc_unarmed(2, 40, 10, "right skeletal hoof");
    set_hitloc_unarmed(3, 40, 10, "left skeletal hoof");
    set_hitloc_unarmed(4, 40, 45, "skeletal body");
    set_hitloc_unarmed(5, 40, 20, "left skeletal hoof");

    set_attack_unarmed(0, 40, 40, W_SLASH, 50, "right skeletal hoof");
    set_attack_unarmed(1, 40, 40, W_SLASH, 50, "left skeletal hoof");
    set_attack_unarmed(2, 40, 40, W_SLASH, 50, "skeletal hind hoofs");
    set_attack_unarmed(3, 40, 40, W_SLASH, 50, "skeletal hind hoofs");

    set_m_in("comes running in");
    set_m_out("runs");
    
    set_skill(SS_CLIMB,     40);
    set_skill(SS_SWIM,      40);
    set_skill(SS_AWARENESS, 40);

    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
    add_prop(CONT_I_WEIGHT, 230000);
    add_prop(LIVE_I_UNDEAD,  1);
    add_prop(OBJ_M_NO_ATTACK, can_attack);
    
    set_alignment(0);
    set_fatigue(TO->query_max_fatigue());
    set_stuffed(TO->query_prop(LIVE_I_MAX_EAT));
    
    auto_mount      = 1;
    auto_dismount   = 1;
    allow_mounted_combat(1);
    set_no_trans(0);
    
    // Make sure the horse stays refreshed.
    set_alarm(1.0, 20.0,  &do_fatigue(TO));
}

/*
 * Function:     do_fatigue()
 * Description:  Find out if the horse is in Terel and adds
 *               fatigue to it, it will never be tired when in
 *               Terel. Add food as well.
 */

void
do_fatigue()
{   
    if (wildmatch("/d/Terel*", file_name(ENV(TP)))) 
    {    
        TO->set_fatigue(TO->query_max_fatigue());
        TO->set_stuffed(TO->query_prop(LIVE_I_MAX_EAT));
    }   
}

/*
 * Function:     can_attack()
 * Description:  
 */
int
can_attack()
{
    // Make it not attackable by other npc's
    if (TP->query_npc())
    {
        return 1;
    }
    return 0;
}

/*
 * Function:     set_ghastly_owner()
 * Description:  Set a owner of this steed.
 */
public string
set_ghastly_owner(string owner)
{        
    ghastly_owner = owner;
}

/*
 * Function:     query_ghastly_owner()
 * Description:  Who's the owner?
 */
public string
query_ghastly_owner()
{
    return ghastly_owner;
}


/*
 * Function:     can_mount()
 * Description:  Everyone can mount it right now.
 *               In the future only the worth will be able to
 *               mount it.
 *
 *               Todo: Refuse mounters, attack them, and tell
 *                     owner.  
 *
 */
public int
can_mount(object rider)
{
    object new_rider, old_rider;

    new_rider = rider->query_name();
    old_rider = TO->query_ghastly_owner();
    
    if (new_rider != old_rider)
    {

        say(QCTNAME(TP) + " attempts to mount the " + short(TO) + " but "
            + "the steed doesn't recognize " + TP->query_objective() + " as "
            + "the owner.\n");

        return STEED_STS_LIVING_NO_RIDER;
    }
 
    return STEED_STS_OK;
}

/* Function name: dismount_lead_move
 * Description:   Dismount, lead horse, and move to given destination.
 *                Used for auto-dismount functionality.
 *                 
 *                Zignur:
 *                We override this function to make the steed able to
 *                move around more smoothly.
 *
 * Arguments:     see original move_living function.
 * Returns:       see original move_living function.
 */
public varargs int dismount_lead_move(object living, string how, 
                                      mixed to_dest, int dont_follow,
                                      int no_glance)
{
    int sts;
    do_dismount(living);
    // Dismount went ok, now let's lead.
    sts = do_lead(living);
    handle_lead_status(sts, living);
    
    living->catch_msg("You are unable to proceed while mounted, you " +
    "dismount the " + short() + ".\n");
   
    return living->move_living(how, to_dest, dont_follow, no_glance);
}

/* Function name: reset_auto_functions
 * Description:   resets the auto functions to off.
 */
public void reset_auto_functions()
{
    auto_dismount = 1;
    set_auto_mount(1);
} 