// OBJECT:  fall_from_tree.c

    /* Calia Domain

    HISTORY

    [99-06-21] Created by Uhclem from
    [D:\CALIA\CENTRAL\FOREST\SPECIALS\FALL_FRO.DOC].

    PURPOSE

    This object controls a player's fall from a tree in the Great Central
    Forest. The fall may be fatal. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <ss_types.h>
#include <wa_types.h>
#include <language.h>
#include <composite.h>
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <formulas.h>
#include "defs.h"

// GLOBAL VARIABLES

/*  All variables in this object are global. */

object Tp;
object Ob;
object Enemy;
int Fall_Level = 0;
string This_Location;
string Upper_Room;
string Middle_Room;
string Low_Room;
string Ground_Room;
string Below_Room;
string Impact_Message;
string Test_Message;
string *x;
int Damage;
int Max_Damage;
int Min_Damage;

string *Message =
    ({"with a loud thud", "at high speed", "with tremendous force"});

// FUNCTIONS

// Function:  final_impact()

/*

Purpose:  land the player abruptly and assess Damage.

Arguments:  none, everything comes from global variables.

Returns:  nothing.

*/

void
final_impact()

{

    if (Tp->query_stat(SS_DIS) < random(100)) Tp->command("scream");

    Tp->move_living("M", Ground_Room, 1, 1);

    /*
     *  The Elementals are so active in Calia that there's a chance that Lady 
     *  Gu will notice your fall and try to save you by softening the spot of
     *  ground where you're about to land.  She'll only try if your earth magic
     *  skill is high enough and there's no pit already in the room where
     *  you're headed.  Even if she does, she still may not prevent you from
     *  being killed.    
     */

    if (Tp->query_skill(SS_ELEMENT_AIR) > random(200) &&
        !member_array("pit", Ground_Room->query_prop(FOREST_COMBAT_INVENTORY)))

    {

        Ground_Room->create_pit();

        tell_object(Tp,
            "Just as you are about to hit the ground," +
            " it disappears from beneath you! Suddenly" +
            " you find yourself continuing to fall into a pit.\n");

        tell_room(Ground_Room,
            QCTNAME(Tp) +
            " falls from the treetops! The ground suddenly gives" +
            " way beneath " + Tp->query_objective() +
            ", and " + Tp->query_pronoun() +
            " disappears into a pit.\n",
            ({Tp}));

        Tp->move_living("M", Below_Room, 1, 1);
        Damage = Damage / 4;

    }

    else

    {

        tell_room(Ground_Room,
            QCNAME(Tp) + " falls from above and slams into the" +
            " ground " + Message[Fall_Level] + "!\n",
            ({Tp}));

    }

    /*
     *  A heavy player can also cause a pit to form when he hits the ground.  I 
     *  purposely do not tell the player this - when he gets over the shock of
     *  the fall (if he lives), he can figure out for himself where he landed.
     *    
     */

    if (Tp->query_prop(OBJ_I_WEIGHT) > 100000 &&
        !member_array("pit", Ground_Room->query_prop(FOREST_COMBAT_INVENTORY)))

    {

        Ground_Room->create_pit();

        tell_room(Ground_Room, "The impact causes the ground to give" +
            " way, and " + QTNAME(Tp) +
            " disappears into a deep pit.\n");

        Tp->move_living("M", Below_Room, 1, 1);

    }

    Tp->reduce_hit_point(Damage);

    if (Tp->query_hp() < 1)

    {

        Impact_Message = "You hear a sickening thud and a sound of" +
            " shattering bones from below.\n";

        tell_object(Tp, "You smash into the ground " +
            Message[Fall_Level] + "!\n");

        Tp->do_die(this_object());

    }

    else

    {

        Impact_Message = "You hear something land on the ground below with" +
            " a loud thud.\n";

        tell_object(Tp, "You smash into the ground " +
            Message[Fall_Level] + ", but the soft carpet of leaves" +
            " and vines cushions your landing.\n");

        Tp->add_attack_delay(5, 1);

    }

    /*
     * Give everyone above the news.   
     */

    tell_room(find_object(Low_Room), Impact_Message);
    tell_room(find_object(Middle_Room), Impact_Message);
    tell_room(find_object(Upper_Room), Impact_Message);

    log_file("forest_events",
        sprintf("%-12s%-20s%7ihp%7idm(%4i - %7i)%4ien%4iac",
        Tp->query_name(),
        "fell from " + Test_Message,
        Tp->query_hp(),
        Damage,
        Min_Damage,
        Max_Damage,
        Tp->query_encumberance_weight(),
        Tp->query_skill(SS_ACROBAT)) + "\n");

    remove_object();

}

// Function:  start_falling()

/*

Purpose:  move the player down, abruptly.

Arguments:  none.

Returns:  nothing.

*/

void
start_falling()

{

    Tp = environment(this_object());

    Max_Damage = (50
        + (Tp->query_encumberance_weight() * Tp->query_encumberance_weight())
        + Tp->query_stat(SS_STR)
        - Tp->query_stat(SS_CON)
        - Tp->query_stat(SS_DEX)
        - (Tp->query_skill(SS_ACROBAT) * 2))
        * Tp->query_max_hp() / 100;

    /*
     *  The base Damage is calculated so that burden affects the results 
     *  geometrically; at high levels it can make other factors moot. Acrobat
     *  skill compensates to a degree, but its effect is linear. A resilience
     *  factor is supplied by (str-con), so that small players with healthy
     *  constitutions enjoy a bit of "float" and fare better than big ones with
     *  weak constitutions, and dex can sway the results significantly when
     *  other factors have low values.  The minimum Damage for a fall from
     *  mid-tree level is 2% of your total hit points.

     *  On average, acrobat will cancel out burden, con will cancel out str,
     *  and the player's risk is (50 - dex)% of his total hitpoints. This means
     *  that a reasonably dextrous player can romp through the forest at
     *  mid-tree level largely unconcerned about his welfare as long as he
     *  doesn't carry too much equipment. However, falls can be fatal if he is
     *  already injured.

     *  The base value is modified by how far you fall: by half at low-tree
     *  level and doubled at upper-tree. Because the forest floor is quite soft
     *  and yielding, armours don't offer significant protection and the extra
     *  weight they add are a disadvantage. My intention is not to kill players
     *  often but to put them at great risk if they don't understand proper
     *  methods for exploring the trees. I plan to provide npc's who will offer
     *  hints about tree climbing precautions.

     *  I'LL BE HAPPY TO ENTERTAIN SUGGESTIONS ON IMPROVING THIS DAMAGE
     *  FORMULA!   
     */

    Min_Damage = Tp->query_max_hp() / 50;
    Damage = random(Max_Damage);
    if (Damage < Min_Damage) Damage = Min_Damage;

    /*
     *  This object is put into a living object's inventory to make it fall 
     *  from a tree and is only used in central forest rooms. If it is
     *  encountered anywhere else, something is wrong. It's also bad form to
     *  use it in a room with no down exit!   
     */

    if (!living(Tp))

    {

        remove_object();
        return;

    }

    if (!wildmatch(CENTRAL + "*", file_name(environment(Tp))))

    {

        Tp->catch_msg("An error just occurred - you invoked a" +
            " forest function in the wrong room. Please file a bugreport.\n");

        remove_object();
        return;

    }

    /*
     *  Following statements locate the possible objects the falling player may 
     *  be occupying. We'll refer to them often enough that it's useful to get
     *  all the definitions out of the way here.   
     */

    x = explode(file_name(environment(Tp)), "/");
    Upper_Room = implode(x[0..5], "/") + "/upper/" + x[7];
    Middle_Room = implode(x[0..5], "/") + "/middle/" + x[7];
    Low_Room = implode(x[0..5], "/") + "/low/" + x[7];
    Ground_Room = implode(x[0..5], "/") + "/ground/" + x[7];
    Below_Room = implode(x[0..5], "/") + "/below/" + x[7];
    Test_Message = x[6];

    if (environment(Tp) == find_object(Upper_Room))

    {

        if (member_array("down", environment(Tp)->query_exit_cmds()) == -1)

        {

            remove_object();
            return;

        }

        tell_room(environment(Tp),
            QCTNAME(Tp) + " loses " + Tp->query_possessive() + " grip" +
            " and falls from the treetop!\n",
            ({Tp}));

        tell_object(Tp, "You lose your grip and fall from the treetop!\n");

        /*
         *  Now let's have some fun! If the player is fighting someone in the 
         *  close quarters of the upper-tree level, let's give him a shot at
         *  taking the Enemy down with him. If a large number of players are
         *  fighting in the treetops, there's a real slim chance we can take
         *  the whole bunch down in one go! The player needs a str+dex
         *  advantage to drag the Enemy down.   
         */

        Enemy = Tp->query_attack();

        if (Enemy &&
            (Tp->query_stat(SS_DEX) + Tp->query_stat(SS_STR) -
            Enemy->query_stat(SS_DEX) - Enemy->query_stat(SS_STR)) >
            random(100))

        {

            tell_room(environment(Tp),
                QCTNAME(Tp) + " manages to grab " + QCTNAME(Enemy) +
                " and drag " + Enemy->query_objective() +
                " down as well!\n",
                ({Tp, Enemy}));

            Tp->catch_msg("You manage to grab " + QCTNAME(Enemy) +
                " as you fall and drag " + Enemy->query_objective() +
                " down with you!\n");

            Enemy->catch_msg(QCTNAME(Tp) + " manages to grab you" +
                " in mid-fall and drag you down with" +
                " " + Tp->query_objective() + "!\n");

            Ob = clone_object(file_name(this_object()));
            Ob->move(Enemy);
            Ob->start_falling();

        }

        Tp->move_living("M", Middle_Room, 1, 1);

        tell_room(Middle_Room,
            QCNAME(Tp) + " arrives from above, plummeting.\n",
            ({Tp}));

        Fall_Level += 1;

        /*
         *  If you fall from upper-tree level you have a chance of landing on 
         *  mid-tree level. You have the best chance of not getting hurt if
         *  you're not carrying much.   
         */

        if (Tp->query_skill(SS_ACROBAT) > random(100))

        {

            /*
             *  Either you're good or you're lucky. Good is better.   
             */

            if ((Tp->query_stat(SS_DEX) - Tp->query_encumberance_weight()) >
                random(100))

            {

                tell_room(environment(Tp),
                    QCTNAME(Tp) + " makes a spectacular acrobatic" +
                    " landing on one of the sturdy tree limbs!\n",
                    ({Tp}));

                tell_object(Tp,
                    "You make a spectacular acrobatic landing on one" +
                    " of the tree limbs! You manage to land" +
                    " without injuring yourself.\n");

            }

            else

            {

                tell_room(environment(Tp),
                    QCTNAME(Tp) + " slams down onto a tree limb with" +
                    " a grisly thud!\n",
                    ({Tp}));

                tell_object(Tp, "You slam down onto a tree limb!\n");
                Damage /= 2;
                Tp->reduce_hit_point(Damage);
                if (Tp->query_hp() < 1) Tp->do_die(this_object());

                log_file("forest_events",
                    sprintf("%-12s%-20s%7ihp%7idm(%4i-%7i)%4ien%4iac",
                    Tp->query_name() + "*",
                    "fell from " + Test_Message,
                    Tp->query_hp(),
                    Damage,
                    Min_Damage,
                    Max_Damage,
                    Tp->query_encumberance_weight(),
                    Tp->query_skill(SS_ACROBAT)) + "\n");
                    /*
                     * Asterisk indicates player landed on mid-tree level.   
                     */

            }

            /*
             *  Whether you land acrobatically or smash into the tree, this 
             *  fall is over.   
             */

            remove_object();
            return;

        }

        else

        {

            Damage *= 2;

        }

    }

    if (environment(Tp) == find_object(Middle_Room))

    {

        if (member_array("down", environment(Tp)->query_exit_cmds()) == -1)

        {

            remove_object();
            return;

        }

        tell_room(environment(Tp),
            QCTNAME(Tp) + " falls between the branches of the great" +
            " tree and plummets toward the ground!\n",
            ({Tp}));

        tell_object(Tp,
            "You fall between the branches of the great tree" +
            " and plummet toward the ground!\n");

        Fall_Level += 1;

        /*
         *  At this level the player is sent to the fall-room for 2 seconds 
         *  before landing.   
         */

        Tp->move_living("M", FOREST_FALL_ROOM, 1);
        set_alarm(2.0, 0.0, final_impact);

        /*
         *  There's no hope of catching the tree trunk, so at this point you're 
         *  definitely heading for ground level. A Message is supplied to
         *  anyone clinging to the trunk as you pass. Low-tree rooms always
         *  have a down exit, so I omit the check to save a bit of cpu.   
         */

        tell_room(Low_Room,
            QCNAME(Tp) + " arrives from above, plummeting.\n" +
            QCTNAME(Tp) + " leaves down, plummeting.\n");

    }

    if (environment(Tp) == find_object(Low_Room))

    {

        tell_room(environment(Tp),
            QCTNAME(Tp) + " loses " + Tp->query_possessive() + " grip" +
            " on the tree trunk and falls to the ground!\n",
            ({Tp}));

        tell_object(Tp,
            "You lose your grip on the tree trunk and fall" +
            " to the ground!\n");

        Damage /= 2;

        /*
         *  At this level the player is sent directly to ground level.   
         */

        final_impact();

    }

}

// OBJECT DEFINITION

void
create_object()

{

    set_no_show();
    set_name("falling from tree");
    set_short("falling from tree");
    set_long("falling from tree");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_WEIGHT, 1);

}
