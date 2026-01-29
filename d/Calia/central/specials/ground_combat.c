// OBJECT:  ground_combat

    /* Calia Domain

    HISTORY

    [99-05-20] created by Uhclem from [D:\CALIA\CENTRAL\SPECIALS\GROUND_C.DOC].

    PURPOSE

    When someone starts a fight in many Great Central Forest rooms, this object
    is cloned into the room to add combat features peculiar to the local
    terrain. There are various environment items, such as logs, branches, and
    puddles, that may either trip up the unwary player or be used by an
    opponent to gain an advantage. In general, while combat continues, this
    object will periodically activate one of the special combat features in the
    room; the feature only threatens one player at a time. The period during
    which the feature is active is called the ground combat effect. Depending
    upon their stats and skills, players may become aware of the effect and
    make use of it.

    There are 5 phases to each ground combat effect:

        1. Avoidance:  the player avoids coming with range of the item. If
        this phase is successful, no further phases are for this effect are
        executed.

        2. Identification:  an opponent identifies an object that can be
        used against you. Alternately, as in the case of a puddle, random
        chance simply gives you an opportunity to slip.

        Identification occurs in 2 sub-phases:  seeing what combat effect
        has become available, and recognizing what can be done with it. If
        an opponent is not successful in the first sub-phase, the second
        sub-phase cannot be executed.

        3. Exploitation:  if the effect is not controlled by random chance,
        a player must actually type a command to exploit the effect. An npc
        must pass a skill/stat test to exploit the effect. If he does not,
        no further phases are executed. Random chance, the most diabolical
        of opponents, never misses an opportunity.

        The opponent who identifies the effect is not required to exploit
        it himself. He may inform an ally who will exploit it for him.

        4. Deflection:  the player may deflect the effect by ducking,
        leaping, or some other maneuver, in which case there is no harm
        done and the last phase is not executed.

        5. Recovery:  if the player fails to deflect the effect, he
        receives some penalty in the form of a stun or unintentional
        movement. NO DAMAGE IS EVER INFLICTED DIRECTLY BY THE GROUND COMBAT
        EFFECT! The process of reovery varies. If the player falls into a
        pit, he must climb out, a task which presents its own set of
        challenges. If the player is knocked down on the ground, he will
        require a time to recover based on his fatigue, health, panic, and
        intoxication. Finally, if he is startled, his recovery time is
        dependent upon his panic level.

    Each phase (and sub-phase) is controlled by either

    (a) a random number from 0-199 compared against a combination of one skill
    and one stat, or
    (b) a time recovery period computed from variable player attributes, such
    as panic or health (except the pit and slope which involve separate rooms
    and have their own recovery routines: you must be able to climb out of the
    pit or find your way back from wherever the slope takes you).

    In case (a) a player with a value of 100 in the relevant skill and 100 in
    the relevant stat is assured of success in that phase. Different skills and
    stats are applicable to different phases, so a player may be expert at
    indentifying special combat effects but be poor at exploiting them. Another
    player may be effectively immune to one effect but be particularly
    vulnerable to another effect in the same room due to the distinct set of
    skills needed to avoid or deflect it. It is possible that a team composed
    of one player who is adept at identifying local combat effects and another
    who is better at exploiting them may work together to take full advantage
    of them.

    The features which a player may encounter are:

        puddle           an ordinary puddle that may make someone slip
        pit              a deep thing to fall into
        root             something to trip over
        slope            an inclined surface to tumble down
        log              an old tree trunk or limb lying on the ground
        branch           a low-hanging branch which can hit someone's face
        vine             something that can trip you with an enemy's help
        animal           something to startle you when you least expect it
        bog              soft ground into which a player may sink
        flowers          (no combat effect at this time, but may become active
                         after the magic system is updated))

    The following table shows the forest combat features and the skills, stats,
    and variables associated with them:



      FEATURE       AVOID       IDENTIFY     EXPLOIT      DEFLECT      RECOVER
                   (player)     (enemy)      (enemy)      (player)     (player)

       puddle       dex +        random     automatic      dex +      fatigue +
                  awareness      chance                   acrobat       burden

        pit         int +        random     automatic      dex +       specific
                   location    chance to                   traps      climb-out
                    sense      fall in as                            requirements
                               result of                               are coded
                                another                                 in pit
                                 effect

       animal       int +        random     automatic      dex +        panic
                  awareness      chance                    animal
                                                          handling

        log         wis +        wis +        str +        dex +      fatigue +
                   appraise     appraise     unarmed      acrobat       burden
                    object       object       combat
                                           (shove log)

       branch       dex +        int +        dex +     str + parry   fatigue +
                   defense      appraise     acrobat                    burden
                                 enemy        (swing
                                             branch)

        vine        int +        wis +        str +        dex +      fatigue +
                  herbalism    herbalism    herbalism     acrobat       burden
                                           (yank vine)

        root        wis +        random     automatic      int +      fatigue +
                    climb        chance                   acrobat       burden

        bog         wis +        random     automatic      int +      fatigue +
                    sneak        chance                   appraise      burden
                                                           object

       slope      hazard of      random     automatic     deflect and recover
                  failing to     chance                  controlled by intox +
                  avoid root                            health + panic + burden

      flowers        n/a          n/a          n/a          n/a          n/a



    Not all effects are in all rooms! Some, like vines, are permanent, and
    others, like puddles, are transient. As players become familiar with the
    effects produced by different features, they will (I hope) arrange to face
    their opponents in the rooms that offer them the best advantage. There's no
    substitute for a home field advantage, so any guilds based in the Great
    Central Forest should offer some of the skills listed in the table above.

    Special note on fatigue:  the function query_fatigue() returns the player's
    remaining capacity for physical exertion, not the amount he has expended.
    To determine the player's energy expended (that is, his current level of
    fatigue), you need to compute it with the formula
    query_max_fatigue() - query_fatigue().

    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include "defs.h"

// GLOBAL VARIABLES

object Room;  /*  room the fight is in  */
object Victim;  /*  the person subject to the current hazard  */
object Enemy;  /*  the person fighting him  */
object *Absentee_List = ({});  /*  npc's who fell in pit or down slope  */

string *Variable_Time =
    ({"immediately",
    "almost immediately",
    "after only a couple of seconds' delay",
    "after a few seconds' delay",
    "slowly",
    "with some difficulty"});

string *Hazards;  /*  hazards available in the current room  */
string Hazard_Verb;  /*  command used to exploit the current hazard  */
int Threshold = 200;  /*  test value for command-activated hazards  */

// FUNCTIONS

// Function:  falls_down_slope(player)

/*

Purpose:  determine if a player falls down the slope; this function is invoked
as a result of failing to avoid a root.

Arguments:  none.
Returns:  1 if the player falls into the pit, 0 if not.

*/

int
falls_down_slope(object player)

    {

    object current_room = Room;
    string direction = current_room->query_prop(FOREST_SLOPE);
    int index = member_array(direction, current_room->query_exit_cmds());
    int return_code = 0;

    /*  Higher value for vulnerability means player is in worse shape to avoid
        the hazard.  */

    int vulnerability =
        player->query_encumbrance_weight() + player->query_panic() +
        player->query_intoxicated() - player->query_hp();

    while (index != -1 && vulnerability > random(1000))

        {

        return_code = 1;

        tell_room(current_room,
            QCTNAME(player) + " tumbles down the slope and disappears" +
            " to the " + direction + ".\n",
            ({player}));

        player->move_living("M",
            current_room->query_exit_rooms()[index], 1, 1);

        player->add_fatigue(-(player->query_fatigue()/3));

        /*  Reset the control variables so player can tumble through multiple
        rooms.  */

        current_room = environment(player);
        direction = environment(player)->query_prop(FOREST_SLOPE);
        index = member_array(direction, current_room->query_exit_cmds());
        vulnerability = vulnerability / 2;

        tell_room(current_room,
            QCTNAME(player) + " arrives tumbling and flailing " +
            player->query_possessive() + " limbs!\n",
            ({player}));

        }

    if (current_room != Room)

        {

        tell_room(current_room,
            QCTNAME(player) + " crashes to a halt against a tree.\n",
            ({player}));

        tell_object(player,
            "You lose your footing completely and tumble head" +
            " over heels down the slope! You come crashing to a" +
            " halt against a tree.\n");

        if (!interactive(player)) Absentee_List += ({player});

        }

    return return_code;

    }

// Function:  falls_in_pit(player)

/*

Purpose:  determine if a player falls into the local pit as a result of failing
to avoid a hazard; this function is called by the yank_vine, shove_log, and
swing_branch functions. If the player falls into the pit, both the movement and
appropriate messages are supplied functions in the room, not this object.

Arguments:  none.
Returns:  1 if the player falls into the pit, 0 if not.

*/

int
falls_in_pit(object player)

    {

    if (member_array("pit", Hazards) != -1
        &&
        player->query_max_fatigue() - player->query_fatigue() +
        player->query_encumbrance_weight() +
        player->query_panic() +
        player->query_intoxicated() > random(1000))

        {

        /*  The file name of the room is inserted into the command as check so
            that the room's fall-control routine will recognize that the player
            is not falling voluntarily.  */

        player->command("$fall " + file_name(Room) + " pit");
        if (!interactive(player)) Absentee_List += ({player});

        return 1;

        }

    else return 0;

    }

// Function:  get_back_up(player)

/*

Purpose:  apply the appropriate attack_delay to a player who has been knocked
down.

Arguments:  none.
Returns:  1/0.

*/

void
get_back_up(object player)

    {

    int delay = (player->query_max_fatigue() - player->query_fatigue()) / 10;

    if (delay > 5) delay = 5;
    player->add_attack_delay(delay + 1, 1);
    player->add_fatigue(-delay - player->query_encumbrance_weight());

    tell_room(Room,
        QCTNAME(player) + " gets back on " +
        player->query_possessive() + " feet " +
        Variable_Time[delay] + ".\n",
        ({player}));

    tell_object(player, "You get back on your feet " +
        Variable_Time[delay] + ".\n");

    }

// Function:  ground_combat_effect()

/*

Purpose:  find a fighting player and subject him to one of the naturally
occurring hazards in the room. An Enemy may or may not be involved in the
hazard; if he is, Hazard_Verb is the command Enemy must use to exploit the
hazard.

Arguments:  none.

Returns:  nothing.

*/

void
ground_combat_effect()

    {

    object *livings = FILTER_LIVE(all_inventory(Room));
    object other_room;
    string *directions = ({"north", "east", "south", "west"});
    string current_hazard;
    int delay;
    int m;
    int n;

    string *animals = ({"hamster", "large frog", "white rabbit",
        "frenzied gopheroo", "sinister black lizard", "striped badger",
        "grey wolf", "wild boar", "huge black wolf"});

    /*  First thing to do is see if any npc's have fallen into the local pit or
        down the slope into an adjacent room.  If any are in there, try to get
        one out.  This will only happen if the battle continues on ground level
        since the ground combat object self-destructs when fighting stops.

        If the absentee is in a room that doesn't have a standard exit to this
        room, he's either already returned to this room or has strayed too far
        from the battle to be retrieved by this function.  */

    if (sizeof(Absentee_List))

        {

        n = random(sizeof(Absentee_List));
        other_room = environment(Absentee_List[n]);

        m = member_array(file_name(Room), other_room->query_exit_rooms());

        if (m != -1)
            Absentee_List[n]->command(other_room->query_exit_cmds()[m]);

        else Absentee_List -= ({Absentee_List[n]});

        }

    /*  Begin ground combat sequence.  */

    /*  Look for someone who is actually being attacked.  */

    while (sizeof(livings))

        {

        m = random(sizeof(livings));
        Enemy = livings[m];
        Victim = Enemy->query_attack();

        if (Victim)

            {

            livings = ({});

            }

        else

            {

            livings -= ({livings[m]});

            }

        }

    if (!Victim)  /* Fight is over.  */

        {

        remove_object();
        return;

        }

    if (environment(Victim) != Room) return;  /* Victim has just wimpied! */

    /*  As the battle progresses, Threshold increases, making the hazards
        harder to avoid.  This value only affects Victim; Enemy's ability to
        use the hazards against Victim is tested against a constant value.  */

    Threshold += 10;

    Hazard_Verb = "";
    current_hazard = Hazards[random(sizeof(Hazards))];

    switch (current_hazard)

        {

        case "puddle":

        if (Victim->query_stat(SS_DEX) + Victim->query_skill(SS_AWARENESS)
            > random(Threshold)) return;

        Hazards -= ({"puddle"});  /*  Only 1 puddle-slip per battle.  */

        if (Victim->query_stat(SS_DEX) + Victim->query_skill(SS_ACROBAT)
            > random(Threshold))

            {

            tell_room(Room,
                QCTNAME(Victim) + " slips as " +
                Victim->query_pronoun() +
                " steps in a puddle but manages to" +
                " avoid falling down.\n");

            tell_object(Victim,
                "You slip in a puddle but manage to" +
                " avoid falling down.\n");

            }

        else

            {

            tell_room(Room,
                QCTNAME(Victim) + " slips and falls in a puddle!\n",
                ({Victim}));

            tell_object(Victim,
                "You suddenly slip and fall in a puddle!\n");

            get_back_up(Victim);

            }

        break;

        case "root":

        if (Victim->query_stat(SS_WIS) + Victim->query_skill(SS_CLIMB)
            > random(Threshold)) return;

        if (Victim->query_stat(SS_INT) + Victim->query_skill(SS_ACROBAT)
            > random(Threshold))

            {

            tell_room(Room,
                QCTNAME(Victim) + " stumbles over" +
                " a tree root but manages to avoid falling down.\n");

            tell_object(Victim,
                "You stumble over a tree root but manage" +
                " to avoid falling down.\n");

            }

        else

            {

            tell_room(Room,
                QCTNAME(Victim) + " stumbles over a tree root and" +
                " falls to the ground!\n",
                ({Victim}));

            tell_object(Victim,
                "You suddenly slip and fall to the ground!\n");

            if (!falls_down_slope(Victim)) get_back_up(Victim);

            }

        break;

        case "bog":

        /*  The use of sneak as the key avoidance skill for soft ground may
            strike you as a bit odd, but I figure that players who are trained
            to move stealthily are also skilled at being "light on their feet";
            that is, they naturally pay more attention to where and on what
            they're stepping even when they're not actively sneaking.  The
            wisdom factor is used to check whether they're currently practicing
            what they've learned.  Once they step into the bog, int and
            appraise object determine whether they can take a good look at
            what's got them by the ankles and figure out how to extract
            themselves.  */

        if (Victim->query_stat(SS_WIS) + Victim->query_skill(SS_SNEAK)
            > random(Threshold)) return;

        if (Victim->query_stat(SS_INT) + Victim->query_skill(SS_APPR_OBJ)
            > random(Threshold))

            {

            tell_room(Room,
                QCTNAME(Victim) + " begins to sink into" +
                " the bog but manages to pull " +
                Victim->query_objective() + "self" +
                " free before getting stuck.\n");

            tell_object(Victim,
                "You begin to sink into the bog but pull" +
                " yourself free before you become stuck.\n");

            }

        else

            {

            tell_room(Room,
                QCTNAME(Victim) + " suddenly steps on a soft" +
                " spot and plunges into the bog!\n",
                ({Victim}));

            tell_object(Victim,
                "You suddenly step on a soft spot and plunge" +
                " into the bog!\n");

            get_back_up(Victim);

            }

        break;

        case "animal":

        Hazards -= ({"animal"});  /* Only 1 animal per battle. */

        if (Victim->query_stat(SS_INT) + Victim->query_skill(SS_AWARENESS)
            > random(Threshold))

            {

            m = random(sizeof(animals));

            tell_room(Room,
                "[The " + animals[m] + " decides to come" +
                " out of hiding.]\n" +
                "A " + animals[m] + " is" +
                " startled by the sound of battle and runs past" +
                " you into the forest depths.\n" +
                "The " + animals[m] + " leaves " +
                directions[random(sizeof(directions))] + ".\n");

            return;

            }

        /*  This is the only hazard that does not knock the player down, so the
            recovery is dependent not upon fatigue but on panic.  Also, the
            player's DIS is queried so that braver players are charged by more
            ferocious beasts.  */

        delay = Victim->query_panic() * 5 / Victim->query_stat(SS_DIS);
        if (delay > 4) delay = 4;
        m = Victim->query_stat(SS_DIS) / 10;
        if (m > sizeof(animals) - 1) m = sizeof(animals) - 1;

        tell_room(Room,
            "[The " + animals[m] + " decides to come" +
            " out of hiding.]\n");

        if (Victim->query_stat(SS_DEX) + Victim->query_skill(SS_ANI_HANDL)
            > random(Threshold))

            {

            tell_room(Room,
                "A " + animals[m] +
                " suddenly springs up in front of " +
                QTNAME(Victim) + ", who deftly steps aside to" +
                " let it run away into the forest depths without" +
                " losing " + Victim->query_possessive() +
                " concentration on the battle.\n",
                ({Victim}));

            tell_object(Victim,
                "A " + animals[m] +
                " suddenly springs up in front of you!" +
                " You deftly step aside to let it run away" +
                " into the forest depth without" +
                " losing your concentration on the battle.\n");

            }

        else

            {

            tell_room(Room,
                "A " + animals[m] +
                " suddenly springs up in front of " +
                QTNAME(Victim) + ", who jumps out of its" +
                " way and then moves back into position " +
                Variable_Time[delay] + ".\n",
                ({Victim}));

            tell_object(Victim,
                "A " + animals[m] +
                " suddenly springs up and charges you!" +
                " You jump out of its" +
                " way, then move back into position " +
                Variable_Time[delay] + ".\n");

            Victim->add_attack_delay(m + 1, 1);
            Victim->add_panic((m + 1) * 10, 1);

            }

        tell_room(Room,
            "The " + animals[m] + " leaves " +
            directions[random(sizeof(directions))] + ".\n");

        break;

        case "log":

        /*  Avoiding the log hazard is a matter of staying away from logs that
            might trip you, so you must be wise enough to add this practice to
            your combat technique and know which logs are a threat and which
            aren't. If you fail to avoid the hazard, your Enemy needs the same
            skill and stat to recognize your precarious position.  */

        if (Victim->query_stat(SS_WIS) + Victim->query_skill(SS_APPR_OBJ)
            > random(Threshold)) return;

        Hazard_Verb = "shove";

        if (Enemy->query_stat(SS_WIS) +
            Enemy->query_skill(SS_APPR_OBJ)
            > random(200))

            {

            if (Enemy->query_stat(SS_INT) > random(100))

                {

                /*  Smart people tend to get a more informative message.  */

                Enemy->catch_msg("[" + QCTNAME(Victim) +
                    " is standing on a loose log! If you shove it," +
                    " you may be able to knock " +
                    Victim->query_objective() + " down.]\n");

                }

            else

                {

                Enemy->catch_msg("[" + QCTNAME(Victim) +
                    " is standing on a loose log.]\n");

                }

            }

        break;

        case "branch":

        /*  Avoiding the branch hazard is a matter of ducking and maneuvering
            around the branches - there are plenty of them - as you fight, so
            you need good defense skill and dexterity. If you fail to avoid the
            hazard, your Enemy needs wisdom and an estimate of your ducking and
            weaving ability to recognize the right moment to swing a branch in
            your direction.  */

        if (Victim->query_stat(SS_DEX) +
            Victim->query_skill(SS_DEFENSE)
            > random(Threshold)) return;

        Hazard_Verb = "swing";

        if (Enemy->query_stat(SS_WIS) +
            Enemy->query_skill(SS_APPR_MON)
            > random(200))

            {

            if (Enemy->query_stat(SS_INT) > random(100))

                {

                /*  Smart people tend to get a more informative message.  */

                Enemy->catch_msg("[" + QCTNAME(Victim) +
                    " is standing near a low branch! If you swing it," +
                    " you may be able to knock " +
                    Victim->query_objective() + " down.]\n");

                }

            else

                {

                Enemy->catch_msg("[" + QCTNAME(Victim) +
                    " is standing near a low branch.]\n");

                }

            }

        break;

        case "vine":

        /*  Avoiding the vine hazard is a matter of paying attention to what
            you're standing on (in forest rooms, it tends to be leaves and
            vines unless you're on a trail or already in another hazard), so
            you must be smart enough to keep your feet planted on the right
            plants and have some training in recognizing which plant is which.
            If you fail to avoid the hazard, your Enemy needs to wisely
            estimate when your feet are encircled by the right vine.  */

        if (Victim->query_stat(SS_INT) +
            Victim->query_skill(SS_HERBALISM)
            > random(Threshold)) return;

        Hazard_Verb = "yank";

        if (Enemy->query_stat(SS_WIS) +
            Enemy->query_skill(SS_HERBALISM)
            > random(200))

            {

            if (Enemy->query_stat(SS_INT) > random(100))

                {

                /*  Smart people tend to get a more informative message.  */

                Enemy->catch_msg("[" + QCTNAME(Victim) +
                    "'s feet are encircled by a strong vine! If" +
                    " you yank it, you may be able to trip " +
                    Victim->query_objective() + ".]\n");

                }

            else

                {

                Enemy->catch_msg("[" + QCTNAME(Victim) +
                    "'s feet are encircled by a strong vine.]\n");

                }

            }

        break;

        case "pit":

        /*  This one is pretty simple - just call the pit function and see if
            Victim falls in.  If he doesn't, nothing else happens.  */

        falls_in_pit(Victim);

        break;

        default:

        /*  It's entirely possible that a hazard will be present in the room
            that the ground combat control object isn't prepared to process.
            Remove it from the array so it doesn't get processed again during
            this fight.  */

        Hazards -= ({current_hazard});

        }

    if (!interactive(Enemy))

        {

        /*  If Enemy is an npc, we have to make it execute the appropriate
            command to use a log, vine, or branch.  As a forest dweller, it's
            familiar with the local terrain and always exploits the hazard if
            it sees it.  A simple intelligence test is sufficient.  */

        if (current_hazard == "log" ||
            current_hazard == "vine" ||
            current_hazard == "branch")

            {

            if (Enemy->query_stat(SS_INT) > random(50))
                Enemy->command(Hazard_Verb + " " + current_hazard);

            }

        }

    }

// Function:  yank_vine(vine)

/*

Purpose:  yank the vine to try and trip "Victim."

Arguments:  string containing "vine".
Returns:  0/1.

*/

int
yank_vine(string vine)

    {

    /*  Although "Enemy" is the player who was notified of the opportunity, any
        player in the room can yank the vine.  */

    object tp = this_player();
    int delay;

    /*  If "yank" is not the current Hazard_Verb, then there's nothing to yank.
        Act as if this command doesn't even exist.  Also, don't let a player
        exploit his own hazard.  */

    if (Hazard_Verb != "yank" || tp == Victim) return 0;

    if (!wildmatch("*vine", vine))

        {

        notify_fail("Yank what - the vine?\n");
        return 0;

        }

    /*  Make sure that Victim hasn't left the room. If he has, give an
        appropriate message but leave the hazard in place just in case he
        returns before the time limit is up.  */

    if (environment(Victim) != Room)

        {

        if (tp == Enemy)

            {

            tp->catch_msg(QCTNAME(Victim) + " stepped away from the" +
                " vine before you could yank it.\n");

            }

        else

            {

            tell_object(tp, "You yank on a vine.\n");

            tell_room(Room,
                QCTNAME(tp) + " yanks on a vine.\n", ({tp}));

            }

        return 1;

        }

    if (Enemy->query_stat(SS_STR) +
        Enemy->query_skill(SS_HERBALISM)
        > random(200))

        {

        /*  At this point tp has successfully yanked the vine. It's up to
            Victim to evade it or suffer the penalty. Either way, the hazard
            will be cancelled so that other players can't try to use it again.
            */

        if (Victim->query_stat(SS_DEX) +
            Victim->query_skill(SS_ACROBAT)
            > random(Threshold))

            {

            tell_room(Room,
                QCTNAME(tp) + " yanks on a vine in an attempt to trip " +
                QTNAME(Victim) + ", who deftly hops out of its way.\n",
                ({tp, Victim}));

            tp->catch_msg("You yank on the vine near " +
                QTNAME(Victim) + "'s feet, but " +
                Victim->query_pronoun() + " deftly hops out" +
                " of its way.\n");

            Victim->catch_msg(QCTNAME(tp) + " yanks on a vine in" +
                " an attempt to trip you, but you deftly hop" +
                " out of its way.\n");

            }

        else

            {

            tell_room(Room,
                QCTNAME(tp) + " yanks on a vine that snags " +
                QTNAME(Victim) + "'s feet and knocks " +
                Victim->query_objective() +
                " to the ground!\n",
                ({tp, Victim}));

            tp->catch_msg("You yank on a vine that snags " +
                QTNAME(Victim) + "'s feet and knock " +
                Victim->query_objective() +
                " to the ground!\n");

            Victim->catch_msg(QCTNAME(tp) +
                " yanks on a vine that snags" +
                " your feet and knocks you to the ground!\n");

            if (!falls_in_pit(Victim)) get_back_up(Victim);

            }

        Hazard_Verb = "";

        }

    else

        {

        /*  At this point tp has yanked the vine but failed to trip the Victim.
            If he pulled well, the vine remains in place for someone else to
            try, but the difficulty of tripping the Victim is increased. If he
            pulled badly, the vine is snapped and taken out of play.  */

        if (tp->query_stat(SS_DEX) +
            tp->query_stat(SS_INT)
            > random(Threshold))

            {

            /*  If he passed this test, tp pulled well but simply at the wrong
                moment.  */

            tell_room(Room,
                QCTNAME(tp) + " yanks on a vine in an attempt" +
                " to trip someone but fails.\n",
                ({tp}));

            tp->catch_msg("You yank on the vine near " +
                QTNAME(Victim) + "'s feet but fail to trip " +
                Victim->query_objective() + ".\n");

            Threshold += 100;

            }

        else

            {

            /*  Tp pulled too clumsily.  */

            tell_room(Room,
                QCTNAME(tp) + " yanks on a vine and breaks it.\n",
                ({tp}));

            tp->catch_msg("You yank clumsily on the vine" +
                " and break it!\n");

            Hazard_Verb = "";

            }

        }

    return 1;

    }

// Function:  shove_log(log)

/*

Purpose:  shove the log to try and trip "Victim."

Arguments:  string containing "log".
Returns:  0/1.

*/

int
shove_log(string log)

    {

    /*  Although "Enemy" is the player who was notified of the opportunity, any
        player in the room can shove the log.  */

    object tp = this_player();
    int delay;

    /*  If "shove" is not the current Hazard_Verb, then there's nothing to
        shove. Act as if this command doesn't even exist.  Also, don't let a
        player explout his own hazard.  */

    if (Hazard_Verb != "shove" || tp == Victim) return 0;

    if (!wildmatch("*log", log))

        {

        notify_fail("Shove what - the log?\n");
        return 0;

        }

    /*  Make sure that Victim hasn't left the room. If he has, give an
        appropriate message but leave the hazard in place just in case he
        returns before the time limit is up.  */

    if (environment(Victim) != Room)

        {

        if (tp == Enemy)

            {

            tp->catch_msg(QCTNAME(Victim) + " stepped away from the" +
                " log before you could shove it.\n");

            }

        else

            {

            tell_object(tp, "You shove a log.\n");

            tell_room(Room,
                QCTNAME(tp) + " shoves a log.\n", ({tp}));

            }

        return 1;

        }

    if (Enemy->query_stat(SS_STR) +
        Enemy->query_skill(SS_UNARM_COMBAT)
        > random(200))

        {

        /*  At this point tp has successfully shoved the log. It's up to Victim
            to evade it or suffer the penalty. Either way, the hazard will be
            cancelled so that other players can't try to use it again.  */

        if (Victim->query_stat(SS_DEX) +
            Victim->query_skill(SS_ACROBAT)
            > random(Threshold))

            {

            tell_room(Room,
                QCTNAME(tp) + " shoves a log on which " +
                QTNAME(Victim) + " is standing, but " +
                Victim->query_pronoun() +
                " jumps off without losing " +
                Victim->query_possessive() + " balance.\n",
                ({tp, Victim}));

            tp->catch_msg("You shove the log on which " +
                QTNAME(Victim) + " is standing, but " +
                Victim->query_pronoun() + " jumps off it" +
                " without losing " +
                Victim->query_possessive() + " balance.\n");

            Victim->catch_msg(QCTNAME(tp) + " shoves a log" +
                " that is supporting your weight, but you jump" +
                " off it without losing your balance.\n");

            }

        else

            {

            tell_room(Room,
                QCTNAME(tp) + " shoves a log out from under " +
                QTNAME(Victim) + "'s feet and knocks " +
                Victim->query_objective() +
                " to the ground!\n",
                ({tp, Victim}));

            tp->catch_msg("You shove a log out from under " +
                QTNAME(Victim) + "'s feet and knock " +
                Victim->query_objective() +
                " to the ground!\n");

            Victim->catch_msg(QCTNAME(tp) +
                " shoves a log out from under" +
                " your feet and knocks you to the ground!\n");

            if (!falls_in_pit(Victim)) get_back_up(Victim);

            }

        Hazard_Verb = "";

        }

    else

        {

        /*  At this point tp has tried to shove the log but failed. If he
            failed badly enough, he's knocked down himself.  */

        if (tp->query_stat(SS_STR) +
            tp->query_stat(SS_DEX)
            > random(200))

            {

            /*  If he passed this test, tp simply shoved but failed.  */

            tell_room(Room,
                QCTNAME(tp) + " tries to shove a log but fails.\n",
                ({tp}));

            tp->catch_msg("You try to shove the log but can't get a" +
                " grip on its slippery surface.\n");

            Threshold += 100;

            }

        else

            {

            /*  Tp shoved too clumsily.  */

            tell_room(Room,
                QCTNAME(tp) + " trips over a log and falls flat on " +
                tp->query_possessive() + " face!\n",
                ({tp}));

            tp->catch_msg("You try to shove a log but slip and" +
                " fall flat on your face!\n");

            get_back_up(tp);
            Hazard_Verb = "";

            }

        }

    return 1;

    }

// Function:  swing_branch(branch)

/*

Purpose:  swing the branch and hit "Victim" in the face.

Arguments:  string containing "branch".
Returns:  0/1.

*/

int
swing_branch(string branch)

    {

    /*  Although "Enemy" is the player who was notified of the opportunity, any
        player in the room can swing the branch.  */

    object tp = this_player();
    int delay;

    /*  If "swing" is not the current Hazard_Verb, then there's nothing to
        swing. Act as if this command doesn't even exist.  Also, don't let a
        player exploit his own hazard.  */

    if (Hazard_Verb != "swing" || tp == Victim) return 0;

    if (!wildmatch("*branch", branch))

        {

        notify_fail("Swing what - the branch?\n");
        return 0;

        }

    /*  Make sure that Victim hasn't left the room. If he has, give an
        appropriate message but leave the hazard in place just in case he
        returns before the time limit is up.  */

    if (environment(Victim) != Room)

        {

        if (tp == Enemy)

            {

            tp->catch_msg(QCTNAME(Victim) + " stepped away from the" +
                " branch before you could swing it.\n");

            }

        else

            {

            tell_object(tp, "You swing a branch.\n");

            tell_room(Room,
                QCTNAME(tp) + " swings a branch.\n", ({tp}));

            }

        return 1;

        }

    if (Enemy->query_stat(SS_DEX) +
        Enemy->query_skill(SS_ACROBAT)
        > random(200))

        {

        /*  At this point tp has successfully swung the branch. It's up to
            Victim to evade it or suffer the penalty. Either way, the hazard
            will be cancelled so that other players can't try to use it again.
            */

        if (Victim->query_stat(SS_STR) +
            Victim->query_skill(SS_PARRY)
            > random(Threshold))

            {

            tell_room(Room,
                QCTNAME(tp) + " swings a low branch toward " +
                QTNAME(Victim) + ", who easily ducks out of the way.\n",
                ({tp, Victim}));

            tp->catch_msg("You swing a low branch toward " +
                QTNAME(Victim) + ", who easily ducks out of the way.\n");

            Victim->catch_msg(QCTNAME(tp) + " swings a low" +
                " branch in your direction, but you easily duck" +
                " out of its way.\n");

            }

        else

            {

            tell_room(Room,
                QCTNAME(tp) + " swings a low branch into " +
                QTNAME(Victim) + "'s face and knocks " +
                Victim->query_objective() + " off " +
                Victim->query_possessive() + " feet!\n",
                ({tp, Victim}));

            tp->catch_msg("You swing a low branch into " +
                QTNAME(Victim) + "'s face and knock " +
                Victim->query_objective() + " off " +
                Victim->query_possessive() + " feet!\n");

            Victim->catch_msg(QCTNAME(tp) +
                " swings a low branch into your face and knocks" +
                " you off your feet!\n");

            if (!falls_in_pit(Victim)) get_back_up(Victim);

            }

        Hazard_Verb = "";

        }

    else

        {

        /*  At this point tp has tried to swing the branch but failed. If he
            failed badly enough, he's knocked down himself.  */

        if (tp->query_stat(SS_STR) +
            tp->query_stat(SS_DEX)
            > random(Threshold))

            {

            /*  If he passed this test, tp simply shoved but failed.  */

            tell_room(Room,
                QCTNAME(tp) + " tries to swing a branch but fails.\n",
                ({tp}));

            tp->catch_msg("You try to swing the branch but your" +
                " hands slip on the smooth bark.\n");

            Threshold += 100;

            }

        else

            {

            /*  Tp shoved too clumsily.  */

            tell_room(Room,
                QCTNAME(tp) + " tries to swing a low branch at" +
                " someone, but the branch springs back, smacking " +
                tp->query_objective() +
                " squarely in the face and knocking " +
                tp->query_objective() + " flat on " +
                tp->query_possessive() + " back!\n",
                ({tp}));

            tp->catch_msg("You swing a branch at " + QCTNAME(tp) +
                " but the branch springs back and knocks you" +
                " flat on your back!\n");

            if (!falls_in_pit(tp)) get_back_up(tp);
            Hazard_Verb = "";

            }

        }

    return 1;

    }

// Function:  enter_env(to, from)

/*

Purpose:  assigns values to some global variables. It is called when this
object enters another object's inventory; this should only happen once when the
object is cloned and then moved into a central forest room. This object does
not move. It controls combat in the room into which it was moved, and when
combat ends there it is removed from the game.

Arguments:  none.
Returns:  nothing.

*/

void
enter_env(object place_to, object place_from)

    {

    ::enter_env(place_to, place_from);
    Room = place_to;
    Hazards = Room->query_prop(FOREST_COMBAT_INVENTORY);
    if (!Hazards) remove_object();

    }

// Function:  init()

/*

Purpose:  add local commands.
Arguments:  none.
Returns:  nothing.

*/

void
init()

    {

    ::init();
    add_action(shove_log, "shove");
    add_action(swing_branch, "swing");
    add_action(yank_vine, "yank");

    }

// OBJECT DEFINITION

create_object()

    {

    set_no_show();
    set_name("_ground_combat_object");
    add_name(filename(this_object());
    set_short("_ground_combat_object");
    set_long("_ground_combat_object");

    /*  PROPERTIES  */

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);

    /*  ALARM  */

    set_alarm(15.0, 15.0, ground_combat_effect);

    }
