#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include <wa_types.h>

void
create_terel_armour()
{
     set_name(({"boots", "pair of boots"}));
     set_pname(({"pairs of boots","armours"}));
     set_short("pair of tempered steel boots");
     set_pshort("pairs of tempered steel boots");
     set_long("It is a pair of boots cast in tempered steel with an  "+
	    "articulating ankle and lined with fur. These steel boots look "+
        "like the ones rumoured to be worn by the tomb dwellers.\n");	 
     set_adj(({"steel", "articulating", "tempered", "tomb", 
        "dweller", "zombie"}));
     set_default_armour(35, A_FEET, 0, 0);
    }
