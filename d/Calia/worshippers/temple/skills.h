
void
set_up_skills()
{
   string me, ot;
   
    me = "perform magic and spells"; ot = me;
    sk_add_train(SS_SPELLCRAFT, ({ me, ot }), 0, 0, 50);
    me = "use conjuration magic"; ot = me;
    sk_add_train(SS_FORM_CONJURATION, ({ me, ot }), 0, 0, 40);
    me = "use enchantment magic"; ot = me;
    sk_add_train(SS_FORM_ENCHANTMENT, ({ me, ot }), 0, 0, 40);    
    me = "understand different languages"; ot = me;
    sk_add_train(SS_LANGUAGE, ({ me, ot }), 0, 0, 60);
    me = "defend yourself"; ot = me;
    sk_add_train(SS_DEFENCE, ({ me, ot }), 0, 0, 30);
    me = "use a polearm"; ot = me;
    sk_add_train(SS_WEP_POLEARM, ({ me, ot }), 0, 0, 50);
    me = "be aware of your surroundings"; ot = me;
    sk_add_train(SS_AWARENESS, ({ me, ot }), 0, 0, 60);
    me = "recognize different herbs"; ot = me;
    sk_add_train(SS_HERBALISM, ({ me, ot }), 0, 0, 60);
}
