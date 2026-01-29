/* Sword Master Training Room. Where Knights train guru sword.    */
/* Taken from Teth's adventurer's guild and the old Keep training */
/* Rooms. By Morrigan, Jan 97                                     */

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
    sk_add_train(SS_WEP_SWORD, "use a sword like a master",  0, 0, 100 );
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
        trainer = clone_object(VNPC + "andreg.c");
        set_guild_trainer(trainer);        
        trainer->move(TO);
    }
 
    if (!kn1)
    {
        kn1 = clone_object(VNPC + "gunthar_guard");
        kn1->move(TO);
    }
 
    if (!kn2)
    {
        kn2 = clone_object(VNPC + "gunthar_guard");
        kn2->move(TO);
    }
 
    if (!kn3)
    {
        kn3 = clone_object(VNPC + "gunthar_guard");
        kn3->move(TO);
    }
}

string
long_desc()
{
    string str;
 
    string description = "This is a significantly quieter part of the "+
                         "courtyard.";
    
    if (!P(kn1, TO) && !P(kn2, TO) && !P(kn3, TO))
    {
        str = " There are currently no Knights training here, a bad sign "+
              "indeed!";
    }
    else
    {
        str = " You don't see any Squires training here, as you did "+
              "to the east, but rather you see a few Knights. Most are "+
              "sparring with each other, but some are practicing alone. You "+
              "also notice that most of them seem to be quite skilled with "+
              "the swords they are using.";
    }
    if (!P(query_guild_trainer(), TO))
    {
        return description +str+ " Oddly, you see no trainer here...\n";
    }
    
    return description +str+ " "+gTrainer->query_The_name(TP)+" stands in the "+
           "center of the Courtyard here, tall and imposing. Occasionally, "+
           "he will comment to a training Knight, but for the most part he "+
           "remains silent.\n";
}
public void
create_vin_room()
{
    set_short("In the Inner Courtyard of Vingaard");
    set_long("@@long_desc");
    
    AE(VROOM + "train1", "east", 0);

    add_prop(ROOM_M_NO_TELEPORT, "The walls of Vingaard Keep prevent " +
             "teleportation in this area... or is it something else?\n");
    
    create_skill_raise();
    set_up_skills();
    
    reset_vin_room();
}

public varargs int
sk_hook_allow_train(object who, string str, string verb)
{
    if (!::sk_hook_allow_train(who, str, verb))
    {
        return 0;
    }
    
    object trainer;
    
    trainer = query_guild_trainer();
    if (!(who->test_bit("Krynn", 1, 6)))
    {
        trainer->command("say You've not yet proved yourself worthy to "+
                          "be trained by me.");
        trainer->command("smile sli");
        return 0;
    }
    
    return 1;
}
