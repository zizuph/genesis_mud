inherit "/std/drink";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

/*
 * /d/Kalad/common/guilds/khiraa/dk/obj/fouled_drink.c
 * Purpose    : Poisoned food from Knight spell
 * Located    : Knight spell 'foul food'
 * Created By : Sarr 17.Mar.97
 * Modified By: 
 */

#define IS_DK_FOULED_FOOD  "_is_dk_fouled_food"   

void
create_drink()
{
   set_soft_amount(10);
   set_alco_amount(0);
   set_name("drink");
   set_adj("fouled");
   set_short("fouled drink");
   set_long("A fouled drink.\n");
   add_prop(OBJ_I_WEIGHT,125);
   add_prop(OBJ_I_VOLUME,125);
   add_prop(IS_DK_FOULED_FOOD,1);
}




void
special_effect(int num)
{
    int i;
    object poison;
    seteuid(getuid());
    if(TP->query_prop(LIVE_I_UNDEAD))
        return;
    for(i=0;i<num;i++)
    {
        poison = clone_object(DK_DIR(obj/food_poison));
        poison->move(TP);
        poison->start_poison();
    }
}

