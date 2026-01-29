inherit "/d/Gondor/common/lib/field";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"

#define OTHER_ROOM (ANO_DIR + "druedain/rangerpath2")

void
create_room()
{
  areatype = 7;
  areadesc = "old path";
  area = "western";
  areaname = "the Druedain Forest";
  land = "Gondor";
  grass = "soft, light green ";
  treetype = "large oaks";
  extraline = "Large oak trees along with some birches line the path on both "+
    "sides, and their branches tangled together above your head, almost forming "+
    "a tunnel through the forest, running from the east to the west. To the "+
    "west you see two great oaks forming a portal, beyond which you see a "+
    "clearing. The dense woods leave you no chance to walk north or south though.";
  set_noshow_obvious(1);
  add_exit(ANO_DIR + "druedain/rangerfield","west","@@enter_portal",1);
  add_exit(ANO_DIR + "druedain/rangerpath2","east",0,1);
  add_item("clearing","There seems to be a clearing further west, beyond the portal.\n");
  add_item("path","The path is clear to see here. It leads east and west, and is\n"+
    "lined by a wall of trees on each side.\n");
  add_item(({"tunnel","branches"}),"The trees growing so tight together, and their branches tangled \n"+
    "into eachother above all makes it feel as if you're in a natural tunnel.\n");
  add_item(({"trees","birches","oak trees"}),"There are oaks and birches, growing quite close on both sides\n"+
    "of the path, creating a feeling of being inside a tunnel.\n");
  add_item(({"portal","oaks"}),"The portal is formed by two great oaks. From each a gigantic bough\n"+
    "grows upwards and towards the other, and then, as strange as it may\n"+
    "seem, the boughs grow together, as was it one giant oak with twin trunks!\n");
  make_the_room();
}

void
do_exp_bit(object player)
{
    if (player->test_bit("Gondor",GONDOR_GROUP, RANGER_TEST_BIT))
        return;
    FIX_EUID
    write("At the same time you feel a little more experienced.\n");
    player->add_exp(RANGER_TEST_EXP,0);
    player->set_bit(GONDOR_GROUP, RANGER_TEST_BIT);
    LOG_QUEST(player, RANGER_TEST_EXP, "RANGER TEST");
    return;
}

int
enter_portal()
{
    FIX_EUID
    if ( (TP->test_bit("Gondor", GONDOR_GROUP, RANGER_TEST_BIT)) &&
         (OTHER_ROOM->query_friend_or_foe(TP) > -1) )
    {
        write("You pass through the portal, and enter the clearing.\n");
        return 0;
    }
    if (objectp(present("Ranger_Test_Proof",TP)) &&
        !(OTHER_ROOM->query_trapped_today(TP->query_real_name())))
    {
        write("You pass through the portal, and enter the clearing.\n");
        do_exp_bit(TP);
        return 0;
    }
    write("Two rugged Rangers suddenly step out from behind the oaks of the\n"+
      "portal. They both hold their arms out, halting you, and one of them says:\n"+
      "      'You would be better off trying another day. You have to prove\n"+
      "       yourself worthy of visiting the Rangers of Gondor first.'\n"+
      "Then the two Rangers step back into the shadows.\n");
    say(QCTNAME(TP)+" tries to walk west through the portal, but is stopped\n"+
      "by two Rangers who advise "+TP->query_objective()+
      " to try another day instead.\n",TP);
    return 1;
}

