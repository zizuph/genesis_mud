#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include "/sys/wa_types.h"

#define ADJS ({"sandy", "black", "odd", "strange-looking"})
#define TYPE ({A_R_FOOT, A_L_FOOT})

create_terel_armour()
{
    string adj;
    int type;

    adj = ADJS[random(sizeof(ADJS))];
    type = TYPE[random(sizeof(TYPE))];

    set_name("shoe");
    set_adj(adj);
    set_long("This " + adj + " leather shoe appears to have been " +
             "buried in sand for a long time.\n");

    set_default_armour(2 + random(3), type, 0, 0);
}
