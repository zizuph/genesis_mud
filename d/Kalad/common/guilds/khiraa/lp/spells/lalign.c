/* Sarr */


void
do_lalign_spell(object caster, object *targets, int *res, int result)
{
    string color;
    int align;
    object target = targets[0];

    res[0] = ( res[0] * 100 ) / result;

    if ( res[0] >= 100)
    {
        tell_object(caster,target->query_The_name(caster)+" seems "+
            "immune to your spell somehow.\n");
        return;
    }

    align = target->query_alignment();

    if(res[0])
    {  
        if(random(10) > 5 ) // offshift the results
            align += (align * res[0]) / 100;
        else
            align -= (align * res[0]) / 100;
    }
    if(align > 1200)
        align = 1200;
    if(align < -1200)
        align = -1200;
    switch(align)
    {
        case 1101..1200:
            color = "pure white";
            break;
        case 1001..1100:
            color = "white";
            break;
        case 901..1000:
            color = "ultra-light blue";
            break;
        case 801..900:
            color = "light blue";
            break;
        case 701..800:
            color = "sky blue";
            break;
        case 601..700:
            color = "blue";
            break;
        case 501..600:
            color = "light grey-blue";
            break;
        case 401..500:
            color = "grey-blue";
            break;
        case 301..400:
            color = "deep grey-blue";
            break;
        case 201..300:
            color = "light grey";
            break;
        case 101..200:
            color = "grey";
            break;
        case 1..100:
            color = "true grey";
            break;
        case -99..0:
            color = "dark grey";
            break;
        case -199..-100:
            color = "light reddish grey";
            break;
        case -299..-200:
            color = "reddish grey";
            break;
        case -399..-300:
            color = "dark reddish grey";
            break;
        case -499..-400:
            color = "red";
            break;
        case -599..-500:
            color = "deep red";
            break;
        case -699..-600:
            color = "dark red";
            break;
        case -799..-700:
            color = "molton red";
            break;
        case -899..-800:
            color = "deep purple";
            break;
        case -999..-900:
            color = "near-black";
            break;
        case -1099..-1000:
            color = "black";
            break;
        case -1200..-1100:
            color = "hellish black";
            break;
        default:
            color = "buggy";
    }

    tell_room(E(target),"A "+color+" glow surrounds "+QTNAME(target)+
    " for a moment.\n",target);
    tell_object(target,"A "+color+" glow surrounds you for a moment.\n");
}

public void
conc_lalign_mess(object caster, object *targets, string arg)
{
    tell_object(caster,"You invoke the prayer to the Horror as your eyes "+
    "begin to glow deep purple.\n");
    tell_room(ENV(caster),QCTNAME(caster)+"'s eyes begin to glow deep purple "+
    "color as "+HE(caster)+" chants unholy words.\n",caster);
}

public int
create_spell_lalign(object caster, object *targets, string arg)
{
    if(!check_ok_cast(caster))
        return 1;

    set_spell_element(SS_ELEMENT_DEATH,15);
    set_spell_form(SS_FORM_DIVINATION,10);
    set_spell_time(2);
    set_spell_mana(25);
    set_spell_ingredients(({"laurel"}));
    set_spell_effect(do_lalign_spell);
    set_spell_task(TASK_SIMPLE);
    set_spell_conc_message(conc_lalign_mess);

    set_spell_target_verify(spell_verify_present);
    set_spell_resist_task(TASK_DIFFICULT);
    set_spell_resist(spell_resist_identify);
    return 0;
}
