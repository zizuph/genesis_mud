/*
 *  /d/Emerald/common/guild/aod/obj/spike.c
 *
 *  These trophy spikes have been placed around the Army of Darkness
 *  guild hall. Guild members can mount a head on them, and they will
 *  save over reboots.
 * 
 *  Copyright (c) July 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";

#include "../defs.h"
#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <time.h>

/* Global Variables */
public int         Occupied    = 0;
public string      Spike_Id    = "";
public string      Gender      = "";
public string      Race        = "";
public string      NonMet      = "";
public string      Met         = "";
public string      Collector   = "";
public int         Spike_Date  = 0;
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
public void        create_object();
public string      spike_short();
public string      spike_long();
public string      short_func();
public string      pshort_func();
public string      long_func();
public string      spike_plaque();
public int         remove_trophy(string arg);
public void        init();


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
    Collector  = SPIKE_INFO("collector");
    Spike_Date = SPIKE_INFO(     "date");

    met = lower_case(Met);

    add_item( ({ "head", "blood-smeared head", "trophy", "skull",
                 met, NonMet, "head of " + met, "head of " + NonMet,
                 "blood-smeared head of " + met,
                 "blood-smeared head of " + NonMet,
                 met + " head", NonMet + " head",
                 Race + " head" }), long_func() + "\n");
    add_item( ({ "plaque", "metal plaque", "small metal plaque" }),
                 spike_plaque);
    add_cmd_item( ({ "plaque", "metal plaque", "small metal plaque" }),
                  ({ "read" }), spike_plaque);
} /* update_spike */


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    setuid();
    seteuid(getuid());

    update_spike();

    set_name("spike");
    add_name( ({ "spike", "_aod_trophy_spike" }) );
    set_adj( ({ "trophy" }) );

    set_short(spike_short);
    set_long(spike_long);

    add_item( ({ "column", "stone column" }),
        "The stone of the column is jet black, and crackles with magical"
      + " energies. Whatever is placed upon the spike will be sealed"
      + " by Darkling magic.\n");

    add_prop(OBJ_M_NO_GET,
        "The spike is embedded in the column, which is embedded in the"
      + " floor. Neither are going anywhere.\n");
    add_prop(OBJ_I_WEIGHT, 12000);
    add_prop(OBJ_I_VOLUME, 5000);
} /* create_object */


/* Function name:        spike_short
 * Description  :        returns the short description of the spike,
 *                       which varies based on whether or not there is
 *                       a head fixed upon it.
 * Returns      :        the short description 
 */
public string
spike_short()
{
    string stxt;

    stxt = "trophy spike";

    if (Occupied)
    {
        stxt += " bearing the disembodied " + short_func();
    }

    return stxt;
} /* spike_short */


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

    ltxt = "A square stone column rises from the ground here. From the"
      + " top of the column, a long black iron spike juts into the"
      + " air. ";

    if (Occupied)
    {
        ltxt += long_func();
    }
    else
    {
        ltxt += "Upon the spike, you may <mount> any head that you have"
          + " collected which you feel would make a worthy trophy for"
          + " the guild.";
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
    object pob;
    string extra = " Beneath the spike, you notice a small metal"
                 + " plaque.";

    if (!Occupied)
    {
        return "";
    }

    pob = vbfc_caller();
    if (!pob || !query_interactive(pob) || pob == this_object())
        pob = this_player();
    if (pob->query_real_name() == lower_case(Met))
        return "Upon the spike, someone has mounted your own blood-"
          + "smeared head for all to see!" + extra;
    if (pob->query_met(Met))
        return "Upon the spike, someone has mounted the blood-smeared"
          + " head of " + capitalize(Met) + " for all to see." + extra;
    else
        return "Upon the spike, someone has mounted the blood-smeared"
          + " head of " + LANG_ADDART(NonMet) + " for all to see." + extra;
} /* long_func */


/*
 * Function name:        spike_plaque
 * Description  :        allow the player to examine the spike to see
 *                       who donated the trophy
 * Returns      :        string -- the description
 */
public string
spike_plaque()
{
    string  date_txt;

    if (!Occupied)
    {
        return "The plaque beneath the spike is bare of any marking.\n";
    }

    date_txt = TIME2FORMAT(Spike_Date, "mmm d yyyy");

    return sprintf("%|80s",  ".--------------------------.\n")
         + sprintf("%|80s", sprintf("%2s %|26s %2s", "|",
                                    "-**- " + Met + " -**-", "|\n"))
         + sprintf("%|80s", "|                            |\n")
         + sprintf("%|80s", "|         Mounted by         |\n")
         + sprintf("%|80s", "|                            |\n")
         + sprintf("%|80s", sprintf("%2s %|26s %2s", "|",
                                    capitalize(Collector), "|\n"))
         + sprintf("%|80s", "|             on             |\n")
         + sprintf("%|80s", sprintf("%2s %|26s %2s", "|",
                                    date_txt, "|\n"))
         + sprintf("%|80s", " `--------------------------'\n");
} /* spike_plaque */


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
      + "] 'from' [the] [trophy] 'spike'"))
    {
        return 0;
    }

    /* determine if the trophy spike has a head upon it */
    if (!Occupied)
    {
        notify_fail("There is nothing on the spike to remove!\n");
        return 0;
    }

    /* only allow the person who mounted it to remove. Possibly also
       allow Council Members to do so. */
    if (Collector != this_player()->query_real_name())
    {
        if (!AOD_GENERAL(this_player()))
        {
            if (environment(this_object())->id("_sph_chamber") &&
               (AOD_CORPORAL(this_player())))
            {
                write("Being the Black Corporal, you know it is well within"
                  + " your authority to do with the trophy on this"
                  + " spike as you see fit!\n");
            }
            else
            {
                write("Purple lightning arcs painfully across your hands as"
                  + " you grab the head! It seems you are not authorized to"
                  + " remove this trophy.\n");

                return 1;
            }
        }
        else
        {
            write("Being the Headhunter General, you know it is well within"
              + " your authority to do with the guild trophies as you see"
              + " fit!\n");
        }
    }

    write("You remove the " + short_func() + " from the trophy"
      + " spike.\n");
    tell_room(environment(this_player()),
        QCTNAME(this_player()) + " removes the "
      + short_func() + " from the trophy spike.\n", this_player());

    skull = clone_object(AOD_OBJ_DIR + "head");

    skull->set_skull_id(Spike_Id);
    skull->set_skull_race(Race);
    skull->set_skull_nonmet(NonMet);
    skull->set_skull_met(Met);

    TROPHY_MASTER->set_info(Spike_Id, "occupied", 0);
    Occupied = 0;
    update_spike();

    write_file(AOD_LOG_DIR + "spike_log",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " (" + ctime(time())[11..18]
      + ") " + capitalize(this_player()->query_name()) + " -- "
      + "removed -- a head (" + Spike_Id + ")\n");

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
 * Function name:        mount_trophy
 * Description  :        give a fail message if the player tries to
 *                       mount something but doesn't possess a head.
 * Arguments    :        string arg -- what was typed following the verb
 * Returns      :        0 -- failure (always)
 */
public int
mount_trophy(string arg)
{
    object *heads,
            head;

    setuid();
    seteuid(getuid());

    if (!strlen(arg))
    {
        notify_fail("Mount what?\n");
        return 0;
    }

    heads = PARSE_THIS(arg, "[a] [the] %i 'on' / 'upon' [the] [trophy]"
          + " 'spike'");
    switch(sizeof(heads))
    {
    case 0:
        notify_fail("Mount what upon what?\n");
        return 0;
    case 1:
        head = heads[0];
        break;
    default:
        notify_fail("Please try to mount only a single item at"
          + " a time.\n");
        return 0;
    }

    if (!head->id("_aod_head"))
    {
        notify_fail("These trophy spikes are for decapitated heads"
          + " only!\n");
    }

    return 0;
} /* mount_trophy */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(remove_trophy, "remove");
    add_action(remove_trophy, "take");
    add_action(remove_trophy, "get");
    add_action(mount_trophy, "mount");
} /* init */