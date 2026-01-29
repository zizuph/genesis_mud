inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
   bring_room_mob("slave", TZ_MINTHOR+"npc/t_slave.c", 1);
}

void
create_room()
 {
  set_short("End of path");
  set_long("You have reached the end of the marble sidewalk. Here "
	+"there lies an amazing thing, a large pool of water. The "
	+"flowers and other plants are some of the greenest and "
	+"healthiest that are commonly seen in Tyr. The is a small dome "
	+"over the pool, helping to keep the sun from directly hitting "
	+"the water. There is also a small shrine to something here. "
	+"Back to the west lies the rest of the marble sidewalk, and "
	+"over the bushes to the northwest you can see the eastern "
	+"side of the large mansion.\n");
  add_item("pool","The pool is about 7 feet in diameter, and is filled "
	+"with clear water. This is an extreme rarity here.\n");
  add_item("dome","The dome is raises about 8 feet off the water, and "
	+"is slightly larger than the pool itself. It is perfectly "
	+"crafted to keep the sun off of the water.\n");
  add_item("shrine","It appears to be a small shrine dedicated to the "
	+"plane of water.\n");
  add_item(({"smell"}),"It smells like moisture, maybe even free "
        +"standing water!\n");
  add_item("sidewalk","It is made of a brilliantly polished marble, "
	+"and seems to be kept impeccably clean.\n");
  add_item(({"wall"}),"The wall is about 9 feet tall, and is made of "
        +"a dark grey granite. It would seem to protect decently well "
        +"against thugs and the like, as well as keep slaves in.\n");
  add_item(({"bushes","bush","plant","plants","flower","flowers"}),
	"They are brilliantly colored plants that must cost an "
	+"incredible amount of money to maintain.\n");
  add_item(({"building","house","mansion"}),"The building is somewhere "
	+"around four  stories tall(about 50 feet), and is covered in statues and "
        +"other decorative items.\n");
  add_item(({"statues","items"}),"They are nicely crafted and must "
        +"be very expensive, probably worth their weight in water.\n");
  add_cmd_item("to shrine","pray","You kneel down and pray to the life "
	+"giving water, hoping to alleve your stress and enhance your "
	+"life.\n");
  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  add_exit(TZ_MINTHOR + "mh6", "west", 0);
   reset_room();
}
void
init()
{
    ::init();
   add_action("drink","drink",0);
}

int
drink(string rest)
{
    object tp = this_player();
    string x,y,z;
    int c;


    c = 0;
    while (tp->drink_soft(50, 0) && c < 15)
        c++;

    if (!c) {
        write("You have drunk all that you can.\n");
        return 1;
    }

   say(QCTNAME(TP) + " drinks from the large pool.\n");
   write("You drink some water from the large pool.\n");
    return 1;
}

