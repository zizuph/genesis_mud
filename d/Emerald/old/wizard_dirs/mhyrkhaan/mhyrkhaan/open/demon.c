inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by mhyrkhaan, with massive amounts of help from Lilith and Sarr */

void
create_monster()
{
   ::create_monster();
   set_name("tinytim");
   set_race_name("demon");
   set_adj("winged");
   add_adj("evil");
   set_long("This uholy abomination stands slightly taller than a human. It's "+
   "black skin is etched with rigid muscles, and it seems to be very unhappy. "+
   "Two huge bat-like wings are folded around it, wrapping its body like "+
   "a cape of flesh. Two large fangs are brimming with green syliva as it "+
   "sputters at you, ready for a fight!\n");
   set_stats(({120,110,150,90,70,120}));
   set_skill(SS_WEP_SWORD,75);
   set_skill(SS_DEFENCE,80);
   set_skill(SS_PARRY,70);
   add_prop(LIVE_O_ENEMY_CLING, 1);
   add_prop(LIVE_I_SEE_DARK,1);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   remove_prop(NPC_M_NO_ACCEPT_GIVE); 
   add_prop(CONT_I_WEIGHT,100000);
   add_prop(CONT_I_VOLUME,100000);
   set_act_time(20);
   add_act("emote hisses dangerously");
   set_alarm(1.0,0.0,"arm_me");
}

public void
enter_inv(object obj, object from)
{ 
    ::enter_inv(obj, from);

    if (obj->id("light_amulet"))
        set_alarm(2.0, 0.0, &remove_object());
    return;            
}

int
do_item_filter(object ob)
{
    return (ob->id("light_amulet"));
}

void
kill_player(object player)
{
    if (!present(player, environment(this_object())))
        return;

    command("say Your time is up foolish mortal, your soul shall be mine!");
    command("cackle demo");
    command("kill "+ player->query_real_name());
}

void
check_for_amulet(object player)
{
    object *light_amulet;
  
    if (!present(player, environment(this_object())))
        return;
  if (!player->query_prop("I_have_it"))
    {
      command("say to "+ player->query_name() +" Foolish mortal, finally after 600 "+
      "years of waiting the Amulet will be mine! I am here to cary out my orders "+
      "to take and destroy the Amulet. If you get in my way, I shall destroy you "+
      "as well, and hurl your pathetic soul into eternal darkness... "+
      "give it to me.... or DIE!");
        player->add_prop("I_have_it", 1);
        set_alarm(60.0, 0.0, &kill_player(player));
     }

    light_amulet = filter(deep_inventory(TP), do_item_filter);
    if (!sizeof(light_amulet))
        return;
    set_follow(player->query_real_name());

    if (!player->query_prop("I_have_it"))
    {
        player->add_prop("I_have_it", 1);
        set_alarm(60.0, 0.0, kill_player(TP));
    }
    return;
}

public void
init_living()
{
    ::init_living();
    if (interactive(this_player()))
        set_alarm(1.0, 0.0, &check_for_amulet(this_player()));
} 


void
arm_me()
{
    object wep;
    seteuid(getuid(TO));
    wep = clone_object("/d/Kalad/common/raum/ruins/floor1/wep/dsword.c");
    wep -> move(TO);
    command("wield all");
}