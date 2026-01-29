#pragma save_binary

inherit "/d/Gondor/common/guild/lib/councilroom";

#include "/d/Gondor/defs.h"

#define COMPANY_NUMBER 2

void create_councilroom()
{
  set_long(BSN("This small rough rock chamber is the office of the "+
    "Council of "+
    "Rangers, in Henneth Annun. It is furnished only with a board and "+
    "a long settle. The room can be used by the Captains to "+
    "discuss the future of the Rangers, and to communicate with the "+
    "Chieftain of the Rangers. "+
    "A poster on the wall explains the commands that are available "+
    "to council members here."));

  add_exit(RANGER_ITH_DIR+"rockchamber", "north", check_sitting, 0, 1);

  seteuid(getuid());
  clone_object(RANGER_ITH_DIR+"rdoor2")->move(TO, 1);
  clone_object(BOARD_DIR + "council_board")->move(TO, 1);

  set_company_number(COMPANY_NUMBER);
}

void init()
{
  ::init();
  init_council_room();
}
