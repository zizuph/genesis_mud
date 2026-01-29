/*
    lphantasm.c

    Lich priest spell,
    included by lp_med.c (the medallion)
    
    Sarr
    Recoded and balanced by Fysix, April 1998
 */

string gTYPE;

// Execute the spell, clones a spell object and moves
// it to the caster.
// Clones some monsies too.
void
do_lphantasm_spell(object caster, object *targets, int *resist, int result)
{
    int i;
    object creature, control;

    control = present("_illmonc_", caster);

    if (!objectp(control))
    {
        control = make_spell_effect_object(LP_DIR + "obj/illmonc",
            caster, targets, resist, result);
        control->set_spell_effect_desc("control phantasms");
        control->move(caster, 1);
    }


    creature = clone_object(gTYPE);

    control->add_monster(creature);
    creature->setup_illusion(caster);

    tell_object(caster,"You throw your hands in the air and scream "+
        "an unholy incantation to the Horror as a black fire erupts from "+
        "the ground before you.\n");
    tell_room(ENV(caster), QCTNAME(caster) + " throws " +
        HIS(caster) + " hands in the air and " +
        "screams an unholy incantation to whatever hellish diety " + 
        HE(caster) + " worships as a black fire erupts from the " +
        "ground!\n", ({caster}));
    tell_room(ENV(caster), "From the black fire, a " +
        creature->short() + " appears!\n");

    creature->move_living("M", ENV(caster), 1);
}

// Configure the spell
int
create_spell_lphantasm(object caster, object *targets, string arg)
{
    if (!check_ok_cast(caster))
        return 1;

    if (!stringp(arg))
    {
        tell_object(caster, "You must specify the type of " +
            "phantasm to conjure!\n");
        return 1;
    }

    gTYPE = "";
    switch (arg)
    {
       case "sdemon":
        gTYPE = LP_DIR + "obj/illusion_fiend1";
        break;
       case "clone":
        gTYPE = LP_DIR + "obj/illusion_fiend2";
        break;

       default:
        tell_object(caster, "That is not one of the types " +
            "of conjurations you can use, read the help file!\n");
        return 1;
    }

    set_spell_element(SS_ELEMENT_DEATH, 50);
    set_spell_form(SS_FORM_ILLUSION, 50);
    set_spell_time(3);
    set_spell_mana(95);
    set_spell_ingredients(({"glowshroom", "rib", "dajla"})); 
    set_spell_conc_message(conc_message_burn_eyes);
    set_spell_effect(do_lphantasm_spell);
    set_spell_task(TASK_ROUTINE);

    return 0;   // success
}

