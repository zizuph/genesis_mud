/* Dwarven camp by Morrigan */
/* Where lost dwarf quest begins, using bit 4, 0 */

#include "/d/Krynn/haven/local.h"
#include <macros.h>

inherit CAMPBASE;

#define I_KILLED_DWARVES "_i_killed_dwarves"

object colin, dwarf1, dwarf2;

// Prototypes
string my_desc();

void
reset_haven_room()
{
    if (!objectp(colin))
    {
        colin = clone_object(DNPC + "colin");
        colin->move(TO);
    }
    if (!objectp(dwarf1))
    {
        dwarf1 = clone_object(DNPC + "colin_guard");
        dwarf1->move(TO);
    }
    if (!objectp(dwarf2))
    {
        dwarf2 = clone_object(DNPC + "colin_guard");
        dwarf2->move(TO);
    }
}

void
create_camp()
{
    add_my_desc(my_desc);

    add_exit(DROOM + "camp8", "north");
    /*
        add_exit(DROOM + "camp12", "south", "@@go_south");
        add_exit(DROOM + "camp9", "west", "@@go_south");
        add_exit(DROOM + "camp11", "east", "@@go_south");
    */

    OUTSIDE;
    reset_haven_room();
}

int
go_south()
{
    object temp, colin_here, dwarf1_here, dwarf2_here;
    
    colin_here = present(colin, TO);
    dwarf1_here = present(dwarf1, TO);
    dwarf2_here = present(dwarf2, TO);

    if (!colin_here && !dwarf1_here && !dwarf2_here)
    {
        return 0;
    }
    
    if (!colin_here)
    {
        if (dwarf1_here)
            temp = dwarf1;
        else
            temp = dwarf2;

        if (!CAN_SEE(temp, TP))
            return 0;

        write(QCTNAME(temp)+" shoves you back as you try to pass.\n");
        say(QCTNAME(temp)+" shoves "+QTNAME(TP)+" back as "+PRONOUN(TP)+
          " tries to pass south.\n");
        temp->command("say Our leader's been slain, we trust no one "+
          "now.\n");
        return 1;
    }

    if (!TP->test_bit(4, 0))
    {
        colin->command("say I'm not sayin' I don't trust ya, "+
          TP->query_race_name()+", but no one but my dwarves "+
          "get past this point unless they prove themselves to "+
          "be trustworthy.\n");
        return 1;
    }

    colin->command("say I remember yer help, "+TP->query_race_name()+
      ", so you can pass.");
    return 0;
}

string
my_desc()
{
    object colin_here, dwarf1_here, dwarf2_here;

    colin_here = present(colin, TO);
    dwarf1_here = present(dwarf1, TO);
    dwarf2_here = present(dwarf2, TO);

    string tmp = "\n";
    
    if (!colin_here && !dwarf1_here && !dwarf2_here)
    {
        return tmp;
    }
    
    if (colin_here)
        tmp = "There is a tall dwarf here, who is apparently "+
              "the leader of this camp.";

    if (((!dwarf1_here && dwarf2_here) || (!dwarf2_here && dwarf1_here)) && colin_here)
        tmp += " There is a guard standing beside the leader.";

    if (dwarf1_here && dwarf2_here && colin_here)
        tmp += " There are two guards standing beside the leader.";

    if (!colin_here && ((!dwarf1_here && dwarf2_here) || (!dwarf2_here && dwarf1_here)))
        tmp += " There is a dwarf here, apparently some kind of "+
               "guard, but guarding what?";

    if (!colin_here && (dwarf1_here && dwarf2_here))
        tmp += " There are two dwarves here, apparently guards, "+
               "but guarding what?";
    return tmp + "\n";
}
