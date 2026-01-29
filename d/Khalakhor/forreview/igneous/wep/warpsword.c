inherit "std/weapon";

#include "/d/Shire/common/defs.h"
#include <composite.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <ss_types.h>
#include <options.h>
#include <filter_funs.h>

#define ERROR_LOG   "/d/Shire/igneous/log/warpsword"

#ifdef  ERROR_LOG
#define ERROR(s)    write_file(ERROR_LOG, ctime(time()) + s + "\n");
#else
#define ERROR(s)
#endif

#define WARP_SHADOW "/d/Shire/igneous/wep/warp_shadow"
#define SWORD_MASTER "igneous"

void warp();

int  warped, Warped_id;

void
create_weapon()
{
    set_name(({"sword","longsword"}));
    set_short("@@myshort");
    set_long("@@mylong");
    set_adj(({"black","faded"}));
    set_hit(45);
    set_pen(35);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_RIGHT);
    set_wf(TO);
    add_prop(OBJ_I_VALUE,  1200 + random(50));
    add_prop(OBJ_I_WEIGHT, 2000 + random(25));
    add_prop(OBJ_I_VOLUME, 2000 + random(100));
    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    warped = 0;
    add_item("hilt","@@hilt_desc");
    add_item(({"jewel","jewels"}),"@@jewel_desc");
}

string
myshort()
{
    if (warped)
	return "jeweled hilt";
    else
	return "faded black longsword";
}

string
mylong()
{
    if (warped)
	return "This sword is warped of of reality\n";
    else
	return "This sword is in reality\n";

}


string
jewel_desc()
{
    return "Oooohh  jewels";
}

string
hilt_desc()
{
    return "a hilt, wow.\n";
}

int
query_is_warped()
{
    return warped;
}

void
warp()
{
    object wielder = query_wielded();

    if (!warped)
    {
	wielder->catch_msg("The blade on the "+short()+" slowly fades out of "+
	  "reality, leaving nothing but a jeweled hit visiable.\n");
	tell_room(ENV(wielder),QCTNAME(wielder)+"'s blade on the "+short()+
	  "slowly disappears before your very eyes, leaving "+HIM_HER(wielder)+
	  " holding nothing but a jeweled hilt.\n",wielder);
	warped = 1;
    }
    else
    {
	wielder->catch_msg("Slowly a blade starts to materialize from the "+short()+
	  " as it reappears once again.\n");
	tell_room(ENV(wielder),"A blade becomes visable on "+QTNAME(wielder)+"'s "+
	  short()+" one more.\n",wielder);
	warped = 0;
    }
    return;
}

mixed
wield(object wep)
{
    write("As you wield the "+short()+" in your right hand, it begins "+
      "to emit a dull humming noise.\n");
    say("As "+QTNAME(TP)+" wields the "+short()+" in "+HIS_HER(TP)+
      " right hand, it begins to emit a dull humming noise.\n");
    if (TP->query_real_name() == SWORD_MASTER)
	set_alarm(0.1,0.0,&warp());
    else
	Warped_id = set_alarm(itof(300+random(300)),itof(300+random(300)),&warp());

    return 1;
}

int
unwield(object wep)
{
    if (Warped_id)
	remove_alarm(Warped_id);
    if (warped)
    {

	write("As you release your grip from the "+short()+", it becomes quiet "+
	  "and the blade becomes visable once more.\n");
	say("As "+QTNAME(TP)+" releases the "+short()+", the humming ceases "+
	  "and the blade becomes visable once more.\n");
	warped = 0;
	return 1;
    }
    return 0;
}

int
try_hit(object enemy)
{
    object shadow;

    if (!enemy->query_is_warp_shadowed())
    {
	setuid(); seteuid(getuid());
	shadow = clone_object(WARP_SHADOW);
	if (shadow->shadow_me(enemy) != 1)
	{
	    ERROR("Shadow failed to load in "+enemy->query_name()+"!\n");
	    shadow->remove_shadow();
	}
    }
    return 1;
}

int
get_hitloc_id(string hdesc, object enemy)
{
    object co = enemy->query_combat_object();
    int *ids  = co->query_hitloc_id();
    int sz = sizeof(ids);
    int i;

    for (i = 0; i < sz; i++)
    {
	if (co->query_hitloc(ids[i])[2] == hdesc)
	    return ids[i];
    }

    return -1;
}

public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    object wielder = query_wielded();
    object *stuff;
    int i, size;
    object armour;
    string hit_desc, wep_short, *how = allocate(3);

    if (!warped)
	return ::did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);

    armour = enemy->query_armour(get_hitloc_id(hdesc, enemy));
    if (enemy->query_hp() <= 0)
    {
	enemy->add_prop(LIVE_I_NO_CORPSE,1);
	stuff = deep_inventory(enemy);
	stuff = filter(stuff, &operator(==)(0) @ &->query_auto_load());
	i = -1;
	size = sizeof(stuff);
	while(++i < size) 
	{
	    stuff[i]->remove_object();
	}
	enemy->do_die(wielder);
	return 1;
    }
    hit_desc = (objectp(armour) ? armour->short(wielder) : hdesc);
    wep_short = short();
    switch (phurt)
    {
    case -1:
	how[0] = "You miss "+QTNAME(enemy)+" entirely with an "+
	"awkward sing of your "+wep_short+".";
	how[1] = QCTNAME(wielder) +" misses you entirely with an awkward "+
	"swing of "+HIS_HER(wielder)+" "+wep_short+".";
	how[2] = QCTNAME(wielder) +" misses "+QTNAME(enemy)+" entirely "+
	"with an awkward swing of "+HIS_HER(wielder)+" "+wep_short+".";
	break;
    case 0:
	how[0] = "You narrowly miss "+QTNAME(enemy)+"'s "+hit_desc+
	" with the invisable blade of your "+wep_short+".";
	break;
    case 1..5:
	break;
    case 6..10:
	break;
    case 11..20:
	break;
    case 21..40:
	break;
    case 41..60:
	break;
    case 61..80:
	break;
    case 81..90:
	break;
    default:
	break;
    }

    wielder->catch_msg(how[0] + "\n");
    enemy->catch_msg(how[1] + "\n");
    wielder->tell_watcher(how[2] + "\n");
    return 1;
}
