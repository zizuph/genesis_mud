/*
 * void.c
 *
 * This serves as a vampire's own personal start location.  While this
 * room itself is not technically the player's registered start room,
 * he is moved here immediately upon login, and the player shouldn't
 * know the difference.  Each player gets his own void room (they are
 * cloned).
 */

inherit "/d/Emerald/std/room";

#include "/d/Emerald/mist_tower/defs.h"
#include "/d/Emerald/common/guild/vamp/guild.h"
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>

#define DO_RESTORE
#ifdef DO_RESTORE
#  define RESTORE_LOG "/d/Emerald/mist_tower/restore_log"
#endif

static private string owner;
static int clean_alarm = 0;
#ifdef DO_RESTORE
int owner_thirst, owner_mana, owner_fatigue;
#endif

void
create_emerald_room()
{
    set_short("A dark void");
    set_long("A dark void.\n");
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(ROOM_I_LIGHT, -1000);
    add_prop(OBJ_S_WIZINFO, "Wizards, please don't light this room if " +
        "there are players present.  To get out of the room, use \"out\".\n");
    add_prop(ROOM_M_NO_TELEPORT, 1);
}

/*
 * Function name: clean
 * Description:   Remove unwanted items from this room.
 */
public void
clean()
{
    string msg;
    object *obs;

    clean_alarm = 0;

    // Move all objects that aren't players to the start room
    obs = filter(all_inventory(this_object()), not @ interactive);
    obs = filter(obs,
        &operator(==)(0) @ &->move(MIST_TOWER_DIR + "tower_start", 1));

    if (sizeof(obs))
    {
        msg = capitalize(COMPOSITE_ALL_DEAD(obs)) + 
            ((sizeof(obs) == 1) ? " fades" : " fade") +
            " into view along the edge of the circle.\n";
        tell_room(MIST_TOWER_DIR + "tower_start", ({ msg, msg, "" }));
    }
}

public void
note_status(object who)
{
    owner_thirst  = who->query_thirst();
    owner_mana    = who->query_mana();
    owner_fatigue = who->query_fatigue();
}

/*
 * Function name: enter_inv
 * Description:   Called when an item enters the room
 * Arguments:     1. (object) The item entering
 *                2. (object) Where the item is coming from
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
    {
        // If there isn't an owner already, this player becomes the owner
        if (!owner)
        {
            owner = ob->query_real_name();
        }
        // If there is an owner, check to see if it's this player
        else if (owner != ob->query_real_name())
        {
            return;
        }

        // The owner has entered.  If he's a vampire, stop his thirst from
        // increasing while inside.
        if (IS_MEMBER(ob))
        {
            /* Players often get moved in here without do_glance() getting
             * called, which doesn't allow the player's darkvision to get
             * reset properly.  This should probably be fixed somehow
             * within the darkvision code, but for now I'll just explicitly
             * reset it here.
             */
            ob->reset_darkvision();

            // We want to delay slightly in case the player is returning
            // from linkdeath.  The delay allows the vampire shadow to
            // reset thirst before we turn it off again.
            set_alarm(0.0, 0.0, &(ob->query_vamp_shadow())->stop_thirst());

#ifdef DO_RESTORE
            // If the player is logging in, some vampire stats might not
            // be loaded yet, so we'll delay.
            set_alarm(0.0, 0.0, &note_status(ob));
#endif
        }
    }
    else if (!clean_alarm)
    {
        // This alarm ensures that the item moves in completely before we
        // move it out again.  It also allows us to move mutliple items all
        // at once if they're dropped at the same time.
        clean_alarm = set_alarm(0.0, 0.0, clean);
    }
}

/*
 * Function name: leave_inv
 * Description:   Called when an item leaves this room
 * Arguments:     1. (object) The object that's leaving
 *                2. (object) The object's destination
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    // If it's a vampire leaving, start his thirst increasing again
    if (IS_MEMBER(ob) && interactive(ob))
    {
#ifdef DO_RESTORE
        if (ob->query_real_name() == owner)
        {
            int t, m, f, flag;
    
            if (owner_thirst || owner_mana || owner_fatigue)
            {
                if ((t = ob->query_thirst()) > owner_thirst)
                {
                    flag = 1;
                    ob->set_thirst(owner_thirst);
                }
    
                if ((m = ob->query_mana()) < owner_mana)
                {
                    flag = 1;
                    ob->add_mana(owner_mana - ob->query_mana());
                }
    
                if ((f = ob->query_fatigue()) < owner_fatigue)
                {
                    flag = 1;
                    ob->add_fatigue(owner_fatigue - ob->query_fatigue());
                }
    
                if (flag)
                {
                    setuid();
                    seteuid(getuid());
                    write_file(RESTORE_LOG, sprintf("%d %s t: %d/%d m: %d/%d f: %d/%d\n",
                        time(), ob->query_real_name(), t, owner_thirst, m, owner_mana,
                        f, owner_fatigue));
                }
            }

            owner_thirst = owner_mana = owner_fatigue = 0;
        }
#endif

        ob->start_thirst();

    }
}

public string
query_owner()
{
    return owner;
}

public int
out(string str)
{
    string msg;
    if (strlen(str) &&
        !parse_command(str, ({}), "[off] / [out] [of] [the] 'circle'"))
    {
        return 0;
    }

    this_player()->move_living("M", "/d/Emerald/blackwall/delrimmon/"
                             + "lakeside/caves/tower_start", 1);

    msg = " fades into view at the center of the circle.\n";
    say(({ METNAME + msg, NONMETNAME + msg, "" }));

    return 1;
}

public void
init()
{
    ::init();
    add_action(out, "out");
    add_action(out, "leave");
    add_action(out, "back");
    add_action(out, "exit");
    add_action(out, "stand");
    add_action(out, "step");
}

