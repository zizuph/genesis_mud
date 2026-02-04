#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include "/sys/wa_types.h"

#define ADJS ({"black", "brown", "strange-looking"})

create_terel_armour()
{
    string adj;

    adj = ADJS[random(sizeof(ADJS))];

    set_name("hat");
    set_adj(adj);
    set_long("This " + adj + " hat appears to have been buried in sand " +
	     "for a long time.\n");

    set_default_armour(1 + random(2), A_HEAD, 0, 0);
}
