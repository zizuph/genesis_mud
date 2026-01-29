#include "/d/Kalad/defs.h"
#include <tasks.h>

public object *heyeg_target(string arg);
public void heyeg_message(object caster, object *target);

public void
create_spell_heyeg()
{
    set_spell_element(SS_ELEMENT_AIR, 45);
    set_spell_form(SS_FORM_DIVINATION, 50);
    set_spell_time(3);

    set_spell_mana(170);
    set_find_target(heyeg_target);

    set_spell_task(TASK_DIFFICULT,1);

    set_spell_message(heyeg_message);
}

public int
do_heyeg(string str)
{
    return cast_spell();
}

public object *
heyeg_target(string str)
{
    return FILTER_LIVE(all_inventory(E(query_caster())));
}

public void
heyeg_message(object caster, object *targets)
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
        if(targets[i]->query_prop(OBJ_I_INVIS))
        {
            targets[i]->add_prop(OBJ_I_INVIS,0);
            tell_room(E(targets[i]),QCTNAME(targets[i])+" is "+
            "revealed by divine light!\n",targets[i]);
            tell_object(targets[i],"You are no longer invisible as "+
            "you are revealed by divine light!\n");
        }
    }

}


