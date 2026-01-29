
/* 	Major Zone of Thalassia
        Psuchae Statue

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar
                23. 8.03    added guru quest for Spirit
                            Circle                          Jaacar
                04. 9.03    added entrance quest for 
                            Spirit Circle                   Jaacar
*/

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"
#include SEA_QUESTS
#include SPIRIT_HEADER

inherit "/d/Calia/std/water_room";

#define SPIRIT_OBJECTS "/d/Calia/guilds/scop/objects/"
#define ELEMENTALIST_OBJS "/d/Calia/guilds/elementalists/objs/"
#define GUILD_MANAGER "/d/Calia/guilds/elementalists/lib/guild_manager"
#define LIVE_I_PLACED_CLERIC_CYLINDER "_live_i_placed_cleric_cylinder"
#define LIVE_I_PLACED_CLERIC_TRIANGLE "_live_i_placed_cleric_triangle"
#define LIVE_I_PLACED_CLERIC_SYMBOL   "_live_i_placed_cleric_symbol"
#define LIVE_I_ON_CLERIC_GURU_QUEST   "_live_i_on_cleric_guru_quest"

int EC_GURU_GROUP = SCOP_GURU_BIT;
int EC_GURU_BIT = SCOP_GURU_BIT;

void
create_water_room()
{
    set_short("Major Zone of Thalassia");
    set_long("You are swimming around in the Major Zone of "+
        "Thalassia. This is the largest area of the "+
        "entire city and is almost entirely decorated with "+
        "white marble and bronze. There are roads leading off to "+
        "the west, east, southwest, south and southeast. Surrounding "+
        "you on the northern side you see the bronze wall that "+
        "encompasses the entire Major Zone. It shines brightly in "+
        "the light giving everything around an almost bronze tint. "+
        "There is a statue on a pedestal here.\n");

    add_item("pedestal","There is a white marble pedestal here with "+
        "a statue sitting on top of it.\n");

    add_item(({"wall","bronze wall","northeast","north","northwest",
        "northeast wall","north wall","northeast"}),"This shiny "+
        "metal surrounds the wall that encompasses the entire Major "+
        "Zone, except where the bridges pass through it.\n"); 

    add_item(({"road","roads"}),"The roads are constructed of "+
        "polished white marble and have been carefully placed so "+
        "no vegitation grows between where the slabs have been "+
        "placed. The slabs themselves are a perfectly square, "+
        "measuring at least a bodies length on each side. The "+
        "road leads off to the west, east, southwest, south "+
        "and southeast.\n");

    add_item("statue","This statue is fairly large, but you cannot "+
        "really tell how big it is because the edges seem to expand "+
        "and contract on their own at random intervals. The statue itself "+
        "is made from some sort of dark stone-like material that absorbs "+
        "almost all of the light in the area. It depicts a figure "+
        "shrouded in a black cloak of shadow. The statue is about eight "+
        "feet tall and three feet wide at the base. The eyes of the statue "+
        "are a deep piercing black and seem to be searching your soul.\n");

    add_swim_exit(THALM+"major26","west",0,1);
    add_swim_exit(THALM+"major30","east",0,1);
    add_swim_exit(THALM+"major27","southwest",0,1);
    add_swim_exit(THALM+"major29","south",0,1);
    add_swim_exit(THALM+"major31","southeast",0,1);
}

int
is_spirit(object living)
{
    return living->query_guild_name_occ() == SPIRIT_GUILD_NAME;
}

int
is_cleric(object living)
{
	return living->query_guild_name_occ() == "Elemental Clerics of Calia";
}

int
do_pray(string str)
{
    int diety;
    string cdiety;
    object triangle, cylinder, scroll, pyros_staff, gu_staff;
    object diabrecho_staff, aeria_staff;

    if ((!str) || (lower_case(str) != "to psuchae"))
    {
        NF("Pray to whom? Psuchae perhaps?\n");
        return 0;
    }
    
    if (present("_schosen_",TP))
    {
        if (!TP->query_prop(LIVE_I_PRAYED_AT_PSUCHAE_STATUE))
        {
            if (present("_psuchae_staff_",TP))
            {
                write("You begin to pray to Psuchae. You feel a presence "+
                    "come over you, a strong presence. You glance up at the "+
                    "eyes of the statue and see that they are looking back "+
                    "down at you. You quickly rub your eyes to make sure you "+
                    "are not imagining it and upon looking again, you see the "+
                    "statue of Psuchae blink. A smile comes across the face "+
                    "of the statue and you feel an inner peace come over you. "+
                    "A telepathic voice echoes in your mind,\n\n"+
                    "\"Follow the instructions written "+
                    "upon the scroll and I shall see you soon.\""+
                    "The statue returns to normal, as before.\n");
                say(QCTNAME(TP)+" prays before the statue.\n");
                return 1;
            }

            write("You begin to pray to Psuchae. You feel a presence "+
                "come over you, a strong presence. You glance up at the "+
                "eyes of the statue and see that they are looking back "+
                "down at you. You quickly rub your eyes to make sure you "+
                "are not imagining it and upon looking again, you see the "+
                "statue of Psuchae blink. A smile comes across the face "+
                "of the statue and you feel an inner peace come over you. "+
                "A telepathic voice echoes in your mind,\n\n"+
                "\"Welcome Enlightened One. You have come before me this "+
                "day because you seek to join my Spirit Circle. You shall "+
                "need to perform a task before you can do so. I shall give "+
                "you a scroll. It shall instruct you on all that you need "+
                "to do before you shall visit me in my realm. You will also "+
                "require these staves to complete your task, so I shall "+
                "give you them as well. Follow the instructions written "+
                "upon the scroll and I shall see you soon.\""+
                "\n\nThe statue hands you a scroll and four staves.\n"+
                "You blink your eyes in disbelief at what has just taken "+
                "place. When you look again at the statue, you notice "+
                "that it has returned to normal, a statue, just as "+
                "before.\n");
            say(QCTNAME(TP)+" prays before the statue.\n");
            
            TP->add_prop(LIVE_I_PRAYED_AT_PSUCHAE_STATUE,1);
            scroll = clone_object(SPIRIT_OBJECTS+"psuchae_scroll");
            pyros_staff = clone_object(SPIRIT_OBJECTS+"pyros_staff");
            gu_staff = clone_object(SPIRIT_OBJECTS+"gu_staff");
            diabrecho_staff = clone_object(SPIRIT_OBJECTS+"diabrecho_staff");
            aeria_staff = clone_object(SPIRIT_OBJECTS+"aeria_staff");
            scroll->move(TP,1);
            pyros_staff->move(TP,1);
            gu_staff->move(TP,1);
            diabrecho_staff->move(TP,1);
            aeria_staff->move(TP,1);
            return 1;
        }

        else
        {
            write("You begin to pray to Psuchae. You feel a presence "+
                "come over you, a strong presence. You glance up at the "+
                "eyes of the statue and see that they are looking back "+
                "down at you. You quickly rub your eyes to make sure you "+
                "are not imagining it and upon looking again, you see the "+
                "statue of Psuchae blink. A smile comes across the face "+
                "of the statue and you feel an inner peace come over you. "+
                "A telepathic voice echoes in your mind,\n\n"+
                "\"Follow the instructions written "+
                "upon the scroll and I shall see you soon.\""+
                "The statue returns to normal, as before.\n");
            say(QCTNAME(TP)+" prays before the statue.\n");
            return 1;
        }
    }

    if (TP->test_bit("Calia",SCOP_GURU_GROUP,SCOP_GURU_BIT))
    {
        write("You begin to pray to Psuchae. You feel a presence "+
            "come over you, a strong presence. You glance up at the "+
            "eyes of the statue and see that they are looking back "+
            "down at you. You quickly rub your eyes to make sure you "+
            "are not imagining it and upon looking again, you see the "+
            "statue of Psuchae blink. A smile comes across the face "+
            "of the statue and you feel an inner peace come over you. "+
            "The statue returns to normal, as before.\n");
        say(QCTNAME(TP)+" prays before the statue.\n");
        return 1;
    }

    if (is_spirit(TP))
    {
        diety = TP->query_skill(SS_PATRON_ELEMENTAL);

        if (TP->query_prop(LIVE_I_PLACED_SPIRIT_CYLINDER))
        {
            write("You begin to pray to Psuchae. You feel a presence "+
                "come over you, a strong presence. You glance up at the "+
                "eyes of the statue and see that they are looking back "+
                "down at you. You quickly rub your eyes to make sure you "+
                "are not imagining it and upon looking again, you see the "+
                "statue of Psuchae blink. A smile comes across the face "+
                "of the statue and you feel an inner peace come over you. "+
                "The statue returns to normal, as before.\n");
            say(QCTNAME(TP)+" prays before the statue.\n");
            return 1;
        }

        if (TP->query_prop(LIVE_I_PLACED_SPIRIT_TRIANGLE))
        {
            if (!present("_psuchae_cylinder_",TP))
            {
                write("You begin to pray to Psuchae with all of your "+
                    "heart and soul. You quickly become dizzy as the room "+
                    "appears to begin swirling rapidly around you. It "+
                    "becomes difficult to see as your eyes glaze over. As "+
                    "quickly as it came over you, the feeling stops and "+
                    "everything is clear again. You look up at the statue "+
                    "of Psuchae and notice it has changed, Psuchae "+
                    "is alive! It glances downward at you, smiling. It "+
                    "extends it's hand towards you and gently touches your "+
                    "head briefly. A telepathic voice echoes in your mind,\n\n"+
                    "\"Welcome my child. You have come before me because "+
                    "the spirit in the black obelisk has asked you to. The "+
                    "spirit must be freed from it's prison inside of the "+
                    "black obelisk. Take this, it will help you in your "+
                    "quest to free the spirit. Go now, free the spirit.\""+
                    "\n\nThe statue hands you something.\n"+
                    "The feeling of dizziness returns, your eyes blur over, "+
                    "everything is spinning again. The feeling stops, you "+
                    "look back to the statue and everything has returned "+
                    "to how it originally was. The statue is just that, "+
                    "merely a statue once again.\n");
                say(QCTNAME(TP)+" prays before the statue. "+
                    capitalize(HIS(TP))+" eyes glaze over but quickly "+
                    "return to normal after just a few moments.\n");
                cylinder = clone_object(SPIRIT_OBJECTS+"psuchae_cylinder");
                cylinder->move(TP,1);
                return 1;
            }

            else
            {
                write("You begin to pray to Psuchae. You feel a presence "+
                    "come over you, a strong presence. You glance up at the "+
                    "eyes of the statue and see that they are looking back "+
                    "down at you. You quickly rub your eyes to make sure you "+
                    "are not imagining it and upon looking again, you see the "+
                    "statue of Psuchae blink. A smile comes across the face "+
                    "of the statue and you feel an inner peace come over you. "+
                    "The statue returns to normal, as before.\n");
                say(QCTNAME(TP)+" prays before the statue.\n");
                return 1;
            }
        }

        if (TP->query_prop(LIVE_I_ON_SPIRIT_GURU_QUEST) && (!diety))
        {
            if (!present("_psuchae_triangle_",TP))
            {
                write("You begin to pray to Psuchae with all of your "+
                    "heart and soul. You quickly become dizzy as the room "+
                    "appears to begin swirling rapidly around you. It "+
                    "becomes difficult to see as your eyes glaze over. As "+
                    "quickly as it came over you, the feeling stops and "+
                    "everything is clear again. You look up at the statue "+
                    "of Psuchae and notice it has changed, Psuchae "+
                    "is alive! It glances downward at you, smiling. It "+
                    "extends it's hand towards you and gently touches your "+
                    "head briefly. A telepathic voice echoes in your mind,\n\n"+
                    "\"Welcome my child. You have come before me because "+
                    "the spirit in the black obelisk has asked you to. The "+
                    "spirit must be freed from it's prison inside of the "+
                    "black obelisk. Take this, it will help you in your "+
                    "quest to free the spirit. Go now, free the spirit.\"."+
                    "\n\nThe statue hands you something.\n"+
                    "The feeling of dizziness returns, your eyes blur over, "+
                    "everything is spinning again. The feeling stops, you "+
                    "look back to the statue and everything has returned "+
                    "to how it originally was. The statue is just that, "+
                    "merely a statue once again.\n");
                say(QCTNAME(TP)+" prays before the statue. "+
                    capitalize(HIS(TP))+" eyes glaze over but quickly "+
                    "return to normal after just a few moments.\n");
                triangle = clone_object(SPIRIT_OBJECTS+"psuchae_triangle");
                triangle->move(TP,1);
                return 1; 
            }
            else
            {
                write("You begin to pray to Psuchae. You feel a "+
                    "presence come over you, a strong presence. A "+
                    "telepathic voice echoes in your mind saying: \"You "+
                    "already possess all that I can give you. Go now, "+
                    "free the spirit.\".\n");
                say(QCTNAME(TP)+" prays before the statue briefly.\n");
                return 1;
            }
        }

        write("You begin to pray to Psuchae. You feel a presence "+
            "come over you, a strong presence. You glance up at the "+
            "eyes of the statue and see that they are looking back "+
            "down at you. You quickly rub your eyes to make sure you "+
            "are not imagining it and upon looking again, you see the "+
            "statue of Psuchae blink. A smile comes across the face "+
            "of the statue and you feel an inner peace come over you. "+
            "The statue returns to normal, as before.\n");
        say(QCTNAME(TP)+" prays before the statue.\n");
        return 1;
    }

    if (is_cleric(TP))
    {
        cdiety = GUILD_MANAGER->query_primary_element(TP->query_real_name());

        if (TP->query_prop(LIVE_I_PLACED_CLERIC_CYLINDER))
        {
            write("You begin to pray to Psuchae. You feel a presence "+
                "come over you, a strong presence. You glance up at the "+
                "eyes of the statue and see that they are looking back "+
                "down at you. You quickly rub your eyes to make sure you "+
                "are not imagining it and upon looking again, you see the "+
                "statue of Psuchae blink. A smile comes across the face "+
                "of the statue and you feel an inner peace come over you. "+
                "The statue returns to normal, as before.\n");
            say(QCTNAME(TP)+" prays before the statue.\n");
            return 1;
        }

        if (TP->query_prop(LIVE_I_PLACED_CLERIC_TRIANGLE))
        {
            if (!present("_psuchae_cylinder_",TP))
            {
                write("You begin to pray to Psuchae with all of your "+
                    "heart and soul. You quickly become dizzy as the room "+
                    "appears to begin swirling rapidly around you. It "+
                    "becomes difficult to see as your eyes glaze over. As "+
                    "quickly as it came over you, the feeling stops and "+
                    "everything is clear again. You look up at the statue "+
                    "of Psuchae and notice it has changed, Psuchae "+
                    "is alive! It glances downward at you, smiling. It "+
                    "extends it's hand towards you and gently touches your "+
                    "head briefly. A telepathic voice echoes in your mind,\n\n"+
                    "\"Welcome my child. You have come before me because "+
                    "the spirit in the obelisk has asked you to. The "+
                    "spirit must be freed from it's prison inside of the "+
                    "obelisk. Take this, it will help you in your "+
                    "quest to free the spirit. Go now, free the spirit.\""+
                    "\n\nThe statue hands you something.\n"+
                    "The feeling of dizziness returns, your eyes blur over, "+
                    "everything is spinning again. The feeling stops, you "+
                    "look back to the statue and everything has returned "+
                    "to how it originally was. The statue is just that, "+
                    "merely a statue once again.\n");
                say(QCTNAME(TP)+" prays before the statue. "+
                    capitalize(HIS(TP))+" eyes glaze over but quickly "+
                    "return to normal after just a few moments.\n");
                cylinder = clone_object(ELEMENTALIST_OBJS+"psuchae_cylinder");
                cylinder->move(TP,1);
                return 1;
            }

            else
            {
                write("You begin to pray to Psuchae. You feel a presence "+
                    "come over you, a strong presence. You glance up at the "+
                    "eyes of the statue and see that they are looking back "+
                    "down at you. You quickly rub your eyes to make sure you "+
                    "are not imagining it and upon looking again, you see the "+
                    "statue of Psuchae blink. A smile comes across the face "+
                    "of the statue and you feel an inner peace come over you. "+
                    "The statue returns to normal, as before.\n");
                say(QCTNAME(TP)+" prays before the statue.\n");
                return 1;
            }
        }

        if (TP->query_prop(LIVE_I_ON_CLERIC_GURU_QUEST) && cdiety == "life")
        {
            if (!present("_psuchae_triangle_",TP))
            {
                write("You begin to pray to Psuchae with all of your "+
                    "heart and soul. You quickly become dizzy as the room "+
                    "appears to begin swirling rapidly around you. It "+
                    "becomes difficult to see as your eyes glaze over. As "+
                    "quickly as it came over you, the feeling stops and "+
                    "everything is clear again. You look up at the statue "+
                    "of Psuchae and notice it has changed, Psuchae "+
                    "is alive! It glances downward at you, smiling. It "+
                    "extends it's hand towards you and gently touches your "+
                    "head briefly. A telepathic voice echoes in your mind,\n\n"+
                    "\"Welcome my child. You have come before me because "+
                    "the spirit in the obelisk has asked you to. The "+
                    "spirit must be freed from it's prison inside of the "+
                    "obelisk. Take this, it will help you in your "+
                    "quest to free the spirit. Go now, free the spirit.\"."+
                    "\n\nThe statue hands you something.\n"+
                    "The feeling of dizziness returns, your eyes blur over, "+
                    "everything is spinning again. The feeling stops, you "+
                    "look back to the statue and everything has returned "+
                    "to how it originally was. The statue is just that, "+
                    "merely a statue once again.\n");
                say(QCTNAME(TP)+" prays before the statue. "+
                    capitalize(HIS(TP))+" eyes glaze over but quickly "+
                    "return to normal after just a few moments.\n");
                triangle = clone_object(ELEMENTALIST_OBJS+"psuchae_triangle");
                triangle->move(TP,1);
                return 1; 
            }
            else
            {
                write("You begin to pray to Psuchae. You feel a "+
                    "presence come over you, a strong presence. A "+
                    "telepathic voice echoes in your mind saying: \"You "+
                    "already possess all that I can give you. Go now, "+
                    "free the spirit.\".\n");
                say(QCTNAME(TP)+" prays before the statue briefly.\n");
                return 1;
            }
        }

        write("You begin to pray to Psuchae. You feel a presence "+
            "come over you, a strong presence. You glance up at the "+
            "eyes of the statue and see that they are looking back "+
            "down at you. You quickly rub your eyes to make sure you "+
            "are not imagining it and upon looking again, you see the "+
            "statue of Psuchae blink. A smile comes across the face "+
            "of the statue and you feel an inner peace come over you. "+
            "The statue returns to normal, as before.\n");
        say(QCTNAME(TP)+" prays before the statue.\n");
        return 1;
    }
    
    write("You begin to pray to Psuchae. You feel a presence "+
          "come over you, a strong presence. You glance up at the eyes "+
          "of the statue and you somehow know they are watching you. "+
          "You sense an inner peace come over you.\n");
    say(QCTNAME(TP)+" prays before the statue.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_pray,"pray");
}

