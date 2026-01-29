
/*
 * joinroom.c
 *
 * The joining room for the Spirit Circle of Psuchae Temple
 * Can you guess what this is for?  Yep, you guessed it!
 * Joining the Spirit Circle of Psuchae!
 *
 * Copyright (C): Jaacar (Mike Phipps), August 1st, 2003
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <ss_types.h>

#include "defs.h"
#include SPIRIT_HEADER
#include COUNCIL_HEADER

#define JOIN_LOG     SPIRIT_LOGS+"joinlog"
#define COUNCIL_LOG  SPIRIT_LOGS+"council"
#define WOR_JOIN_LOG WORSHIP_DIR+"logs/"
#define WOR_OBJECTS  WORSHIP_DIR+"objects/"
#define I_CAN_CAST "_i_can_cast_"
#define I_CAN_JOIN "_i_can_join_"
#define WOR_CAN_PERMIT "_wor_can_permit_"

#define JOINED(x) ({"The voice of Psuchae echoes in your mind: "+ \
                     x->query_name()+" has joined the Spirit Circle."})
#define LEFT(x) ({"You hear the thunderous voice of Lord Pyros proclaim: "+ \
                   x->query_name()+" has left the us and has earned a place "+ \
                   "in the Spirit Circle of Psuchae!",\
                   "Winds howl in the voice of Lady Aeria: "+x->query_name()+ \
                   " has left us and has earned a place in the Spirit Circle "+ \
                   "of Psuchae!",\
                   "The ground shakes violently below you momentarily as "+ \
                   "Lady Gu speaks: "+x->query_name()+" has left us and has "+ \
                   "earned a place in the Spirit Circle of Psuchae!",\
                   "You hear the booming voice of Lord Diabrecho: "+ \
                   x->query_name()+" has left us and has earned a place in "+ \
                   "the Spirit Circle of Psuchae!"})                     


string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

int
is_worship(object living)
{
    return living->query_guild_name_lay() == WORSHIP_GUILD;
}

int
is_spirit(object living)
{
    return living->query_guild_name_occ() == SPIRIT_GUILD_NAME;
}


void
create_room()
{
    set_short("A dark chamber");
    set_long("You are in a black chamber with a white pentagram "+
        "on the floor. You are standing directly in the middle of "+
        "the pentagram.\n\nA voice echoes through your mind: "+
        "Pray to me again if you wish to join us. Pray.\n");

    IN;
}


/*
 * Function: enter_inv
 * Description: block non-interactives from entering.
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (living(ob) && !interactive(ob))
        ob->move(from);
}

void
do_join_2(object ob)
{
    object spell_ob, limit_ob, holy_scroll;
    string str;
    int element;

    if (ob->query_skill(SS_PATRON_ELEMENTAL))
    {
        element = ob->query_skill(SS_PATRON_ELEMENTAL);
        switch(element)
        {
            case FIRE_FLAG:
                ob->catch_msg("Lord Pyros gives you a fiery wink and "+
                    "bows respectfully to you. He reaches out and places "+
                    "his hand on your shoulder saying to you in a crackling "+
                    "voice, 'Go now, with my blessing. Take my spirit with "+
                    "you.'\nYou feel a warmth flow through your heart.\n");
                break;
            
            case WATER_FLAG:
                ob->catch_msg("Lord Diabrecho bows respectfully to "+
                    "you. He reaches out and places his hand on your shoulder "+
                    "saying to you in a deep voice, 'Go now, with my "+
                    "blessing. Take my spirit with you.'\nYou feel the "+
                    "energies of Lord Diabrecho flowing through your veins.\n");
                break;

            case AIR_FLAG:
                ob->catch_msg("Lady Aeria gives you a quick wink and curtseys "+
                    "respectfully to you. She reaches out and places her "+
                    "hand on your shoulder saying to you in a light voice, "+
                    "'Go now, with my blessing. Take my spirit with you.'\n"+
                    "You feel a breeze flow around your entire body.\n");
                break;

            default:
                ob->catch_msg("Lady Gu curtseys respectfully to you. She "+
                    "reaches out and places her hand on your shoulder saying "+
                    "to you in a peaceful voice, 'Go now, with my blessing. "+
                    "Take my spirit with you.'\nYou feel the ground rumble "+
                    "ever so slightly below your feet.\n");
                break;

        }
    }
        
    else
    {
        ob->catch_msg("With that, all five figures bow to you.\n");
    }
    
    ob->catch_msg("You find yourself being sucked down into the "+
        "pentagram. As your legs start to disappear into the darkness "+
        "of the now shadowy floor below you, you feel your tongue "+
        "shrinking, just as Psuchae said it would. As you feel your tongue "+
        "disappear totally, you find you have sunk up to your "+
        "neck into the pentagram. With a final look, Psuchae gives "+
        "what you imagine to be a smile and you disappear into the "+
        "blackness of shadow.\n");

    filter(users(), &is_spirit())->catch_msg(JOINED(ob)[0]+"\n");
    ob->add_cmdsoul(SPIRIT_SOUL);
    ob->update_hooks();
    ob->add_cmdsoul(SPIRIT_LAY_SOUL);
    ob->update_hooks();
    ob->set_skill(SS_SPIRIT_CHOSEN,0);
    ob->set_skill(SS_SPELLS_CASTED,0);
    ob->update_hooks();
    spell_ob = clone_object(SPIRIT_OBJECTS+"apprentice_spells");
    spell_ob->move(ob);
    limit_ob = clone_object(SPIRIT_OBJECTS+"limit");
    limit_ob->move(ob);
    holy_scroll = present("_psuchae_holy_scroll_",ob);
    holy_scroll->remove_object();
    str = lower_case(ob->query_real_name());
    write_file(JOIN_LOG, ob->query_name() + " joined the Spirit Circle on "+ 
        ctime(time())+".\n");
    (COUNCIL_OBJECTS+"council_log_book")->update_log_book(my_time()+
        ob->query_name()+" joined the Spirit Circle.\n");
    write("You feel your feet touch solid ground and the shadows and "+
        "darkness around you disappear. You find yourself somewhere else.\n");
    ob->move_living("M",SPIRIT_TEMPLE+"garden",1);
    tell_room(environment(ob),QCTNAME(ob)+" emerges from inside of the "+
        "black obelisk.\n",({ob}));
}

void
do_join_1()
{
    write("\nThe shadowy figure says to you:\n"+
        "'A meeting of all five Elementals is a rare "+
        "and wonderous occasion. I have called the others here to "+
        "witness this joyous event, that of bringing a member "+
        "into the Spirit Circle. Maybe you have had these four touch "+
        "your heart before, maybe you haven't. In front of you to "+
        "your left is Lady Aeria. Standing in front of you to your "+
        "right is Lord Diabrecho. Behind you to your left is Lady "+
        "Gu and last, but certainly not least, behind you to your "+
        "right is Lord Pyros. I am Psuchae. You have found yourself "+
        "in this place which means you have proven yourself worthy "+
        "of membership in my Circle of followers.'\n\nPsuchae hands "+
        "you a holy symbol.\n\nPsuchae speaks again saying 'We all "+
        "welcome you to the Spirit Circle. You are now one of my "+
        "children. The gifts I shall impart to you shall be great, "+
        "but they come with a large price. First and foremost, you "+
        "shall not be allowed to use any edged weapons of any type, "+
        "only bludgeoning. Secondly, you shall take the ultimate "+
        "vow of silence. In a moment, I shall magically shrink your "+
        "tongue, making it impossible for you to speak. Do not be "+
        "alarmed, you will have other methods to communicate, which "+
        "will become clear enough to you soon enough. Lastly, I ask "+
        "that you remain on the lawful side of neutral.'\n\n");
    set_alarm(15.0,0.0,&do_join_2(TP));
}
    
int
join_2()
{
    object occ_shadow, lay_shadow;
    string str;

    str = lower_case(TP->query_real_name());

    seteuid(getuid());
    occ_shadow=clone_object(SPIRIT_SHADOW);
    lay_shadow=clone_object(SPIRIT_LAY_SHADOW);

    if (occ_shadow->shadow_me(TP,SPIRIT_GUILD_TYPE,SPIRIT_GUILD_STYLE,SPIRIT_GUILD_NAME,"") != 1)
    {
        write("The shadowy figure says to you: 'For some unknown reason "+
            "you cannot join my Circle. Please notify the guildmaster "+
            "of the Spirit Circle and give them this message:'\n\n"+
            "The Shadow of Occupation would not take.\nWith that you "+
            "feel yourself being transported somewhere else.\n");
        shadow->remove_shadow();
        TP->move_living("M","/d/Calia/mountain/road/road15");
        return 0;
    }

    if (lay_shadow->shadow_me(TP,SPIRIT_GUILD_TYPE_LAY,SPIRIT_GUILD_STYLE_LAY,SPIRIT_GUILD_NAME,"") != 1)
    {
        write("The shadowy figure says to you: 'For some unknown reason "+
            "you cannot join my Circle. Please notify the guildmaster "+
            "of the Spirit Circle and give them this message:'\n\n"+
            "The Shadow of Laymanship would not take.\nWith that you "+
            "feel yourself being transported somewhere else.\n");
        shadow->remove_shadow();
        TP->move_living("M","/d/Calia/mountain/road/road15");
        return 0;
    }
    COUNCIL_CODE->add_apprentice(str);
    write("The shadowy figure speaks to you in a wispy voice saying:\n");
    TP->clear_guild_stat(SS_OCCUP);
    TP->clear_guild_stat(SS_LAYMAN);
    clone_object(SPIRIT_OBJECTS+"holy_symbol")->move(TP);
    set_alarm(5.0,0.0,&do_join_1());
    return 1;
}

void
join_1()
{
    write("Just as the cloud is about to disappear "+
        "all together, it explodes again into a shadowy form that is "+
        "almost humanoid shaped and moves to the top-most point of the "+
        "pentagram. You are suddenly aware of other figures in the room. "+
        "Had they been there all along? Where they hidden by the darkness, "+
        "or had they just appeared there now?\nIn the top left point of "+
        "the pentagram you see a white robed, winged female figure. A "+
        "calm look resides on her face as she looks at you. Your attention "+
        "is suddenly brought to the top right point of the pentagram "+
        "where you see a blue robed, large male figure holding a large "+
        "golden trident. He stares at you intensely, but not in what "+
        "like a threatening matter at all. Out of the corner of your "+
        "eye you notice a red robed, serious looking male figure standing "+
        "in the bottom left point of the pentagram. His eyes seem to burn "+
        "a hole into your soul as he looks you up and down. Spinning "+
        "around you see, standing in the bottom right point of the "+
        "pentagram, an older, calm looking female figure who is smiling "+
        "at you. Where had everyone come from? You hear a noise to the "+
        "right of you, you turn to see the shadowy figure in the top-most "+
        "point of the pentagram motioning to pay attention to it. You "+
        "turn to face the figure.\n");
    set_alarm(15.0,0.0,&join_2());
}

void
join()
{
    write("The shadowy hand withdraws from your chest. You feel your "+
        "heart begin to beat once again, slowly, calmly.\nThe darkness "+
        "around you converges into one place, forming a great shadowy "+
        "cloud. The cloud begins to move, individual wisps of shadow "+
        "swirling around the larger mass in all directions. The cloud "+
        "begins to shrink, slowly collapsing and swallowing itself. "+
        "Shrinking and shrinking until there is barely a pinpoint of "+
        "the cloud remaining.\n\nUp to now, you had been unaware of "+
        "any of your other surroundings but now the pentagram you are "+
        "standing in begins to shine brightly, casting a white glow "+
        "upon your entire being.\n\n");
    set_alarm(15.0,0.0,&join_1());
}

void
pre_join()
{
    write("\nYour heart begins to slow, calmness fills your body. "+
        "All you can feel is your breath leaving your lips each "+
        "time you exhale.\n\nMore time passes, you begin to feel "+
        "something touching your skin. Looking down, you see the "+
        "darkness around you has begun to almost turn into some "+
        "kind of mist and it is brushing against your face, neck, "+
        "and shoulders, touching the skin right beneath your clothes.\n\n"+
        "A second misty form starts its way up your body, beginning at "+
        "your feet, working its way up your legs. Moving upwards to "+
        "your abdomen.\n\nYour heart beats faster, your breathing is getting "+
        "more rapid. You can hear the blood pumping around your ears as "+
        "your heard beats faster and faster.\n\nBoth shadowy forms converge "+
        "at your chest, joining together right above your heart. Together "+
        "the shadowy figures intertwine, forming into a hand! The hand "+
        "reaches towards you, piercing your chest, a shadowy finger "+
        "touching your heart ever so softly.\n\nComfort.\nComfort and "+
        "serenity, strangely that is what you feel, not fear. Your heart "+
        "stops.\n\n");
    set_alarm(15.0,0.0,&join());
}

int
do_pray(string str)
{
    if (!str)
    {
        NF("Pray to whom? Psuchae? <pray to Psuchae>\n");
        return 0;
    }

    if (str != "to Psuchae")
    {
        NF("Pray to whom? Psuchae? <pray to Psuchae>\n");
        return 0;
    }

    if (is_worship(TP))
    {
        present("worshipper_chalice",TP)->remove_object();
        present("worshipper_dagger",TP)->remove_object();
        present("worshipper_pentacle",TP)->remove_object();
        present("worshipper_wand",TP)->remove_object();
        present("worshipper_sceptre",TP)->remove_object();
        present(I_CAN_CAST,TP)->remove_object();
        present(WOR_CAN_PERMIT)->remove_object();
        present(I_CAN_JOIN,TP)->remove_object();
        TP->remove_skill(SS_CARVED);
        write("Your Elemental Tools shatter into thousands of tiny pieces "+
            "and fall to the ground below you. The pieces are absorbed "+
            "right into the floor!\n");
        reset_euid();
        if (TP->query_default_start_location() == WORSTART)
            TP->set_default_start_location(TP->query_def_start());
        TP->remove_guild_lay();
        TP->clear_guild_stat(SS_LAYMAN);
        TP->remove_cmdsoul("/d/Calia/worshippers/specials/worshipsoul");
        TP->set_skill(SS_PUNISHMENT,5);
        TP->update_hooks();
        seteuid(getuid());
        (WOR_OBJECTS+"council_log_book")->update_log_book(my_time()+
            TP->query_name()+" left the Elementals for the Spirit Circle "+
            "of Psuchae.\n");
        filter(users(), &is_worship())->catch_msg(LEFT(TP)[1]+"\n");
    }

    write("A shadowy darkness surrounds you, blocking out your vision "+
        "of everything around. Even the pentagram on the ground right "+
        "around you can no longer be seen. Blackness overtakes you. "+
        "All is silent. The only sound you can hear is that of your "+
        "own heart beating rapidly, your own breath entering and exiting "+
        "your lungs. Blackness and silence.\n\n");
    present("_schosen_",TP)->remove_object();
    set_alarm(5.0,0.0,&pre_join());
    return 1;
}

void
init()
{
    ::init();
    add_action(do_pray,"pray");
}
