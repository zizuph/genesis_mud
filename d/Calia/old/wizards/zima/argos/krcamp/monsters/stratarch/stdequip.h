void equip_me() {
    object this=this_object();
    object pouch=clone_object(OBJ_DIR+"pouch");
    int i;
    clone_object(WEAPON_DIR+"stsword")->move(this);
    clone_object(ARMOUR_DIR+"stmail")->move(this);
    clone_object(ARMOUR_DIR+"sthelmet")->move(this);
    clone_object(ARMOUR_DIR+"sttunic")->move(this);
    clone_object(ARMOUR_DIR+"stcloak")->move(this);
    clone_object(ARMOUR_DIR+"stsash")->move(this);
    clone_object(ARMOUR_DIR+"sboots")->move(this);
    command("wear all");
    command("wield all");
    clone_object(WEAPON_DIR+"gauche")->move(this);
    pouch->move(this);
    MONEY_MAKE_CC(random(30))->move(pouch);
    MONEY_MAKE_SC(random(10))->move(pouch);
    for (i=0; i<random(4); i++) (clone_object(OBJ_DIR+"jerky"))->move(pouch);
    pouch->add_prop(CONT_I_CLOSED,1);
}
