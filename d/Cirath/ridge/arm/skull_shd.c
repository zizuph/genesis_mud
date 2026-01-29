/*
* Created by: Luther
* Date: Sept 2001
*
* File: /d/Cirath/ridge/arm/skull_shd.c
* Comments: Skull shield in the ruins of the valley in athas
*/

inherit "/lib/keep";
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

#define FIXEUID          FIX_EUID
#define FIX_EUID         { setuid(); seteuid(getuid()); }

/* Some changes from Lanjelin */
int     given_away;
string  dropped_by_wiz,
        cloned_by_wiz;

void create_armour()
{
    	set_name("shield");
    	set_short("weathered skull shield");
    	set_long("A monsterous shield made solely of skulls of tortured slaves, "
    		+"who died under the harsh conditions of Tyr. The skulls are not "
    		+"fused together with any type of bonding material, yet seem to "
    		+"fit closely together in an intricate interlocking pattern. You "
    		+"think you hear a faint scream or two coming from the shield.\n");
 
    	set_adj("skull");
    	add_adj("weathered");   
    	add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
        add_prop(MAGIC_AM_MAGIC, ({30, "enchantment", 30, "psionic"}));
	add_prop(OBJ_M_NO_BUY, "No I don't want to sell this shield. I'll "
			+"keep it to my self.");
	add_prop(OBJ_I_WEIGHT,3000);
        add_prop(OBJ_I_VOLUME,1200);
	add_prop(OBJ_I_VALUE, 5000);
	add_prop(MAGIC_AM_ID_INFO, ({"This shield has been enchanted to stay "+
      		"together and not fall apart.\n", 10,
      		"Psionics have been used on this shield aswell, anyone "+
      		"finding themself to close will be in for a surprise.\n", 20}));
	add_prop(OBJ_S_WIZINFO, "A shield magically enchanted to last a long time. "
		+"Aswell does damage to those who get to close to it.\n");
	set_ac(35);
    	set_at(A_SHIELD);
    	set_wf(TO);	    	
}

public int *
query_shield_slots()
{
return (::query_shield_slots() + ({ A_BODY, A_LEGS, A_HEAD }) );
}

int
got_hit(int hid, int ph, object att, int dt, int dam)    
{
	int ini, res, pen;
	object me = ENV(TO);
	mixed* hitresult;
	string how;

	::got_hit(hid, ph, att, dt, dam);
	if(random(4)) return 0;
	if (dt == MAGIC_DT)
	{
		if (TP->query_real_name() == "luther")
		TP->catch_msg("TEST: MAGIC_DT.\n");
		return 0;
	}
	else
	{	
		if (TP->query_real_name() == "luther")
		TP->catch_msg("TEST: NON_MAGICAL.\n");
	}
	
	ini = TP->query_base_stat(SS_DEX) / 2 + random(20);
	res = att->query_magic_res(MAGIC_I_RES_MAGIC);	
 	pen = ini * (100 - res) /100;
	hitresult = att->hit_me(pen, MAGIC_DT, me, -1);
	
	
	
	// hitresult=att->hit_me(TP->query_base_stat(SS_DEX) / 2 + random(20), W_SLASH, me, -1);


	how = "just missing with its sharp teeth";
	if (hitresult[0] > 0) how = "just catching some skin with its sharp teeth";
	if (hitresult[0] > 2) how = "drawing blood with its sharp teeth";
	if (hitresult[0] > 5) how = "tearing chunks with its sharp teeth";
	if (hitresult[0] > 9) how = "tearing flesh from the bone";
	if (hitresult[0] > 14) how = "ripping flesh to pieces with its teeth";
	if (hitresult[0] > 20) how = "feasting on flesh";

	if(att->query_hp()<= 0) 
	{
		wearer->catch_msg(QCTNAME(att)+ " finds " + HIM_HER(att) + 
		"self too close to your skull shield.\n"
		+"Some of the skulls start to feast on " + HIM_HER(att) + ".\n");
		wearer->tell_watcher(QCTNAME(att)+ " finds " + HIM_HER(att) + 
		"self too close to the skull shield.\n"
		+"Some of the skulls start to feast on " + HIM_HER(att) + " .\n", wearer, att);
		att->catch_msg("You find yourself too close to the skull shield.\n" 
		+"Some of the skulls start to feast on you.\n");
		att->do_die(me);
		return 1;
	}

	wearer->catch_msg(QCTNAME(att)+ " finds " + HIM_HER(att) + 
		"self too close to your skull shield.\n"
		+"One of the skulls lashes out at " + HIM_HER(att) + ", " + how + ".\n");
	att->catch_msg("You find yourself too close to the skull shield.\n" 
		+"One of the skulls lashes out at you, " + how + ".\n");	
	wearer->tell_watcher(QCTNAME(att)+ " finds " + HIM_HER(att) + 
		"self too close to the skull shield.\n"
		+"One of the skulls lashes out at " + HIM_HER(att) + ", " + how + ".\n", wearer, att);

	return 1;
}

/* Some changes from Lanjelin */
/* This is for log system */

int
test_give()
{
    FIX_EUID
    given_away = 1;
    if (TP->query_wiz_level())
    {
        write_file("/d/Cirath/log/items", TP->query_name()
          + " gave the "+short()+" to "+ENV(TO)->query_name()
          + ". "+ctime(time())+".\n");
    }
    return 0;
}

mixed
drop_check()
{
    if (TP->query_wiz_level() && query_verb() != "give")
    {
        write_file("/d/Cirath/log/items",TP->query_name()
          +" dropped the "+short()+" in "+file_name(ENV(TP))
          +" "+ctime(time())+".\n");
        dropped_by_wiz = TP->query_name();
    }
    else if (TP->query_wiz_level())
    {
        dropped_by_wiz = TP->query_name();
    }
    return 0;
}

void
enter_env(object to, object from)
{
  ::enter_env(to, from);
  seteuid(getuid(this_object()));
  if (!from && TP->query_wiz_level()) {
    cloned_by_wiz = CAP(TP->query_real_name());
    if (!living(to)) write_file("/d/Cirath/log/items",TP->query_name()+" cloned "+short()+" into "+file_name(ENV(TO))+". "+ctime(time())+".\n");
    else write_file("/d/Cirath/log/items",TP->query_name()+" cloned the "+short()+"."+ctime(time())+".\n");
    }
  else if (given_away && from->query_wiz_level())
  {
    write_file("/d/Cirath/log/items",from->query_name()+" gave the "+short()+" to "+to->query_name()+". "+ctime(time())+".\n");
  given_away = 0;
  }
  if (!living(from) && strlen(dropped_by_wiz)) {
    write_file("/d/Cirath/log/items",TP->query_name()+" picked up the "+short()+" dropped by "+dropped_by_wiz+" in "+file_name(ENV(TP))+". "+ctime(time())+".\n");
    }
  else if (!living(from) && strlen(cloned_by_wiz)) {
    write_file("/d/Cirath/log/items",TP->query_name()+" picked up the "+short()+" cloned by "+cloned_by_wiz+" in "+file_name(ENV(TP))+". "+ctime(time())+".\n");
  }
}

void
leave_env(object from, object to)
{
    string  fn = "the void";
    
    ::leave_env(from, to);

    if (!objectp(from))
        return;
    if (from->query_prop(ROOM_I_IS))
        fn = file_name(from);
    else if (objectp(ENV(from)))
        fn = file_name(ENV(from));
    if (!objectp(to))
        write_file("/d/Cirath/log/items", from->query_name()
                   + " destructed the "+short()+", in " + fn + ". "
                   + ctime(time()) + ".\n");
}   