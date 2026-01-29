    /* the following puts this NPC in the Loyal Team for Team support */
    add_prop(ATTACK_TEAM,REBEL_TEAM);
    set_aggressive(1);
    set_attack_chance(100);
 
    set_stats(({30,30,30,15,15,30}));
    set_skill(SS_WEP_POLEARM,30);
    set_skill(SS_PARRY,30);
    set_skill(SS_DEFENCE,30);
    set_hp(query_max_hp());
    set_alignment(-120);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
