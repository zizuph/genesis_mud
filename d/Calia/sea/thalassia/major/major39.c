
/* 	Major Zone of Thalassia
        Diabrecho Statue

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar
                23. 8.03    added guru quest for Spirit
                            Circle                          Jaacar

*/

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"
#include SEA_QUESTS
#include WORSHIP_HEADER
#include SPIRIT_HEADER

#define CITIZENS 5
#define GUARDS   4
#define SPIRIT_OBJECTS "/d/Calia/guilds/scop/objects/"
#define ELEMENTALIST_OBJS "/d/Calia/guilds/elementalists/objs/"
#define GUILD_MANAGER "/d/Calia/guilds/elementalists/lib/guild_manager"
#define LIVE_I_PLACED_CLERIC_TRIANGLE "_live_i_placed_cleric_triangle"
#define LIVE_I_ON_CLERIC_GURU_QUEST   "_live_i_on_cleric_guru_quest"

inherit "/d/Calia/std/water_room";
object *guard = allocate(GUARDS);
object *citizen = allocate(CITIZENS);
int EC_GURU_GROUP = SCOP_GURU_BIT;
int EC_GURU_BIT = SCOP_GURU_BIT;

void
make_guard(int i)
{
    guard[i] = clone_object(SEA_CREATURES+"br_triton");
    guard[i]->equip_me();
    guard[i]->move(TO);
    tell_room(TO, QCTNAME(guard[i]) + " arrives.\n");
}

void
make_citizen(int j)
{
    citizen[j] = clone_object(SEA_CREATURES+"thalassian_swimming_mermaid");
    citizen[j]->move(TO);
    tell_room(TO, QCTNAME(citizen[j]) + " arrives.\n");
}

void
reset_room()
{
    int i,j;

    for (i=0; i < GUARDS; i++)
    {
        if (!guard[i])
            set_alarm(0.5, 0.0, &make_guard(i));
    }

    for (j-0; j < CITIZENS; j++)
    {
        if (!citizen[j])
            set_alarm(0.5,0.0,&make_citizen(j));
    }
}

void
create_water_room()
{
    set_short("Major Zone of Thalassia");
    set_long("You are swimming around in the Major Zone of "+
        "Thalassia. This is the largest area of the "+
        "entire city and is almost entirely decorated with "+
        "white marble and bronze. There are roads leading off to "+
        "the northwest, west, southwest and south. Surrounding "+
        "you on the northeastern side you see the bronze wall that "+
        "encompasses the entire Major Zone. It shines brightly in "+
        "the light giving everything around an almost bronze tint. "+
        "There is a statue on a pedestal here.\n");

    add_item("pedestal","There is a white marble pedestal here with "+
        "a statue sitting on top of it.\n");

    add_item(({"wall","bronze wall","northeast","north",
        "northeast wall","north wall"}),"This shiny "+
        "metal surrounds the wall that encompasses the entire Major "+
        "Zone, except where the bridges pass through it.\n"); 

    add_item(({"road","roads"}),"The roads are constructed of "+
        "polished white marble and have been carefully placed so "+
        "no vegitation grows between where the slabs have been "+
        "placed. The slabs themselves are a perfectly square, "+
        "measuring at least a bodies length on each side. The "+
        "road leads off to the northwest, west, southwest "+
        "and south.\n");

    add_item("statue","This statue is very large. It is carved "+
        "out of a beautiful block of ice-like stone that seems "+
        "to radiate power from within itself yet doesn't melt. It "+
        "depicts a man sitting on his throne, sceptre in hand, "+
        "surrounded by a few of his guards. It measures about five "+
        "feet across at the base of the throne, and stands "+
        "about fifteen feet high at it's highest point. "+
        "The eyes of the statue glow a bright blue.\n");

    add_swim_exit(THALM+"major37","northwest",0,1);
    add_swim_exit(THALM+"major38","west",0,1);
    add_swim_exit(THALM+"major40","southwest",0,1);
    add_swim_exit(THALM+"major41","south",0,1);
    set_alarm(1.0,0.0,"reset_room");
}

public int
clean_up()
{
    int i,j;

    for (i=0; i < GUARDS; i++)
    {
        if (guard[i])
            return 1;
    }

    for (j=0; j < CITIZENS; j++)
    {
        if (citizen[j])
            return 1;
    }

    remove_object();
}

int
is_worship(object living)
{
    return living->query_guild_name_lay() == GUILD_NAME;
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
    object triangle;

    if ((!str) || (lower_case(str) != "to lord diabrecho"))
    {
        NF("Pray to whom? Lord Diabrecho perhaps?\n");
        return 0;
    }
    
    if (is_worship(TP))
    {
        diety = TP->query_skill(SS_PATRON_ELEMENTAL);

        if (diety == WATER_FLAG && 
            !(TP->query_prop(LIVE_I_PRAYED_AT_DIABRECHO_STATUE)))
        {
            write("You begin to pray to Lord Diabrecho with all of your "+
                "heart and soul. You quickly become dizzy as the room "+
                "appears to begin swirling rapidly around you. It becomes "+
                "difficult to see as your eyes glaze over. As quickly as it "+
                "came over you, the feeling stops and everything is clear "+
                "again. You look up at the statue of Lord Diabrecho and "+
                "notice it has changed, Lord Diabrecho is alive! He glances "+
                "downward at you, smiling. He extends his hand towards "+
                "you and gently touches your head briefly. In a strong voice "+
                "you hear him speak,\n\n"+
                "\"Welcome my child. It is good to be able to lay my eyes "+
                "upon you in person. Go forth and spread the blessings of "+
                "the Elementals. Go forth and find glory in our teachings. "+
                "Go forth and embrace the destiny that awaits you.\"\n\n"+
                "The feeling of dizziness returns, your eyes blur over, "+
                "everything is spinning again. The feeling stops, you look "+
                "back to the statue and everything has returned to how it "+
                "originally was. The statue is just that, merely a statue "+
                "once again.\n");
            say(QCTNAME(TP)+" prays before the statue. "+capitalize(HIS(TP))+
                " eyes glaze over but quickly return to normal after just "+
                "a few moments.\n");
            TP->add_prop(LIVE_I_PRAYED_AT_DIABRECHO_STATUE,1);
            return 1;
        }

        write("You begin to pray to Lord Diabrecho. You feel a presence "+
            "come over you, a strong presence. You glance up at the "+
            "eyes of the statue and see that they are looking back "+
            "down at you. You quickly rub your eyes to make sure you "+
            "are not imagining it and upon looking again, you see the "+
            "statue of Lord Diabrecho blink. A smile comes across the face "+
            "of the statue and you feel an inner peace come over you. "+
            "The statue returns to normal, as before.\n");
        say(QCTNAME(TP)+" prays before the statue.\n");
        return 1;
    }

    if (is_spirit(TP))
    {
        if (TP->test_bit("Calia",SCOP_GURU_GROUP,SCOP_GURU_BIT))
        {
            write("You begin to pray to Lord Diabrecho. You feel a presence "+
                "come over you, a strong presence. You glance up at the "+
                "eyes of the statue and see that they are looking back "+
                "down at you. You quickly rub your eyes to make sure you "+
                "are not imagining it and upon looking again, you see the "+
                "statue of Lord Diabrecho blink. A smile comes across the face "+
                "of the statue and you feel an inner peace come over you. "+
                "The statue returns to normal, as before.\n");
            say(QCTNAME(TP)+" prays before the statue.\n");
            return 1;
        }

        diety = TP->query_skill(SS_PATRON_ELEMENTAL);

        if (TP->query_prop(LIVE_I_PLACED_SPIRIT_TRIANGLE))
        {
            write("You begin to pray to Lord Diabrecho. You feel a presence "+
                "come over you, a strong presence. You glance up at the "+
                "eyes of the statue and see that they are looking back "+
                "down at you. You quickly rub your eyes to make sure you "+
                "are not imagining it and upon looking again, you see the "+
                "statue of Lord Diabrecho blink. A smile comes across the face "+
                "of the statue and you feel an inner peace come over you. "+
                "The statue returns to normal, as before.\n");
            say(QCTNAME(TP)+" prays before the statue.\n");
            return 1;
        }

        if (TP->query_prop(LIVE_I_ON_SPIRIT_GURU_QUEST) && diety == WATER_FLAG)
        {
            if (!present("_diabrecho_triangle_",TP))
            {
                write("You begin to pray to Lord Diabrecho with all of your "+
                    "heart and soul. You quickly become dizzy as the room "+
                    "appears to begin swirling rapidly around you. It "+
                    "becomes difficult to see as your eyes glaze over. As "+
                    "quickly as it came over you, the feeling stops and "+
                    "everything is clear again. You look up at the statue "+
                    "of Lord Diabrecho and notice it has changed, Lord Diabrecho "+
                    "is alive! He glances downward at you, smiling. He "+
                    "extends his hand towards you and gently touches your "+
                    "head briefly. In a strong voice you hear him speak,\n\n"+
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
                triangle = clone_object(SPIRIT_OBJECTS+"diabrecho_triangle");
                triangle->move(TP,1);
                return 1; 
            }
            else
            {
                write("You begin to pray to Lord Diabrecho. You feel a "+
                    "presence come over you, a strong presence. A "+
                    "gentle voice echoes in your mind saying: \"You "+
                    "already possess all that I can give you. Go now, "+
                    "free the spirit.\".\n");
                say(QCTNAME(TP)+" prays before the statue briefly.\n");
                return 1;
            }
        }

        write("You begin to pray to Lord Diabrecho. You feel a presence "+
            "come over you, a strong presence. You glance up at the "+
            "eyes of the statue and see that they are looking back "+
            "down at you. You quickly rub your eyes to make sure you "+
            "are not imagining it and upon looking again, you see the "+
            "statue of Lord Diabrecho blink. A smile comes across the face "+
            "of the statue and you feel an inner peace come over you. "+
            "The statue returns to normal, as before.\n");
        say(QCTNAME(TP)+" prays before the statue.\n");
        return 1;
    }

    if (is_cleric(TP))
    {
        if (TP->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT))
        {
            write("You begin to pray to Lord Diabrecho. You feel a presence "+
                "come over you, a strong presence. You glance up at the "+
                "eyes of the statue and see that they are looking back "+
                "down at you. You quickly rub your eyes to make sure you "+
                "are not imagining it and upon looking again, you see the "+
                "statue of Lord Diabrecho blink. A smile comes across the face "+
                "of the statue and you feel an inner peace come over you. "+
                "The statue returns to normal, as before.\n");
            say(QCTNAME(TP)+" prays before the statue.\n");
            return 1;
        }

        cdiety = GUILD_MANAGER->query_primary_element(TP->query_real_name());

        if (TP->query_prop(LIVE_I_PLACED_CLERIC_TRIANGLE))
        {
            write("You begin to pray to Lord Diabrecho. You feel a presence "+
                "come over you, a strong presence. You glance up at the "+
                "eyes of the statue and see that they are looking back "+
                "down at you. You quickly rub your eyes to make sure you "+
                "are not imagining it and upon looking again, you see the "+
                "statue of Lord Diabrecho blink. A smile comes across the face "+
                "of the statue and you feel an inner peace come over you. "+
                "The statue returns to normal, as before.\n");
            say(QCTNAME(TP)+" prays before the statue.\n");
            return 1;
        }

        if (TP->query_prop(LIVE_I_ON_CLERIC_GURU_QUEST) && cdiety == "water")
        {
            if (!present("_diabrecho_triangle_",TP))
            {
                write("You begin to pray to Lord Diabrecho with all of your "+
                    "heart and soul. You quickly become dizzy as the room "+
                    "appears to begin swirling rapidly around you. It "+
                    "becomes difficult to see as your eyes glaze over. As "+
                    "quickly as it came over you, the feeling stops and "+
                    "everything is clear again. You look up at the statue "+
                    "of Lord Diabrecho and notice it has changed, Lord Diabrecho "+
                    "is alive! He glances downward at you, smiling. He "+
                    "extends his hand towards you and gently touches your "+
                    "head briefly. In a strong voice you hear him speak,\n\n"+
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
                triangle = clone_object(ELEMENTALIST_OBJS+"diabrecho_triangle");
                triangle->move(TP,1);
                return 1; 
            }
            else
            {
                write("You begin to pray to Lord Diabrecho. You feel a "+
                    "presence come over you, a strong presence. A "+
                    "gentle voice echoes in your mind saying: \"You "+
                    "already possess all that I can give you. Go now, "+
                    "free the spirit.\".\n");
                say(QCTNAME(TP)+" prays before the statue briefly.\n");
                return 1;
            }
        }

        write("You begin to pray to Lord Diabrecho. You feel a presence "+
            "come over you, a strong presence. You glance up at the "+
            "eyes of the statue and see that they are looking back "+
            "down at you. You quickly rub your eyes to make sure you "+
            "are not imagining it and upon looking again, you see the "+
            "statue of Lord Diabrecho blink. A smile comes across the face "+
            "of the statue and you feel an inner peace come over you. "+
            "The statue returns to normal, as before.\n");
        say(QCTNAME(TP)+" prays before the statue.\n");
        return 1;
    }
    
    write("You begin to pray to Lord Diabrecho. You feel a presence "+
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
