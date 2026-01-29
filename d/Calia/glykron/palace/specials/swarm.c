
/* 
    This is the swarm include file that goes into the calian cmdsoul.  
 */

/*
 * This is a tell_watcher that takes into account the
 * Calian "see specials" option.
 */ 
void
special_tell_watcher(string str, object me, object enemy, mixed notell)
{
    object *ob;
    int i, size;

    ob = all_inventory(environment(me)) - ({ me, enemy });

    if (pointerp(notell))
        ob -= notell;

    /* We only display combat messages to interactive players. */
    ob = FILTER_PLAYERS(ob);

    i = -1;
    size = sizeof(ob);

    while(++i < size)
    {
        if ((!ob[i]->query_option(OPT_BLOOD) ||
             (ob[i]->query_skill(CALIAN_OPTIONS) & CALOPT_SEE_SPECIALS))
             && CAN_SEE_IN_ROOM(ob[i]))
        {
            if (CAN_SEE(ob[i], me))
                ob[i]->catch_msg(str);
            else
                tell_object(ob[i], enemy->query_The_name(ob[i]) +
                    " is hit by someone.\n");
        }
    }
}


/* 
 * query_main_weapon returns the main weapon or the weapon 
 * which is specified by the player in the string p.
 */ 
object
query_main_weapon(object living, string p)
{
    object weapon; 

    if (p == "lhand") {
        if (objectp(weapon = living->query_weapon(W_LEFT)))
            return weapon; 

        if (objectp(weapon = living->query_weapon(W_RIGHT)))
            return weapon; 

        return living->query_weapon(W_BOTH); 
    } 

    if (objectp(weapon = living->query_weapon(W_RIGHT)))
        return weapon; 

    if (objectp(weapon = living->query_weapon(W_LEFT)))
        return weapon; 

    return living->query_weapon(W_BOTH); 
}


int
kill_access(object ob)
{
    if (!living(ob) || ob->query_ghost() || ob == TP)
        return 0;

    return 1;
}


/* Change swarm state, updates the swarm state for a player */
void
change_swarm_state(object tp, int state)
{
    tp->add_prop(CALIAN_I_SWARM_STATE, state);
}

void
ready_to_swarm_now(object tp)
{
    change_swarm_state(tp, PRE_PREPARE);
    tell_object(tp, "You are ready to swarm again.\n");
}


/* Carry out swarm after preparation */ 
void 
calian_swarm_enemy(object tp, object enemy, object weapon) 
{ 
    object *calians, *enemies, *calian_enemies, enemy_target, 
           *team, piece; 
    string enemy_race, weapon_desc, *piece_names, 
           *hit_descr, hit_piece;  
    int x, *ids, p, d, ss, dismember; 
    mixed hit, *loc; 

    if (!objectp(tp)) 
        return; 

    if (!objectp(enemy) || 
        !present(enemy, environment(tp))) { 
        tell_object(tp, "You can no longer see the enemy you were " +
                        "preparing to swarm.\n");
        change_swarm_state(tp, PRE_PREPARE);
        return;
    }

    if (enemy != tp->query_attack()) {
        tell_object(tp, 
            "You are no longer attacking your swarm target.\n");
        change_swarm_state(tp, PRE_PREPARE);
        return;
    }

    if (!objectp(weapon) || weapon->query_wielded() != tp) {
        tell_object(tp, "You're not wielding the same weapon " +
                   "as when you prepared to swarm.\n"); 
        change_swarm_state(tp, PRE_PREPARE);
        return;
    }

    if (!sizeof(team = tp->query_team_others())) {
        tell_object(tp, "You are not in a team!\n");  
        change_swarm_state(tp, PRE_PREPARE);
        return 0;
    }

    if (enemy->query_attack() == tp) {
        tell_object(tp, 
            "Your enemy is paying too much attention for you " +
            "to swarm " + enemy->query_objective() + ".\n");
        change_swarm_state(tp, PRE_PREPARE);
        return 0;
    }

    if (tp->query_prop(LIVE_I_ATTACK_DELAY) || 
        tp->query_prop(LIVE_I_STUNNED)) { 
        tell_object(tp, "You are currently stunned so you can't swarm!\n"); 
        change_swarm_state(tp, PRE_PREPARE);
        return 0;
    } 

    set_this_player(tp); 
    if (!sizeof(team = FILTER_PRESENT_LIVE(team))) {
        tell_object(tp, "None of your team is present!\n"); 
        change_swarm_state(tp, PRE_PREPARE);
        return 0;
    }

    if (!sizeof(enemies = filter(map(team, &->query_attack()), objectp))) { 
        tell_object(tp, "None of your present team members are fighting!\n"); 
        change_swarm_state(tp, PRE_PREPARE); 
        return 0; 
    }

    if (tp->query_mana() < (SWARM_MANA + 1)) { 
        tell_object(tp, "You are too mentally exhausted to swarm.\n"); 
        change_swarm_state(tp, PRE_PREPARE);
        return 0;
    } 

    if (tp->query_fatigue() < (SWARM_FATIGUE + 1)) { 
        tell_object(tp, "You are too physically exhausted to swarm.\n");  
        change_swarm_state(tp, PRE_PREPARE); 
        return 0; 
    } 

    weapon_desc = weapon->short(); 

    change_swarm_state(tp, JUST_SWARMED); 
    set_alarm(itof(SWARM_EXEC_TIME), 0.0, &ready_to_swarm_now(tp)); 

    tp->add_mana(-SWARM_MANA); 
    tp->add_fatigue(-SWARM_FATIGUE); 

    if (tp->query_combat_object()->cb_tohit( 
                     weapon->query_attack_id(), 
                     (25 * weapon->query_hit()) / 8, 
                     enemy) >= 0)  { 
        /* basic multiplier for weapon pen (%age) */ 
        d = 120; 

        /* polearm bonus  */ 
        if (weapon->query_wt() == W_POLEARM) 
            d += 20; 

        /* bonus if a Calian is in your team and fighting the enemy */ 
        /* Find enemies who fellow Calians are fighting */ 
        if (sizeof(calians = filter(team, is_calian))) { 
            calian_enemies = filter(map(calians, &->query_attack()), objectp); 
            if (sizeof(calian_enemies) && 
                (member_array(enemy, calian_enemies) > -1))
                d += 20; 
        }  

        /* Rogue tanker penalty */ 
        if (member_array(enemy_target = enemy->query_attack(), team) == -1) { 
            tell_object(tp, "You find it hard to coordinate your " +
                            "swarm attack with " + 
                            enemy_target->query_the_name(tp) + ".\n"); 
            d = d / 3; 
        } 

        /* water penalties  
        if (IN_DEEP_WATER(tp) || UNDER_WATER(tp)) 
            d = (d * tp->query_skill(SS_SWIM) / 100); 
        */ 
        /* pen calculation */ 
        p = ((weapon->query_pen() * d) / 100) + 
            min(tp->query_stat(SS_DEX) / 12, 16); 
        hit = enemy->hit_me(F_PENMOD(p, tp->query_skill(SS_SWARM)),  
                            W_IMPALE, tp, -1); 

        hit_piece = hit[1]; 
        if (tp->query_wiz_level()) 
            tell_object(tp, "Pen on this swarm was: " + p + ". " + 
                            "Damage was: " + hit[3] + ".\n"); 

        if (enemy->query_hp() < 1)
            hit_descr = ({ "dismembered" });
        else if (hit[0] == 0)
            hit_descr = impale[0]; 
        else if (hit[0] < 5)
            hit_descr = impale[1];
        else if (hit[0] < 10)
            hit_descr = impale[2]; 
        else if (hit[0] < 25)
            hit_descr = impale[3]; 
        else if (hit[0] < 50)
            hit_descr = impale[4]; 
        else
            hit_descr = impale[5]; 
    }
    else
        hit_descr = ({ "miss" });

    if (hit_descr[0] == "miss") {
        tell_object(tp, "You fail to sneak around " + 
                      enemy->query_the_name(tp) + "'s defences.\n");
        if (interactive(enemy))
            tell_object(enemy, tp->query_The_name(enemy) + " fails to " +
                        "sneak around your defences.\n");
        special_tell_watcher(QCTNAME(tp) + " fails to sneak " +
                  "around " + QTNAME(enemy) + "'s defences.\n",
                  tp, enemy, 0);
    }
    else if (hit_descr[0] == "dismembered") {
        dismember = (!enemy->query_prop(LIVE_I_NO_CORPSE) && 
                    (tp->query_skill(CALIAN_OPTIONS) & CALOPT_DISMEMBER)); 

        if (!dismember) { 
            tell_object(tp, "You hit " + enemy->query_the_name(tp) + 
                         " with a thunderous blow of your " + 
                         weapon_desc + "!\n");
            if (interactive(enemy))
                tell_object(enemy, tp->query_The_name(enemy) + 
                         " hits you with a thunderous blow of " + 
                          tp->query_possessive() + " " + weapon_desc + 
                          "!\n");
            special_tell_watcher(QCTNAME(tp) + " hits " +
                      QTNAME(enemy) + " with a thunderous blow of " + 
                      tp->query_possessive() + " " + weapon_desc +
                      "!\n", tp, enemy, 0); 
        }
        else {
            tell_object(tp, "You dismember " + enemy->query_the_name(tp) + 
                         " with a fatal blow of your " + weapon_desc + 
                         ". Pieces fly everywhere!\n");
            if (interactive(enemy))
                tell_object(enemy, tp->query_The_name(enemy) + 
                          " dismembers you with a fatal blow of " + 
                          tp->query_possessive() + " " +
                          weapon_desc + ". Pieces fly everywhere!\n");
            special_tell_watcher(QCTNAME(tp) + " dismembers " +
                          QTNAME(enemy) + " with a fatal blow of " + 
                          tp->query_possessive() + " " + weapon_desc +
                          ". Pieces fly everywhere!\n", tp, enemy, 0); 
        }
    }
    else { 
         tell_object(tp, "You sneak around " + enemy->query_the_name(tp) + 
                 "'s defences" + hit_descr[1] + enemy->query_possessive() + 
                 " " + hit_piece + " with your " + weapon_desc + ".\n");

         if (interactive(enemy))
             tell_object(enemy, tp->query_The_name(enemy) + 
                 " sneaks around your defences" + hit_descr[0] + 
                 "your " + hit_piece + " with " + tp->query_possessive() + 
                 " " + weapon_desc + ".\n");

         special_tell_watcher(QCTNAME(tp) + " sneaks around " +
                       QTNAME(enemy) + "'s defences" + hit_descr[0] +
                      enemy->query_possessive() + " " + hit_piece +
                      " with " + tp->query_possessive() + " " + weapon_desc +
                      ".\n", tp, enemy, 0);
    }

    if (enemy->query_hp() < 1) {
        if (dismember) {
         /* get hitloc strings ready for pieces */
            ids = ({ });
            ids += (enemy->query_combat_object())->query_hitloc_id();
            piece_names = ({ });
            for (x = 0; x < sizeof(ids); x++) {
               loc = (enemy->query_combat_object())->query_hitloc(ids[x]);
               if (stringp(loc[2])) 
                    piece_names += ({ loc[2] });
            }

            enemy->add_prop(LIVE_I_NO_CORPSE, 1);
            enemy_race = enemy->query_race_name();

            enemy->do_die(tp);
            setuid();
            seteuid(getuid(this_object()));
            for (x = 0; x < sizeof(piece_names); x++) {
                piece = clone_object("/std/leftover");
                piece->leftover_init(piece_names[x], enemy_race);
                piece->move(environment(tp), 0);
            }
        } 
        else
            enemy->do_die(tp);
    }
}


/* Return swarm state of the player */
int
swarm_state(object tp)
{
    return (tp->query_prop(CALIAN_I_SWARM_STATE));
}


int
filter_attack_team(object player, object enemy)
{
    return (player->query_attack() == enemy); 
}


/*
 * Function name: swarm
 * Description:   executes the swarm command
 * Arguments:     str - predicate
 * Returns:       success
 */
int
swarm(string str)
{
    object tp, enemy, weapon, *team, *enemies; 
    int ss, dt; 
    string nam; 

    tp = TP;

    ss = maul_state(tp);

    if (ss != PRE_PREPARE)  { 
        notify_fail("You may not swarm while you are involved in " + 
                    "any stage of a maul.\n"); 
        return 0;
    } 

    ss = swarm_state(tp); 
    if (ss == PREPARING) {
        notify_fail("You are currently preparing to swarm.\n");
        return 0;
    }

    if (ss == JUST_SWARMED) {
        notify_fail("You have only just swarmed.\n");
        return 0;
    }

    if (nam = environment(tp)->query_prop(ROOM_M_NO_ATTACK) ) { 
        if (stringp(nam)) {
            notify_fail(nam);
            change_swarm_state(tp, PRE_PREPARE);
            return 0;
        }
        else {
            notify_fail("A magical force prevents you from swarming.\n");
            change_swarm_state(tp, PRE_PREPARE);
            return 0;
        }
    }

    if (tp->query_prop(LIVE_I_ATTACK_DELAY) || 
        tp->query_prop(LIVE_I_STUNNED)) { 
        notify_fail("You are currently stunned so you can't swarm!\n"); 
        change_swarm_state(tp, PRE_PREPARE);
        return 0;
    } 

    if (!strlen(str)) 
        str = "any"; 
    else if ((str != "rhand") && (str != "lhand")) {  
        notify_fail("Swarm with what hand? [lhand/rhand]\n");
        change_swarm_state(tp, PRE_PREPARE);
        return 0;
    }

    if (!objectp(weapon = query_main_weapon(tp, str))) {
        notify_fail("You cannot swarm your enemy without a weapon!\n");
        change_swarm_state(tp, PRE_PREPARE);
        return 0;
    }

    dt = weapon->query_dt();
    if (!(dt & W_IMPALE)) { 
        notify_fail("You can't swarm with a weapon that can't impale.\n");  
        change_swarm_state(tp, PRE_PREPARE);
        return 0;
    } 

    if (!tp->query_skill(SS_SWARM)) {
        notify_fail("You are not skilled in swarming!\n");
        change_swarm_state(tp, PRE_PREPARE);
        return 0;
    }

    seteuid(getuid()); 
    if (COUNCIL_CODE->is_swarm_banned(tp)) {
        notify_fail("The Calian Council has banned you from swarming.\n");
        change_swarm_state(tp, PRE_PREPARE);
        return 0;
    }

    if (tp->query_mana() < (SWARM_MANA + 1)) { 
        notify_fail("You are too mentally exhausted to swarm.\n"); 
        change_swarm_state(tp, PRE_PREPARE);
        return 0;
    } 

    if (tp->query_fatigue() < (SWARM_FATIGUE + 1)) { 
        notify_fail("You are too physically exhausted to swarm.\n"); 
        change_swarm_state(tp, PRE_PREPARE);
        return 0;
    } 

    /* To avoid the swarmer's paradox you need to swarm an enemy who is not 
       attacking someone who is attacking someone who is attacking you, 
       which results in a knot. That sentence is not a typo! */ 
    if (!objectp(enemy = tp->query_attack()) || 
        (((enemy->query_attack())->query_attack())->query_attack() == tp)) { 
        tp->command("$assist"); /* Will assist a fellow team member */ 
        if (!objectp(enemy = tp->query_attack())) { 
            notify_fail("You are not fighting.\n"); 
            change_swarm_state(tp, PRE_PREPARE); 
            return 0; 
        } 
    } 

    if (enemy->query_attack() == tp) {
        notify_fail("Your enemy is paying too much attention for you " +
            "to swarm " + enemy->query_objective() + ".\n");
        change_swarm_state(tp, PRE_PREPARE);
        return 0;
    }

    if (!sizeof(team = tp->query_team_others())) {
        notify_fail("You are not in a team!\n");  
        change_swarm_state(tp, PRE_PREPARE);
        return 0;
    }

    if (!sizeof(team = FILTER_PRESENT_LIVE(team))) {
        notify_fail("None of your fellow team members are present!\n");  
        change_swarm_state(tp, PRE_PREPARE);
        return 0;
    }

    if (!sizeof(enemies = filter(map(team, &->query_attack()), objectp))) { 
        notify_fail("None of your present team members are fighting!\n"); 
        change_swarm_state(tp, PRE_PREPARE);
        return 0;
    }

    if (ss == PRE_PREPARE) {
        change_swarm_state(tp, PREPARING);
        tell_object(tp, 
            "You prepare to swarm " + enemy->query_the_name(tp) + 
            " with your " + weapon->short() + ".\n");
        set_alarm(itof(SWARM_PREP_TIME), 0.0, 
                   &calian_swarm_enemy(tp, enemy, weapon));
        return 1;
    }

    tell_object(tp, "Swarm is buggy!\n"); 
    return 1; 
}

