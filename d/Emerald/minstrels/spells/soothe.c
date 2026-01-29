inherit "/d/Genesis/newmagic/spells/heal";

public varargs int
config_spell(object caster, object *targets, string argument)
{
    if (::config_spell(caster, targets, argument))
    {
        return 1;
    }
    set_spell_mana(20);
    set_heal_amount(200);
}
