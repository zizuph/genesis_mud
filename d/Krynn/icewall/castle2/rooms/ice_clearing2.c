#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;
inherit "/lib/unique";

#define ICE_YETI_FLEE_TIME "_ice_yeti_flee_time"
object wyeti;

int shield_found    =    0;
int yeti_is_here    =    1;
int figure_found    =    0;
int figure_blessed  =    0;
int xp_base         = 5000;

public void
reset_icewall_room()
{
    if (!wyeti)
    {
        if (yeti_is_here)
        {
            wyeti = clone_object(NPCK + "arcticyeti.c");
            wyeti->move_living("xx", TO);
            yeti_is_here = 1;
            shield_found = 0;
            figure_found = 0;
            figure_blessed = 0;
        }
    }
}
void
create_icewall_room()
{

    set_short("Deep in the old forest");
    set_long("@@long_descr@@");


    add_exit("ice_clearing1","northwest","@@northwest",1,1);

    add_item(({"figure","frozen figure"}),"@@figure");
    add_item(({"trees","black trees","frozen trees"}), "Black " +
        "ancient, and dead. Not much more could be said about them...\n\n" +
        "Wait! One of the trees, a mighty oak, appears brown under all that ice.\n");
    add_item(({"mighty oak","oak"}),"@@oak");
    add_item("forest","All around you, the trees stand frozen in " +
        "time. Thick ice chains the bushes, making any further progress " +
        "progress impossible.\n");
    add_item("bushes","The bushes, frozen into a wall of sharp slivers, " +
        "make a journey through this old section of the forest impossible. " +
        "The icy thorn bush to the northwest looks especially deadly.\n");
    add_item(({"icy thorn bush","thorn bush"}),"Hmm... with the ice " +
        "blurring the edges between air and snow, you failed to notice " +
        "that it would be possible to slip northwest around the thorn bush.\n");

    set_tell_time(900);

    add_tell("It is snowing hard... And white flakes begin to " +
        "cover you from head to toe.\n");
    add_tell("You think you have just heard a strange shriek " +
        "carried here by the everpresent freezing wind.\n");
    add_tell("Snow whirls about you, creating myriad of patterns... " +
        "There is a strange beauty in them...\n\n\n" +
        "You shiver and slap your face. It must be the cold.\n");
    add_tell("There is something about this place...\n\n\n" +
        "Something...\n\n\n" +
        "Your sixth sense is pounding hard at the back of your skull.\n");
    add_tell("The dark, icy forest looms above you.\n");

    reset_room();

}

void

enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

string
long_descr()
{
    string ret_str = "Against your reasoning and instinct you have " +
        "ventured far into the old area of the icy forest. " +
        "Thick, ancient trees have died here, and their " +
        "black corpses are slowly eaten by ice";

    if(!wyeti)
        ret_str += ". Somehow, you feel disappointed by this empty " +
            "place, as if your subconsciousness begun preparing " +
            "your for much more.";
    if(wyeti)
        ret_str += ". An ancient evil is here, awaiting you...";

    if(figure_found)
        ret_str += " Slumped under a mighty oak tree a frozen elf " +
            "lays in its final rest here.";

    ret_str += "\n";

    return ret_str;
}

int
northwest()
{
    if (wyeti) /* Carnak: Added a check to see if yeti is here */
    {
        if ((TP->query_prop(ICE_YETI_FLEE_TIME) > time() - 7) &&
            TP->query_attack())
        {
            write("You cannot try fleeing again so quickly!\n");
            TP->add_fatigue(TP->query_fatigue() / 15);
            return 1;
        }

        if (TP->query_attack() && random(100) > 10)
        {
            TP->add_prop(ICE_YETI_FLEE_TIME, time());
            write("You slip in the snow trying to run while in combat!\n");
            say(QCTNAME(TP)+" slips in the snow while trying to "+
            "run and fight at the same time!\n");
            
            if (TP->query_fatigue() > 10)
                TP->add_fatigue(-10);
            return 1;
        }
    }
    write("You breathe with relief as you leave the depths of the " +
        "dark forest.\n");
    say(QCTNAME(TP) + " appears relieved to be leaving.\n");
    return 0;
}

string
figure()
{
    if(!figure_found)
    {
        return "Examine what?! You see on such thing here.\n";
    }
 
    if(shield_found)
    {
        return "The figure slumped under the oak is elven, of " +
            "that can be no doubt. The ice has preserved the body " +
            "for years, for its skin is blue and almost transparent. " +
            "The elf, whoever he was, lays clad in delicately " +
            "ornated full platemail, and obviously fell in battle. " +
            "In his right hand, the dead elf holds a shattered longsword " +
            "but his left one is empty. " +
            "Upon his tunic, a symbol can be barely discerned - one " +
            "of a sleek tower standing proud in full sun. The emblem " +
            "of a royal guard of Sylvanos. The elf appears at peace.\n"; 
    }
 
    if(!figure_blessed)
    {
        return "The figure slumped under the oak is elven, of " +
            "that can be no doubt. The ice has preserved the body " +
            "for years, for its skin is blue and almost transparent. " +
            "The elf, whoever he was, lays clad in delicately " +
            "ornated full platemail, and obviously fell in battle. " +
            "In his right hand, the dead elf holds a shattered longsword " +
            "and in his left a large and strangely shaped shield. " +
            "Upon his tunic, a symbol can be barely discerned - one " +
            "of a sleek tower standing proud in full sun. The emblem " +
            "of a royal guard of Sylvanos.\n\nThe elf's face is wrought " +
            "with distress and anguish.\n"; 
    }

    return "The figure slumped under the oak is elven, of " +
        "that can be no doubt. The ice has preserved the body " +
        "for years, for its skin is blue and almost transparent. " +
        "The elf, whoever he was, lays clad in delicately " +
        "ornated full platemail, and obviously fell in battle. " +
        "In his right hand, the dead elf holds a shattered longsword " +
        "and in his left a large and strangely shaped shield. " +
        "Upon his tunic, a symbol can be barely discerned - one " +
        "of a sleek tower standing proud in full sun. The emblem " +
        "of a royal guard of Sylvanos.\n\nJudging by the elf's face, " +
        "he is finally at peace.\n"; 

}

string
oak()
{
    if(!wyeti) 
    {
        if(!figure_found)
        {
            say(QCTNAME(TP) + " finds a frozen figure slumped at the base of a " +
                "mighty brown oak.\n");
            figure_found = 1; 
            return "The oak has not blackened in all the years. It appears " +
                "asleep, as if waiting for spring's sun to thaw it thick " +
                "branches. As you marvel about it, your eyes catch the " +
                "sight of a frozen figure slumped at the base of the tree.\n";
 

        }
        
        return "The oak has not blackened in all the years. It appears " +
            "asleep, as if waiting for spring's sun to thaw it thick " +
            "branches. As you marvel about it, your eyes catch the " +
            "sight of a frozen figure slumped at the base of the tree.\n";
    }

    return "You cannot simply walk to the oak! First " +
        "do something about the yeti, or it will bite " +
        "your head off!\n";
 
}      

int
bless(string str)
{
    if(!figure_found)
    {
        write("Bless?! There is nothing worth blessing here! Or is there?\n");
        return 1;
    }

    if(str != "frozen figure")
    {
        notify_fail("Bless whom? The frozen figure?\n");
        return 0;
    }

    if(figure_blessed)
    {
        notify_fail("The dead elf already appears at peace.\n");
        return 0;
    }

    write("You bless the dead elf in the name of your faith, " +
        "muttering: Rest, hero. Whomever you defended in your final " +
        "moments made it to safety. There are no other corpses here." +
        "\n\nSuddenly, the snow whirls about, obscuring your vision. " +
        "When you look again, the elf's face has smoothed. At last, he " +
        "appears at peace.\n" + 
        "It makes you feel better.\n");
    say(QCTNAME(TP) + " raises " + HIS(TP) + 
        " hand and blesses the corpse, " +
        "muttering: Rest, hero. Whomever you defended in your final " +
        "moments made it to safety. There are no other corpses here." +
        "\n\nSuddenly, the snow whirls about, obscuring your vision. " +
        "When you look again, the elf's face has smoothed. At last, he " +
        "appears at peace.\n.\n");

    figure_blessed = 1;
    set_alarm(5.0,0.0,"shield");

    if (TP->test_bit("krynn", 3, 9))
    {
        TP->catch_msg("You feel strange... as if you repeated " +
            "your own footsteps.\n");
        return 1;
    }

    if(TP->query_average_stat() < 100)
        xp_base -= (1000);

    TP->catch_msg("You feel more experienced.\n");
    tell_room(E(TP), QCTNAME(TP) + " looks more experienced.\n", TP);
    
    TP->add_exp(xp_base, 0);
    TP->set_bit(3, 9);
    TP->change_prestige(1000);
    
    K_QUEST_LOG("quest", "Bless Frozen Corpse", TP, xp_base);       

    return 1;
}

int
shield()
{
    write("The frozen figure slumps further. The shield falls from " +
        "its dead grasp.\n");
    say("The frozen figure slups further. The shield falls from "+
        "its dead grasp.\n");
    switch(random(4))
    {
    case 1:
        {
            clone_object(UNIQUE(KARM + "silvanesti_shield",5,
                KARM + "crap_shield"))->move(TO);
            shield_found = 1;
            break;
        }
    case 2:
        {
            clone_object(UNIQUE(KARM + "silvanesti_shield",5,
                KARM + "crap_shield"))->move(TO);
            shield_found = 1;
            break;
        }
    case 3:
        {
            clone_object(KARM + "crap_shield")->move(TO);
            shield_found = 1;
            break;
        }
    case 4:
        {
            clone_object(KARM + "crap_shield")->move(TO);
            shield_found = 1;
            break;
        }
    default:
        {
            clone_object(UNIQUE(KARM + "silvanesti_shield",5,
                KARM + "crap_shield"))->move(TO);
            shield_found = 1;
            break;
        }
    }

    return 0;
}

void
init()
{
    ::init();

    add_action(bless, "bless");
}        
