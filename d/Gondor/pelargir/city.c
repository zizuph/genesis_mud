inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"


// Prototypes
void    set_room_type(int i);
void    set_extra_desc(string str);
void    set_where(string part);
string  query_where();

// Global variables
int     room_type;	// 0 - standard
			// 1 - main street
			// 2 - dock
string  extra_desc,
        part;		// defined: "north"

void
create_city_room()
{
    set_room_type(0);
}

nomask void
create_room()
{
    create_city_room();
    set_long(BSN(query_where() + extra_desc));

    switch (room_type)
    {
    case 0:
        break;
    case 1:
        add_item(({"street", "ground"}), BSN(
            "The street is made of large stone slabs which show the "
         + "the heavy use of centuries."));
        break;
    case 2:
        add_item(({"light house", "lighthouse"}), BSN(
            "The light house dominates the harbour, rising high above "
         + "the roofs of all other houses, the top of the city walls "
         + "and even above the top of the highest masts of the ships "
         + "at the docks."));
        break;
    default:
        break;
    }
}

void
set_room_type(int i)
{
    room_type = i;
}

void
set_extra_desc(string str)
{
    extra_desc = str;
}

void
set_where(string str1)
{
    part = str1;
}

string
query_where()
{
    string  where;

    case (part)
    {
    case "north":
        where = "These are the more elegant parts of Pelargir, "
       + "close to the Admiral's palace north of Lebennin street. ";
        break;
    default:
        where = "Somewhere in Pelargir. ";
        break;
    }

    return where;
}
