/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house4b.c
 * Calathin external house.
 * 09/30/1999 -- TOMAS
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>

inherit STDROOM;
#include <stdproperties.h>
string ext_lamps();
string light_lamps();
string butler_light();

public void
create_room()
{
    ::create_room();
    INSIDE;
 
    set_short("Sitting room");
    set_long("This is a lavishly appointed sitting room. " +
       "The walls are paneled with a dark walnut paneling. " +
       "Several niches around the room hold various statues " +
       "of knights. Crystal lamps are evenly spaced around the " +
       "walls lighting the room with a soft warm light. A large " +
       "marble fireplace takes up much of the far wall. The floor " +
       "is covered with a finely woven rug dyed a deep crimson. Near " +
       "the fireplace sit a plush chair and small table making a " +
       "comfortable reading area. In the center of the room is a " +
       "group of chairs arranged around a low table.\n");


    add_item(({"walls", "paneling"}),
       "The walls have been covered with a dark walnut wood stained " +
       "with a slight reddish tint. The trim at the floor and ceiling " +
       "are stained darker to be almost black and have been carved " +
       "with elaborate patterns. A piece of trim also circles around the " +
       "room at waist level it too is stained a darked color. Eight crystal " +
       "lamps, two to a wall are evenly spaced around the room. In three of " +
       "the walls is a niche containing a statue, the fourth wall is dominated " +
       "by a large fireplace.\n");

    add_item(({"statues", "niches"}),
       "In each niche there is a statue. One has been carved from a silvery " +
       "wood you don't recognize, the second looks to have been cast in bronze, " +
       "and the third is carved from marble.\n");

    add_item(({"silver statue", "silvery statue", "wood statue", "first statue"}),
       "This knight has been carven from a silvery wood that has a very fine " +
       "grain and almost seems to glow with the light in the room. The knight " +
       "is holding his sword by its blade out in front of him with the point down. " +
       "He has his head back and seems to be looking up towards the heavens.\n");

    add_item(({"heavens","first niche"}),"A small star has been carved into the " +
       " top of the niche. Perhaps thats what the knight is staring at.\n");

    add_item(({"bronze statue", "second statue"}),
       "This statue is of a knight kneeling down with his head hung low. " +
       "His sword is broken and laying on the ground below his limply hanging " +
       "hand. The shield strapped to his other arm is battered and dented. " +
       "This statue does a remarkable job of capturing the exhaustion and " +
       "despair that often torments a warrior after a long battle. Even the " +
       "color of the bronze contributes to the emotion of the statue.\n");

    add_item(({"marble statue", "third statue"}),
       "Carved from a pink marble this statue depicts a knight standing " +
       "erect and grasping a pike in one hand. The second hand is clasping " +
       "a wound in his side. The dark pink vein in the marble is " +
       "right below his hand creating the image of blood flowing from the wound.\n");

    add_item(("lamps"),"The lamps are made from a delicate crystal and hold " +
       "a fine grade of oil that burns with a soft golden color. A small " +
       "silver disc behind each lamp helps direct the light out into the room.\n");

    add_item(("fireplace"),"The fireplace is crafted from marble and has " +
       "walnut trim and mantle. The oak wood being burned creates a strong " +
       "hot fire giving the room a comfortable warmth despite the cold outside.\n");

    add_item(({"plush chair","chair"}),
       "The chair by the fire is well padded creating a very soft and " +
       "comfortable seat. It has been covered with a crimson cloth matching " +
       "the color of the rug. A small table next to the chair holds a small " +
       "cup and a large book.\n");

    add_item(({"small table","table"}),
       "This table has been crafted from walnut like most of the woodwork " +
       "in this room. The small top has been inlaid with a darker wood to " +
       "create a pattern. It holds a small pewter cup and a large book.\n");

    add_item(({"cup", "small cup", "pewter cup"}),
       "The cup is rather plain and well worn its not very elaborate or " +
       "high quality like most of the stuff in the house. Its probably an " +
       "old favorite of the owners for some reason. It appears to be filled " +
       "with tea, probably been sitting here awhile because the tea is cold.\n");

    add_item(("book"),"This large book is bound in plain brown leather and " +
       "appears to be well worn. From the title The Maintenance of the Modern " +
       "Army you assume it to be a treatise on the logistics of warfare.\n");


    add_exit(CALATHIN_DIR + "houses/house4a","east",0,1);


    add_cmd_item(({"book"}),
                 ("read"),
                 ("You would rather not, there isn't a bed nearby and " +
                  "no doubt reading this would put you to sleep in " +
                  "short order.\n"));

    add_cmd_item(({"chair"}),
                 ("sit"),
                 ("You sit in one of the chairs then decide to get on with " +
                  "your business.\n"));

    add_cmd_item(({"crystal lamps"}),
                 ("extinguish"),
                 ("@@ext_lamps"));
      
    add_cmd_item(({"crystal lamps"}),
                 ("light"),
                 ("@@light_lamps"));
                 

    reset_room();

}

string
ext_lamps()
{
    add_prop(ROOM_I_LIGHT, 0);
    write ("You extinguish the lamps.\n");
    say(QCTNAME(TP) + " extinguishes the crystal lamps.\n");
    set_alarm(10.0, -1.0, "butler_light");
  return "";
}


string
light_lamps()
{
    add_prop(ROOM_I_LIGHT, 1);
    write ("You light the crystal lamps.\n");
    say(QCTNAME(TP) +" lights the crystal lamps.\n");
   
  return "";
}


string
butler_light()
{
    add_prop(ROOM_I_LIGHT, 1);
    say("The butler enters the room relights the lamps then leaves.\n", 
       ({TP}));
         TP->catch_msg("The butler enters the room relights the lamps then leaves.\n");
  return "";
}
