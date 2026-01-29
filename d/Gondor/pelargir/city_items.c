#include "/d/Gondor/defs.h"

varargs void
add_admiral(string where)
{
    switch(where)
    {
    case "north":
        TO->add_item(({"tower","admiral's tower"}),BSN(
            "To the north, high above these pitiful shacks and the rest "+
                "of the city, looms the Admiral's white tower. It is a constant "+
                "reminder to the people here that there are others more "+
                "fortunate than themselves."));
        break;
    case "south":
        TO->add_item(({"tower","admiral's tower"}),BSN(
            "To the south you can see the majestic white tower of the "+
                "Admiral of the Gondor fleet rising above the rest of the city."));
        break;
    case "harbour":
        TO->add_item(({"admiral's tower","tower"}), BSN(
            "The tower of the Admiral rises high above the city. The "+
                "sailors say it was built for the sole purpose of allowing the "+
                "Admiral a better view of the mighty Gondor ships."));
        break;
    default:
        TO->add_item(({"tower", "admiral's tower"}),BSN(
            "High above the city street towers the Admiral's home in "
                + "Pelargir. Most of the citizens will contest that the tower "
                + "was built to better oversee the beautiful city itself."));
        break;
    }
}

varargs void
add_anduin(string where)
{
    switch(where)
    {
    case "docks":
	TO->add_item(({"water","river","great river","anduin"}),BSN(
                "The great river Anduin dominates the landscape here. "
              + "The narrow strip of land supporting the lighthouse "
              + "to the north, also protects the docks here from the "
              + "Anduin's power. Though the current slowly carries "
              + "debris away from the city, the merging of the Sirith "
              + "nearby makes the water close to the docks seem murky."));
            break;
        case "city":
            TO->add_item(({"river","anduin","water","great river"}), BSN(
                "To your east you can see the sparkling waters of the "
              + "great river Anduin, flowing from the north towards "
              + "the sea not far to the south. It is so wide you can "
              + "barely see the other side."));
            break;
        default:
            TO->add_item(({"river", "river anduin", "anduin", }), BSN(
        "The Anduin, mightiest of rivers of Middle Earth, languidly flows "
      + "towards its mouths just east of city and plains. So far south, "
      + "the stream has become so wide that the opposite bank is just "
      + "a green line beyond a wide band of water."));
            break;
    }
}

void
add_cobble()
{
    TO->add_item(({"cobblestone","cobblestones","street","road","ground"}),
        BSN("The cobblestones are worn smooth with age and use."));
}

void
add_dockships()
{
    TO->add_item(({"ships","docks"}),BSN("There is constant activity "
      + "at all the docks, with only one or two exceptions. Crates are "
      + "being loaded and unloaded, and the cargo laden ships often "
      + "ride low in the water. Though many ships head down river to "
      + "the sea, there are some that head up river, deeper into Gondor."));
    if (!TO->item_id("dock"))
	TO->add_item( ({ "dock", "wood"}), BSN(
            "The dock reaches out into the water of the Anduin where "
            + "it rests on wooden pillars that are completely covered "
            + "by shells and clams. The wooden planks on top of the "
            + "dock show the signs of decades of heavy use."));
    if (!TO->item_id("shells"))
	TO->add_item( ({"shells", "clams", "pillars", "wooden pillars"}), 
            BSN("The wooden pillars on which the dock rests are covered "
                + "by a thick layer of shells and clams. They are out of "
                + "reach however."));
    if (!TO->item_id("planks"))
	TO->add_item( ({"planks", "wooden planks", }), BSN("The top "
            + "of the dock is covered by thick wooden "
            + "planks which show the signs of heavy use and old age. The "
            + "planks are still sturdy enough to carry heavy weights and "
            + "they are in good repair."));
}

varargs void
add_lighthouse(string where)
{
    switch(where)
    {
        case "north":
            TO->add_item("lighthouse",BSN(
                "The lighthouse towers above the river from the "
              + "narrow peninsula of rock, guiding wayward ships "
              + "safely into Pelargir."));
            break;
        case "bay":
            TO->add_item("lighthouse",BSN(
                "The lighthouse across the bay to the north "
              + "serves as a beacon to wayward ships that often "
              + "stray in the fog which sometimes blankets the "
              + "river."));
            break;
        default:
            TO->add_item("lighthouse", BSN(
                "The lighthouse of Pelargir is serves as beacon "
              + "to ships travelling upon the Anduin by night or "
              + "in fog. It was built on a narrow peninsula of "
              + "rock reaching out into the Anduin north of the "
              + "harbour."));
            break;
    }
}

void
add_mountains()
{
    TO->add_item(({"mountains", "ered nimrais", "white mountains", }),
        BSN("Far to the north on the horizon you can make out "
      + "the white snow covered peaks of the Ered Nimrais, the "
      + "White Mountains of Gondor."));
}

void
add_north_gate()
{
    TO->add_item(({"gate", "city gate", "northern city gate", 
        "northern gate", }), BSN(
        "Harlond street leads north to the city gate. The gate "
      + "is set between the thick towers on each side of it. "
      + "The city wall continues east and west of the towers."));
}

void
add_northside()
{
    TO->add_item(({"walls","wall","plain","mountains"}),BSN(
        "The main walls of the city are to the north, obscuring "
      + "partially your view of the plains of Lebennin and the "
      + "White Mountains."));
}

void
add_sirith()
{
    TO->add_item(({"river", "sirith", "sirith river", }), BSN(
        "The Sirith river is running through the northern parts "
      + "of Pelargir. It flows into the Anduin just south of "
      + "the lighthouse, north of the docks."));
}

varargs void
add_wall(string where)
{
    TO->add_item(({"wall", "city wall", }), BSN(
        "The city wall protects Pelargir against its enemies, "
      + "mainly the corsairs of Umbar and the peoples of Harad. "
      + "It is almost as wide as it is high and was built from "
      + "giant boulders hewn from the rock of the Ered Nimrais."));
}

void
add_south_gate()
{
    TO->add_item(({"gate", "city gate", "southern city gate", 
        "southern gate", }), BSN(
        "The main street leads south to the city gate. The gate "
      + "is set between the thick towers on each side of it. "
      + "The city wall continues east and west of the towers."));
}

void
add_towers()
{
    TO->add_item(({"towers"}),BSN(
        "From here you can see both the lighthouse of Pelargir "
      + "guiding ships safely, day and night, and the Admiral's tower "
      + "rising out of the city itself."));
}

/*
 * Function name: add_citizen
 * Description:	  add one citizen to the room
 * Arguments:     the object pointer to the global variable
 * Returns:       the object pointer to the global variable
 * Usage:         cit = add_citizen(cit);
 *                where cit is global object pointer.
 */
varargs object
add_citizen(object citizen, string file = (PELAR_DIR + "npc/citizen"))
{
    if (objectp(citizen))
        return citizen;

    citizen = clone_object(file);
    citizen->arm_me();
    citizen->move_living("down", TO);
    return citizen;
}

#if 0
#define RBRICKSTON TO->add_item(({"road","bricks"}),BSN(\
   "The road here is rough brick and stone. Though it gives a "+\
   "rustic look, it is in poor shape and even hard "+\
   "to walk on in some places."))

#define PBUILD TO->add_item(({"shacks","shack","buildings","homes"})\
   ,BSN("The shacks here are of very poor quality, perhaps "+\
   "even hardly livable. Most of the buildings are in need of "+\
   "repair, and from the scent here you can tell this area is "+\
   "mostly populated by poor fisherman."))


#endif




