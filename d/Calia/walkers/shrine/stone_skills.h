
void
set_up_skills()
{
   string me, ot;
   
    me = "mix alchemical potions"; ot = me;
    sk_add_train(SS_ALCHEMY, ({ me, ot }), 0, 0, 90);
    me = "wield the powers of Lady Gu"; ot = me;
    sk_add_train(SS_ELEMENT_EARTH, ({ me, ot }), 0, 0, 90);
    me = "perform magic and spells"; ot = me;
    sk_add_train(SS_SPELLCRAFT, ({ me, ot }), 0, 0, 90);
    me = "communicate with the Elementals"; ot = me;
    sk_add_train(SS_PRAYER, ({ me, ot }), "channeling", 170, 100, SS_INT, 110);
    me = "communicate with the Elementals"; ot = me;
    sk_add_train(SS_LANGUAGE, ({ me, ot }), 0, 0, 75);
    me = "defend yourself"; ot = me;
    sk_add_train(SS_DEFENCE, ({ me, ot }), 0, 0, 70);
    me = "use a polearm"; ot = me;
    sk_add_train(SS_WEP_POLEARM, ({ me, ot }), 0, 0, 50);
    me = "be aware of your surroundings"; ot = me;
    sk_add_train(SS_AWARENESS, ({ me, ot }), 0, 0, 75);
    me = "recognize different herbs"; ot = me;
    sk_add_train(SS_HERBALISM, ({ me, ot }), 0, 0, 75);
}
