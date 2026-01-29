inherit "/std/container";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>

#define MAX_FOOD 10
int alarm_id;
object *food;
create_container()
{
    set_name("tree");
    set_adj("apple");
    set_short("tree");
    set_pshort("trees");
    set_long("This is one of the many beautiful trees in Shire. "
    	    +"Green as a tree should be, and perhaps containing fruits.\n");
    	    
    add_prop(OBJ_M_NO_GET,1);
    add_prop(OBJ_M_NO_GIVE,1);    
    food = allocate(MAX_FOOD);
    enable_reset();
    add_food();
} 

void 
add_food()
{
    alarm_id = set_alarm(2.0,0.0,"make_food");
}

reset_container()
{
    add_food();
}


make_food()
{
    int i;

    i = 0;
    object *food = i to MAX_FOOD

    for (i=0; i + sizeof(food) < MAX_FOOD; i++)
        clone_object(BREE_DIR + "obj/fruit")->move(TO);
}
