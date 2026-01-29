inherit "/std/weapon.c";
#include "/sys/wa_types.h"
#include "defs.h"

create_weapon()
{
    set_name(({"club","_oclub_"}));
   set_adj("huge");
   add_adj("obsidian");
   set_long("This is a massive club. It is basically a large obsidian "
	+"stalagtite that looks to have been torn from the roof of a "
	+"cave. It has some leather wrapped around the handle to "
        +"protect the wielders hands from harm. It must weigh a ton, "
        +"and looks so huge it would be easier to roll (perhaps via "
        +"'rollclub <direction>') then carry.\n");
   set_hit(10);
   set_pen(40);
   set_hands(W_BOTH);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   set_wf(TO);
   add_prop(OBJ_I_WEIGHT,50000);
   add_prop(OBJ_I_VOLUME,18000);
   add_prop(OBJ_M_NO_SELL, "You want me to buy a large rock?\n");
}
mixed
wield(object what)
{
   if (TP->query_skill(SS_WEP_CLUB) > 30)
   if (TP->query_base_stat(SS_STR) > 85)
   if (TP->query_base_stat(SS_CON) > 85)
      {
	write("You manage to lift the huge club from the ground.\n");
      return 0;
      }
     return "You are too weak and pitiful to handle this weapon!\n";
}

init()
{
    ::init();
    add_action("roll","rollclub");
}
 
int
roll(string dest)
{
    object roller=this_player();
    object club=this_object();
    object locale=environment(roller);
    string destpath;
    string *destarr;
    int where;
 
    if (environment(club)==roller)
    {
        roller->catch_msg("It is difficult to roll huge obsidian "
             +"clubs while carrying them.\n");
        return 1;
    }
 
    if (roller->query_attack())
    {
        roller->catch_msg("It is not easy to roll stuff around in "
             +"the middle of a battle.\n");
        return 1;
    }
 
 
    where=(member_array(dest,locale->query_obvious_exits()));
    if (where<0)
    {
        roller->catch_msg("Roll it where?\n");
        return 1;
    }
 
    destarr=(locale->query_exit());
 
    destpath=destarr[member_array(dest,destarr)-1];
    
    club->move(destpath, 1);
    roller->catch_msg("You roll the club towards the "+dest+".\n");
    say(QCTNAME(roller)+" rolls a huge club towards the "+dest+".\n");
    roller->command(dest);
    return 1;
}
