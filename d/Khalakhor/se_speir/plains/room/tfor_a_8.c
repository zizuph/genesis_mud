// temp forest room - Zima
#include "plains.h"
inherit "/d/Khalakhor/se_speir/plains/room/tforbase";
void create_khalakhor_room()
{
   create_tforest();
   add_exit(PLAINS+"tfor_a_6","southwest");
   add_exit(PLAINS+"tfor_a_9","southeast");
   add_exit(PLAINS+"tfor_a_10","north");
}
