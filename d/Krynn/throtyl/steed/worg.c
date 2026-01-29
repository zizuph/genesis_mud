/*
 * Summonable worg, purchasable from East Keep in Throtyl.
 *
 * Created by Arman - July 2020
 * Based on Red Fang mount created by Zignur.
 *
 */

#pragma save_binary
inherit "/d/Genesis/steed/new/steed";
inherit "/d/Krynn/throtyl/steed/worg_lootbag";

#include "/d/Genesis/steed/new/steed.h"
#include "/d/Krynn/common/defs.h"

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <language.h>

/* Global variables */
string owner = "";

string * worg_adj1 = ({ "powerful", "strong", "muscular", "red-eyed",
                        "white", "black", "grey", "huge" });

string * worg_adj2 = ({ "foul-tempered", "malevolent", "nasty", "mean",
                        "bad-tempered", "aggressive", "hostile" });

string * worg_stuff_state = ({ "ravenous with hunger", "famished",
		     	   "hungering", "satiated", "gorged with food" });

#define STEED_ROOM "/d/Krynn/throtyl/steed/steed_room"

public int
query_throtyl_worg()
{
    return 1;
}

/* 
 * Function name: create_steed
 * Description:   Creation function of the steed
 */
public nomask void
create_steed()
{
    setuid();
    seteuid(getuid());   
    set_name("worg");
    add_name("_throtyl_worg_");
    auto_mount      = 1;
    auto_dismount   = 1;
    allow_mounted_combat(1);
    set_no_trans(0);
    
    add_prop(NPC_I_NO_LOOKS, 1);    
}

/*
 * Function name: refresh_steed
 * Description: refreshes the steed
 *
*/
public void
refresh_steed(int fatigue)
{
    /* Make the steed fully refreshed */
    refresh_living();
    set_fatigue(fatigue);
    set_stuffed(this_object()->query_prop(LIVE_I_MAX_EAT));

}

/*
 * Function name: set_owner
 * Description: Set the owner of the steed
 *
*/
public void
set_owner(object ob)
{
    owner = ob->query_real_name();
}

/*
 * Function name: query_owner
 * Description: See who owns the steed
 *
*/
public string
query_owner()
{
    return owner;
}

string
query_fatigue_desc()
{
    if(query_fatigue() < 1)
        return " He is looking extremely exhausted.";
    if(query_fatigue() < 20)
        return " He is looking tired.";

    return "";
}

string
query_stuffed_desc()
{
    return "He is " +GET_NUM_DESC(this_object()->query_stuffed(), 
        this_object()->query_prop(LIVE_I_MAX_EAT), worg_stuff_state)+
	".";

}

/* Function name: configure_steed
 * Description:   Give the steed some standard hitlocs and attacks, called
 *                from create_creature. Redefine when you need other
 *                hitlocs or attacks.
 */
public void
configure_steed()
{
    string ad1 = ONE_OF(worg_adj1);
    string ad2 = ONE_OF(worg_adj2);

    set_race_name("worg");
    add_name("_throtyl_worg_");
    set_gender(0);
    add_adj(ad1);
    add_adj(ad2);
    set_short(ad1+" "+ad2+" worg");
    set_long("@@long_desc");
     
    set_stats( ({ 120, 120, 120, 20, 20, 100 }) );
       
    set_attack_unarmed(0, 20, 30, W_IMPALE, 30, "jaws");
    set_attack_unarmed(1, 15, 20, W_SLASH,  30, "right paw");
    set_attack_unarmed(2, 15, 20, W_SLASH,  30, "left paw");
    set_attack_unarmed(3, 10, 10, W_SLASH,  10, "hind legs");
    
    set_hitloc_unarmed(0, 10, 15, "head");
    set_hitloc_unarmed(1, 10, 40, "body");
    set_hitloc_unarmed(2, 15, 20, "right paw");
    set_hitloc_unarmed(3, 10, 20, "left paw");
    set_hitloc_unarmed(4, 10, 5, "hind legs");
    
    /* default skills */    
    set_skill(SS_CLIMB,        30);
    set_skill(SS_SWIM,         50);
    set_skill(SS_SNEAK,        50);
    set_skill(SS_HIDE,         50);
    set_skill(SS_AWARENESS,    50);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENSE,      50);

    set_alignment(-400);
    
    /* Set what food the worg can eat */
    set_allowed_food(({"leftover", "organ", "steak", "fish","sausage", 
                       "meat", "chicken", "platter"}));
                       
} 

string
long_desc()
{
    string text = "This is a nasty-looking worg common to the moors of " +
      "Throtyl and the Stormshire Forest. Closer in size to a horse " +
      "than your average wolf, this beast is the steed of choice for " +
      "hobgoblins and raiders. ";

    text += query_stuffed_desc();
    text += query_fatigue_desc();

    if ((TO->query_leader())->query_name() == TP->query_name() ||
        (TO->query_driver())->query_name() == TP->query_name())
    {
        return text + additional_longdesc() + 
            "\n";
    }
    return text + additional_longdesc() + "\n";
}


/* Function name: dismount_lead_move
 * Description:   Dismount, lead horse, and move to given destination.
 *                Used for auto-dismount functionality.
 *
 * Arguments:     see original move_living function.
 * Returns:       see original move_living function.
 *
 *    Not sure why this was masked.. commented out. Arman, June 2021
 */

/*
public varargs int dismount_lead_move(object living, string how, 
                                      mixed to_dest, int dont_follow,
                                      int no_glance)
{
    int sts;
    do_dismount(living);

    sts = do_lead(living);
    handle_lead_status(sts, living);
    
    living->catch_msg("You are unable to proceed while mounted, you " +
    "dismount the " + short() + ".\n");
   
    return living->move_living(how, to_dest, dont_follow, no_glance);
}  

*/

/*
 * Function:     can_mount()
 * Description:  Make certain only the owner can mount and that
 *               the owner is skilled enough.
 *
 */
public int
can_mount(object rider)
{
    string currentRider, wolfOwner;

    currentRider = rider->query_real_name();
    wolfOwner = this_object()->query_owner();

    /* Make certain only the owner can mount */
    if (currentRider != wolfOwner)
    {
        say(QCTNAME(TP) + " attempts to mount the " +
        TO->query_short()+" but it snarls wickedly and tries to bite " +
        TP->query_objective() + ".\n");

        rider->catch_msg("You attempt to mount the " +
        TO->query_short()+ " but it snarls wickedly and tries to " +
        "bite you.\n");

        return STEED_STS_LIVING_NO_RIDER;
    }
    
    /* See if we are skilled enough */
    if(rider->query_skill(SS_RIDING) < 40)
    {
        rider->catch_msg("You have no idea how to ride a worg," +
        " perhaps you should train your skills in riding?\n");                  
       
       return STEED_STS_SKILL_TOO_LOW;
    }  

    if(rider->query_skill(SS_ANI_HANDL) < 40)
    {
        rider->catch_msg("You have no idea how to handle a worg," +
        " perhaps you should train your skills in animal handling?\n");
       
       return STEED_STS_SKILL_TOO_LOW;
    }

    if(rider->query_alignment() > 100)
    {
        rider->catch_msg("The worg's dark nature won't allow you " +
            "near it. You need to be more evil to be able to use the " +
            "worg as a steed.\n");
       
       return STEED_STS_CANNOT_BE_MOUNTED;
    }

    if(rider->query_race_name() == "ogre")
    {
        rider->catch_msg("You are too big to ride a worg! You would " +
            "crush it!\n");
       
       return STEED_STS_CANNOT_BE_MOUNTED;
    }

    return STEED_STS_OK;
}


public void
do_die(object killer)
{
    killer->add_prop("_worg_attacked", 1);
    command("emote gives off a fierce growl before leaping away into the"
        +   " shadows.");
    this_object()->move(STEED_ROOM, 1);
  
}

public void
attacked_by(object attacker)
{
    string wolfOwner;
    wolfOwner = this_object()->query_owner();
    object owner = find_living(wolfOwner);
    command ("emote gives off a frightful bone-chilling howl.");
    owner->catch_tell("In the distance you hear a frightful bone-chilling howl."
            +  " A desperate call from your wounded "  + short() + ".\n");
       
}

/* Function name: reset_auto_functions
 * Description:   resets the auto functions to off.
 *                Disabled... don't understand the purpose of masking the auto
 *                functions.  Arman, June 2021.
 */

/*
public void reset_auto_functions()
{
    auto_dismount = 1;
    set_auto_mount(1);
}
*/

void
init_living()
{

    /* lootbag: */
    add_action(do_fill, "fill");
    add_action(do_empty,"empty");
    add_action(do_strap, "strap");
    add_action(do_unstrap, "unstrap");
    add_action(do_close, "close");
    add_action(do_open, "open");
    add_action(raidloot, "raidloot");

    ::init_living();
}

