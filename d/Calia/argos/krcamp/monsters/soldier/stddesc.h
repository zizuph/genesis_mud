    string adj=MaleAdj[(random(sizeof(MaleAdj)))];
    if (!IS_CLONE) return;
    set_name("soldier");
    add_name(({"kretan","human","soldier"}));
    set_adj(({adj,"kretan"}));
    set_race_name("human");
    set_short(adj+" Kretan soldier");
    set_long(
        "He is a "+adj+" Kretan soldier, his face bearing a few scars "+
        "of battle and his eyes gleaming murderingly. His strong athletic "+
        "body exudes an aura of strength and danger.\n");
