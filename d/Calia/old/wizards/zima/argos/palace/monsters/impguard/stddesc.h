    /* standard impguard desc - to be included in create_monster */
    string adj=MaleAdj[(random(sizeof(MaleAdj)))];
    if (!IS_CLONE) return;
    set_name("guard");
    add_name(({"argosian","soldier","human"}));
    set_adj(({adj,"argosian","imperial","palace"}));
    set_race_name("human");
    set_short(adj+" palace guard");
    set_long(
        "He is a stalwart imperial guard in special service to the "+
        "monarch of Argos to protect the royal palace. There is a look "+
        "of devotion and loyalty, with no sign of fear, in his eyes.\n");
