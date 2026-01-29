
/* 
 * Function:      get_duel_related_target 
 * Description:   Returns an array of targets parsed for a duel-related 
 *                command. 
 */ 
object * 
get_duel_related_target(object tp, string command_name, string str, 
                        string optionals, int length_check) 
{ 
    object *who; 

    if (!str || str == "") 
    { 
        if (objectp(tp->query_attack())) 
            who = ({ tp->query_attack() }); 
        else if (length_check)
        { 
            notify_fail(command_name + " whom?\n"); 
            return 0; 
        } 
    } 

    if (!sizeof(who) && 
        !sizeof(who = parse_this(str, optionals + " %l"))) 
    { 
        notify_fail(command_name + " whom?\n"); 
        return 0; 
    } 
    else if (sizeof(who) > 1) 
    { 
        notify_fail("You may only " + command_name + 
                    " one person at once!\n"); 
        return 0; 
    } 
    else if (!tp->query_met(who[0])) 
    { 
        notify_fail("You have to be introduced " + 
                    "before you can duel.\n"); 
        return 0; 
    } 

    if (!IS_GELAN_CADET(who[0]) && !IS_GRADUATE(who[0])) { 
        notify_fail(command_name + "ing is only relevant for cadets " + 
                    "and graduates!\n"); 
        return 0; 
    } 

    return who; 
} 


/* 
 * Function:     remove_duel_name 
 * Description:  Removes someone's name from the list of a duel-related 
 *               property on the specified player. 
 */ 
varargs void 
remove_duel_name(object player, string prop, string nm, string *plist) 
{ 
    if (!pointerp(plist) && 
        !pointerp(plist = player->query_prop(prop))) 
        return; 

    player->add_prop(prop, plist - ({ nm })); 
} 


/* 
 * Function:      add_duel_name 
 * Description:   Adds someone's name from the list of a duel-related 
 *                property on the specified player. 
 */ 
varargs void 
add_duel_name(object player, string prop, string nm, string *plist) 
{ 
    if (!pointerp(plist) || 
        !pointerp(plist = player->query_prop(prop))) 
        plist = ({ }); 

    if (member_array(nm, plist) == -1) 
        player->add_prop(prop, plist + ({ nm })); 
} 


/* 
 * Function:      cgrant 
 * Description:   Grants quarter to an opponent in a duel. That means 
 *                if the opponent asks for quarter, this player will 
 *                automatically grant it. 
 */ 
int 
cgrant(string str) 
{ 
    string *duel, *how, nm; 
    object tp, *who; 

    tp = this_player(); 

    how = parse_adverb_with_space(str, BLANK_ADVERB, 0); 

    if (!pointerp(who = get_duel_related_target(tp, "<cgrant>", how[0], 
                  "[quarter]", 1))) 
        return 0; 

    /* 
     * If the opponent has asked for quarter, grant it 
     * automatically. 
     */ 
    if (who[0] == tp->query_attack() && 
        pointerp(duel = who[0]->query_prop(CADET_AS_ASK_QUARTER)) && 
        (member_array(nm = tp->query_real_name(), duel) > -1)) 
    { 
        actor("You" + how[1] + " grant", who, " quarter."); 
        target(how[1] + " grants you quarter.", who); 
        all2act(how[1] + " grants", who, " quarter."); 
        tp->stop_fight(who[0]); 
        who[0]->stop_fight(tp); 
        tell_object(tp, "The duel between you and " + 
            who[0]->query_the_name(tp) + " ends.\n"); 
        tell_object(who[0], "The duel between you and " + 
            tp->query_the_name(who[0]) + " ends.\n"); 
        tell_room(environment(tp), "The duel between " + 
            QTNAME(tp) + " and " + QTNAME(who[0]) + " ends.\n", 
            ({ tp, who[0] })); 
        remove_duel_name(who[0], CADET_AS_ASK_QUARTER, nm, duel); 
        remove_duel_name(who[0], CADET_AS_GRANT_QUARTER, nm); 
        remove_duel_name(who[0], CADET_AS_DUEL_WITH, nm); 
        nm = who[0]->query_real_name(); 
        remove_duel_name(tp, CADET_AS_ASK_QUARTER, nm); 
        remove_duel_name(tp, CADET_AS_DUEL_WITH, nm); 
        remove_duel_name(tp, CADET_AS_GRANT_QUARTER, nm); 
        return 1; 
    } 

    if (pointerp(duel = tp->query_prop(CADET_AS_GRANT_QUARTER)) && 
        (member_array(who[0]->query_real_name(), duel) > -1)) 
    { 
        notify_fail("You have already said you will grant " + 
                    who[0]->query_the_name(tp) + " quarter.\n"); 
        return 0; 
    } 

    /* 
     * Otherwise, set it up so that the fight will 
     * automatically stop if the opponent asks for 
     * quarter. 
     */ 
    add_duel_name(tp, CADET_AS_GRANT_QUARTER, who[0]->query_real_name(), 
                  duel); 

    actor("You will" + how[1] + " grant", who, " quarter if " + 
          who[0]->query_pronoun() + " asks."); 
    target(" will" + how[1] + " grant you quarter if you ask.", who); 
    all2act(" will" + how[1] + " grant", who, " quarter if " + 
            who[0]->query_pronoun() + " asks."); 
    return 1; 
} 


/* 
 * Function:      cask 
 * Description:   Ask for quarter. In a duel this will automatically 
 *                stop combat between the duelists if the other has 
 *                offered this player quarter. 
 */ 
int 
cask(string str) 
{ 
    string *duel, *how; 
    object tp, *who; 

    tp = this_player(); 

    how = parse_adverb_with_space(str, BLANK_ADVERB, 0); 

    if (!pointerp(who = get_duel_related_target(tp, "<cask>", how[0], 
                  "[quarter]", 1))) 
        return 0; 

    if (who[0]->query_attack() != tp) 
    { 
        notify_fail(who[0]->query_The_name(tp) + " is not fighting " + 
                    "you.\n"); 
        return 0; 
    } 

    if (pointerp(duel = tp->query_prop(CADET_AS_ASK_QUARTER)) && 
        (member_array(who[0]->query_real_name(), duel) > -1)) 
    { 
        notify_fail("You have already asked " + 
                    who[0]->query_the_name(tp) + " for quarter.\n"); 
        return 0; 
    } 

    actor("You" + how[1] + " ask", who, " for quarter."); 
    target(how[1] + " asks you for quarter.", who); 
    all2act(how[1] + " asks", who, " for quarter."); 

    /* 
     * If the opponent has already said s/he will grant quarter, 
     * grant it automatically. 
     */ 
    if (who[0]->query_attack() == tp && 
        pointerp(duel = who[0]->query_prop(CADET_AS_GRANT_QUARTER)) && 
        (member_array(tp->query_real_name(), duel) > -1)) 
    { 
        add_duel_name(tp, CADET_AS_ASK_QUARTER, who[0]->query_real_name()); 
        set_this_player(who[0]); 
        cgrant(tp->query_real_name()); 
        set_this_player(tp); 
        return 1; 
    } 

    /* 
     * Otherwise, note that this player has asked the opponent for 
     * quarter, setting it up so that the fight will automatically 
     * stop if the s/he grants quarter. 
     */ 
    add_duel_name(tp, CADET_AS_ASK_QUARTER, who[0]->query_real_name()); 
    return 1; 
} 


/* 
 * Function:     crefuse 
 * Description:  Refuse quarter to someone in/before a duel. 
 * 
 */ 
int 
crefuse(string str) 
{ 
    string *duel, *how; 
    object tp, *who; 

    tp = this_player(); 

    how = parse_adverb_with_space(str, BLANK_ADVERB, 0); 

    if (!pointerp(who = get_duel_related_target(tp, "<crefuse>", how[0], 
                  "[quarter]", 1))) 
        return 0; 

    if (!pointerp(duel = who[0]->query_prop(CADET_AS_ASK_QUARTER)) || 
        member_array(tp->query_real_name(), duel) == -1) 
    { 
         notify_fail(who[0]->query_The_name(tp) + " has not " + 
                     "asked you for quarter.\n"); 
         return 0; 
    } 

    remove_duel_name(tp, CADET_AS_GRANT_QUARTER, who[0]->query_real_name()); 

    if (tp->query_attack() == who[0]) 
    { 
        actor("You" + how[1] + " refuse to grant", who, " quarter."); 
        target(how[1] + " refuses to grant you quarter.", who); 
        all2act(how[1] + " refuses to grant", who, " quarter."); 
        return 1; 
    } 

    actor("You will" + how[1] + " refuse to grant", who, " quarter."); 
    target(" will" + how[1] + " refuse to grant you quarter.", who); 
    all2act(" will" + how[1] + " refuse to grant", who, " quarter."); 
    return 1; 
} 


/* 
 * Function:      cduel 
 * Description:   Challenge someone to duel. If the opponent returns 
 *                the challenge, combat starts and there won't be a 
 *                penalty for attacking or if one kills the other. 
 */ 
int 
cduel(string str) 
{
    string *duel, *how, nm; 
    object tp, *who; 

    tp = this_player(); 

    if (!str || str == "") { 
        duel = tp->query_prop(CADET_AS_DUEL_WITH); 
        tp->catch_tell("You have the following duel challenges open " + 
                       "on this visit to the realms: " + 
            (sizeof(duel) ? COMPOSITE_WORDS(map(duel, capitalize)) : 
             "none") + ".\n"); 
        return 1; 
    } 

    how = parse_adverb_with_space(str, BLANK_ADVERB, 0); 

    if (!pointerp(who = get_duel_related_target(tp, "<cduel>", how[0], 
                  "[with]", 0))) 
        return 0; 

    if ((member_array(nm = who[0]->query_real_name(), 
         duel = tp->query_prop(CADET_AS_DUEL_WITH)) > -1) && 
        objectp(tp->query_attack())) { 
        notify_fail("You have already challenged " + 
                    capitalize(nm) + " to a duel.\n"); 
        return 0; 
    } 

    add_duel_name(tp, CADET_AS_DUEL_WITH, nm, duel); 

    if (member_array(tp->query_real_name(), 
            who[0]->query_prop(CADET_AS_DUEL_WITH)) > -1) { 
        if (tp->query_attack() == who[0] || 
            who[0]->query_attack() == tp) { 
            notify_fail("You are already in combat with " + 
                        who[0]->query_the_name(tp) + ".\n"); 
            return 0; 
        } 
        actor("You" + how[1] + " accept", who, "'s challenge to duel."); 
        target(how[1] + " accepts your challenge to duel.", who); 
        all2act(how[1] + " accepts", who, "'s challenge to duel."); 
        tp->command("$kill " + OB_NAME(who[0])); 
        if (!objectp(tp->query_attack()) && 
            tp->query_prop(LIVE_O_LAST_KILL) == who[0] && 
            F_DARE_ATTACK(tp, who[0])) 
            tp->command("$kill " + OB_NAME(who[0])); 
        return 1; 
    } 

    if (tp->query_attack() == who[0] || 
        who[0]->query_attack() == tp) 
    { 
        notify_fail("You are already in combat with " + 
                    who[0]->query_the_name(tp) + ".\n"); 
        return 0; 
    } 

    actor("You" + how[1] + " challenge", who, " to a duel. " + 
        "If " + who[0]->query_pronoun() + 
        " accepts, the pair of you will be fighting without the " + 
        "possibility of a penalty."); 
    target(how[1] + " challenges you to a duel. If you want to attack " + 
        tp->query_objective() + " without the possibility of a penalty, " + 
        "use <cduel> on " + tp->query_objective() + ".", who); 
    all2act(how[1] + " challenges", who, " to a duel."); 
    return 1; 
} 
