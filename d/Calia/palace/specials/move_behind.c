

int
is_attacking_this_living(object enemy, object tp)
{
    return enemy->query_attack() == tp;
}


void
reattack_object(object enemy, object friend)
{
    enemy->stop_fight(friend);
    enemy->attack_object(friend);
}


void
ready_to_move_behind_now(object tp)
{
    tp->remove_prop(CALIAN_I_JUST_MOVED_BEHIND);
    tp->catch_msg("You are ready to try to move behind again.\n");
}


void
cleanup_mb_info(object player)
{
    if (!objectp(player)) 
        return;

    player->remove_prop(OBJ_M_NO_ATTACK); 
}


/*
 * Function name:   behind_time_left
 * Description:     This is a support function which determines
 *                  how much time a Calian is "behind" another
 *                  friend.
 * Arguments:       object tp         - Person behind.
 *                  object friend     - Who tp is behind.
 *                  int start_time    - When tp moved behind friend.
 *                  int behind_time   - Default duration in seconds behind.
 * Returns:         ret > 0  : Is behind for ret seconds more.
 *                  ret <= 0 : Is *not* behind the friend no more.
 * 
 * Author:          Sir Rogon.
 */
private int 
behind_time_left(object tp, object friend, int start_time, int behind_time)
{
    if (living(tp) && living(friend) &&
        CAN_SEE_IN_ROOM(tp) && CAN_SEE(tp, friend))
        return start_time + behind_time - time(); 
    else
        return -1;
}


/* 
 * Function:     write_attack_mb_message 
 * Description:  Writes messages when someone who has moved behind 
 *               is attacked, telling those who do not have the 
 *               option set for "see fights" or "gagmisses" of 
 *               the attempted attack and its failure. 
 */ 
void 
write_attack_mb_message(object targ, object friend, object attacker) 
{
    object *liv = 
        FILTER_PLAYERS(all_inventory(environment(targ))) - 
        ({ targ, friend, attacker }); 
    int i; 

    for (i = 0; i < sizeof(liv); i++) { 
        if (!liv[i]->query_option(OPT_BLOOD) && 
            !liv[i]->query_option(OPT_GAG_MISSES)) { 
            tell_object(liv[i], attacker->query_The_name(liv[i]) + 
                " attempts to attack " + targ->query_the_name(liv[i]) + 
                " but " + targ->query_pronoun() + 
                " evades the onslaught with the help of " + 
                friend->query_the_name(liv[i]) + ".\n"); 
        } 
    } 

    if (!targ->query_option(OPT_BLOOD) && 
        !targ->query_option(OPT_GAG_MISSES)) { 
        tell_object(targ, attacker->query_The_name(targ) + 
            " attempts to attack you but you evade " + 
            "the onslaught with the help of " + 
            friend->query_the_name(targ) + ".\n"); 
    } 

    if (!friend->query_option(OPT_BLOOD) && 
        !friend->query_option(OPT_GAG_MISSES)) { 
        tell_object(friend, attacker->query_The_name(friend) + 
            " attempts to attack " + targ->query_the_name(attacker) + 
            " but " + targ->query_pronoun() + 
            " evades the onslaught with your help.\n"); 
    } 
}


/* 
 * Function name:   calian_is_behind 
 * Description:     This function is normally called as a value by function 
 *                  call. It should return a string if text == 1, the time 
 *                  left if text == 0. It used both for the properties 
 *                  OBJ_M_NO_ATTACK and "calian_is_attacked". 
 * Arguments:       tp - this player. 
 *                  friend - Who tp is behind. 
 *                  start_time - When tp moved behind friend. 
 *                  behind_time - For how long is he/she behind? 
 *                  text - Produce text (1) or time (0). 
 * Returns:         A text or the time left. 
 * 
 * Author:          Sir Rogon. 
 */
mixed
calian_is_behind(mixed tp, mixed friend, mixed start_time, mixed behind_time, 
                 mixed text)
{
    int time; 
    object attacker = this_player(); 

    /* Resolve string parameters with find_object() and atoi(). */
    if (stringp(tp)) 
	  tp = find_object(tp); 
    if (stringp(friend)) 
	  friend = find_object(friend); 
    start_time = atoi(start_time); 
    behind_time = atoi(behind_time); 
    text = atoi(text); 

    time = behind_time_left(tp, friend, start_time, behind_time); 
    if (time > 0) { 
	if (text) { 
          if (objectp(attacker) && 
              attacker != tp && 
              attacker != friend && 
              present(attacker, environment(tp))) { 
              write_attack_mb_message(tp, friend, attacker); 
          } 
	    return "That opponent has temporarily maneuvered out " + 
		     "of harm's way by moving behind.\n"; 
      } 
	else
	    return time;
    } 
    else 
	return 0;
}



/*
 * Function name: move_behind
 * Description:   executes the move behind command
 * Arguments:     str - predicate
 * Returns:       success
 */
int
move_behind(string str)
{
    string prep, friend_name, swarm_hand, vb, *tmp;
    object tp, this, friend, attacker, *team, *enemies;
    int number_enemies, tm;
    int mb, i, d, top_dex, total_for, total_against;

    if (!str)
        return 0;

    vb = query_verb(); 

    if (vb == "mbsw") {
        if (sizeof(tmp = explode(str, " "))) { 
            swarm_hand = tmp[sizeof(tmp)-1]; 
            switch (swarm_hand) {
                case "lhand" : 
                case "rhand" : 
                     if (sizeof(tmp) > 1) 
                         friend_name = implode(tmp[0..sizeof(tmp)-2], " ");
                     else
                         friend_name = "";  
                     break; 
                default : 
                     swarm_hand = 0; 
                     friend_name = str;
                     break; 
            }
        }
        else
            friend_name = str; 
    }
    else { 
        if (sscanf(str, "%s %s", prep, friend_name) != 2 || prep != "behind")
        {
            if (explode(str, " ")[0] == "behind")
                 NF("Move behind whom ?\n");
            else
                NF("Move what ?\n");
            return 0;
        }
    } 

    tp = TP;
    friend_name = lower_case(friend_name);
    friend = present(friend_name, environment(tp));
    if (!friend)
    {
        NF("Move behind whom ?\n");
        return 0;
    }

    if (!living(friend))
    {
        NF("You can only move behind living beings if you actually expect " +
            "to get away.\n");
        return 0;
    }

    tm = time();

    if (tm - tp->query_prop(CALIAN_I_LAST_ATTACK_TIME) < 3) {
        notify_fail("Having recently launched an attack " +
                    "you are not yet ready to move behind.\n"); 
        return 0; 
    }

    /* This code prevents the tactic known as `spiralling' which 
       can unbalance the attack/ */ 
    if ((tm - tp->query_prop(CALIAN_I_LAST_MBD_BY_AT_TIME)) <  
        (3 * (SWARM_PREP_TIME + SWARM_EXEC_TIME) / 2)) {  
        notify_fail("Someone moved behind you very recently, you " +
                    "may not use move behind just yet.\n"); 
        return 0;
    } 
    tp->remove_prop(CALIAN_I_LAST_MBD_BY_AT_TIME); 

    this = THIS;
    enemies = filter(all_inventory(environment(tp)), 
                     &is_attacking_this_living(,tp));
    number_enemies = sizeof(enemies);
    team = tp->query_team_others();

    attacker = tp->query_attack();

    /* Check for pigeons and such :) */ 
    if (objectp(present(attacker, tp))) { 
        notify_fail("You can't get away from something you are carrying!\n"); 
        return 0;
    } 

    if (!(mb = tp->query_skill(SS_MOVE_BEHIND))) {
        notify_fail("You have no skill in moving behind team members during " +
                    "battle!\n");
        return 0;
    }
    else if (!number_enemies) {
        notify_fail("No-one is attacking you!\n");
        return 0;
    }
    else if (!sizeof(team)) {
        notify_fail("You are not a member of a team.\n");
        return 0;
    }
    else if (member_array(friend, team) == -1) {
        tp->catch_msg(QCTNAME(friend) + " is not a member of your team.\n");
        return 1;
    }
    else if (tp->query_prop(CALIAN_I_JUST_MOVED_BEHIND)) {
        notify_fail("You are not ready to try to move behind anyone again " +
                    "yet.\n");
        return 0;
    }
    else 
    { 
        tp->add_prop(CALIAN_I_JUST_MOVED_BEHIND, 1); 

        /* Estimate most powerful enemy */ 
        top_dex = 0; 
        for (i = 0; i < sizeof(enemies); i++) 
            if ((d = enemies[i]->query_stat(SS_DEX)) > top_dex)  { 
                 attacker = enemies[i]; 
                 top_dex = d; 
             } 

        total_for = 
          ((mb * (tp->query_stat(SS_DEX) + 
                  tp->query_stat(SS_WIS) + 
                  tp->query_stat(SS_INT) + 
                  friend->query_stat(SS_STR) + 
                  friend->query_stat(SS_DIS))) / 100); 

        total_against = (top_dex + attacker->query_stat(SS_WIS) + 
                        (number_enemies * 16)); 

        if ((random(total_for) + mb)  > random(total_against)) 
        {
            map(enemies, &reattack_object(,friend));
            tp->catch_msg("You move behind " + QTNAME(friend) +
                " and your enemies move to attack " +
                friend->query_objective() + ".\n");
            friend->catch_msg(QCNAME(tp) + " moves behind you, and " +
                tp->query_possessive() + " enemies move to attack you!\n");
            tell_room(environment(tp), QCTNAME(tp) + " moves behind " +
                QTNAME(friend) + ", who is attacked by " +
                tp->query_possessive() +
                " enemies!\n", ({ tp, friend }) );

	    /* Setting up the OBJ_M_NO_ATTACK prop as VBFC. */
            tp->add_prop(OBJ_M_NO_ATTACK,
			 "@@calian_is_behind:" +    // Function name
			 file_name(this) + "|" +    // Object/file name
			 file_name(tp) + "|" +      // tp
			 file_name(friend) + "|" +  // friend
			 tm + "|" +             // start time
			 MB_NO_ATTACKED_TIME + "|" +     // behind time
			 1 + "@@");                 // Produce text.

            /* After a successful move behind, one may not 
               move behind again for twice the period for which
               one may not be attacked.. this ensures against 
               "invulnerability" */ 
            set_alarm(itof(MB_NO_ATTACKED_TIME * 2), 0.0, 
                             &ready_to_move_behind_now(tp));

            set_alarm(itof(MB_NO_ATTACKED_TIME), 0.0, 
                      &cleanup_mb_info(tp));  

            if (is_calian(friend)) 
                friend->add_prop(CALIAN_I_LAST_MBD_BY_AT_TIME, tm); 

            if (vb == "mbsw")  { 
                set_this_player(tp); 
                return swarm(swarm_hand);  
            } 
	}
        else { 
            write("The enemy onslaught is too overwhelming for you " +
                  "to manuever.\n");
            set_alarm(itof(MOVE_BEHIND_DELAY), 0.0, 
                             &ready_to_move_behind_now(tp));
        } 
    }

    return 1;
}
