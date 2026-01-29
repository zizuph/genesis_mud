/*
 * /d/Raumdor/common/farms/std/base.c
 *
 * Base room for Ardent's farms south of Drakmere
 *
 * Varian - April, 2020
 *
 */

#include "../defs.h"

inherit STD_ROOM;
inherit "/d/Gondor/common/lib/herbsearch";
inherit "/d/Gondor/common/lib/room_tell";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <macros.h>
/* #include "/d/Raumdor/common/farms/std/descriptors.c" */

void set_items_city();
void set_items_road();
void set_items_blonks();
void set_items_mill();
void set_items_field();
void set_items_cartwrights();
void set_items_horraces();
void set_herbs_1();
void set_herbs_2();


/*
 * Function name:        create_farms_room
 * Description  :        Use create_farms_room() to make wild rooms
 *                       that use information from this file
 */

void create_farms_room() 
{
}

nomask void create_room() 
{

    create_farms_room();

/*
 * Function name:        add_tell - used when inheriting 
 *                       "/d/Gondor/common/lib/room_tell";
 * Description  :        Gives some atmosphere by providing some
 *                       'sounds' in the room.
 */  

/*        add_tell("A soft breeze swirls past you, dancing across the " +
            "farmer fields as the " + VBFC("daylight_desc") + " " +
            "shines down upon them.\n")  ; 
        add_tell("Rolling clouds drift across the sky, covering the  " + 
            + VBFC("day_desc") + " " + VBFC("sun_moon") + " and " +
            "hiding the " + VBFC("light_type") + " temporarily.\n");
        add_tell("An opening in the clouds above allows the bright " + 
            VBFC("light_type") + " from the " + VBFC("day_desc") + " " +
            VBFC("sun_moon") + " to spread out across the nearby " +
            "farms.\n");
*/
        add_tell("A small brown toad hops past your feet.\n");
      
        add_tell("A flock of crows fly past in the distance.\n");

        add_tell("A nearby tree creaks.\n");

/*
 * Function name:        set_tell_time
 * Description  :        Provides time increments between tells
 */
        set_tell_time(random(400) + 70);
}

/*
 * Function name:        enter_inv
 * Description  :        Needed to start the room tells
 */

void
enter_inv(object ob, object from)
{
    start_room_tells();
    ::enter_inv(ob, from);
}


/*
 * Function name:        set_items_city
 * Description  :        Items added to rooms along the road when you
 *                       use set_items_city(); 
 *                       Use for the northern rooms of the farmroad.
 */




void
set_items_city()
{
    add_item( ({"city", "drakmere", "walled city", "walls"}),
        "To the north you can see the great walled city of Drakmere."+
        " This is where the farmers go with their produce every day "+
        "to keep the citizens fed.\n");
}




/*
 * Function name:        set_items_road
 * Description  :        Items added to rooms along the road when you
 *                       use set_items_road(); 
 *                       Use for all road rooms in the farms
 */

void
set_items_road()
{
    add_item( ({"road", "ground", "path", "narrow road", "dirt road",
            "narrow dirt road", "cobblestones"}),
        "A narrow dirt road runs through the farmlands here, hard " +
        "packed and well worn from the wagons farmers use to move " +
        "their harvest into Drakmere.The road is mostly dirt but in "+
        "some places you notice a few cobblestones.\n");
    add_item( ({"dirt", "soil"}),
        "The dirt on the road here is mostly a dry, dusty light " +
        "brown, having been packed down over years of use by the " +
        "farmers.\n");
    add_item("plains","They stretch all around you. Three farms and "+
        "a windmill are the only noticeable features on the vast "+
        "open plains.\n");
    add_item("hills","They roll on for as far as you can see. The "+
        "hills are spread out across the plains. None of them seem "+
        "to be of any significant size.\n");
    add_item(({"farm", "farms"}), "You notice that there are three "+
        "farms in this area. Two on the eastern side of the road and"+
        " one on the western side. You will have to move closer to "+
        "see any details about them.\n"); 
    add_item(({"tree", "trees"}),"There are trees spread out on the "+
        "plains, over the hills and between the fields and pastures."+
        " Most of them have had their branches broken off, probably "+
        "so they could be used for firewood.\n");
    add_item(({"pasture", "pastures", "fenced pasture",
            "fenced pastures"}),
        "Several pastures can be seen near the farms. Judging from "+
        "the smells and sounds you would guess they contain horses, "+
        "sheep and cows. Each farm seems to have their own favourite "+
        "animal. You should watch your step to avoid the droppings "+
        "that have been left all over the farm areas.\n");
    add_item(({"bush", "bushes", "brush", "underbrush"}), "There are "+
        "bushes lining the road. The foliage is very thick and you "+
        "can only see a short distance into the brush. Long sharp "+
        "thorns can be seen on the bushes and you doubt you would "+
        "want to venture into them. A few berries can be see here "+
        "and then, but not enough for you to want to pick them.\n");
}

/*
 * Function name:        set_items_blonks
 * Description  :        Items added to rooms on Blonks farm when you
 *                       use set_items_blonks(); 
 *                       Use for all Blonks rooms in the farms
 */

void
set_items_blonks()
{
    add_item( ({"house", "farmhouse"}),
        "The farmhouse is a low well built structure made of wooden "+
        "timber. The front door looks solid and there are no "+
        "visible windows.\n");
    add_item(({"tree", "trees"}),"There are trees spread out on the "+
        "plains, over the hills and between the fields and pastures."+
        " Most of them have had their branches broken off, probably "+
        "so they could be used for firewood.\n");
    add_item(({"pasture", "fenced pasture", "horse pasture"}), 
        "South of the farmhouse is a pasture with a few horses. Or "+
        "at least there should be, depending on the number of nearby "+
        " horse thieves. Better keep your eyes open so you do not "+
        "step in the horse droppings that are scattered all over "+
        "the pasture, courtyard and everywhere else. \n");
    add_item(({"field", "grain field", "fields", "grain fields"}),
        "There are grain fields on the east side of the farm. Several "+
        "flowers and herbs can also be seen scattered throughout the "+
        "grain fields.\n"); 
    add_item(({"droppings", "shit", "manure", "horse manure"}),
        "You can see, step on or smell the horse manure everywhere on "+
        "this farm. Whether it is hidden in the tall grass in the "+
        "pasture where you can step on it, or used as fertilizer in "+
        "the grain fields.\n"); 
}

/*
 * Function name:        set_items_mill
 * Description  :        Items added to rooms near the mill when you
 *                       use set_items_mill(); 
 *                       Use for all rooms close to the mill
 */

void
set_items_mill()
{
    add_item( ({"mill", "windmill", "tall mill", "tall windmill",
            "wooden mill", "wooden windmill", "tall wooden windmill"}),
        "A tall wooden windmill rises up out the nearby farms, " +
        "you would guess that the farmers use it to grind their " +
        "grains.\n");
}

/*
 * Function name:        set_items_field
 * Description  :        Items added to farmer fields when you
 *                       use set_items_field(); 
 *                       Use for all farmer fields rooms
 */

void
set_items_field()
{
    add_item( ({"soil", "dirt"}),
        "The soil here is dark and black, ideal for growing crops.\n");
}

/*
 * Function name:        set_items_cartwrights
 * Description  :        Items added to rooms on Cartwrights farm when
 *                       you use set_items_cartwrights(); 
 *                       Use for all Cartwrights rooms in the farms
 */

void
set_items_cartwrights()
{
    add_item( ({"house", "farmhouse"}),
        "A tall, sturdy-looking farmhouse belonging to the " +
        "Cartwright family is in the middle of this farm.\n");
    add_item(({"tree", "trees"}),"There are trees spread out on the "+
        "plains, over the hills and between the fields and pastures."+
        " Most of them have had their branches broken off, probably "+
        "so they could be used for firewood.\n");
}

/*
 * Function name:        set_items_horraces
 * Description  :        Items added to rooms on Horraces farm when
 *                       you use set_items_horraces(); 
 *                       Use for all Horraces rooms in the farms
 */

void
set_items_horraces()
{
    add_item( ({"house", "farmhouse"}),
        "A small wooden farmhouse, belonging to the Horrace's, " +
        "sits on the eastern edge of the farm here.\n");
    add_item(({"tree", "trees"}),"There are trees spread out on the "+
        "plains, over the hills and between the fields and pastures."+
        " Most of them have had their branches broken off, probably "+
        "so they could be used for firewood.\n");
}

/*
 * Function name:        do_toss
 * Description  :        Provides an emote to toss a rock 
 * Returns      :        int 0 - Prompt for proper syntax
 *                       int 1 - Returns the emote
 */

int
do_toss(string str)
{
    if(!str)
    {
        notify_fail("Toss what? A rock perhaps?\n");
        return 0;
    }
    if((str != "rock")  && (str != "small rock") && (str != "a rock")
        && (str != "a small rock"))
    { 
        ("Toss what? A rock perhaps?\n");
        return 1;
    }
    write("You search around the ground and find a small rock which " +
        "feels just right for throwing. You wind up and toss the " +
        "rock, watching as it sails into the distance.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " idly picks " +
        "up a smalle rock and tosses it into the distance.\n");
    return 1;
}

/*
 * Function name:        set_herbs
 * Description  :        Makes all herbs in this list available to be
 *                       found when searching for herbs.
 *                       Different numbers provide different lists
 *                       Must add set_herbs_# into farms rooms
 */

void
set_herbs_1()
{
    set_up_herbs( ({ CARROT, REDWEED, TUO, BLUEBERRY}),
                ({"ground","field"}), 5);
}

void
set_herbs_2()
{
    set_up_herbs(({ GARLIC, GINGER, BLACKBERRY, MINT}),
                ({"ground","field"}), 5);
}
public void
init()
{
    ::init();
    add_action("do_toss", "toss");
    add_action("do_toss", "throw");
}