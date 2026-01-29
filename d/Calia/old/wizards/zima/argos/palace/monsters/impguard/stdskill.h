    /* standard skill and other settings for imperial guards */
    add_prop(ATTACK_TEAM,LOYAL_TEAM);
 
    set_stats(({ 90, 90, 90, 30, 30, 90})); /* STR,DEX,CON,INT,WIS,DIS */
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_WEP_AXE, 90);
    set_skill(SS_WEP_POLEARM, 90);
    set_skill(SS_PARRY, 90);
    set_skill(SS_DEFENCE, 90);
    set_hp(query_max_hp());
    set_alignment(250);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
