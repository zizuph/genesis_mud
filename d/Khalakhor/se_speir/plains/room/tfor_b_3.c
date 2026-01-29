// temp forest room - Zima
#include "plains.h"
inherit "/d/Khalakhor/se_speir/plains/room/tforbase";
void create_khalakhor_room()
{
   create_tforest();
   add_exit(PLAINS+"tfor_b_2","south");
   add_exit(PLAINS+"tfor_b_6","northwest");
   add_exit(PLAINS+"tfor_b_9","northeast");
}
