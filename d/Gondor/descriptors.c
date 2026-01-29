/*
*filepath
*These are descriptors used by the Dimrill Dale path between Moria and
*Lothlorien.  They are for varying the description of rooms and items
*depending on time of day.
*Mona 2020
*Via  Varian
*/
string
daylight_desc()
{
    switch(qhour())
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

 
string
day_desc()
{
    switch(qhour())
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
   switch(qhour())
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

string 
sun_moon()
{
    switch(qhour())
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
    switch(qhour())
    {
        case EARLY_NIGHT :
            return "night";
        case LATE_NIGHT :
            return "midnight";
        case EARLY_MORNING :
            return "dawn";
        case MORNING:
            return "mid-morning";
        case NOON:
            return "noon";
        case AFTERNOON:
            return "afternoon";
        case EVENING:
            return "evening";
    }
}   
string 
mirror_desc()
{
     switch(qhour())
    {
        case EARLY_NIGHT :
            return "The moon, pale and creamy, appears as if it is in the " +
            "water itself.  It sheds its light from within the pond, " +
            "across the deep dusky blue color of surface, an exact match " +
            "of the night sky.  A few early stars are also reflected on " +
            "the water, peeking out from behind smokey wisps of clouds.";
        case LATE_NIGHT :
            return "Stars and planets twinkle in the surface of the water, " +
            "amidst a backdrop of the reflected deep murky blue of the " +
            "midnight sky.";
        case EARLY_MORNING :
            return "The first few rays of morning sun shimmer out from " +
            "the top-edge of the light-giving partial-orb that is " +
            "reflected in the water.  Pinks and oranges the color of the " +
            "early morning sky streak the pond.";
        case MORNING:
            return "The mid-morning sun glimmers yellow and gold in " +
            "deep-blue water the color of the sky.  Small clouds move " +
            "slowly across the water.";
        case NOON:
            return "The sun shines, like a fiery ball in the water, " +
            "reflecting a blinding light back into your eyes!!! Your eyes " +
            "start to close themselves reflexively, from the brightness, " +
            as if you stared directly into the mid-day sun itself. Ouch! " +
            "Clouds move lazily across water that is the perfect blue of " +
            "the mid-day sky.";
    //add set_alarm and tell_object for sunspot blindness
        case AFTERNOON:
            return "The mid-afternoon sun shines like a bright orange orb " +
            "reflected in the water.  A few stray clouds move lazily " +
            "across water that is the dusky blue color of the afternoon sky.";
        case EVENING:
            return "The water reflects a large red-orange orb low on the " +
            "horizon.  Deep blues and purples streak the water, " +
            "highlighted with small areas of yellow in between. It is " +
            "a perfect mirror of the sunset sky above.  A few dark clouds " +
            "move across the water like slow shadows of on-coming night."; 
    }
}