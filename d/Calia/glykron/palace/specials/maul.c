
/* Change maul state, updates the maul state for a player */
void
change_maul_state(object tp, int state)
{
    tp->add_prop(CALIAN_I_MAUL_STATE, state);
}

void
ready_to_maul_now(object tp)
{
    change_maul_state(tp, PRE_PREPARE);
    tell_object(tp, "You are ready to maul again.\n");
}

/* Return maul state of the player */
int
maul_state(object tp)
{
    return (tp->query_prop(CALIAN_I_MAUL_STATE));
}

int
is_attacking(object player, object enemy)
{
    return (player->query_attack() == enemy); 
}

/* 
 * At the moment I prefer to use add_stun() 
 * because of problems with add_attack_delay() 
 */ 
void
take_stun(object enemy)
{
    enemy->remove_stun(); 
}

void
deal_stun(object enemy)
{
     if (!objectp(enemy)) 
         return;

     enemy->add_stun();  
     set_alarm(MAUL_ATTACK_DELAY, 0.0, &take_stun(enemy)); 
}

/* Carry out maul after preparation */
void
calian_maul_enemy(object tp, object enemy, object weapon)
{
    object *team, *calians, *calian_enemies, *enemies;
    string weapon_desc, *hit_descr, hit_piece; 
    int st, p, d, ms; 
    mixed hit;

    if (!objectp(tp)) 
        return; 

    if (!objectp(enemy) || !present(enemy, environment(tp))) { 
        tell_object(tp, "You can no longer see the enemy you were " +
                        "preparing to maul.\n");
        change_maul_state(tp, PRE_PREPARE);
        return;
    }

    if (enemy != tp->query_attack()) { 
        tell_object(tp, 
                    "You are no longer fighting your maul target.\n");
        change_maul_state(tp, PRE_PREPARE);
        return;
    }

    if (!objectp(weapon) || weapon->query_wielded() != tp) {
        tell_object(tp, "You're not wielding the same weapon " +
           "as when you prepared to maul.\n"); 
        change_maul_state(tp, PRE_PREPARE);
        return;
    }

    if (tp->query_prop(LIVE_I_ATTACK_DELAY) || 
        tp->query_prop(LIVE_I_STUNNED)) {
        tell_object(tp, "You are currently stunned so you can't maul!\n");
        change_maul_state(tp, PRE_PREPARE);
        return 0;
    }

    if (tp->query_mana() < (MAUL_MANA + 1)) { 
        tell_object(tp, "You are too mentally exhausted to maul.\n"); 
        change_maul_state(tp, PRE_PREPARE);
        return 0;
    } 

    if (tp->query_fatigue() < (MAUL_FATIGUE + 1)) { 
        tell_object(tp, "You are too physically exhausted to maul.\n"); 
        change_maul_state(tp, PRE_PREPARE);
        return 0;
    } 

    weapon_desc = weapon->short(); 
    team = FILTER_PRESENT_LIVE(tp->query_team_others()); 

    change_maul_state(tp, JUST_MAULED);
    set_alarm(itof(MAUL_EXEC_TIME), 0.0, &ready_to_maul_now(tp));

    tp->add_mana(-MAUL_MANA); 
    tp->add_fatigue(-MAUL_FATIGUE); 

    p = (weapon->query_pen() + (tp->query_stat(SS_STR) / 2)) / 2; 
    if (p > 66) 
        p = 66; 
    else if (p < 24)
        p = 24; 

    /* basic multiplier for weapon pen (%age) */
    d = 50;

    /* Closeness at start of move bonus, this applies
       if solo or in front line of team. */ 
    if (enemy->query_attack() == tp) 
        d += 10; 

    /* sword bonus  */
    if (weapon->query_wt() == W_SWORD) 
        d += 10;

    enemies = filter(map(team, &->query_attack()), objectp);
    /* bonus if you are in a team that is fighting your enemy */ 
    if (sizeof(enemies) && (member_array(enemy, enemies) > -1))  { 
        d += 35; 
        /* bonus if a fellow Calian is in your team fighting the enemy */
        if (sizeof(calians = filter(team, is_calian))) {
            calian_enemies = 
                filter(map(calians, &->query_attack()), objectp);
            if (sizeof(calian_enemies) &&
                (member_array(enemy, calian_enemies) > -1))
                d += 10;
        }
    } 

    /* water penalties 
    if (IN_DEEP_WATER(tp) || UNDER_WATER(tp)) 
        d = (d * tp->query_skill(SS_SWIM) / 100);
    */

    /* final pen calculation */
    p = (p * d) / 100;

    if (tp->query_combat_object()->cb_tohit(
                     weapon->query_attack_id(), 
                     (25 * weapon->query_hit()) / 8, 
                     enemy) >= 0) {
        hit = enemy->hit_me(F_PENMOD(p, tp->query_skill(SS_MAUL)),
                            W_SLASH, tp, -1);
        hit_piece = hit[1];

        st = 0; 

        if (enemy->query_hp() < 1)
            hit_descr = ({ "kill" });
        else if (hit[0] == 0)
            hit_descr = ({ "tickle", "tickles", " over", 
                           "an ineffective drive" });
        else if (hit[0] < 5)
            hit_descr = ({ "graze", "grazes", " over", 
                           "a weak drive" });
        else if (hit[0] < 10)
            hit_descr = ({ "slash", "slashes", " across", 
                           "a determined drive" });
        else if (hit[0] < 15) { 
            hit_descr = ({ "rip", "rips", " into",
                           "a vicious drive" }); 
            deal_stun(enemy); 
            st = 1; 
        } 
        else if (hit[0] < 25) { 
            hit_descr = ({ "maul", "mauls", "", 
                           "a destructive drive"});
            deal_stun(enemy); 
            st = 1; 
        } 
        else if (hit[0] < 50) { 
            hit_descr = ({ "shred", "shreds", "", 
                           "a mighty drive" }); 
            deal_stun(enemy); 
            st = 1; 
        } 
        else { 
            hit_descr = ({ "splinter", "splinters", "",  
                           "a deadly drive" }); 
            deal_stun(enemy); 
            st = 1; 
        } 
        if (tp->query_wiz_level())
             tell_object(tp, "Pen on this maul was: " + p + ". " +
                         "Damage % was: " + hit[0] + ".\n" +
                         "Hit point damage was: " + hit[3] + ".\n" + 
                         "Stun: " + (st == 1 ? "yes" : "no") + ".\n"); 
    }
    else
        hit_descr = ({ "miss" });

    if (hit_descr[0] == "miss") {
        tell_object(tp, "You try to rip into " + enemy->query_the_name(tp) +
                    " with your " + weapon_desc + " but miss.\n");
        if (interactive(enemy))
            tell_object(enemy, tp->query_The_name(enemy) + " tries to " +
                        "rip into you with " + tp->query_possessive() + 
                        " " + weapon_desc + " but misses.\n");
        special_tell_watcher(QCTNAME(tp) + " tries to rip into " +
                  QTNAME(enemy) + " with " + tp->query_possessive() + 
                  " " + weapon_desc + " but misses.\n",
                  tp, enemy, 0);
    }
    else if (hit_descr[0] == "kill") {
        tell_object(tp, "You maul " + enemy->query_the_name(tp) + 
                  " to death with your " + weapon_desc + "!\n");
        if (interactive(enemy))
            tell_object(enemy, tp->query_The_name(enemy) + " mauls " + 
                      "you to death with " + tp->query_possessive() + 
                      " " + weapon_desc + "!\n");
        special_tell_watcher(QCTNAME(tp) + " mauls " +
                  QTNAME(enemy) + " to death with " + 
                  tp->query_possessive() + " " + weapon_desc +
                  "!\n", tp, enemy, 0); 
    }
    else { 
         tell_object(tp, "With " + hit_descr[3] + " of your " +
            weapon_desc + " you " + hit_descr[0] + hit_descr[2] + " " + 
            enemy->query_the_name(tp) + "'s " + hit_piece + ".\n");  
         if (st)  
            tell_object(tp, "You feel that you got in a stunning maul!\n"); 

         if (interactive(enemy)) { 
             tell_object(enemy, "With " + hit_descr[3] + " of " + 
                 tp->query_possessive() + " " + weapon_desc + " " + 
                 tp->query_the_name(enemy) + " " + hit_descr[1] + 
                 hit_descr[2] + " your " + hit_piece + ".\n"); 
             if (st)  
                 tell_object(enemy, "You feel stunned!\n"); 
         } 

         special_tell_watcher("With " + hit_descr[3] + " of " +
             tp->query_possessive() + " " + weapon_desc + " " + 
             QTNAME(tp) + " " + hit_descr[1] + hit_descr[2] + " " + 
             QTNAME(enemy) + "'s " + hit_piece + 
             ".\n", tp, enemy, 0);
    }

    if (enemy->query_hp() < 1)
        enemy->do_die(tp);
}


/*
 * Function name: maul
 * Description:   executes the maul command
 * Arguments:     str - predicate
 * Returns:       success
 */
int
maul(string str)
{
    object tp, enemy, weapon; 
    int ms, dt; 
    string nam; 

    tp = TP;

    ms = swarm_state(tp);

    if (ms != PRE_PREPARE) { 
        notify_fail("You may not maul while you are involved in " +
                    "any stage of a swarm.\n"); 
        return 0;
    } 

    ms = maul_state(tp); 

    if (ms == PREPARING) {
        notify_fail("You are currently preparing to maul.\n");
        return 0;
    }

    if (ms == JUST_MAULED) {
        notify_fail("You have only just mauled.\n");
        return 0;
    }

    if (nam = environment(tp)->query_prop(ROOM_M_NO_ATTACK) ) {
        if (stringp(nam)) {
            notify_fail(nam);
            change_maul_state(tp, PRE_PREPARE);
            return 0;
        }
        else {
            notify_fail("A magical force prevents you from mauling.\n");
            change_maul_state(tp, PRE_PREPARE);
            return 0;
        }
    }

    if (tp->query_prop(LIVE_I_ATTACK_DELAY) || 
        tp->query_prop(LIVE_I_STUNNED)) {
        notify_fail("You are currently stunned so you can't maul!\n");
        change_maul_state(tp, PRE_PREPARE);
        return 0;
    }

    if (!strlen(str))
        str = "none"; 
    else if ((str != "rhand") && (str != "lhand")) {  
        notify_fail("Maul with what hand? [lhand/rhand]\n");
        change_maul_state(tp, PRE_PREPARE);
        return 0;
    }

    weapon = query_main_weapon(tp, str);

    if (!objectp(weapon)) {
        notify_fail("You cannot maul your enemy without a weapon!\n");
        change_maul_state(tp, PRE_PREPARE);
        return 0;
    }

    dt = weapon->query_dt();
    if (!(dt & W_SLASH)) {
        notify_fail("You can't maul with a weapon that can't slash.\n");
        change_maul_state(tp, PRE_PREPARE);
        return 0;
    }

    if (!tp->query_skill(SS_MAUL)) {
        notify_fail("You are not skilled in mauling!\n");
        change_maul_state(tp, PRE_PREPARE);
        return 0;
    }

    if (COUNCIL_CODE->is_swarm_banned(tp)) {
        notify_fail("The Calian Council has banned you from mauling.\n");
        change_maul_state(tp, PRE_PREPARE);
        return 0;
    }

    if (tp->query_mana() < (MAUL_MANA + 1)) { 
        notify_fail("You are too mentally exhausted to maul.\n"); 
        change_maul_state(tp, PRE_PREPARE);
        return 0;
    } 

    if (tp->query_fatigue() < (MAUL_FATIGUE + 1)) { 
        notify_fail("You are too physically exhausted to maul.\n"); 
        change_maul_state(tp, PRE_PREPARE);
        return 0;
    } 

    if (!objectp(enemy = tp->query_attack())) {
        tp->command("$assist"); /* Will assist a fellow team member */
        if (!objectp(enemy = tp->query_attack())) {
            notify_fail("You are not fighting anyone.\n");
            change_maul_state(tp, PRE_PREPARE);
            return 0;
        }
    }

    if (ms == PRE_PREPARE) {
        change_maul_state(tp, PREPARING);
        tell_object(tp, "You prepare to maul " + 
                      enemy->query_the_name(tp) + " with " + 
                      "your " + weapon->short() + ".\n");
        set_alarm(itof(MAUL_PREP_TIME), 0.0, 
                    &calian_maul_enemy(tp, enemy, weapon));
        return 1;
    }

    tell_object(tp, "Maul is buggy!\n"); 
    return 1;
}
