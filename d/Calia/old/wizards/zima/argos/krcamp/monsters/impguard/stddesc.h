    /* standard impguard desc - to be included in create_monster */
    string adj=MaleAdj[(random(sizeof(MaleAdj)))];
    if (!IS_CLONE) return;
    set_name("guard");
    add_name(({"kretan","soldier","human"}));
    set_adj(({adj,"kretan","imperial","hooded"}));
    set_race_name("human");
    set_short("hooded Kretan imperial guard");
    set_long(
        "He is a stalwart Imperial Guard in the army of Kretos. His "+
        "entire head is covered with a black hood, his piercing eyes "+
        "peering out from their anonymnity with an evil, vigilant "+
        "glare.\n");
