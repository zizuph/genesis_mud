/*
 *  /d/Faerun/guilds/vampires/obj/thrall_curse.c
 *
 *  Nerull, 2021
 *
 */

inherit "/std/object";

#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <mail.h>
#include <filter_funs.h>
#include <composite.h>
#include "../guild.h"

              // 30 days
static int    expiration_time = 2592000;
static int    first_received = 0;
static int    exploding = 0;

static string imbuement = "";

//string seconds_to_days();
void destroy_me(object player);
void query_time_left();


int curse_me()
{
    object thrall;
    int current_pool;
    
    thrall = environment(this_object());
     
    int diceroll = random(4);
    
    if (diceroll == 0)
    {
        thrall->catch_tell("You feel weak, and your heart is "
        +"racing fast.\nYou feel less healthy.\n");
    }
    
    if (diceroll == 1)
    {
        thrall->catch_tell("You feel quite sick.\nYou feel less healthy.\n");
    }
    
    if (diceroll == 2)
    {
        thrall->catch_tell("Your bones are aching as if "
        +"you were much older.\nYou feel less healthy.\n");
    }
    
    if (diceroll == 3)
    {
        thrall->catch_tell("You feel pain in your "
        +"limbs.\nYou feel less healthy.\n");
    }
    
    thrall->heal_hp(-1000);
    
    return 1;
}


public void
create_object()
{
    set_name("vampthrall_amp_obj");
    add_adj( ({"moldy"}) );

    set_short("moldy vampthrall_amp");
    set_long("This is a vampire vampthrall_amp_obj.\n");

    add_prop(OBJ_S_WIZINFO,"A vampire thrall curse object.\n");
                      
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    
    add_prop(OBJ_I_INVIS, 100);

    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_TELEPORT, 1);
    
    // By setting this, players should not know that this is in their
    // inventory.
    set_no_show();
    
    //set_alarm(3600.0, 3600.0, &amplify_me());
    
    set_alarm(3600.0, 3600.0, &curse_me());
} 


/*
 * Function name: set_expiration_time
 * Description  : Set how long the reward item should last
 */
void
set_expiration_time(int e_time)
{
    expiration_time = (time() + e_time);
}


/*
 * Function name: enter_env
 * Description  : Called when we enter an environment.
 * Arguments    : object to - the object we are entering.
 *                object from - the object we are leaving.
 */
void
enter_env(object player, object from)
{             
    ::enter_inv(player, from);
        
    // Introduce the reward item when it's new to the player.
    if (first_received == 0)
    {       
        set_expiration_time(expiration_time);
                        
        first_received = 1;
    }
        
    // Tell the player when the reward expires and remove the item. 
    if (expiration_time < time())
    {
        set_alarm(0.2, 0.0, &destroy_me(player));
        return;
    }
        
    /* If experation time is less than one armageddon (12 days),set an
    alarm to remove the item. (to prevent idling to get around the
    expiration time limit that is otherwise checked on log in.)*/
        
    if (query_time_left() < 10360800)
    {
        int time_left;
            
        time_left = query_time_left()+random(5);

        set_alarm(itof(time_left), 0.0, &destroy_me(player));                    
    }
    
    return;
}


/*
 * Function name: init_arg
 * Description  : Upon autoload, initialise the recovered variables.
 * Arguments    : string str - the recovery argument.
 */
void
init_arg(string str)
{
    string *words = explode(str, "#") + allocate(2);

    expiration_time = atoi(words[0]);
    first_received = atoi(words[1]);

    if (!expiration_time)
    {
        expiration_time = (time() + 60);
    }
}


/*
 * Function name: query_auto_load
 * Description  : Get the autoload information with the variables to keep.
 * Returns      : string - the autoload string.
 */
string
query_auto_load()
{
    return MASTER + ":" + expiration_time + "#" + first_received;
}


/*
 * Function name: query_time_left
 * Description  : Get the time left until the reward item expires.
 * Returns      : int - time left in seconds until the item is removed.
 */
int
query_time_left()
{
    return expiration_time-time();
}


/*
 * Function name: destroy_me
 * Description  : Destroys the item when the reward expires
 */
void
destroy_me(object player)
{
    object thrall;
    
    thrall = environment(this_object());
    
    if (thrall->query_prop(LIVE_I_UNDEAD))
    {
        VAMPIRES_MAPPINGS->set_thrall_pool(thrall->query_name(), 3);
        
        THRALL_POOL_LOG("thrall_pool_log",
            "The Thrall " +thrall->query_name() 
            +" is undead. 0 points given, and character set "
            +"to 3.\nObject removed.");
            
            remove_object();
            
            return;
    }
    
    if (VAMPIRES_MAPPINGS->query_thrall_pool(thrall->query_name()) == 0)
    {
        VAMPIRES_MAPPINGS->set_thrall_pool(thrall->query_name(), 2);
    
        THRALL_POOL_LOG("thrall_pool_log",
            "The Thrall " +thrall->query_name() 
            +" received 2 points at the end of expiration.\nObject removed.");
    }
    
    thrall->catch_tell("You feel better.\n");

    remove_object();
}