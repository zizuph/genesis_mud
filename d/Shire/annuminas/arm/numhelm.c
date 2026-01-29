inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name(({"helmet", "helm"}));
    set_short("brightly colored winged helmet");
    set_adj(({"colored","bright","winged", "numenorean"}));
    set_long("This winged helmet retains but a fraction of the "+
    "brilliant hues it must once have borne.  The decoration "+
    "of the helmet, with its reds, blues and yellows "+
    "make this helmet seem as if it were from another world, "+
    "or a long ago forgotten age.\n");
	
    set_ac(25);
    set_at(A_HEAD);
    
    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VALUE, 20*12*12);
    add_prop(OBJ_I_VOLUME, 1000);
}
