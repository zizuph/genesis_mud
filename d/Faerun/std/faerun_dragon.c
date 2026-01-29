/*
 * Dragon base file for Faerun
 * Based on /d/Krynn/std/dragon_base
 * Original base file by Morrigan 11/17/96
 * This version does not have dragonfear. That feature is unique to
 * Krynn dragons.
 * -- Finwe, August 2007
 */

#pragma strict_types
#pragma save_binary

#include "/d/Faerun/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <options.h>

inherit FAERUN_CREATURE;

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/d/Faerun/lib/gems";

// #define DRAGON_FEAR (KROBJECT + "dragon_fear")

int penet, *teeth, *claw, *wing, *skin;
string *how, breath_weapon, res_prop, how_str;
string colour = "red";
string age = "adult";

int forced_attacktype = 0;
int do_intro = 0;

/* prototype */
void setup_dragon();
void fire_breath();
void poison_breath();
void acid_breath();
void electric_breath();
void cold_breath();
void light_breath();
void sound_breath();
void water_breath();

public int
faerun_dragon()
{
    return 1;
}

void
set_colour(string str)
{
    if(colour == str)
    return;
    remove_adj(colour);
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
    if(age == str)
    return;
    remove_adj(age);
    remove_adj("dragon");
    remove_name("hatchling");
    age = str;
    setup_dragon();
}

void
create_dragon_npc()
{
    setup_dragon();
}

void
setup_dragon()
{
    int i, a, mod;
    string col = query_colour();

    switch(colour)
    {
// Metallic dragons
// Mostly good aligned
        case "brass":
            mod = 65;
            a = 1;
            fire_breath();
            break;
        case "bronze":
            mod = 90;
            a = 1;
            electric_breath();
            break;
        case "copper":
            mod = 75;
            a = 1;
            acid_breath();
            break;
        case "gold":
            mod = 105;
            a = 1;
            fire_breath();
            break;
        case "silver":
            mod = 100;
            a = 1;
            cold_breath();
            break;
// Gem Dragons
// Mostly neutral
        case "amethyst":
            mod = 80;
            a = 0;
            sound_breath();
            break;
        case "crystal":
            mod = 70;
            a = 0;
            light_breath();
            break;
        case "emerald":
            mod = 85;
            a = 0;
            sound_breath();
            break;
        case "obsidian":
            mod = 90;
            a = 0;
            fire_breath();
            break;
        case "sapphire":
            mod = 85;
            a = 0;
            sound_breath();
            break;
        case "diamond":
            mod = 95;
            a = 0;
            light_breath();
            break;
// Chromatic dragons
// Typically evil
        case "black":
            mod = 80;
            a = -1;
            acid_breath();
            break;
        case "blue":
            mod = 90;
            a = -1;
            electric_breath();
            break;
        case "green":
            mod = 75;
            a = -1;
            acid_breath();
            break;
        case "red":
            mod = 65;
            a = -1;
            fire_breath();
            break;
        case "white":
            mod = 50;
            a = -1;
            cold_breath();
            break;
        case "brown":
            mod = 70;
            a = -1;
            acid_breath();
            break;
        case "orange":
            mod = 75;
            a = -1;
            acid_breath();
            break;
        case "purple":
            mod = 80;
            a = -1;
            electric_breath();
            break;
        case "yellow":
            mod = 80;
            a = -1;
            water_breath();
            break;
        default:
            colour = "red";
            mod = 100;
            fire_breath();
            a = -1;
    }
    set_adj(colour);

    switch(age)
    {
        case "decrepit":
            set_adj("decrepit");
            add_prop(LIVE_I_SEE_DARK, 2);
            add_prop(OBJ_I_RES_MAGIC, 85);
            add_prop(LIVE_I_QUICKNESS, 75);
            for(i = 0; i < 6; i++)
                set_base_stat(i, (mod+100)*200/200 + random(25));
            set_alignment((1200 + random(300)) * a);
            teeth = ({ 73, 73 });
            claw = ({ 83, 63 });
            wing = ({ 63, 53 });
            skin = ({ 83, 93, 73, 73, 53 });
            penet = 750 + random(550);
            add_prop(CONT_I_HEIGHT, mod * 430 / 100);
            add_prop(CONT_I_WEIGHT, mod * 700000 / 100);
            add_prop(CONT_I_VOLUME, mod * 700000 / 66);
            add_leftover("/d/Krynn/common/weapons/dragonbone", "dragonbone", 1, "", 0, 1);
            set_exp_factor(180);
            break;
        case "ancient":
            set_adj("ancient");
            add_prop(LIVE_I_SEE_INVIS, 1);
            add_prop(LIVE_I_SEE_DARK, 5);
            add_prop(OBJ_I_RES_MAGIC, 75);
            add_prop(LIVE_I_QUICKNESS, 150);
            for(i = 0; i < 6; i++)
                set_base_stat(i, (mod+100)*225/200 + random(25));
            set_alignment((1500 + random(500)) * a);
            teeth = ({ 80, 80 });
            claw = ({ 90, 70 });
            wing = ({ 70, 60 });
            skin = ({ 90, 100, 80, 80, 60 });
            penet = 850 + random(600);
            add_prop(CONT_I_HEIGHT, mod * 420 / 100);
            add_prop(CONT_I_WEIGHT, mod * 650000 / 100);
            add_prop(CONT_I_VOLUME, mod * 650000 / 66);
            add_leftover("/d/Krynn/common/weapons/dragonbone", "dragonbone", 1, "", 0, 1);
            set_exp_factor(200);
            break;
        case "aged":
            set_adj("aged");
            add_prop(LIVE_I_SEE_DARK, 3);
            add_prop(OBJ_I_RES_MAGIC, 50);
            add_prop(LIVE_I_QUICKNESS, 113);
            for(i = 0; i < 6; i++)
                set_base_stat(i, (mod+100)*200/200 + random(25));
            set_alignment((1200 + random(300)) * a);
            teeth = ({ 73, 73 });
            claw = ({ 83, 63 });
            wing = ({ 63, 53 });
            skin = ({ 83, 93, 73, 73, 53 });
            penet = 700 + random(500);
            add_prop(CONT_I_HEIGHT, mod * 420 / 100);
            add_prop(CONT_I_WEIGHT, mod * 620000 / 100);
            add_prop(CONT_I_VOLUME, mod * 620000 / 66);
            add_leftover("/d/Krynn/common/weapons/dragontooth", "tooth", 1, "", 0, 1);
            set_exp_factor(180);
            break;
        case "adult":
            set_adj("adult");
            add_prop(LIVE_I_SEE_DARK, 1);
            add_prop(LIVE_I_QUICKNESS, 75);
            add_prop(OBJ_I_RES_MAGIC, 30);
            for(i = 0; i < 6; i++)
                set_base_stat(i, (mod+100)*175/200 + random(25));
            set_alignment((1000 + random(250)) * a);
            teeth = ({ 65, 65 });
            claw = ({ 75, 55 });
            wing = ({ 55, 45 });
            skin = ({ 75, 85, 65, 65, 45 });
            penet = 550 + random(400);
            add_prop(CONT_I_HEIGHT, mod * 400 / 100);
            add_prop(CONT_I_WEIGHT, mod * 600000 / 100);
            add_prop(CONT_I_VOLUME, mod * 600000 / 66);
            add_leftover("/d/Krynn/common/weapons/dragontooth", "tooth", 1, "", 0, 1);
            set_exp_factor(165);
            break;
        case "young":
            set_adj("young");
            add_prop(OBJ_I_RES_MAGIC, 10);
            add_prop(LIVE_I_QUICKNESS, 38);
            for(i = 0; i < 6; i++)
                set_base_stat(i, (mod+100)*150/200 +random(25));
            set_alignment((800 + random(400)) * a);
            teeth = ({ 55, 60 });
            claw = ({ 65, 50 });
            wing = ({ 50, 40 });
            skin = ({ 65, 75, 55, 55, 35 });
            penet = 300 + random(300);
            add_prop(CONT_I_HEIGHT, mod * 200 / 100);
            add_prop(CONT_I_WEIGHT, mod * 300000 / 100);
            add_prop(CONT_I_VOLUME, mod * 300000 / 66);
            add_leftover("/d/Krynn/common/weapons/dragontooth", "tooth", 1, "", 0, 1);
            set_exp_factor(150);
            break;
        default:
            age = "hatchling";
            add_name("hatchling");
            set_adj("dragon");
            for(i = 0; i < 6; i++)
                set_base_stat(i, (mod+100)*75/200 + random(25));
            set_alignment((300 + random(200)) * a);
            teeth = ({ 30, 30 });
            claw = ({ 40, 20 });
            wing = ({ 25, 20 });
            skin = ({ 30, 50, 20, 20, 10 });
            penet = 50 + random(50);
            add_prop(CONT_I_HEIGHT, mod * 100 / 100);
            add_prop(CONT_I_WEIGHT, mod * 40000 / 100);
            add_prop(CONT_I_VOLUME, mod * 40000 / 66);
            set_exp_factor(135);
            break;
    }
}

// Different breaths for dragons
void fire_breath()
{
    add_prop(OBJ_I_RES_FIRE, 100);
    breath_weapon = "a river of fire erupts from "+HIS_HER(TO)+
        " mouth!\n";
    res_prop = MAGIC_I_RES_FIRE;
    how = ({ "not harmed", "barely burned", "slightly burned",
        "burned quite badly", "burned very badly", "badly incinerated" });
}

void poison_breath()
{
    add_prop(OBJ_I_RES_POISON, 100);
    breath_weapon = "a cloud of noxious gas is blown from "+
        HIS_HER(TO)+" mouth!\n";
    res_prop = MAGIC_I_RES_POISON;
    how = ({ "not harmed", "barely choked", "choked", "harmed",
        "badly harmed", "severely harmed" });
}

void acid_breath()
{
    add_prop(OBJ_I_RES_ACID, 100);
    breath_weapon = "a stream of acid spews from "+HIS_HER(TO)+
        " mouth!\n";
    res_prop = MAGIC_I_RES_ACID;
    how = ({ "not harmed", "barely stung", "slightly singed", "singed",
        "badly corroded", "eaten alive" });
}

void electric_breath()
{
    add_prop(OBJ_I_RES_ELECTRICITY, 100);
    breath_weapon = "a bolt of lightning shoots from "+
        HIS_HER(TO)+" mouth!\n";
    res_prop = MAGIC_I_RES_ELECTRICITY;
    how = ({ "not harmed", "slightly shocked", "slightly burned",
        "shocked", "charred", "electrocuted" });
}

void cold_breath()
{
    add_prop(OBJ_I_RES_COLD, 100);
    breath_weapon = "a cone of frost bursts from "+HIS_HER(TO) +
        " mouth!\n";
    res_prop = MAGIC_I_RES_COLD;
    how = ({ "not harmed", "slightly chilled", "chilled", "chilled to "+
        "the bone", "frozen", "frozen solid" });
}

void light_breath()
{
    add_prop(OBJ_I_RES_LIGHT, 100);
    breath_weapon = "a cloud of blinding light bursts from "+HIS_HER(TO) +
        " mouth!\n";
    res_prop = MAGIC_I_RES_LIGHT;
    how = ({ "not harmed", "barely burned", "slightly burned",
        "burned quite badly", "burned very badly", "badly incinerated" });
}

void sound_breath()
{
    add_prop(OBJ_I_RES_AIR, 100);
    breath_weapon = "a wave of force erupts from "+HIS_HER(TO) +
        " mouth!\n";
    res_prop = MAGIC_I_RES_AIR;
    how = ({ "not harmed", "lightly touched", "slightly touched",
        "buffeted badly", "buffeted very badly", "badly pummelled" });
}

void water_breath()
{
    add_prop(OBJ_I_RES_WATER, 100);
    breath_weapon = "a cone of water blasts from "+HIS_HER(TO) +
        " mouth!\n";
    res_prop = MAGIC_I_RES_WATER;
    how = ({ "not harmed", "moist", "wet", "chilled", "chilled to the bone", 
        "battered hard with water" });
}


// End of breaths
void
create_creature()
{
    add_name("dragon");
    set_race_name("dragon");
    set_gender(random(2));
    set_long("@@long_desc");
    set_short("@@short_desc");

    set_skill(SS_DEFENCE,       100);
    set_skill(SS_BLIND_COMBAT,  100);
    set_skill(SS_UNARM_COMBAT,  100);
    set_skill(SS_PARRY,         100);
    set_skill(SS_AWARENESS,     100);

    create_dragon_npc();

//    add_leftover("/d/Krynn/common/commerce/scale", "scale", 1, "", 0, 1);

    /* Setting the attack and armour values for the dragons */

    remove_attack(512);
    remove_attack(1024);
    remove_attack(1536);
    remove_attack(2049);
    remove_attack(4096);
    set_attack_unarmed(1, wing[0], wing[1], W_BLUDGEON, 15, "right wing");
    set_attack_unarmed(2, wing[0], wing[1], W_BLUDGEON, 15, "left wing");
    set_attack_unarmed(3, claw[0], claw[1], W_SLASH, 35, "right claw");
    set_attack_unarmed(4, claw[0], claw[1], W_SLASH, 35, "left claw");
    //set_attack_unarmed(W_NONE, teeth[0], teeth[1], W_IMPALE, 30, "bite");

    set_hitloc_unarmed(1, skin[0], 20, "head");
    set_hitloc_unarmed(2, skin[1], 40, "body");
    set_hitloc_unarmed(3, skin[2], 25, "tail");
    set_hitloc_unarmed(4, skin[3], 14, "wings");
    set_hitloc_unarmed(5, skin[4], 1, "belly");

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop("_live_m_no_drain", 
        "The scales of the dragon are too strong for you to bite through!\n");
}

string
long_desc()
{
    return (age == "hatchling" ? "The dragon "+age : "The "+age+" dragon") +
    " is covered with "+colour+" scales.\n";
}

string
short_desc()
{
    return (age == "hatchling" ? colour+" dragon "+age : age+" "+colour+" dragon");
}


int
special_attack(object enemy)
{
    int i, attacktype;
    mixed* hitresult;
    object me, *ob;
    object *others = enemy->query_team_others();

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

        tell_room(E(TO), QCTNAME(TO)+" rises to "+HIS_HER(TO)+" full "+
          "height, and you hear a sharp intake of breath as "+HE_SHE(TO)+
          " rears back "+HIS_HER(TO)+" head...\n", TO, TO);
        forced_attacktype = 1;
        return 1;
    }

    tell_room(E(TO), "As "+QTNAME(TO)+"'s head descends, "+breath_weapon,
      TO, TO);

    /* We will hit everyone in the room with the blast we breathe */
    ob = FILTER_LIVE((all_inventory(E(TO))) - ({ TO }));
    // ob = query_enemy(-1); /* OLD KRYNN WAY */
    for (i = 0; i < sizeof(ob); i++)
    {
        if(E(ob[i]) != E(TO))
        continue;

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

public void
init_living()
{
    ::init_living();
}

public varargs void
react_introduce(mixed who = 0)
{
    if (!who)
    set_alarm(2.0, 0.0, &command("introduce me"));
    else
    set_alarm(2.0, 0.0, &command("introduce me to " + who));
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
