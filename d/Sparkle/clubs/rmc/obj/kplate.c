#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

inherit "/std/armour";

int wcl = random(10) + 25;

void
create_armour()
{
    set_name("platemail");
    set_pname("platemails");

    set_adj("golden");
    add_adj("ruby-speckled");

    set_short("ruby-speckled golden platemail");

    set_long(
        "This fine platemail looks like the most valuable "+
        "one of the most valuable in the whole world. The "+
        "plate is made of the hardest steel, coated with "+
        "a thick layer of gold and speckled with rubies.\n");

    set_ac(wcl);
    set_at(A_BODY);
    set_am( ({ 0, 0, 3 }) );

    add_prop(OBJ_I_WEIGHT, 9000 + random(1000));
    add_prop(OBJ_I_VOLUME, 4000 + random(1000));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(wcl));
}
