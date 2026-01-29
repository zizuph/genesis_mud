/* The normal guards by Percy. */
/* Changed just a bit to guard Kentari's Vault */
// defense raised and do_heal func added by Grace 20 Sept 1995

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solamn/guild/guild.h"
#include "/d/Krynn/solamn/guild/local.h"
#include <macros.h>

inherit "/d/Krynn/common/monster/knight_base";

#define OUTKEEP    VDIR + "outkeep"

int i_am_alarmed = 0;
int cloned;

string
query_the_name()
{
    return "the knight human";
}

void
create_knight_npc()
{
	int i;
	set_name("guard");
	set_short("knight guard");
	set_long("This is a guard on duty, guarding the keep. He looks " +
		 "to be very vigilant.\n");
	for (i = 0; i < 6; i++)
		set_base_stat(i, 50 + random(6));
        set_stat_extra(2, 70);
        set_all_attack_unarmed(60, 60);
        set_all_hitloc_unarmed(60);
        set_skill(SS_DEFENCE, 80 + random(10));
        add_cact("@@do_heal");
	
	cloned = 0;
}
void
init_living()
{
    ::init_living();
    ADD("alarm_me","alarm");
}

int
alarm_me(string str)
{
    NF("What?\n");
    if (!(TP->id("knight") || MEMBER(TP) || LAYMAN(TP)))
      return 0;
    if (E(TO) == find_object(OUTKEEP))
      return 0;
    if (i_am_alarmed)
      return 0;
    if (str == "guard" || str == "guards")
      {
	  i_am_alarmed = 1;
	  NF("You alarm the guards.\n");
	  if (str == "guards")
	    command("alarm guards");
	  else
	    write("You alarm a guard.\n");
	  command("southeast");
	  command("southwest");
	  command("south");
	  do_rescue();
	  return 1;
      }
    return 0;
}

void
set_me_alarmed(int i)
{
    i_am_alarmed = i;
}

void
do_heal()
{
      command("smile joy");
      TO->heal_hp(100+random(50));
}

public void
attacked_by(object ob)
{
   ::attacked_by(ob);
   command("emote prays to Paladine for divine intervention against " +
	"this new enemy.\n");
   seteuid(getuid());
   if (cloned == 0)
clone_object("/d/Krynn/kentari/mnstrs/v-humasp")->move(environment());
cloned = 1;
}  
