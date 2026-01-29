/*
 *  /d/Emerald/blackwall/delrimmon/obj/explosive.c
 *
 *  This object will explode if subject to enough force of impact.
 *  It can be loaded into a catapult:
 *      /d/Emerald/blackwall/delrimmon/obj/catapult.c
 *  Or into the broken arm of the catapult:
 *      /d/Emerald/blackwall/delrimmon/obj/wep/catapult_arm.c
 *
 *  Copyright (c) Cooper Sherry (Gorboth) July 1997
 *
 */
#pragma strict_types

inherit "/std/object";
inherit "/d/Emerald/blackwall/delrimmon/legacy/tell_funcs";

#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void    create_object();
public int     read_runes(string str);
public void    init();
public int     untie_cord(string arg);
public void    bomb_explode();
public void    add_crater();
public void    do_log(object ob, string logtxt);
public void    throw_victim(object victim);

/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("explosive");

    set_short("small leather bundle");
    set_long(BSN("Though small, about the size of an average human head,"
      + " this bundle is extremely heavy, as though it were composed of"
      + " solid rock. It is tightly wrapped in what appears to be very"
      + " thick leather which has been securely bound by a cord of"
      + " black material. Runes of some sort have been burned into the"
      + " leather at the top corner of the package."));
    add_name(({"bundle","package","shell","ammunition","_em_shell"}));
    add_adj(({"small","heavy","tightly wrapped","wrapped","leather"}));

    add_item(({"rune","runes","letters"}), BSN(
        "The runes have been burnt into the leather material which"
      + " binds the package. The flowery script of their shapes"
      + " is quite beautiful."));
    add_item(({"leather","thick leather"}), BSN(
        "This leather, though obviously quite ancient, does not"
      + " appear to be cracked or worn through in any places. It"
      + " securely holds the contents of the package, bound only by"
      + " a thin black cord."));
    add_item(({"cord","black cord","thin cord","thin black cord"}),
        BSN("The cord is woven tightly and protected by some residue."
      + " It may be some form of animal hair tightly woven and then"
      + " dipped in tar."));

    add_prop(OBJ_I_WEIGHT, 40000); //  It is extremely heavy for its size.
    add_prop(OBJ_I_VOLUME, 1000);
}

/*
 * Function name:        read_runes
 * Description  :        let the player try to read the runes
 * Arguments    :        string -- arg
 * Returns      :        1 -- success, 0 -- failure
 */
public int
read_runes(string str)
{
    if (!strlen(str))
        NFN0("Read what?");

    if (str != "runes")
        NFN0("What do you wish to read?");

    if (TP->query_skill(SS_LANGUAGE) < 45)
    {
        WRITE("These letters are of a script quite unfamiliar to you.");
        return 1;
    }

    write(BSN("These letters appear to be a type of the Elvish script"
      + " commonly used in the archives of Telberin. They form the"
      + " word 'Thunder.'"));
    return 1;
}

/*
 * Function name:        init
 * Description  :        add some verbs to the player
 */
public void
init()
{
    ::init();

    add_action(untie_cord, "untie");
    add_action(untie_cord, "break");
    add_action(untie_cord, "cut");
    add_action(read_runes, "read");
}


/*
 * Function name:        untie_cord
 * Description  :        lets the player try to untie the cord
 * Arguments    :        string arg -- what the player typed
 * Returns      :        0 (with appropriate fail message)
 */
public int
untie_cord(string arg)
{
    if (!strlen(arg))
    {
        NFN0(CAP(QVB) + " what?");
    }

    if (!parse_command(arg, ({}),
        "[the] [black] [leather] 'cord' / 'bundle'"))
    {
        return 0;
    }

    NFN0("You attempt to " + QVB + " the black cord which binds"
       + " the leather bundle, only to discover that it is as"
       + " hard as iron.");
} /* untie_cord */

/*
 * Function name:        bomb_explode
 * Description  :        cause the bundle to explode, damaging all
 *                       livings in the room, and throwing them
 *                       in the direction of a random exit
 *                       KABOOM!!
 */
public void
bomb_explode()
{
    object *victims = FILTER_LIVE(all_inventory(ENV(TO)));
    int     i;

    tell_room(ENV(TO), "The " + TO->short() + " explodes with a"
      + " deafening concussion as it hits the ground, throwing"
      + " fire and stones in all directions!\n");
    tell_players_in_same_subdir(ENV(TO), BSN(
        "A thunderous boom echoes suddenly throughout the area."));

    while (i < sizeof(victims))
    {
        if (victims[i]->query_wiz_level())
        {
            victims[i]->catch_msg("Your wizard status protects you"
                                + " from the blast.\n");
        }
        else
        {
            throw_victim(victims[i]);
        }

        i++;
    }

    add_crater();
    TO->remove_object();
} /* bomb_explode */


/*
 * Function name:        add_crater
 * Description  :        adds an impact crater to the room. :-)
 */
public void
add_crater()
{
    object  crater;

    FIX_EUID

    crater = clone_object("/std/object");
    crater->set_name("hole");
    crater->add_name( ({ "crater", "mark", "area", "earth" }) );
    crater->add_adj( ({ "large", "blasted" }) );
    crater->set_short("large area of blasted earth");
    crater->set_pshort("large areas of blasted earth");
    crater->set_long(BSN(
        "Various debris of rocks and dirt splay outward from"
      + " this area of blasted earth. It would appear as if"
      + " a violent explosion of some form ripped into the ground"
      + " and immediate area here."));
    crater->add_prop(OBJ_M_NO_GET, 1);
    crater->move(ENV(TO));
} /* add_crater */


/*
 * Function name:        throw_victim
 * Description  :        livings in the vicinity of the explosion
 *                       are thrown out a random exit by the blast
 * Arguments    :        object victim -- the person being thrown
 */
public void
throw_victim(object victim)
{
    object  room = ENV(TO);
    mixed   oroom;
    int     n;
    int    damage;

    FIX_EUID

    victim->catch_msg("You are thrown violently backwards by the"
      + " blast, and land on hard ground a good distance away.\n");

    n = random(sizeof(room->query_exit()) / 3);
    oroom = room->query_exit()[n*3];

    if (objectp(oroom))
    {
        oroom = file_name(oroom);
    }

    tell_room(oroom, "With a frightened yell, " + QNAME(victim)
      + " comes flying through the air, crashlanding just"
      + " beside you!\n");
    victim->move_living("M", oroom, 1, 1);
    tell_room(room, QCTNAME(victim) + " is flung violently "
      + room->query_exit()[n*3+1] + "wards by the blast!\n");

    damage = 500 + random(500);
    victim->reduce_hit_point(damage);

    if (interactive(victim))
    {
        do_log(victim, " hit by blast.  Damage: " + damage);
    }

/*
 * I think we'd better not have this kill things for now. (Gorboth)
 */
//  if (victim->query_hp() <= 0)
//  {
//      victim->do_die(TO);

//      if (interactive(victim))
//      {
//          do_log(victim, " DIED FROM THE BLAST");
//      }
//  }

} /* throw_victim */


/*
 * function name:        do_log
 * description  :        helps us log unpleasantries that happen
 *                       to players
 * arguments    :        object ob -- the player
 *                       string logtxt -- what happened
 */
public void
do_log(object ob, string logtxt)
{
    log_file(LOG_FILE + "explosions", ctime(time())
           + " -- " + ob->query_name() + " ("
           + ob->query_average_stat() + ")"
           + logtxt + ".\n");

    return;
} /* do_log */
