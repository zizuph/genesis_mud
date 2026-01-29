    string adj=MaleAdj[(random(sizeof(MaleAdj)))];
    if (!IS_CLONE) return;
    set_name(({"triterian","commander","kretan","human","soldier"}));
    set_adj(({adj,"kretan","triterian","commander"}));
    set_race_name("human");
    set_short(adj+" Kretan triterian commander");
    set_long(
        "He is a "+adj+" Triterian Commander in the Army of Kretos, in "+
        "charge of a small detatchment of soldiers. His facial features "+
        "betray his youth but also reflect his dedication.\n");
