#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KALAMAN_IN;
object door;
object merchant;

#define RESCUED_MERCHANT "_i_rescued_the_sanction_merchant"
#define GIVEN_QUEST "_given_ansalon_merchant_quest"

void
reset_kalaman_room()
{
    if(!objectp(merchant))
    {
	merchant = clone_object("/d/Ansalon/taman_busuk/sanction/npc/quest_merchant2");
	merchant->arm_me();
	merchant->move(TO);
    }
}

create_kalaman_room()
{
    set_short("Merchants office");
    set_long("@@long_descr");

    add_item(({"office","merchants office","pleasant little office","little office"}),"@@long_descr");
    add_item(({"darkwood desk","beautiful darkwood desk",
	"dark wood desk","desk"}),
      BSN("A beautiful darkwood desk, where the rich merchant does most of his work."));

    add_exit(KROOM + "warehouse","down",0);
    door = clone_object("/d/Ansalon/kalaman/obj/door1a");
    door->move(TO);

}

string
long_descr()
{
    string str;

    str = "You stand in a pleasant little office of a rich merchant. It seems much of its " +
    "finery has been moved to a safer location, as all that is left here is a beautiful darkwood " +
    "desk.";

    return BSN(str);
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if(objectp(merchant) && ob->query_prop(RESCUED_MERCHANT))
    {
	merchant->quest_spool(ob);
    }

    if(objectp(merchant) && ob->query_prop(GIVEN_QUEST))
    {
	merchant->return_response(ob);
    }
}
