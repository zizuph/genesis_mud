#define  WEAPON ({"wsword","waxe","whalberd"})
void equip_me() {
    object this=this_object();
    object pouch;
    int i;
    clone_object(WEAPON_DIR+(WEAPON[(random(sizeof(WEAPON)))]))->move(this);
    clone_object(ARMOUR_DIR+"wmail")->move(this);
    clone_object(ARMOUR_DIR+"whelmet")->move(this);
    clone_object(ARMOUR_DIR+"stunic")->move(this);
    clone_object(ARMOUR_DIR+"sboots")->move(this);
    command("wield all");
    command("wear all");
    clone_object(WEAPON_DIR+"dirk")->move(this);
    if ((random(2))==0) {
        pouch=clone_object(OBJ_DIR+"pouch");
        pouch->move(this);
        MONEY_MAKE_GC(random(8))->move(pouch);
        for (i=0; i < random(3); i++) 
            (clone_object(OBJ_DIR+"jerky"))->move(pouch);
        pouch->add_prop(CONT_I_CLOSED,1);
    }
}
