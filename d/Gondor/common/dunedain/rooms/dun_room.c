#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/dunedain/lib/dunedain_defs.h"

int
check_exit()
{
    if (IS_MEMBER(TP))
        return 0;

    write("Only members of the Houses of the Dunedain may proceed here!\n");

    if (TP->query_wiz_level())
    {
        write("But, since you are a wizard, we make an exception.\n");
        return 0;
    }

    return 1;
}

varargs void
floor(int i = 0)
{
    switch (i)
    {
        case 1:
            add_item(({"floor", "ground", }), BSN(
                "The ground is made from the living rock of the Mindolluin. "
              + "It has been levelled with great care and excellent "
              + "workmanship."));
            break;
        default:
        case 0:
            add_item(({"floor", "ground", }), 
                ONE_OF_LIST( ({
                "The floor is made from large stone slabs.\n",
                "Large grey stone slabs are covering the ground.\n",
                }) ) );
            break;
    }
}

varargs void
walls(int i = 0)
{
    switch (i)
    {
        case 1:
            add_item(({"wall", "walls", }), BSN(
                "The walls have been carved from the living rock of the "
              + "Mindolluin that have been smoothed and polished with "
              + "great care and by experienced and diligent masons."));
            break;
        case 0:
        default:
            add_item(({"wall", "walls", }), ONE_OF_LIST( ({
                BSN("The walls are made from large stone blocks hewn from "
              + "a quarry in the Ered Nimrais not far from the Mindolluin."),
                BSN("The walls are the work of excellent stone masons. "
              + "There are hardly any grooves between the stone blocks "
              + "that make up the walls. Even in Minas Tirith such "
              + "workmanship is probably impossible to find in these days."),
                BSN("Mighty stone blocks have been piled one upon the other "
              + "to built these walls. The excellent workmanship of the "
              + "builders is obvious from the way the blocks fit together "
              + "without hardly any spaces or grooves visible between them."),
                }) ) );
            break;
    }
}

varargs void
ceiling(int i = 0)
{
    switch (i)
    {
        case 1:
            add_item(({"ceiling", "roof", }),
                "The roof has been carved from the living rock of the "
              + "Mindolluin.\n");
            break;
        case 0:
        default:
            add_item(({"ceiling", "roof", }), ONE_OF_LIST( ({
                "The roof vaults high above, details cannot be made out from down here.\n",
                BSN("A mighty vaulted roof, rising high above the floor, "
              + "without any pillars for suport."),
                BSN("In mighty arcs the roof rises high above the walls "
              + "on which it rests. Marvellously, there are no pillars to "
              + "support the aspiring construction."),
                }) ) );
            break;
    }
}
