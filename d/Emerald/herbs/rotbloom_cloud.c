/*
 *  /d/Emerald/herbs/rotbloom_cloud.c
 *
 *  This cloud is created when a player uses the command <squeeze> on
 *  a rotbloom herb.
 *
 *  Copyright (c) July 2004, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>

/* Prototypes */
public void        create_object();
public void        do_blow(string arg);
public void        init();


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("cloud");
    add_name( ({ "vapor", "vapour", "_rotbloom_cloud" }) );

    add_adj( ({ "dark", "brown", "cloud", "of" }) );
    set_short("cloud of dark brown vapor");
    set_long("A cloud of dark brown vapor is hanging before your face."
      + " Though you are not breathing it in, your natural senses urge" 
      + " you to blow it away from you before you accidentally inhale"
      + " its noxious fumes.\n");

    add_prop(OBJ_M_NO_DROP, "You aren't able to rid yourself of the"
      + " cloud that way.\n");
} /* create_object */


/* 
 * Function name:        do_blow
 * Description  :        allow players to blow the cloud toward someone
 *                       else
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - succes, 0 - failure
 */
public int
do_blow(string arg)
{
    mixed   victim;
    mixed   cloud;
    object  shadow_ob;

    if (!strlen(arg))
    {
        notify_fail("Blow what?\n");
        return 0;
    }

    if (parse_command(arg, ({}),
        "[the] [dark] [brown] 'cloud' / 'vapor' [of] [vapor]"))
    {
        write("You quickly blow the cloud of vapor away from"
            + " your face, where it quickly disappates and is soon"
            + " diffused harmlessly into the air.\n");
        this_object->remove_object();

        return 1;
    }

    if (!parse_command(arg, all_inventory(environment(this_player())) + all_inventory(this_player()),
        "[the] %i 'at' / 'toward' / 'towards' %i",
        cloud, victim))
    {
        return 0;
    }

    cloud = NORMAL_ACCESS(cloud, 0, 0);
    victim = NORMAL_ACCESS(victim, 0, 0);

    if (!sizeof(cloud) || !sizeof(victim))
    {
        return 0;
    }

    cloud = cloud[0];
    victim = victim[0];

    if (!cloud->id("_rotbloom_cloud"))
    {
        return 0; /* let the mudlib handle it here */
    }

    if (!living(victim))
    {
        notify_fail("It would probably be more interesting to blow it"
           + " toward something that knows the difference.\n");
        return 0;
    }

    if (this_player()->query_real_name() == victim->query_real_name())
    {
        notify_fail("The cloud is already before you. You can't exactly"
          + " blow it toward yourself.\n");
        return 0;
    }

    this_player()->catch_msg("You blow the vapor toward "
       + QTNAME(victim) + ", who instinctively inhales in surprise!\n");
    victim->catch_msg(QCTNAME(this_player()) + " blows a cloud of"
      + " noxious vapors in your face. You inhale in surprise!\n");
    tell_room(environment(this_player()), QCTNAME(this_player())
      + " blows a cloud of noxious vapor toward " + QTNAME(victim)
      + ", who inhales in surprise!\n", ({ victim, this_player() }) );

    setuid();
    seteuid(getuid());
    
    shadow_ob = clone_object("/d/Emerald/herbs/rotbloom_shadow");
    shadow_ob->shadow_me(victim->query_real_name());
    shadow_ob->begin_alarm();

    victim->catch_msg("The hideous fumes from the noxious cloud"
      + " overwhelm you! Your senses are slammed by a fierce nausea!\n");
    victim->command("$puke");

    this_object()->remove_object();

    return 1;
} /* do_blow *;



/* 
 * Function name:        init
 * Description  :        add some commands to the player
 */
public void
init()
{
    ::init();

    add_action(do_blow, "blow");
} /* init */
