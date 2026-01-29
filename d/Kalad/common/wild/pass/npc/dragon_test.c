/*
 * /d/Kalad/common/wild/pass/npc/deep_dragon.c
 * Purpose    : This is the dreaded deep dragon, for sword of thanar quest
 * Located    : /d/Kalad/common/wild/pass/underdark/u37
 * Created By : Antharanos ??.??.??
 * Modified By: Ibun May 2007
 */
#pragma strict_types
inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
int heal;

void
create_monster()
{
    int i;

    set_name("shadowgloom");
    set_race_name("dragon");
    set_adj("deep");
    set_short("deep dragon");
    set_long("A horrible and magnificent creature, its iridescent maroon "+
      "scales make it appear as if it were covered not in scales, but in red "+
      "gems of the finest quality. The sheer size of the creature, over one "+
      "hundred feet in length, makes you wonder how it could have gotten "+
      "into this relatively cramped cave. Upon its chest is a " +
      "particularly large and triangular scale.\n");
    set_gender(G_MALE);
    for (i = 0; i < 3; i++)
        set_base_stat(i, 150 + random(50));
    set_base_stat(3, 150);
    set_base_stat(4, 150);
    set_base_stat(5, 150);
    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_AWARENESS,100);
    set_skill(SS_SPELLCRAFT,75);
    set_knight_prestige(1200);
    set_alignment(-1200);
    set_attack_unarmed(0, 60, 60, W_IMPALE, 24, "horrifying bite");
    set_attack_unarmed(1, 60, 60, W_BLUDGEON, 12, "powerful right wing");
    set_attack_unarmed(2, 60, 60, W_BLUDGEON, 12, "powerful left wing");
    set_attack_unarmed(3, 50, 50, W_SLASH, 16, "sharp right claws");
    set_attack_unarmed(4, 60, 60, W_SLASH, 16, "sharp left claws");
    set_attack_unarmed(5, 60, 80, W_BLUDGEON, 20, "massive tail");
    set_hitloc_unarmed(0, 90, 10, "great horned head");
    set_hitloc_unarmed(1, 120, 40, "gigantic body");
    set_hitloc_unarmed(2, 80, 20, "long tail");
    set_hitloc_unarmed(3, 85, 20, "bulky legs");
    set_hitloc_unarmed(4, 40, 10, "sweeping wings");
    add_leftover("/d/Kalad/common/wild/pass/obj/dragon_skin","skin", 1," ", 1, 1);
    add_leftover("/d/Kalad/common/wild/pass/arm/dragon_scale","scale", 1," ", 1, 1);
    add_prop(LIVE_I_SEE_DARK, 1000);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_VOLUME, 5679000);
    add_prop(CONT_I_WEIGHT, 5784000);
    add_prop(OBJ_I_RES_FIRE, 100);    // Fire immune
    add_prop(OBJ_I_RES_COLD, -20);    // Vulnerable to coldattacks
    set_act_time(3);
    add_act(({"kill human", "kill elf", "kill dwarf", "kill gnome",
        "kill hobbit","kill goblin"}));
}

int
react_sword(object who)
{
    if(who)
    {
        set_alarm(5.0,0.0,"return_sword", who);
        command("say Ahh...the sword has returned.");
        return 1;
    }
}

void
return_sword(object who)
{
    object *ob;
    mixed *hitresult;
    object *items;
    int i;
    int found = 0;
    int penet;

    if(present(who, environment()))
    {
        command("get foul stygion-black sword");
        items = all_inventory(TO);
        for (i=0; i < sizeof(items); i++)
            if (items[i]->query_short() == "foul stygion-black sword")
                found++;

        if (!found)
        {
            command("emote seems to work itself into a wild frenzy, with fire "+
                "streaming out from its nostrils!");
            tell_room(E(TO),"In a fury of fire and death the dragon roars: "+
                "Mortal fool! Dare you challenge me in this way? That sword "+
                "shall be mine and I shall pick it from your burning corpse!\n");
            ob = FILTER_LIVE(all_inventory(environment(TO))) - ({ TO });

            for (i = 0; i < sizeof(ob); i++)
            {
                penet = 600 + random(1200);
                penet -= penet * ob[i]->query_magic_res(MAGIC_I_RES_FIRE) / 50;
                hitresult = ob[i]->hit_me(penet, MAGIC_DT, TO, -1);
                tell_room(E(TO),"An inferno of flames bursts out from the "+
                    "mouth of the Deep Dragon, and envelopes your body "+
                    "with a devastating heat!\n");
            }
            command("kill "+ who->query_real_name());
            return;
        }

    command("emote makes a strange gasping noise.");
    command("say Ahh, you have brought me the sword of Thanar!");
    command("say Yes, you have done quite well...I shall give you a "+
        "gift of my own...");
    object sword = clone_object("/d/Kalad/common/wild/pass/wep/sword_of_solara");
    sword->move(TO);
    command("drop sword");
    command("get pure snow-white sword");
    command("back");
    command("drop pure snow-white sword");
    command("say This sword is a little something I acquired from Kabal..."+
        "I 'relieved' several priests of it.");
    command("grin");
    command("say Now you may have it, since it is of no use to me.");
    command("say Now leave, before I decide to kill you.");
    }
}

int
react_attack(object who)
{
    if(who)
    {
        set_alarm(2.0,0.0,"return_attack", who);
        return 1;
    }
    return 0;
}

void
return_attack(object who)
{

    if(present(who, environment()))
    {
        command("snarl " + (who->query_real_name()));
        command("kill " + (who->query_real_name()));
        return;
    }
    return;
}

void
tell_watcher(string str, object enemy)
{
    object me, *ob;
    int i;
    ob = FILTER_LIVE(all_inventory(environment(TO))) - ({ TO });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
    if (ob[i]->query_see_blood())
        ob[i]->catch_msg(str);
}

int
special_attack(object enemy)
{
    int attacktype, i, penet;
    mixed* hitresult;
    string how;
    object *ob;
    attacktype = random(10);

    switch (attacktype)
    {
        case 0:
        {
            ob =  FILTER_LIVE(all_inventory(environment(TO))) - ({ TO });
            for (i = 0; i < sizeof(ob); i++)
            {
                penet = 600 + random(600);
                penet -= penet * ob[i]->query_magic_res(MAGIC_I_RES_FIRE) / 50;
                hitresult = ob[i]->hit_me(penet, MAGIC_DT, TO, -1);
                how = "not harmed";
                if (hitresult[0] > 0)
                    how == "barely burned";
                if (hitresult[0] > 10)
                    how = "slightly burned";
                if (hitresult[0] > 20)
                    how = "burned quite badly";
                if (hitresult[0] > 40)
                    how = "burned very badly";
                if (hitresult[0] > 60)
                    how = "utterly devastated";
                ob[i]->catch_msg("You hear a sharp intake of breath " +
                    "and then a deadly stream of acidic spittle shoots " +
                    "forth from the dragon's mouth at you!\n");
                ob[i]->catch_msg("You were " + how + " by the dragon breath!\n");
                tell_watcher(QCTNAME(ob[i]) + " is " + how + " by " +
                    "the dragon breath!\n", ob[i]);
                if (ob[i]->query_hp() <= 0)
                    ob[i]->do_die(TO);
            }
            return 1;
        }

        case 1:
        {
            if (heal <= 5)
                return 0;
            heal++;
            say("The deep dragon begins to lick its wounds...\n");
            say("The deep dragon looks much better!\n");
            TO->heal_hp(2000);
            return 1;
        }
    }
    return 1;
}

void
reset_heal()
{
    heal = 0;
}

