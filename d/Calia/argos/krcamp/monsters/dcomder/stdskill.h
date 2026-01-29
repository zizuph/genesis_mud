    /* the following puts this NPC in the Rebel Team for Team support */
    add_prop(ATTACK_TEAM,REBEL_TEAM);
    set_aggressive(1);
    set_attack_chance(100);
 
    set_stats(({ 95, 95, 95, 65, 65, 130})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_SWORD, 75);
    set_skill(SS_PARRY, 75);
    set_skill(SS_DEFENCE, 75);
    set_hp(query_max_hp());
    set_alignment(0);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
