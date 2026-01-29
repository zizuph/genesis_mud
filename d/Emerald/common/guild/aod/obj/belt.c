/*
 *  /d/Emerald/common/guild/aod/obj/belt.c
 *
 *  This belt is the guild item for the Ogre race guild in Emerald.
 *  From it, members can hang a trophy head for all to see. Also, this
 *  being the guild object cloned for the racial portion of the guild,
 *  it inherits the ogre_speech module from the lib dir to control ogre
 *  speech functionality.
 * 
 *  Copyright (c) August 2006, by Cooper Sherry (Gorboth)
 *
 *  The code here is dupilicated in large part from spike.c in this same
 *  dir. I have not bothered to rename many of the variables and functions
 *  which is why the word "spike" is present so frequently.
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/armour";
inherit AOD_LIB_DIR + "ogre_emotes";

#include <composite.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <options.h>
#include <stdproperties.h>
#include <time.h>
#include <wa_types.h>

/* Global Variables */
public int         Occupied    = 0;
public string      Spike_Id    = "";
public string      Gender      = "";
public string      Race        = "";
public string      NonMet      = "";
public string      Met         = "";
public string      State_Desc  = "head of ";
public string      Pstate_Desc = "heads of ";

public int         query_occupied()      { return Occupied; }
public void        set_spike_id(string s)   { Spike_Id = s; }
public string      query_spike_id()      { return Spike_Id; }
public string      query_spike_gender()    { return Gender; }
public string      query_spike_race()        { return Race; }
public void        set_spike_nonmet(string s) { NonMet = s; }
public string      query_spike_nonmet()    { return NonMet; }
public void        set_spike_met(string s)       { Met = s; }
public string      query_spike_met()          { return Met; }

/* Definitions */
#define            SPIKE_INFO(x) (TROPHY_MASTER->get_info(Spike_Id, x))

/* Prototypes */
public void        update_spike();
public void        create_armour();
public string      spike_long();
public string      short_func();
public string      pshort_func();
public string      long_func();
public int         remove_trophy(string arg);
public void        init();
public void        get_lost();
public void        enter_env(object dest, object old);
public string      query_recover();


/*
 * Function name:        update_spike
 * Description  :        restore to the spike saved values that exist
 *                       from the save_file
 */
public void
update_spike()
{
    string  met;

    if (!(Occupied = SPIKE_INFO("occupied")))
    {
        return;
    }

    Gender     = SPIKE_INFO(   "gender");
    Race       = SPIKE_INFO(     "race");
    NonMet     = SPIKE_INFO(   "nonmet");
    Met        = SPIKE_INFO(      "met");

    met = lower_case(Met);

    add_item( ({ "head", "blood-smeared head", "trophy", "skull",
                 met, NonMet, "head of " + met, "head of " + NonMet,
                 "blood-smeared head of " + met,
                 "blood-smeared head of " + NonMet,
                 met + " head", NonMet + " head",
                 Race + " head" }), long_func() + "\n");
} /* update_spike */


/*
 * Function name:        create_armour
 * Description  :        set up the armour
 */
public void
create_armour()
{
    setuid();
    seteuid(getuid());

    update_spike();

    set_name("belt");
    add_name( ({ "gutstring", AOD_RACE_EMBLEM_ID }) );
    set_adj( ({ "trophy" }) );

    set_short("trophy belt");
    set_long(spike_long);

    add_prop(OBJ_M_NO_DROP, "You would never part with it!\n");
    add_prop(OBJ_M_NO_GIVE, "You would never part with it!\n");
    add_prop(OBJ_M_NO_SELL, "The trophy belt is not for sale.\n");
    add_prop(OBJ_M_NO_BUY,  "The trophy belt is not for sale.\n");
    add_prop(OBJ_I_WEIGHT, 15); /* keep these low */
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(AOD_WEAR_PROP, 1);

    set_ac(1);
    set_at(TS_WAIST);
    set_am( ({ 0, 0, 0 }) );
} /* create_armour */


/* Function name:        spike_long
 * Description  :        returns the long description of the spike,
 *                       which varies based on whether or not there is
 *                       a head fixed upon it.
 * Returns      :        the long description 
 */
public string
spike_long()
{
    string ltxt;

    ltxt = "This belt has been crudely fashioned from the dried and"
      + " twisted gutstrings of a horse. ";

    if (Occupied)
    {
        ltxt += long_func();
    }
    else
    {
        ltxt += "From it, you may <ogretie> any head that you have"
          + " collected which you feel would make a worthy trophy for"
          + " all to see upon you.";
    }

    return ltxt + "\n";
} /* spike_long */


/*
 * Function name: short_func
 * Description  : Returns the short description of the head, based on
 *                recognition of the head.
 * Returns      : string - the short description.
 */
public string
short_func()
{
    object pob;

    if (!Occupied)
    {
        return "";
    }

    pob = vbfc_caller();
    if (!pob || !query_interactive(pob) || pob == this_object())
        pob = previous_object(-1);
    if (!pob || !query_interactive(pob))
        pob = this_player();
    if (pob && pob->query_real_name() == lower_case(Met))
        return State_Desc + "yourself";
    else if (pob && pob->query_met(Met))
        return State_Desc + capitalize(Met);
    else
        return State_Desc + LANG_ADDART(NonMet);
} /* short_func */


/*
 * Function name: pshort_func
 * Description  : Returns the plural short description of the head, based on
 *                recognition of the head.
 * Returns      : string - the plural short description.
 */
public string
pshort_func()
{
    object pob;

    if (!Occupied)
    {
        return "";
    }

    pob = vbfc_caller();
    if (!pob || !query_interactive(pob) || pob == this_object())
        pob = previous_object(-1);
    if (!pob || !query_interactive(pob))
        pob = this_player();
    if (pob && pob->query_real_name() == lower_case(Met))
        return Pstate_Desc + "yourself";
    else if (pob && pob->query_met(Met))
        return Pstate_Desc + capitalize(Met);
    else
        return Pstate_Desc + LANG_PWORD(NonMet);
} /* pshort_func */


/*
 * Function name: long_func
 * Description  : Returns the long description of the head, based on
 *                recognition of the head.
 * Returns      : string - the long description.
 */
public string
long_func()
{
    object  pob;
    string  extra = " You may <ogreuntie> this head from the belt if you"
      + " wish to wear a different trophy instead.";

    if (!Occupied)
    {
        return "";
    }

    pob = vbfc_caller();
    if (!pob || !query_interactive(pob) || pob == this_object())
        pob = this_player();
    if (pob->query_real_name() == lower_case(Met))
        return "Hanging from your belt for all to see is your own blood-"
          + "smeared head! Are you insane?" + extra;
    if (pob->query_met(Met))
        return "Hanging from your belt for all to see is the blood-smeared"
          + " head of " + capitalize(Met) + "." + extra;
    else
        return "Hanging from your belt for all to see is the blood-smeared"
          + " head of " + LANG_ADDART(NonMet) + "." + extra;
} /* long_func */


/*
 * Function name:        remove_trophy
 * Description  :        allow certain people to remove the trophies
 *                       from the spikes
 * Arguments    :        string arg -- what was typed after the verb
 * Returns      :        1 -- success, 0 -- failure
 */
public int
remove_trophy(string arg)
{
    object  skull;

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    notify_fail(capitalize(query_verb()) + " what from where?\n");
    if (!parse_command(arg, ({}),
        "[the] [a] [" + Race + "] 'head' / 'skull' [of] [" + Met
      + "] 'from' [the] [trophy] 'belt'"))
    {
        return 0;
    }

    /* determine if the trophy spike has a head upon it */
    if (!Occupied)
    {
        notify_fail("There is nothing hanging from the belt to remove!\n");
        return 0;
    }

    /* only allow the person wearing the belt to remove the trophy. */
    if (this_player() != environment(this_object()))
    {
        write("Do not mess with an Ogre's trophies!\n");
        return 1;
    }

    write("You remove the " + short_func() + " from the trophy"
      + " belt.\n");
    tell_room(environment(this_player()),
        QCTNAME(this_player()) + " removes the "
      + short_func() + " from " + this_player()->query_possessive()
      + " trophy belt.\n", this_player());

    skull = clone_object(AOD_OBJ_DIR + "head");

    skull->set_skull_id(Spike_Id);
    skull->set_skull_race(Race);
    skull->set_skull_nonmet(NonMet);
    skull->set_skull_met(Met);

    TROPHY_MASTER->set_info(Spike_Id, "occupied", 0);
    Occupied = 0;
    update_spike();

    write_file(AOD_LOG_DIR + "belt_log",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " (" + ctime(time())[11..18]
      + ") " + capitalize(this_player()->query_name()) + " -- "
      + "removed -- a head (" + Met + ":" + Spike_Id + ")\n");

    if (!skull->move(this_player()))
    {
        return 1;
    }

    /* move to player failed ... get rid of the skull */
    write("You can't carry any more! You decide to just eat the head"
      + " instead. Mmm ... delicious!\n");
    tell_room(environment(this_player()),
        QCTNAME(this_player()) + " eats " + LANG_THESHORT(skull)
      + "!\n");
    skull->remove_object();

    return 1;
} /* remove_trophy */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(remove_trophy, "untie");
    add_action(remove_trophy, "ogreuntie");
    add_action(say_text, "say");
    add_action(say_text, "'", 2);
    add_action(asay, "a'", 2);
    add_action(asay, "asay");
    add_action(ask, "ask");
    add_action(shout, "shout");
    add_action(whisper, "whisper");
    add_action(rsay, "rsay");

    add_ogre_emotes();
} /* init */


/*
 * Function name:        get_lost
 * Description  :        if the owner is not an Ogre, lets get rid
 *                       of it. Ogres only!
 */
public void
get_lost()
{
    object  witness = environment(this_object());
    string  lost_msg = "The trophy belt disappears in a flash of"
                     + " darkness!\n";

    if (!living(witness))
    {
        tell_room(witness, lost_msg);
    }
    else
    {
        witness->catch_tell(lost_msg);
    }

    remove_object();
} /* get_lost */


/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 */
public void
enter_env(object dest, object old)
{
    string  belt_id;

    ::enter_env(dest, old);

    if (belt_id = dest->query_real_name())
    {
        Spike_Id = belt_id;
        update_spike();
    }

    if (!IS_OGRE(environment(this_object())) &&
        !environment(this_object())->id(AOD_NPC))
    {
        set_alarm(0.1, 0.0, get_lost);
    }
} /* enter_env */


/*
 * Function name:        query_recover
 * Description  :        We don't want these to recover because they are
 *                       added upon login anyway.
 * Returns      :        0 - no recovery
 */
public string
query_recover()
{
    return 0;
} /* query_recover */

/* Override as this doesn't break */
varargs int
got_hit(int hid, int ph, object att, int dt, int dam)
{
    hits++;
}
