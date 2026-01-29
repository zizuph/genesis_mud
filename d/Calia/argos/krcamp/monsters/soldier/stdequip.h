void equip_me() {
    object this=this_object();
    object pouch;
    int i;
    clone_object(WEAPON_DIR+"sosword")->move(this);
    clone_object(ARMOUR_DIR+"somail")->move(this);
    clone_object(ARMOUR_DIR+"sohelmet")->move(this);
    clone_object(ARMOUR_DIR+"soshield")->move(this);
    clone_object(ARMOUR_DIR+"stunic")->move(this);
    clone_object(ARMOUR_DIR+"sboots")->move(this);
    command("wield all");
    command("wear all");
    /* will have either stilleto or pouch for loot */
    if ((random(2))==0)
       clone_object(WEAPON_DIR+"stilleto")->move(this);
    else {
       pouch=clone_object(OBJ_DIR+"pouch");
       pouch->move(this);
       MONEY_MAKE_GC(random(4))->move(pouch);
       for (i=0; i<random(4); i++) (clone_object(OBJ_DIR+"jerky"))->move(pouch);
       pouch->add_prop(CONT_I_CLOSED,1);
    }
}
