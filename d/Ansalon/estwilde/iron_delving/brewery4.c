#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

#define BREWCHAMBER "/d/Ansalon/estwilde/iron_delving/brewery3"
#define DWARFMEETING "/d/Ansalon/guild/neidar/rooms/meetcircle"

inherit DWARF_IN;

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

    reset_dwarf_room();
}

string
short_descr()
{
    return "great barrel vault of the Iron Delving Brewery";
}

public void
hook_smelled(string str)
{
    write("The musty scent of age fills the cool air of the vault; "+
          "with a faint earthy musk underlying it.\n");
}

void
transfer_to_dest(object ob, object from)
{
    int n, i, ifndbc;
    string brew_chamber;
 
    if (living(ob))
    {
        if ( wildmatch(BREWCHAMBER,file_name(from)) )
        {
            write("... you emerge from between the barrel-tiers into "+
            "a circle of light within the darkness of the Great Vault.\n\n");
            tell_room(DWARFMEETING, QCNAME(TP) + " emerges into the light of the circle.\n");
            ob->move_living("M",DWARFMEETING, 1, 0);
        }
        else
        {
            write("... you emerge from between the barrel-tiers into "+
            "buzz of activity within the Brew Chamber.\n\n");
            tell_room(BREWCHAMBER, QCNAME(TP) + " emerges from the barrel vault.\n");
            ob->move_living("M",BREWCHAMBER, 1, 0);
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
        str = "... you wonder how dwarves can lift barrels so high onto the tiers";
        break;

        case 2:
        str = "... you hurry past a goblin corpse, broken beneath a shattered barrel";
        break;

        case 3:
        str = "... you see a tuft of reddish-brown hair caught between barrels";
        break;

        case 4:
        str = "... you imagine you hear snoring coming from high atop the tiers";
        break;

        default:
        str = "... you glimpse imagined movement high atop the barrel tiers";
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

    write("You wend your way through a bewildering number of twists and "+
          "turns in the dark passages between the towering barrel-tiers...\n");

    set_alarm(5.0,0.0,&walking_encounter());

    set_alarm(10.0,0.0,&transfer_to_dest(ob,from));
}


string
long_descr()
{

    string str0, str1;

    str0 = "The Great Barrel Vault occupies a vast "+
    "space beneath a high hill in Estwilde. Cool shadows dominate "+
    "the vault and the winding passages deep between barrel tiers. It is the "+
    "ideal place to store barrels of brew for any length of time.";

    if ( CLOCK->query_night() ) 
        str1 = "The light of a ring of torches at the centre of the vault cast "+
               "a feeble flickering on the roof of the cavern.";
    else
        str1 = "Beams of natural light, streaming from windows in the hill side "+
               "illuminate the centre of the vault.";
     
    return sprintf("%s %s\n", str0, str1);

}
