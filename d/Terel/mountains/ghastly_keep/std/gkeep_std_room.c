/* /d/Terel/mountains/ghastly_keep/std/gkeep_std_room.c
 *
 * Standardroom for Ghastly Keep
 *
 * Znagsnuf
 *
 * - Language tweak complete (Gorboth)
 *
 * Lucius, Dec 2017: Blocked inbound teleportation.
 *
 */

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h";

inherit "/std/room";
inherit "/d/Sparkle/lib/room_tell";

string extra_longdesc;
string dif_smell();

void set_extra_longdesc(string str);
void update_longdesc();
void set_area(int i);

int query_area();
int area;

/*
 * Function name: set_extra_longdesc()
 * Description  : Sets an additional static string to the long description.
 */
void set_extra_longdesc(string str)
{
    extra_longdesc = str;
}


/*
 * Function name: query_extra_longdesc()
 * Description  : Returns the additional static long desc. string.
 */
string query_extra_longdesc()
{
    return extra_longdesc;
}


/*
 * Function name: set_area()
 * Description  : Sets the integer of a specific area.
 */
void set_area(int i)
{
    area = i;
}

/*
 * Function name: query_area()
 * Description  : Returns the integer of a specific area.
 */
int query_area()
{
    return area;
}

/*
 * Function name: update_longdesc()
 * Description  : Sets the proper long descriptions + items vs season.
 */
void update_longdesc()
{

    // Ghastly keep first level.
    if (area == GKEEP_LVL1)
    {
        set_short("Beneath the fallen castle");
        set_long("Beneath the fallen castle lies a narrow, humid room. "
        + "It is covered in rubble, roots and dead vermin. The blackness "
        + "engulfing the room seems to seep from the very pores of what "
        + "surrounds you. The blackness is formed from some primeval hatred, "
        + "and the collective despair of all those it has taken before. "
        + "The air smells as if it hasn't moved for years, festering like a "
        + "stagnant pool of water. You can feel the wind shifting as the "
        + "spirits roam and wander the soulless ruins.\nYou can sense an "
        + "evil presence around you here.\n");

        add_item(("rubble"), "Rubble made out of rough fragments of broken "
                 + "stone covers the area.\n");

        add_item( ({"roots", "vermin"}), "Old roots and dead vermin lay in "
                   + "heaps at unnatural angle around the area.\n");

        add_item( ({"black", "blackness", "darkness"}), "The blackness "
                   + "is formed from some primeval hatred and the collective "
                   + "despair of all those it has taken before.\n");

        add_item( ({"water", "air", "smell", "pool"}), "The air smells as if "
                   + "it hasn't moved for years, festering like a stagnant "
                   + "pool of water.\n");

        add_item( ({"wind", "spirits", "ruin", "ruins", "presence"}), "You "
                   + "can feel the wind shifting as the spirits roam and "
                   + "wander the soulless ruins. You can sense the evil "
                   + "presence within it.\n");

        add_item( ({"mildew", "fungus"}), "The smell of mildew and fungus "
                 + "makes you cover your mouth and nose. It is unbearable.\n");

        add_item( ({"wall", "walls", "ceiling"}), "The wall and ceiling "
                    + "is completely covered with mildew and fungus.\n");

        add_cmd_item(("rubble"),
                  ({"pull", "pry", "move"}), "You pry away some of the larger blocks "
                  + "of rubble, but you do not discover anything "
                  + "interesting.\n");

        add_cmd_item(("roots"),
                  ({"pull", "pry","move"}), "You pull away some of the roots, but "
                  + "you do not find anything of value.\n");

        add_cmd_item(({"water","air","pool"}),
                  ({"smell", "taste"}), "The smell of death lingers "
                   + "in the air.\n");

        //It's dark.
        add_prop(ROOM_I_LIGHT,         -1);
        add_prop(ROOM_I_INSIDE,         1);
        add_prop(ROOM_I_NO_ALLOW_STEED, 1);

        //Room tell.
        set_tell_time(60);
        start_room_tells();
        add_tell("The wind shifts as the spirits roam the soulless basement.\n");
        add_tell("The stench of death lingers in the air.\n");

        // For adding a custom message in the future
        set_no_exit_msg( ({ "northeast", "northwest", "north", "southeast",
                        "east", "west", "south", "southwest" }),
                        "A wall stops you from walking in that direction.\n");

        set_no_exit_msg( ({ "up", "down" }),
                        "After struggling for a while you find out that is "
                      + "not possible.\n");


    }

    // Ghastly keep second level.
    if (area == GKEEP_LVL2)
    {
        set_short("In a cave under the fallen castle");
        set_long("Small loose stones litter the floor making each step more "
                + "precarious. This cave has been fashioned out of bedrock. "
                + "The stones supporting the ceiling are jagged and uneven "
                + "and arranged in such a way as to be difficult to spot. "
                + "The stalagmites hanging from the ceiling are rather "
                + "unusual.\n");

        add_item( ({"variety", "stalagmites", "stalagmite"}), "They appear to "
                   + "be made of rounded, irregular, hollow cones, which "
                   + "are concave upwards.\n");

        add_item( ({"ceiling", "roof"}), "All the stones supporting "
                   + "the ceiling are jagged and uneven, not one are like.\n");

        add_item( ({"bedrock", "cave"}), "The caves are carved into "
                   + "the consolidated rock underlaying the surface -"
                   + " an impressive piece of work, this place.\n");

        add_item( ({"stone", "stones", "floor"}), "Many stones of "
                   + "uneven shape litters the floor, making you careful "
                   + "with your next step.\n");

        add_item( ({"mildew", "fungus"}), "The smell of mildew and fungus "
                  + "makes you cover your mouth and nose, it is unbearable.\n");

        add_item( ({"wall", "walls", "ceiling"}), "The wall and ceiling "
                   + "is completely covered with mildew and fungus.\n");

        //It's darker.
        add_prop(ROOM_I_INSIDE,         1);
        add_prop(ROOM_I_LIGHT,         -2);
        add_prop(ROOM_I_NO_ALLOW_STEED, 1);

        //Room tell.
        set_tell_time(60);
        start_room_tells();
        add_tell("The stillness of the air seems to suck out even the "
                + "smallest sound.\n");
        add_tell("You hear a faint sound, as a water drops from one "
                + "of the stalagmites.\n");

        // For adding a custom message in the future
        set_no_exit_msg( ({ "northeast", "northwest", "north", "southeast",
                        "east", "west", "south", "southwest" }),
                        "A wall stops you from walking in that direction.\n");

        set_no_exit_msg( ({ "up", "down" }),
                        "After struggling for a while you find out that is "
                      + "not possible.\n");

    }
    // Ghastly Keep outdoor.
    if (area == GKEEP_OUTDOOR)
    {

        set_short("On a slick path towards a Castle");
        set_long("The mountain path has become slick from freezing rain. "
                + "Icy puddles have been left within two deep ruts making "
                + "for a precarious climbing route. The sun occasionally "
                + "glimmers down from a gap between the clouds reflecting "
                + "brightly off the azure-blue lake. "
                + query_extra_longdesc() + "\n");

        add_item( ({"puddle", "puddles", "water", "ice", "icy puddle"}), "The "
                   + "puddles are frozen over with a thin layer of ice that "
                   + "cracks like shattering glass as it is broken.\n");

        add_item( ({"ruts", "rut"}), "Twin lines of tracks have been "
                   + "created from years of merchant wagons which have "
                   + "followed the path through the mountain pass.\n");

        add_item( ({"clouds", "lake", "clouds"}), "Thin lines of sunlight "
                   + "cascade down from a gap in the clouds, onto the azure "
                   + "blue lake.\n");

        add_item( ({"mist", "void"}), "The void obscures your view, but you "
                   + "faintly make out the outlines of a castle in the "
                   + "distance.\n");

        add_item( ({"mountain path", "paths", "path"}), "The mountain path "
                   + "winds ahead as effortlessly as the snowflakes hit the "
                   + "ground. It is as steep as it is narrow and rocky in a "
                   + "chaotic way, just enough to stop your gait falling into "
                   + "a steady rhythm.\n");

        add_item( ({"snowflakes", "snowflake", "flake", "flakes"}), "Gravity "
                   + "has finally won the long battle, and carries "
                   + "the snowflakes to the ground.\n");

        add_item( ({"mountain", "mountains"}), "The dove-white mountain "
                   + "range soars into the air, trapping the glistening "
                   + "sun behind them.\n");

        add_item( ({"sun", "sunlight"}), "Thin lines of sunlight cascade "
                   + "down a gap of clouds into an azure blue lake.\n");

        add_item( ({"gap", "gaps", "sky", "gap of clouds"}), "There is a "
                   + "small gap in the sky, allowing rays of light to find "
                   + "their way to the ground.\n");

        add_item( ({"ground", "floor", "grounds"}), "The ground is covered "
                    + "with fresh shimmering snow.\n");

        add_item( ({"snow", "branches"}), "The branches hangs low "
                   + "with the weight of the snow, they are almost breaking "
                   + "under the weight of snow. The green is still visible "
                   + "under the brilliant white, contrasting perfectly.\n");

        add_item( ({"rain", "rains"}), "The rain has now turned into solid "
                   + "ice.\n");

        add_item( ({"solid ice"}), "The solid ice made out of the melting "
                   + "water, radiates in a bluish color as the sunlight "
                   + "hits it.\n");

        //Outdoor, and light.
        add_prop(ROOM_I_LIGHT, 2);
        add_prop(ROOM_I_INSIDE, 0);

        //Room tell.
        set_tell_time(60);
        start_room_tells();
        add_tell("Silvery flakes drift down.\n");
        add_tell("A blackbird swoops down to it's nest.\n");
        add_tell("The sun is rising and a thick blanket of snow is "
                + "now visible covering most everything.\n");
        add_tell("The snow now reflects the sky.\n");
    }
    // Ghastly Keep in the tree.
    if (area == GKEEP_INTREE)
    {

        set_short("In a snow covered tree");
        set_long("The tree stands mute in the winter air. The branches are "
              + "thick, and covered in snow, they almost obscure the sun rays "
              + "that brings a glimpse of light. There is a fragrance here, a"
              + " distinctive aroma of snow and frost. From the ground far "
              + "below you hear the sounds of cracking ice.\n"
              + "A blackbird's nest.\n");

        add_item( ({"ruts", "puddle", "puddles", "water"}), "The puddles are "
                   + "frozen over with a thin layer of ice that cracks like "
                   + "shattering glass as it is broken.\n");

        add_item( ({"clouds", "lake", "sunlight", "gap"}), "The sunlight "
                   + "cascades from a gap in the clouds into an azure blue "
                   + "lake.\n");

        add_item( ({"ground", "grounds"}), "You are too high "
                   + "up to see any movement on the ground far below, but "
                   + "that doesn't stop you from hearing the sounds.\n");

        add_item( ({"snow", "branches", "branch"}), "The branches hang low "
                   + "with the weight of the snow. They are almost breaking "
                   + "under the weight. The green is still visible "
                   + "under the brilliant white, contrasting perfectly.\n");

        add_item( ({"nest", "blackbirds nest", "blackbird's nest"}),
                     "The nest is made out of "
                   + "clusters of twigs and tiny branches.\n");

        add_item( ({"twigs", "cluster", "clusters","tiny branches"}), "They "
                   + "are cleared of snow, making them perfect for a nest.\n");

        add_item( ({"tree", "trees"}), "This is a massive dark spruce. The "
                   + "branches are snow covered, but the green is still there "
                   + "under the brilliant white, contrasting perfectly.\n");

        //Outdoor, and light.
        add_prop(ROOM_I_INSIDE, 0);
        add_prop(ROOM_I_LIGHT,  2);
        add_prop(ROOM_I_NO_ALLOW_STEED, 1);

        //Room tell.
        set_tell_time(60);
        start_room_tells();
        add_tell("Silvery flakes drifts down.\n");
        add_tell("The sun is rising and the thick blanket of snow is now "
                + "visible.\n");
        add_tell("The snow now reflects the sky.\n");
    }
}

/*
 * Function name: create_gkeep_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_gkeep_room(void)
{
    //add_prop("/d/Terel/open/MAP_FILES/ghastly_keep.txt", 1);
    // Redefine this
}

/*
 * Function name: create_room
 * Description  : Constructor, redefined so we can set some default
 * properties
 */
public nomask void
create_room(void)
{
    create_gkeep_room();
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
}

/*
* Function name: init()
* Description  :
*/
void
init()
{
    ::init();

    if (area == GKEEP_LVL1 || area == GKEEP_LVL2)
	add_action(dif_smell, "smell");
}

public string
dif_smell()
{

  if (area == GKEEP_LVL1 || area == GKEEP_LVL2)
  {
    switch (random(4))
    {
    case 0:
        write("The smell of fungus and mildew is unbearable, making you "
             + "cover your mouth and nose.\n");
        break;
    case 1:
        write("The stench of fungus and mildew is repellent.\n");
        break;
    case 2:
        write("The odor of fungus and mildew is brain-numbingly foul.\n");
        break;
    case 3:
        write("The moldy smell of fungus and mildew is stomach churning.\n");
        break;
    }
    return "";
  }

  return "";
}
