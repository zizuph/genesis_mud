// temp forest room - Zima
#include "plains.h"
inherit "/d/Khalakhor/se_speir/plains/room/tforbase";
void create_khalakhor_room()
{
   create_tforest();
   add_exit(PLAINS+"tfor_a_3","northeast");
   add_exit(PLAINS+"tfor_a_4","northwest");
   add_exit(PLAINS+"tfor_a_1","south");
}
