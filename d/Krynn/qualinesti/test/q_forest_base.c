/*   forest_base.c 
 *   Forest base file for Qualinesti.
 *
 *   Blizzard, 01/2003
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <composite.h>
#include <macros.h>
#include "/d/Krynn/common/clock/clock.h"
#include <tasks.h>
#include "../local.h"


inherit OUT;
inherit HERBSEARCHNEW

string  *herbs = HERB_MASTER->query_herbs(({"mixedforest" }));

/* Some fruits, the player can reach only the limited, random number of them */
int     apple_num  = 5 + random(3); // We choose number of fruits on
int     pear_num   = 3 + random(3); // each tree
int     peach_num  = 3 + random(3);
int     pear_tree  = random(2); // We decide if there is this type
int     peach_tree = random(2); // of tree in this location.
int     apple_tree = random(3); 
int     cones      = 5 + random(6);

object  apple, pear, peach;
int     pick_fruit(string str);
int     climb_tree(string arg);
int     skill_check(object who);
int     gather_cones(string what);
int     breathe(string arg);

string  pear_descr();
string  peach_descr();
string  apple_descr();
string  look_around();

public void
reset_qualinesti_room()
{
    if ( pear_num < 3 )
        pear_num = 3 + random(3);
    
    if ( peach_num < 3 )
        peach_num = 3 + random(3);
    
    if ( apple_num < 5 )
        apple_num = 5 + random(3);
    
    if ( cones < 5 )
        cones = 5 + random(6);
        
    set_searched(random(2));
   
}

public void
create_forest()
{

}

nomask void
create_qualinesti_room()
{
    set_place(FOREST);
    set_long_desc("You travel through the mysterious forest of Qualinesti. " +
        "No matter if you are at the edge of it or in the middle, you are " +
        "sure it is the same everywhere - watched and " +
        "protected. You have never expected you will find yourself so close " +
        "to the elven kingdom. Growing bushes and fallen branches are " +
        "creating a very thick mass and you keep finding imaginary paths, " +
        "which disappear after a few minutes. When you think you have found " +
        "another one it also disappears, luring you out of your right " +
        "direction. Then you realize that none of them were paths at all.");

    add_item(({"forest", "woods"}),
        "The forest seems to be healty, thriving of different types of " +
        "trees. You have a " +
        "feeling these woods are alive and keep observing you, even if the " +
        "most of them stand silent and barely move, when the wind blows.\n");
    add_item(({"trees", "ash trees", "vallenwood trees", "apple trees" +
        "peach trees", "pear trees", "pines", "oaks" }),
        "There are many types of trees growing around. You can see oaks, " +
        "pines, ash, vallenwood, apple, peach and pear trees. Most of them " +
        "stand tall and silent, because single blows of wind hardly manage " +
        "to move them.\n");
    add_item(({ "tree", "ash tree", "vallenwood tree", "oak" }),
        "This forest is full of trees of many types. The one you are " +
        "looking at, is just a part of the healthy and thriving system.\n");
    add_item("pine",
        "This is one of many pines, that grow in this forest. It has thin " +
        "sharp needles, that keep this tree evergreen. Here and there you " +
        "you notice a brown pine cones.\n");
    add_item("peach tree", &peach_descr());
    add_item("pear tree", &pear_descr());
    add_item("apple tree", &apple_descr());
    
    add_item(({ "pine cones", "pine cone" }),
        "You see brown pine cones on the trees, but there are some " +
        "laying on the ground too, almost invisible in the mass of branches " +
        "and leaves.\n");
    add_item(({"leaves", "leaf"}),
        "Leaves? Just look around! This is a forest full of green trees!\n");
    add_item(({"bushes", "bush", "mass"}),
        "Together with fallen branches, bushes create a really thick mass. " +
        "You start to doubt if you are able to find your way through the " +
        "forest.\n");
    add_item(({"branch", "branches"}),
        "There are many fallen branches on the ground. Some of them seem " +
        "to be laying here for a very long time.\n");
    add_item("path",
        "Are you sure there is any path leading through this forest?\n");
    add_item(({"herb growth", "growth"}),
        "There may be useful herbs if you search here.\n");
        
    set_tell_time(250);
    add_tell("The forest has a near mystical air about it.\n");
    add_tell("The forest is so silent that you have a sense of being " +
        "watched.\n");
    add_tell("You hear a long, deep growl in the distance.\n");
    add_tell("You think you have just seen something among the trees.\n\n" +
        "No, that was only your imagination.\n");
    add_tell("A small gust of wind strikes the area, but the forest " +
        "doesnt seem to feel that.\n");
    add_tell("You heard a sound of snapped branch.\n\nLuckily, that was only " +
    	"some wild animal running through the forest.\n");
    add_tell("The leaves above your head rustled silently in a breeze.\n");    

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_HIDE, 5);
         
    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({ "growth", "herb growth", }), 3);
               
    create_forest();
    reset_qualinesti_room();
    set_noshow_obvious(1);

}

/* Function name : unq_no_move
 * Description   : We give extra information if the player tries to go
 *                 in no existing direction
 * Arguments     : string str = the command line argument
 * Returns       : int 0      -always
 */
public int
unq_no_move(string str)
{
    switch ( query_verb() )
    {
    case "south":
    case "north":
    case "west":
    case "east":
    case "southwest":
    case "southeast":
    case "northwest":
    case "northeast":
        notify_fail("You force your way through the bushes in " + 
            query_verb() + " direction. However, after some time you " +
            "find your own tracks and you realize you have been walking " +
            "around in circles.\n");
        return 0;
    break;
    default:
        notify_fail("There is no obvious exit " + query_verb() + ".\n");
        return 0;
    break;
    }
}

/* Function   : skill_check
 * Description: This function checks if the player is skilled enough
 *              to find the path through the forest;
 * Arguments  : the checked person
 * Returns    : 1 - skilled enough
 *              0 - not enough skilled
 */ 
int 
skill_check(object who)
{
    int skill;
    
    skill = who->query_skill(SS_TRACKING) + who->query_skill(SS_LOC_SENSE);

 /* Sometimes it's easier to find a path, sometimes it is not. */    

    if (skill > (50 + random(10)))
    {
        return 1;
    }
    
    return 0;

}

void
init()
{
    ::init();
    add_action(pick_fruit, "pick");
    add_action(climb_tree, "climb");
    add_action(gather_cones, "gather");
    add_action(breathe, "breathe");
    add_action(breathe, "inhale");
}

int
breathe(string arg)
{
    if ( !stringp(arg) || arg == "air" || arg == "the air" || arg == "in" )
    {
        switch ( TP->query_race_name() )
        {
        case "goblin":
            write("You smell the air and almost puke as the fresh scent " +
                "of the forest fills your nostrils.\n");
            tell_room(TO, QCTNAME(TP) + " almost pukes as the scent of " +
                "trees fills " + POSSESSIVE(TP) + " nostrils.\n", TP);
        break;
        case "kender":
            write("You inhale deeply. The scent of this forest reminds you " +
                "of woods surrounding Kendermore. You sigh dreamingly.\n");
            tell_room(TO, QCTNAME(TP) + " inhales and sighs dreamingly.\n", TP);
        break;
        default:
            write("You inhale deeply, enjoying the fresh scent of the " +
                "forest.\n");
            tell_room(TO, QCTNAME(TP) + " inhales deeply, enjoying the fresh " +
                "scent of the forest.\n", TP);
        break;
        } 
    
        return 1;
    }
    else
    {
        notify_fail("Breathe in?\n");
        return 0;
    }    
}  
  
/* Function name   : apple_descr
 * Description     : Returns description of the apple tree, depending on
 *                   the distance to the tree and number of fruits.
 */
string
apple_descr()
{
    if ( apple_tree )
    {
        if ( (apple_num > 0) && GET_SEASON != WINTER && GET_SEASON != SPRING )
        {    
            return "Apples! There are apples on it. Wild apple trees are not " +
                "so common in forestes, but you are not surprised by " +
                "seeing them in this one!\n";
        }
        else
            return "Wild apple trees are not so common in forestes, but " +
                "you are not surprised by seeing them in this one. " +
                "Unfortunately, there are no apples on it.\n";
    }    
    else
    {
        return "You think you see an apple tree among other trees. " +
            "Unfortunately, because of thick bushes you cannot get closer " +
            "to it.\n";
    }
}

/* Function name   : pear_descr
 * Description     : Returns description of the pear tree, depending on
 *                   the distance to the tree and number of fruits.
 */
string
pear_descr()
{
    if ( pear_tree )
    {
        if ( (pear_num > 0) && GET_SEASON != WINTER && GET_SEASON != SPRING )
        {
            return "A single pear tree stands here. There are some fruits " +
                "on it.\n";
        }
        else
            return "A single pear tree stands here. There are no fruits " +
                 "on it.\n";
    }
    else
    {
        return "You are sure there is a pear tree standing among other " +
            "trees. You would like to make sure and check if you can " +
            "find some fruits, but the thick bushes stop you.\n";
    }
}   
        
/* Function name   : peach_descr
 * Description     : Returns description of the peach tree, depending on
 *                   the distance to the tree and number of fruits.
 */
string
peach_descr()
{
    if ( peach_tree )
    {
        if ( (peach_num > 0) && GET_SEASON != WINTER && GET_SEASON != SPRING )
        {
            return "You are not surprised by seeing this tree here. You are " +
                "just sad it is not so common. You see a few orange-red " +
                "fruits on it.\n";
        }
        else
            return "You are not surprised by seeing this tree here. You wish " +
                "there were some fruits on it.\n";
    }
    else
    {
        return "A lone peach tree stands not so far from you. It seems " +
            "it is impossible to get closer to it thou.\n";
    }
}

/* Funcion name : pick_fruit
 * Description  : Picking fruits from the trees.
 */
int 
pick_fruit(string str)
{
    object *dwarfs, *liv;
    object dwarf;
    int i, sz;
    
    liv = FILTER_LIVE(TO->subinventory());

    for ( i = 0, sz = sizeof(liv); i < sz; i++)
    {
        if ( liv[i]->query_race_name() == "dwarf" )
             dwarf = liv[i];
    }
/*
    if ( sizeof(liv) )
    {
        dwarf = liv[random(sizeof(liv))];
    }    
 */ 
    if ( str == "cones" || str == "cone" || str == "pine cones" ||
        str == "pine cone" )
    {
        if ( cones > 0 )
        {
            gather_cones("pine cones");
            return 1;
        }
        else if ( cones <= 0 )
        {
            write("You can not find any pine cones here.\n");
            return 1;
        }
    }
      
    if ( GET_SEASON == WINTER )
    {
        notify_fail("You can not see any fruits on the trees. Well, it's " +
            "winter.\n");
        return 0;
    }
    
    if ( GET_SEASON == SPRING )
    {
        notify_fail("The forest has just awaken from its wintertime " +
            "slumber and there are no fruits on the trees yet.\n");
        return 0;
    }
    
    switch (str)
    {
        case "apple":
        case "apples":
        case "apple fruit":
            if ( apple_tree && (apple_num > 0) )
            {
                if ( random(2) )
                {
                    if ( TP->query_race_name() == "dwarf" )
                    {
                        notify_fail("You peer at the big apple hanging high " +
                            "above your head. You hop slightly trying " +
                            "to pick it, but you are too small to reach " +
                            "it.\n" +
                            "You grumble unhappily.\n");
                        
                        tell_room(TO, QCTNAME(TP) + " hops slightly " +
                            "trying to pick a big apple hanging high " +
                            "high above " + POSSESSIVE(TP) + " head, but " +
                            PRONOUN(TP) + " is too small to reach it.\n" +
                            QCTNAME(TP) + " grumbles unhappily.\n", TP);
                                             
                        return 0;
                    }
                    else if ( TP->query_race_name() == "kender" )
                    {
                        if ( random(2) )
                        {
                            write("You hop as high as you can, trying to " +
                                "catch one of the apples, but you are too " +
                                "small to reach it. " + 
                                "You think for a moment and then giggling " +
                                "merrily you pick one of pine cones, and " +
                                "throw it, aiming at the apple above.\n\n" +
                                "You hit it! The apple falls directly in " +
                                "in your hands. You skip happily around.\n");
                            tell_room(TO, QCTNAME(TP) + " hops as high as " +
                                PRONOUN(TP) + " can, trying to catch one of " +
                                "the apples, but " + PRONOUN(TP) + " is too " +
                                "small. " +
                                QCTNAME(TP) + " picks one of pine cones and " +
                                "throws it, aiming at the apple above. As " +
                                "the fruit is hit, it falls directly into " +
                                POSSESSIVE(TP) + " hands.\n" + QCTNAME(TP) + 
                                " skips happily around.\n", TP);
                        }
                        else
                        {
                            write("You hop as high as you can, trying to " +
                                "catch on of the apples, but you are too " +
                                "small to reach it. ");
                            tell_room(TO, QCTNAME(TP) + " hops as high as " +
                                PRONOUN(TP) + " can, trying to catch one of " +
                                "the apples, but " + PRONOUN(TP) + " is too " +
                                "small. ", TP);
                            
                            if (  dwarf )
                            {
                                write("You think for a moment, then a " +
                                    "brilliant idea comes to your mind.\n" +
                                    "You quickly climb " + 
                                    COMPOSITE_LIVE(dwarf) +
                                    "'s back and jump high, picking " +
                                    "an apple. As you deftly " +
                                    "land on the ground, you run trying to " +
                                    "avoid " + COMPOSITE_LIVE(dwarf) + 
                                    ", who obviously is not happy!\n");
                                dwarf->catch_msg(capitalize(PRONOUN(TP)) +
                                    " seems to " +
                                    "be thinking for a moment. Suddenly, " +
                                    "before you are able to react, " +
                                    PRONOUN(TP) + " climbs your back and " +
                                    "jumps trying to catch an apple.\n" +
                                    "You roar madly. This is too much!\n");
                                tell_room(TO, QCTNAME(TP) + " seems to be " +
                                    "thinking for a moment. Then, " +
                                    "quickly climbing " + 
                                    COMPOSITE_LIVE(dwarf) + 
                                    "'s back, he jumps high, " +
                                    "trying to catch an apple. As " +
                                    QTNAME(TP) + " picks the fruit and " +
                                    "lands deftly on the ground, " +
                                    PRONOUN(TP) + " runs trying to avoid " +
                                    COMPOSITE_LIVE(dwarf) + 
                                    ", who obviously is not happy!\n", 
                                    ({ dwarf, TP }) );
                             
                            }
                            else if ( !present("dwarf", TO) )
                            {
                                notify_fail("You think for a moment, then a " +
                                    "brilliant idea comes to your mind.\n" +
                                    "You sigh, as you realize there is a " +
                                    "hole in your plan. There is no dwarf " +
                                    "here!\n");
                                tell_room(TO, QCTNAME(TP) + " seems to be " +
                                    "thinking for a moment. Then " +
                                    PRONOUN(TP) + " sighs. You wonder what " +
                                    "evil idea appeared in his mind.\n", TP);
                                return 0;
                            }        
                            
                        }
                    
                    }
                    else if ( TP->query_race_name() == "goblin" )
                    {
                        write("You peer at the apple hanging high above " +
                            "your head. You jump, but can not reach it. " +
                            "You consider chopping the tree down.\n");
                        tell_room(TO, QCTNAME(TP) + " peers at apples " +
                            "hanging high above " + POSSESSIVE(TP) + " head. " +
                            capitalize(PRONOUN(TP)) + " jumps, but can not " +
                            "reach them. It seems " + PRONOUN(TP) + " is " +
                            "now considering chopping the tree down.\n", TP);
                    }
                    else
                    {
                        write("You jump as high as you can and pick one of " +
                            "the red apples.\n");
                        tell_room(TO, QCTNAME(TP) + " jumps as high as " +
                            PRONOUN(TP) + " can " +
                            "and picks one the red apples.\n", TP);
                    }
                }
                else
                {
                    write("You reach for a red apple hanging on one of " +
                        "the lower branches.\n");
                    tell_room(TO, QCTNAME(TP) + " reaches for a red apple " +
                        "hanging on one of the lower branches.\n", TP);
                }
                
                apple = clone_object(OBJ + "apple");
                apple->move(TP, 1);
                apple_num--;

                return 1;
            }
            else if ( apple_tree && (apple_num <= 0) )
            {
                tell_room(TO, QCTNAME(TP) + " looks at the apple tree, " +
                    "as " + PRONOUN(TP) + " was searching for " +
                    "something.\n", TP);
                notify_fail("There is no more apples that you could reach.\n");
                return 0;
            }
            else
            {
                notify_fail("How do you want to do that? The tree is a bit " +
                "too far.\n");
                return 0;
            }
        break;
        case "pear":
        case "pears":
        case "peach fruit":
            if ( pear_tree && (pear_num > 0) )
            {
                if ( random(2) )
                {
                    if ( TP->query_race_name() == "dwarf" )
                    {
                        notify_fail("You peer at the fruits hanging high " +
                            "above your head. You hop slightly trying " +
                            "to pick one of them, but you are too small " +
                            "to reach it.\n" +
                            "You grumble unhappily.\n");
                        
                        tell_room(TO, QCTNAME(TP) + " hops slightly " +
                            "trying to pick a yellow fruit hanging high " +
                            "high above " + POSSESSIVE(TP) + " head, but " +
                            PRONOUN(TP) + " is too small to reach it.\n" +
                            QCTNAME(TP) + " grumbles unhappily.\n", TP);
                                             
                        return 0;
                    }
                    else if ( TP->query_race_name() == "kender" )
                    {
                        if ( random(2) )
                        {
                            write("You hop as high as you can, trying to " +
                                "catch one of the yellow fruits, but you " +
                                "are too small to reach it. " + 
                                "You think for a moment and then giggling " +
                                "merrily you pick one of pine cones, and " +
                                "throw it, aiming at the pear above.\n\n" +
                                "You hit it! The fruit falls directly in " +
                                "in your hands. You skip happily around.\n");
                            tell_room(TO, QCTNAME(TP) + " hops as high as " +
                                PRONOUN(TP) + " can, trying to catch one of " +
                                "the yellow fruits, but " + PRONOUN(TP) + 
                                " is too small. " +
                                QCTNAME(TP) + " picks one of pine cones and " +
                                "throws it, aiming at the pear above. As " +
                                "the fruit is hit, it falls directly into " +
                                POSSESSIVE(TP) + " hands.\n" + QCTNAME(TP) + 
                                " skips happily around.\n", TP);
                        }
                        else
                        {
                            write("You hop as high as you can, trying to " +
                                "catch on of the pears, but you are too " +
                                "small to reach it. ");
                            tell_room(TO, QCTNAME(TP) + " hops as high as " +
                                PRONOUN(TP) + " can, trying to catch one of " +
                                "the pears, but " + PRONOUN(TP) + " is too " +
                                "small. ", TP);
                            
                            if (  dwarf )
                            {
                                write("You think for a moment, then a " +
                                    "brilliant idea comes to your mind.\n" +
                                    "You quickly climb " + 
                                    COMPOSITE_LIVE(dwarf) +
                                    "'s back and jump high, picking " +
                                    "a yellow fruit. As you deftly " +
                                    "land on the ground, you run trying to " +
                                    "avoid " + COMPOSITE_LIVE(dwarf) + 
                                    ", who obviously is not happy!\n");
                                dwarf->catch_msg(capitalize(PRONOUN(TP)) +
                                    " seems to " +
                                    "be thinking for a moment. Suddenly, " +
                                    "before you are able to react, " +
                                    PRONOUN(TP) + " climbs your back and " +
                                    "jumps trying to pick a pear.\n" +
                                    "You roar madly. This is too much!\n");
                                tell_room(TO, QCTNAME(TP) + " seems to be " +
                                    "thinking for a moment. Then, " +
                                    "quickly climbing " + 
                                    COMPOSITE_LIVE(dwarf) + 
                                    "'s back, he jumps high, " +
                                    "catching a yellow pear. As " +
                                    QTNAME(TP) + " picks the fruit and " +
                                    "lands deftly on the ground, " +
                                    PRONOUN(TP) + " runs trying to avoid " +
                                    COMPOSITE_LIVE(dwarf) + 
                                    ", who obviously is not happy!\n", 
                                    ({ dwarf, TP }) );
                             
                            }
                            else if ( !present("dwarf", TO) )
                            {
                                notify_fail("You think for a moment, then a " +
                                    "brilliant idea comes to your mind.\n" +
                                    "You sigh, as you realize there is a " +
                                    "hole in your plan. There is no dwarf " +
                                    "here!\n");
                                tell_room(TO, QCTNAME(TP) + " seems to be " +
                                    "thinking for a moment. Then " +
                                    PRONOUN(TP) + " sighs. You wonder what " +
                                    "evil idea appeared in his mind.\n", TP);
                                return 0;
                            }        
                            
                        }
                    
                    }
                    else if ( TP->query_race_name() == "goblin" )
                    {
                        write("You peer at the pear hanging high above " +
                            "your head. You jump, but can not reach it. " +
                            "You consider chopping the tree down.\n");
                        tell_room(TO, QCTNAME(TP) + " peers at pears " +
                            "hanging high above " + POSSESSIVE(TP) + " head. " +
                            capitalize(PRONOUN(TP)) + " jumps, but can not " +
                            "reach them. It seems " + PRONOUN(TP) + " is " +
                            "now considering chopping the tree down.\n", TP);
                    }
                    else
                    {
                        write("You jump as high as you can and pick one of " +
                            "the yellow fruits.\n");
                        tell_room(TO, QCTNAME(TP) + " jumps as high as " +
                            PRONOUN(TP) + " can " +
                            "and picks one the yellow fruits.\n", TP);
                    }
                }
                else
                {
                    write("You reach for a yellow fruit hanging on one of " +
                        "the lower branches.\n");
                    tell_room(TO, QCTNAME(TP) + " reaches for a yellow " +
                        "fruit hanging on one of the lower branches.\n", TP);
                }
                
                pear = clone_object(OBJ + "pear");
                pear->move(TP, 1);
                pear_num--;

                return 1;            
            }
            else if ( pear_tree && (pear_num <= 0) )
            {
                tell_room(TO, QCTNAME(TP) + " sighs as " + PRONOUN(TP) + 
                    " realizes all pears are growing too high for " +
                    OBJECTIVE(TP) + " to pick.\n", TP);
                notify_fail("You sigh as you realize that all pears " +
                    "are growing too high for you to pick.\n");
                return 0;    
            }
            else
            {
                notify_fail("Hmm, you do not know if there even is any " +
                    "fruit on that tree!\n");
                return 0;
            }
        break;
        case "peach":
        case "peach fruit":
            if ( peach_tree && (peach_num > 0) )
            {
                write("You swiftly pick one of the peach fruits, that " +
                    "grow low above the ground.\n");
                tell_room(TO, QCTNAME(TP) + " swiftly picks one of the " +
                    "peach fruits.\n", TP);
                peach = clone_object(OBJ + "peach");
                peach->move(TP, 1);
                peach_num--;
                return 1;
            }
            else if ( peach_tree && (peach_num <= 0) )
            {
                tell_room(TO, QCTNAME(TP) + " cannot find any more peach " +
                    "fruits to pick from the tree.\n", TP);
                notify_fail("You cannot find any more peach fruits to " +
                    "pick from the tree.\n");
                return 0;
            }
            else
            {
                notify_fail("Of course you would like to eat a peach or " +
                    "two, but you can not even get closer to that tree.\n");
                return 0;
            }
        break;
        case "fruit":
        case "fruits":
            notify_fail("What fruit are you trying to pick? There are apple, " +
                "peach and even pear trees growing here.\n");
            return 0;
        break;
    }
    notify_fail("What are you trying to pick? Maybe some fruit?\n");
    return 0;    
}

int
gather_cones(string what)
{
   object cone;
   
   if ( !stringp(what) )
   {
       notify_fail("Gather pine cones?\n");
       return 0;
   }
   
   if ( what == "cones" || what == "pine cones" || what == "cone" ||
       what == "pine cone" )
   {
       if ( cones > 0 )
       {
           write("You search the area for a moment and find a brown pine " +
               "cone.\n");
           tell_room(TO, QCTNAME(TP) + " finds a small pine cone.\n", TP);
           cone = clone_object(OBJ + "pine_cone");
           cone->move(TP, 1);
           --cones;
           
           return 1;
       }
       else 
       {
           notify_fail("You search the area, but you can not " +
               "find any pine cones.\n");
           tell_room(TO, QCTNAME(TP) + " searches the area, but finds " +
               "nothing.\n", TP);
           return 0;
       }
   }
   else
   {
       notify_fail("Gather pine cones?\n");
       return 0;
   }
   
}

/* Function   : set_animal
 * Description: This function randomly places (or not) an animal in
 *              forest location in Qualinesti
 * Returns    : 1 - we place an animal in room
 *              0 - we do not clone an animal
 */
int
set_animal()
{
    object animal;
    int i;
    
    i = random(10);
        
    if (!animal)
    {
 /* We do not want animal to be cloned 100% times when we call the function
      so I make it a bit random.   */
        if ( i > 3 )
        {
            switch(random(6))
            {
 /* Rabbits are more common in this area than other animals, 
    so there is a bigger chance for cloning them.   */
            case 0:
            case 1:
                animal = clone_object(FNPC + "rabbit");
            break;
            case 2:
                animal = clone_object(FNPC + "squirrel");
            break;
            case 3:
                animal = clone_object(FNPC + "fox");
            break;
            case 4:
                if ( random(2) )
                    animal = clone_object(FNPC + "wolf");
                else
                    animal = clone_object(FNPC + "wolf2");
            break;
            case 5:
                animal = clone_object(FNPC + "stag");
            break;  
            default:
                animal = clone_object(FNPC + "rabbit");
            break;
            }
            
            animal->move(TO);
            return 1;
        }
        
        return 0;
    }

    return 0;
}

/* Function name : random_animal
 * Description   : chooses a random animal to clone
 */
object
random_animal()
{
    object ob;
    
    switch (random(21))
    {
        case 0..4:
            ob = clone_object(NPC + "rabbit");
        break;
        case 5..7:
            ob = clone_object(NPC + "stag");
        break;
        case 8..11:
            ob = clone_object(NPC + "wolf");
        break;
        case 12..14:
            ob = clone_object(NPC + "squirrel");
        break;
        case 15..17:
            ob = clone_object(NPC + "fox");
        break;
        case 18..19:
            ob = clone_object(NPC + "wolf2");
        break;
        case 20:
            ob = clone_object(NPC + "dog");
        break;
        default:
            ob = clone_object(NPC + "rabbit");
        break;
    }
    
    return ob;
}

int 
climb_tree(string arg)
{
    string desc = look_around();
    
    if ( !stringp(arg) )
    {
        notify_fail("Climb tree?\n");
        return 0;
    }
    
    if ( arg == "up" || arg == "tree" )
    {
        if ( TP->resolve_task(650, ({ TS_DEX, SS_CLIMB })) > 0 )
        {
            write("You try to climb the nearest tree.\n");
            write(desc);
            tell_room(TO, QCTNAME(TP) + " climbs one of the trees and " +
                "checks the surrounding area.\n", TP);
            return 1;
        }
        else
        {
            write("In a vain attempt you try to climb the nearest tree.\n");
            tell_room(TO, "In a vain attempt " + QTNAME(TP) + 
                " tries to climb one of the trees.\n", TP);
            return 1; 
        }
    }
    else
    {
        notify_fail("Climb tree?\n");
        return 0;
    }
    
}

string
look_around()
{
    object  *rooms, *seen_live = ({ }), *seen_dead = ({ });
    int     i, sz;
    string  desc1, desc2;
    
    rooms = query_exit_rooms();
    rooms += ({ E(TP) });
    
    for ( i = 0, sz = sizeof(rooms); i < sz; i++ )
    {
        seen_live += FILTER_LIVE((rooms[i])->subinventory());
//        seen_dead += FILTER_DEAD(({(rooms[i])->subinventory()}));
    }
    
    seen_live = FILTER_CAN_SEE(seen_live, TP) - ({ TP });
    seen_dead = FILTER_CAN_SEE(seen_dead, TP);
          
    if ( sizeof(seen_live) )
    {
        desc1 = "You see " + COMPOSITE_LIVE(seen_live) + " standing " +
            "on the ground not so far from this place";
    }
    else
    {
        desc1 = "The forest stretches out in all directions";
    }
    
    if ( sizeof(seen_dead) )
    {
        desc2 = ". You also notice " + COMPOSITE_DEAD(seen_dead) +
            " laying on the ground";
    }
    else
    {
        desc2 = "";
    }
    
    return "\nAs you reach the lower branches, you take a quick glance at " +
        "the surrounding area. " + desc1 + desc2 + ". You climb back down.\n";
        
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        start_room_tells();
}

