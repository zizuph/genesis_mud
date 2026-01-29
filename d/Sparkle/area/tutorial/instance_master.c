/*
 * /d/Sparkle/area/tutorial/instance_master
 *
 * Assigns players to instances
 *
 */
#pragma strict_types
#pragma no_clone
#include <macros.h>
#include "defs.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"

/* Definitions */
#define     CAPACITY    5
#define     CHECK_TIME  600.0
//define     EXPIRE_TIME 300
#define     EXPIRE_TIME 1800

/* Global Variables */
mapping     players = ([]);
mixed *     instances = ({});
int         updated;
int         alarm_save, alarm_check;

/* Prototypes */

public void             create();
public void             remove_object();
public void             load();
public void             save(int mode);
public int              get_instance(object player);
public void             check();
public void             follow(object player);



/*
 * Function name:        create
 * Description  :        set up
 */
public void
create()
{
    setuid();
    seteuid(getuid());

    load();

    alarm_save = set_alarm(600.0, 600.0, save);
    alarm_check = set_alarm(0.0, CHECK_TIME, check);
} /* create */


/*
 * Function name:        remove_object
 * Description  :        we are being destructed - save data
 */
public void
remove_object()
{
    save(0);
} /* remove_object */


/*
 * Function name:        load
 * Description  :        load data from file
 */
public void
load()
{
    restore_object(SAVE_DIR + "instance_data");
    updated = 0;
} /* load */


/*
 * Function name:        save
 * Arguments    :        int mode - false = save only if needed, true = always
 * Description  :        save data to file
 */
public void
save(int mode)
{
    if (updated || mode)
        //save_map(imbuements, IMBUE_DIR + "imbuement_data");
        save_object(SAVE_DIR + "instance_data");
    updated = 0;
} /* save */


/*
 * Function name:        get_instance
 * Arguments    :        object player - player in question
 * Returns      :        int - instance number
 * Description  :        Finds the correct instance number for a player
 */
public int
get_instance(object player)
{
    string name = "?";
    int * rec = ({});
    int ins, pop;
    if (IS_PLAYER_OBJECT(player))
        name = player->query_real_name();
    else
        name = player->query_nonmet_name();
    rec = players[name];
    if (sizeof(rec))
    {
        ins = rec[0];
        rec[1] = time();
        send_debug_message("Instances", capitalize(name) +
            " part of instance " + ins);
        updated = 1;
        return ins;
    }
    
    ins = 1;
    foreach (string * instance: instances)
    {
        pop = sizeof(instance);
        if (pop < CAPACITY)
        {
            instance += ({ name });
            instances[ins-1] = instance;
            players[name] = ({ ins, time() });
            send_debug_message("Instances", capitalize(name) +
            " added to instance " + ins + " which had " + pop + " members");
            updated = 1;
            return ins;
        }
        ins++;
    }

    send_debug_message("Instances", capitalize(name) +
            " added to new instance " + ins);
    instances += ({ ({ name }) });
    players[name] = ({ ins, time() });
    updated = 1;
    return ins;
} /* get_instance */


/*
 * Function name:        check
 * Description  :        expire old instance memberships
 */
public void
check()
{
    int ins, insn, last, now;
    now = time();
    object player;
    foreach (string name, int * rec : players)
    {
        ins = rec[0];
        last = rec[1];
        if (player = find_player(name)) {
            if (insn = environment(player)->query_room_instance())
            {
                if ((insn != ins) && (insn > 0))
                {
                    send_debug_message("Instances", capitalize(name) +
                        " member of instance " + ins +
                        " but now in instance " + insn + "??");
                    ins = insn;
                }
                rec = ({ ins, time() });
                updated = 1;
                continue;
            }
            if (environment(player))
                if (file_name(environment(player)) == "/d/Genesis/obj/statue")
                {
                    send_debug_message("Instances", capitalize(name) +
                        " member of instance " + ins +
                        " but linkdead.");
                    rec = ({ ins, time() });
                    updated = 1;
                    continue;
                }
        }
        if ((now - last) >= EXPIRE_TIME)
        {
            send_debug_message("Instances", capitalize(name) +
                " last seen " + ctime(last) + ". Removing from instance " +
                ins);
            m_delkey(players, name);
            instances[ins-1] -= ({ name });
            updated = 1;
        }
    }
} /* check */


/*
 * Function name:        follow
 * Arguments    :        object player - player to update instance for
 * Description  :        sets instance of player to that of leader, so leading
 *                       works as expected through instances.
 */
public void
follow(object player)
{
    int *recp = ({}), *recl = ({});
    int insp, insl;
    string namep, namel;
    object leader = player->query_leader();
    if (IS_PLAYER_OBJECT(player))
        namep = player->query_real_name();
    else
        namep = player->query_nonmet_name();
    recp = players[namep];
    if (sizeof(recp))
        insp = recp[0];
    if (IS_PLAYER_OBJECT(leader))
        namel = leader->query_real_name();
    else
        namel = leader->query_nonmet_name();
    recl = players[namel];
    if (sizeof(recl))
        insl = recl[0];

    if (insp != insl)
    {
        send_debug_message("Instances", capitalize(namep) +
                        " member of instance " + insp +
                        ". Led by " + capitalize(namel) +
                        " member of instance " + insl + ".");
        if (insp)
        {
            instances[insp-1] -= ({ namep });
        }
        instances[insl-1] += ({ namep });
        players[namep] = ({ insl, time() });
        updated = 1;
    }
} /* follow */