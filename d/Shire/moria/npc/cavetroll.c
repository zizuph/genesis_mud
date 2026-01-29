
/*  -*- LPC -*-  */
/* Functions from ~Gondor/morgul/ithil_monster.c have been added
 * here to make the trolls help each other in a fight. Thanks to
 * Elessar for allowing this blatant cut and paste job.
 * Glaurung 4-18-96
 */


inherit "/std/monster";
inherit "/std/act/attack";
inherit "/lib/unique";

#include <stdproperties.h>
#include <formulas.h>
#include "/d/Shire/common/defs.h"
#include "/d/Shire/common/make_money.h"

#define TROLL_HOME "/d/Shire/moria/mines"

#define ADJDESC ({ "red-eyed","brown-eyed","hideous","muscular","grey",\
      "ghastly","quarrelsome","greedy"})

#define LONGDESC ({\
      "looks fierceful and very powerful, with its eyes "+\
      "which look like they can kill on sight. He would make "+\
      "an awesome enemy if anyone dared to attack!\n",\
      "looks kind of stupid. He surely can not know how to swing a weapon.\n",\
      "looks ugly and has a good reason for being here. \n",\
      "appears very big and powerful, his arms like a thick tree and his body."+\
      "if he could get his arms around you, you would not breathe for a long time.\n",\
      "has a grey colored scale and looks very frightening. His eyes are just "+\
      "rolling round in his head, looking dangerous!\n",\
      "is ghastly looking and has a dangerous appearance! No one would dare to fight him.\n",\
      "has intestines hanging out of his mouth. He drools when looking at you.\n",\
      "has greedy looking eyes. He would not hesitate to steal your "+\
      "money or anything precious he could find.\n" })

#define TROLLSTAT ({ \
      ({ 220,160,200,40,20,150 }),\
      ({ 230,140,230,40,30,185 }),\
      ({ 240,170,260,60,20,190 }),\
      ({ 250,180,250,5,5,130 }),\
      ({ 200,190,250,5,5,130 }),\
      ({ 234,150,235,50,32,165 }),\
      ({ 200,230,240,10,5,140 }),\
      ({ 210,240,230,5,5,130 }) })


create_monster()
{
    seteuid(getuid());
    if (!IS_CLONE) 
	return;
    TO->create_troll_guard(random(8));
    add_prop(LIVE_I_NEVERKNOWN, 1);
}
/* global variables */
int attack_alarm;

/* prototypes */
void drink_up();
void test_can_see(object victim);
void help_friend(object ob, object friend);


create_troll_guard (int r)
{
    set_name(({"troll guard","guard","cave troll"}));
    add_name("_moria_troll");
    set_pname("guards");
    set_short(ADJDESC[r] + " cave troll");
    set_pshort("cave trolls");
    set_race_name("troll");
    set_adj(ADJDESC[r]);
    set_long("This is one of the trolls guarding the tunnels under "
	     +"Moria. The troll, or cave troll has a black scaly hide "
	     +"and is extremly tough. They shun sunlight, and most of them "
	     +"will turn into stone if they are struck by it. They prefer "
	     +"the illumination of fire to the glistering aura of the moon. "
	     +"These cave trolls are a horrible enemy as they fear no living "
	     +"thing. This cave troll, " + LONGDESC[r] );
   
    add_prop(CONT_I_WEIGHT, (300 + random(100)*1000));
    add_prop(CONT_I_HEIGHT, (300 + random(75)));
    add_prop(LIVE_I_SEE_DARK, 75);
    
    set_stats(TROLLSTAT[r]);
    
    set_alarm(3.0,0.0,"arm_me");
    set_alignment(-400 -random(150));
    set_aggressive(1);
    set_attack_chance(100);
    set_pick_up(0);
    
    set_skill(SS_UNARM_COMBAT, 0);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 50);
    
    MAKE_MONEY;
    
    set_act_time(3);
    add_act("ponder");
    add_act("scream");
    add_act("peek all");
    add_act("emote picks some guts out of his teeth!");
    add_act("stomp");
    add_act("emote growls: You shouldn't have come here!");
    add_act("emote growls: I shall enjoy killing you.");
    
    set_cact_time(10);
    add_cact("time");
    add_cact("emote growls: Taste the metal of my blade!");
    add_cact("emote growls: Run, coward, before I destroy you!");
    add_cact("scream");
    add_cact("emote grabs your head with his awesome huge fist and throws you away!!");
    add_cact("emote growls: You'll like it in the underground tunnels.");

    /* Cotillion for AoB - 2020-07-13 */
    set_exp_factor(140);
}

arm_me()
{
    object drink;
    object boots;
    int i;
    boots = clone_unique("/d/Shire/moria/arm/cboots", MAX_UNIQUE_ITEMS,
            "/d/Shire/moria/arm/boots");
    boots->move(this_object());
    clone_object(TROLLSH_DIR + "arm/rudeplate")->move(TO);
    clone_object("/d/Shire/moria/arm/gorget")->move(TO);

    command("wear all");
    clone_object(TROLLSH_DIR + "weapon/tr_scimitar")->move(TO);
    command("wield all");
    for (i = 0; i < 25; i++)
    {
        drink = clone_object("/d/Shire/moria/obj/orcdrink");
        drink->move(TO);
    }
    set_alarm(2.0 + itof(random(15)), 0.0, &drink_up());
}    

void
drink_up()
{
  if (present("_tarin_tar_", TO))
    command("drink all");
}

int
query_knight_prestige()
{
    return 400 + random(200);
}

int
moria_monster_filter(object monster)
{
   if (monster->id("_moria_troll"))
       return 1;
   return 0;
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
   object  room = ENV(TO),
          *arr;
   
   ::attacked_by(ob);

   while (!room->query_prop(ROOM_I_IS))
      room = ENV(room);
   arr = filter(all_inventory(room), moria_monster_filter);
   arr->notify_ob_attacked_me(TO, ob);
   set_alarm(150.0, 0.0, &drink_up());
}

/*
 * Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate
 *                attacker - The attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
   if (objectp(query_attack()))
      return;
   
   set_alarm(2.0, 0.0, &help_friend(attacker, TO));
}

void
do_attack(object victim)
{
/*
   if (objectp(query_attack()))
       return;
*/
   if (victim->query_npc())
       return;
   if (!present(victim, ENV(TO)))
       return;
   if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, victim))
   {
      if (!sizeof(get_alarm(attack_alarm)))
          attack_alarm = set_alarm(5.0, 10.0, &test_can_see(victim));
      command("shout Where is the enemy? I can't see him!");
      return;
   }
   command("kill "+victim->query_real_name());
}

/*
* Function name: help_friend
* Description:   Help my friends by attacking their attacker
* Arguments:     attacker - The person who attacked my friend
*/
void
help_friend(object ob, object friend)
{
   if (objectp(ob) && !objectp(query_attack()) &&
       present(ob, ENV(TO)) && F_DARE_ATTACK(TO, ob) &&
       CAN_SEE_IN_ROOM(TO) && CAN_SEE(TO, ob))
   {
       command("shout You will die for this, stinking "+ob->query_race_name()+
		"-!");
       do_attack(ob);
   }
}  

void
test_can_see(object victim)
{
    if (!present(victim,ENV(TO)))
    {
        remove_alarm(attack_alarm);
        attack_alarm = 0;
        return;
    }
    if (CAN_SEE_IN_ROOM(TO) && CAN_SEE(TO,victim))
    {
        remove_alarm(attack_alarm);
        attack_alarm = 0;
        do_attack(victim);
    }
}
