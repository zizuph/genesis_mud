/*
 *  /d/Emerald/torque/torque.c
 *
 *  One of the more famous things in the history of Genesis,
 *  this, the Crystal Torque was originally created by Phase,
 *  and then redone by Mayhem. Shiva again recoded it in
 *  December of 2000. It has been given another full
 *  retreatment for its unveiling as the centerpiece of
 *  the Emerald domain at its reopening after many years of
 *  preparation. This reworking has been done both by Shiva
 *  and by Gorboth, the latter of whom has sought to finally
 *  find a way to make the torque fit into a meaningful
 *  context.
 *
 *  Recode (c) August 2003, by Shiva and Gorboth
 *
 *  Modification History:
 *    - July, 2013 (Gorboth)
 *        Reduced weight and volume from 300 down to a mere 10.
 */
#pragma save_binary
#pragma strict_types

#include "/d/Emerald/torque/torque.h"

inherit TORQUE_BASE;
inherit "/lib/wearable_item";
inherit "/d/Genesis/newmagic/spellcasting";

#include "/d/Emerald/quest_handler/quest_handler.h"

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include <living_desc.h>
#include <composite.h>
#include <filter_funs.h>
#include <std.h>

#include "/d/Emerald/sys/domain.h"

#define TORQUE_QUEST_NAME "torque_portal"
#define MANAGER "/d/Emerald/blackwall/delrimmon/obj/quest_manager"

#define DEBUG_ON

#define 
#define MANA_COST       80
#define RECHARGE_MANA   12

#define MAX_CHARGE     99

#define LOST_TORQUE_FILE(who) (TORQUE_LOG + "lost_torque/" + who[0..0])
#define USED_TORQUE_DESC_FILE (TORQUE_LOG + "used_torque_descs")

#define NUM_ADJS 3

static int last_time, charge, charge_alarm_id, silent_wear;
static string bound = "";
static string command_word = 0;

void stop_recharge();
int add_charge(int ch);
public void config_torque(object owner);
public void do_silent_wear();
public void get_lost();
public void        do_bind(object who);
public int         incant_cmd(string arg);
public string      describe_torque();
public void        complete_quest(object player, int got_xp);

void
create_torque()
{
    set_name("torque");
    add_name("ctower_torque");

    // This should make it so that it can be worn over anything. This is
    // primarily done so that players can't prevent the auto-wear by
    // putting a helmet on.
    set_looseness(1000);

    // 0 layers so as not to prevent anything from being worn over it
    set_layers(0);

    set_wf(this_object());
    set_slots(A_BROW);

    set_long(describe_torque);

    add_prop(OBJ_M_NO_DROP, "You feel unable to part with it.\n");
    add_prop(OBJ_M_NO_STEAL, "The torque cannot be stolen!\n");
    add_prop(OBJ_M_NO_SELL, "The torque is far too valuable to sell.\n");
    add_prop(OBJ_M_NO_BUY, "It is not for sale!\n");
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 80, "divination" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "The torque appears to be enchanted with divine power.\n", 1,
        "It is somehow connected to an awareness which reaches"
      + " far beyond its own bounds, touching others of its kind"
      + " using the command word <scry>.\n", 20,
        "It carries within it the power of Telan-Ri, God of Light,"
      + " who wishes it to be used to further his influence in"
      + " Emerald.\n", 60 }) );

    add_spell("/d/Emerald/torque/scry.c");

    charge = MAX_CHARGE;
    charge_alarm_id = 0;

    setuid();
    seteuid(getuid());
}

string
query_auto_load()
{
    return sprintf("%s:%d,%d,%s,%s", MASTER,
                                     last_time,
                                     charge,
                                     bound,
                                     command_word || "NONE");
}

void
init_arg(string args)
{
    sscanf(args, "%d,%d,%s,%s", last_time, charge, bound, command_word);

    if (command_word == "NONE")
    {
        command_word = 0;
    }

    // Is this_player() guaranteed to be the right player here?
    // It seems like it should be.
    config_torque(this_player());
}

public void
reset_object()
{
    object owner;

    // Just in case the torque is removed somehow, periodically rewear it,
    // if appropriate.
    if (!query_worn() &&
        (owner = environment(this_object())) &&
        living(owner) &&
        strlen(bound) &&
        (bound == owner->query_real_name()))
    {
        set_this_player(owner);
        do_silent_wear();
    }
}

string
query_recover()
{
    return 0;
}

public string
query_bound()
{
    return bound;
}

public void
set_bound(string name)
{
    bound = name;
}

public string
query_command_word()
{
    return command_word;
}

public void
set_command_word(string cmd)
{
    command_word = cmd;
}

void
recharge_torque()
{
    object who = query_worn();

    if (!who)
    {
        stop_recharge();
        return;
    }

    if (who->query_mana() < RECHARGE_MANA)
    {
        return;
    }

    who->add_mana(-RECHARGE_MANA);
    add_charge(max(2, MAX_CHARGE - charge));
}
    
void
start_recharge()
{
    if ((charge < MAX_CHARGE) && !charge_alarm_id && query_worn())
    {
        charge_alarm_id = set_alarm(300.0, 300.0, recharge_torque);
    }
}

void
stop_recharge()
{
    if (charge_alarm_id)
    {
        remove_alarm(charge_alarm_id);
        charge_alarm_id = 0;
    }
}
 
/*
 * Function name: do_silent_wear
 * Description:   Cause the torque to be worn without printing any messages
 */  
public void
do_silent_wear()
{
    silent_wear = 1;
    wear_me();
    silent_wear = 0;
}

int
wear()
{
    start_recharge();
    return (silent_wear ? 1 : 0);
}

void
get_lost()
{
    write("The " + short() + " glows brightly and begins to " +
        "collapse into itself, finally shrinking to a pinpoint of light and " +
        "disappearing!\n");

    remove_object();
}


int
add_charge(int ch)
{
    int tmp = charge + ch;

    if (tmp < 0)
    {
        return 0;
    }

    charge = tmp;
    start_recharge();
    
    return 1;
}


public void
catch_input(string input, object *torques)
{
    int i;
    object torque;

    sscanf(input, "%d", i);

    if ((i < 1) || (i > sizeof(torques)))
    {
        write("No such torque is present.\n");
        return;
    }

    torque = torques[i - 1];

    if (!torque)
    {
        write("No such torque is present.\n");
        return;
    }

    this_player()->start_spell("scry", torque->short(), this_object());    
}

int
scry_cmd(string arg)
{
    object *torques;
    int i;

    if (!strlen(bound) || (bound != this_player()->query_real_name()))
    {
        notify_fail("Nothing happens.\n");
        return 0;
    }

    if (!query_worn())
    {
        notify_fail("You must be wearing the torque in order to use its " +
            "powers.\n");
        return 0;
    }

    torques = 
        (object *)TORQUE_MANAGER->get_active_torques(this_object());

    if (strlen(arg))
    {
        this_player()->start_spell("scry", arg, this_object());
        return 1;
    }

    if (!sizeof(torques))
    {
        write("You sense no other active torques.\n");
        return 1;
    }

    for (i = 0; i < sizeof(torques); i++)
    {
        if ((this_player()->query_wiz_level() &&
             DOMAIN_WIZ(this_player())) ||
            (SECURITY->query_wiz_rank(this_player()->query_real_name()) >= WIZ_ARCH))
        {
            write(sprintf("%2d) %-13s %s\n", i + 1, "(" +
                environment(torques[i])->short() + ")", torques[i]->short()));
        }
        else
        {
            write(sprintf("%2d) %s\n", i + 1, torques[i]->short()));
        }
    }

    write("\nYou sense the presence of the above-listed torques.\n");
    write("Select a torque: ");
    input_to(&catch_input(, torques));

    return 1;
}
    
void
init()
{
    string name;
    string file;

    ::init();

    if (this_player() != environment())
    {
        return;
    }

    if (!this_player()->query_wiz_level()
        && !wildmatch("*jr", this_player()->query_real_name()))
    {  
        setuid();
        seteuid(getuid());
    
        if (!QH_QUERY_QUEST_COMPLETED(this_player(), TORQUE_QUEST_NAME) ||
            QH_QUERY_QUEST_COMPLETED(this_player(), "torque_destroy"))
        {
            set_alarm(1.0, 0.0, get_lost);
            return;
        }
    
        name = this_player()->query_real_name();
        file = LOST_TORQUE_FILE(name);
    
        if ((file_size(file) > 0) &&
            (member_array(name, explode(read_file(file), "\n")) >= 0))
        {
            set_alarm(1.0, 0.0, get_lost);
            return;
        }
    }

    if (strlen(bound))
    {
        if (bound == this_player()->query_real_name())
        {
            set_alarm(0.0, 0.0, do_silent_wear);
        }
        else
        {
            // Somehow this torque is bound to someone else
            set_alarm(0.5, 0.0, &get_lost());
        }
    }

    add_action(scry_cmd, "scry");
    add_action(incant_cmd, "incant");
}

public varargs int
query_torque_active(object requesting_torque)
{
    object wearer;

    // A torque must be worn and bound to be active
    if (!(wearer = query_worn()) &&
         interactive(wearer) &&
         strlen(bound) &&
         (bound == wearer->query_real_name()))
    {
        return 0;
    }

    // Torques belonging to wizards and juniors are not available to others
    if (requesting_torque &&
        (requesting_torque != this_object()) &&
        (wearer->query_wiz_level() ||
         wildmatch("*jr", bound)))
    {
        return 0;
    }

    return 1;
}

public void
config_torque(mixed owner)
{
    string desc;

    setuid();
    seteuid(getuid());

    desc = TORQUE_MANAGER->get_torque_desc(owner);
    if (strlen(desc))
    {
        set_adj(explode(desc, " "));
        set_short(desc + " torque");
    }
}

public void
scry(object scryer, int power)
{
    object env, owner;
    string tmp;
    string seeing = "You can see the following";
    object *items, *dead, *live;

    env = environment();

    if (env && living(env))
    {
        owner = env;
        env = environment(env);
    }

    if (!env || !query_torque_active())
    {
        scryer->catch_tell("You see only blackness through the torque.\n");
        return;
    }

/* 
   Per Gorboth, it is not the user that sees, but the torque.
   Because of this, there is no longer a check for darkness.
   
    if (env->query_prop(OBJ_I_LIGHT) < 1)
    {
        scryer->catch_tell(seeing + ":\n");
        if (!stringp(tmp = env->query_prop(ROOM_S_DARK_LONG)))
        {
            scryer->catch_tell(LD_DARK_LONG);
            return;
        }
         
        scryer->catch_tell(tmp);
        return;
    }
*/

    if (power < 150)
    {
        scryer->catch_tell(seeing + ", though weakly:\n");
        scryer->catch_tell(capitalize(env->short()) + ".\n");
        return;
    }

    scryer->catch_tell(seeing + ", as through new eyes:\n");
    scryer->catch_tell(env->long());

    if (power > 200)
    {  
        items = FILTER_CAN_SEE(all_inventory(env)- ({ query_worn() }),
                this_player());
        if (sizeof(items))
        {
            if (sizeof(dead = FILTER_DEAD(items)))
            {
                tmp = SILENT_COMPOSITE_DEAD(dead);
                if (strlen(tmp))
                {
                    scryer->catch_tell(capitalize(tmp) + ".\n");
                }
            }
            
            if (sizeof(live = FILTER_LIVE(items)))
            {
                tmp = SILENT_COMPOSITE_LIVE(live);
                if (strlen(tmp))
                {
                    scryer->catch_tell(capitalize(tmp) + ".\n");
                }
            }
        }
    }
}


/*
 * Function name:        do_bind
 * Description  :        The torque will now be bound to the player,
 *                       unless they were stupid enough to take it
 *                       off
 * Arguments    :        object who - the player
 */
public void
do_bind(object who)
{
    int got_xp;

    if (bound == this_player()->query_real_name())
    {
        return;
    }

    if (!query_worn())
    {
        write("The torque grows hot in your hands for a few"
              + " brief seconds, and then returns to normal.\n");
        return;
    }

    write("The torque grows suddenly hot on your brow, and you feel"
        + " a painful burning sensation. The gemstones bind themselves"
        + " to your flesh, as strange visions swim through your head"
        + " for a few brief moments.\n");

    set_bound(this_player()->query_real_name());

    got_xp = QH_QUEST_COMPLETED(this_player(), "torque_bind");

    set_alarm(2.0, 0.0, &complete_quest(this_player(), got_xp));

    return;
} /* do_bind */



/*
 * Function name:        incant_cmd
 * Description  :        catch it if the player happens to speak the
 *                       command word which he has been assigned
 * Arguments    :        string arg - what the player typed after 'say'
 * Returns      :        1 - success, 0 - failure
 */
public int
incant_cmd(string arg)
{
    string  txt = lower_case(arg);

    if (!strlen(arg))
    {
        notify_fail("What do you wish to incant?\n");
        return 0;
    }

    if (strlen(command_word) &&
        ((txt == command_word) ||
         (txt == (command_word + ".")) ||
         (txt == (command_word + "!"))))
    {
        write("You incant: " + capitalize(arg) + "!\n");

        set_alarm(1.0, 0.0, &do_bind(this_player()));
        return 1;
    }

    if (txt == "aidelnic" || txt == "aidelnic." || txt == "aidelnic!")
    {
        write("You incant: " + capitalize(arg) + "!\n");

        setuid();
        seteuid(getuid());

        if (QH_QUEST_COMPLETED(this_player(), "torque_destroy"))
        {
            set_alarm(2.0, 0.0, get_lost);
        }

        return 1;
    }

    write("You incant: " + arg + "\n");

    return 1;
} /* incant_cmd */


/*
 * Function name: remove
 * Description  : We do not allow bound torques to be removed.
 * Arguments    : object obj - The armour to remove.
 * Returns      : int  0 - Remove the armour normally.
 *                     1 - Remove the armour, but print no messages.
 *                    -1 - Do not remove the armour, print default message.
 *                string - Do not remove the armour, use this message.
 */
public mixed
remove(object obj)
{
    if (bound == this_player()->query_real_name())
    {
        return("The torque seems to have fused itself to your"
             + " brow. You cannot remove it.\n");
    }

    stop_recharge();

    return 0;
} /* remove */


/*
 * Function name:        describe_torque
 * Description  :        Describe the torque for the player, with
 *                       variation depending on whether or not
 *                       it is worn, and fully charged.
 * Returns      :        string - the info for set_long
 */
public string
describe_torque()
{
    string desc;
    object owner;

    owner = environment(this_object());
    if (!living(owner))
    {
        owner = 0;
    }

    if (owner && (obj_previous == owner) && (owner == query_worn()))
    {
        desc = "Because you wear the torque upon your brow, it is"
             + " quite impossible to view. However, you remember clearly"
             + " that it is incredibly beautiful, having been made of"
             + " precious metal which is set with many sparkling gems";
    }
    else
    {
        desc = "The torque is incredibly beautiful, having been made of"
             + " precious metal which is set with many sparkling gems";
    }

    switch (charge)
    {
        case (3 * MAX_CHARGE / 4) .. MAX_CHARGE:
            if (this_object()->query_worn())
            {
                desc += ". The gems are pulsing with a deep warmth.\n";
            }
            else
            {
                desc += ". You can feel the gems pulsing with a deep"
                      + " warmth against your skin.\n";
            }
            break;
        default:
            desc += ".\n";
            break;
    }   

    return desc;
} /* describe_torque */ 

public int
query_last_scry_time()
{
    return last_time;
}

public void
set_last_scry_time(int t)
{
    last_time = t;
}


/*
 * Function name:        complete_quest
 * Description  :        allow the player the final and largest reward
 *                       for completing the quest for the crystal torque
 * Arguments    :        object player - the player object
 *                       int    got_xp - true if the player received xp
 */
public void
complete_quest(object player, int got_xp)
{
    player->catch_tell("Your vision is suddenly lost, as a brilliant"
      + " and transcendent light fully envelopes your mind and body."
      + " A great voice, gentle and wise, yet powerful beyond your"
      + " ability to comprehend, resonates through your bones, saying:"
      + " Receive this gift of clarity. Use it to preserve my light,"
      + " Torque-Wearer!\n");

    if (got_xp)
    {
        player->catch_tell("You feel MUCH more experienced!\n");
    }

    return;
} /* complete_quest */

void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}

void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

/*
 * Function name: is_emerald_quest_torque
 * Description:   Easy, efficient identification of a torque object
 * Returns:       1
 */
public int
is_emerald_quest_torque()
{
    return 1;
}

/*
 * Create and configure a torque for a player, checking all the relevant bits.
 * This is intended primarily for restoration of lost torques.
 */
public nomask object
mktorque(mixed for_whom)
{
    object owner, torque;
    string command;

    if (stringp(for_whom))
    {
        for_whom = lower_case(for_whom);
        owner = find_player(for_whom);
        if (!owner)
        {
            if (this_interactive()->query_wiz_level())
            {
                this_interactive()->catch_tell("No such player found logged in: \"" + for_whom + "\".\n");
            }

            return 0;
        }
    }
    else if (objectp(for_whom))
    {
        owner = for_whom;

        if (!living(owner) || owner->query_npc())
        {
            if (this_interactive()->query_wiz_level())
            {
                this_interactive()->catch_tell("Owner must be a player.\n");
            }

            return 0;
        }
    }
    else
    {
        if (this_interactive()->query_wiz_level())
        {
            this_interactive()->catch_tell("Invalid argument to mktorque: " +
                "must be player name or player object.\n");
        }

        return 0;
    }

    if (!QH_QUERY_QUEST_COMPLETED(owner, TORQUE_QUEST_NAME))
    {
        if (this_interactive()->query_wiz_level())
        {
            this_interactive()->catch_tell(capitalize(owner->query_real_name()) +
                " has not completed the crystal torque quest.\n");
        }

        return 0;
    }

    if (QH_QUERY_QUEST_COMPLETED(owner, "torque_destroy"))
    {
        if (this_interactive()->query_wiz_level())
        {
            this_interactive()->catch_tell(capitalize(owner->query_real_name()) +
                " has previously destroyed " + owner->query_possessive() + 
                "torque.\n");
        }

        return 0;
    }

    setuid();
    seteuid(getuid());

    torque = clone_object(MASTER);
    torque->config_torque(owner);

    command = "/d/Emerald/blackwall/delrimmon/obj/quest_manager"->query_spell(owner);
    if (strlen(command))
    {
        torque->set_command_word(command);
    }

    if (QH_QUERY_QUEST_COMPLETED(owner, "torque_bind"))
    {
        torque->set_bound(owner->query_real_name());
    }

    return torque;
}

public nomask object
restore_torque(mixed for_whom)
{
    object torque, owner, *inv;
    int i;

    if (stringp(for_whom))
    {
        for_whom = lower_case(for_whom);
        owner = find_player(for_whom);
        if (!owner)
        {
            if (this_interactive()->query_wiz_level())
            {
                this_interactive()->catch_tell("No such player found logged in: \"" + for_whom + "\".\n");
            }

            return 0;
        }
    }
    else if (!objectp(for_whom))
    {
        if (this_interactive()->query_wiz_level())
        {
            this_interactive()->catch_tell("Invalid argument to restore_torque: " +
                "must be player name or player object.\n");
        }

        return 0;
    }
    else
    {
        owner = for_whom;
    }

    // Check to see if the player has a torque already. To be 100% sure, look
    // at the deep inventory.
    inv = deep_inventory(owner);
    for (i = 0; i < sizeof(inv); i++)
    {
        if (inv[i]->is_emerald_quest_torque())
        {
            if (this_interactive()->query_wiz_level())
            {
                this_interactive()->catch_tell("Player already possesses a torque.\n");
            }

            return 0;
        }
    }

    torque = mktorque(owner);

    if (torque)
    {
        torque->move(owner, 1);
    }

    return torque;
}
