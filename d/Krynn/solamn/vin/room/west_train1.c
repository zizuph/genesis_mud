/* Sword Master Training Room. Where Knights train guru sword.    */
/* Taken from Teth's adventurer's guild and the old Keep training */
/* Rooms. By Morrigan, Jan 97                                     */

#include "../knight/guild.h"
#include <macros.h>
#include <ss_types.h>

inherit IN_BASE;
inherit "/lib/skill_raise";

/* Global variables */

object gTrainer, kn1, kn2, kn3;
int levlim;

/* Prototypes */

public void
set_up_skills();


public void
reset_vin_room()
{
    if (!gTrainer)
        {
        gTrainer = clone_object(VNPC + "andreg.c");
        gTrainer->move(TO);
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
        str = " There are currently no Knights training here, a bad sign "+
    "indeed!";
    else
        str = " You don't see any Squires training here, as you did "+
    "to the east, but rather you see a few Knights. Most are "+
    "sparring with each other, but some are practicing alone. You "+
    "also notice that most of them seem to be quite skilled with "+
    "the swords they are using.";
    
    if (!P(gTrainer, TO))
        return description +str+ " Oddly, you see no trainer here...\n";
    
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

public void
init()
{
    init_skill_raise();
    ::init();
}

void
set_up_skills()
{
    sk_add_train(SS_WEP_SWORD, "use a sword like a master",  0, 0, 100 );
}

int
sk_improve(string sk)
{
    if (sk)
        {
        if (!MEMBER(TP))
            {
            NF("You are no member of this guild, you cannot train "+
                "here.\n");
            
            write("Only Knights of Solamnia can improve their skills "+
                "here.\n");
            return 1;
        }
    }
    
    if (!P(gTrainer, TO))
        {
        write("The trainer isn't here to train you.\n");
        return 1;
    }
    
    if (REALAGE(TP) < TP->query_skill(SS_DISGRACED))
        {
        write("You are currently banned from training!\n");
        return 1;
    }
    
    if (!(TP->test_bit("Krynn", 1, 6)))
        {
        gTrainer->command("say You've not yet proved yourself worthy to "+
            "be trained by me.");
        gTrainer->command("smile sli");
        return 1;
    }
    
    TP->remove_skill(SS_DISGRACED);
    
    return ::sk_improve(sk);
}

int
sk_query_max(int snum)
{
    int klev, mxtrain, *skills_available_here;
    mixed skval;
    object pl;
    
    /* Added to adapt to the skill_decay function.            */
    /* If a skill isn't available here, this function should  */
    /* return 0.               Jeremiah, 95/07/09             */
    
    skills_available_here = sk_query_train();
    
    if(member_array(snum, skills_available_here) == -1)
        return 0;
    
    if (!this_player() || ((this_player() != previous_object()) &&
                previous_object() != this_object()))
    pl = previous_object();
    else
        pl = this_player();
    
    klev = pl->query_knight_level();
    mxtrain = MAX_TRAIN[klev];
    
    if (!mappingp(sk_default))
        return 0;
    
    skval = sk_trains[snum];
    
    if (skval[2] < mxtrain)
        {
        mxtrain = skval[2];
        levlim = 0;
    }
    else
        levlim = 1;
    
    if (sizeof(skval) > 2)
        return mxtrain;
    else
        return 0;
}

int
sk_hook_improved_max(string skill)
{
    notify_fail("You cannot raise this skill any further here, you have to\n" +
            "seek knowledge elsewhere.\n");
    if (levlim)
        notify_fail("Sorry but your order doesn't allow you to train\n" +
            "to that level in this skill.\n");
    return 0;
}


