
/*
* Function name: query_descr
* Description  : The descriptors and items of the tunnels.
*/
public void
query_descr(object instances_room, int specific)
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
			instances_room->set_short("A narrow tunnel.");

			instances_room->set_long("It would seem like a common rock tunnel.\n");

			instances_room->add_item(({ "walls", "wall" }),
				"Carved and crooked walls adorn this tunnel.\n");
			break;
		case 1:
			instances_room->set_short("A short tunnel.");

			instances_room->set_long("Rocks look oddly shaped and as if about to fall on your head.\n");

			instances_room->add_item(({ "walls", "wall" }),
				"Carved and crooked walls adorn this tunnel.\n");
			break;
		case 2:
			instances_room->set_short("A wide tunnel.");

			instances_room->set_long("Rocks are smooth here.\n");

			instances_room->add_item(({ "walls", "wall" }),
				"Carved and crooked walls adorn this tunnel.\n");
			break;
		case 3:
			instances_room->set_short("A crooked tunnel.");

			instances_room->set_long("The path bends and twists forward.\n");

			instances_room->add_item(({ "walls", "wall" }),
				"Carved and crooked walls adorn this tunnel.\n");
			break;
		case 4:
			instances_room->set_short("A long tunnel.");

			instances_room->set_long("The path extends beyond view in here.\n");

			instances_room->add_item(({ "walls", "wall" }),
				"Carved and crooked walls adorn this tunnel.\n");
			break;
		case 5:
			instances_room->set_short("A tunnel.");

			instances_room->set_long("Nothing uncommon about this tunnel.\n");

			instances_room->add_item(({ "walls", "wall" }),
				"Carved and crooked walls adorn this tunnel.\n");
			break;
		case 6:
			instances_room->set_short("A happy tunnel.");

			instances_room->set_long("Someone seems to have carved happy smiles on the side of the walls.\n");

			instances_room->add_item(({ "walls", "wall" }),
				"Carved and crooked walls adorn this tunnel.\n");
			break;
		case 7:
			instances_room->set_short("A large tunnel.");

			instances_room->set_long("You cannot see the roof on this tunnel, probably a natural formation.\n");

			instances_room->add_item(({ "walls", "wall" }),
				"Carved and crooked walls adorn this tunnel.\n");
			break;
		case 8:
			instances_room->set_short("A weird tunnel.");

			instances_room->set_long("The walls here are red, as if tainted by blood.\n");

			instances_room->add_item(({ "walls", "wall" }),
				"Carved and crooked walls adorn this tunnel.\n");
			break;
		case 9:
			instances_room->set_short("A clawed tunnel.");

			instances_room->set_long("Rock formations here don't seem to be human carved, more like clawed.\n");

			instances_room->add_item(({ "walls", "wall" }),
				"Carved and crooked walls adorn this tunnel.\n");
			break;
	}
}
