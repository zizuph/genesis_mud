#include <stdproperties.h>
#define WEATHER_MASTER "/d/Wiz/quetzl/open/weather/weather_master"
 
public void
change_weather(object *affected, int new, int old)
{
    string inmess, outmess;
    object *outies, *innies;
 
    if (old == new)
        return;
 
    outies = filter(affected, &not() @ &->query_prop(ROOM_I_INSIDE) @
        environment);
    innies = filter(affected, &->query_prop(ROOM_I_INSIDE) @ environment);
 
    if ((!new && (old == 2)) || (!old && (new == 2)))
        WEATHER_MASTER->manual_set_weather("Esgaroth", new = 1);
 
    if (!new)
        outmess = "The clouds blow away.\n";
    else if (new == 1)
        if (!old)
            outmess = "The sky clouds over.\n";
        else
            outmess = "The rain stops.\n", inmess =
                "You no longer hear rain.\n";
    else
        outmess = "Rain begins to fall over the town of Esgaroth.\n",
        inmess = "You hear the sound of rain begin outside.\n";
 
    outies->catch_msg(outmess);
    if (strlen(inmess))
        innies->catch_msg(inmess);
}
 
public string
query_weather()
{
    int current_weather;
    setuid();
    seteuid(getuid());
    current_weather = WEATHER_MASTER->query_weather("Esgaroth");

    switch(current_weather)
    {
        case 0:
            return "clear";
        case 1:
            return "cloudy";
        case 2:
            return "raining";
        default:
            return "error weather type";
    }
}
