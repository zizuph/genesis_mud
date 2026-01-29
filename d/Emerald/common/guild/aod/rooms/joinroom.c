/*
 *  /d/Emerald/common/guild/aod/rooms/joinroom.c
 *
 *  Here players may join or leave the Army of Darkness guild.
 *
 *  Copyright (c) May 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/std/room";

#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <time.h>
#include <wa_types.h>
#include "../defs.h"

/* definitions */
#define     WARNING_PROP_LEAVE      "_aod_leaving_warning"
#define     WARNING_PROP_JOIN       "_aod_joining_warning"
#define     INFO_PROP               "_aod_read_rules_prop"
#define     ALTAR_DELAY             6.0
#define     VAMP_VISITS             (60 * 60 * 24)

/* global variables */
public int         Tell_Alarm;
public mapping     m_vamps = ([]);

/* prototypes */
public void        create_emerald_room();
public string      read_inscription();
public void        occjoin(object who);
public int         racejoin(object who);
public void        occleave(object who);
public int         do_pray(string arg);
public int         do_climb(string arg);
public int         flame_touch(string arg);
public void        init();
public void        begin_transformation(object player);
public void        transform_body(object player);
public void        transform_mind(object player);
public void        check_altar(object player);
public void        startroom(object player);
public int         not_join(string arg);


/*
 * Function name:        create_emerald_room
 * Description  :        set up the room with domain presets
 */
public void
create_emerald_room()
{
    set_short("the transformation chamber");

    set_em_long("Darkness skitters across the perfect walls of this"
      + " chamber, playing along their glassy surface. Directly at"
      + " the center of the chamber beneath a domed ceiling, a black"
      + " stone altar rests upon the chamber floor. Above the altar,"
      + " suspended in mid air, burns a dark flame. Spiral stairs wind"
      + " their way back down to the base of the tower.\n");

    add_item( ({ "dark", "darkness", "shadow", "shadows" }),
        "The darkness is cast by the flame which flickers above the"
      + " altar.\n");
    add_item( ({ "flame", "fire", "dark flame", "dark fire",
                 "flames", "shadowy flame", "shadowy flames" }),
        "The flame above the altar sends forth darkness rather than"
      + " light. It is a conduit of the essence of Val-Shoreil"
      + " himself! You notice its shadows flickering upon an"
      + " inscription on the altar.\n");
    add_item( ({ "altar", "black altar", "stone altar",
                 "black stone altar", "disc", "round disc" }),
        "The altar is formed as a perfectly round disc that rises"
      + " three feet from the floor. Above the altar swirls the"
      + " shadowy flames of a dark fire. You notice an inscription"
      + " carved into the altar.\n");
    add_item( ({ "inscription" }), read_inscription);
    add_item( ({ "here", "area", "chamber", "room" }), long);
    add_item( ({ "wall", "walls", "perfect wall", "perfect walls",
                 "chamber wall", "chamber walls", "walls of the chamber",
                 "wall of the chamber" }),
        "The chamber walls form a perfect hexagonal perimeter which"
      + " slowly tapers to a domed ceiling above.\n");
    add_item( ({ "surface", "glassy surface", "stone", "dark stone",
                 "black stone" }),
        "The entire tower is comprised of stone so smooth and black"
      + " that to stare at it causes disorientation.\n");
    add_item( ({ "ceiling", "center of the chamber", "center",
                 "up", "domed ceiling", "dome", "sphere",
                 "concave sphere", "polished sphere",
                 "polished concave sphere" }),
        "The ceiling is a round and smooth dome, the severe edges of"
      + " the hexagonal perimeter relaxing to gradually fade to"
      + " a polished concave sphere above.\n");
    add_item( ({ "tower", "building" }),
        "Though the tower surrounds you here, you have no real sense"
      + " of its proportion from this high chamber.\n");
    add_item( ({ "sky", "outside" }),
        "The sky outside is not visibly from here.\n");
    add_item( ({ "down", "ground", "floor" }),
        "The floor is polished and smooth, except where an altar"
      + " rests at its center and a set of spiral stairs interrupts its"
      + " surface in the south corner.\n");
    add_item( ({ "south corner", "corner", "stair", "stairs",
                 "spiral", "spiral stair", "spiral stairs",
                 "staircase", "spiral staircase", "step", "steps",
                 "spiral steps", "stone step", "stone steps" }),
        "Stone steps wind their way down to the base of the tower from"
      + " the south corner of the chamber.\n");
    add_item( ({ "base", "base of the tower", "tower base" }),
        "The tower base is not visible from here. You would need to"
      + " climb down the steps to reach it.\n");
    add_item( ({ "hexagon", "perimeter", "hexagonal perimeter" }),
        "The tower has been crafted with mystical precision. There is"
      + " a power in its very form.\n");
    add_item( ({ "edge", "edges", "severe edge", "severe edges" }),
        "The farther your eyes travel up, the more the edges of the"
      + " hexagonal perimeter seem to melt into the smooth surface of"
      + " the dome.\n");

    add_cmd_item( ({ "inscription", "the inscription" }),
                  ({ "read" }), read_inscription);

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("tower", "down");

    setuid();
    seteuid(getuid());
} /* create_emerald_room */


/*
 * Function name:        read_inscription
 * Description  :        print the info about joining the guild
 * Returns      :        string - the text
 */
public string
read_inscription()
{
    this_player()->add_prop(INFO_PROP, 1);
    return read_file(AOD_DIR + "joining.txt", 0);
} /* read_inscription */


/*
 * Function name:        occjoin
 * Description  :        allow players to try to join this guild 
 * Arguments    :        object who - the player who wants to join
 */
public void
occjoin(string str)
{
    object  sh;
    mixed   why;

    /* Somehow, the player left the altar! */
    if (environment(this_player()) != this_object())
    {
        write("You have left the altar of Val-Shoriel! The flames die"
          + " out instantly.\n");
        return;
    }

    if (this_player()->query_guild_name_occ() == GUILD_NAME)
    {
        write("You are already an Ogre! The gods are confused!\n");
        return;
    }

    if (this_player()->query_guild_member_race())
    {
        write("You already have a race guild!\n");
        write("The flames die out and you stumble back from the altar.\n");
        tell_room(environment(this_player()), "The flames die out, and "
          + QTNAME(this_player()) + " stumbles back from the altar.\n",
            this_player());
        return;
    }

    /* Clone the shadow */

    setuid();
    seteuid(getuid());

    sh = clone_object(AOD_SHADOW);

    /* See if this member is acceptable */
    if (stringp(why = sh->acceptable_member(this_player())))
    {
        write(why);
    }
    else
    {
        /* Try to add the shadow to the player */
	switch (sh->add_occ_shadow(this_player()))
	{
	    case 1:
                /* since we are bundling race membership, we have to
                 * see if they can join the race guild too before we
                 * do anything here.
                 */
                if (racejoin(this_player()))
                {     
                    TELL_G("Successfully joined with race.");  
		    return;
                }

                /* We couldn't shadow the player, so remove the shadow */
                sh->remove_shadow();  
                break;
	    case -4:
	        /* The player has an occ guild already, or one of his existing
                 * guilds has blocked this one.
                 */ 
		write("The flames suddenly weaken and your body and mind"
                  + " are returned to normal. It seems your"
                  + " other guilds do not wish you to join this one.\n");
                write_file(AOD_LOG_DIR + "join_log",
                    TIME2FORMAT(time(), "mm/dd") + " ("
                  + ctime(time())[11..18] + ") "
                  + capitalize(this_player()->query_name()) + " -- "
                  + " failed to join (blocked - occ)\n");
		break;
	    default:
	        /* Some error in shadowing */
		write("The flames suddenly weaken and your body and mind"
                  + " are returned to normal. An error has"
                  + " prevented you from joining. Please mail Gorboth"
                  + " immediately.\n");
                write_file(AOD_LOG_DIR + "join_log",
                    TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
                  + ctime(time())[11..18] + ") "
                  + capitalize(this_player()->query_name()) + " -- "
                  + " failed to join (error - occ)\n");
		break;
	}
    }

    write("The flames die out and you stumble back from the altar.\n");
    tell_room(environment(this_player()), "The flames die out, and "
      + QTNAME(this_player()) + " stumbles back from the altar.\n",
        this_player());

    /* We couldn't shadow the player, so remove the shadow */
    sh->remove_shadow();
} /* occjoin */



/*
 * Function name:        racejoin
 * Description  :        occjoin was successful, so now we have the
 *                       player join the raceguild 
 * Arguments    :        object who - this_player()
 */
public int
racejoin(object who)
{
    object  sh,
            race_sh,
           *clothes = this_player()->query_clothing(-1),
           *weapons = this_player()->query_weapon(-1),
           *dropped_clothes,
           *other_junk;
    mixed   why,
           *target = FILTER_LIVE(all_inventory(environment(
                       this_player())));
    int     ogre_size,
            i = 0,
            n = 0,
           *members;
    string *var_txt = ({ " bursts", "falls", "slips" });

    /* Somehow, the player left the altar! */
    if (environment(who) != this_object())
    {
        write("You have left the altar of Val-Shoriel! The flames die"
          + " out instantly and your body and mind snap back to their"
          + " former state!\n");
        return 0;
    }

    race_sh = clone_object(AOD_RACE_SHADOW);
    sh = clone_object(AOD_SHADOW);

    set_this_player(who);

    /* Now, same thing with the race shadow */
    if (stringp(why = race_sh->acceptable_member(this_player())))
    {
        write(why);
    }
    else
    {
        /* Try to add the shadow to the player */
	switch (race_sh->add_race_shadow(this_player()))
	{
	    case 1:
	        /* We have successfully shadowed the player, so we're set */

                write("You are now a member of the Army of Darkness!\n");
                write("You have become a mighty Ogre!\n\n");

                /* set the join age of the player in the save file */
                AOD_MASTER->set_join_age(this_player());
                AOD_MASTER->set_membership_status(this_player(), 1);

                /* increase the player's height to Ogre standards */
                ogre_size = this_player()->query_prop(CONT_I_HEIGHT);
                ogre_size += HEIGHT_FACTOR;
                this_player()->add_prop(CONT_I_HEIGHT, ogre_size);

                /* give the player ogre weight and volume */
                ogre_size = this_player()->query_prop(CONT_I_WEIGHT);
                ogre_size += WEIGHT_FACTOR;
                this_player()->add_prop(CONT_I_WEIGHT, ogre_size);

                ogre_size = this_player()->query_prop(CONT_I_VOLUME);
                ogre_size += WEIGHT_FACTOR;
                this_player()->add_prop(CONT_I_VOLUME, ogre_size);

                /* the player loses certain skills */
                this_player()->set_skill(SS_PARRY, 0);
                this_player()->set_skill(SS_WEP_CLUB, 0);
                this_player()->set_skill(SS_2H_COMBAT, 0);

                /* The player drops their weapons */
                if (sizeof(weapons))
                {
                    for (i = 0; i < sizeof(weapons); i++)
                    {
                        weapons[i]->move(environment(this_player()));
                    }

                    for (i = 0, n = sizeof(target); i < n; i++)
                    {
                        if (sizeof(weapons) > 1)
                        {
                            var_txt[1] = "fall";
                            var_txt[2] = "slip";
                        }

                        if (target[i] != this_player())
                        {
                            target[i]->catch_msg("With a crash, "
                              + FO_COMPOSITE_DEAD(weapons,
                                                  target[i]) + " "
                              + var_txt[2] + " from "
                              + QTNAME(this_player()) + "'s listless "
                              + "fingers and " + var_txt[1] + " to the"
                              + " ground.\n\n");
                        }
                        else
                        {
                            target[i]->catch_msg("With a crash, "
                              + FO_COMPOSITE_DEAD(weapons,
                                                  target[i]) + " "
                              + var_txt[2] + " from your tingling fingers"
                              + " and " + var_txt[1] + " to the"
                              + " ground.\n\n");
                        }
                    }
                }
                  

//                /* Here, the increase in body size causes the clothes
//                 * and armours the ogre is wearing that are not auto-
//                 * loading or ogre-sized to burst off. The first loop
//                 * is to count the number of such items to allocate
//                 * the proper array size. */
//                for (i = 0, n = 0; i < sizeof(clothes); i++)
//                {
//                    if (!clothes[i]->query_prop(AOD_WEAR_PROP) ||
//                        !strlen(clothes[i]->query_auto_load()))
//                    {
//                        if (clothes[i]->check_armour())
//                        {
//                            n++;
//                        }
//                    }
//                }
//
//                dropped_clothes = allocate(n);
//
//                /* And now, in the second loop, we add the actual
//                 * clothing objects to an array to have them be
//                 * dropped and described. */
//                for (i = 0; i < sizeof(clothes); i++)
//                {
//                    if (!clothes[i]->query_prop(AOD_WEAR_PROP) ||
//                        !strlen(clothes[i]->query_auto_load()))
//                    {
//                        if (clothes[i]->check_armour())
//                        {
//                            dropped_clothes[i] = clothes[i];
//                            clothes[i]->move(environment(this_player()));
//                            clothes[i]->add_prop(OBJ_I_BROKEN, 1);
//                        }
//                    }
//                }
//
//                /* Finally, we describe to the player and the room that
//                 * said objects are bursting off.
//                 */
//                if (sizeof(dropped_clothes))
//                {
//                    for (i = 0, n = sizeof(target); i < n; i++)
//                    {
//                        if (sizeof(dropped_clothes) > 1)
//                        {
//                            var_txt[0] = " burst";
//                            var_txt[1] = "fall";
//                        }
//
//                        if (target[i] != this_player())
//                        {
//                            target[i]->catch_msg("With a violent"
//                              + " shudder, "
//                              + FO_COMPOSITE_DEAD(dropped_clothes,
//                                                  target[i])
//                              + var_txt[0] + " from the swollen body of "
//                              + QTNAME(this_player()) + " and "
//                              + var_txt[1] + " to the ground in ruined"
//                              + " pieces!\n\n");
//                        }
//                        else
//                        {
//                            target[i]->catch_msg("With a violent"
//                             + " shudder, "
//                              + FO_COMPOSITE_DEAD(dropped_clothes,
//                                                  target[i])
//                              + var_txt[0] + " from your swollen body and "
//                              + var_txt[1] + " to the ground in ruined"
//                              + " pieces!\n\n");
//                        }
//                    }
//                }

                /* hmmm ... so maybe the player is also carrying some
                 * weapons on them but not wielding them. We'll need
                 * to change two to one-handers.
                 */
                other_junk = deep_inventory(this_player());
                
                for (i = 0; i < sizeof(other_junk); i++)
                {
                    if (other_junk[i]->weapon_type())
                    {
                        if (other_junk[i]->query_hands() == W_BOTH)
                        {
                            other_junk[i]->add_prop(AOD_WIELD_PROP, 1);
                            other_junk[i]->set_hands(W_ANYH);
                        }
                    }
                }

                this_player()->command("$roar");

                /* If this is the first member to ever join the guild, lets
                 * write to the milestone file.
                 */
                members = AOD_MASTER->scan_accounts();
                if (sizeof(members) < 2)
                {
                    AOD_MASTER->write_milestone("First Member of the Army",
                        this_player());
                }

                /* Teleport the player to the startroom. */
                set_alarm(9.0, 0.0, &startroom(this_player()));

                write_file(AOD_LOG_DIR + "join_log",
                    TIME2FORMAT(time(), "mm/dd") + " ("
                  + ctime(time())[11..18] + ") "
                  + capitalize(this_player()->query_name()) + " -- "
                  + " joined.\n");
		return 1;
    
	    case -4:
	        /* The player has an occ guild already, or one of his existing
                 * guilds has blocked this one.
                 */ 
		write("The flames suddenly weaken and your body and mind"
                  + " are returned to normal. It seems your"
                  + " other race guild does not wish you to join this"
                  + " one.\n");
                write_file(AOD_LOG_DIR + "join_log",
                    TIME2FORMAT(time(), "mm/dd") + " ("
                  + ctime(time())[11..18] + ") "
                  + capitalize(this_player()->query_name()) + " -- "
                  + " failed to join (blocked - race)\n");
		break;
    
	    default:
	        /* Some error in shadowing */
		write("The flames suddenly weaken and your body and mind"
                  + " are returned to normal. An error has"
                  + " prevented you from joining. Please mail Gorboth"
                  + " immediately.\n");
                write_file(AOD_LOG_DIR + "join_log",
                    TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
                  + ctime(time())[11..18] + ") "
                  + capitalize(this_player()->query_name()) + " -- "
                  + " failed to join (error - race)\n");
		break;
	}
    }

    write("The flames die out and you stumble back from the altar.\n");
    tell_room(environment(this_player()), "The flames die out, and "
      + QTNAME(this_player()) + " stumbles back from the altar.\n",
        this_player());

    /* We couldn't shadow the player, so remove the shadow */
    race_sh->remove_shadow();
    sh->remove_shadow();

    return 0;
} /* racejoin */


/*
 * Function name:        occleave
 * Descriptions :        allow the player to leave the guild
 * Arguments    :        object who - who is leaving?
 */
public void
occleave(object who)
{
    object  sack;
    int     normal_size;

    if (check_altar(who))
    {
        return;
    }

    set_this_player(who);

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
        write("You are not currently an Ogre! The Gods are confused!\n");
        return;
    }

    /* The reason for forcing the player to drop all is to make sure
     * that weapons which have been converted from two to one-handers
     * are converted back before the player has a chance to ditch
     * the shadow that controls such processes. This could have been
     * a very NASTY loophole. ;-)
     */
    write("At the touch of the cold flame, your lose your ability"
      + " to hang on to what you are carrying!\n\n");
    this_player()->command("$drop all");

    /* If this was the Headhunter General, it can mess up the election
     * cycle, so we need to make sure the code knows that s/he left.
     */
    if (AOD_GENERAL(this_player()))
    {
        AOD_MASTER->set_info(REPOSITORY_FILE, "General_Awol",
            this_player()->query_real_name());
        AOD_MASTER->set_info(REPOSITORY_FILE, "GENERAL",
            NOT_YET_ASSIGNED);

        write_file(AOD_LOG_DIR + "officer_log",
            TIME2FORMAT(time(), "mm/dd") + " ("
          + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_name()) + " -- "
          + " went AWOL!\n");
    }

    this_player()->remove_occ_member();
    this_player()->remove_race_member();
    AOD_MASTER->set_membership_status(this_player(), 0);

    write("With a sudden surge, the flames leap up your arms"
      + " to dance agonizingly along the surface of your"
      + " massive body, slowly burning away the flesh they had once"
      + " granted you! The pain is beyond description, and yet"
      + " when it is all over, you find yourself still standing,"
      + " staring in disbelief at your smoking limbs.\n\n");
    tell_room(environment(this_player()),
        "With a sudden surge, the flames leap up " + QCTNAME(this_player())
      + "'s arms to dance mercilessly along the surface of "
      + this_player()->query_possessive() + " body, slowly burning away"
      + " its massive bulk. Soon, the flames die down, leaving a shaken,"
      + " smoldering " + this_player()->query_race() + " behind.\n\n",
        this_player());

    this_player()->command("$whimper");
    write("A malevolent voice booms: WRETCHED FOOL!\n\n");

    write("You have left the Army of Darkness!\n");
    write("You are a normal " + this_player()->query_race() + " once"
      + " more.\n\n");

    /* Return the player's height, weight, and volume to normal */
    normal_size = this_player()->query_prop(CONT_I_HEIGHT);
    normal_size -= HEIGHT_FACTOR;
    this_player()->add_prop(CONT_I_HEIGHT, normal_size);

    normal_size = this_player()->query_prop(CONT_I_WEIGHT);
    normal_size -= WEIGHT_FACTOR;
    this_player()->add_prop(CONT_I_WEIGHT, normal_size);

    normal_size = this_player()->query_prop(CONT_I_VOLUME);
    normal_size -= WEIGHT_FACTOR;
    this_player()->add_prop(CONT_I_VOLUME, normal_size);

    /* destroy the guild object */
    if (objectp(sack = present("_aod_guild_sack", this_player())))
    {
        sack->destroy_sack();
    }

    write_file(AOD_LOG_DIR + "leave_log",
      TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
    + ctime(time())[11..18] + ") "
    + capitalize(this_player()->query_name()) + " -- "
    + " left the guild.\n");

    AOD_MASTER->check_leader_update();
} /* occleave */

/*
 * Function name:        do_pray
 * Description  :        allow players to worship Val-Shoreil
 * Arguements   :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - otherwise
 */
public int
do_pray(string arg)
{
    object  here = environment(this_player());
    int     chance = random(4);

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " where or to whom?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[down] [to] [before] [the] 'altar' / 'val-shoreil'"))
    {
        notify_fail("You are in the presence of the Dark God, perhaps"
          + " he is to he you should " + query_verb() + "!\n");
        return 0;
    }

    switch(query_verb())
    {
        case "pray":
        case "kneel":
        default:
            write("You kneel reverently before the altar, and offer"
              + " a quiet prayer to Val-Shoreil.\n");
            tell_room(here, QCTNAME(this_player()) + " kneels"
              + " reverently before the altar, offering a silent"
              + " prayer.\n", this_player());
            break;
        case "worship":
            write("You fall on your knees before the altar, bowing"
              + " down to worship the God of Darkness.\n");
            tell_room(here, QCTNAME(this_player()) + " falls down and"
              + " begins worshipping feverishly at the altar.\n",
                this_player());
            break;
    }

    if (!(random(5)))
    {
	string name = this_player()->query_real_name();

        if (this_player()->query_vampire())
	{
	    if (!m_vamps[name] ||
		((time() - m_vamps[name]) >= VAMP_VISITS))
	    {
		if (this_player()->restore_vamp_power())
		    chance = 99;
	    }
        }

	switch(chance)
	{
	case 0:
	    write("You feel that Val-Shoreil is pleased!\n");
	    break;
	case 1:
	    write("You feel a dark blessing upon you.\n");
	    break;
	case 2:
	    write("Darkness from the flame flitters over your"
		+ " body, exciting your senses!\n");
	    break;
	case 3:
	    write("You feel more confident!\n");
	    break;
	case 99:
	    m_vamps[name] = time();
            write("Confusion washes over you momentarily, and then you"
              + " experience tremendous pain as your blood begins to"
              + " boil within you! Minutes pass as you writhe in agony"
              + " upon the ground. As quickly as it began, the pain"
              + " departs without explanation. A new potency stirs"
              + " within your blood.\n");
	    break;
	}
    }

    return 1;
} /* do_pray */

    
/*
 * Function name:        do_climb
 * Description  :        allow players to climb down the stairs
 * Arguments    :        string arg - what was typed following the verb
 * Returns      :        int 1 -- success, 0 -- failure.
 */
public int
do_climb(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("What do you wish to climb?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[down] [the] [stone] [spiral] 'stair' / 'stairs' /"
      + " 'stairway' / 'staircase' / 'step' / 'steps'"))
    {
        if (parse_command(arg, ({}),
            "'up' [the] [stone] [spiral] 'stair' / 'stairs' /"
          + " 'stairway' / 'staircase' / 'step' / 'steps'"))
        {
            notify_fail("The steps do not lead up. Perhaps you could"
              + " climb down them instead.\n");
            return 0;
        }

        notify_fail("That is not possible. Do you wish to climb down"
          + " the stairs perhaps?\n");
        return 0;
    }

    write("You climb down the spiral staircase.\n");
    this_player()->command("$d");

    return 1;
} /* do_climb */


/*
 * Function name:        flame_touch
 * Description  :        Allow players to touch the flame of Val-Shoreil,
 *                       whereby they may either join or leave the guild.
 * Arguments    :        string arg - what the player typed after the verb.
 * Returns      :        int - 1: success,
 *                             0: failure.
 */
public int
flame_touch(string arg)
{
    string  flametxt = "You step up to the altar and place your hands"
                     + " into the Dark Flame. Instantly, an icy burning"
                     + " sensation begins to burn in your fingers!\n\n",
            othertxt = QCTNAME(this_player()) + " steps up to the altar"
                     + " and places " + this_player()->query_possessive()
                     + " hands into the Dark Flame. " + capitalize(
                       this_player()->query_pronoun()) + " stiffens as"
                     + " the dark flame begins to burn in "
                     + this_player()->query_objective() + "!\n\n";

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [dark] 'flame' / 'fire' [of] [val] [shoreil]"
      + " [val-shoreil]"))
    {
        notify_fail("Perhaps you wish to " + query_verb() + " the"
          + " flame?\n");
        return 0;
    }

    if (!IS_OGRE(this_player()))
    {
        if (!this_player()->query_prop(INFO_PROP))
        {
            write("Just as you are about to touch the flame, you notice"
              + " its dark unlight flickering upon an inscription carved"
              + " into the altar. Perhaps you should read it first.\n");

            return 1;
        }

        if (!this_player()->query_prop(WARNING_PROP_JOIN))
        {
            write("Touch the Dark Flame of Val-Shoreil and join with the"
              + " Army of Darkness? If you are certain you wish to do"
              + " this, simply type <touch flame> one more time.\n");
            this_player()->add_prop(WARNING_PROP_JOIN, 1);

            return 1;
        }

        /* Okay ... they've been warned. Try to join 'em up! */
        if (!Tell_Alarm || !sizeof(get_alarm(Tell_Alarm)))
        {
            Tell_Alarm = set_alarm(ALTAR_DELAY, 0.0,
                &begin_transformation(this_player()));
            write(flametxt);
            tell_room(this_object(), othertxt, this_player());

            return 1;
        }

        write("The flame is currently in motion. You must be"
          + " patient!\n");
        return 1;
    }

    if (!this_player()->query_prop(WARNING_PROP_LEAVE))
    {
        write("Return to your pathetic non-ogre form and leave the"
          + " Army of Darkness? To persue this path of foolishness"
          + " simply type <touch flame> one more time.\n");
        this_player()->add_prop(WARNING_PROP_LEAVE, 1);

        return 1;
    }     

    /* Okay ... they've been warned. Remove them from the guild! */
    if (!Tell_Alarm || !sizeof(get_alarm(Tell_Alarm)))
    {
        Tell_Alarm = set_alarm(ALTAR_DELAY, 0.0, &occleave(this_player()));

        write(flametxt);
        tell_room(this_object(), othertxt, this_player());

        return 1;
    }

    write("The flame is currently in motion. You must be"
      + " patient!\n");
    return 1;
} /* flame_touch */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(flame_touch, "touch");
    add_action(flame_touch, "feel");
    add_action(do_pray, "pray");
    add_action(do_pray, "worship");
    add_action(do_pray, "kneel");
    add_action(do_climb, "climb");
    add_action(not_join, "join");
    add_action(not_join, "leave");
} /* init */


/*
 * Function name:        begin_transformation
 * Description  :        Lets make this change interesting. We'll go
 *                       in a few different stages, checking to see
 *                       if the player ever leaves the room between.
 * Arguments    :        object player - the player being transformed
 */
public void
begin_transformation(object player)
{
    if (check_altar(player))
    {
        return;
    }

    player->catch_msg("With a violent burst, the flame leaps up your"
                  + " arms and engulfs your face and head, quickly"
                  + " travelling down your entire body! You stagger back"
                  + " from the altar as grinding pain whips through"
                  + " every fiber of your flesh!\n\n");

    tell_room(environment(player),
                    "With a violent burst, the flames engulf "
                  + player->query_possessive() + " entire body! "
                  + capitalize(player->query_pronoun())
                  + " staggers back from the altar, collapsing to "
                  + player->query_possessive() + " knees as the"
                  + " black fire rips through flesh and bone.\n\n",
                    player);

    Tell_Alarm = set_alarm(ALTAR_DELAY, 0.0, &transform_body(player));
} /* begin_transformation */


/*
 * Function name:        transform_body
 * Description  :        The transformation process continues
 * Arguments    :        object player - the player being transformed
 */
public void
transform_body(object player)
{
    if (check_altar(player))
    {
        return;
    }

    player->catch_msg("Collapsing to your"
                  + " knees, you feel a brutal transformation taking"
                  + " place. Every cell within you is flailing, ripping"
                  + " outward in sudden growth ... you feel yourself ..."
                  + " expanding.\n\n");
    tell_room(environment(player), "Ripples"
                  + " of new flesh begin to flex from the ravaged"
                  + " tissues of " + player->query_possessive()
                  + " body. As the flames die out, "
                  + QTNAME(player) + " slowly rises as a new"
                  + " life form ... a mighty Ogre!\n\n", player);

    Tell_Alarm = set_alarm(ALTAR_DELAY, 0.0, &transform_mind(player));
} /* transform_body */


/*
 * Function name:        transform_mind
 * Description  :        The transformation process continues
 * Arguments    :        object player - the player being transformed
 */
public void
transform_mind(object player)
{
    if (check_altar(player))
    {
        return;
    }

    player->catch_msg("As you slowly rise to your feet, blinding pain"
      + " stabs like needles into your brain! It feels like your skull"
      + " is thickening, crushing inward ... destroying your mind!"
      + " World ... seems ......... confusing ..........\n\n");
    tell_room(environment(player), QCTNAME(player) + " grabs "
      + player->query_possessive() + " head with both hands, shivering"
      + " in what appears to be excruciating agony. The look of pain"
      + " in " + player->query_possessive() + " eyes fades to one of"
      + " confusion as " + player->query_possessive() + " pupils dialate"
      + " and " + player->query_pronoun() + " gazes stupidly around"
      + " the room.\n\n", player);

    Tell_Alarm = set_alarm(ALTAR_DELAY, 0.0, &occjoin(player));
} /* transform_mind */


/*
 * Function name:        check_altar
 * Description  :        see if the player has left the room. If so,
 *                       call off the transformation.
 * Arguments    :        object player - the person in question
 * Returns      :        int 1, player left so we stop,
 *                           0, player still at altar, keep going
 */
public int
check_altar(object player)
{
    /* Somehow, the player left the altar! */
    if (environment(player) != this_object())
    {
        if (IS_OGRE(player))
        {
            player->catch_msg("You have left the altar! The flames"
              + " vanish from your flesh, and your Ogre form remains"
              + " intact!\n");
        }
        else
        {
            player->catch_msg("You have left the altar! The flames"
              + " vanish from your flesh, returning your body and mind"
              + " to that of a normal " + player->query_race() + ".\n");
        }

        return 1;
    }

    return 0; /* keep the transformation going */
} /* check_altar */


/*
 * Function name:        startroom
 * Description  :        Teleport the player to the startroom and
 *                       have them kick the wall.
 * Arguments    :        object player: the player in question
 */
public void
startroom(object player)
{
    player->catch_tell("You are suddenly enveloped in a ball of purple"
      + " energy and transported elsewhere!\n");
    tell_room(AOD_ROOM_DIR + "start", QCTNAME(player) + " suddenly"
      + " appears in a flash of purple energy!\n");
    player->move_living("M", AOD_ROOM_DIR + "start", 1, 1);
    tell_room(this_object(), QCTNAME(player) + " is suddenly enveloped"
      + " in a ball of purple energy, and vanishes!\n");
    
    player->command("$kick wall");
} /* startroom */


/*
 * Function name:        not_join
 * Description  :        Some hasty players will probably just try to
 *                       <join army> here or something. We'll tell them
 *                       a bit about what to do.
 * Arguments    :        what the player typed after <join>
 * Returns      :        int 1 - if they tried to join the army
 *                           0 - otherwise let the mudlib handle it
 */
public int
not_join(string arg)
{
    if (!strlen(arg) ||
        !parse_command(arg, ({}),
        "[the] 'army' / 'guild' [of] [darkness]"))
    {
        return 0; /* the mudlib can handle <join> */
    }

    write("Upon the altar are the instructions you seek, mortal!\n");
    return 1;
} /* not_join */
