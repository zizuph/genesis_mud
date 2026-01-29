/*
 *  xbow.c
 *
 * This class is the base of all xbow weapons. Inherit this
 * class if you want to create a xbow of your own.
 * Modified /std/bow.c
 *      *set_drawn_weapon(0); to avoid fatigue check while loaded
 *      *added "cocked" state that must be reached before aim/shoot
 *      *changed to work with bolt type projectiles only
 *      *changed unstrung state to 1handed club
 * See /doc/examples/weapons/elven_bow.c for an example.
 */

#pragma strict_types
#pragma save_binary

inherit "/std/launch_weapon";
inherit "/lib/keep";

#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <options.h>
#include <stdproperties.h>
#include <wa_types.h>
#define ENV(x) environment(x)


// Variables
string bowstring; /* The path to the bowstring used to string this bow.*/
int stringed; /* A flag that is set when bow is stringed. */
int cocked; /* A flag that is set when bow is cocked.*/

// Prototypes
public string query_damage_desc(object archer, object target,
                                object projectile, int phurt);

public nomask void snap_string();

public nomask void string_xbow(string bowstr);

public nomask void unstring_xbow();

public nomask void cock_xbow();

public nomask int parse_string(string args);

public nomask int parse_unstring(string args);

public nomask int parse_cock(string args);

public nomask void query_cocked();

public nomask void query_stringed();


/*
 * Function name: create_xbow
 * Description:   Constructor to be used by xbow implementations.
 */
public void
create_xbow()
{
    return;
}

/*
 * Function name: create_launch_weapon
 * Description:   Constructor to be used by launch_weapon implementations.
 */
public nomask void
create_launch_weapon()
{
    set_name("xbow");
    set_short("xbow");
    set_long("A plain xbow.\n");
    set_hit(40);
    set_pen(40);
    set_wf(this_object());
    set_shoot_command("shoot");
    set_drawn_weapon(0);
    stringed = 1;
    set_keep(0);
    create_xbow();
    set_valid_projectile_function("is_bolt");
}


/*
 * Function name: init
 * Description  : Adds the string/unstring and cock commands to the player.
 */
public void
init()
{
    ::init();
    set_hands(W_ANYH);
    add_action(parse_string, "string");
    add_action(parse_unstring, "unstring");
    add_action(parse_cock, "cock");
}

/*
 * Function name: did_parry
 * Description:   Called when this weapon was used to parry an attack. It can
 *                be used to wear down a weapon. Note that his method is called
 *                before the combat messages are printed out.
 * Arguments:     att:   Attacker
 *                aid:   The attack id
 *                dt:    The damagetype
 */

public varargs void
did_parry(object att, int aid, int dt)
{
    if (stringed && !random(F_BOWSTRING_SNAP_CHANCE))
    {
        snap_string();
    }
}

/*
 * Function name: snap_string
 * Description:   Called when the bowstring of this xbow snaps. It
 *                is responsible for giving the messages to all
 *                involved parties and calling unstring_xbow()
 *                to get the internal state updated.
 */
public nomask void
snap_string()
{
    object archer = query_wielded();
    object *bystanders = FILTER_LIVE(all_inventory(environment(archer))) -
        ({ archer });

    bystanders =
        filter(FILTER_IS_SEEN(archer, bystanders), &->can_see_in_room());

    tell_object(query_wielded(), "The bowstring of your " +
                                 short() + " snaps!\n");
    if (sizeof(bystanders))
    {
        bystanders->catch_msg("The bowstring of " +
                              LANG_POSS(QTNAME(archer)) + " " +
                              short() + " breaks!\n");
    }

    unstring_xbow();
    bowstring = 0;
}

/*
 * Function name: string_xbow
 * Description:   Updates the internal state of the xbow when it
 *                gets a bowstring.
 */
public nomask void
string_xbow(string bowstr)
{
    bowstring = bowstr;
    stringed = 1;
    cocked = 0;
    unwield_me();
    set_wt(W_MISSILE);
    set_dt(W_IMPALE);
    this_object()->string_xbow_hook();
}

/*
 * Function name: query_stringed
 * Description:   Returns whether this bow is sttringed or not.
 *
 * Returns      : 1 stringed, 0 unstringed.
 */
public nomask int
query_stringed()
{
    return stringed;
}



/*
 * Function name: unstring_xbow
 * Description:   Updates the internal state of the xbow when it
 *                looses its bowstring.
 */
public nomask void
unstring_xbow()
{
    unwield_me();
    stringed = 0;
    cocked = 0;
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    this_object()->unstring_xbow_hook();
}

/*
 * Function name: parse_string
 * Description  : Parses the player input when he wants to string
 *
 * Arguments    : string - Xbow to string.
 * Returns      : 1 command handled, 0 parse failed.
 */
public nomask int
parse_string(string args)
{
    object dummy;
    object *strings, *bystanders, archer;

    archer = this_player();

    if (environment(this_object()) != archer)
    {
        return 0;
    }

    if (!args || !parse_command(args, ({ this_object() }), " %o ", dummy))
    {
        notify_fail("String what? The " + short() + "?/n");
        return 0;
    }


    if (stringed)
    {
        write("The " + short() + " is already strung.\n");
        return 1;
    }

    strings = filter(all_inventory(archer), &->is_bowstring());

    if (!sizeof(strings))
    {
        write("You don't have any bowstrings.\n");
        return 1;
    }

    string_xbow(MASTER_OB(strings[0]));

    write("You string your " + short() + " with " +
          LANG_ADDART(strings[0]->short()) + ".\n");

    bystanders = FILTER_LIVE(all_inventory(environment(archer))) - ({archer});
    bystanders = filter(FILTER_IS_SEEN(archer, bystanders),
                        &->can_see_in_room());

    if (sizeof(bystanders))
    {
        bystanders->catch_msg(QCTNAME(archer) + " strings " +
                              archer->query_possessive() + " " +
                              short() + ".\n");
    }

    strings[0]->remove_object();
    return 1;
}

/*
 * Function name: parse_unstring
 * Description  : Parses input from a player when he wants to unstring
 *                a xbow.
 *
 * Arguments    : string - Xbow to unstring.
 * Returns      : 1 command handled, 0 parse failed.
 */
public nomask int
parse_unstring(string args)
{
    object dummy;
    object *bystanders, bstring, archer;

    archer = this_player();

    if (environment(this_object()) != archer)
    {
        return 0;
    }

    if (!args || !parse_command(args, ({ this_object() }), " %o ", dummy))
    {
        notify_fail("Unstring what? The " + short() + "?/n");
        return 0;
    }

    if (!stringed)
    {
        write("The " + short() + " has no string.\n");
        return 1;
    }

    if (bowstring)
    {
        clone_object(bowstring)->move(archer, 1);
    }
    else
    {
        clone_object("/std/bowstring")->move(archer, 1);
    }

    unstring_xbow();

    write("You unstring your " + short() + ".\n");

    bystanders = FILTER_LIVE(all_inventory(environment(archer))) - ({archer});
    bystanders = filter(FILTER_IS_SEEN(archer, bystanders),
                        &->can_see_in_room());

    if (sizeof(bystanders))
    {
        bystanders->catch_msg(QCTNAME(archer) + " unstrings " +
                              archer->query_possessive() + " " +
                              short() + ".\n");
    }

    return 1;
}

/*
 * Function name: cock_xbow
 * Description:   Updates the internal state of the xbow when it
 *                gets cocked.
 */
public nomask void
cock_xbow()
{
    cocked = 1;
    this_object()->cock_xbow_hook();
}

/*
 * Function name: query_cocked

 *
 * Returns      : 1 cocked, 0 uncocked.
 */
public nomask int
query_cocked()
{
    return cocked;
}

/*
 * Function name: parse_cock
 * Description  : Parses input from a player when he wants to cock
 *                a xbow.
 *
 * Arguments    : string - Xbow to cock.
 * Returns      : 1 cock state reached, 0 cock failed.
 */
public nomask int
parse_cock(string args)
{
    object dummy;
    object *bystanders, archer;

    int a_str, a_fat, cock_cost;

    archer = this_player();

    if (environment(this_object()) != archer)
    {
        return 0;
    }

/*
    if (!args || !parse_command(args, ({ this_object() }), " %o ", dummy))
    {
        notify_fail("Cock what? The " + short() + "?\n");
        return 0;
    }
*/

    if (!stringed)
    {
        write("The " + short() + " has no string.\n");
        return 0;
    }

    if (cocked)
    {
        write("The " + short() + " is already in a cocked position.\n");
        return 1;
    }

    a_str = archer->query_base_stat(SS_STR);
    a_fat = archer->query_max_fatigue();
    cock_cost = a_fat / a_str;

    if ( archer->query_fatigue() < cock_cost )
    {
      write("You are too tired to cock the " + short() +".\n");
      return 0;
    } else {
      archer->add_fatigue( -cock_cost );
    }

    cock_xbow();

    write("You cock your " + short() + ".\n");

    bystanders = FILTER_LIVE(all_inventory(environment(archer))) - ({archer});
    bystanders = filter(FILTER_IS_SEEN(archer, bystanders),
                        &->can_see_in_room());

    if (sizeof(bystanders))
    {
        bystanders->catch_msg(QCTNAME(archer) + " cocks " +
                              archer->query_possessive() + " " +
                              short() + ".\n");
    }

    return 1;
}



/*
 * Function name: query_hit
 * Description  : This function merely checks if the bow is
 *                stringed and delegates to launch_weapon.
 *                If the bow is not stringed it returns a hit
 *                of 10 and behaves like a normal weapon.
*/
public int
query_hit()
{
    if (stringed && cocked)
    {
        return ::query_hit();
    }
    else
    {
        return 20;
    }
}

/*
 * Function name: query_pen
 * Description  : This function merely checks if the bow is
 *                stringed and delegates to launch_weapon.
 *                If the bow is not stringed it returns a
 *                pen of 10 and behaves like a normal weapon.
 */
public int
query_pen()
{
    if (stringed && cocked)
    {
        return ::query_pen();
    }
    else
    {
        return 20;
    }
}

/*
 * Function name: try_hit
 * Description  : This function merely checks if the bow is
 *                stringed and delegates to launch_weapon.
 *                If the bow is not stringed it returns 1
 *                and behaves like a normal weapon.
 */
public int
try_hit(object target)
{
    if (stringed && cocked)
    {
        return ::try_hit(target);
    }
    else
    {
        return 1;
    }
}

/*
 * Function name: did_hit
 * Description  : This function merely checks if the xbow is
 *                stringed and cocked then delegates to
 *                launch_weapon. If the bow is not stringed
 *                and cocked it returns 0 and behaves like
 *                a normal weapon.
 */
public varargs int
did_hit(int aid, string hdesc, int phurt,
        object enemy,   int dt, int phit, int dam)
{
    if (stringed && cocked)
    {
        cocked = 0;
        return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }
    else
    {
        return 0;
    }
}

/*
 * Function name: extra_sanity_checks
 * Description  : Verifies that the archer and his environment are suited
 *                for aiming or shooting. This function is meant to be
 *                overloaded by subclasses.
 *
 * Arguments    : action (string) - Action the archer performs.
 *              : args (string)   - Arguments the archer supplies.
 *
 * Returns      : 1 - Setup is sane. 0 - Setup fishy.
 */
public int
extra_sanity_checks(string action, string args)
{
    if (stringed && cocked)
    {
        return 1;
    }
    if (!stringed)
    {
        write("Your crossbow is not strung.\n");
        return 0;
    }
    if (!cocked)
    {
        write("Your crossbow is not cocked.\n");
        return 0;
    }
}

/*
 * Function name: load_desc
 * Description  : Returns an extra description of the loaded weapon.
 *                This is meant to be overloaded in subclasses for

 *
 * Returns      : string - Extra description of the load status.
 */
public string
load_desc()
{
    return ( ((cocked && stringed) ? "The string has been drawn back " + 
         "and locked into position. " : "") + 
        (query_projectile() ? "A " + query_projectile()->singular_short() + 
        " is loaded in a narrow groove on top of this crossbow." : "") +
        "\n");
}

/*
 * Function name: tell_archer_no_missiles
 * Description  : Produces a message to the wielder that he is out of missiles.
 *                This function is meant to be overridden by launch_weapon
 *                implementations.
 */
public void
tell_archer_no_missiles()
{
    tell_object(query_wielded(), "You are out of bolts!\n");
}

/*
 * Function name: tell_archer_unload
 * Description  : Produces messages to the wielder when he unloads his
 *                launch_weapon. This function is meant to be overridden
 *                by launch_weapon implementations.
 *
 * Arguments    : archer:      The archer unloading a projectile.
 *                projectile:  The projectile he unloads.
 */
public void
tell_archer_unload(object archer, object target, object projectile)
{
    tell_object(archer, "You relax your grip on the " + short() +
                " and unload the " + projectile->singular_short() + ".\n");
}

/*
 * Function name: tell_others_unload
 * Description  : Produces messages to bystanders that the wielder unloads
 *                his launch_weapon. This function is meant to be
 *                overridden by launch_weapon implementaions.

 * Arguments    : archer:      The archer unloading a projectile.
 *                target:      The person the wilder aimed at.
 *                projectile:  The projectile he unloads.
 */
public void
tell_others_unload(object archer, object target, object projectile)
{
    object *bystanders;

    bystanders = all_inventory(ENV(archer)) - ({ archer });
    bystanders = FILTER_IS_SEEN(archer, FILTER_LIVE(bystanders));
    bystanders = filter(bystanders, &->can_see_in_room());

    bystanders->catch_msg(QCTNAME(archer) + " relaxes " +
                          archer->query_possessive() +
                          " grip on the " + short() + " and unloads the " +
                          projectile->singular_short() + ".\n");
}

/*
 * Function name: tell_archer_load
 *                his launch_weapon. This function is meant to be
 *                overridden by launch_weapon implementations.
 *
 * Arguments    : archer:      The archer loading a projectile.
 *                target:      The soon to be target!
 *                projectile:  Projectile beeing loaded.
 *                adj_desc:    Description of the adjecent room.
 */
public void
tell_archer_load(object archer, object target,
                 object projectile, string adj_desc)
{
    // You load a black-feathered bolt in your dwarven crossbow,
    // aiming carefully at the black orc.

    if (ENV(archer) == ENV(target))
    {
        tell_object(archer, "You load " +
                    LANG_ADDART(projectile->singular_short()) +
                    " in your " + short() + ", aiming carefully at " +
                    target->query_the_name(archer) + ".\n");
    }
    else
    {
        tell_object(archer, "You load " +
                    LANG_ADDART(projectile->singular_short()) +
                    " in your " + short() + ", aiming carefully at " +
                    target->query_the_name(archer) + " " + adj_desc + ".\n");
    }
}

/*
 * Function name: tell_others_load
 * Description  : Produces messages to spectators when the player loads his
 *                launch_weapon. This method is meant to be overridden by
 *                launch_weapon implementations.
 *
 * Arguments    : archer:     The player loading his weapon.
 *                target:     The target player is aiming at.
 *                projectile: The projectile we are loading.
 *                adj_string: Description of the adjecent location.
 */
public void
tell_others_load(object archer, object target,
                 object projectile, string adj_desc)
{
    if (ENV(archer) == ENV(target))
    {
        tell_bystanders_miss(QCTNAME(archer) + " loads " +
                             LANG_ADDART(projectile->singular_short()) +
                             " in " + archer->query_possessive() +
                             " " + short() + ", aiming carefully at " +
                             QTNAME(target) + ".\n",

                             QCTNAME(archer) + " loads " +
                             LANG_ADDART(projectile->singular_short()) +
                             " in " + archer->query_possessive() +
                             " " + short() +
                             ", aiming at something.\n",

                             0, 0, archer, target, ENV(archer));
    }
    else
    {
        tell_bystanders_miss(QCTNAME(archer) + " loads " +
                             LANG_ADDART(projectile->singular_short()) +
                             " in " + archer->query_possessive() +
                             " " + short() +
                             ", aiming carefully at " + QTNAME(target) +
                             " " + adj_desc + ".\n",

                             QCTNAME(archer) + " loads " +
                             LANG_ADDART(projectile->singular_short()) +
                             " in " + archer->query_possessive() +
                             " " + short() +
                             ", aiming carefully at something " +
                             adj_desc + ".\n",

                             0, 0, archer, target, ENV(archer));
    }
}


/*
 * Function name: tell_target_load
 * Description  : Produces a message to the player when he is loading his
 *                launch_weapon.

 * Arguments    : archer:     The player loading his weapon.
 *                target:     The target player is aiming at.
 *                projectile: The projectile we are loading.
 */
public void
tell_target_load(object archer, object target, object projectile)
{
    if (ENV(archer) == ENV(target) &&
        CAN_SEE(target, archer) && CAN_SEE_IN_ROOM(target))
    {
        tell_object(target, archer->query_The_name(target) + " loads " +
                    LANG_ADDART(projectile->singular_short()) +
                    " in " + archer->query_possessive() + " " +
                    short() + ", aiming carefully at you.\n");
    }
}

/*
 * Function name: tell_archer_miss
 * Description  : Produces a message to the player when he misses his target.
 *                This function take visual conditions in consideration as

 *
 * Arguments    : archer:        The player loading his weapon.
 *                target:        The target player is aiming at.
 *                projectile:    The projectile we are loading.
 *                adj_room_desc: Description of the room we shoot into. 0 if
 *                               target stand in the same room.
 */
public void
tell_archer_miss(object archer, object target, object projectile,
                 string adj_room_desc)
{
    if (archer->query_npc() || archer->query_option(OPT_GAG_MISSES))
    {
        return;
    }

    if (ENV(archer) == ENV(target))
    {
        if (CAN_SEE(archer, target) && CAN_SEE_IN_ROOM(archer))
        {
          /*
           * You shoot a bolt at the black orc, but miss.
           */

          tell_object(archer, "You shoot a bolt at " +
                      target->query_the_name(archer) + ", but miss.\n");
        }
        else
        {
            // You shoot blindly at the orc.

            if (archer->query_met(target))
            {
                tell_object(archer, "You shoot blindly at " +
                            target->query_met_name() + ".\n");
            }
            else
            {
                tell_object(archer, "You shoot blindly at the " +
                            target->query_race_name() + ".\n");
            }
        }
    }
    else
    {
        if (check_remote_seen(archer, target))
        {
            // You shoot a bolt at the black orc on the courtyard, but miss.

            tell_object(archer, "You shoot a bolt at " +
                        target->query_the_name(archer) + " " +
                        adj_room_desc + ", but miss.\n");
        }
        else
        {
            // You shoot blindly at the orc on the courtyard.

            if (archer->query_met(target))
            {
                tell_object(archer, "You shoot blindly at " +
                            target->query_met_name() + " " +
                            adj_room_desc + ".\n");
            }
            else
            {
                tell_object(archer, "You shoot blindly at the " +
                            target->query_race_name() + " " +
                            adj_room_desc + ".\n");
            }
        }
    }
}

/*
 * Function name: tell_target_miss
 * Description  : Produces a message to the target when the archer tries to
 *                shoot at him but miss. This function take visual
 *                conditions in consideration as well as shoots across rooms.
 *
 * Arguments    : archer:        The player loading his weapon.
 *                target:        The target player is aiming at.
 *                projectile:    The projectile we are loading.
 *                adj_room_desc: Description of the room we shoot into. 0 if
 *                               target stands in the same room at the archer.
 *                org_room_desc: Description of originating room. 0 if
 *                               target stands in the same room as the archer.
 */
public void
tell_target_miss(object archer, object target, object projectile,
                 string adj_room_desc, string org_room_desc)
{
    if (target->query_npc() || target->query_option(OPT_GAG_MISSES))
    {
        return;
    }

    if (ENV(archer) == ENV(target))
    {
        if (CAN_SEE(target, archer) && CAN_SEE_IN_ROOM(archer))
        {
            // The tall green-clad elf shoots a bolt at you, but misses.

            tell_object(target, archer->query_The_name(target) +
                        " shoots a bolt at you, but misses.\n");
        }
        else
        {
            tell_object(target, "You hear the wizz of a bolt " +
                        "flying past.\n");
        }
    }
    else
    {
        if (check_remote_seen(target, archer))
        {
            /*
             * The tall green-clad elf shoots a bolt at you from
             * the battlement, but misses.
             */

            tell_object(target, archer->query_The_name(target) +
                        " shoots a bolt at you from " +
                        org_room_desc + ", but misses.\n");
        }
        else if (CAN_SEE_IN_ROOM(target))
        {
            tell_object(target, "Someone shoots a bolt at you," +
                        " but misses.\n");
        }
        else
        {
            tell_object(target, "You hear the wizz of a bolt " +
                        "flying past.\n");
        }
    }
}

/*
 * Function name: tell_others_miss
 * Description  : Produces messages to all bystanders when the archer misses
 *                his target. This function take visual conditions in
 *                consideration as well as shoots across rooms.
 *
 * Arguments    : archer:        The player loading his weapon.
 *                target:        The target player is aiming at.
 *                projectile:    The projectile we are loading.
 *                adj_room_desc: Description of the room we shoot into. 0 if
 *                               target stands in the same room at the archer.
 *                org_room_desc: Description of originating room. 0 if
 *                               target stands in the same room as the archer.
 */
public void
tell_others_miss(object archer, object target, object projectile,
                 string adj_room_desc, string org_room_desc)
{
    if (ENV(archer) == ENV(target))
    {

        /*
         * The tall green-clad elf shoots a bolt at the black orc,
         * but misses.
         */

        tell_bystanders_miss(QCTNAME(archer) + " shoots a bolt at " +
                             QTNAME(target) + ", but misses.\n",

                             QCTNAME(archer) +
                             " shoots a bolt at something.\n",

                             "A bolt flies past " + QTNAME(target) + ".\n",

                             "You hear the wizz of a bolt flying through " +
                             "the air.\n",

                             archer, target, ENV(archer));

    }
    else
    {

        /*
         * Archer shooting to adjecent room. Archer room:
         *
         * The tall green-clad elf shoots a bolt at the black orc on
         * the courtyard, but misses.
         */

        tell_bystanders_miss(QCTNAME(archer) +
                             " shoots a bolt at " + QTNAME(target) +
                             " " + adj_room_desc + ", but misses.\n",

                             QCTNAME(archer) +
                             " shoots a bolt at something " +
                             adj_room_desc + ".\n",

                             "Someone shoots a bolt at " + QTNAME(target) +
                             " " + adj_room_desc + ", but misses.\n",

                             "You hear the wizz of a bolt flying through " +
                             "the air.\n",

                             archer, target, ENV(archer));

        /*
         * Archer shooting to adjecent room. Target room:
         *
         * The tall green-clad elf shoots a bolt at the black orc
         * from the battlements, but misses.
         *
         */

        tell_bystanders_miss(QCTNAME(archer) + " shoots a bolt at " +
                             QTNAME(target) + " from " + org_room_desc +
                             ", but misses.\n",

                             QCTNAME(archer) + " shoots a bolt " +
                             " at something.\n",

                             "Someone shoots a bolt at " +
                             QTNAME(target) + ", but misses.\n",

                             "You hear the wizz of a bolt flying through " +
                             "the air.\n",

                             archer, target, ENV(target));
    }

    return;
}

/*
 * Function name: tell_archer_bounce_armour
 * Description  : Produces a message to the archer when his bolt hits the
 *                target without causing any harm. This is described as
 *                the bolt bouncing off his armour.
 *
 * Arguments    : archer:        The player loading his weapon.
 *                target:        The target player is aiming at.
 *                projectile:    The projectile we are loading.
 *                adj_room_desc: Description of the room we shoot into. 0 if
 *                               target stands in the same room at the archer.

 *                               target stands in the same room as the archer.
 *                armour:        The armour that deflects the bolt. armour
 *                               may be 0 if no armour covers the hid.
 */
public void
tell_archer_bounce_armour(object archer, object target, object projectile,
                          string adj_room_desc, object armour)
{
    string armour_desc;

    if (archer->query_npc() || archer->query_option(OPT_GAG_MISSES))
    {
        return;
    }

    if (armour)
    {
        armour_desc = ", but the bolt glances off " +
            target->query_possessive() + " " + armour->short() + ".\n";
    }
    else
    {
        armour_desc = ", but the bolt glances off " +
            target->query_objective() + " harmlessly.\n";
    }


    if (ENV(archer) == ENV(target))
    {
        if (CAN_SEE(archer, target) && CAN_SEE_IN_ROOM(archer))
        {
            // You shoot a bolt at the black orc, but the bolt glances off
            // his helm.

          tell_object(archer, "You shoot a bolt at " +
                      target->query_the_name(archer) + armour_desc);
        }
        else
        {
            // You shoot blindly at the orc.
            if (archer->query_met(target))
            {
                tell_object(archer, "You shoot blindly at " +
                            target->query_met_name() + ".\n");
            }
            else
            {
                tell_object(archer, "You shoot blindly at the " +
                            target->query_race_name() + ".\n");
            }
        }
    }
    else
    {
        if (check_remote_seen(archer, target))
        {
            /*
             * You shoot a bolt at the black orc on the courtyard,
             * but the bolt glances off his helm.
             */
            tell_object(archer, "You shoot a bolt at " +
                        target->query_the_name(archer) + " " +
                        adj_room_desc + armour_desc);

        }
        else
        {
            // You shoot blindly at the orc on the courtyard.
            if (archer->query_met(target))
            {
                tell_object(archer, "You shoot blindly at " +
                            target->query_met_name() + " " +
                            adj_room_desc + ".\n");
            }
            else
            {
                tell_object(archer, "You shoot blindly at the " +
                            target->query_race_name() + " " +
                            adj_room_desc + ".\n");
            }
        }
    }
}

/*
 * Function name: tell_target_bounce_armour
 * Description  : Produces a message to the target when he is hit by

 *                the bolt bouncing off his armour.
 *
 * Arguments    : archer:        The player loading his weapon.
 *                target:        The target player is aiming at.
 *                projectile:    The projectile we are loading.
 *                adj_room_desc: Description of the room we shoot into. 0 if
 *                               target stands in the same room at the archer.
 *                org_room_desc: Description of originating room. 0 if
 *                               target stands in the same room as the archer.
 *                armour:        The armour that deflects the bolt. armour
 *                               may be 0 if no armour covers the hid.
 */
public void
tell_target_bounce_armour(object archer, object target, object projectile,
                          string adj_room_desc, string org_room_desc,
                          object armour)
{
    string armour_desc;

    if (target->query_npc() || target->query_option(OPT_GAG_MISSES))
    {
        return;
    }

    if (armour)
    {
        armour_desc = ", but the bolt glances off your "
            + armour->short() + ".\n";
    }
    else
    {
        armour_desc = ", but the bolt glances off harmlessly.\n";
    }

    if (ENV(archer) == ENV(target))
    {
        if (CAN_SEE(target, archer) && CAN_SEE_IN_ROOM(archer))
        {
            /*
             * The tall green-clad elf shoots a bolt
             * at you, but the bolt glances off your helm.
             */

            tell_object(target, archer->query_The_name(target) +
                        " shoots a bolt at you" + armour_desc);
        }

        else
        {
            tell_object(target, "A bolt from out of nowhere hits you, " +
                        "but harmlessly glances off" +
                        (armour ? " your " + armour->short() + ".\n"
                         : " you.\n"));
        }
    }
    else
    {
        if (check_remote_seen(target, archer))
        {
            /*
             * The tall green-clad elf shoots a bolt at you
             * from the battlements, but the bolt glances off your helm.
             */

            tell_object(target, archer->query_The_name(target) +
                        " shoots a bolt at you" + armour_desc);
        }
        else if (CAN_SEE_IN_ROOM(target))
        {
            tell_object(target, "Someone shoots a bolt at you from " +
                        org_room_desc + armour_desc);
        }
        else
        {
            tell_object(target, "A bolt from out of nowhere hits you, " +
                        "but harmlessly glances off" +
                        (armour ? " your " + armour->short() + ".\n"
                         : " you.\n"));
        }
    }
}

/*
 * Function name: tell_others_bounce_armour
 * Description  : Produces messages to bystanders when the archer's bolt
 *                harmlessly hits the target. This is described as
 *                the bolt bouncing off the target's armour.

 * Arguments    : archer:        The player loading his weapon.
 *                target:        The target player is aiming at.
 *                projectile:    The projectile we are loading.
 *                adj_room_desc: Description of the room we shoot into. 0 if
 *                               target stands in the same room at the archer.
 *                org_room_desc: Description of originating room. 0 if
 *                               target stands in the same room as the archer.
 *                armour:        The armour that deflects the bolt. May
 *                               be 0 if no piece of armour protects the
 *                               location.
 */
public void
tell_others_bounce_armour(object archer, object target, object projectile,
                          string adj_room_desc, string org_room_desc,
                          object armour)
{
    string armour_desc;

    if (armour)
    {
        armour_desc = ", but the bolt glances off " +
            target->query_possessive() + " " + armour->short() + ".\n";
    }
    else
    {
        armour_desc = ", but the bolt glances off " +
            target->query_objective() + " harmlessly.\n";
    }

    if (ENV(archer) == ENV(target))
    {

        /*
         * The tall green-clad elf shoots a bolt at the
         * black orc, but the bolt glances off his chainmail.
         *
         */

        tell_bystanders_miss(QCTNAME(archer) + " shoots a bolt at " +
                             QTNAME(target) + armour_desc,

                             QCTNAME(archer) + " shoots a bolt at " +
                             "something. You hear a thud as the bolt " +
                             "hits something.\n",

                             "A bolt hits " + QTNAME(target) + armour_desc,

                             "You hear the wizz of a bolt flying through " +
                             "the air and a thud as it hits something.\n",

                             archer, target, ENV(archer));
    }

    else
    {

        /*
         * Archer shooting to adjecent room. Archer room:
         *
         * The tall green-clad elf shoots a bolt at the black orc on
         * the courtyard, but the bolt glances off his chainmail.
         */

        tell_bystanders_miss(QCTNAME(archer) + " shoots a bolt at " +
                             QTNAME(target) + " " + adj_room_desc +
                             armour_desc,

                             QCTNAME(archer) +
                             " shoots a bolt at something" +
                             adj_room_desc + ".\n",

                             "Someone shoots a bolt at " + QTNAME(target) +
                             " " + adj_room_desc + armour_desc,

                             "You hear the wizz of a bolt flying through " +
                             "the air.\n",

                             archer, target, ENV(archer));

        /*
         * Archer shooting to adjecent room. Target room:
         *
         * The tall green-clad elf shoots a bolt at the black orc
         * from the battlements, but the bolt glances off his chainmail.
         */

        tell_bystanders_miss(QCTNAME(archer) + " shoots a bolt at " +
                             QTNAME(target) + " from " + org_room_desc +
                             armour_desc,

                             QCTNAME(archer) + " shoots a bolt at " +
                             "something. " +
                             "You hear a thud as the bolt hits something.\n",

                             "Someone shoots a bolt at " +
                             QTNAME(target) + " from " + org_room_desc +
                             armour_desc,

                             "You hear the wizz of a bolt flying through " +
                             "the air and a thud as it hits something.\n",

                             archer, target, ENV(target));
    }
    return;
}

/*
 * Function name: tell_archer_hit
 * Description  : Produces a message to the archer when he hits the target.

 *                across rooms in consideration.
 *
 * Arguments    : archer:        The player loading his weapon.
 *                target:        The target player is aiming at.
 *                projectile:    The projectile we are loading.
 *                adj_room_desc: Description of the room we shoot into. 0 if
 *                               target stands in the same room at the archer.
 *                org_room_desc: Description of originating room. 0 if
 *                               target stands in the same room as the archer.
 *                hdesc:         The hitlocation description.
 *                phurt:         The %hurt made on the enemy
 *                dt:            The current damagetype
 *                dam:           The damage caused by this weapon in hit points
 *                hid:           The hitlocation we hit.
 */
public void
tell_archer_hit(object archer, object target,
                object projectile, string adj_room_desc,
                string hdesc, int dt, int phurt, int dam, int hid)
{
    string damage_desc = query_damage_desc(archer, target, projectile, phurt);

    if (archer->query_npc())
    {
        return;
    }

    if (ENV(archer) == ENV(target))
    {
        if (CAN_SEE(archer, target) && CAN_SEE_IN_ROOM(archer))
        {
            /*
             * You shoot a bolt at the black orc.
             * The bolt strikes into his legs.
             */

            tell_object(archer, "You shoot a bolt at " +
                        target->query_the_name(archer) +
                        ". The bolt" + damage_desc +
                        target->query_the_possessive_name(archer) +
                        " " + hdesc + ".\n");
        }
        else
        {
            // You shoot blindly at the orc.
            if (archer->query_met(target))
            {
                tell_object(archer, "You shoot blindly at " +
                            target->query_met_name() +
                            ". You hear a thud as the bolt hits.\n");
            }
            else
            {
                tell_object(archer, "You shoot blindly at the " +
                            target->query_race_name() +
                            ". You hear a thud as the bolt hits.\n");
            }
        }
    }
    else
    {
        if (check_remote_seen(archer, target))
        {
            /*
             * You shoot a bolt at the black orc on the courtyard.
             * The bolt hits him in the legs.
             */

            tell_object(archer, "You shoot a bolt at " +
                        target->query_the_name(archer) + " " +
                        adj_room_desc + ". The bolt" +  damage_desc +
                        target->query_the_possessive_name(archer) +
                        " " + hdesc + ".\n");
        }
        else
        {
            if (archer->query_met(target))
            {
                tell_object(archer, "You shoot blindly at " +
                            target->query_met_name() + " " +
                            adj_room_desc + ".\n");
            }
            else
            {
                tell_object(archer, "You shoot blindly at the " +
                            target->query_race_name() + " " +
                            adj_room_desc + ".\n");
            }
        }
    }
}

/*
 * Function name: tell_target_hit
 * Description  : Produces a message to the target when he is hit by the
 *                archer. This function takes visual conditions as well as
 *                shoots across rooms in consideration.
 *
 * Arguments    : archer:        The player loading his weapon.
 *                target:        The target player is aiming at.
 *                projectile:    The projectile we are loading.
 *                adj_room_desc: Description of the room we shoot into. 0 if
 *                               target stands in the same room at the archer.
 *                org_room_desc: Description of originating room. 0 if
 *                               target stands in the same room as the archer.
 *                hdesc:         The hitlocation description.
 *                phurt:         The %hurt made on the enemy
 *                dt:            The current damagetype
 *                dam:           The damage caused by this weapon in hit points

 */
public void
tell_target_hit(object archer, object target, object projectile,
                string adj_room_desc, string org_room_desc, string hdesc,
                int dt, int phurt, int dam, int hid)
{
    string damage_desc = query_damage_desc(archer, target, projectile, phurt);

    if (target->query_npc())
    {
        return;
    }

    if (ENV(archer) == ENV(target))
    {
        if (CAN_SEE(target, archer) && CAN_SEE_IN_ROOM(archer))
        {
            tell_object(target, archer->query_The_name(target) +
                        " shoots a bolt at you. The bolt" +     damage_desc +
                        "your " + hdesc + ".\n");
        }
        else
        {
            tell_object(target, "An bolt from out of nowhere" + damage_desc +
                        "your " + hdesc + ".\n");
        }

    }
    else
    {
        if (check_remote_seen(target, archer))
        {
            tell_object(target, archer->query_The_name(target) +
                        " shoots a bolt at you from " + org_room_desc +
                        ". The bolt" + damage_desc + "your " + hdesc + ".\n");
        }
        else if (CAN_SEE_IN_ROOM(target))
        {
            tell_object(target, "Someone shoots a bolt at you from " +
                        org_room_desc + ". The bolt" + damage_desc + "your " +
                        hdesc + ".\n");
        }
        else
        {
            tell_object(target, "A bolt from out of nowhere" + damage_desc +
                        "your " + hdesc + ".\n");
        }
    }
}

/*
 * Function name: tell_others_hit
 * Description  : Produces messages to all bystanders when target is hit
 *                by the archer. This function tells targets in both the
 *                archer's and target's environment if they are not the
 *                same.
 *
 * Arguments    : archer:        The player loading his weapon.
 *                target:        The target player is aiming at.
 *                projectile:    The projectile we are loading.
 *                adj_room_desc: Description of the room we shoot into. 0 if
 *                               target stands in the same room at the archer.
 *                org_room_desc: Description of originating room. 0 if
 *                               target stands in the same room as the archer.
 *                hdesc:         The hitlocation description.

 *                dt:            The current damagetype
 *                dam:           The damage caused by this weapon in hit points
 *                hid:           The hitlocation we hit.
 */
public void
tell_others_hit(object archer, object target, object projectile,
                string adj_room_desc, string org_room_desc, string hdesc,
                int dt, int phurt, int dam, int hid)
{

    string damage_desc = query_damage_desc(archer, target, projectile, phurt);

        if (ENV(archer) == ENV(target))
    {

        /*
         * Typical message:
         *
         * The tall green-clad elf shoots a bolt at the black orc.
         * The bolt strikes deeply into the orc's legs.
         */

        tell_bystanders_hit(QCTNAME(archer) + " shoots a bolt at " +
                            QTNAME(target) + ". The bolt" +
                            damage_desc + QTPNAME(target) + " " +
                            hdesc + ".\n",

                            QCTNAME(archer) +
                            " shoots a bolt at something. " +
                            "You hear a thud as the bolt hits something.\n",

                            "A bolt hits " + QTNAME(target) + ". The bolt" +
                            damage_desc + QTPNAME(target) +
                            " " + hdesc + ".\n",

                            "You hear the wizz of a bolt flying through " +
                            "the air and a thud as it hits something.\n",

                            archer, target, ENV(archer));
    }

    else
    {

        /*
         * Archer shooting to adjecent room. Archer room:
         *
         * The tall green-clad elf shoots a bolt at the black orc
         * on the courtyard. The bolt strikes soundly into the orc's legs.
         *
         */

        tell_bystanders_hit(QCTNAME(archer) + " shoots a bolt at " +
                            QTNAME(target) + " " + adj_room_desc +
                            ". The bolt" + damage_desc + QTPNAME(target) +
                            " " + hdesc + ".\n",

                            QCTNAME(archer) +
                            " shoots a bolt at something " +
                            adj_room_desc + ".\n",

                            "Someone shoots a bolt at " +
                            QTNAME(target) + " " + adj_room_desc +
                            ". The bolt" + damage_desc + QTPNAME(target) +
                            " " + hdesc + ".\n",

                            "You hear the wizz of a bolt flying through " +
                            "the air.\n",

                            archer, target, ENV(archer));

        /*
         * Archer shooting to adjecent room. Target room:
         *
         * The tall green-clad elf shoots a bolt at the black orc from the
         * battlements. The bolt strikes soundly into the orc's legs.
         *
         */

        tell_bystanders_hit(QCTNAME(archer) + " shoots a bolt at " +
                            QTNAME(target) + " from " + org_room_desc +
                            ". The bolt" + damage_desc + QTPNAME(target) +
                            " " + hdesc + ".\n",

                            QCTNAME(archer) +
                            " shoots a bolt at something. " +
                            "You hear a thud as the bolt hits something.\n",

                            "Someone shoots a bolt at " + QTNAME(target) +
                            " from " + org_room_desc + ". The bolt" +
                            damage_desc + QTPNAME(target) +
                            " " + hdesc + ".\n",

                            "You hear the wizz of a bolt flying through " +
                            "the air and a thud as it hits something.\n",

                            archer, target, ENV(target));
    }
    return;
}

/*
 * Function name: query_damage_desc
 * Description  : Returns a string describing how much damage we have done.
 *                The string should have leading and tailing spaces.
 *
 * Arguments    : archer:        The player loading his weapon.
 *                target:        The target player is aiming at.
 *                projectile:    The projectile we are loading.

 * Returns      : (string) A string describing how much the bolt hurt.
 */
public string
query_damage_desc(object archer, object target, object projectile, int phurt)
{
    switch (phurt)
    {
      case 0..2:
        return " merely glances off of ";
        break;
      case 3..5:
        return " grazes ";
        break;
      case 6..9:
        return " hits ";
        break;
      case 10..19:
        return " strikes ";
        break;
      case 20..39:
        return " hits soundly into ";
        break;
      case 40..59:
        return " strikes solidly into ";
        break;
      case 60..90:
        return " drives deeply into ";
        break;
      default:
        return " strikes with devastating precision into ";
        break;
    }
}


/*
 * Function name: query_wep_recover
 * Description:   Return the recover strings for changing weapon variables.
 * Returns:       A recover string
 */
string
query_wep_recover()
{
    return ::query_wep_recover() + "XBOW#" + bowstring + "#" + stringed +
        "#" + cocked + "#" + query_keep_recover() + "#";
}

/*
 * Function name: init_wep_recover
 * Description:   Initialize the weapon variables at recover.
 * Arguments:     arg - String with variables to recover
 */
void
init_wep_recover(string arg)
{
    string wep_str, recover_str, tail;

    sscanf(arg, "%sXBOW#%s#%d#%d#%s#%s",
           wep_str, bowstring, stringed, cocked, recover_str, tail);

    init_keep_recover(recover_str);
    ::init_wep_recover(wep_str);
}
