inherit "/std/weapon";
#include "/sys/wa_types.h"

#define ADJS ({"rusty", "dull", "plain", "low-quality"})

public void
create_weapon()
{
    string adj;

    adj = ADJS[random(sizeof(ADJS))];

    set_name("knife");
    set_pname("knives");
    set_adj(adj);
    set_short(adj + " knife");
    set_pshort(adj + " knives");
    set_long("It appears to be a " + adj + " knife.\n");

    set_hit(6 + random(3));
    set_pen(3 + random(3));

    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);

    set_hands(W_ANYH);
}
