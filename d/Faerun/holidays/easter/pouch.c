inherit "/std/receptacle.c";
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>

#define EASTER_DIR      "/d/Faerun/holidays/easter/"

void
create_receptacle()
{

    int i;

    setuid(); seteuid(getuid());

    set_name("pouch");
    set_adj("braided");
    set_adj("wooden");
    set_short("braided wooden pouch");
    set_pshort("braided wooden pouches");
    set_long("This is a " + query_short() + ". It is small and made from flexible wooden strips. The pouch is supple and soft.\n");

    add_item(({"wood strips", "strips of wood", "flexible strips of wood", "wood"}),
        "The flexible strips of wood are thin and wide. They have been braided together and form pouch.\n");


    add_prop(CONT_I_WEIGHT,      500); 	
    add_prop(CONT_I_VOLUME,     2000);
    add_prop(CONT_I_MAX_WEIGHT, 2500); 	
    add_prop(CONT_I_MAX_VOLUME, 4000);
    add_prop(OBJ_I_VALUE,        150);
    add_prop(CONT_I_CLOSED,     0);
    add_prop(CONT_I_RIGID,      0);
    add_prop(CONT_I_TRANSP,     0);

    for(i=0; i<25; i++)
    {
        clone_object("/d/Faerun/holidays/easter/jbean2")->move(this_object(), 1);
    }
 
        
}
