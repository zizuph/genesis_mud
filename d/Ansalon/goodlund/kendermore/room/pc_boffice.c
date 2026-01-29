#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

inherit KENDERMORE_IN;

#define PLAYER_IS_IN_PC_CHAIR "_player_is_in_pc_char"

int in_chair;

void
reset_kendermore_room()
{
    return;
}

void
create_kendermore_room()
{
    set_short("A doctor's office");
    set_long("You stand in a small doctor's office. A heavy desk has been " +
        "pushed against the far wall nearby a large wall cabinet, and a " + 
        "hanging skeleton stares at you near the exit. The most unusual " + 
        "piece of furniture, though, is a large metal chair in the center " + 
        "of the room. Soft light flickers from a small, dim oil lantern " + 
        "with a greasy, black mantle.\n");  
    add_item(({"office", "doctor's office"}), "It seems the doctor is out.\n");
    add_item(({"chair", "metal chair"}) ,"It is mostly metal, lined with " + 
        "brown cushioning. A " +
        "metal footrest extends at an angle from the base of the seat. It " + 
        "appears to be a chair that a doctor would use in examining a " + 
        "patient. It looks like it can be turned to the doctor's liking, " + 
        "or perhaps even spun around in by a mischievous patient.\n"); 
    add_item(({"wall", "walls"}), "They are made of unadorned wood.\n");
    add_item("lantern", "Someone must refill it regularly, since it's " + 
        "still burning.\n");
    add_item(({"desk", "heavy desk"}), "It looks very worn by age, and has " + 
        "several drawers in the side.\n");
    add_item(({"cabinet", "wall cabinet"}), "It has been built into the " + 
        "wall, and has many drawers.\n");
    add_item(({"skeleton", "hanging skeleton"}), "You can't tell if it's " + 
        "real or not, but it appears to very accurately represent the human " + 
        "body.\n");

    add_cmd_item(({"drawers", "drawer"}), ({"open", "pull"}), "@@pull_drawer");

    in_chair = 0;
 
    add_exit(KROOM + "pc_upstairs", "up", "@@up_message");
    add_exit(KROOM + "pc_office", "south", 0);

    reset_kendermore_room();
    return;
}


string
pull_drawer()
{
    write("You pull open all the drawers, but find nothing!\n");
    say(QCTNAME(TP) + " pulls open all the drawers, looking in each one.\n");
    return "";
}

int
up_message()
{
    write("You head up the stairs with a loud CREEEEAAAAKKKK!\n");
    return 0;
}

int
spin_chair(string str)
{
    NF("Spin in what?\n");
    if ((!str) || (str == "around") || (str == "around in chair") || 
        (str == "chair") || (str == "in chair"))
    {
        if (TP->query_prop(PLAYER_IS_IN_PC_CHAIR))
        {
            write("You push the chair around and around, gaining speed. " + 
                "You pull your legs up, and let the chair spin quickly " + 
                "until it slows to a stop.\n");
            say(QCTNAME(TP) + " pushes the chair around and around, gaining " + 
                "speed. " + HE(TP) + " pulls " + HIS(TP) + " legs up, and " + 
                "lets the chair spin quickly until it slows to a stop.\n");
        }

        if (!TP->query_prop(PLAYER_IS_IN_PC_CHAIR))
            write("You should sit down first.\n");
        return 1;
    }
    return 0;
}

int
chair_sit(string str)
{
    if ((str == "in chair") || (str == "down"))
    {
        if (!in_chair)
        {
            write("You sit down in the large metal chair and rest your " + 
                "feet.\n");
            say(QCTNAME(TP) + " sits down in the large metal chair and " + 
                "rests " + HIS(TP) + " feet.\n");
            TP->add_prop(PLAYER_IS_IN_PC_CHAIR, 1);
            TP->add_prop(LIVE_S_EXTRA_SHORT, " is sitting in a chair");
            in_chair = 1;
            return 1;
        }

        if (in_chair)
        {
            if (!TP->query_prop(PLAYER_IS_IN_PC_CHAIR))
            {
                write("There's not enough room left in the large metal " + 
                    "chair for you.\n");
                say(QCTNAME(TP) + " eyes the chair.\n");
                return 1;
            }

            if (TP->query_prop(PLAYER_IS_IN_PC_CHAIR))
            {
                write("You are already seated!\n");
                return 1;
            }
        }
    }

    NF("Sit in what?\n");
    return 0;
}

int
stand_up(string str)
{
    if ((str == "up") || (!str))
    {
        if (TP->query_prop(PLAYER_IS_IN_PC_CHAIR))
        {
            write("You jump out of the large metal chair, feeling very " + 
                "refreshed.\n");
            say(QCTNAME(TP) + " jumps out of the large metal chair, looking " +
                "very refreshed.\n");
            TP->remove_prop(LIVE_S_EXTRA_SHORT);
            TP->remove_prop(PLAYER_IS_IN_PC_CHAIR);
            in_chair = 0;
            return 1;
        }

        if (!TP->query_prop(PLAYER_IS_IN_PC_CHAIR))
        {
            write("First you must be seated in order to stand!\n");
            return 1;
        }
    }

    NF("Stand up?\n");
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!living(ob))
        return;

    if (ob->query_prop(PLAYER_IS_IN_PC_CHAIR))
    {
        ob->catch_msg("You jump out of the large metal chair, feeling very " + 
            "refreshed.\n");
        ob->tell_watcher(QCTNAME(ob) + " jumps out of the large metal " +
            "chair, looking very refreshed.\n");
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        ob->remove_prop(PLAYER_IS_IN_PC_CHAIR);
        in_chair = 0;
        return;
    }

    return;
}

void
init()
{
    ::init();
    add_action(chair_sit, "sit");
    add_action(stand_up, "stand");
    add_action(spin_chair, "spin");
}

