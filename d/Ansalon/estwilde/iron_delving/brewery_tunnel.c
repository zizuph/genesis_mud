#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

#define BREWENTRANCE "/d/Ansalon/estwilde/iron_delving/brewery1"
#define TUNNELENTRANCE "/d/Ansalon/estwilde/plains/12k"

inherit DWARF_IN;

static int EnemiesOnly = 0;  // ==1 enforces policy

void
reset_dwarf_room()
{
    return;
}

void
create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    INSIDE;
    DARK;

    reset_dwarf_room();
}

string
short_descr()
{
    return "dark twisting tunnel under a dwarven settlement";
}

public void
hook_smelled(string str)
{
    write("The scent of earth dominates the damp air of the tunnel; "+
          "with but faint traces of blood and ash and yeasty " +
          "fermentation underneath.\n");
}

void
transfer_to_dest(object ob, object from)
{
    int n, i, ifndbc;
    string brew_chamber;
    string *exits;
 
    if (living(ob))
    {
        if ( EnemiesOnly )  
        { 
            if(ob->query_race_name() == "goblin" ||
               ob->query_race() == "goblin" ||
               ob->query_race_name() == "hobgoblin" ||
               ob->query_race_name() == "minotaur" ||
               ob->query_race_name() == "ogre" ||
               ob->query_prop(DWARF_ENEMY) ||
               ob->query_wiz_level() != 0)
                ifndbc = wildmatch(BREWENTRANCE,file_name(from));
            else
            {
                write("... the oppressive confines of the tunnel overcome "+
                       "your desire to explore further.\n");
                ifndbc = 1;
            }
        }
        else
            ifndbc = wildmatch(BREWENTRANCE,file_name(from));
        
        if (ifndbc) 
        {
            write("... you emerge from the dark tunnel, into an open stone "+
            "chimney in a chasm wall, and climb upwards to reach the foot of a "+
            "bridge far above.\n\n");
            tell_room(TUNNELENTRANCE, QCNAME(TP) + " emerges from a chimney to stand above the chasm.\n");
            ob->move_living("M",TUNNELENTRANCE, 1, 0);
        }
        else
        {
            write("... you find yourself at the end of the earthen section of the " +
            "tunnel, within a large barrel...\n"+
            "... the end of the barrel leading to the tunnel " +
            "is entirely missing, while the other end before you is hinged closed.\n\n"+
            "... on the inside of the closed end, you can see luminous letters " +
            "'GOBBOS ROK DA IRIN DELVIN BREWRY SUCKR DWARFZ'\n\n" +
            "... you silently open the hinged end to emerge "+
            "stealthily. You close the barrel, last in its row, behind you.\n\n");
            tell_room(BREWENTRANCE, QCNAME(TP) + " emerges from a closed barrelcot.\n");
            ob->move_living("M",BREWENTRANCE, 1, 0);
        }
    }
    else
    {
        ob->remove_object();
    }
}

void
walking_encounter()
{
    string str; 

    switch (random(5))
    {
        case 1:
        str = "... you wonder at this tunnel, it seems not to be of dwarven make";
        break;

        case 2:
        str = "... you pause at an elf skeleton, planted in the moist soil of the tunnel, far from any light";
        break;

        case 3:
        str = "... you feel a grail-like form in the dark, battered and discarded in the tunnel";
        break;

        case 4:
        str = "... you imagine you hear the faint sound of dwarven voices, or could it be the whispering of the wind";
        break;

        default:
        str = "... you feel things crawl over your flesh as you make your way forward";
        break;
    }

    write(str + ".\n");

    return;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    set_long("@@long_descr");

    write("You wend your way through an endless number of twists and "+
          "turns underground...\n following your nose between the smell of "+
          "fresh wind and something altogether more curious.\n");

    set_alarm(5.0,0.0,&walking_encounter());

    set_alarm(10.0,0.0,&walking_encounter());

    set_alarm(15.0,0.0,&transfer_to_dest(ob,from));
}


string
long_descr()
{
    return "Dark and damp; this crude tunnel winds tightly between underground roots and rocks "+
           "under a dwarven settlement between distant ends.\n";

}
