#include "/d/Kalad/defs.h"
#include <tasks.h>

public object *light_target(string arg);
public void light_message(object caster, object *target);

public int
hlight_success()
{
    return 1;
}

public void
create_spell_hlight()
{
    set_spell_element(SS_ELEMENT_FIRE, 10);
    set_spell_form(SS_FORM_CONJURATION, 10);
    set_spell_time(2);


    set_spell_mana(10);
    set_find_target(light_target);

    set_spell_task(TASK_ROUTINE,0);

    set_spell_message(light_message);
}

public int
do_light(string str)
{
    return cast_spell();
}

public object *
light_target(string str)
{
    return ({ query_caster() });
}

public void
light_message(object caster, object *targets)
{
    int light_amount;
    
     /* Add two levels of light to caster */

    light_amount = caster->query_prop(OBJ_I_LIGHT);
    caster->add_prop(OBJ_I_LIGHT,light_amount + 2);

    tell_room(E(targets[0]), "A bright, white aura surrounds "+
    QTNAME(caster)+".\n",caster);
    tell_object(caster,"A bright, white aura surrounds you.\n");

    set_alarm(30.0,0.0,"end_light_spell",caster);
}

public void
end_light_spell(object caster)
{
    int light_amount;
    
    light_amount = caster->query_prop(OBJ_I_LIGHT);
    caster->add_prop(OBJ_I_LIGHT,light_amount - 2);

    tell_room(E(caster),"The light surrounding "+QTNAME(caster)+
    " suddenly blinks out.\n",caster);
    tell_object(caster,"The light surrounding you suddenly blinks out.\n");
}


