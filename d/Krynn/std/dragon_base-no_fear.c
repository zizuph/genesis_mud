/* Dragon base file by Morrigan 11/17/96 */
/* Some features and props added by Teth, Feb 20 1997 */
/* including introing and no run away */
/* also added 'decrepit' age. */

/* A non-Dragon-fear base, for Kentari's pet, but whomever too */

/* Original code for Ember by Jeremiah referenced, and the code for the
* dragonfear functions is taken directly from it.
*/


#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <filter_funs.h>

inherit C_FILE

inherit "/std/act/domove";
inherit "/std/act/action";

void setup_dragon();
int i, a, penet, *teeth, *claw, *wing, *skin;
string *how, breath_weapon, res_prop, how_str, colour, age;

int forced_attacktype = 0;
int do_intro = 0;

void
set_colour(string str)
{
    colour = str;
    setup_dragon();
}

string
query_colour()
{
    return colour;
}

string
query_age()
{
    return age;
}

void
set_age(string str)
{
    age = str;
    setup_dragon();
}

void
create_dragon_npc()
{
    set_age("adult");
    set_colour("red");
}

void
setup_dragon()
{
    string col = query_colour();

    /* Breath weapon definitions */
    string fire_breath = "a river of flame erupts from "+POSSESSIVE(TO)+
    " mouth!\n";
    string frost_breath = "a cone of frost bursts from "+POSSESSIVE(TO)+
    " mouth!\n";
    string lightning_breath = "a bolt of lightning shoots from "+POSSESSIVE(TO)+
    " mouth!\n";
    string acid_breath = "a stream of acid spews from "+POSSESSIVE(TO)+
    " mouth!\n";
    string gas_breath = "a cloud of noxious gas is blown from "+POSSESSIVE(TO)+
    " mouth!\n";
    string heat_breath = "waves of heat are cast from "+POSSESSIVE(TO)+
    " mouth!\n";

    if (col == "gold" || col == "silver" || col == "copper" || col ==
      "brass" || col == "bronze")
        a = 1;

    if (col == "red" || col == "blue" || col == "green" || col == "black"
      || col == "white")
        a = -1;

    switch(query_age())
    {
    case "decrepit":
        set_adj("decrepit");
        add_prop(LIVE_I_SEE_DARK, 2);
        add_prop(OBJ_I_RES_MAGIC, 50);
        add_prop(LIVE_I_QUICKNESS, 75);
        for(i = 0; i < 6; i++)
            set_base_stat(i, 200 + random(25));
        set_alignment((1200 + random(300)) * a);
        teeth = ({ 73, 73 });
        claw = ({ 83, 63 });
        wing = ({ 63, 53 });
        skin = ({ 83, 93, 73, 73, 53 });
        break;

    case "ancient":
        set_adj("ancient");
        add_prop(LIVE_I_SEE_INVIS, 1);
        add_prop(LIVE_I_SEE_DARK, 5);
        add_prop(OBJ_I_RES_MAGIC, 75);
        add_prop(LIVE_I_QUICKNESS, 150);
        for(i = 0; i < 6; i++)
            set_base_stat(i, 225 + random(25));
        set_alignment((1500 + random(500)) * a);
        teeth = ({ 80, 80 });
        claw = ({ 90, 70 });
        wing = ({ 70, 60 });
        skin = ({ 90, 100, 80, 80, 60 });
        break;

    case "aged":
        set_adj("aged");
        add_prop(LIVE_I_SEE_DARK, 3);
        add_prop(OBJ_I_RES_MAGIC, 50);
        add_prop(LIVE_I_QUICKNESS, 113);
        for(i = 0; i < 6; i++)
            set_base_stat(i, 200 + random(25));
        set_alignment((1200 + random(300)) * a);
        teeth = ({ 73, 73 });
        claw = ({ 83, 63 });
        wing = ({ 63, 53 });
        skin = ({ 83, 93, 73, 73, 53 });
        break;

    case "adult":
        set_adj("adult");
        add_prop(LIVE_I_SEE_DARK, 1);
        add_prop(LIVE_I_QUICKNESS, 75);
        add_prop(OBJ_I_RES_MAGIC, 30);
        for(i = 0; i < 6; i++)
            set_base_stat(i, 175 + random(25));
        set_alignment((1000 + random(250)) * a);
        teeth = ({ 65, 65 });
        claw = ({ 75, 55 });
        wing = ({ 55, 45 });
        skin = ({ 75, 85, 65, 65, 45 });
        break;

    case "young":
        set_adj("young");
        add_prop(OBJ_I_RES_MAGIC, 10);
        add_prop(LIVE_I_QUICKNESS, 38);
        for(i = 0; i < 6; i++)
            set_base_stat(i, 150 +random(25));
        set_alignment((800 + random(400)) * a);
        teeth = ({ 55, 60 });
        claw = ({ 65, 50 });
        wing = ({ 50, 40 });
        skin = ({ 65, 75, 55, 55, 35 });
        break;

    default:
        set_adj("hatchling");
        for(i = 0; i < 6; i++)
            set_base_stat(i, 75 + random(25));
        set_alignment((300 + random(200)) * a);
        teeth = ({ 30, 30 });
        claw = ({ 40, 20 });
        wing = ({ 25, 20 });
        skin = ({ 30, 50, 20, 20, 10 });
        break;
    }

    /* Adding props to make them immune to their own type of breath weapons */
    if (col == "red")
        add_prop(OBJ_I_RES_FIRE, 100);
    else if (col == "blue")
        add_prop(OBJ_I_RES_ELECTRICITY, 100);
    else if (col == "white")
        add_prop(OBJ_I_RES_COLD, 100);
    else if (col == "black")
        add_prop(OBJ_I_RES_ACID, 100);
    else if (col == "green")
        add_prop(OBJ_I_RES_POISON, 100);

    if (a == -1)
        set_knight_prestige(-2 * query_alignment() + -1 * random(query_alignment()));
    else
        set_knight_prestige(-10 - random(7));

    /* Good dragons have various gas breaths as well that disable their opponent */
    /* Perhaps this could be added at a later date? */

    if (colour == "gold" || colour == "red")
    {
        breath_weapon = fire_breath;
        res_prop = MAGIC_I_RES_FIRE;
        how = ({ "not harmed", "barely burned", "slightly burned", 
          "burned quite badly", "burned very badly", "badly incinerated" });
    }
    else if (colour == "silver" || colour == "white")
    {
        breath_weapon = frost_breath;
        res_prop = MAGIC_I_RES_COLD;
        how = ({ "not harmed", "slightly chilled", "chilled", "chilled to "+
          "the bone", "frozen", "frozen solid" });
    }
    else if (colour == "bronze" || colour == "blue")
    {
        breath_weapon = lightning_breath;
        res_prop = MAGIC_I_RES_ELECTRICITY;
        how = ({ "not harmed", "slightly shocked", "slightly burned", "shocked",
          "charred", "electrocuted" });
    }
    else if (colour == "copper" || colour == "black")
    {
        breath_weapon = acid_breath;
        res_prop = MAGIC_I_RES_ACID;
        how = ({ "not harmed", "barely stung", "slightly singed", "singed",
          "badly corroded", "eaten alive" });
    }
    else if (colour == "green")
    {
        breath_weapon = gas_breath;
        res_prop = MAGIC_I_RES_POISON;
        how = ({ "not harmed", "barely choked", "choked", "harmed", 
          "badly harmed", "severely harmed" });
    }
    else if (colour == "brass")
    {
        breath_weapon = heat_breath;
        res_prop = MAGIC_I_RES_FIRE;
        how = ({ "not harmed", "slightly burned", "burned", "injured", 
          "burned badly", "caused to collapse" });
    }

    /* Defining penetration of breath weapon based on dragon's age */

    if (age == "decrepit")
        penet = 750 + random(550);   
    else if (age == "ancient")
        penet = 850 + random(600);
    else if (age == "aged")
        penet = 700 + random(500);
    else if (age == "adult")
        penet = 550 + random(400);
    else if (age == "young")
        penet = 300 + random(300);
    else if (age == "hatchling")
        penet = 50 + random(50);

}

void
create_creature()
{

    add_name("dragon");
    set_race_name("dragon");
    set_gender(random(2));
    set_long("@@long_desc");
    set_short("@@short_desc");
    set_skill(SS_DEFENCE, 100);
    create_dragon_npc();

    /* Setting the attack and armour values for the dragons */
    set_attack_unarmed(0, teeth[0], teeth[1], W_IMPALE, 20, "bite");
    set_attack_unarmed(1, wing[0], wing[1], W_BLUDGEON, 10, "right wing");
    set_attack_unarmed(2, wing[0], wing[1], W_BLUDGEON, 10, "left wing");
    set_attack_unarmed(3, claw[0], claw[1], W_SLASH, 30, "right claw");
    set_attack_unarmed(4, claw[0], claw[1], W_SLASH, 30, "left claw");

    set_hitloc_unarmed(0, skin[0], 20, "head");
    set_hitloc_unarmed(1, skin[1], 40, "body");
    set_hitloc_unarmed(2, skin[2], 25, "tail");
    set_hitloc_unarmed(3, skin[3], 14, "wing");
    set_hitloc_unarmed(4, skin[4], 1, "belly");

    seteuid(getuid(TO));
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop("_ranger_i_not_brawl", 1); 
}

string
long_desc()
{
    string a_an;

    if (age == "hatchling" || age == "young")
        a_an = "a ";
    else
        a_an = "an ";

    if (age == "hatchling")
        return "This is "+a_an+colour+" dragon "+age+".\n";

    return "This is "+a_an+age+" "+colour+" dragon.\n";
}

string
short_desc()
{
    if (age == "hatchling")
        return colour+" dragon "+age;
    else
        return age+" "+colour+" dragon";
}

/* Test friends function. Might want to redifine it to suit your needs better. */
/* Defined friends in your dragon file by doing this:
* string *friend_list;
* friend_list = ({ friend1, friend2, friend3 });
* Note - if you are not changing test_friend function, the strings in your 
* friend_list must be the capitalized names of the friends
*/
int
test_friend(object who)
{
    int j;
    string *friend_list = ({ "verminaard", "aridor" });

    if (friend_list)
    {
        for(j = 0; j < sizeof(friend_list); j++)
            if (who->query_real_name() == friend_list[j])
                return 1;
    }

    return 0;
}


int
special_attack(object enemy)
{
    int attacktype;
    mixed* hitresult;
    object me, *ob;

    me = this_object();

    if (forced_attacktype == 0)   /* no forced special attack this turn */
        attacktype = random(5);
    else
        attacktype = forced_attacktype;

    if (attacktype == 1)
    {
        if (forced_attacktype == 0)
        {
            /* Dragon inhales air, forced next attack to be cloud breath */

            tell_room(E(TO), QCTNAME(TO)+" rises to "+POSSESSIVE(TO)+" full "+
              "height, and you hear a sharp intake of breath as "+PRONOUN(TO)+
              " rears back "+POSSESSIVE(TO)+" head...\n", TO);
            forced_attacktype = 1;
            return 1;
        }

        tell_room(E(TO), "As "+QTNAME(TO)+"'s head descends, "+breath_weapon,
          TO);

        ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });

        /* Remove friends from breath victims */

        for (i = 0; i < sizeof(ob); i++)
        {
            if(test_friend(ob[i]))
                ob -= ({ ob[i] });
        }

        for (i = 0; i < sizeof(ob); i++)
        {
            penet -= penet * ob[i]->query_magic_res(res_prop) /100;
            hitresult = ob[i]->hit_me(penet, MAGIC_DT, me, -1);

            how_str = how[0];
            if (hitresult[0] > 0)
                how_str = how[1];
            if (hitresult[0] > 10)
                how_str = how[2];
            if (hitresult[0] > 20)
                how_str = how[3];
            if (hitresult[0] > 40)
                how_str = how[4];
            if (hitresult[0] > 60)
                how_str = how[5];

            ob[i]->catch_msg("You are "+how_str+" by the dragon breath!\n");
            tell_watcher(QCTNAME(ob[i]) + " is "+how_str+" by the dragon "+
              "breath!\n", ob[i]);

            if (ob[i]->query_hp() <= 0)
                ob[i]->do_die(me);
        }
        forced_attacktype = 0;
        return 1;
    }

    return 0;
}

public varargs void
react_introduce(mixed who = 0)
{
    if (!who)
        set_alarm(2.0,0.0,"command","introduce me");
    else
        set_alarm(2.0,0.0,"command","introduce me to " + who);
}

public void
add_introduced(string who)
{
    if (do_intro)
        react_introduce(who);
}

public void
set_introduce(int on)
{    
    do_intro = on;
}


