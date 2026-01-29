string
daylight_desc()
{
    switch(quhour())
    {
        case EARLY_NIGHT :
            return "moonlight";
        case LATE_NIGHT :
            return "starlight";
        case EARLY_MORNING :
            return "morning light";
        case MORNING:
            return "morning sunlight";
        case NOON:
            return "noon sunlight";
        case AFTERNOON:
            return "afternoon sunlight";
        case EVENING:
            return "evening light";
    }
}

/*
string
day_desc()
{
    switch(query_time_desc())
    {
        case EARLY_NIGHT :
            return "early night";
        case LATE_NIGHT :
            return "late night";
        case EARLY_MORNING :
            return "early morning";
        case MORNING:
            return "morning";
        case NOON:
            return "noon";
        case AFTERNOON:
            return "afternoon";
        case EVENING:
            return "evening";
    }
}
 
string
light_type()
{
   switch(query_time_desc())
    {
        case EARLY_NIGHT :
            return "moonlight";
        case LATE_NIGHT :
            return "starlight";
        case EARLY_MORNING :
            return "haze of dawn";
        case MORNING:
            return "sunlight";
        case NOON:
            return "sunlight";
        case AFTERNOON:
            return "sunlight";
        case EVENING:
            return "glow of dusk";
    }
}

string sun_moon()
{
    switch(query_time_desc())
    {
       case EARLY_NIGHT :
            return "moon";
        case LATE_NIGHT :
            return "stars";
        case EARLY_MORNING :
            return "sun";
        case MORNING:
            return "sun";
        case NOON:
            return "sun";
        case AFTERNOON:
            return "sun";
        case EVENING:
            return "sun";
    }
}

string
day_time()
{
    switch(query_time_desc())
    {
        case EARLY_NIGHT :
            return "night";
        case LATE_NIGHT :
            return "night";
        case EARLY_MORNING :
            return "morning";
        case MORNING:
            return "morning";
        case NOON:
            return "noon";
        case AFTERNOON:
            return "afternoon";
        case EVENING:
            return "evening";
    }
}
*/