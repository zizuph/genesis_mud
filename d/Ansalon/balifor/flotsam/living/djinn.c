/* created by Gorr 19/12/96 */
/* last updated    29/01/97 */

#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <const.h>
#include "../local.h"
#include <money.h>

inherit "/d/Ansalon/std/monster.c";

int paid_for_ride = 0;
void djinn_died();
void go_err();
void travel();
int exhausted = 0;
int place_err;

string to_go;

object Aowner;
object lamp_obj;
object murderer;
object gifter;
object payer;

void
create_krynn_monster()
{

    set_name("azerel");
    add_name("gennie");
    set_race_name("djinn");
    set_title(" of the Lamp");
    set_adj("old");
    add_adj("muscular");
    set_gender("G_MALE");
    set_long("@@long_desc");

    set_stats(({100,100,100,200,200,100}));
    set_hp(query_max_hp());
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_AWARENESS, 70);

    if((lamp_obj->query_lamp_al()) == 0)
    {
        set_alignment(-100);
        set_knight_prestige(10);
    }
    else
    {
        set_alignment(100);
        set_knight_prestige(-10);
    }

    add_ask("solace","@@solace",1);
    add_ask("palanthas","@@palanthas",1);
    add_ask("newports","@@newports",1);
    add_ask("flotsam","@@flotsam",1);

    set_default_answer(QCTNAME(TO) + " mutters: Oh, I'm feeling " +
                       "very well. Thank you, friend.\n");

    set_act_time(1);
    add_act("emote grins.");

    set_cact_time(1);
    add_cact("emote flows up and down.");

    trig_new("%w 'introduces' %s","react_to_intro");

    add_prop(MAGIC_AM_MAGIC,({100,"conjuration"}));
    add_prop(MAGIC_AM_ID_INFO,({"Djinn Azarel of the Lamp. " +
       "He was summoned from the other plane by some renegate mage " +
       "from one of the nomad " +
       "tribes living on the Plains of Dust. He is prisoner of the lamp " +
       "He is also using ornamented curved magic scimitar. " +
       "To summon him from the lamp one must rub it. " +
       "He can curse his killer who is sucked by lamp. " +
       "He follows the lamp whenever it is moved. " +
       "Bribed by lamp owner he can transport him to the various " +
       "places on Krynn. \n",15}));

    add_prop(LIVE_I_NO_CORPSE,1);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

}

string
long_desc()
{
    return".\n";
}

void
react_to_intro(string who,string garbage)
{
    set_alarm(2.0,0.0,"return_intro",who);
}

void
return_intro(string who)
{
    who = L(who);
    if (P(who,E(TO)))
    {
        command("introduce myself");
    }
}

/*
 * Some masked functions
 */

void
do_die(object killer)
{
    murderer = killer;
    djinn_died();
    ::do_die(killer);
}

void
djinn_died()
{
    command("point " + (murderer->query_name()));
    command("emote mutters some strange words.");
    if(murderer = E(lamp_obj))
    murderer->command("drop old shining lamp");
    if(murderer = E(E(lamp_obj)))
    lamp_obj->move(E(E(lamp_obj)));
    murderer->catch_message("You feel terrible sensations as you " +
            "change into smoke and are sucked by the magic lamp.\n");
    murderer->move(FROOM + "in_lamp.c");
    say(QCTNAME(murderer) +" dissolves into smoke and is sucked by " +
       "the magic lamp.\n");
    lamp_obj->set_prisoner(murderer);
    if((lamp_obj->query_lamp_al()) == 1)
     lamp_obj->set_lamp_al(0);
    else
     lamp_obj->set_lamp_al(1);
}

void
enter_inv(object ob, object from)
{
    gifter = from;
    ::enter_inv(ob, from);
    if(ob->query_name() == "gold coin" && (from == E(lamp_obj) || from == E(E(lamp_obj))))
     paid_for_ride = 1;
    set_alarm(1.0,0.0,"thanks");
}

void
thanks()
{
    command("smile " + (gifter->query_name()));
    command("emote mutters: Thank you, my dear " + (gifter->query_race()) +
            ".");
    if(paid_for_ride == 1)
    {
        payer = gifter;
        command("whisper " + payer->query_name() + " Just ask me where " +
                "you want to go, mortal.");
    }
}

string
solace()
{
    if(paid_for_ride == 0)
     {
     command("emote mutters: Oh, Solace is a beautiful town. I wish " +
             "I would see it again.");
     return"";
     }
    to_go = "/d/Krynn/...";
    travel();
    say("Both " + QCTNAME(TO) + " and " + QCTNAME(payer) +
        "are carried away by the wind.\n");
    return"";
}

string
palanthas()
{
    if(paid_for_ride == 0)
     {
     command("emote mutters: Oh, Palanthas is a wonderful city. Once I " +
             "lived there.");
     return"";
     }
    to_go = "/d/Krynn/...";
    travel();
    say("Both " + QCTNAME(TO) + " and " + QCTNAME(payer) +
        "are carried away by the wind.\n");
    return"";
}

string
newports()
{
    if(paid_for_ride == 0)
     return"emote mutters: Hmmm, Newports. Isn't it this small " +
           "village by Newsea ?";
    to_go = "/d/Krynn/...";
    travel();
    say("Both " + QCTNAME(TO) + " and " + QCTNAME(payer) +
        "are carried away by the wind.\n");
    return"";
}

string
flotsam()
{
    if(paid_for_ride == 0)
     return"emote mutters: Flotsam, it was once a beautiful city, you know.";
    to_go = "/d/Ansalon/...";
    travel();
    say("Both " + QCTNAME(TO) + " and " + QCTNAME(payer) +
        "are carried away by the wind.\n");
    return"";
}

void
resting()
{
    exhausted = 0;
}

void
travel()
{
    if(!(payer == this_player()))
    {
command("grin " + TP->query_name());
command("whisper " + TP->query_name() + " Dont be so smart, mortal.");
        return;
    }
if(!(payer == E(lamp_obj) || payer == E(E(lamp_obj))))
    {
        command("eyebrow " + TP->query_name());
        command("whisper " + TP->query_name() + " Why should I help you ?");
        return;
    }
    if(exhausted == 1)
    {
        command("sigh");
    command("whisper " + TP->query_name() + " Oh, I'm so exhausted " +
               "now, would you mind to wait a bit, mortal.");
        return;
    }
    command("emote wonders: Hmmm ... lets see what we can do.");
    command("emote starts to make some strange gestures.");
    command("emote raises his hands up.");
    say("Suddenly a powerful wind arises !");
    TP->catch_msg("Suddenly a powerful wind arises !");
    command("grin proudly");
    TP->move(FROOM + "in_wind.c");
    exhausted = 1;
    set_alarm(500.0,0.0,"resting");
    move(FROOM + "in_wind.c");
    command("emote shouts through the blast of wind: Hold on, we'll be " +
            "there in the twinkling of an eye.");
    place_err = random(10);
    set_alarm(30.0,0.0,"on_place");
    return;
}

void
on_place()
{
    if(place_err == 0)
     go_err();
    payer->catch_msg("The wind suddenly dies and you are thrown to the ground.");
    payer->move(to_go);
    TO->move(to_go);
    if(place_err == 0)
     command("oops");
    else
     command("smile whole");
}

void
go_err()
{
    switch(random(5))
    {
         case 0:
         to_go = "/d/Krynn/...";
         break;

         case 1:
         to_go = "/d/Krynn/...";
         break;

         case 2:
         to_go = "/d/Krynn/...";
         break;

         case 3:
         to_go = "/d/Krynn/...";
         break;

         case 4:
         to_go = "/d/Ansalon/...";
         break;
     }
}

/*
 * This part of code was made by *** Sarr *** and only
 * slightly updated by Gorr for Djinn.
 *
 * --- BEWARE TWO RR's !!! --- ;)
 *
 * It allows Djinn to follow the magic lamp.
 *
 */

string
check_estring(object ob, int x)
{
    int i;
    string str1,*str;
    if(x == 0)
        str1 = ob->query_m_out();
    else
        str1 = ob->query_mm_out();
    str = explode(str1," ");
    for(i=0;i<sizeof(str);i++)
    {
        if(x != 0 && i == sizeof(str)-1)
            str[i] = "'"+str[i]+"\n'";
        else
        str[i] = "'"+str[i]+"'";
    }
    str1 = implode(str," ");
    return str1;
}


int
set_owner(object ob)
{
    if(!ob)
        return 0;
    trig_new("%s "+check_estring(ob,0)+" %w","react_leave");
    trig_new("%s "+check_estring(ob,1),"react_trans");
    Aowner = ob;
    return 1;
}

object
query_owner()
{
    return Aowner;
}

void
react_leave(string name, string dir)
{
    object tone;
    tone = find_player(lower_case(name));
    if(!tone)
    {
        return;
    }
    if(query_owner() == tone)
    {
        dir = extract(dir,0,-3);
        set_alarm(0.5,0.0,&command(dir));
        return;
    }
}

void
react_trans(string name, string dir)
{
    object tone;
    tone = find_player(lower_case(name));
    if(!tone)
    {
        return;
    }
    if(query_owner() == tone)
    {
        set_alarm(0.5,0.0,"trans_me",tone);
        return;
    }
}

trans_me(object ob)
{
    object dest;
    dest = E(ob);
    move_living("dissapears in a puff of smoke.",dest);
}

/* End of Sarr's code ;) */

/* A function setting the proper lamp for Djinn */

void
set_lamp(object lamp)
{
    lamp_obj = lamp;
}
