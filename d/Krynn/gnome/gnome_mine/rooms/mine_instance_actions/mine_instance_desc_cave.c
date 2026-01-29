
/*
* Function name: query_descr
* Description  : The descriptors and items of the caves.
*/

//TODO
//simpler monster/loot, no traps
public void
query_descr_caves(object instances_room, int specific)
{
    int z;

    if (specific != -1)
    {
        z = specific;
    }
    else
    {
        z = random(10);        
    }

    switch(z)
    {
        case 0:
            instances_room->set_short("A narrow cave.");

            instances_room->set_long("It would seem like a common cave tunnel.\n");
            break;
        case 1:
            instances_room->set_short("A short cave.");

            instances_room->set_long("This short cave tunnel appears as if about to collapse.\n");

            instances_room->add_item(({ "walls", "wall" }),
                "Dark and smooth.\n");
            break;
        case 2:
            instances_room->set_short("A wide cave.");

            instances_room->set_long("Underground rivers made a wide cave tunnel here.\n");

            instances_room->add_item(({ "walls", "wall" }),
                "Smooth and solid.\n");
            break;
        case 3:
            instances_room->set_short("A crooked cave.");

            instances_room->set_long("The path bends and twists forward.\n");

            instances_room->add_item(({ "walls", "wall" }),
                "Crooked walls adorn this cave.\n");
            break;
        case 4:
            instances_room->set_short("A long cave.");

            instances_room->set_long("The path extends beyond view in here.\n");
            break;
        case 5:
            instances_room->set_short("A cave.");

            instances_room->set_long("Nothing uncommon about this cave.\n");
            break;
        case 6:
            instances_room->set_short("A dark cave.");

            instances_room->set_long("Black walls make this cavern look darker than usual.\n");

            instances_room->add_item(({ "walls", "wall" }),
                "Very black.\n");
            break;
        case 7:
            instances_room->set_short("A large cave.");

            instances_room->set_long("You cannot see the roof on this cave, probably a natural formation.\n");

            instances_room->add_item(({ "walls", "wall" }),
                "They rise out of view, into the darkness.\n");
            break;
        case 8:
            instances_room->set_short("A weird cave.");

            instances_room->set_long("The walls here are red, as if tainted by blood.\n");

            instances_room->add_item(({ "walls", "wall" }),
                "Crimson red.\n");
            break;
        case 9:
            instances_room->set_short("A clawed cave.");

            instances_room->set_long("Rock formations here don't seem to be human carved, more like clawed.\n");

            instances_room->add_item(({ "walls", "wall" }),
                "Clawed into form, probably by a beast.\n");
            break;
    }
}
