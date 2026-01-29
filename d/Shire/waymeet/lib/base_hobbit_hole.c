/* 
 * add_items, etc for hobbit holes
 * in Waymeet
 *
 * --Raymundo, Jan 2020
 */
 
inherit "/d/Shire/std/room";


#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>

void reset_shire_room();

void
create_hobbit_room()
{
    
}

void
create_shire_room()
{

        
    
    add_prop(ROOM_I_INSIDE, 1);
    set_room_tell_time(200);
    
    create_hobbit_room();
        
}

void
reset_shire_room()
{
    
}

void
init()
{
    ::init();

}



/*
 * Function:     add_kitchen
 * Counter_top    material the counter top is made of (noun)
 *
 * This function adds the kitchen for a poor house. The counter
 * top material is included as a string.
 */

void
add_kitchen(string counter_top)
{
    add_item( ({"counter", "counter top"}), "The counter top is made of "
        + counter_top + " and is a bit taller than a hobbit's waist. It "
        + "looks like a nice place to cut some vegetables for a soup or "
        + "maybe even a Sunday roast.\n");
    add_item( "sink", "You see a small farmhouse-style sink tucked against "
        + "the exterior wall. There is a small pipe that leads into the "
        + "the wall from underneath it. You infer the pipe is the drain.\n");
    add_item( ({"pipe", "drain"}), "The drain leads from beneath the sink "
        + "into the exterior wall. It must drain the water from the sink "
        + "somewhere outside.\n");
    add_item( ({"icebox", "ice box"}), "You see an ice box against one of "
        + "the walls. That would be a handy place to store meat or cheese!\n");
    add_item( ({"meat", "cheese"}), "It's probably in the ice box.\n");
    add_item( ({"pantry"}), "There is a closed pantry next to the counter. "
        + "You would expect to find beans and salt and spices in there, and "
        + "perhaps even some tea.\n");
        
    add_cmd_item("ice box", "open", "Your hands are too big to open the "
        + "icebox.\n");
    add_cmd_item( ({"in ice box", "in icebox"}), ({"look", "l"}),
        "You can't look in the icebox--it's closed. But honestly, it wouldn't "
        + "do much good to leave the icebox open. All the ice would melt and "
        + "then the food would spoil.\n");
    add_cmd_item( "pantry", "open", "You open the pantry and look inside. You "
        + "see beans and salt and spices in there. Ooooh, and a little tea "
        + "too!\n");
        
}//add_kitchen

//If the hobbit hole is low-income, here's a floor.

add_floor_poor(string rug)
{
    add_item("The floor seems to be made of river stones that were carried "
        + "here one by one and mortarted into a somewhat smooth floor. There "
        + "is a " + rug + " rug that tries to cover the floor as best as it "
        + "can, given its condition.\n");
    add_item("rug", "The rug is " + rug + " and mostly covers the floor, "
        + "although you can see a few places where the rug has worn away "
        + "and now the floor peeks through.\n");
    add_item( ({"place", "places"}), "In these places, you can see the floor, "
        + "even though there is a rug.\n");
    add_item( ({"rock", "river rock", "mortar", "rocks", "river rocks"}), 
        "These rocks have been "
        + "hauled into the room from the river. Because of the moving water, "
        + "the rocks are completely smooth. A basic mortar holds the rocks "
        + "together and makes an inexpensive (but labor intensive) floor for "
        + "the smial.\n");
    add_item("smial", "In a hole in the ground, stood a " 
        + TP->query_nonmet_name() 
        + ". Not a nasty, dirty, wet hole, filled with the ends of worms and "
        + "an oozy smell, nor yet a dry, bare, sandy hole with nothing in it "
        + "to sit down on or to eat: it was a hobbit-hole, and that means "
        + "comfort.\n");
    add_item("floor", "The floor is made of river rocks. It's quite smooth, "
        + "almost slippery.\n");
        
    add_item( ({"wall", "walls"}), "The walls are made of river rocks stacked "
        + "one on top of another. They remind you of a cave.\n");
    add_item( "ceiling", "You can't say much about the ceiling, except that it "
        + "keeps the rain off your head.\n");
        
    add_cmd_item( ({"rock", "river rock", "mortar", "rocks", "river rocks", "floor"}), 
        ({"feel", "touch"}), "The river "
        + "rocks on the floor feel smooth to the touch. They are securely "
        + "mortared together.\n");
    add_cmd_item( "rug", "shake", "You begin to shake the rug, but notice "
        + "dust start to billow off of it. Perhaps this is not the best "
        + "place to shake a rug.\n");
    add_cmd_item( "floor", "clean", "You don't have a broom to clean the "
        + "floor with.\n");
}//add_floor_poor

/*
 * Function:    add_bedroom_child
 * arg            either bed or bunk bed
 *
 * This function adds either a single bed or bunk bed for a child's room,
 * along with various add_items for a hobbit bedroom.
 */
 
add_bedroom_child(string arg)
{
    if(arg == "bed")
    {
        add_item( ({"bed", "single bed"}), "The bed is just large enough "
            + "for a hobbit child, which is to say it's entirely too "
            + "small for you. It has warm covers and a fluffy pillow on "
            + "it.\n");
        add_cmd_item( "bed", "make", "You dont need to make the bed. It's "
            + "already been made!\n");
    }
    if(arg == "bunk bed")
    {
        add_item( ({"bed", "beds", "bunk bed"}), "This is a bunk bed, "
            + "designed to allow two children to sleep in one room. The "
            + "top bunk is quite narrow, but it has a railing to keep "
            + "the child from falling out of it, while the bottom bunk "
            + "is much wider, presumably for an older child. Both bunks "
            + "have warm covers and fluffy pillows.\n");
        add_item( ({"top bunk", "top bed"}), "The top bunk is so high "
            + "that you couldn't even sit on it without bumping your "
            + "head on the ceiling. You notice a ladder leading up "
            + "to the top bunk and a railing to keep its occupant "
            + "from falling out.\n");
        add_item( ({"ladder", "ladders"}), "The ladder is made of wood, "
            + "and leads from the floor up to the ceiling.\n");
        add_item( ({"railing"}), "The railing is about two hands high. "
            + "It's made of wood and runs the length of the bed, except "
            + "for a small gap where the occupant gets onto the bunk.\n");
        add_item("gap", "The gap is just wide enough for a hobbit child.\n");
        
        add_cmd_item( ({"ladder", "ladders"}), "climb", "You start to climb "
            + "the ladder, but it creaks so loudly you stop. You're way too "
            + "heavy for this ladder!\n");
    }
    
    add_item( ({"pillow", "pillows"}), "The pillow is nice and soft, and "
        + "quite fluffy. It appears someone has taken the time to fluff the "
        + "pillow.\n");
    add_item( ({"blanket", "blankets", "cover", "covers"}), "The covers look "
        + "very warm.\n");
    
    add_item( ({"dresser", "chest of drawers", "drawer", "drawers"}),
        "The dresser a little taller than a hobbit child. It looks like the "
        + "perfect place to store some clothes or extra blankets.\n");
    add_cmd_item( ({"dresser", "chest of drawers", "drawer", "drawers"}),
        "open", "You try to open the drawer, but it's stuck closed.\n");
        
    add_item( ({"toy", "toys"}), "You see toys all over the floor. This looks "
        + "like the kind of place where kids would be happy.\n");
    add_cmd_item( ({"toy", "toys"}), ({"get", "take"}), "You wouldn't feel right "
        + "taking a toy from a child! You should play with them instead.\n");
    add_cmd_item( ({"toy", "with toy", "toys", "with toys"}), "play",
        "You take a minute and play with the toys. How fun it is to relive "
        + "your childhood!\n");
    
    add_cmd_item( "on bed", "sit", "You consider sitting on the bed, but then "
        + "realize you're too heavy for it.\n");
    add_cmd_item( "pillow", "fluff", "You fluff the pillow, making it even "
        + "more fluffy.\n");

} //add_bedroom_child

/* 
 * Function:    add_bedroom_master
 * bed_type:     "poster, "large", or "princess"
 * flooring:    "stone", "wood", or "tile"
 *
 * This function allows you to build a master bedroom quickly.
 */
 
void
add_bedroom_master(string bed_type, string flooring)
{
    if(bed_type == "poster")
    {
        add_item( ({"bed", "poster bed", "four poster bed"}),
            "This is a four-poster bed. Thick oak posts rise from the "
            + "floor to the ceiling. They're merely decorative, but they "
            + "do look nice.\n");
        add_item( ({"post", "posts"}), "The posts have been hand carved "
            + "scenes of daily life in the Shire: a woman baking bread, "
            + "a man smoking his pipe, children at play, trees swaying "
            + "gently in the wind. These are very well-done carvings.\n");
        add_item( ({"carving", "carvings"}), "The carvings are all "
            + "over the bed posts!\n");
        add_cmd_item( ({"bed post", "bed posts", "on bed post", "on bed posts"}),
            "carve", "You're joking, right?\n");
    }
    if(bed_type == "large")
    {
        add_item( "bed", "This is one of the largest beds you've ever "
            + "seen in a hobbit hole! It's nearly big enough for a human "
            + "to sleep in. The bed itself is covered with a mound of "
            + "blankets and pillows. It must be a warm place to sleep.\n");
        add_item( ({"mound"}), "This mound of blankets must be half a "
            + "meter thick!\n");
    }
    if(bed_type == "princess")
    {
        add_item( "bed", "This looks like a bed made for a princess. "
            + "Sheer drapes cascade down from the ceiling making it look "
            + "exotic and tantalizing.\n");
        add_item( ({"drape", "drapes"}), "The drapes cascade down "
            + "from the ceiling and would obscure the whole bed if they "
            + "weren't almost see-through. You could likely see your hand "
            + "through the curtain if you placed it behind one.\n");
        add_cmd_item( ({"hand behind drape", "hand behind drapes"}),
            "place", "You place your hand behind the curtain. You can still "
            + "see the shape of your hand, but not the details.\n");
    }
        add_item( ({"blanket", "blankets", "cover", "covers"}), 
            "The blankets are soft and warm, perfect for a cold winter's "
            + "night.\n");
        add_item( ({"pillow", "pillows"}), "The pillows look soft and "
            + "comfortable.\n");
        add_cmd_item( "on bed", "sleep", "It's not your bed. How rude!\n");
        add_cmd_item( ({"pillow", "pillows"}), "fluff", "You fluff the "
            + "pillows, making them even more comfortable. Nice!\n");
            
    if(flooring == "stone")
    {
        remove_item("floor");
        add_item("floor", 
            "The floor is constructed out of river stones, but they have "
            + "mortared in place until they provide a nearly smooth surface.\n");
        add_cmd_item("floor", "touch", "The floor feels cold and smooth.\n");
    }
    if(flooring == "wood")
    {
        remove_item("floor");
        add_item("floor", "The floor is made of cherry wood boards. They have "
            + "been dovetailed together so that they create a smooth surface.\n");
        add_item( ({"board", "boards"}), "The boards are made of cherry wood. "
            + "While they are hard, they have more give to them than stone, "
            + "making hard wood like this much more comfortable to walk on. "
            + "They have a deep rich color.\n");
    }
    if(flooring == "tile")
    {
        remove_item("floor");
        add_item("floor", "Instead of using river rock, this floor is made of "
            + "cut stone tiles. Different stones have been used in a repeating "
            + "pattern, so the floor looks very colorful.\n");
        add_item( ({"stone", "stones", "different stones"}), "There are many "
            + "kinds of stone in use on the floor. You think you see some "
            + "granite, marble, quartz--and many of them have been taken from "
            + "different quarries. You can tell because the coloration "
            + "changes even when the type of stone remains the same.\n");
    }
        add_item("closet", "A closet is recessed in the wall, looking like "
            + "the perfect place to hang clothes and store shoes. The door "
            + "is closed.\n");
        add_cmd_item("door", "open", "The door is shut tight and you cannot "
            + "open it!\n");
        add_cmd_item("lock on door", "pick", "The door isn't locked!\n");


}//add_bedroom_master

    
/*
 * Function:     add_bedroom_poor
 * bed:            An adjective to describe the bed.
 * This function should give the add_items for a low-income bedroom.
 */
 
void
add_bedroom_poor(string bed)
{
    add_item( ({ "bed", bed + " bed"}), "The " + bed + " bed takes up most "
        + "of this tiny room. While it's quite obviously supposed to be a "
        + "bedroom, a wealthier family would use this room as a closet. "
        + "The bed itself looks like a cloth sack stuffed with hay or maybe "
        + "feathers. It's lumpy and you're not quite sure it would feel "
        + "soft. There are a few covers on top of it, although not quite "
        + "enough to feel completely warm.\n");
    add_item( ({"covers", "blankets", "cover", "blanket"}), "The covers "
        + "are on the bed. It is made neatly and with care. But the "
        + "covers feel thin. Very, very thin.\n");
    add_item( ({"sack", "cloth sack", "matress"}), "The matress is basically "
        + "a large, off-white cloth sack filled with feathers or hay or "
        + "something. You notice some stains on it.\n");
    add_item( ({"stain", "stains"}), "The stains are yellow... eeeeeew.\n");
    
    add_item( ({"shelf", "shelves", "closet", "chest of drawers", "drawer", "drawers"}),
        "It contains a few items of clothing, but they seem old and nearly "
        + "worn out.\n");
    add_item( ({"clothes", "clothing", "items of clothing"}), "The clothing "
        + "is hobbit-sized. It seems quite old and like it's been worn "
        + "for a long time.\n");
    
    add_item( ({"table", "nightstand", "night stand"}), "A small table, "
        + "which some would call a nightstand, sits next to the bed. It is "
        + "clean, but otherwise looks worn. There is a lamp on top of it.\n");
        
    add_item( "lamp", "The lamp sits on top of the nightstand. Unfortunately, "
        + "it is out of oil.\n");
    add_item("oil", "There is some oil on the nightstand. It looks like "
        + "the lamp leaks.\n");
        
    add_cmd_item( ({"bed", bed + " bed", "matress"}), 
        ({"touch", "feel", "fondle", "rub"}),
        "The bed is, in fact, lumpy. Your best guess is that the matress is "
        + "filled with hay, but you might need to smell it to be sure.\n");
    add_cmd_item( ({"bed", bed + " bed", "matress"}), "smell", "Yes, the "
        + "matress is filled with hay. It smells like a barn.\n");
    add_cmd_item( "warm", "feel", "You're not sure you could feel warm with "
        + "covers this thin!\n");
    add_cmd_item( "lamp", "light", "You try to light the lamp but fail. It "
        + "seems to be out of oil.\n");
    add_cmd_item( "lamp with oil", "fill", "You try to fill the lamp with "
        + "oil, but notice the oil leaking out onto the nightstand. The "
        + "lamp is too damaged to hold any more oil!\n");
        
} //add_bedroom_poor

//Walls, celing, floor add_items
void
add_walls()
{
    add_item( ({"wall", "walls", "west wall",}), 
        "The walls clean and welcoming. They "
        + "are covered with wood paneling.\n");
    add_item( ({"panel", "wood panel", "wood paneling", "paneling"}),
        "The wood panels are fitted together nicely and stained a deep, rich "
        + "brown.\n");
    add_item( "ceiling", "The ceiling is gently rounded to distribute the "
        + "weight of the ground above.\n");
    add_item( "floor", "The floor is spotless. Whoever lives here takes the "
        + "time to clean!\n");
        
    add_cmd_item( "floor", "clean", "There is no need to clean the floor. "
        + "It's spotless!\n");
    
} //add_walls

//adds a stove for the kitchen
void
add_stove(string stove_adj)
{
    add_item( ({"stove", "stoves", stove_adj + " stove", stove_adj + " stoves"}),
        "This " + stove_adj + " stove looks like the metaphorical center of "
        + "the home. It is made of cast-iron and is shaped a bit like a vase, "
        + "with a bulbous bottom and flat top. There is a stove-door on the "
        + "front "
        + "of the stove where you could add wood or coal. The heat from below "
        + "warms the flat surface on top, making a cooking surface. "
        + "Warmth radiates from it. A pot sits atop the stove.\n");
    add_item("stove door", "The stove door is big enough to insert a log or "
        + "shovel full of coal so that the fire can stay lit.\n");
    add_item( ({"bottom", "bulbous bottom"}), "The bottom of the stove looks a "
        + "bit like the bottom of the vase, having a bulbous shape and four "
        + "small legs to steady it on the floor. The " + stove_adj
        + "stove has a flat top for cooking, and a stove pipe extending "
        + "from the "
        + "back to the chimney.\n");
    add_item( ({"top", "flat top", "stove top"}), "This top is nothing more "
        + "than a flat piece of iron. You could cook directly on top  of it "
        + "or place a pot on it. It is very hot.\n");
    add_item( ({"leg", "legs", "small legs", "small leg"}), "The legs are "
        + "about a human hand long. They steady the stove and help it "
        + "remain upright.\n");
    add_item( ({"pipe", "stove pipe"}), "The stove pipe extends from the back "
        + "of the stove to the chimney. This way, smoke can exit the "
        + "home.\n");
    add_item( "chimney", "The chimney lets the smoke out of the home.\n");
    add_item("smoke", "The smoke is outside, thanks to the chimney.\n");
    add_item("pot", "This is a large black cast-iron pot. It has a lid "
        + "on it, but you can still smell dinner cooking from inside.\n");
    add_item("lid", "The lid sits on top of the pot. It is too hot to "
        + "to remove with your bare hands!\n");
        
    add_cmd_item("stove door", "open", "The handle is too hot! You'd "
        + "burn yourself!\n");
    add_cmd_item( ({"top", "flat top", "stove top"}), "touch", "You wouldn't "
        + "dare! You'd burn yourself!\n");
    add_cmd_item( ({"pot", "dinner"}), "smell", "Ooooooh, that's the stuff! This meal "
        + "will taste amazing.\n");
    
    add_cmd_item( "heat", "feel", "You extend your hand forward and notice "
        + "the heat radiating from the stove. The kitchen is warm and cozy.\n");
    add_cmd_item("lid", ({"remove", "lift", "open"}), "It's too hot!\n");
    
    add_room_tell("The fire in the stove crackles.");
    add_room_tell("Orange light flickers from the gap between the stove "
        + "door and the stove.");
    add_room_tell("You can smell dinner cooking on the stove.");
    add_room_tell("The pot lid rattles as dinner boils beneath it.");
}//add_stove

//Clouds for window room tell
string
window_clouds()
{
    if(CLOCK->query_night())
    {
        return("Clouds drift in front of the moon, dimming the light "
            + "momentarily.");
    }
    else
    {
        return("Clouds drift in front of the sun, casting shadows across "
            + "the room.");
    }
}
// Wolves or children for the room tell
string
wolf_child()
{
    if(CLOCK->query_night())
    {
        return("Wolves howl in the distance, causing the little hairs on "
            + "the back of your neck to rise a little.");
    }
    else
    {
        return("You hear children laughing and playing outside the window.");
    }
}

void
add_window(string curtain)
{
    set_room_tell_time(45);
    
    add_cmd_item( ({"window", "windows"}), "open", "It's not your house. "
        + "You don't feel right opening the window like that!\n");
    add_cmd_item( ({"curtain", "curtains"}), "close", "It's not your "
        + "house. You don't feel right closing the curtains like that!\n");
    add_cmd_item( ({"curtain", "curtains", "close curtain", "close curtains"}),
        "draw", "It's not your house. You don't feel right closing the "
        + "curtains like that.\n");
    add_cmd_item( ({"window", "windows"}), "close", "The window "
        + "is already closed.\n");
    add_cmd_item( ({"curtain", "curtains"}), "open", "The curtains are "
        + "already open.\n");
    
    add_item( ({"window", "windows"}), "The window looks a bit like a "
        + "porthole on a ship. It's round and about the size of a couple "
        + "trolls' heads. There are " + curtain + " curtains tied off to "
        + "the side of the window.\n");
    add_item( ({"frame", "window frame", "windowframe"}), "The frame is "
        + "made of wood and has been painted to match the curtains!\n");
    add_item( ({"curtain", "curtains"}), "The " + curtain + " curtains "
        + "are open now, but could be drawn closed to provide a little "
        + "more privacy.\n");
    
    add_room_tell("You hear birds chirping outside the window.");
    add_room_tell("The wind blows outside, rattling the window.");
    add_room_tell(window_clouds());
    add_room_tell(wolf_child());

}//add window

/* Function:     add_window_two
 * window:        A string depicting the window size or shape.
 * wall:        A string telling which wall the window is on (north, south, etc)
 *
 */
void
add_window_two(string window, string wall)
{
    add_item( ({"window", "windows"}), "Along the " + wall 
        + " wall, you notice a " + window + " window. Because of "
        + "its size, you can't see much out of it, but at least "
        + "it lets in some light.\n");
    add_item( ({"window sill", "sill"}), "The window sill has been "
        + "painted white, but the paint is peeling a little and "
        + "looks scuffed. Still, there's no dust on it.\n");
    add_item( ({wall + "wall"}), "This wall looks much like the others, "
        + "except that you see a " + window + " window on it.\n");
}
