
/* 
   This code may be inherited into water rooms that have room tells
   in order to make various types of sea life swim/float around. 
   This is sea life for which combat would not really be appropriate.  
   The info was researched from "A Seafarer's Guide to Marine Life" 
   by Paul V Horsman. 

   Coded by Maniac, 1-4/3/96
   Modified 19/3/96 with more creatures, Maniac. 
   11/9/98 Added feature for several names, Maniac
*/

#pragma save_binary
#pragma strict_types

#include <language.h>
#include <composite.h>


string *sea_creature_list = ({ });

string *sea_creature_present = ({ }); 

mapping sea_creature_number = ([ ]);

mapping presence_chance = ([ ]); 


mixed 
sea_creatures(string el)
{
    switch (el) {
         case "lantern fish" :  
                return ({ ("These tiny blackish silvery fish (about 7 cm " +
                         "long) are unusual in that they give off light. " +
                         "They have large reflective eyes and " +
                         "photophores down each side of their bellies.\n"),
                       ({"medium shoal of", "large shoal of",
                         "huge shoal of"}),
                       100, 100, "medium to deep", "swimming speedily",
                       ({ "lantern fish" }) });
                break;

        case "hatchet fish" :
               return ({ ("Hatchet fish are very small (about 5 cm) and " +
                          "peculiar looking, with steep upwards-opening " +
                          "mouths and fat bodies.\n"),
                         ({"small shoal of", "medium shoal of",
                           "large shoal of" }),
                         75, 75, "medium to deep", "swimming peculiarly",
                         ({ "hatchet fish" }) });
             break;

        case "sea catfish" :
              return ({ ("Some 45 cm long, these are silvery fish " +
                       "with a high pointed dorsal fin and whisker-like " +
                       "spines hanging from the mouth.\n"),
                      ({"solitary"}), 3000, 3000, "deep",
                        "swimming lithely",
                        ({"catfish", "sea catfish" }) });
              break;

        case "frog fish" :
               return ({ ("Unusually coloured small fish (about 10 cm), " +
                          "with mottled yellow " +
                          "brown and white compact bodies and ragged fins " +
                          "that " +
                          "resemble leaves. They can suck water to pump " +
                          "themselves into a shape that they hope will " +
                          "dissuade would-be attackers.\n"),
                        ({"solitary", "small shoal of"}), 400, 400,
                          "any level", "swimming nonchalantly", 
                          ({"frog fish" }) });
              break;
 
        case "red herring" : 
              return ({ ("You may as well ignore this fish.\n"),
                        ({"solitary"}), 500, 500,
                        "any level",
                        "swimming in the pattern of a question mark",
                        ({ "herring", "red herring" }) });
              break;

       case "trigger fish" :
            return ({("These medium-sized fish (some 45 cm) get " +
                      "their name from the interlocking spines " +
                      "in their first dorsal fin. Their bodies are " +
                      "flattened vertically, and their eyes are " +
                      "set well back.\n"),
                     ({"solitary", "small shoal of", "medium shoal of"}),
                      2300, 2300, "any level", "swimming jerkily", 
                     ({ "trigger fish" }) });

       case "flying fish" :
            return ({ ("These sleek fish often fling themselves " +
                      "out of the water to escape danger. Their " +
                      "blue and silver bodies (about 40 cm long) " +
                      "are highly streamlined " +
                      "and their pectoral and pelvic fins resemble " +
                      "wings.\n"),
                     ({"small shoal of", "medium shoal of"}),
                     2500, 2500, "upper levels", "swimming sleekly",
                     ({"flying fish" }) });
            break;

       case "needle fish" : 
            return ({ ("These are very slim fish about half " +
                      "a metre " +
                      "long. They are of pale gold colour " +
                      "with blueish fins and pointed noses.\n"),
                     ({"medium shoal of", "large shoal of" }),
                    2400, 2400, "upper levels", "swimming pointedly", 
                    ({"needle fish" }) });
            break;

       case "yellowtail fish" : 
            return ({ ("These fish have a brilliant yellow " +
                       "colour. Their flattened bodies are about " +
                       "a metre long, and they swim very " +
                       "quickly.\n"),
                    ({"solitary", "small shoal of"}),
                       5000, 5000, "any level", "swimming quickly",
                      ({"yellowtail", "yellowtail fish" }) });
             break;

        case "sun fish" : 
              return ({ ("A huge disc-shaped fish with leathery " +
                         "skin. Its tail fin is simply a frill " +
                         "running down the blunt rear end. It has " +
                         "a grey-brown back with lighter sides " +
                         "and belly. The mouth is very small, " +
                         "with a single beak-like tooth in " +
                         "each jaw.\n"),
                        ({"solitary"}), 100000, 100000, "deep",
                          "swimming slowly",
                         ({"sun fish" }) });
              break;

         case "whale shark" : 
              return ({ ("The world's largest fish, some " +
                        "fifteen metres long, but harmless, " +
                        "feeding on plankton. These creatures " +
                        "are as lethargic as they are huge, " +
                        "sometimes swimming lazily into ships.\n"),
                        ({"solitary"}), 1000000, 1000000,
                          "any level", "swimming titanically",
                        ({"whale shark" }) });
              break;

         case "aurelia aurita" : 
               return ({ ("A jellyfish that has a pale blue " +
                          "umbrella with faded pink lines. " +
                          "Its oral arms are dark blue with " +
                          "golden edges, and its tentacles are " +
                          "short and frilly.\n"),
                           ({"solitary" }),
                         1000, 1000, "upper levels",
                         "floating gracefully", 
                         ({"aurelia aurita" }) });
               break;

         case "chrysaora isosceles" : 
                           ({ ("This jellyfish has a " +
                           "beautiful alternated golden brown colour, " +
                           "long wavy oral arms and ordinarily " +
                           "proportioned tentacles.\n"),
                                 ({"solitary"}),
                          1000, 1000, "upper levels",
                          "floating imperiously",
                         ({ "chrysaora isosceles" }) });
              break;

        case "pelagia noctiluca" : 
               return ({ ("A jellyfish with a reddish, " +
                         "pocked umbrella, flattish oral arms " +
                         "and long tentacles.\n"),
                         ({"solitary"}),
                       1000, 1000, "upper levels",
                       "floating peacefully",
                       ({ "pelagia noctiluca" }) });
             break;

       case "cyanea lamarki" : 
             return ({ ("This jellyfish has a flattish, " +
                        "broad blue umbrella, leaf-like " +
                        "short oral arms and long golden " +
                        "tentacles.\n"),
                       ({"solitary"}),
                        1000, 1000, "upper levels",
                       "floating flatly", 
                       ({"cyanea lamarki" }) });
            break;

       case "rhizostoma pulmo" :
            return  ({ ("A jellyfish with a pale blue, " +
                        "bell shaped umbrella, thick " +
                        "central oral arms and no " +
                        "tentacles.\n"),
                      ({"solitary"}),
                      1000, 1000, "upper levels",
                      "floating magnificently", 
                      ({ "rhizostoma pulmo" }) });
            break;

       default : return 0;
                break;
   } 
}


/* Set chance of particular creatures being here. */ 
int
set_presence_chance(string cn, int ch)
{
     if (!sea_creatures(cn))  
         return 0;
     
     if ((ch < 1) || (ch > 100))  
         return 0;

     presence_chance = m_delete(presence_chance, cn); 
     presence_chance += ([ cn : ch ]); 
}


/* Add possibility of certain creatures arriving/leaving in the room */ 
int
add_sea_creature(string cn)
{
    if (!sea_creatures(cn)) 
        return 0;
    sea_creature_list += ({cn});  
    this_object()->add_tell("@@sea_creature_arrive:" + 
                              file_name(this_object()) + "|" + cn + "@@"); 
    this_object()->add_tell("@@sea_creature_leave:" + 
                              file_name(this_object()) + "|" + cn + "@@");
} 


string
sea_creature_desc()
{
     int i;
     string *tmp, cn, scd;

     if (!sizeof(sea_creature_present))
          return "";

     tmp = ({ });
     for (i = 0; i < sizeof(sea_creature_present); i++) {
         cn = sea_creature_present[i];
         tmp += ({ (LANG_ADDART(sea_creature_number[cn]) + " " + cn) });  
     }
     scd = capitalize(COMPOSITE_WORDS(tmp)); 

     if (sizeof(sea_creature_present) > 1)
         scd += " are here.\n";
     else
         scd += " is here.\n";

     return scd;
}


string
sea_creature_arrive(string cn)
{
    mixed el;
    string num, entry, the_tell; 
    int ch;

    if (!sea_creatures(cn)) 
        return "";

    if (member_array(cn, sea_creature_present) != -1)
        return "";

    ch = presence_chance[cn];

    if (!ch)
        return "";

    if (random(100) >= ch)
        return "";

    sea_creature_present += ({cn}); 

    el = sea_creatures(cn); 
    num = el[1][random(sizeof(el[1]))]; 
    entry = el[5];

    sea_creature_number += ([ cn : num ]); 

    the_tell = (capitalize(LANG_ADDART(num)) + " " + cn + " " +  
                "arrives " + entry + ".\n"); 
    this_object()->add_item(el[6], el[0]); 
    this_object()->change_my_desc(sea_creature_desc());

    return the_tell;
}


string
sea_creature_leave(string cn)
{
    mixed el;
    string num, entry, the_tell; 
    int ch;

    if (!sea_creatures(cn)) 
        return "";

    if (member_array(cn, sea_creature_present) == -1)
        return "";

    if (!random(4)) 
        return "";

    sea_creature_present -= ({cn}); 

    el = sea_creatures(cn); 
    entry = el[5];
    num = sea_creature_number[cn];

    sea_creature_number = m_delete(sea_creature_number, cn); 

    the_tell = (capitalize(LANG_ADDART(num)) + " " + cn + " " +  
                "leaves " + entry + ".\n"); 

    this_object()->remove_item(cn); 
    this_object()->change_my_desc(sea_creature_desc());

    return the_tell;
}


void
sea_creature_arrive_leave(string cn)
{
    if (member_array(cn, sea_creature_present) == -1)
         sea_creature_arrive(cn);
    else
         sea_creature_leave(cn); 
}


/* Start some creatures in this room */
void
start_creatures()
{
     int i;

     for (i = 0; i < sizeof(sea_creature_list); i++) 
         sea_creature_arrive_leave(sea_creature_list[i]); 

     this_object()->add_item(({"fish", "shark"}),  
                         "Give the type of sea creature that you want " +
                         "to look at, e.g. examine flying fish, " +
                         "examine aurelia aurita.\n");
     this_object()->add_item(({"shoal", "large shoal", "medium shoal", 
                               "huge shoal", "small shoal"}), 
                         "Give the type of sea creature that you want " +
                         "to look at, e.g. examine flying fish, " +
                         "examine aurelia aurita.\n");
}

