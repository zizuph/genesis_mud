/* Filename:     /d/Krynn/qualinesti/obj/copper_ring.c
 * Original Description:  This ring makes the wearer impossible to be located by
 *                        scry spells. The weaer must be good aligned for the ring
 *                        to work.
 * Coder:        Blizzard, June 2005
 *
 * Note by Navarre, November 22th 2005:
 *
 * This item was one of many inappropriate items that was created.
 * It originally made any goodaligned player immune to be scryed.
 * I added a log file to the item, when a player wears it, his name
 * will be written to a log file, since the artifact was extremely 
 * well hidden, this will give us an idea about who is actually getting
 * this artifact.
 * The scry immunity has been removed, but I have left the message the same
 * not to scare off anyone who thinks it is good.
 * I altered the magical information about the ring, and to keep it magic
 * I have added a little amount of panic to the player as he wears it.
 */

inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

void
create_armour()
{
    set_name("ring");
    set_adj("copper");
    set_short("copper ring");
    set_at(A_ANY_FINGER);
    set_long("You don't see anything special in this ring. However, you " +
        "have a feeling that this small copper ring is not so simple " +
        "as it looks, or maybe it is?\n");

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO, ({
        "The ring is enchanted with some spell.\n", 5,
        "The ring makes the wearing feel a little paranoid about being "+
        "watched when wearing it.\n", 20}));
    add_prop(OBJ_S_WIZINFO,"The ring adds a little panic to the wearer as he is "+
                           "being a little paranoid when wearing it.\n");
    set_ac(1);
    set_af(TO);
    add_prop(OBJ_I_WEIGHT,  50);
    add_prop(OBJ_I_VOLUME,  30);
    add_prop(OBJ_I_VALUE, 0);
}


private void
write_to_log()
{
    if(!TP->query_wiz_level())
    {
      setuid();
      seteuid(getuid());
      log_file("suspicious_items/suspicious_items.log",ctime(time())+": "+TP->query_name()+
                " wore this suspicious item: "+
                this_object()->query_short()+" located at: "+
                file_name(this_object())+
               "\nThe suspicious effects has been removed, but we keep "+
               "track of the item for abusers.\n\n", 0);
    }
}

public int
wear(object what)
{
    if (TP->query_alignment() > 100)
    {
        write("As you wear the copper ring, you have a feeling of being " +
            "watched.\n");
        TP->add_panic(200);
        write_to_log();

        return 1;
    }
    write_to_log();       
    return 0;
}
