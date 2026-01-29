inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* A Sarr Industries production */

int pulled;

void
create_armour()
{
    ::create_armour();
    set_name("gloves");
    set_adj("long");
    add_adj("black");
    set_short("pair long black gloves");
    set_long("These gloves go all the way up your arms.\n");
    set_ac(1);
    set_af(TO);
    set_at(A_ARMS);
    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,15);
    add_prop(OBJ_I_VALUE,8);
}

int
wear(object what)
{
    write("You slip on the silky gloves, then rub your face with them to "+
    "feel the sexy silk on your face.\n");
    say(QCTNAME(TP)+" slips on the long black gloves, then rubs "+HIS(TP)+
    " face with them to feel the sexy silk.\n");
    TP->command("moan soft");
    return 1;
}

int
remove(object what)
{
    write("You remove the long black gloves slowly...finger by finger.\n");
    say(QCTNAME(TP)+" removes the long black gloves slowly, finger by finger.\n");
    TP->command("lick erotic");
    return 1;
}

