/* 
 * Mortis 01.2006
 *
 * Fixes weapons and armours.  Forges weapons with a
 * folded-steel technique.
 *
 */

#include "../../local.h"
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <language.h>

inherit M_FILE
inherit "/std/act/action";

#define MY_CLOTHING         NOBLE + "arms/parmour"
#define MY_KNIFE            MERCH + "arms/smith_knife"
#define MY_SWORD            MERCH + "arms/smith_sword"
#define MY_POLEARM          MERCH + "arms/smith_polearm"
#define MY_CLUB             MERCH + "arms/smith_club"
#define MY_AXE              MERCH + "arms/smith_axe"
#define MY_STAFF            MERCH + "arms/smith_staff"
#define MY_SHOP             MERCH + "smith"
#define FRIEND_HOME         MERCH + "leather"

/* prototypes */
void arm_me();
int alrm; /* the alarm while tailoring an item */
int good = 0;
int enter_alrm = 0;
int attacked = 0;
mixed my_own = ({});
string he_forges();
string he_forges2();
string he_forges3();
string he_forges4(string wep);
string he_forges5(string sty1, string sty2, string wep);
object myhome = find_object(MY_SHOP);
object friendhome = find_object(FRIEND_HOME);

mapping stock = ([ ]);

string *weapon_desc = ({"style1", "style2", "weapon"});

mapping knife_desc_values = (["style1":({"blackened", "curved", "folded-steel",
    "heavy", "light", "long", "polished", "serrated", "shining", "short",
    "thin", "throwing", "wide"}),
    "style2":({"blackened", "curved", "folded-steel", "heavy", "light", "long",
    "polished", "serrated", "shining", "short", "thin", "throwing", "wide"}),
    "weapon":({"dagger", "flatknife", "knife", "kukri", "machete", "shank",
    "shiv", "stiletto"})]);

mapping sword_desc_values = (["style1":({"basket-hilted", "blackened",
    "curved", "folded-steel", "heavy", "large", "light", "long", "polished",
    "shining", "short"}),
    "style2":({"basket-hilted", "blackened", "curved", "folded-steel", "heavy",
    "large", "light", "long", "polished", "shining", "short"}),
    "weapon":({"cutlass", "rapier", "sabre", "scimitar", "sword"})]);

mapping polearm_desc_values = (["style1":({"barbed", "blackened",
    "folded-steel", "heavy", "hooked", "light", "long", "polished", "pointed",
    "serrated", "shining", "short"}),
    "style2":({"barbed", "blackened", "folded-steel", "heavy", "hooked",
    "light", "long", "polished", "pointed", "serrated", "shining", "short"}),
    "weapon":({"bardiche", "halberd", "partisan", "pike", "spear"})]);

mapping club_desc_values = (["style1":({"beaked", "blackened", "heavy",
    "hooked", "light", "polished", "shining", "spiked", "steel"}),
    "style2":({"beaked", "blackened", "heavy", "hooked", "light", "polished",
    "shining", "spiked", "steel"}),
    "weapon":({"club", "flail", "hammer", "mace", "maul", "morning-star", "pick",
    "war-chain", "warhammer"})]);

mapping axe_desc_values = (["style1":({"blackened", "double-bladed",
    "folded-steel", "grensh", "heavy", "hooked", "large", "light", "long", 
    "polished", "shining", "spiked"}),
    "style2":({"blackened", "double-bladed", "folded-steel", "grensh", "heavy",
    "hooked", "large", "light", "long", "polished", "shining", "spiked"}),
    "weapon":({"axe", "battleaxe", "cleaver", "handaxe"})]);

mapping staff_desc_values = (["style1":({"blackthorn", "blackened", "heavy",
        "studded", "light", "long", "thick", "polished" }),
        "style2":({"blackthorn", "blackened", "heavy",
        "studded", "light", "long", "thick", "polished" }),
        "weapon":({"staff", "quarterstaff"})]);


void
create_krynn_monster()
{
    seteuid(getuid(TO));

    set_name("ken");
    set_living_name("ken");
    add_name(({"human", "smith", "master"}));
    set_adj("calm");
    add_adj("rock-muscled");
    set_gender(G_MALE);
    set_short("calm rock-muscled male smith");
    set_long("Dressed all in white with a white dupion headband, this man "
    + "is exceptionally tall and lean with rock hard muscles beneath his "
    + "loose white clothes.  Perhaps in his early forties, his calm, "
    + "collected face shows little signs of age or expression.\nHe is "
    + "ordering the journeymen smiths around with curt hand signals.\n");
    set_race_name("human");
    set_title("Francous, Master Smith of Palanthas en Mystaclitas");
    
    set_size_descs("very tall", "lean");
    set_appearance(5);
    
    set_skill(SS_DEFENCE,      75);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_AWARENESS,    75);
    set_skill(SS_RIDING,       30);
    set_skill(SS_DEFENCE,      75);
    set_skill(SS_PARRY,        90);
    set_skill(SS_WEP_SWORD,    90);
    set_skill(SS_WEP_AXE,      85);
    set_skill(SS_WEP_KNIFE,    85);
    set_skill(SS_WEP_CLUB,     85);
    set_skill(SS_WEP_POLEARM,  85);
    set_skill(SS_BLIND_COMBAT, 75);

    set_stats((({225, 210, 210, 200, 210, 210})), 5);
    set_all_attack_unarmed(20, 30);
    set_all_hitloc_unarmed(40);

    set_alignment(1000);
    set_knight_prestige(-200);
    set_introduce(1);


    set_act_time(14);
    add_act("@@_my_add_acts");

    set_cact_time(11);
    add_cact("emote ponders why you wish to die.");

    add_ask("[about] [how] [to] [do] [i] 'order' / 'ordering' / 'weaponry' / 'weapon' / 'weapons' / 'arms'",
      "say These are the finest forged folded-steel weapons in the land.  "
    + "Look at the marble sign upon the west wall. You may also "
    + "<check> anything on the five smaller signs beneath it.", 1);

    set_default_answer("@@def_answer");

    set_alarm(1.0,0.0,"arm_me");

}

void
return_home()
{
    command("say Call upon Mystaclitas again should you need me, friend.");
    command("emote leaves returning to his smithy.");
    TO->move(MY_SHOP);
    command("emote arrives from a harrowing journey.");
}

string
my_add_acts()
{
    string myact;

    if (E(TO) != myhome)
        return_home();

    myact = one_of_list(({"emote sits in a half lotus and meditates by the "
    + "forge.",
    "emote nods at you in a flowing, calm manner.",
    "emote hammers out instructions to his journeymen smiths as they "
    + "forge " + "@@exa_it@@" + ".",
    "smell",
    "time",
    "emote adjusts his white dupion headband.",
    "emote narrows his eyes discerningly as he examines "
    + "@@exa_it@@" + " fresh from the forge.",
    "check knife",
    "check sword",
    "check polearm",
    "check club",
    "check axe",
    "check staff",
    "emote arranges his tools and hammers in their racks by the "
    + "forge.",
    "emote barely looks up as he says:  Welcome.",
    "emote folds his hand before him in silent meditation.",
    "emote motions with his hand, directing a journeyman smith to "
    + "deliver " + "@@exa_it@@" + " to " + "@@exa_it2@@" + "."}));

    return myact;
}

string
def_answer()
{
    command("say I am not concerned with such things.");
    return "";
}

void
arm_me()
{
    // Ken's custom shirt.
    object kshirt = clone_object(MY_CLOTHING);
    kshirt->set_armour_data("Ken" + "&&"
                            + "loose" + "&&"
                            + "white" + "&&"
                            + "dupion" + "&&"
                            + "shirt");
    kshirt->move(TO);

    // Ken's custom legwear.
    object kpants = clone_object(MY_CLOTHING);
    kpants->set_armour_data("Ken" + "&&"
                            + "loose" + "&&"
                            + "white" + "&&"
                            + "dupion" + "&&"
                            + "pants");
    kpants->move(TO);

    // Ken's custom gloves.
    object kgloves = clone_object(MY_CLOTHING);
    kgloves->set_armour_data("Ken" + "&&"
                            + "heavy" + "&&"
                            + "white" + "&&"
                            + "dupion" + "&&"
                            + "gloves");
    kgloves->move(TO);

    // Ken's custom boots.
    object kboots = clone_object(MERCH + "arms/larmour");
    kboots->set_armour_data("heavy" + "&&"
                            + "white" + "&&"
                            + "suede" + "&&"
                            + "boots");
    kboots->move(TO);

    command("wear all");
}

void
arm_weapon()
{
    int wep1;
    string wepname;
    object mywep;

    command("say So be it.");
    if (attacked == 0)
    {
        wep1 = random(5);

        switch (wep1)
        {
        case 0:
            break;
            mywep = clone_object(MY_KNIFE);
            mywep->set_weapon_data("heavy" + "&&"
                                   + "serrated" + "&&"
                                   + "dagger");
        case 1:
            mywep = clone_object(MY_AXE);
            mywep->set_weapon_data("shining" + "&&"
                                   + "double-bladed" + "&&"
                                   + "handaxe");
            break;
        case 2:
            mywep = clone_object(MY_POLEARM);
            mywep->set_weapon_data("short" + "&&"
                                   + "hooked" + "&&"
                                   + "bardiche");
            break;
        case 3:
            mywep = clone_object(MY_CLUB);
            mywep->set_weapon_data("steel" + "&&"
                                   + "spiked" + "&&"
                                   + "war-chain");
            break;
        default:
            mywep = clone_object(MY_SWORD);
            mywep->set_weapon_data("curved" + "&&"
                                   + "folded-steel" + "&&"
                                   + "sword");
        }
        mywep->move(TO);
        wepname= mywep->short();
        command("emote takes a " + wepname + " from a rack on "
        + "the west wall.");
        command("wield weapon");
        command("emote grasps his " + wepname + " with his "
        + "fingertips calmly.");
        attacked = 1;
    }
}

void
assist_friend()
{
    command("say Hmm, a friend needs my aid.");
    if (attacked == 0)
    {
        arm_weapon();
        attacked = 1;
    }
    command("south");
    command("east");
    command("say What foes are these that trouble you, my friend?");
    command("assist scruffy-bearded leatherworker");
}

void
delay_call_friend()
{
    command("emote calls upon the power of Mystaclitas:  Friend to me!");
}

void
attacked_by(object ob)
{
    arm_weapon();
    friendhome->help_my_friend();
    set_alarm(4.5, 0.0, "delay_call_friend");

    ::attacked_by(ob);
}


void
init_living()
{
    add_action("order","order");
    add_action("collect","collect");
    ::init_living();
}

int
collect(string str)
{
    object weapon;
    if (alrm)
    {
        command("say I forge.  Wait.  Soon I will finish.");
        return 1;
    }
    command("say Your order.  Yes.");
    command("emote removes your weapon from a rack upon the west wall.");
    command("emote bows saying:  Your weapon.");
    weapon = stock[TP->query_real_name()];
    alrm = set_alarm(2.0,0.0,"give_out_weapon",TP->query_real_name(),
             weapon, 1);
    return 1;
}
/*
 * returns an array: ({ style1, style2, weapon })
 */
mapping compute_all_necessary_weapon_data(string *argdata)
{
    int i, j, k, k1, s1, p1, c1, a1, s2;
    string wepcomp = argdata[2];
    mapping order;
    order = (["type":0,"style1":"","style2":"","weapon":""]);
    k1 = IN_ARRAY(wepcomp, knife_desc_values["weapon"]);
    s1 = IN_ARRAY(wepcomp, sword_desc_values["weapon"]);
    p1 = IN_ARRAY(wepcomp, polearm_desc_values["weapon"]);
    c1 = IN_ARRAY(wepcomp, club_desc_values["weapon"]);
    a1 = IN_ARRAY(wepcomp, axe_desc_values["weapon"]);
    s2 = IN_ARRAY(wepcomp, staff_desc_values["weapon"]);

    if (k1)
    {
        for(i=0,j=sizeof(weapon_desc);i<j;i++)
        {
            k = member_array(argdata[i],knife_desc_values[weapon_desc[i]]);
            if (k == -1)
            {
                command("say I'm sorry, but " + argdata[i] + " is not an "
                + "available " + weapon_desc[i] + " choice for a " + wepcomp
                + ".");
                return (["type":0]); // invalid weapon
            }
            order[weapon_desc[i]] = knife_desc_values[weapon_desc[i]][k];
        }
        order["type"] = 1;
    }

    if (s1)
    {
        for(i=0,j=sizeof(weapon_desc);i<j;i++)
        {
            k = member_array(argdata[i],sword_desc_values[weapon_desc[i]]);
            if (k == -1)
            {
                command("say I'm sorry, but " + argdata[i] + " is not an "
                + "available " + weapon_desc[i] + " choice for a " + wepcomp
                + ".");
                return (["type":0]); // invalid weapon
            }
            order[weapon_desc[i]] = sword_desc_values[weapon_desc[i]][k];
        }
        order["type"] = 1;
    }

    if (p1)
    {
        for(i=0,j=sizeof(weapon_desc);i<j;i++)
        {
            k = member_array(argdata[i],polearm_desc_values[weapon_desc[i]]);
            if (k == -1)
            {
                command("say I'm sorry, but " + argdata[i] + " is not an "
                + "available " + weapon_desc[i] + " choice for a " + wepcomp
                + ".");
                return (["type":0]); // invalid weapon
            }
            order[weapon_desc[i]] = polearm_desc_values[weapon_desc[i]][k];
        }
        order["type"] = 1;
    }

    if (c1)
    {
        for(i=0,j=sizeof(weapon_desc);i<j;i++)
        {
            k = member_array(argdata[i],club_desc_values[weapon_desc[i]]);
            if (k == -1)
            {
                command("say I'm sorry, but " + argdata[i] + " is not an "
                + "available " + weapon_desc[i] + " choice for a " + wepcomp
                + ".");
                return (["type":0]); // invalid weapon
            }
            order[weapon_desc[i]] = club_desc_values[weapon_desc[i]][k];
        }
        order["type"] = 1;
    }

    if (a1)
    {
        for(i=0,j=sizeof(weapon_desc);i<j;i++)
        {
            k = member_array(argdata[i],axe_desc_values[weapon_desc[i]]);
            if (k == -1)
            {
                command("say I'm sorry, but " + argdata[i] + " is not an "
                + "available " + weapon_desc[i] + " choice for a " + wepcomp
                + ".");
                return (["type":0]); // invalid weapon
            }
            order[weapon_desc[i]] = axe_desc_values[weapon_desc[i]][k];
        }
        order["type"] = 1;
    }

    if (s2)
    {
        for(i=0,j=sizeof(weapon_desc);i<j;i++)
        {
            k = member_array(argdata[i],staff_desc_values[weapon_desc[i]]);
            if (k == -1)
            {
                command("say I'm sorry, but " + argdata[i] + " is not an "
                + "available " + weapon_desc[i] + " choice for a " + wepcomp
                + ".");
                return (["type":0]); // invalid weapon
            }
            order[weapon_desc[i]] = staff_desc_values[weapon_desc[i]][k];
        }
        order["type"] = 1;
    }
    
    return order;
}

void
give_out_weapon(string who_name, object weapon, int flag)
{
    int price, k1, s1, p1, c1, a1, s2;
    object who;
    string what_is_it = weapon->short();
    string wepprice = weapon->query_name();

    k1 = IN_ARRAY(wepprice, knife_desc_values["weapon"]);
    s1 = IN_ARRAY(wepprice, sword_desc_values["weapon"]);
    p1 = IN_ARRAY(wepprice, polearm_desc_values["weapon"]);
    c1 = IN_ARRAY(wepprice, club_desc_values["weapon"]);
    a1 = IN_ARRAY(wepprice, axe_desc_values["weapon"]);
    s2 = IN_ARRAY(wepprice, staff_desc_values["weapon"]);

    if (what_is_it == 0)
    {
        what_is_it = "weapon";
    }

    if (who_name)
        who = find_player(who_name);

    if (!who || E(TO) != E(who))
    {
        if (flag)
            command("say I see my last customer was too impatient to pick up "
            + "their " + what_is_it + ".");
        else
            command("say I see my last customer was too impatient to see the "
            + "completion of their " + what_is_it + ".");

        command("emote expresses no emotion, only an air of calm and "
        + "control.");

        if (weapon)
        {
            if (flag)
                command("emote places " + what_is_it + " on a rack upon the "
                + "west wall to be collected later.");
            else
            {
                command("emote places " + what_is_it + " on a rack upon the "
                + "west wall to be collected later.");
                stock += ([ who_name:weapon ]);
            }
        }
        command("say Such is the way of things at times for some.");
        alrm = 0;
        return;
    }

    if (!weapon)
    {
        if (flag)
            command("say I have no recollection of an order for a " + what_is_it
            + " placed by you.");
        else
            command("say Apologies.  Something went wrong with your "
            + "order.");

        command("gesture calmly");
        alrm = 0;
        return;
    }
    weapon->move(TO);
    command("say Your " + what_is_it + ".  Praise the Tamer of Chaos.");
    alrm = 0;

    if (k1) // 8gc
        price = 1152;

    if (s1) // 20gc
        price = 2880;

    if (p1 || s2) // 24gc
        price = 3456;

    if (c1) // 16gc
        price = 2304;

    if (a1) // 16gc
        price = 2304;
    
    if (!MONEY_ADD(who, -price))
    {
        command("say You bear insufficient funds.  There are no discounts.");
        command("say Your " + what_is_it + " will be here for you to collect "
        + "when you can pay.");
        command("emote places " + what_is_it + " on a rack upon the west "
        + "wall.");
        weapon->move(VOID);
        stock += ([ who_name:weapon ]);
        return;
    }
    who->catch_msg("You pay the smith " + price + " copper coins.\n");

    weapon->remove_shadow();

    if (!command("give " + weapon->query_name() + " to " + who_name))
        command("drop " + weapon->query_name());

    stock = m_delete(stock, who_name);
    
    if (enter_alrm)
      {
          remove_alarm(enter_alrm);
          enter_alrm = 0;
      }
}

int
order(string str)
{
    string cus, col, mat, art;
    string *argdata;
    mapping my_order;

    if (alrm)
    {
        command("say I forge.  Wait.  Soon I will finish.");
        return 1;
    }

    NF(C(query_verb()) + " what?\n");

    if (!str)
        return 0;

    if (stock[TP->query_real_name()])
    {
          NF("There is already a weapon in stock for you.  "
          + "Would you collect it first?\n");
          return 0;
    }

    /* syntax is: 'order <style1> <style2> <weapon>' */
    argdata = explode(str," ");

    NF(C(query_verb()) + " <style1> <style2> <weapon>.\n");

    if(sizeof(argdata) != 3)
    { return 0; }

    my_order = compute_all_necessary_weapon_data(argdata);

    if (my_order["type"])
    {
        alrm = set_alarm(36.0, 0.0, "finished_weapon",
        TP->query_real_name(), my_order["style1"],
        my_order["style2"], my_order["weapon"]);
        write("You place your order.\n");
        say(QCTNAME(TP) + " orders a weapon.\n");

        command("say I must focus now.  If you are not here when I finish, "
        + "you may return later to <collect> it.");

        add_prop(TSIT, 1);
        add_prop(LIVE_S_EXTRA_SHORT," is at the forge crafting a masterful "
        + argdata[0] + " " + argdata[1] + " " + argdata[2]);

        set_alarm(2.0, 0.0, "he_forges");
        set_alarm(10.0, 0.0, "he_forges2");
        set_alarm(16.0, 0.0, "he_forges3");
        set_alarm(24.0, 0.0, "he_forges4", argdata[2]);
        set_alarm(34.0, 0.0, "he_forges5", argdata[0], argdata[1], argdata[2]);

      return 1;
    }
    NF("You failed to order a valid weapon type.  Read the signs again for "
    + "valid weapon choices.\n");
    return 0;
}

void
finished_weapon(string for_who, string sty1, string sty2, string wep)
{
    int k1, s1, p1, c1, a1, s2;
    string gentype;

    k1 = IN_ARRAY(wep, knife_desc_values["weapon"]);
    s1 = IN_ARRAY(wep, sword_desc_values["weapon"]);
    p1 = IN_ARRAY(wep, polearm_desc_values["weapon"]);
    c1 = IN_ARRAY(wep, club_desc_values["weapon"]);
    a1 = IN_ARRAY(wep, axe_desc_values["weapon"]);
    s2 = IN_ARRAY(wep, staff_desc_values["weapon"]);

    if (k1)
        gentype = MY_KNIFE;

    if (s1)
        gentype = MY_SWORD;

    if (p1)
        gentype = MY_POLEARM;

    if (c1)
        gentype = MY_CLUB;

    if (a1)
        gentype = MY_AXE;
    
    if (s2)
        gentype = MY_STAFF;

    object weapon = clone_object(gentype);
    weapon->set_weapon_data(sty1 + "&&"
                            + sty2 + "&&"
                            + wep);

    give_out_weapon(for_who, weapon, 0);
}

string
exa_it()
{
    return one_of_list(({"a knife", "a sword", "a polearm", "a club",
      "an axe"}));
}

string
exa_it2()
{
    return one_of_list(({"a cloaked short figure", "a cloaked tall figure",
    "a young constable", "a well-dressed squire", "an aging mercenary",
    "a leather armoured male elf", "an old, wide-hatted traveller",
    "a swarthy, stubble-chinned mercenary", "a white-robed woman",
    "a pair of short-cloaked, young noblemen", "a long-bearded dwarf"}));
}

int
react_bow(object actor)
{
    command("emote bows slowly and formally, his eyes steady and calm never "
    + "leaving yours.");
    return 1;
}

void
emote_hook(string emote, object actor, string adverb)
{
    if (emote == "bow")
        set_alarm(1.0, 0.0, &react_bow(actor));
}

string he_forges()
{
    command("emote motions to a few journeymen smiths as he kneels and "
    + "meditates beside the forge.\nA pair of journeymen smiths pick up "
    + "hammers and await the master at his anvils as another pumps the "
    + "great bellows sending waves of heat rippling through the air.");
    return "";
}

string he_forges2()
{
    command("emote uses a pair of tongs to remove a red-hot block of steel "
    + "from the coals of the forge fire.\nHe places it on an anvil and "
    + "begins tapping out instructions upon it with a small hammer "
    + "to his journeymen smiths who begin pounding upon the block "
    + "rhythmically sending sparks flying with each blow.");
    return "";
}

string he_forges3()
{
    command("emote continues tapping out instructions to his journeymen "
    + "smiths as he folds the elongated block over tossing a white powder "
    + "in between the layers.\nThe journeymen smiths rain down blows "
    + "upon the block as the master continues his folds.");
    return "";
}

string he_forges4(string wep)
{
    command("emote concentrates intensely as the journeymen smiths pound "
    + "the glowing red block into the shape of a steel " + wep + ".");
    return "";
}

string he_forges5(string sty1, string sty2, string wep)
{
    command("emote plunges the finished " + wep + " into a trough of water "
    + "with a loud \"HISS\" before personally adding the final touches that "
    + "will make the " + wep + " " + sty1 + " and " + sty2 + ".");
    command("say Ahh, a fine " + sty1 + " " + sty2 + " " + wep + ".");

    remove_prop(TSIT);
    remove_prop(LIVE_S_EXTRA_SHORT);
    return "";
}

int
special_attack(object enemy)
{
    int pen, att, wloc;
    string hitloc, how, withweak, withstrong, withmold, mywep = "tanto";
    mixed hitres;

    if (sizeof(TO->query_weapon(-1)))
    {
        mywep = TO->query_weapon(-1)[0]->query_short();
    }

    if (random(4) == 1)
    {
        pen = 275 + random(250);
        wloc = one_of_list(({A_HEAD, A_TORSO, A_LEGS, A_R_ARM, A_L_ARM}));
        withweak = one_of_list(({"an open palmed slap", "an elbow uppercut",
        "a swift knuckle punch"}));
        withstrong = one_of_list(({"iron-knuckled punch", "jumping knee "
        + "strike", "spinning back kick", "flurry of lightning punches",
        mywep}));
        
        switch (wloc)
        {
            case A_HEAD:
                hitloc = "head";
                break;
            case A_TORSO:
                hitloc = "body";
                break;
            case A_LEGS:
                hitloc = "legs";
                break;
            case A_R_ARM:
                hitloc = "right arm";
                break;
            case A_L_ARM:
                hitloc = "left arm";
                break;
            default:        
        }

        hitres = enemy->hit_me(pen, W_BLUDGEON, TO, -1, wloc);

        switch (hitres[0])
        {
            case -1..0:
                enemy->catch_msg(QCTNAME(TO) + " launches " + withweak
                + " at your " + hitloc + " but misses.\n");
                tell_room(E(TO), QCTNAME(TO) + " launches " + withweak
                + " at " + QTNAME(enemy) + "'s " + hitloc + " but misses.\n",
                ({enemy, TO}));
                break;
            case 1..9:
                enemy->catch_msg(QCTNAME(TO) + " strikes your " + hitloc
                + " with " + withweak + " leaving you stunned by his "
                + "speed.\n");
                tell_room(E(TO), QCTNAME(TO) + " strikes " + QTNAME(enemy)
                + "'s " + hitloc + " with " + withweak + " leaving "
                + HIM(enemy) + " stunned by his speed.\n", ({enemy, TO}));
                break;
            case 10..16:
                enemy->catch_msg(QCTNAME(TO) + " launches " + withweak
                + ", pummeling your " + hitloc + " and leaving you woozy.\n");
                tell_room(E(TO), QCTNAME(TO) + " launches " + withweak
                + ", pummeling " + QTNAME(enemy) + "'s " + hitloc + " and "
                + "leaving " + HIM(enemy) + " woozy.\n" + QCTNAME(enemy)
                + " groans:  Oh, my " + hitloc + ".\n", ({enemy, TO}));
                enemy->command("puke");
                break;
            case 17..30:
                enemy->catch_msg(QCTNAME(TO) + " flashes out suddenly with "
                + HIS(TO) + " " + withstrong + ", brutalizing your " + hitloc
                + " and sending a spray of blood across the room.\n");
                tell_room(E(TO), QCTNAME(TO) + " flashes out suddenly with "
                + HIS(TO) + " " + withstrong + ", brutalizing " + QTNAME(enemy)
                + "'s " + hitloc + " and sending a spray of blood across the "
                + "room.\n" + QCTNAME(enemy) + " groans badly.\n",
                ({enemy, TO}));
                break;
            case 31..43:
                enemy->catch_msg(QCTNAME(TO) + " flashes out viciously with "
                + HIS(TO) + " " + withstrong + ", brutalizing your " + hitloc
                + " and sending a spray of blood across the room.\n");
                tell_room(E(TO), QCTNAME(TO) + " flashes out viciously with "
                + HIS(TO) + " " + withstrong + ", brutalizing " + QTNAME(enemy)
                + "'s " + hitloc + " and sending a spray of blood across the "
                + "room.\n", ({enemy, TO}));
                enemy->command("groan confus");
                enemy->command("south");
                break;
            case 44..66:
                enemy->catch_msg(QCTNAME(TO) + " reduces your " + hitloc
                + " to a bloody stump with " + HIS(TO) + " " + withstrong
                + " as he lashes out over and over swiftly.\n");
                tell_room(E(TO), QCTNAME(TO) + " reduces " + QTNAME(enemy)
                + "'s " + hitloc + " to a bloody stump with "+ HIS(TO) + " "
                + withstrong + " as he lashes out over and over swiftly.\n",
                ({enemy, TO}));
                enemy->command("shout Oh gods, my " + hitloc + "!");
                break;
            default:
                enemy->catch_msg(QCTNAME(TO) + " knocks your legs out from "
                + "under you with a spinning low kick, leaps into the air, "
                + "and lands upon you with a THUD!\n" + QCTNAME(TO) + " sits "
                + "on your " + hitloc + " sending bits of bone and blood "
                + "splurting out all over the floor.\n");
                tell_room(E(TO), QCTNAME(TO) + " knocks " + QTNAME(enemy)
                + "'s legs out from under " + HIM(enemy) + " with a spinning "
                + "low kick, leaps into the air, and lands upon " + HIM(enemy)
                + " with a THUD!\n" + QCTNAME(TO) + " sits on "
                + QTNAME(enemy) + "'s " + hitloc + " sending bits of bone and "
                + "blood splurting out all over the floor.\n", ({enemy, TO}));
                enemy->command("say No, Lars... not yet!");
                break;
        }

        if (enemy->query_hp() <= 0)
            enemy->do_die(TO);

        return 1;
    }

    return 0;
}
