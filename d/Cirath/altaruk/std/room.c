/*
 * std/room.c
 *
 * by Azazel 2002
 *
 */
inherit "/d/Cirath/std/room.c";

#include "/d/Cirath/common/defs.h"

public static string     Short_d, Street_n, Extra_line, Last_line ;

void short_name(string a) { Short_d = a; }
void street_name(string a) { Street_n = a; }
void extra_line(string a) { Extra_line = a; }
void last_line(string a) { Last_line = a; }

string
long_desc()
{
	string r;
	
    r = capitalize(Short_d);
    if (Street_n) r += " You are in " + Street_n + " street.";
    r += " The town is built up on the commerce that follows the" +
        " caravans that pass trough here. Sandstone and clay walls" +
        " makes up most of your view.";
    if (Extra_line) r += " " + Extra_line ;
    r += " You can hear the shouts of pedlers and guards shouting" +
        " orders about.";
    if (Last_line) r += " " + Last_line ;
    r += "\n";

    return r;
}

void
create_street()
{
}

public nomask void
create_room()
{
    create_street();
    set_short(Short_d);
    set_long(&long_desc());
    
    if (Street_n)
        add_item( ({"sign", "street sign" }), "A sign on the wall tells" +
            " you your on " + Street_n + " street.\n");
    ADD_SUN_ITEM
    add_item("dust", "The amount of dust covering everything tell you" +
        " your not far from the edges of the silt sea.\n");
    add_item("sand", "Sand piles up quickly on street-corners and fills" +
        " every crevice it can find. Hopefully you can keep most of it" +
        " out of your clothes.\n");
    add_item("walls", "The walls here are sandstone and clay of various" +
        " quality. Some are crumbling from years of wear and tear.\n");
    add_item("ground", "The ground is bare, less for the sand and dust" +
        " that twirl around.");
}

