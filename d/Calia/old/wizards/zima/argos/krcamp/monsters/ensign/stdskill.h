    /* the following puts this NPC in the Loyal Team for Team support */
    add_prop(ATTACK_TEAM,REBEL_TEAM);
    set_aggressive(1);
    set_attack_chance(100);
 
    /* actions added when cloned */
    set_act_time(10);
    set_cact_time(5);
    set_stats(({25,25,25,10,10,25}));
    set_skill(SS_WEP_KNIFE,25);
    set_skill(SS_PARRY,25);
    set_skill(SS_DEFENCE,25);
    set_hp(query_max_hp());
    set_alignment(-80);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
