string
location_desc() 
{

    switch(query_mirkwood_location())
    {
        case LOCATION_WEST_EDGE: return "on the western edge";
        case LOCATION_WEST_PART: return "in the western part";
        case LOCATION_MIDDLE: return "somewhere in the middle";
        case LOCATION_EAST_PART: return "in the eastern part";
        case LOCATION_EAST_EDGE: return "on the eastern edge";
        default:
            return "somewhere";
    }
}

string
daylight_desc()
{
    switch(qhour())
    {
        case EARLY_NIGHT :
            return "Moonlight";
        case LATE_NIGHT :
            return "Starlight";
        case EARLY_MORNING :
            return "Soft morning light";
        case MORNING:
            return "Morning sunlight";
        case NOON:
            return "Noon sunlight";
        case AFTERNOON:
            return "Afternoon sunlight";
        case EVENING:
            return "Evening light";
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
            return "Moonlight";
        case LATE_NIGHT :
            return "Starlight";
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
    switch(qhour())
    {
       case EARLY_NIGHT :
            return "moon";
        case LATE_NIGHT :
            return "stars";
        case EARLY_MORNING :
            return "rising sun";
        case MORNING:
            return "early sun";
        case NOON:
            return "sun";
        case AFTERNOON:
            return "sun";
        case EVENING:
            return "setting sun";
    }
}

/*
 * Function name : set_add_all_rooms
 * Arguments     : str: none
 * Description   : adds standard items to all rooms.
 */
void set_add_all_rooms()
{

add_item_light(({"tree", "trees"}),
    "Hovering over you, the trees of Mirkwood give you the" +
    " strangest feeling that they are actually watching your every" +
    " movement. The massive black trunks of the trees are all" +
    " tangled in the underbrush, and making your way in almost" +
    " any direction seems to be a chore. Occasionally, a slender" +
    " ray of @@light_type@@ from the @@sun_moon@@" +
    " has been able to penetrate the eerie darkness of the trees." + 
    " However, most of the time the branches of the great trees" +
    " wrap you in the darkness of the forest.\n", LIGHT_ALL);
add_item_light(({"branch", "tree branch", "branches", "tree branches"}),
    "The branches of the great trees of Mirkwood seems to reach" +
    " out to hover over your head menacingly, striving to prevent" +
    " any light from the @@sun_moon@@ from ever reaching" +
    " your eyes.\n", LIGHT_ALL);
add_item_light(({"ground", "floor", "forest floor"}),
    "The soft dirt of the forest floor is littered with various animal" +
    " tracks, which weave in and out of the twisted maze of underbrush" +
    " which seems to dominate every inch of the forest.\n",
    LIGHT_ALL);
add_item_light(({"underbrush", "bushes", "brush", "bush", "shrub", "shrubs"}),
    "Aside from the occasional animal trails or man-made paths, the" +
    " forest floor seems to be absolutely littered with all manner of" +
    " bushes and shrubs. Most of these patches of undergrowth are" +
    " difficult to pass through easily, slowing you down every time" +
    " you try to pass directly through the hear of the forest itself.\n",
    LIGHT_ALL);
add_item_light(({"sky", "light", "up"}),
    "With the massive trees blocking almost all semblance of natural" +
    " light, it is almost impossible for you to even see the" +
    " @@daylight_desc@@ from here. Perhaps you might be able" +
    " to find a tree which you could climb up to see more details?\n",
    LIGHT_ALL);
}

/*
 * Function name : set_add_spiders_close
 * Arguments     : str: none
 * Description   : adds the description for the spiders close by
 */

void set_add_spiders_close()
{
     add_item(({"web strands","web strand", "strands", "strand", "spider webs","spider web"}),
     "As you examine the trees and underbrush here very carefully," +
     " you notice that there are residual strands of spider webs" +
     " all over the place. Most of the webs appear to have been" +
     " broken a long time ago, yet several are still intact and are" +
     " certainly far larger and stronger than any spider web you have" +
     " ever heard of. Perhaps you should start moving around very" +
     " carefully in this part of Mirkwood.\n");
}

/*
 * Function name : set_add_spiders_near
 * Arguments     : str: none
 * Description   : adds the description for the spiders near by
 */

void set_add_spiders_near()
{
     add_item(({"web strands","web strand", "strands", "strand", "spider webs","spider web"}),
     "As you examine the trees and underbrush here very carefully," +
     " you notice that there are residual strands of spider webs" +
     " every now and then. Most of the webs appear to have been" +
     " broken a long time ago, yet judging by their size, you certainly" +
     " would not want to meet the kind of spider who could spin a web" +
     " that large.\n");

}

/*
 * Function name : set_add_elves_close
 * Arguments     : str: none
 * Description   : adds the description for the elves close by
 */

void set_add_elves_close()
{
      add_item(({"glade","glades","clearing","clearings"}),
     "There are several odd clearings around you here, which seem" +
     " to have been made by mortal hands. Signs of recent bonfires" +
     " are present in most of the glades, letting you know that someone" +
     " still uses them frequently. You get a strong feeling that your" +
     " continued presence in these glades is unwelcome.\n");
     add_item(({"bonfire","bonfires","signs"}),
     "Scattered ashes and neatly dug fire pits lead you to believe that someone" +
     " has been using these clearings quite frequently to entertain large gatherings" +
     " of people on a regular basis.\n");
}

/*
 * Function name : set_add_elves_near
 * Arguments     : str: none
 * Description   : adds the description for the elves near by
 */

void set_add_elves_near()
{
     add_item(({"glade","glades","clearing","clearings"}),
     "There is the occasional odd clearing around you here, which you" +
     " could almost swear was made by mortal hands. However, you" +
     " get the feeling that examining these clearings too closely might" +
     " be unwelcome.\n");
}

/*
 * Function name : set_add_mirkmount_close
 * Arguments     : str: none
 * Description   : adds the description for the mountains close by
 */

void set_add_mirkmount_close()
{
    add_item(({"mountain", "mountains", "mountains of mirkwood", "the mountains of mirkwood", "peak", "peaks"}),
    "You are passing very close to the southern feet of the" +
    " legendary mountains of Mirkwood. The horrible tales" +
    " about the dangers within echo in your mind as you gaze" +
    " at them in the @@daylight_desc@@ with a nervous eye.\n");
}

/*
 * Function name : set_add_mirkmount_near
 * Arguments     : str: none
 * Description   : adds the description for the mountains neaby
 */

void set_add_mirkmount_near()
{
    add_item(({"mountain", "mountains", "mountains of mirkwood", "the mountains of mirkwood", "peak", "peaks"}),
        "The ominous peaks of the mountains of Mirkwood are visible" +
        " north of where you now stand. Rising up out of the forest in the "+
        " @@daylight_desc@@, the mountains of mirkwood are" +
        " legendary for the dangers which lurk within.\n");
}

/*
 * Function name : set_add_mirkmount_far
 * Arguments     : str: none
 * Description   : adds the description for the mountains from far away
 */

void set_add_mirkmount_far()
{
    add_item(({"mountain", "mountains", "mountains of mirkwood", "the mountains of mirkwood", "peak", "peaks"}),
        "Far to the north, you can barely make out the mountains" +
        " of Mirkwood in the @@daylight_desc@@." +
        " Legendary for the supposed dangers which lurk within," +
        " you feel slightly uneasy even seeing them from" +
        " this distance.\n");
}

/*
 * Function name : set_add_riverrun_close
 * Arguments     : str: none
 * Description   : adds standard descr for the river nearby
 *                
 */

void set_add_riverrun_close()
{
    add_item(({"river", "river running"}),
        "The rushing waters of the River Running are quite" +
        " visible to you here, as they flow to the southeast" +
        " into the lands of Dorwinion..\n");
}


/*
 * Function name : set_add_riverrun_near
 * Arguments     : str: none
 * Description   : adds standard descr for the river running
 *                
 */

void set_add_riverrun_near()
{
    add_item(({"river", "river running"}),
        "Not too far away, you can hear the rushing sounds" +
        " of the River Running. A twisting blue ribbon of water," +
        " the River Running flows south and east out of Mirkwood " +
        " to feed the distant land of Dorwinion.\n");
}


/*
 * Function name : set_add_riverrun_far
 * Arguments     : str: none
 * Description   : adds standard descr for the river far away
 *                
 */

void set_add_riverrun_far()
{
    add_item(({"river", "river running"}),
        "Far off in the distance, you can barely make out the" +
        " rushing waters of the River Running. Twisting its way" +
        " to the south and east, the River Running flows into the" +
        " fabled land of Dorwinion.\n");
}


/*
 * Function name : set_add_wildlife
 * Arguments     : str: none
 * Description   : adds proof of wildlife in the forest
 */
void set_add_wildlife()
{
    add_item(({"wildlife", "animals"}),
        "There are abundant signs of wildlife all around you here in" +
        " Mirkwood, as various animal tracks cross beneath your"+
        " every step.\n");
    add_item(({"tracks", "animal tracks"}),
        "These tracks show the passing of many of the animals you" +
        " would expect to find in a great forest. Only, there also seems" +
        " to be faint signs of something rather unexpected as well.\n");
}
