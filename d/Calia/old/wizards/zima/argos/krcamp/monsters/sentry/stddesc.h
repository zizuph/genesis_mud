    string adj=MaleAdj[(random(sizeof(MaleAdj)))];
    if (!IS_CLONE) return;
    set_name(({"kretan sentry","sentry","kretan","human","soldier"}));
    set_adj(({adj,"Kretan"}));
    set_race_name("human");
    set_short(adj+" Kretan sentry");
    set_long(
        "He is a "+adj+" Kretan sentry, a watchful guard and enthusiastic "+
        "member of the army of Kretos. He looks willing to fight to the "+
        "death for his cause.\n");
 
