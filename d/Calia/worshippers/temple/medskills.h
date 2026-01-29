
void
set_up_skills()
{
   string me, ot;
   
    me = "unleash the elemental fire"; ot = me;
    sk_add_train(SS_ELEMENT_FIRE, ({ me, ot }), 0, 0, 40);
    me = "wield the elemental waters"; ot = me;
    sk_add_train(SS_ELEMENT_WATER, ({ me, ot }), 0, 0, 40);
    me = "control the elemental winds"; ot = me;
    sk_add_train(SS_ELEMENT_AIR, ({ me, ot }), 0, 0, 40);
    me = "compel the elemental earth"; ot = me;
    sk_add_train(SS_ELEMENT_EARTH, ({ me, ot }), 0, 0, 40);
}
