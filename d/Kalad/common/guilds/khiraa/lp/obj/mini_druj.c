inherit "/d/Kalad/common/raum/std/undead_std.c";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"

string gRace;

string
query_race()
{
    return gRace;
}

void
set_race(string str)
{
    gRace = str;
}

void
create_monster() 
{
   ::create_monster();
   set_name("hand");
   add_name("druj");
   set_race_name("hand");
   set_adj("crawling");
   add_adj("dismembered");
   set_short("crawling dismembered @@query_race@@ hand");

   set_long("You look at what appears to be a dismembered hand, only "+
   "it is moving and wiggling! It crawls around, leaving a bloody "+
   "trail from its torn stump at the wrist. A most horrible sight.\n");

   set_gender(G_NEUTER);

   set_stats(({1,1,1,1,1,1}));

   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_I_NO_CORPSE,1);
   add_prop(LIVE_I_SEE_DARK, 100);
   add_prop(OBJ_I_WEIGHT, 6500);
   add_prop(OBJ_I_VOLUME, 3500);
   add_prop(LIVE_I_UNDEAD,2);
   set_alignment(-10);
   set_knight_prestige(10);
    set_act_time(6);
    add_act("emote wiggles around horribly.");
    add_act("emote slowly twitches.");
    add_act("emote slowly crawls around in a circle.");
   set_attack_unarmed(0, 40, 50, W_SLASH,  50, "hand");
   set_attack_unarmed(1, 40, 50, W_IMPALE, 50, "hand");
   set_hitloc_unarmed(0,43,70,"palm");
   set_hitloc_unarmed(1,43,30,"fingers");
    set_m_out("crawls");
    set_m_in("crawls in.");
    set_random_move(4);
}


query_combat_file()
{ return "/d/Kalad/common/raum/std/drujplain.c"; }


void
do_die(object killer)
{
    command("ffinger "+killer->query_real_name());
    command("emote vaporizes into the air.");
    ::do_die(killer);
}
