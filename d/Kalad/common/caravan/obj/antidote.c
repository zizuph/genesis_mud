#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#include <herb.h>
inherit "/std/potion.c";

/* A poison potion, can be bought in Caravan lot in shop */
/* Sarr 19.Mar.97 */
/*  Potion value is 0 for some reason
    Tried the following:
    #include <money.h>
    #include <std.h>
    editing out set_potion_value
    editing out OBJ_I_VALUE
    Edited both values out
    adding a space in <obj_i_valu, 800>
    putting add_prop(obj_i_value) at the bottom
    doing ::create_potion();
    
    Obviously i have no clue why add_prop(obj_i_value) doesnt work so i tried various random things :-)
    Meton 2021
  
    */

void
create_potion()
{
    set_name("potion");
    set_adj("black");
    add_adj("bubbling");
    set_short("black bubbling potion");

    set_id_long("This potion looks to be made out of foxglove and "+
      "spider venom converted in magical ways to make a spider poison "+
      "curing potion.\n");

    set_unid_long("It bubbles sinisterly, and looks rather foul.\n");

    set_unid_smell("It smells rather putrid.\n");
    set_id_smell("It smells rather putrid.\n");
    set_unid_taste("It tastes awful!\n");
    set_id_taste("It tastes awful!\n");
    set_potion_name("spider-cure");
    set_potion_value(800);
    add_prop(OBJ_I_VALUE, 800);
    add_prop(HEAP_I_UNIT_VALUE,800);
    set_effect(HERB_CURING,"spider",80);

    
}
