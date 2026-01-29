   inherit "/std/drink";
#include "/sys/stdproperties.h"
   
    create_drink()
    {
        set_soft_amount(95);
        set_alco_amount(2);
        set_name("ale");
        set_adj("watery");
        set_short("watery ale");
        set_pshort("watery ales");
        set_long("Its an almost clear mug of ale.\n");
        add_prop(OBJ_I_WEIGHT, 100);
        add_prop(OBJ_I_VOLUME, 100);
   }
