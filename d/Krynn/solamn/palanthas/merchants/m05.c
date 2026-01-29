/* Mortis 12.2005
 * Smells
 *
 * Mortis 09.2014
 * Opened Tower of Arms entrance.
 * Mortis 10.2014
 */

#include "../local.h"
#include CLOCKH
#include <cmdparse.h>
#include <macros.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>

inherit MERCH_BASE;

#define VIEWNW                (MERCH + "m03")
#define VIEWSW                (MERCH + "m06")

string
query_to_jail()
{
  return "southwest";
}

nomask public string
get_time_desc()
{
    string desc = "";
    string road = "  Long flights of stairs lead west down the small hill "
    + "upon which this landing is built. A few benches sit beside an "
    + "ornate railing of marble overlooking the grassy slope overlooking "
    + "Palanthas Circle below. Surrounding you to the north and "
    + "south is a thick wood which opens into a vast field. In the south "
    + "of the field, due east of you, rises a squat, square tower of "
    + "marble. \n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
    desc += "The clean marble of this majestic, marble landing "
    + "glows in " + one_of_list(({"pale purple ", "soft pink ",
      "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
    + "mountains in the east. The air is rich with the smells of morning "
    + "dew dripping from the leaves on a cool, misty breeze." + road;
    break;

    case TOD_DAY:
    desc += "The clean marble of this majestic, marble landing gleams "
    + "in the midday sun. The streets below are filled with the noisy "
    + "murmurings of merchants and shoppers going about their daily "
    + "business." + road;
    break;

    case TOD_TWILIGHT:
    desc += "The clean marble of this majestic, marble landing catches the "
    + "last rays of the sun appearing to glow of its own accord "
    + "as travellers and merchants make their way about in the "
    + "streets below." + road;
    break;

    case TOD_NIGHT:
    desc += "The moon and stars shed pale light across the translucent marble "
    + "of this majestic landing amplifying the yellow glow of the street "
    + "lamps. A few people still make their way about at this hour." + road;
    break;

    default:
    break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("On a majestic, marble landing west of a squat, square tower");
    LONG("@@get_time_desc@@");

    ITEM(({"wood", "woods", "north wood", "north woods", "thick wood",
           "thick woods"}), "A thick wood of trees surrounds you to the  "
    + "north and south. They are the Gallant Field Woods and home to the "
    + "constabulary of Palanthas, the Palanthian Guard. Their Tower of "
    + "Arms rises from the vast field at its center to the east.\n");
    ITEM(({"landing", "majestic landing", "marble landing",
           "majestic marble landing"}), "This landing of clean and polished "
    + "marble blocks spreads out in a large oval with stairs three flights "
    + "long leading down the grassy slope to the northwest and southwest to "
    + "Palanthas Circle below. A great deal of ornate chiselwork has been "
    + "applied to the marble borders, the ornate railing, and even the "
    + "marble benches of the landing. The marble blocks continue east as a "
    + "walkway to the Tower of Arms, and you can <view> what's going on below "
    + "to the northwest or southwest.\n");
    ITEM("walkway", "Clean and polished marble blocks form a walkway from "
    + "the landing into the Tower of Arms in the field to your east.\n");
    ITEM(({"railing", "marble railing", "ornate railing"}), "A short railing "
    + "of thick, ornately chiseled marble overlooks the grassy slope to your "
    + "west from which you may <view> the travellers of Palanthas Circle "
    + "below to the northwest or southwest.\n");
    ITEM(({"circle", "palanthas circle"}), "Palanthas Circle loops around "
    + "the inner city of Palanthas. It is an expertly engineered work of "
    + "translucent white marble perfection. You can <view> who's travelling "
    + "it to the northwest or southwest.\n");
    ITEM(({"stair", "stairs", "flight", "flights", "flight of stairs",
           "flights of stairs"}), "Three long flights of translucent white "
    + "marble stairs descend west to Palanthas Circle. They are worn with "
    + "the steps of many travellers but still nearly perfect and smooth.\n");
    ITEM("chiselwork", "Ornate chiseling has been applied to the borders of "
    + "the marble blocks, ornate railing, and marble benches giving the "
    + "landing a majestic, noble appearance.\n");
    ITEM(({"benches", "bench", "marble bench", "marble benches"}), "Thick "
    + "benches of marble sit beside the ornate railing overlooking the "
    + "grassy slope to the west. You may sit on them if you like.\n");
    ITEM(({"field", "fields", "vast field"}), "A vast field of pale brown "
    + "and green grasses surrounds the Tower of Arms to the east and extends "
    + "a ways to the north from there. It is surrounded by a thick wood "
    + "atop this hill.\n");
    ITEM(({"slope", "grassy slope", "hill"}), "Thick, green grasses cover "
    + "the slope to the west below this landing.\n");

    CMD(({"northwest", "nw"}), "view", "@@view_northwest");
    CMD(({"southwest", "sw"}), "view", "@@view_southwest");

    EXIT(MERCH + "m03", "northwest", 0, 0);
//    EXIT(TOA + "toa01", "east", "@@place_closed", 0);
    EXIT(TOA + "toa01", "east", 0, 0);
    EXIT(MERCH + "m06", "southwest", 0, 0);

}

/*int
place_closed()
{
        write("Constables only for the present.\n");
        return 1;
}*/


view_northwest()
{
    /* This function returns an equivalent of 'look' from m01
     * most importantly without any supporting code from the
     * target room.
     */

    object *inv, *obs, *ppl, target;
    string desc;

    write(VIEWNW->long());
    target = find_object(VIEWNW);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    write(one_of_list(({"From above you can make out ",
                        "You believe you spot ",
                        "Your eyes come across "}))
                        + desc + " on the ground.\n");

    if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    write(one_of_list(({"Down below you see ",
                        "You notice below ",
                        "Down below you spy "}))
                        + desc + " outside the tower.\n");
 
    return 1;
}

view_southwest()
{
    /* This function returns an equivalent of 'look' from m01
     * most importantly without any supporting code from the
     * target room.
     */

    object *inv, *obs, *ppl, target;
    string desc;

    write(VIEWSW->long());
    target = find_object(VIEWSW);
    inv = all_inventory(target);
    obs = FILTER_SHOWN(FILTER_DEAD(inv));
    ppl = FILTER_LIVE(inv);

    if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
    write(one_of_list(({"From above you can make out ",
                        "You believe you spot ",
                        "Your eyes come across "}))
                        + desc + " on the ground.\n");

    if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
    write(one_of_list(({"Down below you see ",
                        "You notice below ",
                        "Down below you spy "}))
                        + desc + " outside the tower.\n");
 
    return 1;
}

void
init()
{
  ::init();
  add_action("action_sit", "sit");
  add_action("action_stand", "stand");
}

int 
action_sit(string str)
{
        if(TP->query_prop(TSIT))
        {
                write("But you are already sitting on a bench! How do you "
                + "expect to sit in two places at once?\n");
                return 1;
        }
          
        if(str == "around bench" | str == "around a bench" | 
           str == "at bench" | str == "at a bench" | str == "by bench" |
           str == "by a bench" | str == "bench" |
           str == "on a bench" | str == "on the bench" |
           str == "on one of the benches" | str == "chair at bench" |
           str == "in bench by railing" | str == "on bench by railing" |
           str == "by railing" | str == "in a bench by bench" |
           str == "on bench") 
        {
                TP->catch_msg("You sit down on one of the marble benches "
                + "by the railing.\n");
                say(QCTNAME(TP) + " sits down in one of the marble "
                + "benches by the railing.\n");
                TP->add_prop(TSIT, 1);
                TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting on one of the "
                + "marble benches by the railing");
                return 1;
        }
    
        else
        {
                TP->catch_msg("Where would you like to sit?  On a bench?\n");
                return 1;
        }
        
        return 1;
}

int 
action_stand(string str)
{
        if(str == "up" || str != "up")
        {
                if(TP->query_prop(TSIT))
                {
                        
                        TP->catch_msg("You stand up and leave the bench "
                        + "by the railing.\n");
                        say(QCTNAME(TP)+" stands up from the bench by the "
                        + "railing.\n");
                        TP->remove_prop(TSIT);
                        TP->remove_prop(LIVE_S_EXTRA_SHORT);
                        return 1;
                }

        }
        
        else
        {
                TP->catch_msg("Stand?  Stand up?\n");
                return 1;
        }
        
        return 1;
}

void leave_inv(object ob, object to)
{
        ::leave_inv(ob, to);    
        
        if(!objectp(to) || !objectp(ob))
                return;
                
        if(TP->query_prop(TSIT))
        {
                TP->catch_msg("You stand up from the bench by the railing "
                + "before leaving.\n");
                say(QCTNAME(TP) + " stands up from the bench by the "
                + "railing as "+ HE(TP) +" leaves.\n");
                TP->remove_prop(LIVE_S_EXTRA_SHORT);
                TP->remove_prop(TSIT);
        }

}
