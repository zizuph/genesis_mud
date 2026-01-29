
/* 	Major Zone of Thalassia
        Aeria Statue

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar
                23. 8.03    added guru quest for Spirit
                            Circle                          Jaacar
                8. 9.03     added Create Staff quest        Jaacar
                5. 4.09     added message to show gained xp Petros
                2  9 10     typo                            Lavellan
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
#define STAFF_QUEST_LOG "thalassia_staff_quest_log"
#define BREAK_LOG "/d/Calia/log/aeria_staff_break_log"
#define RECOVERED "/d/Calia/log/recovered_aeria_staff_log"
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
    citizen[j] = clone_object(SEA_CREATURES+"thalassian_swimming_triton");
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
        "the northeast, east, south and southeast. Surrounding "+
        "you on the northwestern side you see the bronze wall that "+
        "encompasses the entire Major Zone. It shines brightly in "+
        "the light giving everything around an almost bronze tint. "+
        "There is a statue on a pedestal here.\n");

    add_item("pedestal","There is a white marble pedestal here with "+
        "a statue sitting on top of it.\n");

    add_item(({"wall","bronze wall","northwest","north",
        "northwest wall","north wall"}),"This shiny "+
        "metal surrounds the wall that encompasses the entire Major "+
        "Zone, except where the bridges pass through it.\n"); 

    add_item(({"road","roads"}),"The roads are constructed of "+
        "polished white marble and have been carefully placed so "+
        "no vegitation grows between where the slabs have been "+
        "placed. The slabs themselves are a perfectly square, "+
        "measuring at least a bodies length on each side. The "+
        "road leads off to the northeast, east, south "+
        "and southeast.\n");

    add_item("statue","This statue is very large. It is carved out "+
        "of a transparent crystal, glowing with power. It depicts a "+
        "lady floating above the lands, watching over her people. "+
        "It measures about four feet across at the base of the clouds, "+
        "and stands about six feet high at its highest point. The "+
        "eyes of the statue seem to sparkle an emerald green.\n");

    add_swim_exit(THALM+"major20","northeast",0,1);
    add_swim_exit(THALM+"major19","east",0,1);
    add_swim_exit(THALM+"major16","south",0,1);
    add_swim_exit(THALM+"major17","southeast",0,1);
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

    if ((!str) || (lower_case(str) != "to lady aeria"))
    {
        NF("Pray to whom? Lady Aeria perhaps?\n");
        return 0;
    }
    
    if (is_worship(TP))
    {
        diety = TP->query_skill(SS_PATRON_ELEMENTAL);

        if (diety == AIR_FLAG && 
            !(TP->query_prop(LIVE_I_PRAYED_AT_AERIA_STATUE)))
        {
            write("You begin to pray to Lady Aeria with all of your "+
                "heart and soul. You quickly become dizzy as the room "+
                "appears to begin swirling rapidly around you. It becomes "+
                "difficult to see as your eyes glaze over. As quickly as it "+
                "came over you, the feeling stops and everything is clear "+
                "again. You look up at the statue of Lady Aeria and "+
                "notice it has changed, Lady Aeria is alive! She glances "+
                "downward at you, smiling. She extends her hand towards "+
                "you and gently touches your head briefly. In a gentle voice "+
                "you hear her speak,\n\n"+
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
            TP->add_prop(LIVE_I_PRAYED_AT_AERIA_STATUE,1);
            return 1;
        }

        write("You begin to pray to Lady Aeria. You feel a presence "+
            "come over you, a strong presence. You glance up at the "+
            "eyes of the statue and see that they are looking back "+
            "down at you. You quickly rub your eyes to make sure you "+
            "are not imagining it and upon looking again, you see the "+
            "statue of Lady Aeria blink. A smile comes across the face "+
            "of the statue and you feel an inner peace come over you. "+
            "The statue returns to normal, as before.\n");
        say(QCTNAME(TP)+" prays before the statue.\n");
        return 1;
    }

    if (is_spirit(TP))
    {
        if (TP->test_bit("Calia",SCOP_GURU_GROUP,SCOP_GURU_BIT))
        {
            write("You begin to pray to Lady Aeria. You feel a presence "+
                "come over you, a strong presence. You glance up at the "+
                "eyes of the statue and see that they are looking back "+
                "down at you. You quickly rub your eyes to make sure you "+
                "are not imagining it and upon looking again, you see the "+
                "statue of Lady Aeria blink. A smile comes across the face "+
                "of the statue and you feel an inner peace come over you. "+
                "The statue returns to normal, as before.\n");
            say(QCTNAME(TP)+" prays before the statue.\n");
            return 1;
        }

        diety = TP->query_skill(SS_PATRON_ELEMENTAL);

        if (TP->query_prop(LIVE_I_PLACED_SPIRIT_TRIANGLE))
        {
            write("You begin to pray to Lady Aeria. You feel a presence "+
                "come over you, a strong presence. You glance up at the "+
                "eyes of the statue and see that they are looking back "+
                "down at you. You quickly rub your eyes to make sure you "+
                "are not imagining it and upon looking again, you see the "+
                "statue of Lady Aeria blink. A smile comes across the face "+
                "of the statue and you feel an inner peace come over you. "+
                "The statue returns to normal, as before.\n");
            say(QCTNAME(TP)+" prays before the statue.\n");
            return 1;
        }

        if (TP->query_prop(LIVE_I_ON_SPIRIT_GURU_QUEST) && diety == AIR_FLAG)
        {
            if (!present("_aeria_triangle_",TP))
            {
                write("You begin to pray to Lady Aeria with all of your "+
                    "heart and soul. You quickly become dizzy as the room "+
                    "appears to begin swirling rapidly around you. It "+
                    "becomes difficult to see as your eyes glaze over. As "+
                    "quickly as it came over you, the feeling stops and "+
                    "everything is clear again. You look up at the statue "+
                    "of Lady Aeria and notice it has changed, Lady Aeria "+
                    "is alive! She glances downward at you, smiling. She "+
                    "extends her hand towards you and gently touches your "+
                    "head briefly. In a gentle voice you hear her speak,\n\n"+
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
                triangle = clone_object(SPIRIT_OBJECTS+"aeria_triangle");
                triangle->move(TP,1);
                return 1; 
            }
            else
            {
                write("You begin to pray to Lady Aeria. You feel a "+
                    "presence come over you, a strong presence. A "+
                    "gentle voice echoes in your mind saying: \"You "+
                    "already possess all that I can give you. Go now, "+
                    "free the spirit.\"\n");
                say(QCTNAME(TP)+" prays before the statue briefly.\n");
                return 1;
            }
        }

        write("You begin to pray to Lady Aeria. You feel a presence "+
            "come over you, a strong presence. You glance up at the "+
            "eyes of the statue and see that they are looking back "+
            "down at you. You quickly rub your eyes to make sure you "+
            "are not imagining it and upon looking again, you see the "+
            "statue of Lady Aeria blink. A smile comes across the face "+
            "of the statue and you feel an inner peace come over you. "+
            "The statue returns to normal, as before.\n");
        say(QCTNAME(TP)+" prays before the statue.\n");
        return 1;
    }
    
    if (is_cleric(TP))
    {
        if (TP->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT))
        {
            write("You begin to pray to Lady Aeria. You feel a presence "+
                "come over you, a strong presence. You glance up at the "+
                "eyes of the statue and see that they are looking back "+
                "down at you. You quickly rub your eyes to make sure you "+
                "are not imagining it and upon looking again, you see the "+
                "statue of Lady Aeria blink. A smile comes across the face "+
                "of the statue and you feel an inner peace come over you. "+
                "The statue returns to normal, as before.\n");
            say(QCTNAME(TP)+" prays before the statue.\n");
            return 1;
        }

        cdiety = GUILD_MANAGER->query_primary_element(TP->query_real_name());

        if (TP->query_prop(LIVE_I_PLACED_CLERIC_TRIANGLE))
        {
            write("You begin to pray to Lady Aeria. You feel a presence "+
                "come over you, a strong presence. You glance up at the "+
                "eyes of the statue and see that they are looking back "+
                "down at you. You quickly rub your eyes to make sure you "+
                "are not imagining it and upon looking again, you see the "+
                "statue of Lady Aeria blink. A smile comes across the face "+
                "of the statue and you feel an inner peace come over you. "+
                "The statue returns to normal, as before.\n");
            say(QCTNAME(TP)+" prays before the statue.\n");
            return 1;
        }

        if (TP->query_prop(LIVE_I_ON_CLERIC_GURU_QUEST) && cdiety == "air")
        {
            if (!present("_aeria_triangle_",TP))
            {
                write("You begin to pray to Lady Aeria with all of your "+
                    "heart and soul. You quickly become dizzy as the room "+
                    "appears to begin swirling rapidly around you. It "+
                    "becomes difficult to see as your eyes glaze over. As "+
                    "quickly as it came over you, the feeling stops and "+
                    "everything is clear again. You look up at the statue "+
                    "of Lady Aeria and notice it has changed, Lady Aeria "+
                    "is alive! She glances downward at you, smiling. She "+
                    "extends her hand towards you and gently touches your "+
                    "head briefly. In a gentle voice you hear her speak,\n\n"+
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
                triangle = clone_object(ELEMENTALIST_OBJS+"aeria_triangle");
                triangle->move(TP,1);
                return 1; 
            }
            else
            {
                write("You begin to pray to Lady Aeria. You feel a "+
                    "presence come over you, a strong presence. A "+
                    "gentle voice echoes in your mind saying: \"You "+
                    "already possess all that I can give you. Go now, "+
                    "free the spirit.\"\n");
                say(QCTNAME(TP)+" prays before the statue briefly.\n");
                return 1;
            }
        }

        write("You begin to pray to Lady Aeria. You feel a presence "+
            "come over you, a strong presence. You glance up at the "+
            "eyes of the statue and see that they are looking back "+
            "down at you. You quickly rub your eyes to make sure you "+
            "are not imagining it and upon looking again, you see the "+
            "statue of Lady Aeria blink. A smile comes across the face "+
            "of the statue and you feel an inner peace come over you. "+
            "The statue returns to normal, as before.\n");
        say(QCTNAME(TP)+" prays before the statue.\n");
        return 1;
    }

    write("You begin to pray to Lady Aeria. You feel a presence "+
          "come over you, a strong presence. You glance up at the eyes "+
          "of the statue and you somehow know they are watching you. "+
          "You sense an inner peace come over you.\n");
    say(QCTNAME(TP)+" prays before the statue.\n");
    return 1;
}

int
do_offer(string str)
{
    object mirror;
    object enchanted_mirror;

    if(!str || !parse_command(str, ({}), 
        "[the] [fancy] 'mirror' [to] [the] [statue] [of] [Lady] [Aeria]"))
    {
        NF("Offer what?\n");
        return 0;
    }

    if (TP->test_bit(THAL_A_STAFF_DOMAIN,THAL_A_STAFF_GROUP,
        THAL_A_STAFF_BIT))
    {
        NF("You have already completed this quest.\n");
        return 0;
    }

    mirror = present("_fancy_mirror_",TP);
    if (!mirror)
    {
        NF("You don't have a mirror to offer.\n");
        return 0;
    }

    write("You offer the fancy mirror to Lady Aeria. You feel a "+
        "presence come over you, a strong presence. A gentle voice "+
        "echoes in your mind saying: \"You have made me a beautiful "+
        "mirror, just as I have asked of you.\"\nThe statue of Lady Aeria "+
        "looks at itself in the fancy mirror.\nA gentle voice echoes "+
        "in your mind saying: \"Yes, I look just as beautiful as always. "+
        "Now, I ask that you construct the Staff of Aeria for me. If you "+
        "do this, I shall activate it for you so that it might be of "+
        "use to you.\"\nThe statue of Lady Aeria waves its hand over "+
        "the mirror and smokey writing appears on the mirror's surface.\n"+
        "The statue of Lady Aeria hands you the mirror.\nA gentle voice "+
        "echoes in your mind saying: \"Follow the instructions written "+
        "upon that mirror. Once you have completed the task, bring the "+
        "staff back to me to activate. Good luck in your quest.\"\n");
    mirror->remove_object();
    enchanted_mirror = clone_object(SEA_OBJECTS+"enchanted_mirror");
    enchanted_mirror->move(TP,1);
    say(QCTNAME(TP)+" offers something to the statue.\n");
    log_file(STAFF_QUEST_LOG, ctime(time())+" "+TP->query_name() +" "+
        "has completed the mirror in the Create Aeria Staff quest.\n",-1);
    return 1;
}

int
do_activate(string str)
{
    object staff, mirror;
    object activated_staff;

    if(!str || !parse_command(str, ({}), "[the] 'staff'"))
    {
        NF("Activate what?\n");
        return 0;
    }

    if (TP->test_bit(THAL_A_STAFF_DOMAIN,THAL_A_STAFF_GROUP,
        THAL_A_STAFF_BIT))
    {
        NF("You have already completed this quest.\n");
        return 0;
    }

    staff = present("_unactivated_aeria_staff_",TP);
    if (!staff)
    {
        NF("You do not have the Staff of Aeria to activate.\n");
        return 0;
    }

    write("You place the runed staff on the pedestal. The staff and "+
        "the statue begin to glow brightly! The staff rises up in the "+
        "water towards the head of the statue. The statue stops glowing "+
        "just as the staff reaches a point parallel to the emerald eyes and "+
        "begins to hover there. The eye flash of power and a bright green "+
        "light pulses out from the eyes to the staff, bathing it in an "+
        "emerald glow. The pulses stop and the staff floats back down to "+
        "the pedestal. You reach out and take it.\n");
    staff->remove_object();
    mirror = present("_enchanted_mirror_",TP);
    mirror->remove_object();
    activated_staff = clone_object(SEA_OBJECTS+"aeria_staff");
    activated_staff->move(TP,1);
    say(QCTNAME(TP)+" places a staff on the pedestal. The staff and the statue "+
        "begin to glow brightly! The staff rises up in the water towards "+
        "the head of the statue. The statue stops glowing just as the "+
        "staff reaches a point parallel to the emerald eyes and begins to "+
        "hover there. The eye flash of power and a bright green "+
        "light pulses out from the eyes to the staff, bathing it in an "+
        "emerald glow. The pulses stop and the staff floats back down to "+
        "the pedestal. "+QCTNAME(TP)+" reaches out and takes it.\n");
    TP->set_bit(THAL_A_STAFF_GROUP,THAL_A_STAFF_BIT);
    TP->add_exp_quest(THAL_A_STAFF_EXP); 
    write("You feel more experienced!\n");
    TP->command("save");
    log_file(STAFF_QUEST_LOG, ctime(time())+" "+TP->query_name() +" "+
        "has completed the Create Aeria Staff quest, gaining "+
        THAL_A_STAFF_EXP+" experience.\n",-1);
    return 1;
}

int
do_devote(string str)
{
    if (!str)
        return 0;

    if (str != "myself to Lady Aeria")
        return 0;

    if (TP->test_bit(THAL_A_STAFF_DOMAIN,THAL_A_STAFF_GROUP,
        THAL_A_STAFF_BIT))
    {
        NF("You have already completed this quest.\n");
        return 0;
    }

    write("A gentle voice echoes in your mind saying: "+
        "\"I would like to offer you a gift. In order for "+
        "me to give you this gift, I need you to construct "+
        "me a mirror. Once you have constructed this mirror, "+
        "come back to here and offer it to me. To start you on "+
        "your way, you must seek out the mermaid's true love. "+
        "He will start you on your way.\"\nThe voice disappears.\n");
    say(QCTNAME(TP)+" closes "+TP->query_possessive()+" eyes for a moment.\n");
    log_file(STAFF_QUEST_LOG, ctime(time())+" "+TP->query_name() +" "+
        "has started the Create Aeria Staff quest.\n",-1);
    return 1;
}

int
do_recover(string str)
{
    object staff;
    string *losers;
    string who;
    string player_name;
    int player_len;
    int i;
    
    if (!TP->test_bit(THAL_A_STAFF_DOMAIN,THAL_A_STAFF_GROUP,THAL_A_STAFF_BIT))
    {
        NF("You have not finished the quest.\n");
        return 0;
    }

    if (present("staff of Aeria",TP))
    {
        NF("You already have your staff!\n");
        return 0;
    }

/*
    Changed April 2009 by Petros
      - The staff of Aeria can be broken when wielded by a player and used
        to fight with. This seems like an overly harsh penalty. Since it 
        not meant to be used in fights, I have made it a holdable item and
        allowed those whose staffs were broken to recover it here.

    if (file_size(BREAK_LOG) > -1)
    {
        player_name = TP->query_name();
        player_len = strlen(player_name) - 1;
        seteuid(getuid());
        losers = explode(read_file(BREAK_LOG), "\n");
        for (i = 0; i < sizeof(losers); i++)
        {
            if (extract(losers[i], 0, player_len) == player_name)
            {

                write("\nYour staff was broken and is not recoverable.\n");
                return 1;
            }
        }
    }
*/
    
    staff = clone_object("/d/Calia/sea/objects/aeria_staff");
    write("Your staff of Aeria has been restored.\n");
   
    staff->move(TP, 1);
    write_file(RECOVERED, TP->query_name() + " got a new Aeria "+
        "staff."+ctime(time())+".\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_devote,"devote");
    add_action(do_pray,"pray");
    add_action(do_offer,"offer");
    add_action(do_activate,"activate");
    add_action(do_recover,"recover");
}
