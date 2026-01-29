/*
 * tailor.c
 * FIXA
 * Used in nyreese/cadu_h3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
//#pragma strict_types

inherit "/std/monster";
inherit "/lib/trade.c";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <wa_types.h>

klaga(object who);
tillverka(mixed glah);
make_armour(object *glah);
make_bag(object who);
give_back(mixed *obs);

/* tailor by gresolle - not to be used anywhere right now */

mapping plmapping;

mapping ammap = ([
          "shoes":({0,-1,0}),
          "boots":({1,0,-1}),
          "leggings":({0,0,0}),
          "shirt":({1,0,0}),
          "gloves":({0,0,0}),
          "helmet":({0,0,0}),
          ]);
mapping atmap = ([
          "shoes":A_FEET,
          "boots":A_FEET|A_LEGS,
          "leggings":A_LEGS,
          "shirt":A_TORSO,
          "gloves":A_HANDS,
          "helmet":A_HEAD,
          ]);

mapping acmap = ([
          "grugg":15,
          "dragon":20,
          "knight":3,
          "orc":2,
          "kroug":4,
          "pig":8,
          ]);

mapping shmap =([
         "shoes":"pair of shoes",
         "boots":"pair of boots",
         "leggings":"pair of leggings",
         "shirt":"shirt",
         "gloves":"pair of gloves",
         "helmet":"helmet"
]);
mapping needmap = ([
            "shoes":700,
            "boots":1000,
            "leggings":2000,
            "shirt":5000,
            "gloves":500,
            "helmet":3500,
            ]);
armourlist()
{
    return "He replies: I can make shoes, boots, leggings, shirts,"+
        " gloves, bags\nand helmets, just bring me some skin and "+
        "we'll work something out.\n";
}

create_monster()
{
    config_default_trade();

    set_name("gandril");
    add_name("tailor");
    set_race_name("elf");
    add_name("elf");
    set_title("the tailor");

    set_long("This is Gandril the Tailor. Perhaps he can make you "+
        "something if you ask him.\n");

    add_ask(({"make","items","something"}),
        QCTNAME(TO)+" says: I can make a lot of things from skins "+
        "and furs.  Just give me a skin, then 'say' what you'd like"+
        " me to make.\n");

    add_ask(({"for list", "list","clothes","armour","armours",
        "what make"}), VBFC_ME("armourlist"));

    add_ask(({"skin","skins","fur","furs"}),
        QCTNAME(TO)+" says: Furs and skins comes from dead "+
        "animals.\nIf you want me to return something, ask me "+
        "'for' it.\n");

    add_ask(({"bag","bags"}),
        QCTNAME(TO)+" says: Well, I guess I can make those too.\n"+
        QCTNAME(TO)+" says: Just bring me some skin and I'll see "+
        "what I can do.\n");

    add_ask(({"for skin","for fur"}),
        VBFC_ME("giveback"));

    default_config_npc(30);
    set_base_stat(0,100);
    set_hp(10000);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    trig_new("%s 'says:' %s","apa");
    trig_new("%s 'introduces' %s","intrme");
}
intrme(string s,string ss)
{
    set_alarm(1.0, 0.0, &command("introduce_me"));
}
apa(string s1,string s2)
{
    string foo,item;
    object who;

    s2 = explode(s2, "\n")[0];
    if(!(who = find_player(lower_case(s1))))
    return 0;

    if(!parse_command(s2,E(TO),"'make' / 'buy' [me] %w",item))
    {
    set_alarm(2.0, 0.0, &klaga(who));
    return 1;
    }

    if(!mappingp(plmapping) || !plmapping[who])
    {
    set_alarm(2.0, 0.0, &command("say But you havn't given me" +
            " any skin!"));

    return;
    }
    if(!plmapping[who]->query_prop("_skin_by_gresolle"))
    {
    set_alarm(1.0, 0.0, &command("say You should really pay" +
            " me for the other thing I made."));
    return;
    }
    set_alarm(1.0, 0.0, &tillverka(who, item));
}
tillverka(object who, string item)
{
    tell_room(E(TO),QCTNAME(TO)+" says something to "+ QCTNAME(who)+
        ".\n",({who}));


    switch(item)
    {
    case "armour":
    case "armours":
    case "clothes":
        who->catch_msg("I can make many kinds of armours and "+
            "clothes.  Ask me for a list.\n");
        return;
    case "shoes":
    case "boots":
    case "shirt":
    case "leggings":
    case "gloves":
    case "helmet":
        set_alarm(10.0, 0.0, &make_armour(who, item));
        break;
    case "bag":
        set_alarm(5.0, 0.0, &make_bag(who));
        break;
    default:
        who->catch_msg("I don't understand what you want me to "+
            "make.\n");
        return;
    }
    set_alarm(1.0, 0.0, &command("emote goes to work."));

}
det_ac(object who,string what,object skin)
{
    int ac;

    ac = acmap[skin->query_adj()];

    ac = (ac*skin->query_prop(OBJ_I_WEIGHT))/needmap[what];


    if(!ac)
    return skin->query_prop("_skin_by_gresolle");
    else
    return (ac>20)?20:ac;
}

make_armour(object who, string what)
{
    object arm,skin;
    int ac;

    skin = plmapping[who];

    arm = clone_object("/std/armour");

    arm->set_ac(det_ac(who,what,skin));
    arm->set_am(ammap[what]);
    arm->set_at(atmap[what]);

    arm->add_prop(OBJ_I_WEIGHT,skin->query_prop(OBJ_I_WEIGHT));
    arm->add_prop(OBJ_I_VOLUME,skin->query_prop(OBJ_I_VOLUME));

    arm->set_long("An expertly tailored "+skin->query_adj()+
        "-skin " +shmap[what]+", finely crafted by "+
        "Gandril, the tailor.  ");

    arm->set_name(what);
    arm->set_adj(skin->query_adj());

    arm->set_short(skin->query_adj()+" "+what);

    arm->move(TO);

    arm->update_prop_settings();

    who->catch_msg(QCTNAME(TO)+" says: The armour is finished! I "+
        "want "+ arm->query_prop(OBJ_I_VALUE)+ " cc for it.\n");

    tell_room(E(TO),QCTNAME(TO)+" says something to "
        +QCTNAME(who)+".\n",({who}));

    skin->remove_object();
    plmapping[who] = arm;
}

make_bag(object who)
{
    object skin,bag;

    skin = plmapping[who];

    bag = clone_object("/std/container");
    bag->set_name("bag");
    bag->set_adj(skin->query_adj());
    bag->add_prop(OBJ_I_WEIGHT,skin->query_prop(OBJ_I_WEIGHT));
    bag->add_prop(OBJ_I_VOLUME,skin->query_prop(OBJ_I_VOLUME));
    bag->add_prop(CONT_I_MAX_VOLUME,bag->query_prop(OBJ_I_VOLUME)*10)
;
    bag->add_prop(CONT_I_MAX_WEIGHT,bag->query_prop(OBJ_I_WEIGHT)*10)
;

    bag->set_long("An expertly crafted bag made from the skin of a "+
        skin->query_adj()+ ".  You notice it has a small "+
        "embroidered label.");
    bag->add_item(({"label","embroidery"}), "The word \"Gandril\""+
        " is stitched delicately on the label.\n");
    bag->add_cmd_item("label", "read", "The word \"Gandril\""+
        " is stitched delicately on the label.\n");

    bag->set_short(skin->query_adj()+" bag");
    skin->remove_object();
    bag->move(TO);
    plmapping[who] = bag;

    who->catch_msg(QCTNAME(TO)+" says: The bag is finished, now pay"+
        " me for it. It costs 50 cc.\n");

    bag->add_prop(OBJ_I_VALUE,50);
}

klaga(object who)
{

    who->catch_msg(QCTNAME(TO)+" tells you: I don't understand what"+
        " you're saying.\n");
    return 1;

}
addera(object who,object ob)
{
    if(!mappingp(plmapping))
    plmapping = ([]);

    if(plmapping[who])
    {
    /* already got a skin */

    set_alarm(1.0, 0.0, &give_back(ob, who, "I'm already busy " +
            "with another of your items.\n" + "Ask me "+
            "for that first!\n"));
    return 1;
    }
    plmapping[who] = ob;

    set_alarm(1.0, 0.0, &command("say Thank you. Now tell me what" +
            " you want me to do with it."));
}
enter_inv(object ob,object from)
{
    object *apa;

    ::enter_inv(ob,from);

    if(!from)
    return;

    if(!interactive(from))
    ob->remove_object();

    if(member_array("coin",ob->query_names())>-1)
    {
    set_alarm(2.0, 0.0, &give_back(ob,from,"You should 'pay' " +
            "me instead!"));
    return;
    }

    if(!ob->query_prop("_skin_by_gresolle"))
    {
    set_alarm(2.0, 0.0, &give_back(ob,from,"I don't want that!"));
    return;
    }

    addera(from,ob);

}
giveback()
{
    if(!mappingp(plmapping))
    return process_string(QCTNAME(TO)+" says: You havn't given me "+
        "any skin!\n");

    if(!plmapping[TP])
    return process_string(QCTNAME(TO)+" says: You havn't given me "+
        "any skin!\n");
    if(!plmapping[TP]->query_prop("_skin_by_gresolle"))
    return process_string(QCTNAME(TO)+" says: You should really "+
        "pay me for the item I made for you!\n");

    give_back(({plmapping[TP],TP,"Well then, here you are."}));

    plmapping[TP] = 0;
    return "";
}
give_back(mixed *obs)
{
    command("say "+obs[2]);
    obs[1]->catch_msg(QCTNAME(TO)+" gives you " +LANG_ASHORT(obs[0])+
        ".\n");
    say(QCTNAME(TO)+" gives "+LANG_ASHORT(obs[0])+" to "
        +QCTNAME(obs[1])+ ".\n",({obs[1]}));

    obs[0]->move(obs[1]);
}
/*
catch_tell(string s)
{
  ::catch_tell(s);
  find_player("gresolle")->catch_msg(s);
}
*/
init_living()
{
    ::init_living();

    add_action("pay_me","pay");
}
pay_me(string s)
{
    int value;
    object what;
    mixed arr;

    NF("Pay who?\n");

    if(s!="tailor" && s!="elf" && s!="gandril")
    return 0;

    NF("But you don't owe me anything.\n");
    if(!mappingp(plmapping))
    return 0;

    if(!(what = plmapping[TP]))
    return 0;

    if(!(value = what->query_prop(OBJ_I_VALUE)))
    return 0;

    NF("Sorry, but you don't seem to have enough money!\n");
    if(!can_pay(value,TP))
    return 0;



    TP->catch_msg("You pay the tailor "
        +text(pay(value,TP,0,0,0,0,0))+".\n"+
        "He gives you your item.\n");

    say(QCTNAME(TP)+" pays the tailor.\n");

    what->move(TP);

    plmapping[TP] = 0;

    return 1;
}
