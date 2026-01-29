#include "/d/Kalad/defs.h"
#include <tasks.h>

public object *heyel_target(string arg);
public void heyel_message(object caster, object *target);

public void
create_spell_heyel()
{
    set_spell_element(SS_ELEMENT_AIR, 25);
    set_spell_form(SS_FORM_DIVINATION, 35);
    set_spell_time(2);

    set_spell_mana(20);
    set_find_target(heyel_target);

    set_spell_task(TASK_ROUTINE,1);

    set_spell_message(heyel_message);
}

public int
do_heyel(string str)
{
    return cast_spell();
}

public object *
heyel_target(string str)
{
    return FILTER_LIVE(all_inventory(E(query_caster())));
}

public void
heyel_message(object caster, object *targets)
{
    int i,hlev;    
    for(i=0;i<sizeof(targets);i++)
    {
        if(targets[i]->query_prop(OBJ_I_HIDE))
        {
            targets[i]->add_prop(OBJ_I_HIDE,0);
            tell_room(E(targets[i]),QCTNAME(targets[i])+" is "+
            "revealed by divine light!\n",targets[i]);
            tell_object(targets[i],"You are no longer hidden as you "+
            "are revealed by divine light!\n");     
        }
    }

}


