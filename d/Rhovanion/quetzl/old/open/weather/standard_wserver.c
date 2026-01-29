#include <stdproperties.h>

static string * weather_names = ({ "", "light rain",
     "heavy rain", "light sleet", "blinding sleet",
     "light snow", "heavy snow" });
 
public void
change_weather(object *affected, int new, int old)
{
    string mess;
 
    // Filter out those indoors.
    affected = filter(affected, &operator(==)(0) @
        &->query_prop(ROOM_I_INSIDE) @ environment);
 
    if (old == new)
        return;
    switch(new)
    {
        case 0:
            mess = "The " + weather_names[old] + " stops.\n";
            break;
        default:
            if (!old)
                mess = "A " + weather_names[new] + " begins to fall.\n";
            else
                mess = "The " + weather_names[old] + " changes " +
                    "to a " + weather_names[new] + ".\n";
            break;
    }
    affected->catch_msg(mess);
}
