    string adj=MaleAdj[(random(sizeof(MaleAdj)))];
    if (!IS_CLONE) return;
    set_name("warrior");
    add_name(({"kretan","human","soldier"}));
    set_adj(({adj,"kretan"}));
    set_race_name("human");
    set_short(adj+" Kretan warrior");
    set_long(
        "He is a "+adj+" Kretan warrior, a stalwart and intimidating "+
        "combatant with a deadly conviction in his eyes.\n");
 
