/*  -*- LPC -*-  */
/*
 * lootsack.c
 *
 * A simple rugged sack carried by orcs in Moria
 *
 */

inherit "/std/receptacle";
inherit "/lib/keep";
void fill_sack(int ran);
#include "defs.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include <composite.h>


#define SACK     this_object(), 1

int ran;

/*
 *  Description: Constructor.
 */
public void
create_container()
{
    set_name("shire_sack");
    add_name("sack");
    set_pname("sacks");
    set_adj( ({ "canvas","large" }) );
    set_short("large canvas sack");
    set_pshort("large canvas sacks");
    set_long("This is a large canvas sack, used by orcs to haul their loot.\n" +
         "Use <sackloot> to loot something.\n");
    add_prop(CONT_I_IN,1);
    add_prop(CONT_I_WEIGHT,     1200);          /* 1.2 kg        */
    add_prop(CONT_I_VOLUME,     500);           /* Empty volume. */
    add_prop(CONT_I_MAX_VOLUME, 3*10000);       /* 30 l          */
    add_prop(CONT_I_MAX_WEIGHT, 5*10000);      /* 50 kg        */
    add_prop(CONT_I_CLOSED,     1);
    add_prop(CONT_I_RIGID,      0);
    add_prop(CONT_I_TRANSP, 0);
    add_prop(OBJ_M_NO_SELL, "@@check_sell@@");
    add_prop(OBJ_I_VALUE,   50+random(11));
    ran = random(100); 
    setuid();
    geteuid();

    set_alarm(2.0, 0.0, "fill_sack", ran);
    set_keep();
}

init()
{
    ::init();
    add_action("do_loot", "sackloot");
    add_action("do_empty", "empty");
    add_action("do_empty", "sackempty");
}

mixed
check_sell()
{
    if (sizeof(all_inventory(TO)))
    return "There are things in the "+short()+"! Empty it first.\n";
    else
    return 0;
}

string
short(object for_obj)
{
    if (query_prop(CONT_I_CLOSED))
    return "closed " + ::real_short(for_obj);
    else
    return "open " + ::real_short(for_obj);
}

void
fill_sack(int ran)
{
    object jewel, coins;
    
    if (!environment() || !environment()->query_npc())
    return;

#define PUT(name) clone_object(MORIA_OBJ + name)->move(SACK)
#define COINS(type, num) \
    coins=clone_object("/std/coins"); \
    coins->set_coin_type(type);       \
    coins->set_heap_size(num);        \
    coins->move(SACK)

#define GEM(gemtype) \
    jewel=clone_object(MORIA_OBJ + "gems"); \
    jewel->set_gem_type(gemtype);           \
    jewel->move(SACK)
        
    setuid();
    seteuid(getuid(TO));

    switch (ran)
    {
    case 21..25:
        PUT("orcmeat");

    case 16..20:
        PUT("torch");
        return; 

    case 0..15:
        PUT("orcmeat");
        return;
    }
     
    PUT("torch");
    PUT("orcmeat");

    switch(ran)
    {
    case 26..30:
        COINS("copper", 20 + random(30));
        break;

    case 31..50:
        COINS("silver", 20 + random(30));
        break;

    case 51..55:
        COINS("silver", 20 + random(30));
        PUT("sbracelet");
        break;

    case 56..60:
        COINS("copper", 20 + random(30));
        PUT("necklace");
        break;

    case 61..65:
        COINS("silver", 20 + random(30));
        GEM("emerald");
        break;

    case 66..80:
        COINS("gold", 2 + random(3));
        PUT("ring");
        break;

    case 81..85:
        COINS("gold", 2 + random(3));
        PUT("ring");
        GEM("opal");
        break;

    case 86..90:
        COINS("gold", 2 + random(3));
        PUT("ring");
        GEM("sapphire");
        break;

    case 91..95:
        COINS("gold", 2 + random(3));
        PUT("ring");
        GEM("ruby");
        break;

    case 96..100:
        COINS("gold", 5 + random(3));
        PUT("mithring");
        GEM("ruby");
        break;
    }
}

int is_corpse(object what)
{
    return !living(what) && what->query_prop(CONT_I_IN);
}

int
is_sack(object what)
{
    return what->id("shire_sack");
}

int
do_loot(string arg)
{
    mixed  *obs;
    object *loot;
    string rest;
    object sack;

    FIXEUID;

    notify_fail("Usage: " + query_verb() +" <corpse> [with <sack>]\n");

    if (ETO != TP)
    return notify_fail("You must hold the sack to loot corpses.\n");

    if (!strlen(arg))
    arg = "corpse";

    if (parse_command(arg, INV(ENV(TP)),
               "%i 'in' / 'into' / 'with' / 'using' [the] %s", 
              obs, rest))
    {
        loot = VISIBLE_ACCESS(obs, "is_corpse", TO);
        if (!parse_command(rest, INV(TP), "[the] %i", obs))
        return notify_fail("Loot it into which sack?\n");
        obs = VISIBLE_ACCESS(obs, "is_sack", TO);
        if (!sizeof(obs))
        return notify_fail("Which sack do you mean?\n");
        if (sizeof(obs) > 1)
        return notify_fail("Only one sack at a time please..\n");
        sack = obs[0];
        return sack->do_loot_one(loot, rest);
    }
    else {
    loot = IM_PARSE_FILE->parse_environment_items(arg, "");
    if (!sizeof(loot))
        return 0;
    loot = filter(loot, "is_corpse", TO); 
    if (!sizeof(loot))
        return 0;
    return TO->do_loot_one(loot, "loot sack");
    }
}

int move_to(object what)
{
    if (!objectp(what))
      return 0;
    if( what->move(TO) != 0 )
      return 0;

    return 1;
}

int
do_loot_one(object *loot, string name)
{   
    int i, j;
    object *thing;
    object *got;

    if (query_prop(CONT_I_CLOSED))
    return notify_fail("Perhaps open the " + name + " first?\n");

    i=sizeof(loot);

    if (!i)
    return 0;

    write("You loot " + COMPOSITE_DEAD(loot) + " using your "+name+".\n");
    say(QCTNAME(TP) + " starts looting " + QCOMPDEAD + ".\n");

    while (i--) {
    if (!objectp(loot[i]))
        continue;

    thing = all_inventory(loot[i]);
    j = sizeof(thing);

    if (!j) {
        write("The " + loot[i]->short() + " is empty.\n");
        continue;
    }

    got = filter(thing, "move_to", TO);

    if (!sizeof(got)) 
        write("You couldn't loot anything from the " + loot[i]->short() + ".\n");
    else {
        write("You loot " + COMPOSITE_DEAD(got) + " from the " + 
          loot[i]->short() + " into " + name + ".\n");
        say(QCTNAME(TP) + " loots " + QCOMPDEAD + " from the " +
        loot[i]->short() + ".\n");
    }
    }
    return 1;
}

int
do_empty(string arg)
{
    object *objs;
    mixed *sacks;
    int i, r=0;

    notify_fail("Usage: " + query_verb() + " <sack>\n");
    
    if (!strlen(arg))
    arg = "loot sack";
    
    if (!parse_command(arg, INV(TP), "%i", sacks))
    return 0;

    sacks = VISIBLE_ACCESS(sacks, "is_sack", TO);
    if (!sacks)
    return notify_fail(CAP(query_verb()) + " which sacks?\n");

    for (i=0; i<sizeof(sacks); i++)
    if (sacks[i]->do_empty_sack())
        r = 1;
    return r;
}

int
do_empty_sack()
{
    if (query_prop(CONT_I_CLOSED))
    return notify_fail("Perhaps open the loot sack first?\n");
    if(!sizeof(all_inventory(TO)))
    return notify_fail("The loot sack is already empty.\n");
    write("You empty the sack, and drop " + COMPOSITE_DEAD(INV(TO)) + ".\n");
    say(QCTNAME(TP) + " drops " + QCOMPDEAD + " from a sack.\n");
    INV(TO)->move(ENV(TP));
    return 1;
}

mixed
query_recover() { return MASTER; }

