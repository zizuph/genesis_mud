inherit "/d/Gondor/minas/lib/outgate";
#include "/d/Gondor/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "ngatedefs.h"
void
create_outgate()
{
    set_gfile1(GFILE1);
    set_ofile(OFILE);
    set_ogroom(OGROOM);
    set_igroom(IGROOM);
    set_igdir(IGDIR);
    set_gdir(GDIR);
    set_grtoog(GRTOOG);
    set_gopen(GOPEN);
    set_gclosed(GCLOSED);
    set_short("Before the Anorien Fort");
    add_item("fort",BSN("This is the Anorien Fort, a gatehouse protecting the gate which "+
    "the road from Anorien and Rohan to Minas Tirith passes through. "+
    "The road comes from the north crossing the green fields of Anorien, and "+
    "runs up to the gate to the south. The fort is made of thick "+
    "stone walls, and there are strong battlements on its top."));
    add_exit(ANO_DIR+"road/wr1","north","@@test_blocked",1);
    add_exit(ANO_DIR+"plains/an14w11n","northeast","@@test_blocked",1,1);
    add_exit(INGATE,IGDIR,1,1);
    seteuid(getuid(this_object()));
    /*
      clone_object("/d/Genesis/obj/wizquest/mage_stone")->move(this_object());
    */
}
int
test_blocked()
{
    int stopped;
    object attacker;
    attacker = TP->query_attack();
    if (objectp(attacker) && attacker->query_npc())
    /*
        if (present(objectp(attacker)) && 
          CAN_SEE(attacker,TP) &&
          CAN_SEE_IN_ROOM(attacker) &&
          attacker->query_npc())
    */
    {
    stopped = TP->query_stat(SS_DEX) - attacker->query_stat(SS_DEX) + 85;
    if (stopped < 0)
        stopped = 0;
    stopped = 12 - stopped/10;
    if (stopped < 1)
        stopped = 1;
    if (stopped > 10)
        stopped = 10;
    if (random(stopped))
    {
        write("The " + attacker->query_nonmet_name() + " stops you!\n");
        return 1;
    }
    }
    return 0;
}