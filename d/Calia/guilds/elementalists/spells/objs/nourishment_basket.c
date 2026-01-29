
/* 
 *  Nourishment Basket for the Elemental Clerics
 *  February, 2017
 */


inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>

#include "defs.h"

#define GELAN_FOODS "/d/Calia/gelan/objects/"
private string * foods = 
    ({"apple","banana","beetroot","broccoli","celery","melon","orange"});
            
public void
fill_basket()
{
    int num_foods, food_selection, quant_food, i, j;
    string current_fruit;
    object FRUIT, FLAGON;
    
    num_foods = random(7) + 1;
       
    for (i=0; i < num_foods; i++)
    {
        food_selection = random(sizeof(foods));
        quant_food = random(5) + 1;

        setuid(); 
        seteuid(getuid());
        current_fruit = (GELAN_FOODS + foods[food_selection]);
        FRUIT = clone_object(current_fruit);
        FRUIT->set_heap_size(quant_food);
        FRUIT->move(this_object(),1);

    }
    
    setuid(); 
    seteuid(getuid());
    FLAGON = clone_object(ELEMENTALIST_OBJS + "flagon");
    FLAGON->move(this_object(), 1);   
}

public void
remove_object()
{
    tell_object(environment(this_object()),"The nourishment basket "+
        "disappears!\n");
    ::remove_object();
}

void
create_container()
{
    set_name("basket");
    add_name("_cleric_nourishment_basket");
    set_adj("nourishment");
    add_adj("large");
    set_short("large nourishment basket");
    set_long("This is a large nourishment basket. It is summoned from the "+
        "trefo prayer and contains items of nourishment. You suspect the "+
        "basket won't stay around forever so you should probably remove "+
        "any items you want out of it before it disappears.\n"); 

    add_prop(CONT_I_MAX_WEIGHT, 2500);
    add_prop(CONT_I_MAX_VOLUME, 2500);
    add_prop(CONT_I_WEIGHT, 250);
    add_prop(CONT_I_VOLUME, 250);
    add_prop(OBJ_M_NO_DROP, "You cannot drop the nourishment basket.\n");
    add_prop(OBJ_M_NO_GIVE, "You cannot give the nourishment basket away.\n");
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_SELL,1);
    if (IS_CLONE)
    {
        set_alarm(1.0,0.0,fill_basket);
        set_alarm(600.0,0.0,remove_object);
    }
        
}
