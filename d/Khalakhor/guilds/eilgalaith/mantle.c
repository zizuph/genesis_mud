/**********************************************************************
 * - mantle.c                                                       - *
 * - Orginal code created by Tomas, Damaris and Lucius              - *
 * - Recoded by Damaris 2/2002                                      - *
 * - Updated by Damaris 6/2003                                      - *
 * - Updated by Damaris 8/2005                                      - *
 **********************************************************************/
/* 2006/01/13 Last update
 * 2011/02/28 Lavellan,  fixed "remove" messages
 * 2021/07 Tapakah reduced the weight to appropriate guild item weight
 */

#pragma strict_types

#include "guild.h"
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/d/Genesis/newmagic/spellcasting";

string 
query_auto_load ()    { return MASTER + ":"; }

string 
query_recover ()        { return 0; }

void 
init ()
{
  mixed tmp;
  ::init();
    
  if (!living(environment()))
    return;
    
  setuid(); seteuid(getuid());
  tmp = (string)SERVER->query_house(ENV(TO)->query_real_name());
    
  if (!strlen(tmp)) {
    set_adj( tmp = ({"soft","grey"}) );
    set_short("soft grey mantle");
    set_pshort("soft grey mantles");
  }
  else  {
    set_adj(tmp = (string *)SERVER->query_house(tmp)[HOUSE_CLRS]);
    set_short(implode(tmp, " and ") + " mantle");
    set_pshort(implode(tmp, " and ") + " mantles");
  }
  add_adj("wool");
  set_long("This soft woolen mantle is commonly worn by members "+
           "of the " + GUILD_NAME + ". The frills and shoulders of the "+
           "mantle have been dyed " +
           (tmp[0] == "soft" ? "a greyish "+
            "colour" : tmp[0]) + ", and the torso has been coloured "+
           (tmp[1] == "grey" ? "grey as well" : tmp[1]) + ".\n");

}

varargs string
long(string str, object for_obj)
{
  string res = ::long(str, for_obj);
  if (!objectp(for_obj))
    for_obj = this_player();
    
  if (str || !IS_MEMBER(for_obj))
    return res;
    
  return res + "Use <eghelp> to guide you in the ways "+
    "of the Eil-Galaith.\n";
}

void
create_object()
{
  set_name( ({"mantle","tunic","shirt","clothing"}) );
  add_name(OBJECT_ID);
  add_spell("/d/Khalakhor/guilds/eilgalaith/spells/summon");
  add_spell("/d/Khalakhor/guilds/eilgalaith/spells/aura");
  set_layers(1);
  set_looseness(10);
  set_wf(this_object());
  set_slots(A_BODY | A_ARMS);
    
  add_prop(OBJ_S_WIZINFO, "Eil-Galaith Racial Guild Item.\n");
  add_prop(OBJ_M_NO_DROP,"Oddly enough, you can't seem to "+
           "do that.\n");
  add_prop(OBJ_M_NO_GIVE, "It's sentimental value is too high "+
           "for you to simply give it away.\n");
  add_prop(OBJ_M_NO_SELL, "The shopkeeper finds it "+
           "ininteresting.\n");
  add_prop(OBJ_M_NO_STEAL, 1);
  add_prop(OBJ_I_WEIGHT, 40);
  add_prop(OBJ_I_VOLUME, 100);
  add_prop(OBJ_I_VALUE,  1);
}

int
wear (object item)
{
  write("You pull the " + short() + " over your head and "+
        "settle it on your shoulders.\n");
  say(QCTNAME(TP) + " pulls the " + short() + " on over "+
      "" + HIS(TP) + " head.\n");
  return 1;
}

int
remove (object item)
{
  wearer->catch_tell("You slip the " + short() + " off over your head.\n");
  tell_room(environment(wearer), QCTNAME(wearer) + " slips the " + short() +
            " off over "+ HIS(wearer) + " head.\n", wearer);
  return 1;
}

void
enter_env (object env, object from)
{
  ::enter_env(env, from);
  if (IS_MEMBER(env) || env->query_wiz_level())
    add_spell_object(env);
}

void
leave_env (object from, object to)
{
  ::leave_env(from, to);
  wearable_item_leave_env(from, to);

}

void
appraise_object (int num)
{
  ::appraise_object(num);
  appraise_wearable_item();
}

string
show_subloc (string subloc, object on, object for_obj)
{
  if (subloc != GUILD_SUBLOC)
    return this_player()->show_subloc(subloc, on, for_obj);
    
  if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    return "";
    
  return for_obj == on
    ? "You proudly wear your " + short()
    + ", displaying your house colours.\n"
    : on->query_The_name(for_obj) + " is wearing "
    + LANG_ADDART(short()) + " of the Eil Galaith.\n";
}
