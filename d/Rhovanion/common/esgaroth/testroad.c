inherit "/d/Rhovanion/common/esgaroth/esroom";

#include <stdproperties.h>
#include <macros.h>

create_esgaroth() {}

create_exits() {}

reset_road()
{
    if (random(4))
        return;
    switch(random(10))
    {
        case 0: case 1: case 2: case 3:
            reset_a_monster("townsman"); break;
        case 4: case 5: case 6: case 7:
            reset_a_monster("townswoman"); break;
        case 8:
            reset_a_monster("ruffian"); break;
        case 9:
            reset_a_monster("guard"); break;
    }
}

nomask void
reset_room()
{
    reset_road();
}

string longdesc()
{
    string text, foobar, area;
    int x, y;

    sscanf(MASTER, "%s/es-%d-%d", foobar, x, y);
    if (x < 5)
    {
        area = "northwestern";
        if (y > 5)
            area = "western";
        if (y > 9)
            area = "southwestern";
    }
    if ((x < 8) && (x > 4))
        if (y > 5) area = "southern"; else area = "northern";
    if (x > 7)
    {
        area = "northeastern";
        if (y > 5)
            area = "eastern";
        if (y > 9)
            area = "southeastern";
    }

    text = "You are on a planked road in the " + area + " section of " +
        "the lake town of Esgaroth.  ";
    switch (ctime())
    {
        case "early morning":
            text += "The sun is rising in the east, and the reflection " +
                "off of the water has made the lake into a glowing sheet " +
                "of flame.  ";
            break;
        case "morning":
            text += "The sun has already risen, and shines down on the " +
                "faded planking of the city streets, and the roofs of the " +
                "homes and businesses nearby.  ";
            break;
        case "noon":
            text += "It is noon now, and the sun burns fiercely overhead.  ";
            break;
        case "afternoon":
            text += "The sun has passed its zenith, and is slowly " +
                "descending into the west.  The houses cast long afternoon " +
                "shadows on the ground.  ";
            break;
        case "evening":
            text += "It is evening now, and the air is starting to get " +
                "cooler as the sun goes down.  ";
            break;
        case "night":
            text += "It is nighttime in Esgaroth, the moon reflects off of " +
                "the water.  There are lights in many of the houses, as " +
                "the people work and talk long into the night.  ";
            break;
    }
    text += query_extras();
    return text;
}

nomask void
create_room()
{
    set_short("A road in Esgaroth");
    set_long("@@longdesc@@");
    create_exits();
    create_esgaroth();
    reset_room();
} 
