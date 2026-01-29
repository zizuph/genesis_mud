#include "/d/Kalad/defs.h"
#include <tasks.h>

public object *evil_target(string arg);
public void evil_message(object caster, object *target);

public void
create_spell_hreveal()
{
    set_spell_element(SS_ELEMENT_LIFE, 10);
    set_spell_form(SS_FORM_DIVINATION, 10);
    set_spell_time(2);

    set_spell_mana(20);
    set_find_target(evil_target);

    set_spell_task(TASK_ROUTINE,0);

    set_spell_message(evil_message);
}

public int
do_hreveal(string str)
{
    return cast_spell();
}

public object *
evil_target(string str)
{
    return FILTER_LIVE(all_inventory(E(query_caster())));
}

public void
reveal_the_evil(object ob)
{
    int alig;
    string alevel;
    alig = -ob->query_alignment();
    switch(alig)
    {
        case 0..100:
        alevel = "faint orange";
        break;
        case 101..200:
        alevel = "slight orange";
        break;
        case 201..300:
        alevel = "deep orange";
        break;
        case 301..400:
        alevel = "light red-orange";
        break;
        case 401..500:
        alevel = "light red";
        break;
        case 501..600:
        alevel = "red";
        break;
        case 601..700:
        alevel = "deep red";
        break;
        case 701..800:
        alevel = "strong red";
        break;
        case 801..900:
        alevel = "bright red";
        break;
        case 901..1000:
        alevel = "intense red";
        break;
        case 1001..1100:
        alevel = "blazing red";
        break;
        case 1101..1200:
        alevel = "blinding red";
        break;
        default:
        alevel = "buggy";
    }
    tell_room(E(ob),"A "+alevel+" aura suddenly surrounds "+QTNAME(ob)+
    "!\n",ob);
    ob->catch_msg("A "+alevel+" aura suddenly surrounds you!\n");
    ob->add_prop(LIVE_S_EXTRA_SHORT," surrounded by a "+alevel+" aura");
    set_alarm(60.0,0.0,"remove_aura",ob);
}

void
remove_aura(object ob)
{
    tell_object(ob,"The dark aura surrounding you fades away.\n");
    tell_room(E(ob),"The dark aura surrounding "+QTNAME(ob)+
    " fades away.\n",ob);
    ob->remove_prop(LIVE_S_EXTRA_SHORT);
}

public void
evil_message(object caster, object *targets)
{
    int i,eviln;    
    for(i=0;i<sizeof(targets);i++)
    {
        eviln = targets[i]->query_alignment();
        if(eviln < 0)
        {
            reveal_the_evil(targets[i]);
        }
    }

}


