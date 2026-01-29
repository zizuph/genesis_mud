 
 inherit "/d/Genesis/specials/new/magic/spells/unfinished/turn_undead.c"
 
 public void config_turn_undead_spell()
 {
     // This is not a maintained spell, but rather an instant
     // effect.
     set_dispel_time(0);
     
 }
 
public void
hook_describe_turn_undead(object caster, mixed * targets, int result)
{
    caster->catch_tell("You invoke the Goddess Sachluph.\nThe "+
        "amulet glows with a fierce and blinding greenish light, "+
        "then subsides, leaving you feeling both mentally and "+
        "physically tired.\n");
    tell_room(environment(caster), QCTPNAME(caster) +" "+
        "amulet glows with a fierce and blinding greenish light, "+
        "then subsides.\n", query_worn());
        /* NOW lets make the undead turn and run away */
    targets->catch_msg("The greenish light causes terror to rise "+
            "from the depths of your being.  You feel the need to "+
            "flee.\n");

}

public void
resolve_spell_resisted(object caster, object target, int resist, int result)
{
    caster->catch_tell("The undead is unaffected "+
        "by your invocation of Sachluph.  "+ 
        capitalize(target->query_pronoun()) +" is protected "+
        "against Her power.\n");
    target->catch_tell("You are unaffected by the light.\n");
}
