inherit "/d/Roke/gresolle/open/sceduler";
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>

create_sceduler()
{
  set_name("cigar");
  set_short("fat cigar");
  set_adj("fat");
  set_long("This is a fat cigar from Roke.\n");

}

smoke(string s)
{
  notify_fail("Smoke what?\n");
  if(!id(s))
    return 0;

  notify_fail("It's already lit, stupid!\n");
  if(query_prop("geggegeg"))
    return 0;

  add_prop("geggegeg",1);

  say(QCTNAME(this_player())+" lights a huge cigar.\n");
  this_player()->catch_msg("You light the cigar.\n");

  enable_random(1);

  set_duration(120);

  set_m_time(15);

  init_sceduling();

  this_player()->add_prop(LIVE_S_SOULEXTRA,"smoking a cigar");

  add_prop(OBJ_I_NO_DROP,"You decide against dropping the burning cigar. It might start a fire.\n");
 
  return 1;
}
sceduled_function()
{
  this_player()->catch_msg("You inhale some smoke from the cigar.\n");
  tell_room(environment(this_player()),QCTNAME(this_player())+" inhales some smoke from a huge cigar.\n",this_player());
}
remove_function()
{
  this_player()->catch_msg("You drop the consumed cigar on the floor.\n");
  say(QCTNAME(this_player())+" drops a consumed cigar on the floor.\n");
}
init()
{
  ::init();

    add_action("smoke","smoke");
  add_action("smoke","light");
    add_action("blow","blow");
  }
blow(string s)
{
  object *obs,who;

  notify_fail("You must light the cigar first.\n");
  if(!query_prop("geggegeg"))
    return 0;

  notify_fail("Blow smoke in whos face?\n");
  if (!s) return 0;
  obs = PARSE_THIS(s,"%l");

  if(!sizeof(obs))
    return 0;
  who = obs[0];

  this_player()->catch_msg("You blow some smoke in "+QTNAME(who)+"'s face.\n");
  who->catch_msg(QCTNAME(this_player())+" blows some cigar smoke in your face.\n");
  say(QCTNAME(this_player())+" blows some smoke in "+QTNAME(who)+"'s face.\n",({this_player(),who}));

  seteuid(getuid(this_object()));
  clone_object("/d/Roke/gresolle/wiztoys/csmoke")->move(who);

  return 1;
}
