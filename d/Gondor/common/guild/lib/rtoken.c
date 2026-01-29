/* 
 * The guild token for the Rangers of Gondor
 *
 * modified from the ranger ring
 * Modification log:
 * Gwyneth: /d/Gondor/elessar/lib/binbit.h->/d/Gondor/common/lib/binbit.h
 *
 * Olorin, Nov-1993
 */
#pragma save_binary

inherit "/std/armour";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/ranger_defs.h"
#include "/d/Gondor/common/lib/binbit.h"

#undef  COUNCIL
#define COUNCIL (RANGER_DIR + "council")

int     inited;
string  token_type, 
ranger_name;

int query_value() { return 0; }

public void create_token()
{
    set_name("token");
    set_at(A_ANY_FINGER);
}

string set_token_short()
{
    return token_type+" token";
}  

string set_token_long()
{
    return "It is a plain "+token_type+" token. You see nothing special about it.\n";
}

nomask void create_armour()
{
    add_name(({"ranger_guild_object", "token", "guild token", "ranger token"}));
    set_short("@@set_token_short");
    set_long("@@set_token_long");
    set_ac(1);
    set_af(TO);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,10);
    add_prop(OBJ_I_NO_DROP,1);
    seteuid(getuid(TO));
    create_token();
}

#ifndef NEW_RANGER_SHADOW
string query_auto_load()
{
    return MASTER + ":";
}
#else
int
query_ranger_token()
{
    return 1;
}

void
enter_env(object env, object from)
{
    object *doubles;

    doubles = all_inventory(env) - ({ this_object() });
    doubles = filter(doubles, &->query_ranger_token());
    if (sizeof(doubles))
	doubles->remove_object();

    ::enter_env(env, from);
}
#endif

int is_ranger(object pl)
{
    int rb;
    return 1;
    rb = query_bin_bits(1,18,2,pl);
    return (rb == 1 || rb == 2 || pl->query_guild_occ_name()=="Gondorian Rangers Guild");
}

mixed wear(object ob)
{
    if (is_ranger(TP)) 
    {
	write("You wear the "+token_type+" ring on your finger.\n"+
	  "It feels good to be back with the Rangers of Gondor.\n");
	say(QCTNAME(TP)+" wears the "
	  +(stringp(token_type) ? token_type : "")
	  +" ring on "+POSSESSIVE(TP)+" finger.\n",TP);
	return 1;
    }
    return "You try to wear the ring, but it is too small!\n";
}

string describe_token()
{
    int lvl;
    lvl = TP->query_stat(SS_OCCUP);  
    switch (lvl)
    {
    case   0..9: return "brass";    break;
    case 10..19: return "copper";   break;
    case 20..29: return "iron";     break;
    case 30..39: return "bronze";   break;
    case 40..49: return "steel";    break;
    case 50..59: return "silver";   break;
    case 60..69: return "gold";     break;
    case 70..79: return "platinum"; break;
    case 80..89: return "emerald";  break;
    case 90..99: return "mithril";  break;
    default: return "diamond";      break;
    }
}

void initiate(object pl)
{
    string *impc;
    int     si;

    inited = 1;
    RANGER_GUILD->short();
    if (RANGER_GUILD->check_keep_player(pl)) 
    {
	ranger_name = pl->query_name();
	token_type = describe_token();
	set_adj(token_type);
	pl->add_cmdsoul(SOUL_FILE);
	pl->update_hooks();
	if(COUNCIL->query_election(RANGER_GUILD->query_company_number(ranger_name),ranger_name))
	    write("\n" +
	      ">>>     Your vote is requested in the election of a new Captain!    <<<\n"+
	      ">>>   Please vote outside the councilroom in your company hideout!  <<<\n\n");
	if(COUNCIL->check_votes(ranger_name))
	    write("\n" +
	      ">>>      Your vote is requested in the Council of the Rangers!      <<<\n"+
	      ">>> Please cast your vote in the councilroom of the Gondor company. <<<\n\n");
	if (IS_CAPTAIN(pl) && !COUNCIL->query_captain(ranger_name))
	    set_bin_bits(1,18,2,pl,1);
	if (si = (sizeof(impc = COUNCIL->query_impeached_captain())))
	{
	    write("\n>>>>> \n" +
	      ">>>>> " + impc[1] + " has called for the impeachment of " + impc[0] + "!\n" +
	      ">>>>> \n"+
	      ">>>>> There "+(si==3?"is ":"are ") + LANG_WNUM(si-2) + " vote"+(si==3?"":"s")+" of support.\n"+
	      ">>>>> \n");
	}
	if (COUNCIL->query_pending_punishment(pl->query_real_name()))
	    COUNCIL->execute_punishment(pl->query_real_name());

	return;
    }
}

void throw_out(object tp)
{
    if (!tp) 
	return;
    RANGER_GUILD->throw_out(tp);
}

void init()
{
    ::init();
    if (!inited && ENV() == TP)
	set_alarm(0.0, 0.0, &initiate(TP));
}

public string
query_recover() { return 0; }
