/*
 * Base room for Waymeet villiage outdoors
 * -- Raymundo, Jan 2020
 */

/*    Notes:
 *    add_dogs()        room tells and add_items for the dogs around
 *                        town.
 *                        
 *    add_smial()        Include a string with the file name of 
 *                        the room you want players to go to when
 *                        they <enter smial>. This is set to the
 *                        WAYM_HOUSE_DIR.
 *                        
 *    add_street()    1 for weeds. 0 for no weeds.
 *                        Otherwise, just add_items for the street.
 *
 *    gravel_sound()    This is purely cosemetic. Use in exits for the
 *                        sound of gravel crunching under players' feet
 *                        as they walk.
 *
 */ 


#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <terrain.h>
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>

inherit AREA_ROOM;
inherit "/d/Shire/std/room/room_tell";



string smial = "h_1_1";  //for use with the add_smail function.
int weeds; //Determines whether or not there are weeds in add_street()

void
create_waymeet_room()
{
}

void
create_area_room()
{
    setuid(); 
    seteuid(getuid());

    area = "in"; /* Distance from areaname */
    areaname = "Waymeet";
    land = "the Shire";
    areatype = 10;
    areadesc = "village";
    
    extraline = "";
    
    create_waymeet_room();
    set_room_tell_time(200);
    add_item(({"surroundings","expanse","plain","shire"}),
      "The Shire is an expanse of plains, with the occasional village "
      +"or cultivated field, where the hobbits till the rich soil of the "
      +"Shire.\n");
 
    add_item(({"field", "fields"}),
        "In the distance, you see fields where farmers grow vegetables for the "
        + "hobbits of Waymeet to eat.\n");
    add_item(({"vegetables", "food"}),
        "You can't tell what type of vegetables they are from here.\n");
    add_item(({"village", "Waymeet", "waymeet"}),
        "Yes, you are in the small village of Waymeet. Many hobbits live in "
        + "their smials here north of the Great East Road, while to the "
        + "south of the road they have shops and an inn.\n");
    add_item(({"farm", "farms"}),
        "The farms are in the distance. You can see an old red barn as "
        + "well as a farmhouse.\n");
    add_item( ({"house", "farmhouse", "farm house"}), "The farmhouse looks "
        + "like the type of place a hobbit farmer would live. You see small "
        + "windows and even a round door on the farmhouse.\n");
    add_item( ({"barn", "barns"}), "The barn is large enough to house several "
        + "ponies and even a few cows. It's painted red, but the paint has "
        + "chipped and faded over time.\n");
}

/* Function:    gravel_sound()
 *                Use this in your exits if you want the gravel to crunch under
 *                people's feet when they walk. Purely for effect. This function
 *                returns 0 because we don't want to block the player from 
 *                leaving the room.
 */

int
gravel_sound()
{
    int the_sound = (random(5));
    if(!the_sound)
    {
    write("\nThe gravel on the road crunches beneath your feet as you walk.\n\n");
    say("\nThe gravel on the road crunches beneath " + QTPNAME(TP) + " feet as "
        + HE_SHE(TP) + " walks on the street.\n\n");
    }
    return 0;
}

/* I plan to have dogs in Waymeet. The dogs will protect the 
 * hobbits who live here and chase off the scallywags who try 
 * to hurt hobbits. This will be a nice warning to those
 * sneaky snooks!
 */
void
add_dogs()
{
    add_room_tell("A large mastiff trots by.");
    add_room_tell("You hear dogs barking nearby.");
    add_room_tell("You hear a hobbit man calling for his dog.");
    add_room_tell("You hear deep, dangerous sounding growling.");
    add_room_tell("A dog the size of a small pony walks up and sniffs "
        + "your hand before wandering back toward its smial.");
    add_room_tell("You notice a dog, alert and defensive, watching you.");
    
    add_item( ({"dog", "dogs", "mastiff", "mastiffs"}), "You notice quite "
        + "a few dogs around Waymeet. They all look very protective of the "
        + "hobbits who live here.\n");

}

/*
 * Function:     add_street
 * Arguments:    weeds (1, 0)
 *                If you select 1, weeds will be added to the road description.
 *                0 is for no weeds. Pretty simple. Otherwise, this is just the 
 *                description of the street and the gravel.
 */
 
void
add_street(int weeds)
{
    string is_weeds;
    if(weeds == 1)
    {
        is_weeds =("Weeds poke up here and there through the gravel on the "
            + "road.");
        add_item( ({"weed", "weeds"}), "The weeds look like grasses and "
            + "dandelions and other things a goat or cow might eat.\n");
        add_item( ({"grass", "grasses"}), "The grass is green. It's about up to "
            + "the top of your boots, and would make a lovely snack for a goat "
            + "or a sheep.\n");
        add_item( ({"dandelion", "dandelions"}), "The dandelions are bright "
            + "yellow, rising above the street like short balls of sunshine. "
            + "They look like weeds, but some hobbits collect the leaves and "
            + "turn them into wine.\n");
    }
    
    else
    {
        is_weeds = ("");
    }
    add_item( ({"street", "road"}), "This is one of the streets that "
        + "hobbits use to walk around Waymeet. It has been covered with "
        + "gravel to both keep dust down and alleviate the mud after "
        + "it rains. " + is_weeds + "\n");
        
    add_item( ({"gravel", "rocks"}), "The gravel looks like rocks common "
        + "to the Shire, except that they've been crushed into pebble "
        + "sized gravel.\n");
        
}

/* 
 * Function:     add_smail
 * arguments:     smial_room
 *                    For this string, write the file name of the smial
 *                    in WAYM_HOUSE_DIR that you want the <enter smail>
 *                    command to take the player to. For example, if you
 *                    set the string to "h_3_1", the player will be moved 
 *                    to WAYM_HOUSE_DIR + "h_3_1" when he/she types 
 *                    <enter smial>.
 */
 
void
add_smial(string smial_room)
{
    add_item("door", "You see a round door leading into the smial. You could "
        + "likely enter if you want.\n");
    add_cmd_item("on door", "knock", "You knock on the door but hear no "
        + "reponse from inside.\n");
    add_cmd_item( ({"door", "smial", "hole", "hobbit hole", "burrow"}), "enter", 
        "@@enter_hole@@");
    add_item( ({"smial", "hole", "hobbit hole"}), "This smial looks like a "
        + "cozy home for a hobbit. It's almost completely underground, "
        + "as smials are, with a cute round door leading inside.\n");
    smial = smial_room;
    
}
//works with the add_smail function.
int
enter_hole()
{
    say(QCTNAME(TP) + " opens the door and enters the smial.\n");
    write("You open the door and enter the smial.\n");
    tell_room((WAYM_HOUSE_DIR + smial), QCTNAME(TP) + " enters the smial from outside.\n");
    TP->move_living("M", (WAYM_HOUSE_DIR + smial));
    return 1;
}