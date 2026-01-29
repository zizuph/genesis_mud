
void
set_up_skills()
{
   string me, ot;
   
	me = "perform magic and spells"; ot = me;
	sk_add_train(SS_SPELLCRAFT, ({ me, ot }), 0, 0, 75);
	me = "understand different languages"; ot = me;
	sk_add_train(SS_LANGUAGE, ({ me, ot }), 0, 0, 50);
    me = "defend yourself"; ot = me;
    sk_add_train(SS_DEFENCE, ({ me, ot }), 0, 0, 75);
    me = "use fire magic"; ot = me;
    sk_add_train(SS_ELEMENT_FIRE, ({ me, ot }), 0, 0, 75);
    me = "use air magic"; ot = me;
    sk_add_train(SS_ELEMENT_AIR, ({ me, ot }), 0, 0, 75);
    me = "use water magic"; ot = me;
    sk_add_train(SS_ELEMENT_WATER, ({ me, ot }), 0, 0, 75);
    me = "use earth magic"; ot = me;
    sk_add_train(SS_ELEMENT_EARTH, ({ me, ot }), 0, 0, 75);
    me = "use abjuration magic"; ot = me;
    sk_add_train(SS_FORM_ABJURATION, ({ me, ot }), 0, 0, 75);
    me = "use conjuration magic"; ot = me;
    sk_add_train(SS_FORM_CONJURATION, ({ me, ot }), 0, 0, 75);
}
