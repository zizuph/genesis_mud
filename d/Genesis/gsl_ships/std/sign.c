/*
 * standard Genesis pier sign
 * TAPAKAH, 04/2008
 *
 * Modification history:
 *   - Gorboth, April 2011
 *         Added functionality for Sparkle Dock Tour
 */

#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>

#include "../ships.h"
#include "/d/Sparkle/sys/quests.h"
#include "/d/Sparkle/area/city/defs.h"

inherit "/std/object";

#define COMPANY ("Genesis ShipLines")

void   create_sign    ();
string describe();
void   configure_sign (string port, int price, string destination);
int    is_pier_sign   ();
int    read_sign      (string str);
string get_label      (string *lines);

/* Global Variables */
public string         Sign_Desc = get_label( ({ 
                                    "This pier is currently unused" }) );


void
create_object ()
{
  create_sign();
}

void
create_sign ()
{
  set_name("sign");
  add_name(SHIPLINE_SIGN);
  set_adj(({"tall", "wooden"}));
  set_short("Genesis ShipLines sign");
  set_long("@@describe@@");
  add_prop(OBJ_M_NO_GET, COMPANY + " property cannot be taken!\n");

    add_item( ({ "scum" }), "@@exa_scum@@");
}  


/*
 * Function name:        describe
 * Description  :        provide a dynamic long description for the
 *                       sign
 * Returns      :        string - the description
 */
public string
describe()
{
    string  room = FILE_NAME(file_name(environment(this_object())));
    string  extra = "";
    string *room_array;

    if (!this_player()->test_bit("Sparkle",
        CITY_TOUR_DOCK_GROUP,
        CITY_TOUR_DOCK_BIT) &&
        this_player()->query_prop(SPARKLE_TOUR_PROP) == "tour_docks")
    {
        room_array = this_player()->query_prop(DOCK_TOUR_PROP);

        if (!IN_ARRAY(room, room_array))
        {
            extra = "You notice quite a bit of scum on the sign.\n"
              + "Perhaps you should <scrub> it off?\n";
        }
    }

    return Sign_Desc + extra;
} /* describe */


varargs void
configure_sign (string port = "", int price = 0, string destination = "")
{
  string *new_description;

  new_description = ({});
  if(port != "")
    new_description += ({port + " office"});
  if(destination != "")
    new_description += ({"Line " + destination});
  if(price)
    new_description += ({"Ticket price: " + price + "cc"});

  if(!sizeof(new_description))
    new_description = ({"This pier is currently unused"});
  Sign_Desc = get_label(new_description);
}

public nomask int
is_pier_sign ()
{
  return 1;
}

public int
read_sign (string arg)
{
    object  sign;

    if (!objectp(sign = PARSE_COMMAND_ONE(arg, 0, "[the] %i"))
        || sign != this_object())
    {
        notify_fail("Read what?\n");
        return 0;
    }

    write("The sign reads:\n" + describe());
    return 1;
}

public string
get_label (string *lines)
{
  int max_width;
  string label;

  max_width = applyv(max, map(lines, strlen)) + 10;
  if(max_width > 70)
                max_width = 70;
  label = "";
  label += sprintf("%'-'-*s", max_width+4,"-") + "\n";
  label += sprintf("|%*|s|",max_width+2, " ") + "\n";
  label += sprintf("|%*|s|",max_width+2, COMPANY) + "\n";
  label += sprintf("|%*|s|",max_width+2, " ") + "\n";
  foreach(string line: lines) {
                label += sprintf("|%*|s|",max_width+2, line) + "\n";
  }
  label += sprintf("|%*s|",max_width+2, " ") + "\n";
  label += sprintf("%'-'-*s", max_width+4,"-") + "\n";

  return label;
}

void
init ()
{
  ::init;
  add_action(read_sign, "read");
}


/*
 * Function name:        exa_scum
 * Description  :        allow players to look at the scum if they are
 *                       in the process of doing the dock tour.
 * Returns      :        string - the string to display
 */
public string
exa_scum()
{
    string  room = FILE_NAME(file_name(environment(this_object())));
    string *room_array;

    if (!this_player()->test_bit("Sparkle",
        CITY_TOUR_DOCK_GROUP,
        CITY_TOUR_DOCK_BIT) &&
        this_player()->query_prop(SPARKLE_TOUR_PROP) == "tour_docks")
    {
        room_array = this_player()->query_prop(DOCK_TOUR_PROP);

        if (!IN_ARRAY(room, room_array))
        {
            return "This sign is definitely in need of some cleaning."
              + " Anyone with the right sort of tool could probably"
              + " <scrub> the scum off.\n";
        }

        return "Thanks to you, the scum is gone from this sign now.\n";
    }

    return "You find no scum.\n";
} /* exa_scum */
