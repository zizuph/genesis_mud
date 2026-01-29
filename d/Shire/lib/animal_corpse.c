 /*
  * /d/Gondor/common/obj/rabbit_corpse.c
  *
  * Olorin, Apr 1993
  *
  * Modification log:
  * Modified to use /d/Gondor/common/obj/animal_corpse
  * Olorin, 26-may-1995
  * Modified to use weapon type and damage type of the knife
  * instead of "knife", "dagger" to determin if it is suitable
  * skinning. /Rohim 27-feb-2000
  *
  */
#pragma strict_types


#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

// global variables
int     skinned = 0;

void
create_object()
{
    ::create_object();

    set_animal_type(Animal_Type);
//    set_food_amount(100 + query_prop(CONT_I_WEIGHT)/10);
//    set_meal_file(OBJ_DIR + "prep_rabbit");
}

int
hook_query_prepared(string verb)
{
    NF("You have to skin and disembowel the "+Animal_Type+
    " before you can "+verb+" it!");
    return skinned;
}

/*
int
hook_setup_meal(string verb, object meal)
{
    if(!animal="rabbit")
        NF("You can't do that with the "+Animal_Type+".\n");
    
    if (verb == "cook" || verb == "stew")
        meal->add_name("_rabbit_stew");
    return 0;
}

void
interrupt_cooking(object pot, string what)
{
    int     i;
    object *contents;

    if (!objectp(pot) || (pot != ENV(TO)))
        return;
    if (!strlen(what) || what != "clean")
        return;
    contents = all_inventory(pot);
    write("To clean the pot, you remove the "
      + COMPOSITE_DEAD(contents = all_inventory(pot))
      + " from the pot.\n");
    for (i = 0; i < sizeof(contents); i++)
        contents[i]->move(TP, 1);
    stop_preparation(pot);
}
*/

int
do_skin(string str)
{
    object  pelt;
    object* knives;
    string  verb = LOW(query_verb());

    NF(CAP(verb) + " what?\n");
    if (!strlen(str) || (str != Animal_Type && str != "corpse of "+Animal_Type))
        return 0;

    knives = filter(this_player()->query_tool(-1), 
                   &operator(==)(, W_KNIFE) @ &->query_wt());
    
    if (!sizeof(knives))
    {
        write("You need a knife to "+verb+" the "+Animal_Type+".\n");
        return 1;
    }
    
    knives = filter(knives, &operator(&)(, W_SLASH) @ &->query_dt());
    
    if (!sizeof(knives))
    {
        write("You need a knife with a sharp edge to " + verb +
              " the "+Animal_Type+".\n");
        return 1;
    }

    if (skinned)
    {
        write("But the dead "+Animal_Type+" has already been skinned and disemboweled!\n");
        return 1;
    }

    skinned = 1;
    set_adj("skinned");
    remove_adj("dead");
    set_short(0);
    add_prop(CONT_I_WEIGHT,TO->query_prop(CONT_I_WEIGHT)-2000);
    add_prop(CONT_I_VOLUME,TO->query_prop(CONT_I_VOLUME)-1500);
    add_prop(OBJ_I_VOLUME,TO->query_prop(CONT_I_VOLUME));
    add_prop(OBJ_I_WEIGHT,TO->query_prop(CONT_I_WEIGHT));
    set_food_amount(100 + query_prop(CONT_I_WEIGHT)/10);

    if (TP->query_skill(SS_WEP_KNIFE) < 10 + random(10))
    {
        write("Inexpertly, you try to "+verb+" the "+
        Animal_Type+", but you completely ruin the pelt in the " +
        "process. All you are left with is the skinned body of " +
        Animal_Type+" the rabbit.");
       say(QCTNAME(TP)+" tries to "+verb+" a "+Animal_Type+
       ", but completely ruins the pelt in the process.\n");
       return 1;
  }

    write("You skillfully skin and disembowel the dead "+
        Animal_Type+". Now you have a skinned "+Animal_Type+
        " and a "+Animal_Type+ " pelt.");
    say(QCTNAME(TP) + " skillfully skins and disembowels a dead "+
        Animal_Type+".\n");
    FIX_EUID
    pelt = clone_object(OBJ_DIR + "animalpelt");
    pelt->add_prop("_skin_by_gresolle",4);
    pelt->move(ENV(TO));

    return 1;
}

public void
init()
{
    ::init();
    add_action(do_skin, "skin");
    add_action(do_skin, "disembowel");
}
