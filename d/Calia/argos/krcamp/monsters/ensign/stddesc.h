    string adj=MaleAdj[(random(sizeof(MaleAdj)))];
    if (!IS_CLONE) return;
    set_name(({"kretan ensign","ensign","kretan","human","soldier"}));
    set_adj(({adj,"Kretan"}));
    set_race_name("human");
    set_short(adj+" Kretan ensign");
    set_long(
        "He is a "+adj+" Kretan ensign, a young recruit for the rebel "+
        "army. He is too small to fight, but he bears a large black banner "+
        "in one hand with pride. His innocent face betrays a cold dedicated "+
        "heart.\n");
