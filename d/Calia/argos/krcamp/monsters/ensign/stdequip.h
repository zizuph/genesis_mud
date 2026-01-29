void equip_me() {
    object this=this_object();
    object pouch;
    int i;
    clone_object(WEAPON_DIR+"sdagger")->move(this);
    clone_object(ARMOUR_DIR+"smail")->move(this);
    clone_object(ARMOUR_DIR+"shelmet")->move(this);
    clone_object(ARMOUR_DIR+"stunic")->move(this);
    command("wield all");
    command("wear all");
    clone_object(OBJ_DIR+"standard")->move(this);
    if ((random(3))==0) { /* 33% chance ensign will have a pouch */
       pouch=clone_object(OBJ_DIR+"pouch");
       pouch->move(this);
       MONEY_MAKE_CC(random(12))->move(pouch);
       MONEY_MAKE_SC(random(1))->move(pouch);
       for (i=0; i<random(3); i++) (clone_object(OBJ_DIR+"jerky"))->move(pouch);
       pouch->add_prop(CONT_I_CLOSED,1);
    }
}
