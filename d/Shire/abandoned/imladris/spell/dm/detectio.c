/*
 *  detection_mastery.c
 *
 *    A Channeling spell list called Detection Mastery.
 *
 */

#include "defs.h"

inherit SpellListFile;

#include "/secure/std.h"
#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include "defs.h"

void	
create_spell_list()
{	
    set_name(({"spell list","list","mastery"}));
    set_short("spell list");
    set_list_name("Detection Mastery");
    set_list_short("dm");
    set_realm("channeling");
    set_pshort("spell lists");
    set_long(
	"This is the magic spell list Detection Mastery. "+
	"It consists of Channeling spells which might do some detections.\n\n"+
	"Do 'slist' to list your available spell lists, and 'dm' to see this "+
	"lists spells.\n");
    
    add_adj(({"detection", "detections", "detection mastery"}));

    add_spell_data(
	"detect magic", "parse_detect_magic", TO, "cast_detect_magic", TO,
	1, TO, ({ "spellcraft", 100, "divination", 100, "life", 100 }),
	"Detects if objects are magic.",
	({ "on <what>", "here", "in me",  "on <who" })
    );
    add_spell_data(
	"identify magic", "parse_identify_magic", TO, "cast_detect_magic", TO,
	4, TO, ({ "spellcraft", 100, "divination", 100, "life", 100 }),
	"Tells what sort of magic is present.",
	({ "in <what>", "on <what>" })
    );

    add_spell_data(
	"life typing", "parse_life_typing", TO, "cast_life_typing, TO, 8, TO,
	({"spellcraft", 100, "divination", 100, "life", 100}),
	"Make you understand a creatures life status.",
	({ "on <who>" })
    );

}

int
query_mana_cost(string spell, int class)
{
    int ind;
    ind = spell_index(spell, class);
    if(ind>=0)
	return class*({ 10, 20, 40, 50, 60 })[ind];
}

/*----------------------------------------------------------------------*/

mixed
parse_detect_magic(string str) {
    object *ob;
    string fail;

    if(!str)
	return SERR_SYNTAX;

    if(parse_inventory(str, ob))
	return ([ TP: ob ]);
    else if(parse_in_room(str, ob))
	return ([ EP: ob ]);
    else if(parse_inventory_of(str, obmap))
	return obmap;
    else
	return SERR_SYNTAX;
}

mixed
cast_mult_detect_magic(object tp, mixed ob)
{
  mixed *id;
  int lvl = level(tp);
  int i;
  string gs;
  string what;
  object *mt = ({});
  object oth = 0;
  
  if(objectp(ob[0])) {
    oth = ob[0];
    what = "on [oth]";
  } else
    what = ob[0];

  ob = ob[1..sizeof(ob)];
  tellem(tp, oth, "[You] cast a {Detect Magic;mysterious} spell "+what+".\n", 1);
  for(i=0;i<sizeof(ob);i++)
    {
      id = ob[i]->query_prop(MAGIC_AM_MAGIC);
      if(id && lvl*5 > id[0]) 
	mt += ({ ob[i] });
    }
  if(!sizeof(mt)) 
    write(BSN("Nothing of "+COMPOSITE_DEAD(ob)+" seems to be magical."));
  else if(sizeof(mt)==1) 
    write(BSN("Only the "+mt[0]->short()+" flashes up as the spell lasts, so it must be magical."));
  else {
    write("Several things flashes up as the spell lasts.\n");
    write("The "+BSN(COMPOSITE_DEAD(mt))+ " are magical!"));
  }
  return;
}

mixed
cast_detect_magic(object tp, mixed ob)
{
    mixed *id;
    int lvl;

    if(sizeof(ob)>3) 
      return cast_mult_detect_magic(tp, ob);
    if(sizeof(ob)<2) {
      write("Nothing seems magical.\n");
      return ;
    }
    
    ob = ob[1];
    lvl = level(tp);
    id = ob->query_prop(MAGIC_AM_MAGIC);
    
    if(id && level(tp)*5 > id[0])
    {
	tp->catch_msg("The "+ob->short()+" seems magical!\n");
	tp->catch_msg("It has been subject to "+id[1]+".\n");
	return;
    }

    tp->catch_msg("The "+ob->short()+" seems non-magical.\n");
    return;
}

mixed
parse_life_typing(string str) {
    object ob;
    string fail;

    if(!parse_command(str, ({ E(TP) }),
	"'on' %l", ob))
	return SERR_SYNTAX;

    return ;
}

mixed
cast_life_typing(object tp, mixed ob)
{
    ob = ob[0];
    if(ob->query_real_name())
	tell_object(tp, 
	    "The name of the "+ob->query_race()+" is:    "+C(ob->query_real_name())+"\n");
    else
	tell_object(tp,
	    "The name of the "+ob->query_race()+" is not known.\n");

    tell_object(tp,
	His(ob)+" health is : "+ob->query_hp()+ " ("+ob->query_max_hp()+")\n");
}

mixed
parse_detect_invisible(string str)
{
    object ob;
    string fail;
    notify_fail("Syntax: detect invisible [on <who>]\n");
    ob = TP;
    if(str) {
	if(!parse_command(str, ({ E(TP) }),
	    "'on' %l", ob) &&
           !parse_command(str, ({ E(TP) }),
	    "'on' 'me'"))
	    return 0;
    }

    if(fail=check_room())
	Fail(fail);
    if(fail=check_player())
	Fail(fail);

    return ({ ob });
}

mixed
cast_detect_invisible(object tp, mixed who)
{
    int old_see;
    int str;

    who = who[0];
    if(tp == who) {
	tp->catch_msg("You cast Detect Invisible on yourself.\n");
	tell_room(E(tp), QCTNAME(tp)+" casts a spell on "+him(tp)+"self.\n");
    } else {
	tp->catch_msg("You cast Detect Invisible on "+QTNAME(tp)+".\n");
	who->catch_msg(QCTNAME(tp)+" casts a Detect Invisible spell on you.\n");
	tell_room(E(tp), QCTNAME(tp)+" casts a spell on "+QTNAME(who)+".\n");
    }
    str = (tp==who?level(tp):level(tp)/2);
    old_see = who->query_prop(LIVE_I_SEE_INVIS);
    if(old_see >= 0)
	who -> add_prop(LIVE_I_SEE_INVIS, old_see + str);
    call_out("remove_detect_invisible", str * 60, ({ who, old_see }) );
}

remove_detect_invisible(mixed buf)
{
    buf[0] -> add_prop(LIVE_I_SEE_INVIS, 
	query_prop(LIVE_I_SEE_INVIS) - buf[1]);
    buf[0] -> catch_msg(
	"You see less of invisible things now.\n");
}

#if 0

mixed
parse_percieve_power(string str) {
    object ob;
    notify_fail("Syntax: percieve power in <what>\n"+
	"        percieve power in <who>\n");
    if(!parse_command(str, ({ E(TP) }),
	"'in' / 'on' %o", ob))
	return 0;

    returb ob;
}

mixed 
cast_percieve_power(object tp, object ob)
{
    if(living(ob)) {
    }
}
#endif

mixed
parse_identify_magic(string str)
{
    string fail;
    object ob;

    notify_fail("Syntax: identify magic in <what>\n");
    
    if(!parse_command(str, player_access(TP),
	"'in' / 'on' %o", ob))
	return 0;

    if(fail=check_room())
	Fail(fail);
    if(fail=check_player())
	Fail(fail);
    return ({ ob });
}

mixed
cast_identify_magic(object tp, mixed ob)
{
    mixed *proplist;
    int i, lev;
    string obname;

    ob = ob[0];
    proplist = ob->query_prop(MAGIC_AM_ID_INFO);
    lev = level(tp)*5;

    if(living(ob))
	obname = QCTNAME(ob);
    else
	obname = "the "+ob->short();
 
    if(proplist)
       for(i=sizeof(proplist)-2;i>=0;i-=2) 
	   if(lev > proplist[i+1]) {
	       tp -> catch_msg(proplist[i]);
	       return;
	   }

    tp -> catch_msg("The Identify Magic spell on "+obname+" shows nothing special.\n");
}

mixed
parse_detect_resistance(string str)
{
    string fail;
    object ob;

    notify_fail("Syntax: detect resistance in <what>\n");

    if(!str || str=="" || str=="on me" || str=="in me")
      return this_player();

    if(!parse_command(str, player_access(TP),
	"'in' / 'on' %o", ob))
	return 0;

    if(fail=check_room())
	Fail(fail);
    if(fail=check_player())
	Fail(fail);
    return ob;
}

#define 

mixed
cast_detect_resistance(object tp, mixed ob)
{
    int i, one;
    string obname;
    string *m = ({ 
	"acid.........", MAGIC_I_RES_ACID,
	"air..........", MAGIC_I_RES_AIR,
	"cold.........", MAGIC_I_RES_COLD,
	"death........", MAGIC_I_RES_DEATH,
	"earth........", MAGIC_I_RES_EARTH,
	"electricity..", MAGIC_I_RES_ELECTRICITY,
	"fire.........", MAGIC_I_RES_FIRE,
	"life.........", MAGIC_I_RES_LIFE,
	"light........", MAGIC_I_RES_LIGHT,
	"magic........", MAGIC_I_RES_MAGIC,
	"poison.......", MAGIC_I_RES_POISON,
	"water........", MAGIC_I_RES_WATER
	});

    if(living(ob)) 
      obname = QTNAME(ob);
    else
      obname = "the "+short();

    if(tp!=ob) {
      tellem(tp, ob, "[You] cast[*s] a {Detect Resistance;strange} spell on [oth]!\n", 1);
      write("The "+obname+" resists the following elements:\n");
    }
    else {
      tellem(tp, 0, "[You] cast[*s] a {Detect Resistance;strange} spell on [yourself].\n", 1);
      write("You resist:\n");
    }
    one = 0;
    for(i=0; i<sizeof(m); i+=2)
      if(ob->query_magic_res(m[i+1])) {
	write(" - "+C(m[i])+" "+ob->query_magic_res(m[i+1])+"\%\n");
	one = 1;
      }
    if(!one)
      write(" - No elements!\n");
    write("> ");
    return;
}
