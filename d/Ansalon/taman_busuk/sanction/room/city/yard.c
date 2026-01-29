/* Navarre June 20th 2006, Moved clone board to reset room,
   The board was occassionally not being cloned.
   Possibly because it was placed in the create room function
   and sometimes the room wasnt quite done being created before
   the object was moved to it.
   That should be fixed now.
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>

inherit SANCOUTROOM;

object m1,m2,m3;
object board;

reset_sanction_room()
{
    if(!objectp(m1))
    {
	m1 = clone_object(SNPC + "mercenary");
	m1->move(TO);
    }
    if(!objectp(m2))
    {
	m2 = clone_object(SNPC + "mercenary");
	m2->move(TO);
    }
    if(!objectp(m3))
    {
	m3 = clone_object(SNPC + "mercenary");
	m3->move(TO);
    }

    if(!objectp(board))
    { 
        board = clone_object(SOBJ + "normal_board");
        board->move(TO, 1);
    }
}

void
create_sanction_room()
{
    set_short("The marshalling yard in Sanction");
    set_long("@@long_descr");

    add_item(({"marshalling yard","yard"}),
      "The large cobbled area you stand in now is used as the " +
      "marshalling yard for the soldiers of the dragonarmy.\n");
    add_item(({"blackened pole","pole"}),
      "A blackened pole of wood with a notice board on it.\n");
    add_item(({"small stone office","stone office","building",
	"office building"}),
      "To your east stands a small stone office building, presently " +
      "occupied by dragonarmy staff.\n");

    add_exit(SCITY + "street11","northwest",0);
    add_exit(SCITY + "street19","northeast",0);
    add_exit(SCITY + "office","east",0);
    add_exit("/d/Genesis/room/common","common","@@enter_common");
    add_exit(SCITY + "discuss", "discuss");
    add_exit(SCITY + "forge_sw", "southwest", "@@enter_forge@@");
    add_exit(SCITY + "forge_s", "south", "@@enter_forge@@");
    add_exit(SCITY + "forge_se", "southeast", "@@enter_forge@@");
    reset_sanction_room();
}


string
long_descr()
{
    return "You are standing in the marshalling yard in " +
    "Sanction, where the eager warriors of the dragonarmies are gathered " +
    "for deployment. To your east stands a small stone office " +
    "building, while before you a board has been posted on a blackened "+
    "pole for the amusement of the soldiers as well as to pass " +
    "directives to them from their officers.\n";
}

int
enter_common()
{
    if(TP->query_dragonarmy_occ_member() ||
      TP->query_guild_member("Priests of Takhisis"))
    {
        return 0;
    }
    write("Only members of the dragonarmy may enter the " +
          "common board room!\n");
    return 1;
}

int
enter_forge()
{
    if(TP->query_dragonarmy_occ_member() ||
       TP->query_guild_member("Priests of Takhisis") ||
       TP->query_wiz_level())
    {
        return 0;
    }
    write("Only members of the dragonarmy may enter the " +
          "forge!\n");
    return 1;
}
