inherit "/std/weapon";
#include "/sys/wa_types.h"

void
create_weapon()
{
    string *arr;
    int n;

    set_name("rapier");

    arr = ({"sharp",26, "slender",22, "engraved", 26, "nimble",28,
           "edged",24, "flexible",24, "bent",18, "etched",26,
            "bloodied",24, "dirty",18, "ancient",28, "swashbuckling",31,
           "masters",38, "silver",34, "shimmering",40});

    n = random(sizeof(arr)/2)*2;
    if (strlen(arr[n])) set_adj(arr[n]);
    set_long("This "+short()+" seems to be a pirates weapon.");

    set_hit(arr[n+1]);
    set_pen(random(5)+20);
    set_wt(W_SWORD);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_ANYH);
}
