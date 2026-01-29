/*
 *  The Anghoth token.
 *    (code borrowed from the Ranger emblem)
 *
 *  Alto, 03 June 2002.
 *
 */

#pragma strict_types
#pragma save_binary

inherit "/std/armour";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>
#include <composite.h>
#include <std.h>
#include <const.h>
#include "/d/Gondor/defs.h"
#include "../anghoth_defs.h"


int     inited;
string  emblem_type, anghoth_name, sponsor_name; 
object  gShadow = 0;

//private void add_anghoth_shadow(object ob);

int query_value() 
{ 
    return 0; 
}

public void create_emblem()
{
    set_name("token");
    set_at(A_ANY_FINGER);
}

string set_emblem_short(object pl)
{
    return emblem_type + " token";
}  

string set_emblem_long(object pl)
{
    return "It is a plain " + emblem_type + " token. You see nothing "
        + "special about it.\n";
}

nomask void create_armour()
{
    add_name(({"anghoth_club_object", "_anghoth_token_id", 
        "anghoth_token"}));
    set_short(set_emblem_short);
    set_long(set_emblem_long);
    set_ac(1);
    set_af(TO);
    set_may_not_recover();
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    seteuid(getuid(TO));
    create_emblem();
}

//string
//query_auto_load() 
//{ 
//    return MASTER + ":"; 
//}

string
query_recover()
{
    return 0;
}

int
query_anghoth_emblem()
{
    return 1;
}

void
enter_env(object dest, object old)
{
    object *doubles;

    doubles = all_inventory(dest) - ({ this_object() });
    doubles = filter(doubles, &->query_anghoth_emblem());
    if (sizeof(doubles))
	       doubles->remove_object();

//    set_alarm(3.0, 0.0, &add_anghoth_shadow(dest));
    ::enter_env(dest, old);
}

//private void
//add_anghoth_shadow(object ob)
//{
//    string name, rank, sponsor;
//    name = ob->query_real_name();
//    sponsor = MANAGER->query_anghoth_sponsor(name);
//
//    gShadow = clone_object(ANGHOTH_SHADOW);
//    gShadow->shadow_me(ob);
//    ob->init_anghoth_shadow();
//
//    if (MANAGER->query_expelled_anghoth(name))
//    {
//    ob->expel_anghoth("expelled while asleep");
//    }
//
//    if (MANAGER->query_anghoth_level(name) < 2 &&
//        !TO->id("anghoth_kriechek_token"))
//    {
//    rank = MANAGER->query_anghoth_rank(name);
//    ob->change_tokens("rank");
//    }
//    
//    if (MANAGER->query_anghoth_level(name) >= 2 &&
//        TO->id("anghoth_kriechek_token"))
//    {
//    rank = MANAGER->query_anghoth_rank(name);
//    ob->change_tokens("rank");
//    }
//
//}

mixed wear(object ob)
{
    if (ANGHOTH_MEMBER(TP)) 
    {
       	write("You slip the " + emblem_type + " token on your finger.\n"
            + "You are a coward and a craven. Your Lord does not presently "
            + "acknowledge you.\n");
	       say(QCTNAME(TP) + " wears the "
	           +(stringp(emblem_type) ? emblem_type : "")
            + " ring on " + POSSESSIVE(TP) + " finger.\n", TP);
	       return 1;
    }
    return "You try to wear the ring, but it burns you painfully!\n";
}

string describe_emblem(object pl)
{
    int lvl;
   	anghoth_name = pl->query_name();
    lvl = MANAGER->query_anghoth_level(anghoth_name);  
    switch (lvl)
    {
    case 1:   return "tin";           break;
    case 2:   return "iron";          break;
    case 3:   return "gold";          break;
    case 4:   return "mithril";       break;
    default:  return "broken glass";  break;
    }
}

void initiate(object pl)
{
    inited = 1;
   	anghoth_name = pl->query_name();
    sponsor_name = MANAGER->query_anghoth_sponsor(anghoth_name);
    emblem_type = describe_emblem(pl);
	   set_adj(emblem_type);
		  return;
}

void init()
{
    ::init();
    if (!inited && ENV() == TP)
	       set_alarm(0.0, 0.0, &initiate(TP));
}

