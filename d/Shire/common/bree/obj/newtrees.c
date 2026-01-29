inherit "/std/container";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>

#define MAX_FOOD 10
//int alarm_id;
object food;
create_container()
{
    seteuid(getuid(TO));
    set_name("tree");
    set_adj("apple");
    set_short("tree");
    set_pshort("trees");
    set_long("This is one of the many beautiful trees in Shire. "
    	    +"Green as a tree should be, and perhaps containing fruits.\n");
    	    
    add_prop(CONT_I_VOLUME, 4000000);
    add_prop(CONT_I_WEIGHT, 5000000); 
    add_prop(CONT_I_MAX_VOLUME, 1200000);
    add_prop(CONT_I_MAX_WEIGHT, 10000000);
    add_prop(OBJ_M_NO_GET,1);
    add_prop(OBJ_M_NO_GIVE,1);    
    //food = allocate(MAX_FOOD);
    //enable_reset();
    //add_food();
    food = clone_object(BREE_DIR + "obj/fruit");
    food->move(TO);
    reset_container();

} 
/*
void 
add_food()
{
    alarm_id = set_alarm(2.0,0.0,"make_food");
}
*/

reset_container()
{
    if (!food)
    {
    food = clone_object(BREE_DIR +"obj/fruit");
    food->move(TO);
    }
    //add_food();
}
/*
int
check_orange(object thing)
{
    return function_exists("create_food", thing) == BREE_DIR + "obj/fruit";
}	
*/
/*
make_food()
{
    // Ok, we now must check how much food there is in the tree.
    int i;
    object *food = filter(all_inventory(TO), "check_orange", TO);

    for (i=0; i + sizeof(food) < MAX_FOOD; i++)
        clone_object(BREE_DIR + "obj/fruit")->move(TO);
}
*/    