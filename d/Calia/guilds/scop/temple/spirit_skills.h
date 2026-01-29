
void
set_up_skills()
{
   string me, ot;
   
    me = "use the powers of life spells"; ot = me;
    sk_add_train(SS_ELEMENT_LIFE, ({ me, ot }), 0, 0, 60);

    me = "perform rituals and spells"; ot = me;
    sk_add_train(SS_SPELLCRAFT, ({ me, ot }), 0, 0, 90);
    me = "utilize the shadows of Psuchae"; ot = me;
    sk_add_train(SS_ELEMENT_SPIRIT, ({ me, ot }), "spirit spells", 100, 100, SS_WIS, 110);

    me = "defend yourself"; ot = me;
    sk_add_train(SS_DEFENCE, ({ me, ot }), 0, 0, 80);

    me = "use a bludgeoning weapon"; ot = me;
    sk_add_train(SS_WEP_CLUB, ({ me, ot }), 0, 0, 75);

    me = "be aware of your surroundings"; ot = me;
    sk_add_train(SS_AWARENESS, ({ me, ot }), 0, 0, 60);

    me = "recognize different herbs"; ot = me;
    sk_add_train(SS_HERBALISM, ({ me, ot }), 0, 0, 70);

    me = "use the powers of divination"; ot = me;
    sk_add_train(SS_FORM_DIVINATION, ({ me, ot }), 0, 0, 80);

    me = "use the powers of transmutation"; ot = me;
    sk_add_train(SS_FORM_TRANSMUTATION, ({ me, ot }), 0, 0, 80);

    me = "use the powers of enchantment"; ot = me;
    sk_add_train(SS_FORM_ENCHANTMENT, ({ me, ot }), 0, 0, 60);

    me = "use the powers of conjuration"; ot = me;
    sk_add_train(SS_FORM_CONJURATION, ({ me, ot }), 0, 0, 60);

    me = "trade for a profit"; ot = me;
    sk_add_train(SS_TRADING, ({ me, ot }), 0, 0, 60);

    me = "parry blows with a bludgeoning weapon"; ot = me;
    sk_add_train(SS_PARRY, ({ me, ot }), 0, 0, 50);

    me = "understand different languages"; ot = me;
    sk_add_train(SS_LANGUAGE, ({ me, ot }), 0, 0, 60);

    me = "appraise the value of an object"; ot = me;
    sk_add_train(SS_APPR_VAL, ({ me, ot }), 0, 0, 60);
}
