/*
  A room in the sea area off the west coast of Calia.

  Coded by Maniac, Jan 96.
  Added Thalassia Gate Entrance Quest - Jaacar, July 2003

*/

#include <stdproperties.h>
#include <macros.h>
#include <math.h>
#include <cmdparse.h>
#include <composite.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"
#include SEA_QUESTS

inherit "/d/Calia/sea/std/sector_1_0_3_room";

void
create_water_room()
{
    make_the_room("\n", 13, 1, 3);
    add_item(({"head","whale's head","whales head","whale head",
        "gigantic head","gigantic whale's head","gigantic whales head",
        "gigantic whale head"}),"The head looks to be the actual "+
        "gate into the walls surrounding the city.\n");
    add_item(({"opening","vertical opening","jaw","jaws"}),"This "+
        "opening and the "+
        "closing mechanism represent the jaw of this gigantic whale's "+
        "head. It appears if it were opened somehow, you could swim "+
        "through it into the city beyond.\n");
    add_item(({"mechanism","closing mechanism"}),"The closing "+
        "mechanism is made from some type of mechanical devices that "+
        "are like none you have ever seen before. The gnomes of the "+
        "realms would be fascinated by such an intricate design. Try "+
        "as you might, you cannot figure out how it works, or more "+
        "importantly, how to open the gates at this time.\n");
    add_item(({"skin","plate","plates","silver plate","silver plates",
        "silvery plate","silvery plates","metallic plate",
        "metallic plates","metallic silver plate",
        "metallic silver plates","metallic silvery plate",
        "metallics silvery plates"}),"These metallic silvery "+
        "plates form the skin of this whale head gate. They cover "+
        "the entire head and shine in the water with the light "+
        "coming from above.\n");
    add_item(({"teeth","bars","white bars","vertical white bars",
        "interlocking vertical white bars","sharp interlocking vertical bars"}),
        "These sharp interlocking vertical white bars form the teeth of "+
        "the whale's head. If these were to be opened somehow, or "+
        "if you were a small fish, you could probably swim through "+
        "to the other side.\n");
    add_item(({"eye","eyes","rocks","ruby coloured rocks",
        "giant ruby coloured rocks","right eye","left eye"}),"These "+
        "giant ruby coloured "+
        "rocks form the eyes of this whale's head gate. They sparkle "+
        "in the light shining down through the water from above as a "+
        "small fish swims by them. The eyes eerily appear to watch "+
        "you wherever you go in this area, even though "+
        "you know that it is not possible.\n");
    add_item("small fish","You notice a small fish rub against one "+
        "of the eyes and then disappear through a small slit in "+
        "the teeth.\n");

    add_swim_exit(SECTOR_PATH(13,2,3)+"wr_13_2_3", "south", 0, 1);
    add_swim_exit(SECTOR_PATH(12,1,3)+"wr_12_1_3", "east", 0, 1);
    add_swim_exit(SECTOR_PATH(12,0,3)+"wr_12_0_3", "northeast", 0, 1);
    add_swim_exit(SECTOR_PATH(12,2,3)+"wr_12_2_3", "southeast", 0, 1);
    add_swim_exit(SECTOR_PATH(14,2,3)+"wr_14_2_3", "southwest", 0, 1);
    add_swim_exit(SECTOR_PATH(13,1,2)+"wr_13_1_2", "up", 0, 0);
    add_swim_exit(SECTOR_PATH(13,1,4)+"wr_13_1_4", "down", 0, 2);
}

void
init()
{
    ::init();
    add_action("rub_eye","rub");
    add_action("feed_gate","feed");
}

int
rub_eye(string str)
{
    int ran_riddle;
    string player_name;

    if (str == "right eye")
    {
        if (!TP->test_bit(THAL_GATEQ_DOMAIN,THAL_GATEQ_GROUP,THAL_GATEQ_BIT))
        {
            write("You swim up and rub the right eye of the "+
                "whale's head. Your mind begins to wander "+
                "and things become all blurry around you. "+
                "Your eyes and mind clear and you see the "+
                "whale's head before you has come to life. "+
                "It begins to speak to you.\n\nTo enter the "+
                "gates, you must find the answer to this "+
                "riddle. Once you have figured out the "+
                "answer, you must feed me the object that the "+
                "riddle refers to ('feed <object> to the gates').\n\n");
            tell_room(environment(TP),QCTNAME(TP)+" swims up and rubs "+
                "the right eye of the whale's head.\n",TP);
            TP->add_prop(LIVE_I_PLAYER_TOUCHED_THAL_EYE,1);
            player_name = lower_case(TP->query_real_name());
            ran_riddle = NAME_TO_RANDOM(player_name,TGQS,TGQV);
            switch (ran_riddle)
            {
                case 0:               // Dolphin Eye
                    write("I swim through the oceans with "+
                        "speed and grace,\nso fast I am, "+
                        "others find it hard to keep "+
                        "pace.\nWhat you seek is dear to "+
                        "me,\nfor without it, I cannot see.\n");
                    TP->add_prop(LIVE_I_PLAYER_THAL_RIDDLE,1);
                    break;
                case 1:               // Turtle Neck
                    write("Large and green and swimming in the "+
                        "sea,\na shelled place to hide I always "+
                        "have with me.\nWhat you will require "+
                        "from me just might be torn,\nbut I am "+
                        "afraid it cannot be worn.\n");
                    TP->add_prop(LIVE_I_PLAYER_THAL_RIDDLE,2);
                    break;
                case 2:               // Eel Skin
                    write("Through the depths of the ocean I fly,\n"+
                        "though the powers I possess usually "+
                        "come from the sky.\nThat which you "+
                        "seek I will not lose,\nbecause I will "+
                        "not be made into a pair of shoes.\n");
                    TP->add_prop(LIVE_I_PLAYER_THAL_RIDDLE,3);
                    break;
                case 3:                // Demon Toad Legs
                    write("With my pink, flickering tongue and "+
                        "enormous green eyes,\nI am swimming in "+
                        "the sea.\nThese webbed things you will "+
                        "require from me.\n");
                    TP->add_prop(LIVE_I_PLAYER_THAL_RIDDLE,4);
                    break;
                default:               // Shark Fin
                    write("Fear strikes when seeing that which "+
                        "you seek,\nI am certainly not "+
                        "what you would call weak.\nLarge and "+
                        "white and swimming in the sea,\neveryone "+
                        "I meet has fear of me.\n\n");
                    TP->add_prop(LIVE_I_PLAYER_THAL_RIDDLE,5);
                    break;
            }
            write("Your mind begins to clear and your vision returns "+
                "to normal. The whale's head gate is as solid as it "+
                "was before. Did you just imagine what happened?\n");
            return 1;
        }
        write("You swim up and rub the right eye of the whale's head. "+
            "After waiting a few moments you realize nothing is "+
            "happening.\n");
        tell_room(environment(TP),QCTNAME(TP)+" swims up and rubs "+
            "the right eye of the whale's head.\n",TP);
        return 1;
    }

    if (str == "left eye")
    {
        if (!TP->test_bit(THAL_GATEQ_DOMAIN,THAL_GATEQ_GROUP,THAL_GATEQ_BIT))
        {
            write("You swim up and rub the left eye of the whale's head. "+
                "After waiting a few moments you realize nothing is "+
                "happening.\n");
            tell_room(environment(TP),QCTNAME(TP)+" swims up and rubs "+
                "the left eye of the whale's head.\n",TP);
            return 1;
        }
        write("\nYou swim up and rub the left eye of the whale's head. "+
            "A rune suddenly appears on your left hand and begins "+
            "to glow. As your hand touches the eye the gate opens, "+
            "swallowing you up inside and closing behind you.\n\n");
        tell_room(environment(TP),QCTNAME(TP)+" swims up and rubs "+
            "the left eye of the whale's head. The mouth opens quickly "+
            "and swallows "+TP->query_objective()+" up, closing "+
            "immediately behind "+TP->query_objective()+".\n",TP);
        TP->move_living("M",THAL+"gates",0);
        tell_room(environment(TP), QCTNAME(TP) + " arrives swimming "+
            "through the gates.\n", TP);
        return 1;
    }
    NF("Rub which eye? The right eye or the left eye? <rub right eye> "+
       "<rub left eye>\n");
    return 0;
}

void
reward_gate_quest(string str)
{
    write("You extend your hand with the "+str+" "+
        "in it to the whale's head gate. Your head "+
        "begins to swirl and your eyes go blurry "+
        "once more. The whale's head gate speaks to "+
        "you again.\n\nIndeed, that is what I required "+
        "to permit you entrance beyond these walls. If "+
        "you wish to pass, simply rub my left eye. I "+
        "shall give you a mark so that I know you have "+
        "already answered my riddle.\n\nAs your eyes "+
        "and head begin to refocus, your left hand "+
        "suddenly has a burning sensation in it. You "+
        "look down to see some type of rune burning "+
        "itself into the palm of your hand. As soon as "+
        "it has finished forming, the pain stops and "+
        "the rune fades away to nothingness although "+
        "you know it is still there somehow. When "+
        "you look back at the whale's head, it has "+
        "become solid again as before and the "+str+" "+
        "is gone.\n");
    tell_room(TO, QCTNAME(TP) + " offers something "+
        "before the whale's head gate.\n", TP);
    
    TP->set_bit(THAL_GATEQ_GROUP,THAL_GATEQ_BIT);
    TP->add_exp_quest(THAL_GATEQ_EXP);
    TP->command("save");
    write("You feel a bit more experienced!\n");
    TP->remove_prop(LIVE_I_PLAYER_TOUCHED_THAL_EYE);
    TP->remove_prop(LIVE_I_PLAYER_FED_THAL_GATE);
    TP->remove_prop(LIVE_I_PLAYER_THAL_RIDDLE);
    log_file("thalassian_gate_quest", 
        capitalize(TP->query_real_name()) + 
        " gets " + THAL_GATEQ_EXP + " experience, " + 
        ctime(time()) + ".\n");
}

void
wrong_gate_quest_item()
{
    write("As you extend your hand with your "+
        "offering towards the whale's head, a "+
        "voice rings out in your head saying "+
        "'That is not the object that I seek.\n");
    tell_room(TO, QCTNAME(TP) + " offers something "+
        "before the whale's head gate.\n", TP);
}

int
feed_gate(string str)
{
    int ran_riddle, i;
    object quest_object;
    object *obj;

    if (!str)
    {
        NF("Feed what?\n");
        return 0;
    }
    if (TP->test_bit(THAL_GATEQ_DOMAIN,THAL_GATEQ_GROUP,THAL_GATEQ_BIT))
    {
        write("You have already fed the gates what they required.\n");
        return 1;
    }

    if(TP->query_prop(LIVE_I_PLAYER_TOUCHED_THAL_EYE))
    {
        ran_riddle=TP->query_prop(LIVE_I_PLAYER_THAL_RIDDLE);
        switch (ran_riddle)
        {
            case 1:
                parse_command(str,TP, "[the] %o [to] [the] %s]",obj,str);
                                    
                if (!objectp(obj)) 
                {
                    NF("You have no such object.\n");
                    return 0;
                    break;
                }
                
                if (!strlen(str)) 
                {
                    NF("Feed object to what?\n");
                    return 0;
                    break;
                }
                
                if (!present("_dolphin_eyeball_", TP))
                {
                    NF("The gates do not accept that item.\n");                
                    return 0;
                    break;
                }
                    
                if (obj->query_name() == "_dolphin_eyeball_")
                {
                    quest_object = present("_dolphin_eyeball_", TP);
                    quest_object->remove_object();
                    reward_gate_quest("dolphin eyeball");
                    return 1;
                    break;
                }

                wrong_gate_quest_item();
                return 1;
                break;
            case 2:
                parse_command(str,TP, "[the] %o [to] [the] %s]",obj,str);
                                    
                if (!objectp(obj)) 
                {
                    NF("You have no such object.\n");
                    return 0;
                    break;
                }
                
                if (!strlen(str)) 
                {
                    NF("Feed object to what?\n");
                    return 0;
                    break;
                }

                if (!present("_turtle_neck_", TP))
                {
                    NF("The gates do not accept that item.\n");                 
                    return 0;
                    break;
                }
                    
                if (obj->query_name() == "_turtle_neck_")
                {
                    quest_object = present("_turtle_neck_", TP);
                    quest_object->remove_object();
                    reward_gate_quest("turtle neck");
                    return 1;
                    break;
                }

                wrong_gate_quest_item();
                return 1;
                break;
            case 3:
                parse_command(str,TP, "[the] %o [to] [the] %s]",obj,str);
                                    
                if (!objectp(obj)) 
                {
                    NF("You have no such object.\n");
                    return 0;
                    break;
                }
                
                if (!strlen(str)) 
                {
                    NF("Feed object to what?\n");
                    return 0;
                    break;
                }

                if (!present("_eel_skin_", TP))
                {
                    NF("The gates do not accept that item.\n");                 
                    return 0;
                    break;
                }

                if (obj->query_name() == "_eel_skin_")
                {
                    quest_object = present("_eel_skin_", TP);
                    quest_object->remove_object();
                    reward_gate_quest("eel skin");
                    return 1;
                    break;
                }
                wrong_gate_quest_item();
                return 1;
                break;
            case 4:
                parse_command(str,TP, "[the] %o [to] [the] %s]",obj,str);
                                    
                if (!objectp(obj)) 
                {
                    NF("You have no such object.\n");
                    return 0;
                    break;
                }
                
                if (!strlen(str)) 
                {
                    NF("Feed object to what?\n");
                    return 0;
                    break;
                }
                 
                if (!present("_toad_legs_", TP))
                {
                    NF("The gates do not accept that item.\n");                 
                    return 0;
                    break;
                }

                if (obj->query_name() == "_toad_legs_")
                {
                    quest_object = present("_toad_legs_", TP);
                    quest_object->remove_object();
                    reward_gate_quest("toad legs");
                    return 1;
                    break;
                }
                wrong_gate_quest_item();
                return 1;
                break;
            default:
                parse_command(str,TP, "[the] %o [to] [the] %s]",obj,str);
                                    
                if (!objectp(obj)) 
                {
                    NF("You have no such object.\n");
                    return 0;
                    break;
                }
                
                if (!strlen(str)) 
                {
                    NF("Feed object to what?\n");
                    return 0;
                    break;
                }

                if (!present("_shark_fin_", TP))
                {
                    NF("The gates do not accept that item.\n");                 
                    return 0;
                    break;
                }

                if (obj->query_name() == "_shark_fin_")
                {
                    quest_object = present("_shark_fin_", TP);
                    quest_object->remove_object();
                    reward_gate_quest("shark fin");
                    return 1;
                    break;
                }
                wrong_gate_quest_item();
                return 1;
                break;

        }

        return 0;
    }
    
    NF("Why would you feed anything to the gates?\n");
    return 0;
}
