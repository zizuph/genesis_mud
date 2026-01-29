/*
 *  This heap is created as a way for potions to grant multiple castings
 *  of a spell. Taken from the pouch of a kender who had been visiting
 *  the Morgul Mages.
 */
#include <stdproperties.h>

inherit "/std/heap";

string ingredient_name;
string *spell_names;

void
create_heap() 
{
    set_heap_size(1);
    
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(HEAP_I_UNIT_VOLUME, 0);
    add_prop(HEAP_I_UNIT_WEIGHT, 0);
    add_prop(HEAP_S_UNIQUE_ID, "_sohm_spell_ingredient");

    set_no_show();
}

void
configure_spell_ingredient(string name, string *spells)
{
    ingredient_name = name;
    spell_names = spells;

    set_name(name);
    add_prop(HEAP_S_UNIQUE_ID, "_sohm_spell_ingredient" + name);
}

public string
query_ingredient_name()
{
    return ingredient_name;
}

public string *
query_spell_names()
{
    return spell_names;
}

public void
config_split(int new_num, object orig)
{
    ::config_split(new_num, orig);
    configure_spell_ingredient(orig->query_ingredient_name(),
        orig->query_spell_names());
}