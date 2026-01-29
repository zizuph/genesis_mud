inherit "/std/weapon";
#include "/d/Shire/common/defs.h"
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>

void create_weapon() 
{
    set_name("morningstar");
    add_name(({"star","club","morning-star"}));
    set_adj(({"spiked","steel","blue"}));
    set_short("spiked steel morningstar");
    set_pshort("spiked steel morningstars");
    set_long("This "+short()+" has a short length of chain that "+
      "holds the spiked ball to the handle. The handle is a short "+
      "shaft of lacquered blue steel, with a grip that consists of "+
      "intertwined braids of gold and silver wire. The ball itself "+
      "is blued steel, the spikes alternately plated gold and "+
      "silver. The chain is forged of the same blued steel that "+
      "composes the rest of the "+short()+".\n");
    set_default_weapon(25,33,W_CLUB,W_IMPALE | W_BLUDGEON,W_ANYH,TO);
    set_pm(({-5,0,5}));
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(29,W_CLUB) + random(151));
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(25,29) + 100 + random(51));
    add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON);
}


init()
{
    ::init();
    add_action("twirl_me","twirl");
}

int twirl_me(string what)
{
    if(!what) { notify_fail("Twirl what?\n"); return 0; }
    if(!strlen(what)) { notify_fail("Twirl what?\n"); return 0; }

    if(!TO->query_wielded()) 
    {
	write("Perhaps you had better wield the "+short()+" first?\n");
	return 1; 
    }

    switch(what)
    {
    case "idly":
	write("You twirl the "+short()+" idly.\n");
	say(QCTNAME(TP)+" idly twirls "+HIS_HER(TP)+" "+short()+".\n");
	break;
    case "combat":
	write("You twirl the "+short()+" over your head in preparation "+
	  "for attack!\n");
	say(QCTNAME(TP)+" twirls the "+short()+" over "+HIS_HER(TP)+ 
	  " head, evidently preparing for an attack!\n");
	break;
    case "threat":  case "threateningly":
	write("You twirl the "+short()+" violently, causing "+
	  "the spiked head to whistle through the air threateningly.\n");
	say(QCTNAME(TP)+" twirls the "+short()+" quickly, causing the "+
	  "spiked ball to whistle as it passes dangerously close "+
	  "to your head.\n");
	break;
    default:
	write("Perhaps you'd like to twirl the "+short()+" <idly>, "+
	  "in preparation for <combat>, or <threateningly>?\n");
	break;
    }
    return 1;
}


did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    if(TP->query_intoxicated()>TP->intoxicated_max()/(2+random(3)))
    {
	if(random(5))
	{
	    wielder->catch_msg("You smash yourself with the spiked "+
	      "ball of the "+short()+".\n");
	    tell_room(ENV(wielder),QCTNAME(wielder)+" smashes the spiked "+
	      "ball of the "+short()+" into "+HIM_HER(wielder)+"self"+
	      ".\n",wielder);
	    wielder->heal_hp(-dam);
	    enemy->heal_hp(dam);
	    return 1;
	}
	else
	{
	    wielder->catch_msg("You swing the spiked ball of the "+short()+
	      " around wildly, missing everything in sight.\n");
	    tell_room(ENV(wielder),QCTNAME(wielder)+" swings the spiked "+
	      "ball of the "+short()+" around wildly, hitting only air.\n",
	      wielder);
	    enemy->heal_hp(dam);
	    return 1;
	}
    }
}

