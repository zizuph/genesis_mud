
 /* Join/Leave room for the Elemental Worshippers of Calia
  * by Jaacar
  * July 22nd, 1996
  */

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <ss_types.h>
#include "defs.h"
#include WORSHIP_HEADER
#include COUNCIL_HEADER

#define JOIN_LOG     WOR_LOGS+"joinlog"
#define COUNCIL_LOG  WOR_LOGS+"council"

#define JOINED(x) ({"The voice of Lord Pyros echoes in your mind: "+x->query_name()+" has joined the circle.",\
        "Lady Gu's voice rings forth in your head: "+x->query_name()+" is the newest member of the circle.",\
        "Echoing through your mind you hear Lord Diabrecho say: "+x->query_name()+" has just joined the circle.",\
        "Like a small breeze in your ears you hear Lady Aeria say: "+x->query_name()+" has joined the circle."})

#define LEFT(x) ({"You hear the thunderous voice of Lord Pyros proclaim: "+x->query_name()+" has betrayed us and has been banished from the circle!",\
        "Winds howl in the voice of Lady Aeria: "+x->query_name()+" has betrayed the circle and is no longer one of us!",\
        "The ground shakes violently below you momentarily as Lady Gu speaks: "+x->query_name()+" has betrayed the Elementals and is no longer one of the circle!",\
        "You hear the angry voice of Lord Diabrecho: "+x->query_name()+" has betrayed the circle and is no longer with us!"})


#define I_PRAYED_WORSHIPPER "_i_prayed_worshipper"
#define TOOLARR ({"worshipper_wand","fire","worshipper_dagger","air","worshipper_chalice","water","worshipper_pentacle","earth"})

void betray1(object player);

string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

int
is_worship(object living)
{
    return living->query_guild_name_lay() == GUILD_NAME;
}

void
create_room()
{
    set_short("At a silver altar");
    set_long("You have entered a large section of this temple. "+
        "Before you on the ground is a pure silver altar that "+
        "shines brightly in the sunshine which enters through a "+
        "small hole in the ceiling. Its bright radiance "+
        "fills your soul with peace and happiness. Surrounding the altar "+
        "are small bushes and bright yellow flowers. There are two "+
        "archways, one in each of the southern corners of this room. "+
        "You can also head out of the room to the north.\n");

    add_item(({"ceiling","hole","small hole","roof"}),"A bright beam "+
        "of sunlight streams forth through a small hole in the ceiling. "+
        "It appears to have been cut into the roof so as the sun will "+
        "always shine upon the altar when it is high in the sky above.\n");

    add_item(({"light","sunshine","sunlight","radiance","beam"}),
        "The radiance from the beam of sunlight is almost blinding as "+
        "it reflects off of the silver altar. Heat rises off of the "+
        "altar as the sunlight warms it.\n");

    add_item(({"pure silver altar","silver altar","altar"}),
        "The altar is crafted from pure silver and is polished "+
        "brightly. There are no markings whatsoever on it at all.  "+
        "It is surrounded by some small bushes and bright yellow "+
        "flowers.\n");

    add_item(({"bush","bushes","small bush","small bushes"}),
        "These small bushes are expertly trimmed, and well taken "+
        "care of, most likely by the inhabitants of this temple.\n");

    add_item(({"flower","flowers","yellow flower","yellow flowers",
        "bright flower","bright flowers","bright yellow flower",
        "bright yellow flowers"}),"As if by some sort of magic, "+
        "these flowers are perfect in every way. They are all "+
        "exactly the same height, have the same colour stems, "+
        "and have the same yellow petals.\n");

    add_prop(ROOM_M_NO_ATTACK,1);

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_IS,1);

    add_exit(WOR_TEMPLE+"entrance","north",0,1);
    add_exit(WOR_TEMPLE+"post","southwest",0,1);
    add_exit(WOR_TEMPLE+"board","southeast","@@check_worship",1);
}

int
check_worship()
{
    // Worshippers, Spirit Circle, and Wizards can enter
    object player = this_player();
    if (player->query_wiz_level()
        || is_worship(player)
        || player->query_guild_name_occ() == "Spirit Circle of Psuchae")
    {
        return 0;
    }

    write("A voice echoes through your mind: 'Only those who "+
        "follow the Elemental ways may pass.'\n");
    return 1;
}

void
init()
{
    ::init();
    add_action("pray","pray");
    add_action("betray","betray");
    add_action("worship","worship");
    add_action("smell","smell");
}

int
smell(string str)
{
    int align;

    if (!str || !strlen(str) || (str != "flowers"))
    {
        NF("Smell what?  The flowers?\n");
        return 0;
    }
    align = this_player()->query_alignment();
    switch (align)
    {
        case -1200..-600:
            write("The flowers smell of sulphur and brimstone.\n");
            break;
        case -599..-1:
            write("The flowers smell of smoke and fire.\n");
            break;
        case 0:
            write("The flowers do not smell like anything.\n");
            break;
        case 1..599:
            write("The flowers smell sweet, like gentle roses.\n");
            break;
        default:
            write("The flowers smell like a mixture of honey suckle, "+
                "and roses.\n");
            break;
    }
    return 1;
}

int
worship(string str)
{
    if (!is_worship(TP))
    {
        notify_fail("What?\n");
        return 0;
    }
    
    if (TP->query_skill(SS_PATRON_ELEMENTAL) > 0)
    {
        write("You have already chosen your patron elemental!\n");
        return 1;
    }
    
    if (str == "pyros" ||
        str == "Pyros")
    {
        TP->set_skill(SS_PATRON_ELEMENTAL,FIRE_FLAG);
        write("The booming voice of Lord Pyros echoes through your mind: "+
            "Welcome, "+capitalize(TP->query_real_name())+"! "+
            "May you unleash the elemental flames upon all those who "+
            "stand in your way!\n");
        TP->init_worshipper_titles();
        return 1;
    }
    if (str == "gu" || str == "Gu")
    {
        TP->set_skill(SS_PATRON_ELEMENTAL,EARTH_FLAG);
        write("The ground beneath your feet rumbles as you hear the "+
            "voice of Lady Gu: Welcome, "+capitalize(TP->query_real_name())+
            "! May you compel the elemental earth in any way you need be.\n");
        TP->init_worshipper_titles();
        return 1;
    }
    if (str == "aeria" || str == "Aeria")
    {
        TP->set_skill(SS_PATRON_ELEMENTAL,AIR_FLAG);
        write("A strong wind howls around your ears in which you recognize "+
            "the voice of Lady Aeria: Welcome, "+capitalize(TP->query_real_name())+
            "! May you learn to control the elemental winds to aid you in "+
            "all of your adventures.\n");
        TP->init_worshipper_titles();
        return 1;
    }
    if (str == "diabrecho" || str == "Diabrecho")
    {
        TP->set_skill(SS_PATRON_ELEMENTAL,WATER_FLAG);
        write("Your body fluids race as the voice of Lord Diabrecho ring "+
            "in your ears: Welcome, "+capitalize(TP->query_real_name())+
            "! May you conform the elemental waters to any way you deem "+
            "necessary on your journies.\n");
        TP->init_worshipper_titles();
        return 1;
    }
    write("Worship who? Pyros, Gu, Aeria, or Diabrecho perhaps?\n");
    return 1;
}

int
betray(string str)
{

    if (!is_worship(TP))
    {
        notify_fail("You are not a member of this guild!\n");
        return 0;
    }
    if (str !="the Elementals")
    {
        notify_fail("Betray who? The Elementals?\n");
        return 0;
    }
    clone_object(PARALYZE)->move(TP,1);
    present("worshipper_chalice",TP)->remove_object();
    present("worshipper_dagger",TP)->remove_object();
    present("worshipper_pentacle",TP)->remove_object();
    present("worshipper_wand",TP)->remove_object();
    present("worshipper_sceptre",TP)->remove_object();
    present(I_CAN_CAST,TP)->remove_object();
    present(WOR_CAN_PERMIT)->remove_object();
    present(I_CAN_JOIN,TP)->remove_object();
    TP->remove_skill(SS_CARVED);
    TP->remove_skill(SS_PATRON_ELEMENTAL);
    
    TP->set_skill(SS_PUNISHMENT,3);
    write("Your Elemental Tools shatter into thousands of tiny pieces!\n");
    reset_euid();
    if (TP->query_default_start_location() == WORSTART)
        TP->set_default_start_location(TP->query_def_start());
    TP->remove_guild_lay();
    TP->clear_guild_stat(SS_LAYMAN);
    TP->remove_cmdsoul("/d/Calia/worshippers/specials/worshipsoul");
    TP->update_hooks();
    write_file(JOIN_LOG, TP->query_name()+" betrayed the Elementals on "+ctime(time()) +".\n");
    (WOR_OBJECTS+"council_log_book")->update_log_book(my_time()+
    TP->query_name()+" betrayed the Elementals.\n");
    write("The air around feels like it is closing in on you. Your "+
        "skin begins to feel very warm. Your blood temperature seems "+
        "to be rising very rapidly. You notice the area around you "+
        "begins to get darker. The ground beneath your feet rumbles "+
        "and shakes. Suddenly you find yourself surrounded by four "+
        "powerful beings, one made of earth, one of air, one of water, "+
        "and one of fire. Each seems to be invoking some terrible "+
        "spell. All goes dark.\nYou still feel the ground trembling.\n");
    tell_room(environment(TP),QCTNAME(TP)+" prays at the altar.\nSuddenly, the air "+
        "around "+TP->query_objective()+" grows very dark, the ground "+
        "beneath "+TP->query_possessive()+" feet begins to shake violently. "+
        capitalize(TP->query_possessive())+" eyes glaze over.\n",TP);
    set_alarm(2.0,0.0,&betray1(TP));
    return 1;
}

void
betray1(object player)
{
    object piece;
    string enemy_race;
    tell_object(player,"Your blood begins to boil under your skin.\n"+
        "You hear a demonic "+
        "laughter filling the air around you.\nA voice echoes in your "+
        "mind: You have betrayed us and shall now pay the ultimate price!\n"+
        "The last thing you feel is your arms and legs literally exploding "+
        "from the pressure of your boiling blood.");
    tell_room(environment(player),capitalize(player->query_pronoun())+
        " is surrounded totally by "+
        "darkness.\nThe ground shakes massively.\nSuddenly, all is back "+
        "to normal, except where "+QTNAME(player)+" was standing is now a "+
        "smouldering pile of remains.\n",player);
    if (!player->query_prop(LIVE_I_NO_CORPSE))
    {
        player->add_prop(LIVE_I_NO_CORPSE,1);
    }
    enemy_race = player->query_race_name();
    player->heal_hp(-player->query_max_hp());
    player->do_die(this_object());
    setuid();
    seteuid(getuid(this_object()));
    piece = clone_object(DEATH_OBJECT);
    piece->set_race(enemy_race);
    piece->move(WOR_TEMPLE+"s_chamber",1);
    filter(users(), &is_worship())->catch_msg(LEFT(player)[random(4)]+"\n");
}

void
do_join1(object ob)
{
    ob->catch_msg("The apparition takes a solid shape before your eyes.\n");
    tell_room(environment(ob),"Suddenly a cloud appears, and slowly "+
        "solidifies into a human shape.\n",ob);
    ob->catch_msg("The shape speaks to you: I am the Elder of The "+
        "Elemental Worshippers of Calia. I congratulate you on "+
        "proving yourself worthy of becoming one with the Elementals. "+
        "I hereby welcome you into the circle.\nThe Elder gives you a "+
        "long sceptre.\nThe Elder whispers to you: Take care of this "+
        "sceptre and of your Elemental Tools. You must now select an "+
        "Elemental to follow. Go to the library and read about each of "+
        "the Elementals, then come back here to 'worship <name>'. "+
        "You may now pass through the doors in the southern corners "+
        "of this chamber. May the Elementals guide "+
        "your way always.\nThe Elder disappears into a swirling mass of "+
        "mist.\n");
    tell_room(environment(ob),"The shape speaks to "+QTNAME(ob)+": "+
        "I am the Elder of the Elemental Worshippers of Calia. I "+
        "congratulate you on proving yourself worthy of becoming one "+
        "with the Elementals. I hereby welcome you into the circle.\n"+
        "The Elder gives something to "+QTNAME(ob)+".\nThe shape whispers "+
        "something to "+QTNAME(ob)+".\nThe shape disappears into a swirling "+
        "mass of mist.\n",ob);
    filter(users(), &is_worship())->catch_msg(JOINED(ob)[random(4)]+"\n");
    ob->add_cmdsoul("/d/Calia/worshippers/specials/worshipsoul");
    ob->set_skill(SS_CARVED,0);
    
    ob->update_hooks();
    present(I_CAN_JOIN,ob)->remove_object();
    write_file(JOIN_LOG, ob->query_name() + " joined the Elementals on " + ctime(time())+".\n");
    (WOR_OBJECTS+"council_log_book")->update_log_book(my_time()+
    ob->query_name()+" joined the Elementals.\n");
}

int
join()
{
    object shadow;
    seteuid(getuid());
    shadow=clone_object("/d/Calia/worshippers/specials/worshipshadow");
    if (shadow->shadow_me(TP,GUILD_TYPE,GUILD_STYLE,GUILD_NAME,"") != 1)
    {
        write("For some unknown reason you cannot join.\n");
        shadow->remove_shadow();
        return 0;
    }
    TP->clear_guild_stat(SS_LAYMAN);
    clone_object(WOR_OBJECTS+"sceptre")->move(TP);
    set_alarm(2.0,0.0,&do_join1(TP));
    return 1;
}

int
pray(string str)
{
    int i;
    string *missing_arr = ({});
    if (TP->query_skill(SS_PUNISHMENT) == 3)
    {
        write("A voice booms in your head:  LEAVE NOW!  You have "+
            "betrayed the Elementals!\n");
        return 1;
    }
    if (TP->query_skill(SS_PUNISHMENT) == 4)
    {
        write("You have been outcast from the Circle, and must seek "+
            "atonement before rejoining.\n");
        return 1;
    }
    if (TP->query_skill(SS_PUNISHMENT) == 5)
    {
        write("You are a member of the Spirit Circle and therefore cannot join.\n");
        return 1;
    }
    if (str != "to the Elementals")
    {
        if (TP->query_guild_member_lay())
        {
            write("You pray at the altar. You feel the Elementals "+
                "are watching over you.\n");
            return 1;
        }
        write("An apparition appears before you.\n");
        tell_room(this_object(),QCTNAME(TP)+"'s eyes "+
            "suddenly glaze over.\n",TP);
        write("The apparition speaks to you: Greetings in the name "+
            "of the Elementals.\n");
        write("The apparition speaks to you: If you wish to "+
            "become one with the Elements, 'pray to "+
            "the Elementals'.\n");
        write("The apparition disappears.\n");
        tell_room(this_object(),QCTNAME(TP)+"'s eyes return to "+
            "normal.\n",TP);
        return 1;
    }
    if (is_worship(TP))
    {
        write("An apparition appears to you and says: "+
            "Go in peace my child.\n");
        write("The apparition disappears.\n");
        return 1;
    }
    
    if (TP->query_prop(I_PRAYED_WORSHIPPER))
    {
        write("An apparition appears to you.\n");
        write("The apparition speaks to you: Greetings again, child.\n");
        if(!present(I_CAN_JOIN,TP))
        {
            write("The apparition speaks to you:  You have not yet "+
                "been accepted by a member of the Circle. Return "+
                "to me again once this has been done.\nThe apparition "+
                "disappears.\n");
            return 1;
        }

        for (i=0; i < 8; i+=2)
        {
            if(!present(TOOLARR[i], TP))
                missing_arr += ({TOOLARR[i+1]});
        }
        if (sizeof(missing_arr) == 0)
        {
            write("The apparition speaks to you: You have brought "+
                "all four of the Elemental Tools.\n");
            join();
            return 1;
        }
        write("The apparition speaks to you: You are missing "+
            "the "+(sizeof(missing_arr) > 1 ? "tools " : "tool ") +
            "of "+COMPOSITE_WORDS(missing_arr)+".\n");
        tell_room(this_object(),QCTNAME(TP)+"'s eyes suddenly glaze over.\n",TP);
        write("The apparition speaks to you: Return when you have "+
            "all four of the Elemental Tools.\n");
        tell_room(this_object(),QCTNAME(TP)+"'s eyes return to normal.\n",TP);
        return 1;
    }

    if (str == "to the Elementals")
    {
        write("An apparition appears to you.\n");
        tell_room(this_object(),QCTNAME(TP)+"'s eyes suddenly glaze over.\n",TP);
        write("The apparition speaks to you: If you are interested "+
            "in becoming one with the Elementals, then you should "+
            "seek out the library within this temple. There you "+
            "shall find information about us and what is expected "+
            "of you if you should choose to join us. You shall also "+
            "find information about four items known as the "+
            "Elemental Tools. If you truly seek to join us, then "+
            "you must prove yourself by constructing these tools "+
            "in the chamber across from the library. You must also "+
            "be accepted by a member of the Circle Council. You "+
            "can mail the council in the room located southwest "+
            "from here. Once you have "+
            "completed this, return here and you shall be entered "+
            "into the Circle.\n");
        write("The apparition disappears.\n");
        tell_room(this_object(),QCTNAME(TP)+"'s eyes return to normal.\n",TP);
        TP->add_prop(I_PRAYED_WORSHIPPER,1);
        return 1;
    }
    write("You pray at the altar but nothing happens.\n");
    return 1;
}

