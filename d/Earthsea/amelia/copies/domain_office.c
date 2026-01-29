

#pragma save_binary

#include "/sys/macros.h"
#include "/d/Genesis/start/human/town/tower.h"
inherit TOWER_OFFICE;

object *portal_players = ({ }); 
object *air_players = ({ }); 
leave_room();

void
create_tower_office()
{
    disable_logged_in_display();
    disable_rank_display();
set_project_path("/d/Earthsea/open/project/");
    set_long(BS("Wind whistles past the pillars which"+
        " hold the roof over this tower room. The room"+
        " is open looking out over Havnor, the greatest"+
        " island in Earthsea. The large white pillars "+
        "are the only walls of this room, and you can "+
        "smell the fresh salt air blowing in. Below lies"+
        " the city Havnor Great Port. Ships from all the"+
        " islands fill its ports. Beyond the stone "+
        "buildings of the city, miles of farmland stretch"+
        " inland towards the Revnian mountains and "+
        "westward towards Mt. Onn. Some words have been "+
        "etched into the stone base of the pillar "+
        "nearest you.  As you survey the "+
        "room you become aware of a vague flickering at "+
        "its center. You notice a portal you haven't seen"+
        " before, pulsing in a hypnotic manner.", 70));

    add_item(({"portal","flickering","flicker"}),
        "It shimmers softly, just within the scope of your "+
        "visual perception. Its faint rippling pulses "+
        "rhythmically... Perhaps if you focused on the portal"+
        " you could catch a glimpse of what lies beyond it.\n");
    add_item(({"pillar","pillars"}),"The pillars are made of "+
        "sturdy white stone, pockmarked by the wind and "+
        "elements.  You notice some words etched into the stone"+
        " of the pillar nearest you.\n");
    add_item(({"pockmark","pockmarks","abrasion","abrasions"}),
        "They are tiny little abrasions in the stone "+
        "probably caused by exposure to the salt air.\n");
    add_item(({"ship","ships"}), "Looking out over the port "+
        "you can see a quite a few of them coming and going "+
        "in the bustle that lies below.\n");
    add_item(({"port","ports"}), "You can't tell anything more "+
        "about them from here, other than that the ships come"+
        " and go.\n");
    add_item(({"dock","docks"}), "The docks "+
        "seem fairly busy, with ships pulling into port here "+
        "and there along the beach.\n");
    add_item(({"beach","sand","shore","shoreline","beaches"}),
        BS("The silvery sands of the beaches below extend to the"+
        " south and northeast as far as you can see.  Near the"+
        " harbour there is quite a bit of activity as the ships"+
        " come and go.\n", 70));
    add_item("harbour","The waters stretching out below are "+
        "spotted with activity of passenger ships and fishing"+
        " boats.\n");
    add_item(({"farm","farms","farmland"}),BS("The land "+
        "looks rich. It's pastures are a deep green, and"+
        "  small animals, possibly sheep or goats dot the "+
        "landscape.\n",70));
    add_item(({"sheep","goat","goats"}), "You can't tell "+
        "enough about them from this distance to be sure "+
        "what they are.\n");
    add_item("walls", "The room is open to the air, its roof held"+
        " overhead by large white pillars, pockmarked by time and "+
        "the elements.\n");
    add_item(({"pasture","pastures"}), "They are lush and green. "+
        " Animals, possibly goats or sheep dot the landscape.\n");
    add_item(({"mountain","mountains",}), "Which did you want to "+
        "look at?  The Revnians? or Mt. Onn?\n");
    add_item(({"peak","peaks"}), "You can't see much detail from"+
        " here.\n");
    add_item(({"ships","boats","ship","boat"}), "There are many"+
        " that come and go to the different docks, but you "+
        "can't tell too much about them from here.\n");
    add_item(({"revnians", "revnian"}),"This is"+
        " a range of smaller mountains.  Many peaks stretch "+
        "to the north, bending to the horizon.\n");
    add_item("horizon","The peaks of mountain tops gently meet "+
        "the sky, blending off into the distance.\n");
    add_item(({"onn","west mountain","mt onn"}), BS(
        "The mountain looms to your"+
        " west, its great peak rising awesomely to the sky from a"+
        " mist-shrouded base.  As you look the mountain almost "+
        "seems to breathe, the deep mist ripples as if exhaled by "+
        "the land itself.  There is a penetrating silence in its"+
        " majesty.", 70));
    add_item("base","You can't make out the base of Mt. Onn.  It "+
        "is covered by a thick fog.\n");
    add_item(({"mist","fog"}),"It is deep and billowy.\n");
    add_item(({"city","havnor","[havnor] great port"}), "Stone and "+
        "wooden buildings line the busy streets, and many a "+
        "ship fill the ports of this great city.\n");
    add_item(({"building", "buildings"}), "The buildings are well "+
        "kept, and the streets have a healthy bustle about them "+
        "with people milling about below.\n");
    add_item(({"people"}),"You can't see much about them from "+
        " here.\n");
    add_item(({"floor","ground"}), "The floor, like the pillars, is "+
        "made of white stone--sturdy and grand.\n");
    add_item(({"roof","ceiling"}),"The ceiling is made of a marbled"+
        " stone.  At its center is an intricately carved scene,"+
        " engraved in the stone.\n");
    add_item(({"scene","engraving","picture"}),"@@scene");
    add_item("figure", "The image melts away from your mind as "+
        "you try to focus on it.  You sense that there is a somehow"+
        " a great power in what is dipicted here.\n");
    add_item(({"words", "sign"}), "@@sign");
    add_item(({"stone", "base", "stone base"}), "There are "+
        "some words etched into it.\n");
    add_cmd_item(({"words","sign"}), "read", "@@sign");

    //add_tower_link("tower");
    add_exit("/d/Genesis/start/human/town/tfloor1", "tower",
        "@@check_exit");
}

void
init()
{
    ::init();
    add_action("enter","enter");
    add_action("air","smell");
    add_action("portal","focus");
}
 
string
scene()
{
    return(BS("The scene dipicts a solitary figure, or is it a "+
        "figure?  Hmm.  It seems almost as if it were a voice "+
        "really.  How can that be?  A voice or a feeling? And "+
        "yet it is a figure. A man perhaps, amidst the swirling"+
        " and powerful mists of...  Hmm.  You can't quite put "+
        "your finger on what you're looking at.  Yet there is a "+
        "strong impression of a time beyond this one.  Somehow "+
        "the beginning, yet the end of time.  It is an odd picture "+
        "indeed.", 70) + "Below the picture is a single word: \"Ea\".\n");
}

sign()
{
    cat("/d/Roke/Earthsea/open/office_sign.txt");
    return "";
}

check_exit()
{
    write("As you turn to leave this place words echo powerfully "+
        "in your mind:\n    Only in Silence the word,\n");
    
    say(QCTNAME(TP)+ " turns as if about to leave, and then pauses "+
        "a moment.\n");
    set_alarm(2.0, 0.0, &write("  only in dark the light,\n"));
    set_alarm(4.0, 0.0, &write("    only in dying life:\n"));
    set_alarm(6.0, 0.0, &write("    bright the hawk's flight\n"));
    set_alarm(8.0, 0.0, &write("    on the empty sky.\n"));
    set_alarm(11.0, 0.0, &leave_room());
    return 1;
}

leave_room()
{
    write("You leave the tower.\n");
    say(QCTNAME(TP)+ " leaves tower.\n");
    TP->move_living("M", "/d/Genesis/start/human/town/tfloor1");
    say("/d/Genesis/start/human/town/tfloor1",QCTNAME(TP)+
        " stumbles in from Roke, appearing a little dazed.\n");
    return 1;
}

int
enter(string s)
{
    if(!strlen(s) || !parse_command(s, TO,
        "[the] [rippling] 'portal'"))
        return 0;
    else
    {
        TP->catch_msg("The portal does not transport yet.\n");
        return 1;
    }
} 


void
air_stage(int stage, object player)
{
    if (!objectp(player) || !objectp(present(player, this_object()))) { 
        air_players -= ({ player });  
        return;
     } 

    switch (stage) { 
        case 1 :  
                tell_object(player, "Mmmm.....\n");
                tell_room(this_object(), (QCTNAME(player)+ " takes a "+
                     "deep breath, smiling happily.\n"), player);
                break;
        case 2 : 
               tell_object(player, "There is no place like"+
                        " the sweet lands of the Archipelago.\n");
               break;
     } 

     stage++; 

     if (stage > 2) { 
         air_players -= ({ player }); 
         return;
     } 
     set_alarm(1.0, 0.0, &air_stage(stage, player)); 
}

int
air(string s)
{
    object tp = this_player(); 

    NF("Smell what? The air?\n");
    if(!strlen(s) || !parse_command(s,TO,"[the] [sea] 'air'"))
        return 0;
    else
    {
        if (member_array(tp, air_players) > -1) { 
            notify_fail("You are already smelling the air.\n"); 
            return 0;
        } 
   
        tp->catch_msg("You breathe the fresh, salty sea "+
            "air deep in your lungs, tasting it on your"+
            " lips.\n");
        air_players += ({ tp }); 
        set_alarm(1.0, 0.0, &air_stage(1, tp)); 
        return 1;
    }
}


void
portal_stage(int stage, object player)
{
    if (!objectp(player) || !objectp(present(player, this_object()))) { 
        portal_players -= ({ player });  
        return;
     } 

     switch (stage) { 
        case 1 : 
            tell_object(player, "The rhythmic ripples rise"+
                " and fall repetitiously. As you focus on\nthem the "+
                "world around you falls away. The ripples oscillate "+
                "and\nchurn. Suddenly you can see lapping waves..."+
                "\n\n");
            tell_room(this_object(), ("You notice "+QCTNAME(player)+
                " standing before the portal with a glazed look in "+
                player->query_possessive() + " eyes.\n"), player);
             break;
        case 2 : 
            tell_object(player, "You continue to look "+
               "through the portal. The crashing waves beat upon\n"+
                "the shores of a tiny island...\n\n");
            break;
        case 3 : 
            tell_object(player, ("Suddenly the image draws "+
                "much closer. Your hawk's eye view narrows\nto a small"+
                " hut. The shack is small and rickety as if a child "+
                "had\nbuilt it.\n\n"));
             break;
        case 4 : 
             tell_object(player, ("Inside a man with white, "+
                 "long hair crouches in terror. A man or a\nwoman (you"+
                 " can not tell) peers up from a heap of rags "+
                 "or hides on the\nfloor.\n\n"));
             break;
        case 5 : 
             tell_object(player, ("Suddenly you feel as if "+
                  "the eyes you have been looking through were\nnot your"+
                  " own. Yet still you focus again on the figures..."+
                  "\nWhat can possibly be important about these people"+
                  " or this place?\nThe shadows of the dark "+
                  "hut rise up, becoming a blanket of darkness,\n"+
                  "obscuring your view before you can see much"+
                  " more.\n\n"));
             break;
        case 6 : 
             tell_object(player, "You can not see anything, "+
                    "yet somehow you feel certain what you are\nviewing "+
                    "has shifted elsewhere.\n\n");
             break;
        case 7 :  
            tell_object(player, ("...the air beyond the "+
                "portal is cold and you can feel the chill of\ndank "+
                "stale air. Utter blackness lies like a weight "+
                "even from afar.\nA welling sense of unease catches"+
                " in your throat...\nThe glow of a pale violet "+
                "marshlight appears out of the darkness\nrevealing"+
                " a winter traveler. The traveler peers up at a "+
                "tiny hole\nin the cavern ceiling. He holds a wooden"+
                " staff which emits the dim\nfog-like light. The "+
                "traveler seems oddly familiar.\n\n"));
             break;
        case 8 : 
            tell_object(player, ("The traveler shifts his "+
                 "position, focusing on the wall. He seems\nto mutter "+
                 "some sort of incantation, but before you can see "+
                 "anything\nhappen the fog thickens and swirls up "+
                 "obscuring your view.\n\n"));
            break;
        case 9 : 
             tell_object(player, ("The swirling fog takes on "+
                  "odd shapes wisping and grasping for a\nmoment and then"+
                  " dissipates.\n\n"));
             break;
        case 10 : 
             tell_object(player, ("You are left standing before "+
                  "the portal.\n\n"));
             break;
      } 

      stage++; 
      if (stage > 10) { 
          portal_players -= ({ player }); 
          return;
      } 
      set_alarm(5.0, 0.0, &portal_stage(stage, player)); 
}

int
portal(string s)
{
    object tp = this_player(); 

    NF("Focus on what? The portal?\n");
    if(!strlen(s) || !parse_command(s, TO,
        "[on] [the] [rippling] 'portal'"))
        return 0;
    else
    {
        if (member_array(tp, portal_players) > -1) { 
            notify_fail("You are already focused on the portal.\n"); 
            return 0;
        } 
        tell_object(tp, ("You focus on the faint rippling of the "+
                         "portal before you...\n\n"));  
        portal_players += ({ tp }); 
        set_alarm(4.0, 0.0, &portal_stage(1, tp)); 
        return 1;
    }
}

