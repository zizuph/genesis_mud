/* Defence Master Training Room. Where Knights train weapon skills. */
/* Taken from Teth's adventurer's guild and the old Keep training   */
/* Rooms. By Morrigan, Jan 97                                       */

#include "../../guild.h"
#include <macros.h>
#include <ss_types.h>

inherit TRAIN_BASE;
inherit IN_BASE;

/* Global variables */

object kn1, kn2, kn3;

void
set_up_skills()
{
    sk_add_train(SS_BLIND_COMBAT, "fight while blinded", 0, 0, 60);
    sk_add_train(SS_DEFENCE, "dodge attacks",  0, 0, 75 );
    sk_add_train(SS_PARRY, "parry blows",     0, 0, 90 );
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
    object trainer;
    
    trainer = query_guild_trainer();
    if (!objectp(trainer))
    {
        trainer = clone_object(VNPC + "constance.c");
        set_guild_trainer(trainer);
        trainer->move(TO);
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

    string description = "This is where the Squires train in the arts of "+
                         "warfare and battle.";
    
    if (!P(kn1, TO) && !P(kn2, TO) && !P(kn3, TO))
    {
        str = " There are currently no Knights and Squires training here, "+
              "a bad sign indeed!";
    }
    else
    {    
        str = " The courtyard rages with Squires in mock combat, "+
              "sparring each other, occasionally sparring the Knights who instruct "+
              "them. You see most of the Squires here being instructed on how to "+
              "dodge and parry blows. ";
    }
    
    if (!P(query_guild_trainer(), TO))
    {
         return description + str +"Oddly, you see no trainer here...\n";
    }

    return description + str +gTrainer->query_The_name(TP)+" walks through "+
           "the courtyard calmly, giving tips to the training Squires.\n";
}

public void
create_vin_room()
{
    set_short("In the Inner Courtyard of Vingaard");
    set_long("@@long_desc");
    
    AE(VROOM + "inner_court", "west",0);
    AE(VROOM + "east_train2", "east", 0);

    add_prop(ROOM_M_NO_TELEPORT, "The walls of Vingaard Keep prevent " +
             "teleportation in this area... or is it something else?\n");
    
    create_skill_raise();
    set_up_skills();
    
    reset_vin_room();
}
