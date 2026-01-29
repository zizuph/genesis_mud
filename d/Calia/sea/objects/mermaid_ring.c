
/* 
    A mermaid ring, reward for doing the mermaid quest in Calia. 
    When worn in a water room of Calia it allows the player 
    to breathe water with effectiveness 70/100. 

    Coded by Maniac, 10/9/96, revised 12/3/97, Maniac, 
    made wearable on any finger, 18/3/97, Maniac. 
    made into a wearable item rather than armour, 27/12/98, Maniac
*/ 

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <files.h>

#include "defs.h"
#include SEA_QUESTS

inherit "/std/object";
inherit "/lib/wearable_item";  

function this_vbfc; 
int losing_it; 

void
create_object()
{
    set_name("ring"); 
    set_pname("rings"); 
    set_adj(({"silver", "mermaid"})); 
    set_short("silver mermaid ring"); 
    add_name(MERMQ_RING_ID); 

    set_long("A silver ring set with the tiny figurine of a mermaid. " + 
             "The exquisite lady of the deeps is made from " +
             "tiny sparkling gemstones and the purest of " +
             "precious metals. From the minute diamond scales of her " +
             "fish tail to the gold tracings of her hair, she is " +
             "flawless. She looks almost disturbingly real, and your " +
             "gaze is drawn to her aquamarine eyes.\n"); 

    config_wearable_item(A_ANY_FINGER, 1, 6, this_object()); 

    add_prop(OBJ_I_VALUE, 0); 
    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment"}));  
    add_prop(MAGIC_AM_ID_INFO, 
                     ({"The tiny mermaid on this ring is enchanted " +
                     "to allow the wearer to breathe in the " +
                     "waters of Calia.\n",10, 
                     "The magic in this ring is drawn from the " +
                     "power of the Elemental Diabrecho, Lord " +
                     "of the waters in Calia. Hence the wearer " +
                     "may breathe in any water of His domain.\n",25}) );

    add_prop(OBJ_S_WIZINFO, "This ring is the autoloading quest " +
                "item for the mermaid quest in the sea of Calia. " +
                "It is automatically restored to anyone losing it " +
                "if the player returns to the mermaid rock. " +
                "The ring gives players MAGIC_I_BREATH_WATER of 70 " +
                "in rooms of the Calia domain.\n"); 

    add_item(({"aquamarine eyes", "mermaid eyes"}), 
            "One of the mermaid's aquamarine eyes winks at you! " +
            "You hear a musical voice in your head say: \"If you lose " +
            "me, seek me where you found me.\" If you actually _want_ " +
            "to <lose> the ring, that is also possible.\n"); 

    add_prop(OBJ_I_WEIGHT, 50); 
    add_prop(OBJ_I_VOLUME, 50); 
    add_prop(OBJ_M_NO_DROP, "You may <lose> the silver mermaid " +
                            "ring if you want, but you may " +
                            "not drop it.\n");  
    add_prop(OBJ_M_NO_GIVE, "You may <lose> the silver mermaid " +
                            "ring if you want, but you may not " +
                            "give it to anyone.\n"); 
    add_prop(OBJ_M_NO_SELL, 1); 
    add_prop(OBJ_M_NO_STEAL, 1); 
    losing_it = 0; 
}

/*
 * Function name: remove
 * Description  : This function might be called when someone tries to remove
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour to remove.
 * Returns      : int  0 - Remove the armour normally.
 *                     1 - Remove the armour, but print no messages.
 *                    -1 - Do not remove the armour, print default message.
 *                string - Do not remove the armour, use this message.
 */
public mixed
remove(object obj)
{
    object player = query_worn();
    if (!objectp(player))
    {
        // Something is wrong because we can't get the wearer.
        return -1;
    }

    player->remove_mermaid_ring_shadow();
    return 0;
}


/*
 * Function name: wear
 * Description  : This function might be called when someone tries to wear
 *                this armour. To have it called, use set_wf().
 * Arguments    : object obj - The armour we want to wear.
 * Returns      : int  0 - The armour can be worn normally.
 *                     1 - The armour can be worn, but print no messages.
 *                    -1 - The armour can't be worn, use default messages.
 *                string - The armour can't be worn, use this message.
 */
public mixed
wear(object obj)
{
    object player = environment(this_object());
    if (!objectp(player))
    {
        // Something is wrong because we can't get the person trying to wear this ring.
        return -1;
    }

    if (player->has_mermaid_ring_shadow())
    {
        // Already has the shadow, we don't need to add it again.
        return 0;
    }

    // Add the shadow to the player so that they can get the benefits
    // of MAGIC_I_BREATH_WATER in Calia
    setuid();
    seteuid(getuid());
    object mermaid_shadow = clone_object(MERMQ_SHADOW);
    mermaid_shadow->shadow_me(player);
    
    return 0;
}


string
query_auto_load()
{
    return MASTER; 
}

string
query_recover()
{
    return 0;
}


void
env_check()
{
    // Non-players objects and wizards can have this object.
    object player = environment(this_object());
    if (!objectp(player)
        || !IS_PLAYER_OBJECT(player)
        || player->query_wiz_level())
    {
        return;
    }
    if (!environment(this_object())->test_bit(MERMQ_DOMAIN, 
                                              MERMQ_GROUP, 
                                              MERMQ_BIT))
        remove_object(); 
}


/*
 * Function name: leave_env
 * Description  : When you inherit /lib/wearable_item.c into any object other
 *                than /std/armour.c you MUST also define the function
 *                leave_env() as copy of this function. It MUST make the
 *                call to wearable_item_leave_env(from, to) as well. If
 *                you omit this, then the item will not be automatically
 *                removed when the player drops it, for instance.
 *                PS: This is just a dummy function. It does not exist. You
 *                    must write your own as copy of this one.
 * Arguments    : object from - the environment we are leaving.
 *                object to   - the environment we are entering.
 */
public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    wearable_item_leave_env(from, to);
}

void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    set_alarm(1.0, 0.0, env_check);
}


int
do_lose(string str)
{
    object ob;

    notify_fail("Lose what?\n"); 
    if (!stringp(str) || !strlen(str) ||
        !parse_command(str, environment(), "[the] %o", ob))
        return 0;

    if (ob != this_object())
        return 0; 

    if (losing_it) {
        write("You lose the " + short() + ".\n"); 
        say(QCTNAME(this_player()) + " loses " + 
            this_player()->query_possessive() + " " + 
            short() + ".\n");
        set_alarm(0.0, 0.0, remove_object); 
        return 1;  
    } 
    write("Type the command again to confirm you want to lose " +
          "the " + short() + ".\n"); 
    losing_it = 1; 
    return 1; 
}

void
init()
{
    ::init(); 
    add_action(do_lose, "lose"); 
}
