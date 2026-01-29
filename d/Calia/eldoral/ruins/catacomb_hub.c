#pragma strict_types

#include "defs.h"
#include <wa_types.h>
#include <language.h>
#include <composite.h>

#define BLADE_PEN         500
#define WEIGHT_TO_RELEASE 50000    /* 50 kg */
#define TIMEOUT           1800     /* 30 minutes */

inherit STDROOM;

mixed stone_descs = ({ ({"first", "inner", "center"}),
                         ({"second", "middle"}),
                         ({"third", "outer"}) });
mixed wedge_descs = ({ ({"first", "north"}),
                       ({"second", "north-northeast"}),
                       ({"third", "east-northeast"}),
                       ({"fourth", "east"}),
                       ({"fifth", "east-southeast"}),
                       ({"sixth", "south-southeast"}),
                       ({"seventh", "south"}),
                       ({"eighth", "south-southwest"}),
                       ({"ninth", "west-southwest"}),
                       ({"tenth", "west"}),
                       ({"eleventh", "west-northwest"}),
                       ({"twelfth", "north-northwest"}) });
int *sword_freed,
    may_not_reset_id;

/* marked format: marked = ([wedge_index: ([stone_index: ({objects})]) ]);
 *
 * fallen format: fallen = ([wedge_index: ({stone_index}) ]);
 * allweigh format: allweigh = ([wedge_index: weight]);
 */
mapping fallen,
        marked,
        allweigh;
object pedestal,
       may_not_reset;

public int do_drop(string str);

public void
reset_quest()
{
    int i;
    string tempweigh;

  /* Replace or reset pedestal as necessary. */
    if (!pedestal)
    {
        pedestal = clone_object(OBJ + "pedestal");
        pedestal->move(TO, 1);
    }
    else
        pedestal->reset_quest();

  /* Destruct all objects currently being used as markers. */
    for (i = 0; i < m_sizeof(marked); i++)
    {
        tempweigh = m_indexes(allweigh)[i];
        m_values(marked[tempweigh])[0]->remove_object();
    }

  /* Reset global vars. */
    if (m_sizeof(fallen))
        tell_room(TO, "You hear a grinding sound as the fallen " +
            "stones rise back into place.\n");
    fallen = ([]);
    if (m_sizeof(marked))
        tell_room(TO, "A rumbling sound comes from the marked " +
            "stones, and they abruptly flip over, their burden " +
            "vanishing.\n");
    marked = ([]);
    allweigh = ([]);
}

/*
 * Function name: query_reset_lockout
 * Descrition   : Returns object pointer to the current person
 *                who has weighted stones, as 'remembered' by the
 *                may_not_reset lockout variable.
 * Arguments    : n/a
 * Returns      : Value of the may_not_reset variable.
 */
public object
query_reset_lockout()
{
    return may_not_reset;
}

public void
remove_reset_lockout()
{
    may_not_reset = 0;
}

/*
 * Function name: reset_room
 * Description  : Attempts to reset the room. With this particular
 *                room, however, we do not always want it to reset
 *                normally. All the variables that may require
 *                resetting are in reset_quest, so call that function
 *                if we can reset. We will reset only if one of the
 *                following is true:
 *                1: Object pointer to the last player to weight
 *                   a trigger stone (may_not_reset variable) is
 *                   no longer valid.
 *                2: may_not_reset has no environment.
 *                3: may_not_reset has been linkdead longer than a
 *                   15 minutes.
 *                4: may_not_reset has left the domain Calia.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_room()
{
    if (may_not_reset &&
        objectp(may_not_reset) &&
        environment(may_not_reset) &&
        (time() - may_not_reset->query_linkdead() < (TIMEOUT / 2)) &&
        domain(environment(may_not_reset)) == domain(TO))
    {
        return;
    }
    else
    {
      /* Reset this room's quest variables. */
        reset_quest();
      /* Reset the skywalk's quest variables. */
        (RUIN + "skywalk")->reset_quest();
    }
}

public string
extra_fallen()
{
    string str;
    int i,
        j,
        temp_index;
    string *numbers;

    str = "";

    if (fallen && m_sizeof(fallen))
    {
        str = "\n";
        str += "Also, a dark opening rests where a stone block " +
            "once was in the ";
        numbers = ({});
        for (i = 0; i < m_sizeof(fallen); i++)
        {
            temp_index = m_indexes(fallen)[i];
            for(j = 0; j < sizeof(fallen[temp_index]); j++)
                numbers += ({LANG_WORD(fallen[temp_index][j] + 1) +
                    " stone of the " +
                    LANG_WORD(temp_index + 1) + " wedge"});
        }
        str += COMPOSITE_WORDS(numbers) + ".\n";
    }
    return str;
}

public string
extra_marked()
{
    string str,
           *numbers;
    int i,
        j,
        temp_index,
        temp_index2;
    object *arr;

    str = "";
    numbers = ({});

    if (marked && m_sizeof(marked))
    {
        str = "\n";
        for (i = 0; i < m_sizeof(marked); i++)
        {
            temp_index = m_indexes(marked)[i];
            temp_index2 = m_indexes(marked[temp_index])[0];
            arr = marked[temp_index][temp_index2];
            str += "Upon the " +
                LANG_WORD(temp_index2 + 1) +
                " stone of the " +
                LANG_WORD(temp_index + 1) + " wedge " +
                (sizeof(arr) > 1 ? "lie" : "lies") + " " +
                COMPOSITE_DEAD(arr) + ".\n";
        }
    }
    return str;
}

public string
extra_shadows()
{
    string str;
    mixed shadows;
    int i;

    string *numbers;

    str = "\n";

    shadows = SWORD_BRAIN->query_marked();

    if (!sizeof(shadows))
        return "";

    if (sizeof(shadows) == 1)
        str = "A lone shadow falls upon the floor, ";
    else if (sizeof(shadows) == 2)
        str = "A pair of shadows fall upon the floor, ";
    else if (sizeof(shadows))
        str = "A number of shadows fall upon the floor, ";

    str += "darkening ";

    numbers = ({});
    for (i = 0; i < sizeof(shadows); i++)
    {
        numbers += ({"the " + LANG_WORD(shadows[i][1] + 1) +
            " stone of the " + LANG_WORD(shadows[i][0] + 1) + " wedge"});
    }

    str += COMPOSITE_WORDS(numbers);

    return str + ".\n";
}

public string
extra_floor()
{
    return extra_shadows() + extra_fallen() + extra_marked();
}

public void
create_room()
{
    set_short("in a wide chamber beneath " + CASTLE_NAME);
    set_long("You find yourself in a massive chamber " +
        "deep beneath "+ CASTLE_NAME + ". Apparently precisely " +
        "circular, and at least fifty feet across, it's "+
        "almost like being outside. The walls are seemingly " +
        "cut from solid stone, and vault upwards smoothly, " +
        "making the room appear like an inverted bowl. At the " +
        "top of the dome, where you'd expect to find a ceiling, " +
        "you find an expanse of stained " +
        "glass. " +
        "In the center of the floor stands a low stone " +
        "pedestal of some sort. You also take note " +
        "of a number of exits from the chamber, tunnels cut " +
        "into the stone walls. Most seem to be straight " +
        "passages but you think you can see stairs in the east " +
        "passage.\n\n");

    add_item(({"ceiling", "roof"}),
        "The roof is dominated by an incredible sight, it appears " +
        "to be made completely of some kind of glass, like a " +
        "window!\n");
    add_item(({"walls"}),
        "The walls of the chamber surround you in a smooth, " +
        "circular curve, apparently cut from the surrounding " +
        "stone. As they wrap around the room, they also curve " +
        "gracefully upwards towards a massive 'window', for " +
        "lack of a better word, at the top of the ceiling.\n");
    add_item(({"window", "glass"}),
        "The window depicts one of the strange creatures known " +
        "as chimeras. Strangely enough, the creature seems to " +
        "be overlaid upon the image of a knight or warrior of " +
        "some sort. Above the window, the light seems to have " +
        "rippling effect, and you realize the trickling sound " +
        "is originating from up there. You come to the " +
        "conclusion that what serves as a ceiling here is " +
        "actually the floor of a fountain or pool up above.\n");
    add_item(({"floor"}),
        "Upon the floor, straight lines are cut into the stone, " +
        "dividing it into twelve wedges, running from the walls " +
        "to meet beneath the pedestal in the center of the " +
        "room. " +
        "@@extra_floor@@\n");
    add_item(({"wedges"}),
        "The wedges in the floor all appear to be of the same " +
        "dimensions, and made entirely out of three sections of " +
        "stone. The center-most piece of each wedge being " +
        "somewhat shorter in length than the end pieces, and " +
        "of a slightly darker stone. " +
        "@@extra_floor@@\n");
    add_item(({"shadow", "shadows"}),
        "Here and there, small shadows fall into corners of the " +
        "room where the light from above does not reach.\n" +
        "@@extra_shadows@@");

    INSIDE;

    add_exit(RUIN + "catacomb_4", "north");
    add_exit(RUIN + "catacomb_3", "east");
    add_exit(RUIN + "catacomb_6", "south");
    add_exit(RUIN + "catacomb_2", "west");

    reset_room();
}

public void
init()
{
    ::init();
    add_action(do_drop, "drop");
    add_action(do_drop, "put");
    add_action(do_drop, "place");
}

/*
 * Function name: do_drop
 * Description  : Handles what to do when a player tries to drop items
 *                on trigger stones in the floor.
 * Arguments    : str - String argument passed with the command verb
 *                      by the player.
 * Returns      : 0 - Keep threading.
 *                1 - Stop threading.
 */
public int
do_drop(string str)
{
    object what;
    string stone,
           wedge,
           verb,
           tempweigh,
           *tempstr;
    int i,
        stone_index,
        wedge_index,
        temp;

  /* Get the current keystones from the sword brain. The keystones */
  /* are the stones that will release the sword from the */
  /* pedestal. */
    mapping keystones = SWORD_BRAIN->query_keystones();

    verb = query_verb();

    notify_fail(capitalize(verb) + " what where?\n");

  /* If no argument was passed, keep threading. */
    if (!str || !strlen(str))
        return 0;

  /* If we can't get a syntax match for dropping objects on a */
  /* trigger stone, keep threading. */
    if (!parse_command(str, TP,
        "%o 'on' [the] %w 'stone' / 'block' / 'flagstone' " +
        "'of' / 'on' / 'in' [the] %w 'wedge'", what, stone, wedge))
        return 0;

  /* Is it possible to drop what the player's trying to drop? */
    if (what->query_prop(OBJ_M_NO_DROP))
    {
        write("You cannot " + verb + " the " + what->short() + ".\n");
        return 1;
    }

  /* You can't drop what you can't see. */
    if (!CAN_SEE_IN_ROOM(TP) || !CAN_SEE(TP, what))
    {
        write("You see no such thing to " + verb + ".\n");
        return 1;
    }

  /* Set the stone index if the player tried dropping something */
  /* on a valid stone. */
    for (i = 0; i < sizeof(stone_descs); i++)
    {
        if (member_array(stone, stone_descs[i]) >= 0)
        {
            stone_index = i;
            temp = 1;
            break;
        }
    }

  /* Fail if the player specified an invalid stone. */
    if (!temp)
    {
        write(capitalize(verb) + " the " + what->short() + " on which " +
            "stone of which wedge?\n");
        return 1;
    }

    temp = 0;

  /* Get the wedge index for the wedge the player tried to drop */
  /* something on. */
    for (i = 0; i < sizeof(wedge_descs); i++)
    {
        if (member_array(wedge, wedge_descs[i]) >= 0)
        {
            wedge_index = i;
            temp = 1;
            break;
        }
    }

  /* Fail if the player specified an invalid wedge. */
    if (!temp)
    {
        write(capitalize(verb) + " the " + what->short() + " on the " +
            stone + " stone of which wedge?\n");
        return 1;
    }

  /* Ok, now we should have something to drop, and which stone on which */
  /* wedge to drop it on. */

  /* You can't drop something on a stone which no longer */
  /* exists. */
    if (fallen[wedge_index] &&
        member_array(stone_index, fallen[wedge_index]) >= 0)
    {
        write("The " + stone + " stone of the " + wedge + " wedge " +
            "has fallen away, there's nothing there to put the " +
            what->short() + " on.\n");
        return 1;
    }

  /* Make sure the object can be moved. Another fail message if it */
  /* couldn't be. */
    if (what->move(TO))
    {
        write("You don't seem to be able to move the " +
            what->short() + ", for some reason.\n");
        return 1;
    }

    write("You " + verb + " the " + what->short() + " on the " +
        stone + " stone of the " + wedge + " wedge.\n");
    say(QCTNAME(TP) + " " + verb + "s " + LANG_ADDART(what->short()) +
        " on the " + stone + " stone of the " + wedge + " wedge.\n");

    if (!(TP->query_prop(LIVE_I_SWORD_QUEST) & SWQ_WEIGHT_STONE))
        TP->add_prop(LIVE_I_SWORD_QUEST,
            TP->query_prop(LIVE_I_SWORD_QUEST) | SWQ_WEIGHT_STONE);

  /* Set the 'may not reset' variable, and start the alarm to */
  /* remove it again. This gives the player some extra time */
  /* beyond a normal room reset, so they'll have at least a */
  /* half hour after the last time they weighted a stone to */
  /* weight the rest without the room resetting. */
    may_not_reset = TP;
    if (get_alarm(may_not_reset_id))
        remove_alarm(may_not_reset_id);
    may_not_reset_id = set_alarm(itof(TIMEOUT), 0.0, remove_reset_lockout);

  /* If the specified stone and wedge combination isn't a keystone */
  /* (as obtained from the sword brain), remove the stone from */
  /* the room, and slice up the player as punishment. */
    if (member_array(wedge_index, m_indexes(keystones)) < 0 ||
        keystones[wedge_index] != stone_index)
    {
        say("Suddenly, the stone falls away from beneath " + QTNAME(TP) +
            "! You hear a thin whistle, like a blade slicing through " +
            "the air, and " + TP->query_pronoun() + " screams in pain!\n");
        write("Suddenly, the stone falls away from beneath you! You " +
            "hear a thin whistle, like a blade slicing through the " +
            "air, and suddenly feel an intense flash of pain as " +
            "something sharp slashes into you!\n");
        TP->hit_me(BLADE_PEN, MAGIC_DT, TO, -1);
        TP->add_prop(LIVE_I_SWORD_QUEST,
            TP->query_prop(LIVE_I_SWORD_QUEST) | SWQ_FAILED);
        if (TP->query_hp() <= 0)
        {
            TP->do_die(TO);
            log_file("eldoral_deaths", ctime(time()) + ": " +
                TP->query_name() + " killed by blades in catacomb_hub");
        }

        clone_object(WEP + "wheel_blade")->move(TP, 1);

      /* Now add the stone to the fallen mapping. This effectively */
      /* removes this trigger stone from the room. */
        if (fallen[wedge_index])
            fallen[wedge_index] += ({stone_index});
        else
            fallen[wedge_index] = ({stone_index});
        what->remove_object();
        return 1;
    }

  /* Ok, the specified stone was a keystone. Add this object to */
  /* the marked mapping as resting on it. Note that this produces */
  /* a mapping like: */
  /* ([ 0 : ([ 1 : ({ object1, object2 }) ]) ]) */
  /* when object1 and object2 are dropped on the second stone of */
  /* the first wedge. */
    if (marked[wedge_index] &&
        marked[wedge_index][stone_index])
        marked[wedge_index][stone_index] += ({what});
    else
        marked[wedge_index] = ([stone_index: ({what})]);

  /* Since only one trigger stone exists on each wedge, in */
  /* the mapping that tracks the total weight of objects */
  /* dropped on the stones, we need only index off the */
  /* wedge index (from 0 to 11). */
    if (allweigh[wedge_index])
        allweigh[wedge_index] += what->query_prop(OBJ_I_WEIGHT);
    else
        allweigh[wedge_index] = what->query_prop(OBJ_I_WEIGHT);

  /* Tell the player if they've piled enough weight on this */
  /* trigger stone. */
    if (allweigh[wedge_index] > WEIGHT_TO_RELEASE)
        tell_room(TO, "You hear a faint 'click' come from somewhere " +
            "beneath the floor.\n");

  /* Once you drop something, you can't get it back. */
    what->add_prop(OBJ_M_NO_GET, "It seems to have almost become " +
        "attached to the stone it's sitting on, somehow.\n");

  /* If the allweigh mapping has 4 indexes, start checking to */
  /* see if we should release the sword from the pedestal. We */
  /* do this quickly by filtering the m_values against the */
  /* weight to release. */
    if (m_sizeof(allweigh) >= 4 &&
        !sizeof(filter(m_values(allweigh), &operator(>)(WEIGHT_TO_RELEASE))))
    {
        tempstr = ({});
        for (i = 0; i < m_sizeof(allweigh); i++)
        {
            tempweigh = m_indexes(allweigh)[i];
            tempstr += ({"the " +
                LANG_WORD(m_indexes(marked[tempweigh])[0] + 1) +
                " stone of the " + LANG_WORD(tempweigh + 1) + " wedge"});
        }
        tell_room(TO, "Suddenly, " + COMPOSITE_WORDS(tempstr) + " " +
            "sink slowly into the floor with a grinding sound.\n");
        pedestal->release_sword();
        for (i = 0; i < m_sizeof(marked); i++)
        {
            tempweigh = m_indexes(allweigh)[i];
            m_values(marked[tempweigh])[0]->remove_object();
            if (fallen[tempweigh])
                fallen[tempweigh] += m_indexes(marked[tempweigh]);
            else
                fallen[tempweigh] = m_indexes(marked[tempweigh]);
        }
        marked = ([]);
        return 1;
    }
    return 1;
}

public mapping
query_marked()
{
    return marked + ([]);
}

