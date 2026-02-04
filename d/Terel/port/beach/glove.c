#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include "/sys/wa_types.h"

#define ADJS ({"worn", "peculiar", "wet", "cheap-looking"})
#define TYPE ({A_R_HAND, A_L_HAND})

create_terel_armour()
{
    string adj;
    int type;

    adj = ADJS[random(sizeof(ADJS))];
    type = TYPE[random(sizeof(TYPE))];

    set_name("glove");
    set_adj(adj);
    set_long("This " + adj + " leather glove appears to have been " +
             "buried in sand for a long time.\n");

    set_default_armour(2 + random(3), type, 0, 0);
}
