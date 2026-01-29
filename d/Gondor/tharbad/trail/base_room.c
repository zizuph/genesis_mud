/*
 * Base room for Corsairs at Tharbad
 *
 * Raymundo, June 2020
 */
 
inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/herbsearch.c";
inherit "/d/Shire/std/room/room_tell";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include <language.h>
#include <tasks.h>
#include <composite.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/clock.h"
#include "/d/Gondor/common/lib/herb_list.h"
 
 void
 add_landscape()
 {
     add_item( ({"tree", "trees"}), "The trees are short and stunted, "
        + "looking almost more like a bush than a tree, but their "
        + "leaves are still green and they provide welcome shade from "
        + "the sun, as well as some protection from prying eyes.\n");
    add_item( ({"leaf", "leaves"}), "The leaves are green and healthy. "
        + "The trees seem to be getting plenty of water from the river.\n");
    add_item( ({"river"}), "To the east is a river, swift and fast and "
        + "large enough to pilot a boat on.\n");
    add_item( ({"clearing"}), "This is a clearing, where someone or "
        + "another hacked down all the trees to make space for an "
        + "encampment.\n");
    add_item( ({"encampment", "camp"}), "The corsairs have made their home "
        + "here, securely hidden in the trees, yet still close enough to "
        + "the river for some piracy.\n");
    add_item( ({"piracy", "pirate"}), "Avast me harties! Drink yer rum! "
        + "I'll be sendin' ye t' the deep!... You know. Pirates.\n");
    add_item( ({"ground", "dirt", "grass", "stumps"}), "The ground is "
        + "mostly dirt, with a little grass here and there. There are "
        + "treestumps leftover, evidence that this is not a natural "
        + "clearing, but they have been cut more-or-less even with the "
        + "ground, so as to make this an almost comfortable place to "
        + "walk or sleep.\n");
    add_item( ({"edge", "edges"}), "The edges of the clearing are still "
        + "wooded, all the better to try to "
        + "keep prying eyes from observing "
        + "what happens in the area.\n");
    add_item( ({"eye", "prying eye", "eyes", "prying eyes"}),
        "Prying eyes\n"
        + "They're watching you\n"
        + "They see your every move\n"
        + "Prying eyes\n"
        + "They're watching you\n"
        + "Do what pirates do\n");
    add_item("shade", "@@exa_shade@@");
    add_item( ({"sky"}), "@@exa_sky@@");
    add_item( ({"bush", "bushes"}), "The trees are short, almost the size "
        + "of bushes.\n");
    
    set_room_tell_time(90);
    
    add_room_tell("The river gurgles to the east.");
    add_room_tell("Hushed voices discuss whom to rob next.");
    add_room_tell("Birds chirp from the trees on the edge of the clearing.");
    add_room_tell("Clouds drift across the sky");
    add_room_tell("You hear a creaking indicative of someone walking in "
        + "leather armour.");
    add_room_tell("Frogs ribbit from the direction of the river.");
    add_room_tell("Flies buzz around your head.");
    add_room_tell("Aaaaargh! A mosquito bit you, and now your arm itches.");
    add_room_tell("Everything goes eerily silent.");
    add_room_tell("@@sun_tell@@");
    
 }
 
 string
 exa_sky()
 {
    object  clock = find_object(CLOCK);
    if(clock->query_time_of_day() == "night")
    {
        return("Between the clouds, stars appear. Bright pinpoints of "
            + "light, sparkling against the night sky.\n");
    }
    else
        return("The sun is punishingly bright, making you squint. Its "
    + "heat makes you sweat. Some shade would be nice right about now, "
    + "but all the trees that were here have been cut down to form "
    + "the clearing, leaving the only shade available at the edges of "
    + "the area.\n");
 }
 
 string
 exa_shade()
 {
     object  clock = find_object(CLOCK);
    if(clock->query_time_of_day() == "night")
    {
        return("The sun has set, making the whole clearing feel shaded.\n");
    }
    else
        return("Sunlight pounds down from above. The only shade here comes "
            + "in thin slivers against the trees at the edges of the "
            + "clearing.\n");
 }
 
 string
 sun_tell()
 {
     object  clock = find_object(CLOCK);
    if(clock->query_time_of_day() == "night")
    {
        return("The moon shines down, illuminating the clearing.");
    }
    else
        return("The sun beats down on you, making you wish for shade.");
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

void
add_trash()
{
        add_item( 
        ({"sign", "signs", "activity", "human", "humans", "human activity"}),
        "There are footprints and trash everywhere, as humans so often leave "
        + "when they venture into nature.\n");
    add_item("trash", "The trash is mostly scraps of food and broken bottles "
        + "of rum and wine.\n");
    add_item( ({"bottle", "bottles", "rum", "wine"}),
        "All the bottles are broken. Someone had a good time--a really good "
        + "time--here recently.\n");
    add_item( ({"scraps", "scrap", "food"}), "The scraps are things like "
        + "fish bones, vegetable peels, crusts of bread, and--could it be?--"
        + "bones from frog legs.\n");
}