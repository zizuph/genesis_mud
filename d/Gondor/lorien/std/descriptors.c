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
            return "mid-day sunlight";
        case AFTERNOON:
            return "afternoon sunlight";
        case EVENING:
            return "evening light";
    }
}

string
daylit_desc()
{
    switch(qhour())
    {
        case EARLY_NIGHT :
            return "moonlit";
        case LATE_NIGHT :
            return "starlit";
        case EARLY_MORNING :
            return "barely lit";
        case MORNING:
            return "morning sunlit";
        case NOON:
            return "mid-day sunlit";
        case AFTERNOON:
            return "afternoon sunlit";
        case EVENING:
            return "dimly lit";
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
            return "glow of dawn";
        case MORNING:
            return "sunlight";
        case NOON:
            return "sunlight";
        case AFTERNOON:
            return "sunlight";
        case EVENING:
            return "haze of dusk";
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
            return "mid-day";
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
            "water itself. It sheds its light from within the pond, " +
            "across the deep dusky blue color of surface, an exact match " +
            "of the night sky. A few early stars are also reflected on " +
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
            "as if you stared directly into the mid-day sun itself. Ouch! " +
            "Clouds move lazily across water that is the perfect blue of " +
            "the mid-day sky.";
    //add set_alarm and tell_object for sunspot blindness
        case AFTERNOON:
            return "The mid-afternoon sun shines like a bright orange orb " +
            "reflected in the water. A few stray clouds move lazily " +
            "across water that is the dusky blue color of the afternoon sky.";
        case EVENING:
            return "The water reflects a large red-orange orb low on the " +
            "horizon. Deep blues and purples streak the water, " +
            "highlighted with small areas of yellow in between. It is " +
            "a perfect mirror of the sunset sky above. A few dark clouds " +
            "move across the water like slow shadows of on-coming night."; 
    }
}

string 
sky_desc()
{
     switch(qhour())
    {
        case EARLY_NIGHT :
            return "A pale and creamy moon sheds its light across the " +
 	        "deep dusky blue of the night sky.  A few early stars peek out " +
	        "from behind smokey wisps of clouds.";
        case LATE_NIGHT :
            return "Stars and planets twinkle amidst a backdrop of the " +
            "deep murky blue of the midnight sky.";
        case EARLY_MORNING :
            return "The first few rays of morning sun shimmer out from " +
            "the top-edge of the light-giving partial-orb to peek out over " +
            "the horizon. Pinks and oranges streak the early morning sky";
        case MORNING:
            return "The mid-morning sun glimmers yellow and gold in the " +
            "deep-blue sky.  Small clouds move slowly across.";
        case NOON:
            return "As you look up, the mid-day sun is blindingly bright. " +
            "You try to look at it, but it shines like a fiery ball. Its " +
            "searing light is blinding!!! Your eyes start to closer " +
            "reflexively, from the brightness.  Ouch! Clouds move lazily " +
            "across the perfect blue of the mid-day sky.";
        //add set_alarm and tell_object for sunspot blindness
        case AFTERNOON:
            return "The mid-afternoon sun shines like a bright orange orb " +
            "hanging half way between the horizon and its mid-day " +
            "position.  A few stray clouds move lazily across the dusky " +
            "blue afternoon sky.";
        case EVENING:
            return "The sun is a large red-orange orb low on the horizon. " +
            "Deep blues and purples streak the sky, highlighted with small " +
            "areas of yellow in between. A few dark clouds move across " +
            "the sunset sky like slow shadows of on-coming night."; 
    }
}
