/*     Created by:  Sarr
 *     Location:
 *     Modified:    Toby, 970919 (fixed typos)
 *     Modified:    Alignment from -800 to -400.
 *     Modified:    Petros, 10/3/2010, Reduced clone_unique of rust-red weapon
 *                  and limited to one of each type in the realm. Also reduced
 *                  percentage chance of it cloning to increase the rarity of
 *                  the item.
 *
 *     Modified:    Increased the droprate somewhat of the items due to them
 *                  being ultrarare - A weapon working for a few hours that 
 *                  drops twice a year is just silly and poor 
 *                  gamedesign. 25/8/2020.
 */
/* 2017-09-07 Malus: Fixed special_attack check on fire resistance */

#include "defs.h"
inherit STD_MONSTER;
inherit "/d/Raumdor/lib/intro";
inherit "/lib/unique";

#define ITEMSPAWN_LOG(x,y)  write_file("/d/Raumdor/log/" + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
void arm_me();

/* Gorrtoth, the Beast Lord, Sarr */

void
create_monster()
{
    //::create_monster();
    set_name("gorrtoth");
    set_race_name("beast");
    set_adj("hulking");
    add_adj("monster");
    set_short("hulking monster beast");
    set_long(
      "This is creature before is an awesome sight. He stands 9 feet tall, " +
      "and looks like he weighs a ton, all of it muscle mass. His skin is " +
      "black, covering rippling muscles. Red eyes glow softly from within " +
      "deep dark eyes sockets. Shining ebony horns grow out of his head. A " +
      "row of spikes project out of his back along his spine. His arms are " +
      "as thick as tree trunks, and long nasty looking claws extend out of " +
      "his huge hands. He bends slightly over, so that he can fit in this " +
      "corridor. A short, spiked tail pokes out of from behind him. This " +
      "creature is certainly not one you would like to mess with.\n");
    set_stats(STAT_ARRAY(210));
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 120);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_AXE, 100);
    add_prop(OBJ_I_WEIGHT, 90000);
    add_prop(OBJ_I_VOLUME, 88000);
    add_prop(LIVE_I_UNDEAD, 120);
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(RANGER_M_NOT_DISARM, 1);
    set_alignment(-250);
    set_act_time(5);
    set_title("the Beast Lord");
    add_act("emote grunts.");
    add_act("emote looks down at you like you are some bug.");
    set_cact_time(3);
    add_cact("say You cannot defeat me, mortal.");
    add_cact("say Die fool!");
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    set_hitloc_unarmed(0, 60, 15, "head");
    set_hitloc_unarmed(1, 60, 10, "left arm");
    set_hitloc_unarmed(2, 60, 10, "right arm");
    set_hitloc_unarmed(3, 60, 45, "body");
    set_hitloc_unarmed(4, 60, 20, "legs");
    add_ask(({"help", "task", "job", "quest"}),
      "say Yes, there is something you could do for me. You could recover " +
      "the staff of Ages and give it to me. In return, I would part with a " +
      "book I have hidden away: The Necromonicon.",
      1);
    add_ask(({"book", "necronomicon"}),
      "say Yes, this I have hidden. It is most valuable to me. The only " +
      "thing I find more valuable to me than this book, whose worm-ridden " +
      "pages hold the secrets of forgotten lore, is that mystical staff.",
      1);
    add_ask(({"staff", "staff of Ages", "mystical staff of Ages",
              "mystical staff of ages", "staff of ages"}),
      "say The staff contains power from the Netherworld. I have not seen it " +
      "for many years. I have not left my duty here, but from what I have " +
      "heard from my unseen servants, is that it was last seen by a " +
      "traveller from Drakmere. An aged old man, who is known as Galbert.",
      1);
    add_ask(({"galbert", "old man"}),
      "say The aged old man still lives somewhere in that foul city.", 1);

    MONEY_MAKE_GC(random(15))->move(TO, 1);
    
    arm_me();
}


void
arm_me()
{
    object wep, magic_wep;
    
    int dice;
    
    dice = random(4);
    
    if (dice == 0)
    {
        wep = clone_unique(one_of_list(({
                  "/d/Raumdor/magical_weapons/2h_beast_naginata.c",
                  })),
        10, "/d/Raumdor/common/wep/bskatana", 0, 25);
        
        wep->move(this_object(), 1);
    }
    
    if (dice == 1)
    {
        wep = clone_unique(one_of_list(({
                  "/d/Raumdor/magical_weapons/2h_beast_mace.c",
                  })),
        10, "/d/Raumdor/common/wep/bskatana", 0, 25);
        
        wep->move(this_object(), 1);
    }
    
    if (dice == 2)
    {
        wep = clone_unique(one_of_list(({
                  "/d/Raumdor/magical_weapons/2h_beast_cleaver.c",
                  })),
        10, "/d/Raumdor/common/wep/bskatana", 0, 25);
        
        wep->move(this_object(), 1); 
    }
    
    if (dice == 3)
    {
        wep = clone_unique(one_of_list(({
                  "/d/Raumdor/magical_weapons/2h_beast_broadsword.c",
                  })),
        10, "/d/Raumdor/common/wep/bskatana", 0, 25);
        
        wep->move(this_object(), 1);
    }
    
    ITEMSPAWN_LOG("beastlord_weaponspawn_log",
                "The beastlord spawned with a "
                +wep->query_name()+".\n");    

    clone_object(COMMON_ARM_DIR + "utplate")->move(this_object(), 1);   
    
    this_object()->command("wear all");
    this_object()->command("wield all"); 
}


void
do_die(object killer)
{
    log_file("beast_killed",
      " --- " + capitalize(killer->query_real_name()) +
        " (Avg:" + killer->query_average_stat() + "), (Hp max:" +
        killer->query_max_hp() + "),(Hp left:" + killer->query_hp() +
        ") killed beast at " + extract(ctime(time())) + ".\n");

    ::do_die(killer);
}


mixed
query_option(int opt)
{
    return (opt == OPT_UNARMED_OFF);
}


void
return_staff(object ob, object from)
{
    ob->remove_object();
    command("emote rumbles: Yes, the staff is mine!");
    command("emote rumbles: I no longer need this, you may have it now, " +
            from->query_race_name() + ".");
    seteuid(getuid());
    clone_object(COMMON_OBJ_DIR + "necro_book")->move(TO);
    command("drop book");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (MASTER_OB(ob) == COMMON_WEP_DIR + "staff_of_ages" && living(from))
    {
        set_alarm(3.0, 0.0, &return_staff(ob, from));
    }
}

int
special_attack(object enemy)
{
    int i;
    if (random(6) != 0)
        return 0;
    i = random(6);
    if (i < 3)
    {
        enemy->heal_hp(-(random(TO->query_stat(0)) + 50));
        enemy->catch_msg(
          QCTNAME(TO) +
          " spins on his feet and roundhouse kicks you brutally!\n");
        tell_room(E(TO),
          QCTNAME(TO) + " spins on his feet and roundhouse kicks " +
            QTNAME(enemy) + " brutally!\n",
          enemy);
        if (enemy->query_hp() <= 0)
            enemy->do_die(TO);
        return 1;
    }
    else
    {
        enemy->catch_msg(QCTNAME(TO) +
                         " rears back his head, opens his mouth and showers " +
                         "you with red flames!\n");
        tell_room(E(TO),
          QCTNAME(TO) + " rears back his head, opens his mouth and showers " +
            QTNAME(enemy) + " with red flames!\n",
          enemy);
        if (TP->query_magic_res(MAGIC_I_RES_FIRE) >= 30)
        {
            enemy->heal_hp(-60);
            enemy->catch_msg("You are barely burnt.\n");
            tell_room(E(TO), CAP(HE(enemy)) + " is barely burnt.\n", enemy);
            if (enemy->query_hp() <= 0)
                enemy->do_die(TO);
            return 1;
        }
        else
        {
            enemy->heal_hp(-(random(200) + 150));
            enemy->catch_msg("You are burnt badly.\n");
            tell_room(E(TO), CAP(HE(enemy)) + " is burnt badly.\n", enemy);
            if (enemy->query_hp() <= 0)
                enemy->do_die(TO);
            return 1;
        }
    }
}

public string
race_sound()
{
    return "rumbles";
}

public int
query_panic()
{
    return 0;
}
