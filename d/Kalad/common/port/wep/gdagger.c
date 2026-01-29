inherit "/d/Kalad/std/weapon.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_weapon()
{
    ::create_weapon();
    set_name("dagger");
    set_adj("keen");
    set_long("A Kabal guardsman's dagger. The edge is extremely sharp, "+
      "probably sharp enough to slice off a man's fingers as easily as a "+
      "hot knife through butter.\n"+
      "Something has been enscribed on the hilt.\n");
    add_item(({"hilt"}),"Perhaps you should read it?\n");
    set_hit(10);
    set_pen(15);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    add_prop(OBJ_I_VALUE,300);
    add_prop(OBJ_I_WEIGHT,1500);
    add_prop(OBJ_I_VOLUME,1500);
}
void
init()
{
    ::init();
    add_action("read","read");
}
int
read(string s)
{
    if(!s || s != "hilt")
    {
	notify_fail("Read what? The hilt?\n");
	return 0;
    }
    write("Property of Delbin.\n");
    say(QCTNAME(TP) + " reads something on the keen dagger.\n");
    return 1;
}
