inherit "/std/weapon";

#include "/d/Cirath/common/defs.h"
#include <wa_types.h>
#include <poison_types.h>

//int poison_used;

void
create_weapon()
{
    ::create_weapon();
   set_name("dagger");
   set_adj("cold");
   add_adj("blackened");
   set_pname("daggers");
   set_short("cold blackened dagger");
   set_pshort("cold blackened daggers");
    set_long("@@long_desc");
   set_hit(39);
   set_pen(42);
    set_wf(TO);
   set_hands(W_ANYH);
   set_wt(W_KNIFE);
   set_dt(W_IMPALE|W_SLASH);
    add_prop(OBJ_S_WIZINFO, "This dagger has been enchanted to provide "
	+"a very high hit/pen(39/42) as well as having a coating of "
	+"poison on the blade.  It requires a 100 dex to wield it.\n");
    add_prop(MAGIC_AM_ID_INFO,({"The dagger is definitely magical.\n", 5,
        "It seems to have a strong magical poison on the blade.\n", 25,
        "Only the most lithe and graceful will be able to harness its "
	+"power.\n",51}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 75, "enchantment" }));
    add_prop(OBJ_I_VALUE, 960);
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,1000);
    add_prop(OBJ_M_NO_BUY, 1);

//    poison_used = 0;
}

string
long_desc()
{
  /*  if (poison_used)

        return "A slim razor sharp dagger made from some sort of blackened "
	+"steel, this dagger looks evil.  It has a blade no more than an "
	+"inch wide, that curves gently along its twelve inch length and "
	+"is lightly serrated.  It looks like it could slive through "
	+"armor and flesh easily.\n";
    else*/
        return "A slim razor sharp dagger made from some sort of blackened "
	+"steel, this dagger looks evil.  It has a blade no more than an "
	+"inch wide, that curves gently along its twelve inch length and "
	+"is lightly serrated.  It looks like it could slive through "
	+"armor and flesh easily.  You notice what appears to be a fine "
	+"coating of some sort of fluid on the blade as well.\n";

}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    object poison;

    if (random(10) == 9)
    {
	seteuid(getuid());
	poison = clone_object("/std/poison_effect");
	if (poison)
	{
//     	   poison_used = 1;
	   poison->move(enemy);
           poison->set_time(150);
           poison->set_interval(25);
           poison->set_strength(200);
	poison->set_damage(({POISON_FATIGUE, 40, POISON_STAT, SS_CON}));
	   poison->start_poison();
	   return 0;
	}
	else
	   write("Failed to load poison for some reason.\n");
    }
    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

mixed
wield(object what)
{
  object me = ENV(TO);
   if(TP->query_base_stat(SS_DEX) > 100)
    {
   write("The cold blackened dagger fits perfectly into your hand.\n");
   say(QCTNAME(TP) + " wields the cold blackened dagger with a "
	+"smile.\n");
   command("smile grimly");
	return 1;
    }
   write("Your body explodes in pain as you try to wield the dagger!\n");
   say(QCTNAME(TP)+"'s body contorts in pain as the cold blackened "
   +"dagger drains the life from "+HIM_HER(me)+".\n");
    TP->heal_hp(-100);
    return -1;
}

mixed
unwield(object what)
{
    say("You release the cold weapon from your hand.\n");
    return 0;
}
/*
public string
query_recover()
{
    return MASTER + ":" + sprintf("%d", poison_used) + query_wep_recover();
}

public void
init_recover(string arg)
{
    string s1, s2;

    sscanf(arg, "%s#%s", s1, s2);
    poison_used = atoi(s1);
    init_wep_recover(s2);
}*///  Don't think this is needed when I remove the poison_used

int
query_recover()
{
return 1;
}
