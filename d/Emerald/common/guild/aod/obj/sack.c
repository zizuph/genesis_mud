/*
 *  /d/Emerald/common/guild/aod/obj/sack.c
 *
 *  This is the membership object given to all members of the Army of
 *  Darkness. It is the skull collecting sack that can be used to bring
 *  skulls back to the darklings. Its capacity and description improve
 *  with collector status.
 *
 *  Copyright (c) March 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";

#include "../defs.h";
#include <cmdparse.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

/* prototypes */
public void        create_object();
public int         skullset(string arg);
public void        init();
public void        sack_collect(object skull, object player);
public int         sack_deposit(string arg);
public int         query_skulls(string arg);
public int         collect_skull(string arg);
public void        do_tutorial(object player, int ogg = 0);

/* Global Variables */
public int         Tell_Alarm;


public void
add_skull(string skulltype, int amount = 1)
{
    AOD_MASTER->collect_skull(this_player(), "Sack-" + capitalize(skulltype),
        amount);
}


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("_aod_guild_sack");
    add_name("sack");
    add_adj( ({ "large", "bloody", "soaked", "blood-soaked", "blood" }) );

    set_short("large blood-soaked sack");
    set_long("Deep red blood stains have soaked through the dense fabric"
      + " of this, the harvesting sack for the Army of Darkness. Through"
      + " Darkling magic, it is able to hold an infinite number of skulls"
      + " without increasing its size or weight. When in possession of"
      + " it, you may use the following commands:\n\n"
      + "\t<rip head from corpse>\t- take the head of your kill.\n"
      + "\t<collect head>\t\t- place a skull in the sack.\n"
      + "\t<skulls> [repository]\t- list your sack collection or your"
      + " deposits.\n"
      + "\t<deposit skulls>\t- transfer your collection into the"
      + " Repository.\n\n"
      + "To learn about other commands, you'll have to talk to Ogg.\n"
      + "Use <ogghelp> to do so.\n\n"
      + "\t(In case of redundancy problems, <ogrecollect> works too.)\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_WEIGHT,  20);
    add_prop(OBJ_I_VOLUME,  20);

    remove_prop(OBJ_I_VALUE);

    setuid();
    seteuid(getuid());
} /* create_object */


/*
 * Function name:        skullset
 * Description  :        Allow the player to manually set his
 *                       sack count for a particular skull type
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - fail
 */
public int
skullset(string arg)
{
    string *races = ({ "human", "elf", "hobbit", "dwarf", "gnome" });
    int     amount;

    notify_fail("Syntax: <skullset racename amount>\n");

    if (!strlen(arg))
    {
        return 0;
    }

    if (!parse_command(arg, ({}), "%p %d", races, amount))
    {
        return 0;
    }

    AOD_MASTER->collect_skull(this_player(), "Sack-" + capitalize(races[0]),
        amount);

    write(capitalize(races[0]) + " skull count increased to "
      + amount + ".\n");

    return 1;
} /* skullset */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

//  add_action(skullset, "skullset");
    add_action(query_skulls, "skulls");
    add_action(sack_deposit, "deposit");
    add_action(collect_skull, "collect");
    add_action(collect_skull, "ogrecollect");
    add_action(collect_skull, "trophycollect");
} /* init */


/*
 * Function name:        sack_collect
 * Description  :        collect a particular skull type, and write that
 *                       to the player's file.
 * Arguments    :        object skull - the skull to be collected,
 *                       object player - the person collecting it
 */
public void
sack_collect(object skull, object player)
{
    string *races = ({ "elf", "human", "dwarf", "hobbit", "gnome" });

    if (AOD_OGG_MASTER->get_info(player, "Tutorial") !=
        "tutorial4" &&
        AOD_OGG_MASTER->get_info(player, "Tutorial") != "done")
    {
        if (!Tell_Alarm || !sizeof(get_alarm(Tell_Alarm)))
        {
            Tell_Alarm = set_alarm(3.0, 0.0, &do_tutorial(player));
        }
    }

    if (member_array(skull->query_skull_race(), races) == -1)
    {
        AOD_MASTER->collect_skull(player, "Sack-Other");
    }
    else
    {
        AOD_MASTER->collect_skull(player, "Sack-" + capitalize(
            skull->query_skull_race()));
    }

    return;
} /* sack_collect */


/*
 * Function name:        sack_deposit
 * Description  :        deposit the entire contents of the sack to
 *                       the repository.
 * Arguments    :        string arg - what was typed after the verb
 * Return       :        int 1 - success, 0 - failure
 */
public int
sack_deposit(string arg)
{
    string   player = this_player()->query_real_name();
    string  *args   = ({ "human", "elf", "hobbit", "dwarf", "gnome",
                         "total", "other" });
    string   mind;
    int      amount;
    int     *previous_guildcount = allocate(6);
    int     *previous_playercount = allocate(6);
    int      playerrank = AOD_MASTER->compute_title(this_player());
    int      preoffense,
             preadv_offense,
             predefense,
             preadv_defense,
             preelite,
             skulls;

    if (!strlen(arg))
    {
        notify_fail("Deposit what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [my] 'skull' / 'skulls' / 'collection'"))
    {
        notify_fail("What, do you want to deposit your skulls?\n");
        return 0;
    }

    if (!environment(this_player())->id("_aod_repository"))
    {
        write("You can only make deposits at the Repository of"
          + " Skulls!\n");

        return 1;
    }

    if ((amount = AOD_MASTER->query_skull_total(this_player())) == 0)
    {
        write("You approach the rendering vat and are just about"
          + " to haul your sack up the stairs when you realize that"
          + " you haven't collected a single skull! Rather than embarrass"
          + " yourself, you step back, and smile sheepishly.\n");

        return 1;
    }
    else
    {
        /* okay ... so a deposit is actually going to take place.
         * we assign values to the variables to see if the player
         * has achieved any personal or guild milestones.
         */
        previous_guildcount = ({ AOD_MASTER->query_guild_total("human"),
                                 AOD_MASTER->query_guild_total("elf"),
                                 AOD_MASTER->query_guild_total("hobbit"),
                                 AOD_MASTER->query_guild_total("dwarf"),
                                 AOD_MASTER->query_guild_total("gnome"),
                                 AOD_MASTER->query_guild_total("total") });
        previous_playercount = ({
            AOD_MASTER->get_info(this_player(), "Human"),
            AOD_MASTER->get_info(this_player(), "Elf"),
            AOD_MASTER->get_info(this_player(), "Hobbit"),
            AOD_MASTER->get_info(this_player(), "Dwarf"),
            AOD_MASTER->get_info(this_player(), "Gnome"),
            AOD_MASTER->query_skull_total(this_player(), 0) });

        skulls = AOD_MASTER->query_skull_total(this_player(), 0);

        preoffense     = AOD_TRAINING->aod_training_check(
                         SS_WEP_CLUB, skulls);
        preadv_offense = AOD_TRAINING->aod_training_check(
                         SS_AOD_WALLOP, skulls);
        predefense     = AOD_TRAINING->aod_training_check(
                         SS_PARRY, skulls);
        preelite       = AOD_TRAINING->aod_training_check(
                         SS_2H_COMBAT, skulls);

        write("You haul your sack up the stairs to stand over the lip"
          + " of the great rendering vat and give it a good shake."
          + " From its opening ");
    }

    /* additional messages are written at this point from the
     * deposit_skull() function in the master object.
     */
    AOD_MASTER->deposit_skull(this_player(), "Human",
        AOD_MASTER->get_info(this_player(), "Sack-Human"));
    AOD_MASTER->deposit_skull(this_player(), "Elf",
        AOD_MASTER->get_info(this_player(), "Sack-Elf"));
    AOD_MASTER->deposit_skull(this_player(), "Hobbit",
        AOD_MASTER->get_info(this_player(), "Sack-Hobbit"));
    AOD_MASTER->deposit_skull(this_player(), "Dwarf",
        AOD_MASTER->get_info(this_player(), "Sack-Dwarf"));
    AOD_MASTER->deposit_skull(this_player(), "Gnome",
        AOD_MASTER->get_info(this_player(), "Sack-Gnome"));
    AOD_MASTER->deposit_skull(this_player(), "Other",
        AOD_MASTER->get_info(this_player(), "Sack-Other"));

    write("a trickle of blood, and a few extra bits of gore and nastiness"
      + " tumble and fall into the depths of the vat. You jump down just"
      + " as a geyser of steam rushes from atop the vat.\n\n");

    tell_room(environment(this_player()),
        QCTNAME(this_player()) + " climbs up to the lip of the rendering"
      + " vat and empties his sack into its gaping maw. "
      + capitalize(this_player()->query_pronoun()) + " jumps down just"
      + " as a geyser of steam rushes from atop the vat.\n\n",
        this_player());

    tell_room(environment(this_player()),
        "A few minutes pass as the vat broils and churns, separating"
      + " flesh and brain from the deposits and sending only purified"
      + " skulls into the deep recesses of the repository. With a"
      + " shrill hiss, black liquid sprays from the tube at the base of"
      + " the vat to fill a stone bowl which rests directly beneath"
      + " it. ");
    tell_room(environment(this_player()),
        QCTNAME(this_player()) + " quickly grabs the bowl and slurps"
      + " down its contents.\n", this_player());

    write("You quickly grab the bowl and slurp down the mind fluid.\n\n"
      + "You feel the energy of " + LANG_NUM2WORD(amount)
      + ((amount > 1) ? " minds" : " mind") + " flowing into you!\n");

    /* see if the guild leaders should change based on this */
    AOD_MASTER->check_leader_update();
    /* see if the player has achieved any milestones */
    AOD_MASTER->check_milestones(previous_guildcount,
                                 previous_playercount, this_player(),
                                 playerrank, preoffense, preadv_offense,
                                 predefense, preelite);
    /* If this is the first deposit from this Ogre, complete the
     * tutorial and turn him over to Ogg.
     */
    if (AOD_OGG_MASTER->get_info(this_player(), "Tutorial") != "done")
    {
        AOD_OGG_MASTER->set_info(this_player(), "Tutorial", "done");

        if (!AOD_OGG_MASTER->get_info(player, "Bosses"))
        {
            set_alarm(8.0, 0.0, &do_tutorial(this_player(), 1));
        }
    }

    return 1;
} /* sack_deposit */



/*
 * Function name:        query_skulls
 * Description  :        Give the player an at a glance check of their
 *                       sack's contents.
 * Arguments    :        string arg - what the player typed after the verb
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
query_skulls(string arg)
{
    int     num;
    string *races = ({ "human", "elf", "hobbit", "dwarf", "gnome",
                       "total", "other" });

    if (strlen(arg))
    {
        if (!parse_command(arg, ({}),
            "'human' / 'elf' / 'hobbit' / 'dwarf' / 'gnome' / 'other'"))
        {
            if (arg == "repository")
            {
                AOD_MASTER->print_skull_list(this_player(), 0);
                return 1;
            }

            if (arg == "goblin" || arg == "goblins")
            {
                write("You check your sack to make sure no goblin"
                  + " heads are in there. Phew! If you had an Ogre-"
                  + "Mommy, she'd be proud of you.\n");
                return 1;
            }

            notify_fail("Huh?? There are no skulls of that type!\n");
            return 0;
        }

        num = AOD_MASTER->get_info(this_player(), "Sack-"
            + capitalize(arg));

        if (!num)
        {
            write("You haven't collected any " + arg + " skulls.\n");
            return 1;
        }

        if (num > 1)
        {
            write("You have collected " + num + " " + arg + " skulls.\n");
            return 1;
        }

        write("You have only collected one " + arg + " skull.\n");
        return 1;
    }

    AOD_MASTER->print_skull_list(this_player());

    return 1;
} /* query_skulls */


/*
 * Function name:        collect_skull
 * Description  :        allow us to put this skull into the sack,
 *                       therefore collecting it.
 * Arguments    :        string arg - what the player typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
collect_skull(string arg)
{
    object  skull;

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, all_inventory(this_player()),
        "[the] %o", skull))
    {
        notify_fail("What do you want to collect? Maybe you need to"
          + " <rip> the head off of some corpse first?\n");
        return 0;
    }

    if (!(skull->id("_aod_head")))
    {
        notify_fail("You cannot collect that!\n");
        return 0;
    }

    if (skull->query_playerskull() &&
        query_verb() != "trophycollect")
    {
        notify_fail("Hmmm ... since the " + skull->short_func()
          + " belonged to an actual player, you figure you'll think"
          + " twice before collecting it. If you are sure you want"
          + " to harvest this perfectly good trophy, use"
          + " <trophycollect> as the command instead.\n");
        return 0;
    }

    write("You toss the "  + skull->short_func() + " into your sack.\n");
    tell_room(environment(this_player()),
        QCTNAME(this_player()) + " tosses the " + skull->short_func()
      + " into " + this_player()->query_possessive() + " blood-soaked"
      + " sack.\n", this_player());
    sack_collect(skull, this_player());
    skull->remove_object();

    /* We'll set the player age here. This will be used for calculating
     * skulls per hour in the Repository, but since that is hard to
     * catch at logout, we'll approximate by setting it here, which
     * is one of the most frequently performed actions by an Ogre.
     */
    AOD_MASTER->set_info(this_player(), "player_age",
        this_player()->query_age());

    return 1;
} /* collect_skull */


/*
 * Function name:        destroy_sack
 * Description  :        Remove the sack if we are not supposed to
 *                       have it
 */
public void
destroy_sack()
{
    write("The large blood-smeared sack disappears in a"
      + " flash of darkness!\n");

    remove_object();
} /* destroy_sack */


/*
 * Function name:        do_tutorial
 * Description  :        a part of the tutorial for new ogres. This
 *                       function is part of a delay call for a darkling
 *                       message
 * Arguments    :        object player - the player in question
 *                       int ogg - true if we want to do ogghelp instead
 */
public void
do_tutorial(object player, int ogg = 0)
{
    if (ogg)
    {
        player->ogghelp(player);
        return;
    }

    if (AOD_OGG_MASTER->get_info(player, "Tutorial") != "done")
    {
        AOD_OGG_MASTER->set_info(player, "Tutorial", "tutorial4");
        return;
    }

    set_this_player(player);           
    DARKLING_TELL(read_file(AOD_DIR + "tutorial4.txt", 0));
} /* do_tutorial */


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
    ::enter_env(dest, old);

    if (!IS_OGRE(environment(this_object())) &&
        !environment(this_object())->id(AOD_NPC))
    {
        set_alarm(0.1, 0.0, destroy_sack);
    }
} /* enter_env */