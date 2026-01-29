 
#define  WEAPON ({"igsword","igaxe","ighalberd"})
void equip_me() {
    object this=this_object();
    object pouch=clone_object(OBJ_DIR+"pouch");
    int i;
    clone_object(WEAPON_DIR+(WEAPON[(random(sizeof(WEAPON)))]))->move(this);
    clone_object(ARMOUR_DIR+"igmail")->move(this);
    clone_object(ARMOUR_DIR+"ighelmet")->move(this);
    clone_object(ARMOUR_DIR+"igtunic")->move(this);
    clone_object(ARMOUR_DIR+"igcloak")->move(this);
    clone_object(ARMOUR_DIR+"igsash")->move(this);
    clone_object(ARMOUR_DIR+"sboots")->move(this);
    command("wield all");
    command("wear all");
    clone_object(WEAPON_DIR+"gauche")->move(this);
    pouch->move(this);
    MONEY_MAKE_CC(random(30))->move(pouch);
    MONEY_MAKE_SC(random(10))->move(pouch);
    for (i=0; i<random(4); i++) (clone_object(OBJ_DIR+"jerky"))->move(pouch);
    pouch->add_prop(CONT_I_CLOSED,1);
}
