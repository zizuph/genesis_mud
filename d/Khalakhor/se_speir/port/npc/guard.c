/*
 * guard.c
 *
 * Guards for Port MacDunn.
 * 
 * The guards contain a special 'arrest' code that is intended
 * to imprison players who fight with them rather than kill. Death
 * is still a possibility though, but only by critical hits.
 *
 * What happens, is that when a player's health gets below 50% of
 * their max, the guards start using their special attack. The
 * special attack is basically striking their target in the side
 * of the head with the flat of their sword (note than an unarmed
 * guard cannot do this). If this attack inflicts a %hurt greater
 * than 10%, the opponent is rendered unconscious. The guard who
 * stunned will then drag the opponent off to jail.
 *
 * This part of the code is rather miserable and involved a lot
 * more work than I had intended originally. When a player is
 * knocked out, a paralyzer object is moved into their inventory.
 * The paralyzer object also adds a stunned prop to the player,
 * and adjusts their LIVE_I_SEE_DARK prop so that any incidental
 * messages they get (suck as an m_in of an npc wandering in) will
 * be like 'Someone arrives.', or everything will be dark if
 * they're forced to look for some reason.
 *
 * The actual movement of being dragged to jail involves the guard
 * walking back to the prison (this is possible by a function
 * defined in most rooms in Port Macdunn which give the direction
 * for the shortest route to jail). On the first move, the player
 * is teleported to a 'waiting room', and left there as the guard
 * wanders around the village. If the guard encounters another
 * player, then the unconscious player is brought into the guard's
 * environment until the guard is once again alone. Exit blocks
 * of any kind will prevent the guard from moving around, as will
 * the guard being in a fight.
 * Khail - June 15/97
 */
#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <cmdparse.h>
#include <composite.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/random.h"
#include "npc.h"

inherit STDHUMAN;

object captain,
       prisoner;
int drag_alarm;
int has_armed;

public void
set_wanderer()
{
    set_random_move(30);
    set_restrain_path(ROOM);
    set_monster_home(ROOM + "jail_garrison");
}

mixed
oke_to_move(string exit)
{
    if (prisoner)
        return 0;
    return ::oke_to_move(exit);
}
    
/*
 * Function name: arm_me
 * Description  : Clones in the guard's equipment
 *                and has him wear/wield it.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
arm_me()
{
    if (has_armed)
        return;
    
    equip(({
        WEP + "basket_sword",
        COM_ARM + "targe",
        COM_ARM + "vest_leather",
        COM_ARM + "belt",
        COMMON + "kilts/kilt_macdunn",
        COM_ARM + "bracers_hard_leather",
    }));
    
    command("lace vest");
    has_armed = 1;
}

/*
 * Function name: hook_return_intro
 * Description  : Called when someone introduces to us by the
 *                add_introduced hook in the knowledge base.
 *                Defined here only to prevent the guard from
 *                introducing himself (as he's a neverknown
 *                npc with no name.)
 * Arguments    : str - lowercase name of whoever intro'd.
 * Returns      : 1.
 */
public int
hook_return_intro(string str)
{
    return 1;
}

public string
act_1()
{
    object *wep;
    string desc;

    if (!sizeof(wep = query_weapon(-1)))
    {
        command("say What the...where'd my sword go?");
        return "";
    }

    desc = wep[0]->short();

    command("emote examines his " + desc + " carefully " +
        "and nods to himself in satisfaction.");
    return "";
}

public string
act_2()
{
    if (environment()->query_prop(ROOM_I_INSIDE))
    {
        command("emote paces around the room restlessly.");
        return "";
    }

    command("emote paces around restlessly.");
    return "";
}

public string
act_3()
{
    object *others;

    others = filter(all_inventory(environment()), &->id("guard"));
    others -= ({TO});

    if (!sizeof(others))
    {
        command("emote looks around carefully, apparently " +
            "unformfortable about being alone.");
        return "";
    }

    command("say to " + OB_NAME(others[0]) + " I think I'm going to "+
        "head to Murah's for an ale when the shift is over, " +
        "feel like coming along?");
    others[0]->command("say If you're buying, sure.");
    others[0]->command("grin");
    return "";
}

public string
act_4()
{
    object *masters,
           *others;

    masters = filter(all_inventory(environment()),
        &->is_khalakhor_blademaster());
    others = filter(all_inventory(environment()), &->id("guard"));
    others -= ({TO});

    if (!sizeof(masters))
    {
        command("say I wonder if some day I'll be good enough " +
            "with a sword to claim the title of Blademaster.");
        if (!sizeof(others))
            return "";
        else
            others->command("laugh");
        command("grumble");
        return "";
    }

    if (sizeof(masters) == 1)
    {
        masters[0]->catch_msg(QCTNAME(TO) + " stares at " +
            "you in awe and whispers: A Blademaster!\n");
        tell_room(environment(), QCTNAME(TO) + " stares at " +
            QTNAME(masters[0]) + " in awe and whispers: " +
            "A Blademaster!\n", masters);
        return "";
    }

    masters->catch_msg(QCTNAME(TO) + " stares at you in awe and " +
        "whispers: Blademasters!\n");
    tell_room(environment(), QCTNAME(TO) + " stares at " +
        COMPOSITE_LIVE(masters) + " in awe and whispers: " +
        "Blademasters!\n", masters);
    return "";
}

/*
 * Function name: create_khalakhor_human
 * Description  : Turns this object into a guard.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_human()
{
    set_name("guard");
    add_name("_port_macdunn_guard");
    add_name("man");
    set_adj(RANDOM_DETAILED_ADJS(TO));
    set_long("This man appears to be one of the village " +
        "guardsman. He's not a terribly formidable sight, " +
        "but the guards of Port Macdunn are more of a " +
        "military unit than anything else, so shouldn't " +
        "be underestimated.\n");

    default_config_npc(40);
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_WEP_SWORD, 70);

    set_alignment(200 + random(200));

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_random_size_descs();

    set_act_time(random(10) + random(10) + random(10));
    add_act("ponder");
    add_act(VBFC_ME("act_1"));
    add_act(VBFC_ME("act_2"));
    add_act(VBFC_ME("act_3"));
    add_act("peer");
    add_act(VBFC_ME("act_4"));
 
    arm_me();
}

public void
reset_arrest()
{
    prisoner = 0;
    remove_alarm(drag_alarm);
}

/*
 * Function name: move_guard
 * Description  : This function actually moves the guard around
 *                the village when dragging a prisoner to jail.
 *                The guard doesn't use the existing exits, but
 *                uses the information in them to move from room
 *                to room. This is to allow us to customize the
 *                messages delivered upon arriving/leaving. This
 *                function also takes into consideration blocked
 *                exits, so it should be possible for players to
 *                prevent team mates from being dragged away by
 *                blocking exits just as it normally would be.
 * Arguments    : dir - String which is the direction to travel.
 *                      This should be one of the exit cmds for
 *                      the normal exits available in the current
 *                      environment.
 * Returns      : n/a
 */
public void
move_guard(string dir)
{
  /* Always move the prisoner to the waiting room before */
  /* moving the guard. */
    if (present(prisoner, environment()))
    {
        prisoner->move_living("M", ROOM + "jail_waiting", 1, 1);
        present("_guard_stun_object", prisoner)->move(prisoner, 1);
    }
    tell_object(prisoner, "You dimly feel yourself being dragged " +
        "along the ground.\n");

  /* Move the guard in the right direction. */
    set_m_in("arrives, dragging an unconscious " +
        prisoner->query_race_name() + ".");
    set_m_out("drags an unconscious " + 
        prisoner->query_race_name());
    command(dir);
    set_m_in("arrives.");
    set_m_out("leaves");

  /* If there's any players in the new room, bring back the */
  /* prisoner. */
    if (sizeof(FILTER_PLAYERS(all_inventory(environment()))))
    {
        prisoner->move_living("M", environment(), 1, 1);
        present("_guard_stun_object", prisoner)->move(prisoner, 1);
    }
}

/*
 * Function name: init_living
 * Description  : Called when we meet another object.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
init_living()
{
    object stun_object;

    ::init_living();

  /* If the guard encounters a player, we'll bring the prisoner */
  /* back from the waiting room. */
    if (!prisoner)
        return;

    if (interactive(TP) && TP != prisoner &&
        environment() && !present(prisoner, environment()))
    {
        prisoner->move_living("M", environment(), 1, 1);
        present("_guard_stun_object", prisoner)->move(prisoner, 1);
    }        
}

/*
 * Function name: finalize_jailing
 * Description  : Called when the guard finally reaches the jail
 *                cells and is throwing the prisoner into one.
 * Arguments    : cell - Object pointer to the cell to throw
 *                       the prisoner into.
 * Returns      : n/a
 */
public void
finalize_jailing(object cell)
{
    string dir,
           cell_key_name;
    object door,
           stun_object;

  /* First, we find the direction of the cell, which key to use, */
  /* and which door to unlock based on the filename of the cell */
  /* we're throwing the prisoner into. */
    switch(file_name(cell))
    {
        case ROOM + "jail_cell_1":
            dir = "east";
            cell_key_name = "_cell_1_key";
            door = environment()->query_door();
            break;
        case ROOM + "jail_cell_2":
            dir = "east";
            cell_key_name = "_cell_2_key";
            door = environment()->query_east_door();
            break;
        case ROOM + "jail_cell_3":
            dir = "west";
            cell_key_name = "_cell_3_key";
            door = environment()->query_west_door();
    }

  /* Unlock the cell door if it's locked. */
    if (door->query_locked())
        command("$unlock " + dir + " door with " + cell_key_name);

  /* Open the cell door if it's closed. */
    if (!door->query_open())
        command("$open " + dir + " door");    

  /* Throw the person into the cell. */
    tell_room(environment(), QCTNAME(TO) + " throws " +
        QTNAME(prisoner) + " into the jail cell to the " + dir +
        ".\n", ({prisoner}));
    tell_room(cell, "Someone throws " + QTNAME(prisoner) +
        " into the cell with you!\n", ({prisoner}));
    prisoner->move_living("M", cell, 1, 1);
    present("_guard_stun_object", prisoner)->move(prisoner, 1);
    present("_guard_stun_object", prisoner)->set_recovery_time(60);

  /* Now we move the object that keeps the prisoner in jail */
  /* into the prisoners inventory. */
    reset_euid();
    door = clone_object(OBJ + "prison_timer");
    door->move(prisoner, 1);
    door->arrest_me(prisoner);

  /* Close and lock the cell door. */
    command("$close " + dir + " door");
    command("$lock " + dir + " door with " + cell_key_name);

    tell_room(environment(), QCTNAME(TO) + " returns to duty.\n");

  /* Since we've got nowhere better to go, we'll trans the */
  /* guard to the storage room and destruct him there, after */
  /* we return the cell keys to the captain of the prison. */
    move_living("M", ROOM + "jail_storage");
    if (captain)
        FIND_STR_IN_OBJECT("keys", TO)->move(captain,1);
    set_this_player(TO);
    remove_object();
}

/*
 * Function name: try_to_drag
 * Description  : This function is called by an alarm by itself
 *                and is what makes the guard move through the
 *                village, dragging an unconscious prisoner along
 *                with him. It also handles stuff like deciding
 *                which cell to throw the prisoner into, and
 *                strips them of appropriate items.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
try_to_drag()
{
    string dir,
           *dirs;
    object stun_object,
           *inv,
           *temparr,
           cell;
    int i;

  /* Obviously, we can't drag someone if they've managed */
  /* to vanish on us.  A player is considered to have 'vanished' */
  /* if they quit, aren't in the guard's environment, or aren't */
  /* in the waiting room. */
    if (!prisoner ||
        (!present(prisoner, environment()) &&
        file_name(environment(prisoner)) != ROOM + "jail_waiting"))
    {
        reset_arrest();
        return;
    }

  /* If the player's gone LD, we'll put the guard into a */
  /* sort of holding pattern, where he does nothing until */
  /* the player returns from being LD. */
    if (prisoner->query_linkdead())
    {
        reset_arrest();
        return;
    }

  /* First make sure the prisoner is still unconscious. */
  /* If the prisoner has regained consciousness, attack */
  /* them. */
    if (!(stun_object = present("_guard_stun_object", prisoner)))
    {
        command("$kill " + OB_NAME(prisoner));
        reset_arrest();
        return;
    }

  /* Guard can't drag anyone away while fighting, but will */
  /* keep trying every 5 seconds until no longer being */
  /* attacked. */
    if (query_attack())
    {
        if (get_alarm(drag_alarm))
            remove_alarm(drag_alarm);
        drag_alarm = set_alarm(5.0, 0.0, try_to_drag);
        return;
    }

  /* If we've reached the room where the jailer is, first */
  /* we'll forget about the prisoner if the jailer's gone. */
  /* If he's not gone, we'll try to get the keys from him, */
  /* and if we can't for some reason, keep trying every */
  /* few seconds until the prisoner wakes up. If we do */
  /* get the keys, strip the prisoner of the appropriate */
  /* items, and then head east to the actual cells. */
    if (file_name(environment()) == ROOM + "jail_corridor_1")
    {
      /* If the jailer's gone, the prisoner gets left here. */
        if (!(captain = present("_macdunn_jail_captain", environment())))
        {
            command("$confused");
            command("$emote shrugs and walks away.");
            move_living("M", ROOM + "jail_storage");
            remove_object();
            return;
        }

      /* Next we try to get the keys. */
        tell_room(environment(), QCTNAME(TO) + " asks " +
            QTNAME(captain) + " for the cell keys.\n", ({prisoner}));

      /* If the jailer doesn't have the keys, keep trying */
      /* every 10 seconds until the prisoner wakes up. */
        if (!captain->give_keys_to_guard(TO))
        {
            if (get_alarm(drag_alarm))
                remove_alarm(drag_alarm);
            drag_alarm = set_alarm(10.0, 0.0, try_to_drag);
            return;
        }

      /* Ok, we got the keys from the jailer. Now we strip */
      /* the player's inventory. */
      /* Strip prisoners of weapons, armour, containers and */
      /* cash. */
        temparr = all_inventory(prisoner);
        inv = filter(temparr, &->check_weapon());
        inv += filter(temparr, &->check_armour());
        inv += filter(temparr, &->query_prop(CONT_I_IN));
      /* Now we filter out the autoloaders, invis objects, etc. */
        inv = filter(inv, &not() @ &->query_auto_load());
        inv = filter(inv, &not() @ &->query_invis());
        inv = filter(inv, &not() @ &->query_prop(OBJ_M_NO_DROP));
        inv += filter(temparr, &->id("coin"));

      /* Now we tell the captain to store the equipment. */
        captain->store_equip(prisoner, inv, TO);

      /* Ok, we've gotten the cell keys and stripped the player */
      /* of their appropriate inventory. Now we go one room */
      /* east (to the first jail cell), and call this function */
      /* again to figure out what to do next. */
        move_guard("east");
        if (get_alarm(drag_alarm))
            remove_alarm(drag_alarm);
        drag_alarm = set_alarm(1.0, 0.0, try_to_drag);
        return;
    }

  /* What to do if we've reached the prison cells. */
  /* Here all we do is really decide which cell to */
  /* throw the player into. */
    if (file_name(environment()) == ROOM + "jail_corridor_2")
    {   
      /* Next we decide which cell to throw them into. We'll */
      /* use the first cell which has the fewest occupants. */
        temparr = allocate(3);
        for (i = 0; i < 3; i++)
        {
            dir = ROOM + "jail_cell_" + (i + 1);
            if (!(temparr[i] = find_object(dir)))
            {
                dir->load_me();
                temparr[i] = find_object(dir);
            }
            if (!cell ||
                sizeof(FILTER_LIVE(all_inventory(temparr[i]))) <
                sizeof(FILTER_LIVE(all_inventory(cell))))
            {
                cell = temparr[i];
            }
        }
      /* Next we actually throw players into cells. If the */
      /* destination cell isn't cell 1 (which should be off */
      /* the room the guard's now in), move south and do it, */
      /* where cells 2 and 3 are. */
        if (file_name(cell) == (ROOM + "jail_cell_1"))
        {
            finalize_jailing(cell);
            return;
        }
        else
        {
            move_guard("south");
            if (get_alarm(drag_alarm))
                remove_alarm(drag_alarm);
            set_alarm(5.0, 0.0, &finalize_jailing(cell));
            return;
        }   
    }             

  /* Looks like we haven't reached the prison yet, so keep */
  /* dragging the player around. */        
    if (!(dir = environment()->query_dir_to_jail()))
    {
        dirs = environment()->query_exit_cmds();
        dir = dirs[random(sizeof(dirs))];
    }

    move_guard(dir);

    if (get_alarm(drag_alarm))
        remove_alarm(drag_alarm);
    drag_alarm = set_alarm(5.0, 0.0, try_to_drag);
}

/*
 * Function name: special_attack
 * Description  : This is the guard's special attack, which has
 *                the capability of knocking a player unconscious.
 *                If this happens, it moves a special paralyzer
 *                into the target's inventory, stops all fighting,
 *                and the guard begins dragging the target to
 *                jail.
 * Arguments    : enemy - Object pointer to the current target.
 * Returns      : 0 - Did not use special, continue with a normal
 *                    attack.
 *                1 - Used stun special, no further attack this
 *                    round.
 */
public int
special_attack(object enemy)
{
    int i,
        dam,
        phit,
        do_stun,
        s_time;
    string message1,
           message2;
    object weapon,
           stun_object,
           *enemies;

  /* Attack will never be attempted until the enemy is down */
  /* to at least 50% of full health. */
    if (100 * enemy->query_hp() / enemy->query_max_hp() > 50)
        return 0;

  /* Attack can not be made if the npc has been disarmed. */
    if (!sizeof(query_weapon(-1)))
        return 0;

    weapon = query_weapon(-1)[0];

    enemy->catch_msg(QCTNAME(TO) + " swings the flat of his " +
        weapon->short() + " at your head!\n");
    tell_watcher(QCTNAME(TO) + " swing the flat of his " +
        weapon->short() + " at " + QTNAME(enemy) +
        "'s head!\n", enemy);

  /* The attack is actually normal damage for the guard's */
  /* sword and sword skill, except that it's a bludgeon */
  /* attack to the head. */    
    phit = enemy->hit_me(F_PENMOD(weapon->query_pen(),
        query_skill(SS_WEP_SWORD)), W_BLUDGEON, TO, -1, A_HEAD)[0];
    switch(phit)
    {
        case -1:
            message1 = "The blade narrowly misses your skill.\n";
            message2 = "The blade narrowly misses " + 
                HIS_HER(enemy) + " skull.\n";
            break;
        case 0:
            message1 = "The blade glances harmlessly off your " +
                "skull.\n";
            message2 = "The blade glances harmlessly off  " +
                HIM_HER(enemy) + " skull.\n";
            break;
        case 1..10:
            message1 = "The blade slaps against the side of " +
                "your head, leaving a ringing in your ears.\n";
            message2 = "The blade slaps against the side of " +
                HIS_HER(enemy) + " head.\n";
            break;
        case 11..99:
            message1 = "The blade slams against the side of " +
                "your skull, everything goes black, and " +
                "you lose consciousness!\n";
            message2 = "The blade slams against the side of " +
                HIS_HER(enemy) + " head, and " +
                HIS_HER(enemy) + " eyes roll back " +
                "as " + HE_SHE(enemy) + " falls to " +
                "the ground unconcsious!\n";
            do_stun = 1;
            break;
        default:
            message1 = "You feel bone crush beneath the weight " +
                "of the blade slamming into your skull!\n";
            message2 = "You hear a sickening crunch as " +
                HIS_HER(enemy) + " skull is " +
                "crushed by the attack!\n";
    }

    tell_object(enemy, message1);
    tell_watcher(message2, enemy);

  /* If the do_stun flag was set, we'll knock the target out. */
    if (do_stun)
    {
        reset_euid();
        stun_object = clone_object(OBJ + "guard_stun_object");
        stun_object->set_guard(TO);
        stun_object->move(enemy);
        s_time = phit * 20;  /* 220 to 1980 seconds */
        s_time -= enemy->query_stat(SS_CON) * 10;
      /* Never stun for less than 60 seconds. */
        s_time = (s_time < 60 ? 60 : s_time);
      /* Never stun for more than 5 minutes (300 seconds) */
        s_time = (s_time > 300 ? 300 : s_time);
        stun_object->set_recovery_time(s_time);
        enemies = enemy->query_enemy(-1) + ({});
        enemy->stop_fight(enemies);
        enemies->stop_fight(enemy);
        set_team_name("dragging_prisoner");
        command("leave");

      /* We only start dragging a new prisoner around if we */
      /* don't already have one. */
        if (!prisoner)
        {
            prisoner = enemy;
            if (get_alarm(drag_alarm))
                remove_alarm(drag_alarm);
            drag_alarm = set_alarm(2.0, 0.0, try_to_drag);
        }
    }

    if (enemy->query_hp() <= 0)
        enemy->do_die(TO);

    return 1;
}

public void
remove_object()
{
    if (prisoner &&
        file_name(environment(prisoner)) == ROOM + "jail_waiting")
    {
        prisoner->move_living("M", environment(), 1, 1);
        present("_guard_stun_object", prisoner)->move(prisoner, 1);
    }
    ::remove_object();
}

public void
come_assist_me(object victim, object attacker, string where)
{
    string *rooms,
           *cmds;
    int index;

    if (query_attack())
        return;

    if (!environment(TO))
        return;

    if (where != file_name(environment(TO)))
    {
        rooms = environment(TO)->query_exit_rooms();
        cmds = environment(TO)->query_exit_cmds();

        index = member_array(where, rooms);

        if (index < 0)
            return;
    
        command(cmds[index]);
    }
    command("kill " + OB_NAME(attacker));
}
        
