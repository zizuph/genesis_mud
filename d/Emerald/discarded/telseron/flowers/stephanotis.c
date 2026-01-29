/*
 * stephanotis flower
 * Coded by Finwe
 * August 1996   
 */ 
 
inherit "/d/Emerald/telseron/flowers/flowers.c";
#include "/sys/language.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
 
public void
create_flower()
{
 
    set_name("stephanotis");
    set_short("flower");
    set_short("stephanotis");
    set_pname("stephanotises");
    set_fragrance(1);
    set_adj("white");
    set_long("A beautiful stephanotis flower. This white, tube shaped " +
        "is a favorite in bridal bouquets.\n");
    set_wilt_time(2560);
    set_flower_value(25);
    add_prop("_garden_flower", 1);
    add_prop(OBJ_I_VALUE, 25);
}
