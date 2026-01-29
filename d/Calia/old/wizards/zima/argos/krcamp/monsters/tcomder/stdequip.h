void equip_me() {
    object this=this_object();
    object pouch=clone_object(OBJ_DIR+"pouch");
    int i;
    clone_object(WEAPON_DIR+"tcsword")->move(this);
    clone_object(ARMOUR_DIR+"smail")->move(this);
    clone_object(ARMOUR_DIR+"shelmet")->move(this);
    clone_object(ARMOUR_DIR+"sshield")->move(this);
    clone_object(ARMOUR_DIR+"stunic")->move(this);
    clone_object(ARMOUR_DIR+"tccloak")->move(this);
    clone_object(ARMOUR_DIR+"sboots")->move(this);
    command("wear all");
    command("wield all");
    clone_object(WEAPON_DIR+"sdagger")->move(this);
    pouch->move(this);
    MONEY_MAKE_CC(random(37))->move(pouch);
    MONEY_MAKE_SC(random(15))->move(pouch);
    for (i=0; i<random(4); i++) (clone_object(OBJ_DIR+"jerky"))->move(pouch);
    pouch->add_prop(CONT_I_CLOSED,1);
}
