/* sld_chtn: A shield made from the shell of a giant insect. */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/d/Cirath/common/defs.h"

void create_armour()
{
    set_name("shield");
   set_short("red bone shield");
   set_long("This is a shield made from a large bone.  You imagine "
	+"it came from a giant because it is so huge.  Its hard to "
	+"tell because it is covered in red paint and draped "
     +"with a small leather tabard.\n");
    set_adj("bone");
    add_adj("red");

    set_ac(40);
    set_at(A_SHIELD);

    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(OBJ_I_VOLUME, 4500);
}
