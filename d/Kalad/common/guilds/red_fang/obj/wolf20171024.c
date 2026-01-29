/*
 * The new wolf for the Red Fang racial guild.
 *
 * Created by Zignur October 2017
 * Zignur 2017-10-18 gave the wolf a unique name
 * Zignur 2017-10-23 Increased swim,
 *                   Made sure it works in teams auto-dismount
 *                   and auto-mount did not work properly before.
 *                   Added a function to prevent abusive behavior
 *                   when you could summon and kill the wolf over
 *                   and over again. The wolf dont reward any xp 
 *                   now and if the player attack a red fang wolf
 *                   he will not be able to summon one until he
 *                   relogs.
 *                   
 *
 *
 */

#pragma save_binary
inherit "/d/Genesis/steed/new/steed";
#include "/d/Genesis/steed/new/steed.h"
#include "/d/Kalad/defs.h"
#include "../default.h"
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <language.h>

/* Global variables */
string owner = "";

/* 
 * Function name: create_steed
 * Description:   Creation function of the steed
 */
public nomask void
create_steed()
{
    setuid();
    seteuid(getuid());   
    set_name("wolf");
    add_name("_rf_wolf_");
    auto_mount      = 1;
    auto_dismount   = 1;
    allow_mounted_combat(1);
    set_no_trans(0);
    
    /* The wolf is well rested and feed when he is summoned*/
    set_fatigue(this_object()->query_max_fatigue());
    set_stuffed(this_object()->query_prop(LIVE_I_MAX_EAT));
    
    add_prop(NPC_I_NO_LOOKS, 1);    
}

/*
 * Function name: refresh_steed
 * Description: refreshes the steed
 *
*/
public void
refresh_steed(object ob)
{
    /* Make the steed fully refreshed */
    set_fatigue(this_object()->query_max_fatigue());
    set_stuffed(this_object()->query_prop(LIVE_I_MAX_EAT));
    refresh_living();
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

/*
 * Function name: set_wolf_desc
 * Description: set the short and gender of the steed
 *
*/
public void
set_wolf_desc(string adj1, string adj2)
{
    if(stringp(adj1))
    {
        switch(adj1)
        {   
        case "male":        
        set_gender(G_MALE);
        add_adj(adj1);
        adj1 = (string)0;
        break;
        case "female":
        set_gender(G_FEMALE);
        add_adj(adj1);
        adj1 = (string)0;
        break;
        default:
        add_adj(adj1);
        break;
        }
    }
    if(stringp(adj2))
    {
        switch(adj2)
        {
        case "male":
        set_gender(G_MALE);
        add_adj(adj2);
        adj2 = (string)0;
        break;
        case "female":
        set_gender(G_FEMALE);
        add_adj(adj2);
        adj2 = (string)0;
        break;
        default:
       add_adj(adj2);
       break;
       }
    }

    if(strlen(adj1) && strlen(adj2))
    {
        set_short(adj1+" "+adj2+" wolf");
    }
    else if(strlen(adj1))
    {
        set_short(adj1+" wolf");
    }
    else if(strlen(adj2))
    {
        set_short(adj2+" wolf");
    }
    else
    {
        set_short("wolf");
    }
}

/*
 * Function name: configure_wolf
 * Description: configure the wolf
*/

public int
configure_wolf(object me)
{
    string adjs,ad1,ad2;
    mapping temp = ([]);
    temp = restore_map(FANG_DIR(doc/wolf_log));
    adjs = temp[me->query_real_name()];
    if(!stringp(adjs))
    {
        return 0;
    }
    sscanf(adjs,"%s|%s",ad1,ad2);
    set_wolf_desc(ad1,ad2);
    set_owner(me);
    return 1;
}

/*
 * Function name: save_wolf
 * Description: saves the wolfs desc in a file
*/

public void
save_wolf()
{
    string *adjs = query_adjs();
    int     size = sizeof(adjs);    
    mapping temp = restore_map(FANG_DIR(doc/wolf_log));
    
    if (size > 2)
    {
        adjs = slice_array(adjs, 1, 2);
    }

    if (size == 1)
    {
        temp[query_owner()] = adjs[0] + "|";
    }
    else
    {
        temp[query_owner()] = implode(adjs, "|");
    }
    
    save_map(temp, FANG_DIR(doc/wolf_log));
    
}


/* Function name: configure_steed
 * Description:   Give the steed some standard hitlocs and attacks, called
 *                from create_creature. Redefine when you need other
 *                hitlocs or attacks.
 */
public void
configure_steed()
{
    set_race_name("wolf");
    add_name("_rf_wolf_");
    set_gender(0);
    set_short("strong wolf");
    set_long("This is a strong and ferocious looking wolf. Bred by "+
      "goblins as a steed, it looks quite powerful. Only goblins would "+
      "know how to ride such a creature. It growls and stares at you "+
      "with fierce blood-shot eyes.\n");
     
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
    
    /* Some skills */
    
    set_skill(SS_CLIMB,        30);
    /* Zignur 2017-10-23 Buffing swimming so the wolf dont drown in ME */
    set_skill(SS_SWIM,         50);
    set_skill(SS_SNEAK,        50);
    set_skill(SS_HIDE,         50);
    set_skill(SS_AWARENESS,    50);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENSE,      50);
    
    /* Set what food the wolfie can eat */
    set_allowed_food(({"leftover", "organ", "steak", "fish","sausage", 
                       "meat", "chicken", "platter"}));
                       
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
    /* Give a message so the rider knowns what happended */
    
    living->catch_msg("You are unable to proceed while mounted, you " +
    "dismount the " + short() + ".\n");
    
    /* Zignur 2017-10-23 make sure the autodismount and automount stays on */
    auto_mount      = 1;
    auto_dismount   = 1;
    
    return living->move_living(how, to_dest, dont_follow, no_glance);
}  

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
        TO->query_short()+" but the wolf snarls wickedly and tries to bite " +
        TP->query_objective() + ".\n");

        return STEED_STS_LIVING_NO_RIDER;
    }
    
    /* See if we are skilled enough */
    if(rider->query_skill(SS_WOLF_RIDING) < 1)
    {
        rider->catch_msg("You have no idea how to ride a wolf," +
        " perhaps you should train your skills in wolf riding?\n");                  
       
       return STEED_STS_ERROR;
    }  
    return STEED_STS_OK;
}

/* Zignur 2017-10-23 Make sure we dont reward any xp for killing wolves */
public void
do_die(object killer)
{
    killer->add_prop("_rf_wolf_attacked", 1);
    command("emote manages to avoid a fatal blow by sneaking away into the shadows.");
    this_object()->remove_object();
  
}

/* Zignur 2017-10-23 The wolf will notify its owner when he is attacked */
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


