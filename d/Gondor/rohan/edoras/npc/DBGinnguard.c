inherit "/std/monster";
#include <ss_types.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void arm_me();

object  fastred,
        attacker;
int     minstat;

void
create_monster()
{
    set_name("guard");
    add_pname("men");
    set_adj(({"rohirrim", "brave"}));
    set_short("rohirrim guard");
    set_race_name("human"); 
    // add name 'rohirrim' as last to be able to use 'rohirrim' as adj, too
    add_name(({"man", "rohirrim" }));
    set_long(BSN("This brave Rohirrim guard looks strong. His long braided long "
      + "hair falls down onto his shoulders."));
    fastred = find_living("DBGfastred");
    attacker = fastred->query_attacker_name();
    minstat = fastred->query_attack_stat();
    if (minstat < 50)
        minstat = 50;
    set_stats(({ minstat+20+random(20) , minstat+20+random(20), minstat+20+random(20),
                 minstat-10, minstat-20, minstat+30 }));
    set_skill(SS_WEP_SWORD,minstat+20);
    set_skill(SS_PARRY,minstat+20);
    set_skill(SS_DEFENCE,minstat+20);
    set_skill(SS_2H_COMBAT,minstat+20);
    set_alignment(150 + random(150));
    seq_new("do_things");
    seq_addfirst("do_things",({"@@arm_me","say Where is the attacker?"}));
    set_chat_time(20);
    add_chat("He who attacks a rohirrim in Edoras, will die!");
    add_chat("By Eorl! Vanquish foe!");
    add_cchat("Alarm! Invaders in Rohan!");
    add_cchat("Help! Foes in the town!");
    add_cchat("Woe to you, deceiving enemy!");
}

void
arm_me()
{
    FIX_EUID

    clone_object(EDORAS_DIR + "obj/guardsword")->move(TO);
    command("wield sword");

    clone_object(EDORAS_DIR + "obj/corslet")->move(TO);
    command("wear armour");
}

void
start_attack()
{
  command("open door");
  command("shout Die, " + attacker->query_race_name() + "!");
  command("east");
  command("close door");
  command("shout You will die now, " + attacker->query_nonmet_name() + "!");
  command("kill " + attacker->query_real_name());
  command("shout Why did you attack the inn?");
}

void
end_attack()
{
  move_living("west", EDORAS_DIR + "guard_w");
  this_object()->remove_object();
}

void
reset_inn()
{
    fastred = find_living("DBGfastred");
    if (objectp(fastred))
        fastred->reset_inn();
}

void
notify_you_killed_me(object player)
{
    if (player->query_npc())
        return;
    seteuid(getuid(this_object()));
    write_file(LOG_DIR + "goodkill", player->query_name()+" was killed by "
      + this_object()->query_name()+" on "+ctime(time())+".\n");
    set_alarm(4.0, 0.0, reset_inn);
    return;
}

/* Solemnian prestige */
int
query_knight_prestige() {return (-6);}
