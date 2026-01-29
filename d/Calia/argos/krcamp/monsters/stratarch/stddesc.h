    string adj=MaleAdj[(random(sizeof(MaleAdj)))];
    if (!IS_CLONE) return;
    set_name("stratarch");
    add_name(({"kretan","soldier","commander"}));
    set_adj(({adj,"kretan"}));
    set_race_name("human");
    set_short(adj+" Kretan stratarch");
    set_long(
        "He is a "+adj+" Kretan Stratarch, a battallion commander in "+
        "the army of Kretos. His strong muscular body and scarred "+
        "serious face emanate an aura of strict discipline and "+
        "wisdom.\n");
