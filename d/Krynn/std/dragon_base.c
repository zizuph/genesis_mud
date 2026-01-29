/* Dragon base file by Morrigan 11/17/96 */
/* Some features and props added by Teth, Feb 20 1997 */
/* including introing and no run away */
/* also added 'decrepit' age. */

/* Original code for Ember by Jeremiah referenced, and the code for the
* dragonfear functions is taken directly from it.
*/

/*
 * Last update by Milan 10.10.98.
 *
 * Changes:
 * - Fixed adjectives (only proper ones are set)
 * - test_friend function not used in special_attack. Dragon uses breath at all
 *   fighting enemies (why should it not breath at friend if fighting him?).
 * - new dragon_fear object used
 * - changed long description (old one was too plain ;)
 *
 * 16.10.98
 * - fixed height, weight and volume
 *   height: 100 200 400 420 420 430 (that's height, not length ;-)
 *   weight: 40000 300000 600000 620000 650000 700000
 *         volume = weight * 1.5;
 *   modifiers according to color
 *   red 100%, blue 90%, green 75%, black 65%, white 50%
 *   gold 105%, silver 100%, copper 75%, bronze 90%, brass 65%
 *   (stat modifier is only 1/2 of above)
 *
 * 04.02.04
 *   Added xp modifiers to the various dragon ages.
 *   Arman
 *
 * 26.02.04
 *   Added additional leftovers (tooth and dragonbone)
 *   Arman
 *
 * 27.05.10
 *   Added check for query_not_attack_me for special_attacks
 *   Petros
 * 
 * 21.12.13
 *   Changed to use dragon_fear_new instead of dragon_fear
 *   Petros
 * 2022-02-06
 *   Removed magic resistance - natural armour provides that instead.
 *   Zizuph
 */

#pragma strict_types
#pragma save_binary

#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <filter_funs.h>

inherit C_FILE

inherit "/std/act/domove";
inherit "/std/act/action";

#define DRAGON_FEAR (KROBJECT + "dragon_fear_new")

int penet, *teeth, *claw, *wing, *skin;
string *how, breath_weapon, res_prop, how_str;
string colour = "red";
string age = "adult";

int forced_attacktype = 0;
int do_intro = 0;

/* prototype */
void setup_dragon();

public int
ansalon_krynn_dragon()
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
    case "gold":
    mod = 105;
    a = 1;
    break;
    case "silver":
    mod = 100;
    a = 1;
    break;
    case "bronze":
    mod = 90;
    a = 1;
    break;
    case "copper":
    mod = 75;
    a = 1;
    break;
    case "brass":
    mod = 65;
    a = 1;
    break;
    case "blue":
    mod = 90;
    a = -1;
    break;
    case "green":
    mod = 75;
    a = -1;
    break;
    case "black":
    mod = 65;
    a = -1;
    break;
    case "white":
    mod = 50;
    a = -1;
    break;
    default:
    colour = "red";
    mod = 100;
    a = -1;
    }
    set_adj(colour);

    switch(age)
    {
    case "decrepit":
    set_adj("decrepit");
    add_prop(LIVE_I_SEE_DARK, 2);
    //add_prop(OBJ_I_RES_MAGIC, 40);
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
    //add_prop(OBJ_I_RES_MAGIC, 50);
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
    //add_prop(OBJ_I_RES_MAGIC, 40);
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
    //add_prop(OBJ_I_RES_MAGIC, 30);
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
    //add_prop(OBJ_I_RES_MAGIC, 10);
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

    if (a == -1)
    set_knight_prestige(-2 * query_alignment() + -1 * random(query_alignment()));
    else
    set_knight_prestige(-10 - random(7));

    /* Good dragons have various gas breaths as well that disable their opponent */
    /* Perhaps this could be added at a later date? */

    switch(colour)
    {
    case "silver":
    case "white":
    add_prop(OBJ_I_RES_COLD, 100);
    breath_weapon = "a cone of frost bursts from "+HIS(TO)+" mouth!\n";
    res_prop = MAGIC_I_RES_COLD;
    how = ({ "not harmed", "slightly chilled", "chilled", "chilled to "+
      "the bone", "frozen", "frozen solid" });
    break;
    case "bronze":
    case "blue":
    add_prop(OBJ_I_RES_ELECTRICITY, 100);
    breath_weapon = "a bolt of lightning shoots from "+HIS(TO)+" mouth!\n";
    res_prop = MAGIC_I_RES_ELECTRICITY;
    how = ({ "not harmed", "slightly shocked", "slightly burned", "shocked",
      "charred", "electrocuted" });
    break;
    case "copper":
    case "black":
    add_prop(OBJ_I_RES_ACID, 100);
    breath_weapon = "a stream of acid spews from "+HIS(TO)+" mouth!\n";
    res_prop = MAGIC_I_RES_ACID;
    how = ({ "not harmed", "barely stung", "slightly singed", "singed",
      "badly corroded", "eaten alive" });
    break;
    case "green":
    add_prop(OBJ_I_RES_POISON, 100);
    breath_weapon = "a cloud of noxious gas is blown from "+HIS(TO)+" mouth!\n";
    res_prop = MAGIC_I_RES_POISON;
    how = ({ "not harmed", "barely choked", "choked", "harmed",
      "badly harmed", "severely harmed" });
    break;
    case "brass":
    add_prop(OBJ_I_RES_FIRE, 100);
    breath_weapon = "waves of heat are cast from "+HIS(TO)+" mouth!\n";
    res_prop = MAGIC_I_RES_FIRE;
    how = ({ "not harmed", "slightly burned", "burned", "injured",
      "burned badly", "caused to collapse" });
    break;
    default: /* "gold" and "red" */
    add_prop(OBJ_I_RES_FIRE, 100);
    breath_weapon = "a river of flame erupts from "+HIS(TO)+" mouth!\n";
    res_prop = MAGIC_I_RES_FIRE;
    how = ({ "not harmed", "barely burned", "slightly burned",
      "burned quite badly", "burned very badly", "badly incinerated" });
    }
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

    add_leftover("/d/Krynn/common/commerce/scale", "scale", 1, "", 0, 1);

    /* Setting the attack and armour values for the dragons */
    set_attack_unarmed(0, teeth[0], teeth[1], W_IMPALE, 30, "bite");
    set_attack_unarmed(1, wing[0], wing[1], W_BLUDGEON, 15, "right wing");
    set_attack_unarmed(2, wing[0], wing[1], W_BLUDGEON, 15, "left wing");
    set_attack_unarmed(3, claw[0], claw[1], W_SLASH, 45, "right claw");
    set_attack_unarmed(4, claw[0], claw[1], W_SLASH, 45, "left claw");

    set_hitloc_unarmed(0, skin[0], 20, "head");
    set_hitloc_unarmed(1, skin[1], 40, "body");
    set_hitloc_unarmed(2, skin[2], 25, "tail");
    set_hitloc_unarmed(3, skin[3], 14, "wing");
    set_hitloc_unarmed(4, skin[4], 1, "belly");

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
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

/* I left this function here. It may be used in files that inherit this. */
int
test_friend(object who)
{
    int j;
    string *friend_list = ({ "verminaard", "aridor" });

    if (friend_list)
    {
    for(j=0; j < sizeof(friend_list); j++)
        if (who->query_real_name() == friend_list[j])
        return 1;
    }
    return 0;
}

int
special_attack(object enemy)
{
    int i, attacktype;
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

        tell_room(E(TO), QCTNAME(TO)+" rises to "+HIS(TO)+" full "+
          "height, and you hear a sharp intake of breath as "+HE(TO)+
          " rears back "+HIS(TO)+" head...\n", TO, TO);
        forced_attacktype = 1;
        return 1;
    }

    tell_room(E(TO), "As "+QTNAME(TO)+"'s head descends, "+breath_weapon,
      TO, TO);

    ob = query_enemy(-1);
    for (i = 0; i < sizeof(ob); i++)
    {
        if(E(ob[i]) != E(TO))
        continue;

        if (ob[i]->query_not_attack_me(me, -1))
        {
            continue; // attack was blocked, move onto the next attack
        }
        
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

public object
clone_dragon_fear_object()
{
    setuid();
    seteuid(getuid());
    return clone_object(DRAGON_FEAR);
}

private void
dragon_fear_player(object who)
{
    object *inv;
    if(!objectp(who))
    return;
    if(QRACE(who) == "draconian" || QRACE(who) == "dragon")
    {
    return;
    }
    inv = filter(all_inventory(who), &->ansalon_krynn_dragonfear());
    if(sizeof(inv))
    {
    inv[0]->slow_refresh_dragon_fear();
    }
    else
    {
        clone_dragon_fear_object()->move(who, 1);
    }
}

public void
init_living()
{
    ::init_living();

    set_alarm(0.1, 0.0, &dragon_fear_player(TP));
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
