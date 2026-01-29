// armoire
// grace aug 1994

#include "../local.h"

inherit IN_BASE;

int robe;

int
out_message()
{
    write("You fumble around, trying to find the exit, and "+
        "suddenly stumble into the hallways of Vingaard Keep once again.\n");
    return 0;
}
create_vin_room()
{
    
    set_short("Inside a hidden closet");
    set_long("This is a fairly sizable and well-made wardrobe. "+
        "It smells strongly of the cedar panelling which lines "+
        "the interior. A shelf has been built into the armoire "+
        "just above eye-level, and a rod for hanging clothing is "+
        "below it.\n");
    
    LIGHT;
    
    AI(({"cedar","panelling","cedar panelling"}),"The cedar " +
        "panelling is a rich brown colour, and fragrant.\n");
    AI("interior", "It is spacious and fragrant with the scent "+
        "of cedar.\n");
    AI("shelf", "It is dusty and bare.\n");
    ACI(({"air","fragrance", "scent"}), "smell", "It smells strongly "+
        "of cedar.\n");
    AI("rod", "@@rod");
    
    add_invis_exit(VROOM + "south_hallway", "out", "@@out_message");
    reset_vin_room();
    
}

init()
{
    ::init();
    ADA("get");
    ADD("get","take");
}

string rod()
{
    if (robe == 4)
        {
        write("There is nothing hanging from the rod at this time.\n");
        return "";
    }
    
    write("There is a robe of some sort hanging from the rod.\n");
    return "";
}

int
get(string str)
{
    NF("Get what?\n");
    if ((str == "robe") || (str == "robe from rod") ||
            (str == "robes") || (str == "robe off rod"))
    {
        
        if (robe == 4)
            {
            write("There doesn't seem to be anything "+
                "hanging from the rod.\n");
            return 1;
        }
        clone_object(VARM + "cloak")->move(TP);
        write("You get a robe from the rod.\n");
        SAY(" gets a robe from the rod.\n");
        robe++;
        return 1;
    }
    return 0;
} 

reset_vin_room()
{
    robe = 0;
}

