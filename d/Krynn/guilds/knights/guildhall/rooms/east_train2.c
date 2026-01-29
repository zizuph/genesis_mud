/* Special Master Training Room. Where Knights train block, rescue,     */
/* and awareness. Taken from Teth's adventurer's guild and the old Keep */
/* training rooms. By Morrigan, Jan 97                                  */

#include "../../guild.h"
#include <macros.h>
#include <ss_types.h>

inherit TRAIN_BASE;
inherit IN_BASE;

#include "/d/Genesis/specials/debugger/debugger_tell.h"

/* Global variables */

object kn1, kn2, kn3;
int levlim;

void
set_up_skills()
{
    sk_add_train(SS_RESCUE, "rescue others in combat", "rescue", 100, 100 );    
    sk_add_train(SS_BLOCK, "block opponents from fleeing", "block", 100, 100);
    sk_add_train(SS_AWARENESS, "be aware of the surroundings", 0, 0, 60);
}

public void
init()
{
    init_skill_raise();
    ::init();
}

public void
reset_vin_room()
{
    if (!objectp(query_guild_trainer()))
    {
        set_guild_trainer(clone_object(VNPC + "bernard.c"));
        query_guild_trainer()->move(TO);
    }

    if (!kn1)
    {
        kn1 = clone_object(NPCSTD + "vin_knight_base");
        kn1->move(TO);
    }

    if (!kn2)
    {
        kn2 = clone_object(NPCSTD + "vin_knight_base");
        kn2->move(TO);
    }

    if (!kn3)
    {
        kn3 = clone_object(NPCSTD + "vin_knight_base");
        kn3->move(TO);
    }

}

string
long_desc()
{
    string str;

    string description = "This area is considerably less crowded than "+
                         "the other areas of the Courtyard.";

    if (!P(kn1, TO) && !P(kn2, TO) && !P(kn3, TO))
    {
        str = " There are currently no Knights and Squires training here, "+
              "a bad sign indeed! ";
    }
    else
    {
        str = " You find it strange to see that most "+
              "of the training Knights and Squires here do not even wield "+
              "weapons. If you didn't know any better, you might think they "+
              "were dancing as they move around in mock combat. ";
    }

    if (!P(query_guild_trainer(), TO))
    {
        return description + str +"Oddly, you see no trainer here...\n";
    }
    return description + str +query_guild_trainer()->query_The_name(TP)+" casually "+
           "strolls around the area, often stopping to demonstrate the "+
           "proper technique, or to offer advice to a trainee.\n";
}

public void
create_vin_room()
{
    set_short("In the Inner Courtyard of Vingaard");
    set_long("@@long_desc");

    AE(VROOM + "train2", "west", 0);

    add_prop(ROOM_M_NO_TELEPORT, "The walls of Vingaard Keep prevent " +
             "teleportation in this area... or is it something else?\n");
 
    create_skill_raise();
    set_up_skills();

    reset_vin_room();
}

