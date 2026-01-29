    string adj=MaleAdj[(random(sizeof(MaleAdj)))];
    if (!IS_CLONE) return;
    set_name("commander");
    add_name(({"kretan","deuterian","human","soldier"}));
    set_adj(({adj,"kretan","deuterian"}));
    set_race_name("human");
    set_short(adj+" Kretan deuterian commander");
    set_long(
        "He is a "+adj+" Kretan deuterian commander, in charge of a "+
        "regiment of soldiers in the army of Kretos. His squared jaw "+
        "and serious eyes reflect his veteran command experience.\n");
 
