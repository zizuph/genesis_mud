/*
 * Tom Bombadill's pants
 * By Finwe, January 2002
 */

inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("pants");
    set_short("pair of leather pants");
    add_adj("brown");
    set_long("This is a pair of leather pants. They are of " +
        "exceptional quality with a green belt.\n");
    add_item(({"girdle", "belt", "green belt"}),
        "The green belt is made of woven leather. It is threaded " +
        "through some belt loops at the top of the leather pants. " +
        "The belt is worn to help keep the pants on the wearer.\n");
    add_item(({"belt loops"}),
        "They are thin vertical straps at the top of the pants. " +
        "A belt is threaded through them\n");
    set_ac(4);
    set_am(({2,1,1,}));
    set_at(A_LEGS);
    add_prop(OBJ_I_VALUE, 9);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 100);

}
