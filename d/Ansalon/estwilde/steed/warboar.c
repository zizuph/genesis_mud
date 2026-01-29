/*
 * Summonable war boar, purchasable from Iron Delving.
 *
 * Created by Arman - October 2021
 * Based on Red Fang mount created by Zignur.
 *
 */

#pragma save_binary
inherit "/d/Genesis/steed/new/steed";
inherit "/d/Ansalon/estwilde/steed/warboar_lootbag";

#include "/d/Genesis/steed/new/steed.h"
#include "/d/Ansalon/common/defs.h"

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <language.h>

/* Global variables */
string owner = "";

string * boar_adj1 = ({ "powerful", "strong", "muscular", "long-tusked",
                        "bristled", "striped", "grey", "aggressive" });

string * boar_adj2 = ({ "dire", "great", "war", "war", "war" });

string * boar_stuff_state = ({ "ravenous with hunger", "famished",
		     	   "hungering", "satiated", "gorged with food" });

#define STEED_ROOM "/d/Ansalon/estwilde/steed/steed_room"
#define ONE_OF(x)     ((x)[random(sizeof(x))])

public int
query_estwilde_boar()
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
    set_name("boar");
    add_name("_estwilde_boar_");
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
        this_object()->query_prop(LIVE_I_MAX_EAT), boar_stuff_state)+
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
    string ad1 = ONE_OF(boar_adj1);
    string ad2 = ONE_OF(boar_adj2);

    set_race_name("boar");
    add_name("_estwilde_boar_");
    set_gender(0);
    add_adj(ad1);
    add_adj(ad2);
    set_short(ad1+" "+ad2+" boar");
    set_long("@@long_desc");
     
    set_stats(({180, 150, 250, 40, 40, 150}));
       
    set_attack_unarmed(0, 20, 30, W_IMPALE, 30, "tusks");
    set_attack_unarmed(1, 15, 20, W_SLASH,  30, "right hoof");
    set_attack_unarmed(2, 15, 20, W_SLASH,  30, "left hoof");
    set_attack_unarmed(3, 10, 10, W_SLASH,  10, "hind legs");
    
    set_hitloc_unarmed(0, 10, 15, "head");
    set_hitloc_unarmed(1, 10, 40, "body");
    set_hitloc_unarmed(2, 15, 20, "right hoof");
    set_hitloc_unarmed(3, 10, 20, "left hoof");
    set_hitloc_unarmed(4, 10, 5, "hind legs");
    
    /* default skills */    
    set_skill(SS_CLIMB,        30);
    set_skill(SS_SWIM,         50);
    set_skill(SS_SNEAK,        50);
    set_skill(SS_HIDE,         50);
    set_skill(SS_AWARENESS,    50);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENSE,      50);

    set_alignment(0);
    
    /* Set what food the boar can eat */
    set_allowed_food(({"vegetable", "mushroom", "steak", "fish", "sausage", 
        "meat", "chicken", "platter", "herb", "soup", "fruit", "apple"}));
                       
} 

string
long_desc()
{
    string text = "This especially large and aggressive boar is of a " +
      "kind found exclusively on the plains of Estwilde, and is often " +
      "bred by the hill dwarves of that region as vicious guardians and " +
      "war pigs. Closer in size to a very muscular pony " +
      "than your average wild pig, this beast is the steed of choice for " +
      "dwarven warriors as shock cavalry. ";

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
        TO->query_short()+" but it squeals viciously and tries to bite " +
        TP->query_objective() + ".\n");

        rider->catch_msg("You attempt to mount the " +
        TO->query_short()+ " but it squeals viciously and tries to " +
        "bite you.\n");

        return STEED_STS_LIVING_NO_RIDER;
    }
    
    /* See if we are skilled enough */
    if(rider->query_skill(SS_RIDING) < 30)
    {
        rider->catch_msg("You have no idea how to ride a boar," +
        " perhaps you should train your skills in riding?\n");                  
       
       return STEED_STS_SKILL_TOO_LOW;
    }  

    if(rider->query_skill(SS_ANI_HANDL) < 30)
    {
        rider->catch_msg("You have no idea how to handle a boar," +
        " perhaps you should train your skills in animal handling?\n");
       
       return STEED_STS_SKILL_TOO_LOW;
    }

    if(rider->query_race_name() != "dwarf" &&
       !rider->query_guild_member("Shieldbearers of Iron Delving"))
    {
        rider->catch_msg("The boar is trained to only allow dwarves " +
            "and their Shieldbearer allies to ride them! It rejects " +
            "your attempts to mount it.\n");
        say(QCTNAME(TP) + " attempts to mount the " +
            TO->query_short()+" but is rejected.\n");
       
       return STEED_STS_CANNOT_BE_MOUNTED;
    }

    return STEED_STS_OK;
}


public void
do_die(object killer)
{
    killer->add_prop("_boar_attacked", 1);
    command("emote gives off a fierce grunt before darting away.");
    this_object()->move(STEED_ROOM, 1);
  
}

public void
attacked_by(object attacker)
{
    string wolfOwner;
    wolfOwner = this_object()->query_owner();
    object owner = find_living(wolfOwner);
    command ("emote gives off a high-pitched shriek!");
    owner->catch_tell("In the distance you hear a high-pitched shriek!"
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
    add_action(boarloot, "boarloot");

    ::init_living();
}


/* Function name: do_feed
 * Description:   Try to feed this living.
 * Arguments:     object - the food object
 *                object - feeder, defaults to this_player()
 * Returns:       int 0 - failed feeding, 1 - success
 */
 public varargs int
 do_feed(object o, object feeder)
 {
     // Check if we can eat this
     if (!can_feed(o))
         return 0;
 
     if (!objectp(feeder))
         feeder = this_player();
     // Transfer food and eat
     if (o->move(TO) == 0)
     {
        hook_feed(feeder, o);
 
        // This doesn't work. Command("eat all") still returns a
        // value if the living is too full to eat.
        // Try to eat, otherwise drop on the floor
        //       if (!command("eat all"))
        //       {
        //            hook_fail_eat(o);
        //        }
 
        // Instead, use this to make sure the steed can eat it.
 
        if (!TO->eat_food(o->query_amount(),1))
      {
        hook_fail_eat(o);
      }
 
        command("eat all");
        set_alarm(0.2, 0.0, &command("drop foods"));
     }
     else // the move failed, drop food on the floor
     {
         hook_fail_food_move(feeder, o);
     }
 
     return 1;
 }