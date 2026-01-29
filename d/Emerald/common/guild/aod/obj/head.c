/*
 *  /d/Emerald/common/guild/aod/obj/head.c
 *
 *  The file for heads that Ogres in the Army of Darkness have ripped
 *  off the corpses of their victims.
 * 
 *  Copyright (c) May 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types 

inherit "/std/leftover";

#include "../defs.h"
#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <time.h>


/* Global Variables */
public string      Gender      = "";
public string      Race        = "";
public string      NonMet      = "";
public string      Met         = "";
public string      State_Desc  = "head of ";
public string      Pstate_Desc = "heads of ";
public string      Spike_Id    = "";
public int         Playerskull = 0;

public string      query_skull_gender()     { return Gender; }
public string      query_skull_race()         { return Race; }
public void        set_skull_nonmet(string s)  { NonMet = s; }
public string      query_skull_nonmet()     { return NonMet; }
public void        set_skull_met(string s)        { Met = s; }
public string      query_skull_met()           { return Met; }
public void        set_playerskull(int i) { Playerskull = i; }
public int         query_playerskull() { return Playerskull; }    

/* Definitions */
#define            SPIKE_INFO(x,y) (TROPHY_MASTER->set_info(Spike_Id, x, y))


/* Prototypes */
public void        create_leftover();
public string      short_func();
public string      pshort_func();
public string      long_func();
public int         mount_trophy(string arg);
public int         tie_trophy(string arg);
public void        init();
public string      query_recover();
public int         command_eat();
public int         devour_head(string arg);


/*
 * Function name:        set_skull_id
 * Description  :        because these are heaps, we need to give
 *                       them a unique id. Lets just use the clone
 *                       number from the former corpse object
 * Arguments    :        string arg - the id number
 */
public void
set_skull_id(string arg)
{
    add_prop(HEAP_S_UNIQUE_ID, "aod_head_" + arg);
} /* set_skull_id */


/*
 * Function name:        set_skull_gender
 * Description  :        assign the gender to the skull
 */
public void
set_skull_gender(string s)
{
    Gender = s;
    add_adj(s);
} /* set_skull_gender */


/*
 * Function name:        set_skull_race
 * Description  :        assign the race to the skull
 */
public void
set_skull_race(string s)
{
    Race = s;
    add_adj(s);
} /* set_skull_race */


/*
 * Function name:        create_leftover
 * Description  :        set up the leftover
 */
public void
create_leftover()
{
    set_name("head");
    add_name( ({ "leftover", "aod_head", "skull",
                 "_aod_head" }) );
    set_adj( ({ "bloody", "blood-smeared", "blood", "smeared" }) );
    set_short(short_func);
    set_pshort(pshort_func);
    set_long(long_func);
 
    set_decay_time(9999); /* lets not have them decay too easily */
    set_amount(1); /* perhaps up this later */

    add_prop(OBJ_I_WEIGHT, 5000); /* roughly 10 lbs. */
    add_prop(OBJ_I_VOLUME, 3000); /* 3 liters */

    setuid();
    seteuid(getuid());
} /* create_leftover */


/*
 * Function name: short_func
 * Description  : Returns the short description of this object, based on
 *                recognition of the head.
 * Returns      : string - the short description.
 */
public string
short_func()
{
    object pob;

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
 * Description  : Returns the plural short description of this object, based on
 *                recognition of the head.
 * Returns      : string - the plural short description.
 */
public string
pshort_func()
{
    object pob;

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
 * Description  : Returns the long description of this object, based on
 *                recognition of the head.
 * Returns      : string - the long description.
 */
public string
long_func()
{
    object  pob;
    string  extra = "\n";

    pob = vbfc_caller();

    if (!pob || !query_interactive(pob) || pob == this_object())
    {
        pob = this_player();
    }

    if (pob->query_guild_name_occ() == GUILD_NAME)
    {
        extra = " You may <collect> this head in your sack to keep it"
          + " safe until you have a chance to return to the Repository."
          + " However, once you do this, you will not be able to take it"
          + " back out of the sack again. If you'd like, you could also"
          + " try to <ogretie> it to your belt or <mount> it on a spike"
          + " in the Army Guildhall.\n";
    }   

    if (pob->query_real_name() == lower_case(Met))
    {
        return "This is your own blood-smeared head!" + extra;
    }

    if (pob->query_met(Met))
    {
        return "This is the blood-smeared head of " 
             + capitalize(Met) + "." + extra;
    }

    return "This is the blood-smeared head of " + NonMet + "." + extra;
} /* long_func */


/*
 * Function name:        mount_trophy
 * Description  :        if a trophy spike is present, allow the player 
 *                       to mount the head as a trophy
 * Arguments    :        string arg -- what was typed following the verb
 * Returns      :        int 1 -- success, 0 -- failure
 */
public int
mount_trophy(string arg)
{
    object *heads,
            head,
            spike;

    setuid();
    seteuid(getuid());

    if (!strlen(arg))
    {
        notify_fail("Mount what?\n");
        return 0;
    }

    notify_fail("Mount what upon what?\n");
    heads = PARSE_THIS(arg, "[a] [the] %i 'on' / 'upon' [the] [trophy]"
          + " 'spike'");
    switch(sizeof(heads))
    {
    case 0:
        return 0;
    case 1:
        head = heads[0];
        break;
    default:
        notify_fail("Please try to mount only a single head at"
          + " a time.\n");
        return 0;
    }

    /* determine if there is a trophy spike present */
    if (!objectp(spike = present("_aod_trophy_spike",
        environment(this_player()))))
    {
        notify_fail("There is nothing present upon which you could"
          + " mount the " + head->short() + ".\n");
        return 0;
    }

    if (!head->id("_aod_head"))
    {
        notify_fail("These trophy spikes are for decapitated heads"
          + " only!\n");
        return 0;
    }

    /* determine if the trophy spike already has a head upon it */
    if (spike->query_occupied())
    {
        notify_fail("There is already a trophy mounted upon this"
          + " spike!\n");
        return 0;
    }

    write("You press the " + head->short_func() + " down onto the"
      + " trophy spike, and the air crackles with magical energy!\n");
    tell_room(environment(this_player()),
        QCTNAME(this_player()) + " mounts the "
      + head->short_func() + " on the trophy spike. The air crackles"
      + " with magical energy!\n", this_player());

    Spike_Id = spike->query_spike_id();

    SPIKE_INFO("race", Race);
    SPIKE_INFO("nonmet", NonMet);
    SPIKE_INFO("met", Met);
    SPIKE_INFO("collector", this_player()->query_real_name());
    SPIKE_INFO("date", time());
    SPIKE_INFO("occupied", 1);

    spike->update_spike();

    write_file(AOD_LOG_DIR + "spike_log",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " (" + ctime(time())[11..18]
      + ") " + capitalize(this_player()->query_name()) + " -- "
      + "mounted -- a head (" + Spike_Id + ")\n");

    head->remove_object();

    return 1;
} /* mount_trophy */


/*
 * Function name:        tie_trophy
 * Description  :        if a trophy belt is present, allow the player 
 *                       to tie the head as a trophy
 * Arguments    :        string arg -- what was typed following the verb
 * Returns      :        int 1 -- success, 0 -- failure
 */
public int
tie_trophy(string arg)
{
    object *heads,
            head,
            spike;

    setuid();
    seteuid(getuid());

    if (!strlen(arg))
    {
        notify_fail("Tie what?\n");
        return 0;
    }

    notify_fail("Tie what to what?\n");
    heads = PARSE_THIS(arg, "[a] [the] %i 'to' [the]"
          + " [trophy] 'belt'");
    switch(sizeof(heads))
    {
    case 0:
        return 0;
    case 1:
        head = heads[0];
        break;
    default:
        notify_fail("Please try to tie only a single head at"
          + " a time.\n");
        return 0;
    }

    /* determine if there is a trophy spike present */
    if (!objectp(spike = present(AOD_RACE_EMBLEM_ID,
        this_player())))
    {
        notify_fail("There is nothing present to which you could"
          + " tie the " + head->short() + ".\n");
        return 0;
    }

    if (!spike->query_worn())
    {
        notify_fail("You must wear the belt first!\n");
        return 0;
    }

    /* determine if the trophy spike already has a head upon it */
    if (spike->query_occupied())
    {
        notify_fail("There is already a trophy tied to your"
          + " belt. You will need to <untie> the other one first.\n");
        return 0;
    }

    if (!heads[0]->id("_aod_head"))
    {
        notify_fail("You aren't able to tie the " + heads[0]->short()
          + " to the trophy belt.\n");
    }

    write("You tie the " + head->short_func() + " onto your trophy"
      + " belt, hanging it there for all to see!\n");
    tell_room(environment(this_player()),
        QCTNAME(this_player()) + " ties the "
      + head->short_func() + " onto " + this_player()->query_possessive()
      + " trophy belt, hanging it there for all to see!\n", this_player());

    Spike_Id = spike->query_spike_id();

    SPIKE_INFO("race", Race);
    SPIKE_INFO("nonmet", NonMet);
    SPIKE_INFO("met", Met);
    SPIKE_INFO("occupied", 1);

    spike->update_spike();

    write_file(AOD_LOG_DIR + "belt_log",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " (" + ctime(time())[11..18]
      + ") " + capitalize(this_player()->query_name()) + " -- "
      + "tied -- a head (" + Met + ":" + Spike_Id + ")\n");

    head->remove_object();

    return 1;
} /* tie_trophy */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(mount_trophy, "mount");
    add_action(tie_trophy, "tie");
    add_action(tie_trophy, "ogretie");
    add_action(devour_head, "devour");
} /* init */


/*
 * Function name:        query_recover
 * Description  :        We don't want these to recover. Colleect 'em or
 *                       lose 'em!
 * Returns      :        0 - no recovery
 */
public string
query_recover()
{
    return 0;
} /* query_recover */


/*
 * Function name:        command_eat
 * Description  :        mask the parent so we don't accidentally
 *                       eat heads.
 * Returns      :        string - an error message upon failure.
 *                       int 1 - when successfully eaten.
 */
public mixed
command_eat()
{
    if (!IS_OGRE(this_player()))
    {
        return "Are you insane? Eat someone's head? You're not an"
          + " Ogre, you know!\n";
    }

    return "You gaze hungrily down at " + short()
      + ". Eat from the Harvest?? Oh ... the Bosses won't"
      + " like that! Still, you could probably ignore orders and"
      + " <devour> it if you really wanted to.\n";
} /* command_eat */


/*
 * Function name:        devour_head
 * Description  :        Allow ogres to eat the head. Its their loss.
 * Arguments    :        string arg - what was typed following the verb
 * Returns      :        1 - success, 0 - failure
 */
public int
devour_head(string arg)
{
    object  head;

    if (!IS_OGRE(this_player()))
    {
        return 0; /* Give 'em the 'What?' */
    }

    if (!strlen(arg))
    {
        notify_fail("What do you want to devour, hungry Ogre?\n");
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] %o", head))
    {
        return 0; /* pass it on */
    }

    if (head != this_object())
    {
        notify_fail("Err ... maybe that is edible. Not sure. Just try"
          + " to <eat> it instead, I guess.\n");
        return 0;
    }

    write("You cram " + head->short() + " into your mouth and crunch"
      + " it down like there is no tomorrow. Bits of scalp and"
      + " skull fly all over the place as you devour your treat!\n"); 
    say(QCTNAME(this_player()) + " crams " + head->short() + " into "
      + this_player()->query_possessive() + " mouth and crunches it down"
      + " with ferocious zeal! Bits of scalp and skull fly all"
      + " over the place as the head is devoured.\n");

    this_player()->set_stuffed(5); /* Feed the player! */
    this_object()->remove_object();
    return 1;
} /* devour_head */


