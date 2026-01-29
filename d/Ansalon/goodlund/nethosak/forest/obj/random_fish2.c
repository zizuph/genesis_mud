inherit "/std/food";
#include "/sys/stdproperties.h"
#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include "/d/Ansalon/common/defs.h"

int gutted_fish;

void create_food()
{
    set_name("trout");
    add_name("fish");
    set_adj("young");
    set_long("This is a slimy trout. It has all the colors of the rainbow on its side.\n");

    add_prop(OBJ_I_VOLUME, 600);
    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VALUE, 0);
   
    gutted_fish = 0;

    set_amount(200);
  
    add_cmd_item(({"fish"}),"gut","@@gut_fish");
    add_cmd_item(({"fish"}),"cut","@@gut_fish");
    set_no_merge(1);
}


void
special_effect(int numoffood)
{
    object add;
    
    TP->add_fatigue(20);
    write("You feel less tired.\n");        
}


int
gut_fish()
{
    int chance;
    object obj;
    chance = random(5);

    if (gutted_fish == 1)
    {
        write("This fish has already been gutted!\n");
        return 1;
    }
    if(!P("knife",TP) && !P("dagger",TP))
    {
        write("But you don't have a knife to gut the fish!\n");
        return 1;
    }
  

    write("You gut the fish open.\n");
    write("You find nothing inside, and thus discard the fish again.\n");
    TO->remove_object();
    return 1;
}
