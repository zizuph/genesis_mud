/* Standard foothills leading towards round Mount Kyrus in Calia. 
   Template based on std_tunnel.c in Gondor.

   Coded by Maniac 1/3/95
   Modfied Maniac 25/7/95
   typo corrected Maniac 9/1/96
   now inherit from kr_room code, Maniac, 5/4/96 
*/

#pragma save_binary

inherit "/d/Calia/std/kr_room";
#include "/sys/stdproperties.h"


int c;
string w; 

string
mountain_des = "The rock face of the mountain is bare, totally " +
               "devoid of plant life, and there is a mist about " +
               "its peak. These things combine to give it a " +
               "striking and markedly grim appearance. "; 


string
opp_direc(string dir)
{
    switch (dir) {
        case "north": return "south"; break;
        case "south": return "north"; break;
        case "east": return "west"; break;
        case "west": return "east"; break;
        case "northeast": return "southwest"; break;
        case "northwest": return "southeast"; break;
        case "southeast": return "northwest"; break;
        case "southwest": return "northeast"; break;
        default: return "";
    }
}


string
hill_short()
{
    switch (c) {
       case 0: return "gigantic, imposing hills";
                  break;
       case 1 : return "great, bleak hills";
                  break;
       case 2 : return "bare looking, dark green hills"; 
                  break;
    }
}


string
mountain_short()
{
    switch (c) {
       case 2: return "stands imperiously ";
                  break;
       case 1 : return "rises, massive and sheer, ";
                  break;
       case 0 : return "rears up, huge and menacing, "; 
                  break;
    }
}



/* Description of the mountain depending on how close one it */
string
close_desc(int examining)
{
     string str;

     switch (c) {
         case 0: str = 
             "You are not far from where the foothills merge with the " +
             "base of the mountain. " +
             "Its mighty rock face extends right across your " + 
             "view and rises up far into the sky, casting a huge " +
             "shadow over the land around. "; 
             if (examining) str += mountain_des;
             return str; 
             break;
         case 1: str = 
            "The mountain is not more than a few hundred yards away now, "+
             "all the landscape around it completely dwarfed, as if the " +
             "rolling hills are cowering in humble worship. ";
             if (examining) str += mountain_des;
             return str; 
            break;
         default: str =
            "The mountain is a fair distance away, but its " +
            "great grey mass dominates the landscape. ";
            if (examining) str += mountain_des; 
            return str;
            break;
     }
}



/* Give a special addition to the description is this is a potential 
   kroug room */
string
kroug_desc()
{
    if (!this_object()->query_kroug_start_room()) 
        return "";
   
    switch (random(5)) { 
        case 0 : return "You get a sense of deep foreboding in this place. ";
                 break; 
        case 1 : return "There is an air of gloom and darkness here. ";
                 break;
        case 2 : return "Something about this place makes you feel nervous. ";
                 break;
        case 3 : return "There is a great depression in the atmosphere " +
                        "here. ";
                 break;
        default : return "The sunlight seems to be much dimmer than usual " +
                         "here. ";
                  break;
    }
}



/*
 * This function defines the room.
 * extra_long - to add to description.
 * where - where foothills are in proximity to the mountain, 
           should be a direction.
 * close - how close we are to mountain.
 */
varargs void
make_the_room(string extra_long, string where, int close, int no_road)
{
    if (!extra_long) { extra_long = ""; }

    /* Set globals */
    c = close;
    w = where;

    if (!no_road) {
        set_name("road");
        set_short("Road through " + where + "ern foothills of Mount Kyrus");
        set_long("You are on a cobbled road through the " +
            where + "ern foothills of Mount Kyrus. " +
            "The " + hill_short() + " rise to steadily greater heights " +
            "as they approach the mountain, which " + mountain_short() + 
            "to the " + opp_direc(where) + ". " + close_desc(0) + 
            extra_long);
    }
    else {
        set_short(capitalize(where) + "ern foothills of Mount Kyrus"); 
        set_long("You are in the " +
            where + "ern foothills of Mount Kyrus. " +
            "The " + hill_short() + " rise to steadily greater heights " +
            "as they approach the mountain, which " + mountain_short() + 
            "to the " + opp_direc(where) + ". " + close_desc(0) + 
            kroug_desc() + extra_long);
    }

    add_item(({"mount kyrus", "mountain", "mount", "rock face"}),
       close_desc(1) + "\n");

    add_item(({"hills", "foothills", (where+"ern hills"), 
              (where+"ern foothills"), "hill" }), 
         "The foothills are getting higher and more imposing " +
         "as they sweep " + opp_direc(where) +" towards Mount " +
         "Kyrus. They are also getting more bare and devoid of grass " +
         "and plant life as they near the mountain.\n"); 

    add_item("grass", "The short grass that grows on the foothills is " +
                      "a very dark green colour.\n");

    if (!no_road) 
        add_item(({"road", "cobbled road"}), 
            "A simple road through the surrounding foothills, its surface " +
            "made of smallish grey stones that are " +
            "closely cobbled together. It might create a slightly " +
            "bumpy ride for carriages.\n"); 

    add_prop(ROOM_I_INSIDE, 0);
}
