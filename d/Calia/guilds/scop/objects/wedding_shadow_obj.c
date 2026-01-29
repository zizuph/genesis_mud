
/*
 * wedding_shadow_obj.c
 *
 * This is the spell object for the skiamorfi (Shadow Form) spell for 
 * the Spirit Circle of Psuchae
 *
 * Copyright (C): Jaacar, July 31st, 2003
 *
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <cmdparse.h>

#include "defs.h"
#include SPIRIT_HEADER

object s_shadow;
int    st_timer;
string *adjectives1 = ({"capacious","enormous","colossal","vast",
                        "gigantic","massive","immense","great","sizable"});
string *adjectives2 = ({"light-aborbing","penetrating","engrossing","chilling",
                        "intimidating","unnerving","spooky","ghostly",
                        "unearthly","supernatural","phantasmal"});
string adj1, adj2, new_short;

void 
create_object()
{
    set_name("_skiamorfi_object_");
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
}

public int
start()
{
    int j,k;
    
    j = random(sizeof(adjectives1));
    k = random(sizeof(adjectives2));
    adj1 = adjectives1[j];
    adj2 = adjectives2[k];
    new_short = adj1 + " " + adj2;
    
    set_spell_effect_desc("shadow form");
   
    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    setuid(); 
    seteuid(getuid());
    s_shadow=clone_object(SPIRIT_SPELLS+"skiamorfi_shadow");
    s_shadow->shadow_me(TP);
    TP->set_disguise(({adj1,adj2}));

    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    tell_room(environment(TP),"The "+new_short+" shadowy form "+
        "is suddenly enveloped in blinding flash of light. You are forced to "+
        "avert your eyes.\n",({TP}));
    TP->remove_disguise_shadow();
    tell_room(environment(TP),"When you look upon "+HIM+" again, "+
        HE+" stands in the shape of a "+TP->query_nonmet_name()+
        ".\n",({TP}));
    remove_spell_effect_object();
    return 1;

}