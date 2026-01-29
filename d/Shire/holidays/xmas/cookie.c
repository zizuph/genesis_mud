/*
 * Holiday food from Bree
 * Finwe, December 2002
 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"

string cookie_type();
string shape, icing_color, decorations;
int cookie_counter, num_of_cookies;

create_food()
{
    setuid();
    seteuid(getuid());
    
    num_of_cookies = 9;

    cookie_counter = random(num_of_cookies);

    cookie_type();
    
    set_name("cookie");
    add_name("sugar cookie");
    add_name(shape + " sugar cookie");
    add_name(shape + " cookie");
    add_name(shape + " shaped sugar cookie");
    add_name(shape + " shaped cookie");
    add_pname("sugar cookies");
    add_pname(shape + " sugar cookies");
    add_pname(shape + " cookies");
    add_name(shape + " shaped sugar cookies");
    add_name(shape + " shaped cookies");
    add_pname("cookies");
    set_short(shape + " shaped sugar cookie");
    set_pshort(shape + " shaped sugar cookies");
    set_long("This is a sugar cookie, in the shape of a " + 
        shape + ". The cookie is frosted with " + icing_color + 
        " icing and decorated with " + decorations +".\n");
    set_amount(15); 
}

string cookie_type()
{
    switch(cookie_counter)
    {
        case 0:
            shape = "star";
            icing_color = "yellow";
            decorations = "tiny, edible silver balls. It sparkles in the " +
                "light from white colored sugars sprinkled on it";
            break;
        case 1:
            shape = "tree";
            icing_color = "yellow";
            decorations = "tiny, edible multi-colored balls. It looks almost " +
                "too good to eat";
            break;
        case 2:
            shape = "house";
            icing_color = "red";
            decorations = "a door, some windows, and a chimney outlined " +
                "in white icing and filled with colored sugars";
            break;
        case 3:
            shape = "wreath";
            icing_color = "green";
            decorations = "red drops resembling berries";
            break;
        case 4:
            shape = "candy cane";
            icing_color = "white";
            decorations = "a stripe of red sugar";
            break;
        case 5:
            shape = "bell";
            icing_color = "white";
            decorations = "a thin bead of yellow icing, outlining the cookie";
            break;
        case 6:
            shape = "sleigh";
            icing_color = "white";
            decorations = "red sugars. Black sugar fills in the runners at " +
                "the bottom of the sleigh";
            break;
        case 7:
            shape = "candle";
            icing_color = "red";
            decorations = "white icing outlining the cookie. The top of the " +
                "cookie is flame shaped and yellow";
            break;
        case 8:
            shape = "snowman";
            icing_color = "white and black";
            decorations = "white sugars, black candies for the eyes, " +
                "nose, and smile. There is a black hat on top of the head";
            break;
    }

}
