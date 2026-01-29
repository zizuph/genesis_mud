inherit "/std/receptacle";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_container()
{
    set_name("basket");
    set_pname("wicker baskets");
    set_short("wicker basket");
    set_adj("wicker");
    set_long("The basket has seen better days.\n");

    add_prop(CONT_I_WEIGHT, 250);  /* It weights 250 grams */
    add_prop(CONT_I_MAX_WEIGHT, 2250);     /* It can hold 2000 grams*/
    add_prop(CONT_I_VOLUME, 30);   /* Only 30 ml volume (very small) */
    add_prop(CONT_I_MAX_VOLUME, 2030);     /* 2 litres of volume */ 

    make_fruit();
}


make_fruit()
{

    object fruit;
    int n;

    seteuid(getuid(this_object()));
    for (n=0;n < 10;n++)
    {
	fruit = clone_object("/d/Kalad/common/port/obj/rfruit");
	fruit->move(TO);
    }

}
