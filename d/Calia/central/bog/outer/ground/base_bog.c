// ROOM:  base_bog.c

    /*  Calia Domain

    HISTORY

    [99-06-22] created by Uhclem from
    [D:\CALIA\CENTRAL\BOG\OUTER\GROUND\BASE_BOG.DOC].

    PURPOSE

    This is the base for bog rooms surrounding the Sanctimonian fortress.  The
    bog itself is not much of a playing area; its features are intentionally
    designed to be unpleasant and dangerous with no redeeming value.  Smart
    players will learn to cross it quickly on their way to or from the
    fortress.

    IMPORTANT NOTE:  The bog is designed to be "solid," a mass of contiguous
    rooms with few gaps.  Most rooms created with this baseroom should have at
    least 6 adjacent rooms.  If you have fewer exits, you may defeat the
    special exit configuring routines; however, at the edge of the bog where it
    connects with non-bog rooms, that may be exactly what you want.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/bog/baseroom";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include "defs.h"

#define FILTER_ENEMIES(x) \
    filter(all_inventory(this_object()), &operator(==)(x) @ &->query_attack())

// FUNCTIONS

// Function:  unq_no_move(string str)

/*

Purpose:  penalize a player for trying to take a nonexistent exit.  He steps
onto a part of the bog that's too soft to support his weight.  He'll
automatically be returned to his oroginal position after some fatigue and
possible loss of some items he's carrying.  This function overrides the
standard unq_no_move in the standard room.

Arguments:  a string is provided to hold any input, but as with the standard
function, it is not processed in any way.

Returns:  1.

*/

int
unq_no_move(string str)

{

    object tp = this_player();
    object *tp_inventory;
    object ob;
    int tp_penalty;
    int tp_drop_something = 0;
    int m;

    if (query_verb() == "up")

    {

        write("There is no obvious exit up.\n");

    }

    else if (query_verb() == "down")

    {

        write("You ponder descending into the bog, but" +
            " the murky depths are far too" +
            " vegetation-clogged for swimming.\n");

        say(QCTNAME(tp) + " tries to go down into the depths of" +
            " the bog but fails.\n");

    }

    /*
     *  If the player didn't try to go up or down, then he must have gotten 
     *  here by trying to go in a compass direction for which there is no
     *  exit.  He falls into the bog, and in the process of clambering out
     *  experiences some fatigue and may lose some objects he's carrying.    
     */

    else

    {

        tp_penalty = 1 + (100 /
            (tp->query_stat(SS_DEX) + tp->query_skill(SS_ACROBAT) + 1));

        tp_inventory = all_inventory(tp);

        if (tp_penalty > sizeof(tp_inventory))
            tp_penalty = sizeof(tp_inventory);

        for (m = 0; m < tp_penalty ; m += 1)

        {

            ob = tp_inventory[random(sizeof(tp_inventory))];

            if (ob->num_heap())

            {

                if (!tp->query_wiz_level())

                {

                    ob->set_heap_size(tp_inventory->num_heap() - 1);
                    tp_drop_something = 1;

                }

                else

                {

                    write("[If you were not a wizard, the" +
                        " bog would have swallowed your " +
                        ob->singular_short() + ".]\n");

                }

            }

            else if (!ob->query_worn() &&
                !ob->query_wielded() &&
                !ob->query_auto_load() &&
                !living(ob))

            {

                if (!tp->query_wiz_level())

                {

                    ob->remove_object();
                    tp_drop_something = 1;

                }

                else

                {

                    write("[If you were not a wizard, the" +
                        " bog would have swallowed your " +
                        ob->short() + ".]\n");

                }

            }

        }

        tp->add_fatigue(tp_penalty * 10);

        write("You step onto a soft part of the bog and quickly" +
            " sink into the morass of tangled vegetation" +
            " and rotting debris! After a bit of thrashing about," +
            " you manage to climb back to where you were before.\n");

        say(QCTNAME(tp) + " steps onto a soft part of the bog" +
            " and quickly sinks into the morass of" +
            " tangled vegetation and rotting debris! After a" +
            " bit of thrashing about, " + tp->query_pronoun() +
            " manages to climb back to where " + tp->query_pronoun() +
            " was before.\n");

        if (tp_drop_something && random(100) < tp->query_skill(SS_AWARENESS))

        {

            write("You suspect that you may have dropped" +
                " something while you were thrashing about" +
                " in the bog.\n");

        }

    }

    return 1;

}

// Function:  bog_move()

/*

Purpose:  determines if a player can exit the room.  Key factors are burden and
the number of people attacking you.

Arguments:  none.

Returns:  0/1.

*/

int
bog_move()

{

    object tp = this_player();
    object *enemies = FILTER_ENEMIES(tp);
    object enemy;
    int burden = tp->query_encumbrance_weight();

    if (tp->query_stat(SS_DEX) +
        tp->query_stat(SS_DIS) +
        tp->query_skill(SS_DEFENSE)
        >
        random((sizeof(enemies) + 1) * burden))

    {

        return 0;

    }



    if (sizeof(enemies))

    {

        enemy = enemies[random(sizeof(enemies))];

        switch (burden)

        {

            case 0..33:

            tp->catch_msg(QCTNAME(enemy) + " stands in your way, " +
                " and in the treacherous footing of the bog you" +
                " can't seem to maneuver around " +
                enemy->query_objective() + ".\n");

            break;

            case 34..66:

            tp->catch_msg(QCTNAME(enemy) + " stands in your way, " +
                " and the weight you're carrying" +
                " prevents you from maneuvering around " +
                enemy->query_objective() + ".\n");

            break;

            default:

            tp->catch_msg(QCTNAME(enemy) + " stands in your way, " +
                " and your heavy load pushes you so deep into the" +
                " bog that you can hardly seem to lift your" +
                " feet, much less maneuver around an enemy.\n");

        }

        enemy->catch_msg(QCTNAME(tp) +
            " tries to go " + query_verb() + ", but" +
            " on the soft ground " +
            tp->query_pronoun() + " cannot maneuver around you.\n");

        tell_room(this_object(),
            QCTNAME(tp) +
            " tries to go " + query_verb() + ", but" +
            " on the soft ground " +
            tp->query_pronoun() + " cannot maneuver around " +
            QTNAME(enemy) + ".\n",
            ({tp, enemy}));

    }

    else

    {

        switch (burden)

        {

            case 0..33:

            tp->catch_msg("You stumble and fall as you try" +
                " to go " + query_verb() + ", tripped up by" +
                " the soft ground underfoot.\n");

            break;

            case 34..66:

            tp->catch_msg("You stumble under your load as you try to" +
                " go " + query_verb() + " and only barely" +
                " manage to avoid plunging into the bog.\n");

            break;

            default:

            tp->catch_msg("Your heavy load drives you knee-deep into" +
                " the bog as you try to go " + query_verb() + "," +
                " and you stop to free yourself from its grasp.\n");

        }

        tell_room(this_object(), QCTNAME(tp) +
            " loses " + tp->query_possessive() + " footing on" +
            " the soft ground as " + tp->query_pronoun() +
            " tries to go " + query_verb() + ".\n",
            ({tp}));

    }

    /*
     *  The following penalty is fairly severe, but the bog is a severe 
     *  environment.  The object of this entire routine is to make carrying a
     *  heavy load through the bog a mistake of geometrically-increasing
     *  magnitude.  The heavier the load, the more likely you are to fail the
     *  test above and incur the penalty below.  Conversely, if you drop some
     *  weight, you immediately become more likely to pass the test and will
     *  incur a smaller penalty even if you don't.  All a player needs to do is
     *  figure this out before his fatigue gets to the point where he can't
     *  muster the strength to walk out of here (and becomes a prime target for
     *  a wandering Santimonian).    
     */

    tp->add_fatigue(-tp->query_encumbrance_weight());
    return 1;

}

// Function:  hook_smelled(item)

/*

Purpose:  add smell characteristics to items in the room.

Arguments:  string indicating which item is being smelled.

Returns:  nothing.

*/

void
hook_smelled(string item)

{

    switch (item)

    {

        case "bog":
        case "dark bog":

        write("The whole area has a musty smell" +
            " of rotting vegetation.\n");

        break;

        case "water":
        case "liquid":

        write("The water has an unpleasant, pungent odor" +
            " that immediately signals rot, yet the bubbles" +
            " that rise periodically are less repellent.\n");

        break;

        case "bubbles":

        write("Oddly enough, the bubbles don't smell quite so bad as the" +
            " rest of the bog. They remind you a bit of the" +
            " aroma of a brewery, or perhaps of rising bread dough.\n");

        break;

        case "vegetation":

        write("Unpleasant odors of decay permeate everything" +
            " growing here; if the vegetation has its own" +
            " distinctive scent, you cannot discern it.\n");

        break;

        case "trees":
        case "tree":

        write("The trees smell vaguely of bark and leaves," +
            " nothing remarkable and hardly perceptible under" +
            " the unpleasant smells pervading the bog.\n");

        break;

        case "mist":
        case "dense mist":
        case "thick mist":
        case "swirling mist":

        write("As unlikely as it may seem, the mist carries the" +
            " distinctive smell of fresh-cut wood, perhaps " +
            ({"cedar", "pine", "spruce", "fir"})[random(4)] + ".\n");

        break;

        default:

        write("You detect the musty odors of mold and rotting vegetation.\n");

    }

}

// Function:  bog_effects()

/*

Purpose:  (1) tell players about periodic bog movements; (2) remove room when
it is not in use so that the exits and descriptions will be recreated the next
time the room is entered.

Arguments:  none.

Returns:  nothing.

*/

void
bog_effects()

{

    if (!sizeof(FILTER_LIVE(all_inventory(this_object()))))

    {

        remove_object();
        return;

    }

    /*
     *  If you add any sentences to the string array below, be sure to update 
     *  the integer at the end to reflect the new element count.    
     */

    tell_room(this_object(),
        ({"The surface of the bog sags and ripples under your weight.\n",
        "A great bubble of gas swells the surface of the" +
        " bog, which rises momentarily and then flattens again" +
        " as it disgorges its musty load into the air.\n",
        "Some vague gurgling noises emerge from under the surface" +
        " of the bog as if something were being" +
        " digested, perhaps with resistance.\n",
        "The trees sway momentarily in unison, silently reacting" +
        " to some motion in the bog.\n",
        "A few bubbles rise up from the depths of the bog and" +
        " waft a pungent scent toward your nostrils.\n",
        "Strange noises echo throughout the bog, some" +
        " sounding like distant thunder, others seeming to" +
        " come from just beneath the surface.\n",
        "Somewhere in the bog a deep frog voice booms: " +
        ({"burlap", "foomp", "oorororg", "yoomp"})[random(4)] +
        "!\n",
        "Dozens of tiny bubbles rise to the surface of the bog and" +
        " pop in quick succession.\n",
        "Tendrils of thick mist curl around you.\n",
        "Eddies suddenly appear in the mist, little" +
        " white whirlpools barely visible in the shadow cast by" +
        " the trees, and then just as quickly disappear.\n"})[random(10)]);

}

// Function:  ground_description()

/*

Purpose:  return a description of the ground underfoot that varies according to
the viewer's skills and the amount of light available.

Arguments:  none.

Returns:  string containing descriptive text which may include exit
information.

*/

string
ground_description()

{

    object tp = this_player();

    int perception = (query_prop(OBJ_I_LIGHT) - 1) * 10 +
        tp->query_prop(LIVE_I_SEE_DARK) * 50 +
        tp->query_skill(SS_AWARENESS);

    string *exit_directions = query_exit_cmds();
    string description;

    switch (perception)

    {

        case -9999..0:

        description = "It is too dark to see.\n";
        break;

        case 1..10:

        description = "You can only barely detect that" +
            " there's anything under your feet at all. It's wet" +
            " and smelly, but more than that you cannot discern.\n";

        break;

        case 11..30:

        description = "The ground does not seem solid at all," +
            " but soft and pliant, giving way under your" +
            " weight with every step.\n";

        break;

        case 31..50:

        description = "The bog is covered with thick" +
            " vegetation that rises from deep water, from which" +
            " bubbles rise periodically and waft peculiar" +
            " smells toward you.  Like a natural raft," +
            " the surface supports your weight and bobs up and" +
            " down as you move.\n";

        break;

        case 51..70:

        description = "The bog is covered with thick" +
            " vegetation that rises from deep water. Like a" +
            " natural raft, it supports your weight and bobs up and" +
            " down as you move. The vegetation doesn't cover the" +
            " surface of the bog uniformly; some parts" +
            " are obviously strong enough to hold you, others may" +
            " not be, but in the darkness it's difficult to" +
            " determine where you may safely tread.\n";

        break;

        case 71..90:

        description = "The bog is covered with thick" +
            " vegetation that rises from deep water, and you" +
            " can see nothing other than some rotting debris enmeshed" +
            " in it. The tangled vegetation forms" +
            " a surface that supports your weight here," +
            " alebit with some sagging, but it doesn't" +
            " look to be uniformly distributed. A false step" +
            " could send you plunging into the depths of the bog.\n";

        break;

        case 91..110:

        description = "The bog is covered with thick" +
            " vegetation that rises from deep water, and you" +
            " can see nothing other than some rotting debris enmeshed" +
            " in it. The tangled vegetation forms" +
            " a surface that supports your weight here," +
            " alebit with some sagging, but it isn't" +
            " uniformly distributed. To the " +
            exit_directions[0] +
            " and " +
            exit_directions[sizeof(exit_directions)-1] +
            " it looks solid enough to walk on.\n";

        break;

        default:

        description = "The bog is covered with a thick" +
            " mat of tangled vegetation and rotting debris." +
            " It supports your weight like a natural raft" +
            " over water whose depth you cannot gauge due to" +
            " its darkness and the concentration of weeds" +
            " and decaying matter. The vegetation" +
            " isn't distributed uniformly, but it looks solid" +
            " enough to support travel to the ";

        if (sizeof(exit_directions) > 2)

        {

            description = description +
                implode(exit_directions[1..(sizeof(exit_directions)-1)], ", ")
                + ", and " + exit_directions[0] + ".\n";

        }

        else

        {

            description = description +
                exit_directions[0] + " and " + exit_directions[1] + ".\n";

        }

    }

    return description;

}

// Function:  enter_inv(object, from_object)

/*

Purpose:  register a player (or foreign npc) with the Sanctimonian control
room.

Arguments:  object entering the room, object from whence it came.

Returns:  nothing.

*/

void
enter_inv(object ob, object from)

{

    ::enter_inv(ob, from);

    if (living(ob) && !ob->sanctimonian()) register_player(ob);

}

// Function:  create_bog(*adjacent_rooms)

/*

Purpose:  Create the room description and add standard attributes.

Arguments:  string containing the filename of this room, string array
containing the filenames of adjacent rooms.

Returns:  nothing.

*/

void
create_bog(string *adjacent_rooms)

{

    string *compass = ({"north", "northeast", "east", "southeast", "south",
        "southwest", "west", "northwest"});

    string *bog_text =
        ({"You stand somewhere within a damp, dark bog that smells" +
        " of decay and mold.",
        "The bog encloses you in dark and dampness.",
        "You find yourself in the depths of a dark bog that" +
        " echoes with the sounds of gurgling liquids and reeks" +
        " of decay and mold.",
        "The bog is dark and clammy, filled with vague" +
        " gurgling sounds and unpleasant odors."});

    string *ground_text =
        ({"Beneath your feet the ground is far from solid; it" +
        " shifts, sags, and bubbles with every step.",
        "Whatever you are standing on is firmer than water" +
        " but softer than solid ground; it seems to pull and cling" +
        " as you move over it.",
        "You trudge slowly as the ground sags and gurgles" +
        " under your weight.",
        "Your feet sink into the ground as you travel" +
        " and make slurping, sucking noises when you lift them."});

    string *mist_text =
        ({"A thick mist conceals the surface of the bog, a" +
        " layer of translucent white over vague areas of" +
        " brown and green.",
        "Mist swirls around your feet and even rises" +
        " occasionally to eye level.",
        "A mist covers the surface of the bog and even seems to" +
        " take on its dull colors, a swirl of vague browns" +
        " and greens that blend in with the trees and water.",
        "Swirling mist rises and falls like ocean" +
        " waves, constantly obscuring whatever surface" +
        " is supporting you.",
        "Dense mist completely blankets the bog, sometimes" +
        " extending a tendril as if to conceal you as well."});

    string *trees_text =
        ({"Tall slender trees surround you, profusely" +
        " covered with twisted branches and broad" +
        " deep green leaves.",
        "Trees grow thickly here, long, slender," +
        " gracefully arched trunks bristling with a myriad" +
        " of twisting branches that produce countless broad leaves.",
        "In graceful arcs the trunks of countless skinny trees" +
        " sprout from the bog and erupt into a tumult" +
        " of twisting branches.",
        "You can just barely make your way through the" +
        " countless trees that grow in this bog, all with" +
        " narrow, curved trunks covered with" +
        " even narrower branches."});

    string *light_text =
        ({"The branches intertwine only a short distance above" +
        " your head, and their leaves block nearly all sunlight.",
        "Only a small amount of light penetrates the leaves" +
        " overhead, and the area is cast in hazy shadows of" +
        " green and brown.",
        "The leaves on the intertwined branches form an" +
        " opaque canopy, casting the entire bog in deep shadow.",
        "No light from above penetrates the leaves overhead;" +
        " some faint rays filter through the thick mist, but" +
        " it's difficult to tell from which direction the" +
        " light is strongest.",
        "Under the dense canopy of intertwined branches and" +
        " leaves no direct sunlight is visible, but" +
        " a little illumination filters in from somewhere far" +
        " away through the swirling mist."});

    object check_room;
    string *dummies;
    string dummy;
    int l;
    int m;
    int n;

    set_short("In a dark, mist-enshrouded bog");

    set_long(bog_text[random(sizeof(bog_text))] + " " +
        ground_text[random(sizeof(ground_text))] + " " +
        mist_text[random(sizeof(mist_text))] + " " +
        trees_text[random(sizeof(trees_text))] + " " +
        light_text[random(sizeof(light_text))] + "\n");

    set_noshow_obvious(1);  /*  Bog exits are never obvious.  */

    if (adjacent_rooms[0]) add_exit(adjacent_rooms[0],
        "north", "@@bog_move@@", 20);

    if (adjacent_rooms[1]) add_exit(adjacent_rooms[1],
        "northeast", "@@bog_move@@", 20);

    if (adjacent_rooms[2]) add_exit(adjacent_rooms[2],
        "east", "@@bog_move@@", 20);

    if (adjacent_rooms[3]) add_exit(adjacent_rooms[3],
        "southeast", "@@bog_move@@", 20);

    if (adjacent_rooms[4]) add_exit(adjacent_rooms[4],
        "south", "@@bog_move@@", 20);

    if (adjacent_rooms[5]) add_exit(adjacent_rooms[5],
        "southwest", "@@bog_move@@", 20);

    if (adjacent_rooms[6]) add_exit(adjacent_rooms[6],
        "west", "@@bog_move@@", 20);

    if (adjacent_rooms[7]) add_exit(adjacent_rooms[7],
        "northwest", "@@bog_move@@", 20);

    /*
     *  Now for the most important part.  The signature of the bog room is its 
     *  peculiar exit array.  Exits are discernable by a player who has good
     *  awareness and location sense and enough light to examine the ground.
     *  The exits added by the block of statements above will now be removed
     *  one by one.  We will keep removing them until we can no longer do so
     *  and still have all four cardinal directions represented in the
     *  exit_cmds array.  Two exits of "northwest" and "southeast" will satisfy
     *  the need for all four directions just as well as four exits to the
     *  cardinal directions themselves.  In addition, we check for any adjacent
     *  rooms which have already been loaded and have defined exits to this
     *  room - we don't delete exits back to those rooms.    
     */

    /*
     *  First, protect any exits to rooms that are already loaded and have 
     *  exits pointing to this room.  The "compass" array contains the list of
     *  exit directions subject to removal; delete a direction from this array
     *  to ensure that the associated exit will not be removed from the room.
     *    
     */

    dummies = query_exit_rooms();
    l = sizeof(dummies) - 1;

    for (m = 0; m < l; m += 1)

    {

        if (check_room = find_object(dummies[m]))

        {

            if (member_array(file_name(this_object()),
                check_room->query_exit_rooms()) != -1)
                compass -= ({query_exit_cmds()[m]});

        }

    }

    /*
     *  Next, scramble the order of compass directions so that we'll try 
     *  deleting them in a different order every time the room is loaded.    
     */

    l = sizeof(compass) - 1;
    for (m = 0; m < l; m += 1)

    {

        n = random(l + 1);
        dummy = compass[m];
        compass[m] = compass[n];
        compass[n] = dummy;

    }

    /*
     *  Finally, remove the exits in the "compass" directions one by one as 
     *  long as we preserve a mention of all four cardinal directions in the
     *  remaining exit commands.    
     */

    for (m = 0; m < l; m+=1)

    {

        dummy = implode(query_exit_cmds() - ({compass[m]}), " ");

        if (wildmatch("*north*", dummy) &&
            wildmatch("*south*", dummy) &&
            wildmatch("*east*", dummy) &&
            wildmatch("*west*", dummy)) remove_exit(compass[m]);

    }

    add_item(({"ground", "surface"}), "@@ground_description@@");

    add_item(({"bog", "dark bog"}),
        "The bog envelopes you with a canopy of branches and leaves" +
        " above and a thick mist on every side. The meager amount" +
        " of light that filters through the trees reveals" +
        " little detail, only shadowy tracts of green and brown" +
        " beneath a layer of swirling mist. Through the mist" +
        " you can see the trunks of many trees, but the surface they" +
        " stand on is only barely visible.\n");

    add_item(({"decay", "mold", "liquid", "liquids", "water",
        "vegetation", "thick vegetation", "tangled vegetation",
        "mat", "thick mat"}),
        "Water permeates everything here, deep brown and opaque" +
        " where it is visible through the mist, and strong odors" +
        " verify the presence of mold and decay. The vegetation" +
        " that floats on the water forms a surface that you can" +
        " walk on, albeit uneasily.\n");

    add_item(({"bubbles", "bubble"}),
        "Bubbles rise frequently to the surface of the bog," +
        " disturbing the mist as they pop.\n");

    add_item(({"mist", "thick mist", "swirling mist", "dense mist"}),
        "The mist is thickest at the ground, if the surface" +
        " upon which you stand can seriously be called" +
        " ground, and it constantly swirls and surges around" +
        " you, rising high enough at times to completely" +
        " obscure your vision and then subsiding again.\n");

    add_item(({"trees", "tall trees", "slender trees", "skinny trees",
        "tree", "tall tree", "slender tree", "skinny tree"}),
        "Trees grow profusely here, barely leaving you room" +
        " to travel between them. Their narrow trunks arch" +
        " gracefully in myriad directions, as if the dampness" +
        " had softened them, and their twisted branches and" +
        " thick clumps of leaves intertwine just above your head.\n");

    add_item(({"branches", "twisted branches", "intertwined branches",
        "branch", "twisted branch", "intertwined branch"}),
        "The branches are so twisted, they're practically tied" +
        " in knots, and they tangle between one tree and the" +
        " next throughout the bog, forming an opaque canopy" +
        " with their broad leaves.\n");

    add_item(({"leaves", "broad leaves", "green leaves",
        "leaf", "broad leaf", "green leaf", "canopy", "opaque canopy"}),
        "Any deeper shade of green would be closer to black." +
        " The leaves are broad and thick, cover" +
        " the twisted branches abundantly, and mesh together" +
        " to absorb any light from above.\n");

    add_item(({"light", "illumination", "shadow", "deep shadow", "ray",
        "shadows", "deep shadows", "rays"}),
        "Hardly any light filters into this area. An occasional" +
        " ray strikes the mist, a sudden shock of bright white" +
        " against the dull browns and greens, but rather" +
        " than reveal any detail, it only serves to further" +
        " limit your vision. Deep shadow conceals the bog's" +
        " secrets and hinders travel.\n");

    add_item(({"morass", "debris", "rotting debris", "forest debris"}),
        "Enmeshed in the tangled vegetation is some ordinary" +
        " forest debris, and the damp conditions are making sure" +
        " that it decays rapidly, making the water" +
        " dark and foul-smelling.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(ROOM_I_HIDE, 95);  /*  Good hiding opportunities here. */
    add_prop(ROOM_I_LIGHT, 1);  /*  Little light. */

    /*
     *  ALARMS    
     */

    set_alarm(30.3, 60.6, bog_effects);

    /*
     *  "uid" settings required for cloning objects.    
     */

    setuid();
    seteuid(getuid());

    /*
     *  NO SPECIAL FUNCTION    
     */

    /*
     *  Just in case you're wondering, the bog rooms do not get the special 
     *  register_room function that goes in other rooms in the bog area.  Bog
     *  rooms remove themselves pretty quickly when they're unoccupied, so
     *  there's no sense registering them with the control room.    
     */

}
