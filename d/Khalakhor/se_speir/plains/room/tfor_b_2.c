// temp forest room - Zima
#include "plains.h"
inherit "/d/Khalakhor/se_speir/plains/room/tforbase";
void create_khalakhor_room()
{
   create_tforest();
   add_exit(PLAINS+"tfor_b_3","north");
   add_exit(PLAINS+"tfor_b_4","east");
   add_exit(PLAINS+"tfor_b_1","south");
}
