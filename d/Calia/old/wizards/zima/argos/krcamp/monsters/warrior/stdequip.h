#define  WEAPON ({"wsword","waxe","whalberd"})
void equip_me() {
    object this=this_object();
    object pouch=clone_object(OBJ_DIR+"pouch");
    int i;
    clone_object(WEAPON_DIR+(WEAPON[(random(sizeof(WEAPON)))]))->move(this);
    clone_object(ARMOUR_DIR+"wmail")->move(this);
    clone_object(ARMOUR_DIR+"whelmet")->move(this);
    clone_object(ARMOUR_DIR+"wshield")->move(this);
    command("wear all");
    clone_object(ARMOUR_DIR+"stunic")->move(this);
    clone_object(ARMOUR_DIR+"sboots")->move(this);
    command("wield all");
    command("wear all");
    clone_object(WEAPON_DIR+"dirk")->move(this);
    pouch->move(this);
    MONEY_MAKE_CC(random(30))->move(pouch);
    MONEY_MAKE_SC(random(15))->move(pouch);
    for (i=0; i<random(4); i++) (clone_object(OBJ_DIR+"jerky"))->move(pouch);
    pouch->add_prop(CONT_I_CLOSED,1);
}
