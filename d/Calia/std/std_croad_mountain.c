/* Standard crystalline road up Mount Kyrus in Calia. 
   Template based on std_tunnel.c in Gondor.

   Coded by Maniac 1/3/95.
    
   History:
          19/5/95        Spear quest elements added      Maniac
          27.3.95              Modified                  Maniac
          9.1.96         typo corrected                  Maniac
          5/4/96         inherit from kr_room            Maniac
          12/5/16        typo corrected                  Jaacar
*/

#pragma save_binary

inherit "/d/Calia/std/kr_room";
#include "/sys/stdproperties.h"
#include "/d/Calia/mountain/special/spear_quest.h"

int how_high;


string
query_spear_quest_type()
{
     if (how_high < 4)
         return "bronze";
     if (how_high < 8)
         return "silver"; 
     if (how_high < 12)
         return "golden";
     if (how_high < 16)
         return "steel";
     if (how_high < 20)
         return "mithril";
     return "crystalline";
}


string
*spear_keywords()
{
    string *str = ({"spears", "spear"});

    str += ({ (query_spear_quest_type()+" spears"), 
              (query_spear_quest_type()+" spear") }); 
    return str;
}


string
spear_long()
{
    return "A pair of " + query_spear_quest_type() + " spears are " +
           "stuck upright into the ground on " +
           "either side of the road at this point. ";
}


string
view_long()
{
    if (how_high < 4)
        return "From here you get a decent view " +
               "of the foothills, and then moorland, to the " +
               "northwest. "; 
    if (how_high < 8)
        return "From here you get a good view of the great " +
               "land around Argos opening out to the east and " +
               "northeast. ";
    if (how_high < 11)
        return "From here you get a good view of the southeastern " +
               "regions of Calia, with the great lake Lantia " +
               "dominating the view. ";  
    if (how_high < 15)
        return "From here you get a magnificent view of " +
               "the great plains of southwestern Calia. ";

    return "A pale mist hangs in the air at this high altitude. " +
           "The mist is stopping you " +
           "from seeing the view of the lands below from here; " +
           "a pity as it would surely be magnificent from this " +
           "height. ";
}


string
road_des()
{
    string str;
    
    str = "This stretch of the road is ";
    if (how_high < 7) return str + 
                      "relatively near the mountain's base. ";
    if (how_high < 12) return str +
                      "roughly half way up the mountain. ";
    if (how_high < 17) return str +
                      "more than half way up the mountain. ";
    if (how_high < 24) return str + "near the top of the mountain. ";
    return str + "very near the plateau at the top of the mountain, " +
                 "which is no more than fifty yards above you now. ";
}


/*
 * This function defines the room.
 */
void
make_the_room(string extra_long, int h_h)
{
    if (!extra_long) extra_long = ""; 

    how_high = h_h;
    set_name("road");
    set_short("Crystalline road up Mount Kyrus");
    set_long(
       "You are on a crystalline road that winds steeply up the side " +
       "of Mount Kyrus, encircling " +
       "the mountain in a long spiral that leads towards its peak, " + 
       "which is crowned by the Palace of Caliana. " +
       road_des() + 
       view_long() +
       "Beside you on the near side of the road, the sheer jagged " +
       "rock face of Mount Kyrus rises up, its mighty wall reaching " + 
       ((how_high < 22) ? "far up into the sky. " : 
       "up high above you, although you are now quite near the peak. ") + 
       "Just off the other side of the road, a " + 
       ((how_high > 4) ? "huge " : "") + "fall " +
       "onto merciless rocks below awaits anyone suicidal or clumsy " +
       "enough to step off the edge of the precipice. "  +
       ((how_high % 2 == 1) ? spear_long() : "") +
       extra_long); /* "The road leads up to <direction>.." */
          
    add_item(({"rocks", "rock", "rock face", "wall", "face", 
               "mighty wall", "cliff", "precipice"}), 
          "The massive, steep rock face of the mountain rises above " +
          "you on the near side of the road and falls away steeply on " +
          "the other side. The rock face is bare, totally devoid of " +
          "plant life, giving it a rather grim appearance.\n");     

    if (how_high > 14) 
    add_item(({"mist", "pale mist"}), "A thin pale mist is all about " +
        "you since you are now at quite a high altitude. One cannot " +
        "see far above or below from here.\n"); 

    if (how_high % 2 == 1)
    add_item(spear_keywords(), "About eight feet long, the " +
        "spears are set upright in the rock of the mountain on " +
        "either side of the road. These spears, that mark the territory " +
        "of the Calian warriors, have to be kept well " +
        "polished at all times.\n");

    add_item(({"road", "crystalline road"}), "The road surface is made " +
         "of crystal. The path on which it was based is very ancient, " +
         "perhaps thousands of years old.\n");

    add_item(({"mountain", "mount kyrus"}), "The mountain is huge " +
        "and imposing, the most striking natural landmark in all of " +
        "Calia, whether seen up close or from a distance. Its grey, " +
        "bare rock gives it a grim, mysterious appearance.\n");

    add_prop(ROOM_I_INSIDE, 0);
}



/* do_polish, intended to catch when players try to polish spears */
int
do_polish(string str)
{
     string s, sd;
     object polish_ob;
     object tp = this_player();

     if (!str) {
         notify_fail("Polish what?\n");
         return 0;
     }
    
     sd = query_spear_quest_type(); 
     if ((str != "spear") && (str != "spears") &&
         (str != sd + " spear") && (str != sd + " spears") &&
         (sscanf(str, "spear %s", s) != 1) &&
         (sscanf(str, "spears %s", s) != 1) && 
         (sscanf(str, sd + " spear %s", s) != 1) &&
         (sscanf(str, sd + " spears %s", s) != 1)) {  
         notify_fail("Polish what?\n");
         return 0;
     }

     if (polish_ob = present(SQ_POLISH_OB, tp)) {
          polish_ob->do_polish(tp, sd);
          return 1;
     }

     notify_fail("You cannot polish the spears with what you have. " +
                 "It seems that you'll need something special to polish " +
                 "the spears with. Some shopkeepers might have an useful " +
                 "item for you.\n");
     return 0;
}


void
init()
{
    ::init();
    if ((how_high % 2) == 1) 
        add_action("do_polish", "polish"); 
}
