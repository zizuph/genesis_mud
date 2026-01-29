#pragma strict_types
#pragma no_clone

#include "guild_room.h"

#define TYPE_ABBR ([ \
   "occupational" : "occ", \
   "layman" : "lay", \
   "racial" : "race", \
])

private string _guild_name, _guild_style, _guild_type, _guild_soul,
   _guild_shadow, _remove_func, _join_func
;
private string *_join_cmds, *_join_args, *_leave_cmds, *_leave_args;

public string query_guild_name() { return _guild_name; }

public nomask varargs void
config_guild_room(string name, string soul, string shadow,
   string style = "fighter", string type = "occupational",
   string join_func = 0,
   string remove_func = "remove_guild_" + TYPE_ABBR[type],
   string *joincmds = ({ "join" }), string *leavecmds = ({ "leave" }),
   string *joinargs = ({ "the guild", "guild" }),
   string *leaveargs = ({ "the guild", "guild" })
)
{
   _guild_name = name;
   _guild_soul = soul;
   _guild_shadow = shadow;
   _guild_style = style;
   _guild_type = type;
   _join_cmds = joincmds;
   _leave_cmds = leavecmds;
   _join_args = joinargs;
   _leave_args = leaveargs;
   _join_func = join_func;
   _remove_func = remove_func;
}

public nomask varargs void
init_guild_room()
{
   int i;

   if(_join_cmds && pointerp(_join_cmds))
   {
      for(i=0; i < sizeof(_join_cmds); i++)
      {
         add_action(_join, _join_cmds[i]);
      }
   }

   if(_leave_cmds && pointerp(_leave_cmds))
   {
      for(i=0; i < sizeof(_leave_cmds); i++)
      {
         add_action(_leave, _leave_cmds[i]);
      }
   }
}

public void
log_guild_join(object player)
{
}

public void
log_guild_leave(object player)
{
}

public string
hook_guild_join_syntax(string str)
{
   return "Join the what? The guild?\n";
}

public string
hook_guild_join_succeed(string str)
{
   return "You join the " + _guild_name + ".\n";
}

public string
hook_join_already_member(string str)
{
   return "But you are already a member!\n";
}

public string
hook_guild_cant_join(string str)
{
   return "Someone does not want you to join the " + _guild_name + ".\n";
}

public string
hook_guild_join_fail(mixed result)
{
   return "There was a problem joining. Please report bug #" + result + ".\n";
}

public string
hook_guild_join_shadow_error(string str)
{
   return hook_guild_join_fail("LOAD_SHADOW");
}

public string
hook_guild_leave_syntax(string str)
{
   return "Leave the what? The guild?\n";
}

public string
hook_guild_leave_not_member()
{
   return "But you are not a member!\n";
}

public string
hook_guild_leave_succeed(string str)
{
   return "You left the " + _guild_name + ".\n";
}

public int
_join(string str)
{
   object shadow, tp = this_player();
   int result;

   seteuid(getuid(tp));

   if(member_array(str, _join_args) == -1)
   {
      tp->catch_msg(hook_guild_join_syntax(str));
      return 1;
   }

   if(_guild_name == call_other(tp, "query_guild_name_" +
      TYPE_ABBR[_guild_type]))
   {
      tp->catch_msg(hook_join_already_member(str));
      return 1;
   }

   shadow = clone_object(_guild_shadow);

   if(!objectp(shadow))
   {
      tp->catch_msg(hook_guild_join_shadow_error(str));
      return 1;
   }

   result = shadow->shadow_me(tp, _guild_type, _guild_style,
      _guild_name
   );

   switch(result)
   {
      case 1:
         if(_guild_soul && strlen(_guild_soul) > 0)
         {
            if(tp->query_wiz_level())
            {
               tp->catch_tell("You will want to add the cmdsoul: " +
                  _guild_soul + " as well as the autoshadow: " +
                  _guild_shadow + ":\n");
               tp->catch_tell("Example: \n" +
                  "   Call me add_cmdsoul " + _guild_soul + "\n" +
                  "   Call me add_autoshadow " + _guild_shadow + ":\n" +
                  "   newhooks\n");
             }
         }

         tp->add_autoshadow(shadow);
         tp->catch_msg(hook_guild_join_succeed(str));

         if(_join_func)
         {
            call_other(tp, _join_func);
            log_guild_join(tp);
         }

         return 1;
      break;
      case 0:
          tp->catch_msg(hook_join_already_member(str));
          return 1;
      case -4:
          tp->catch_msg(hook_guild_cant_join(str));
          return 1;
      default:
         tp->catch_msg(hook_guild_join_fail(result));
         return 1;
   }
}

public int
_leave(string str)
{
   object tp = this_player();
   int result;

   seteuid(getuid(tp));

   if(member_array(str, _leave_args) == -1)
   {
      tp->catch_msg(hook_guild_leave_syntax(str));
      return 1;
   }

   if(_guild_name != call_other(tp, "query_guild_name_" +
      TYPE_ABBR[_guild_type]))
   {
      tp->catch_msg(hook_guild_leave_not_member());
      return 1;
   }

   if(call_other(tp, _remove_func) != 1)
   {
      write("A very strange error occured. You cannot leave!\n");
      return 1;
   }

   tp->remove_autoshadow(_guild_shadow);
   tp->catch_msg(hook_guild_leave_succeed(str));
   log_guild_leave(tp);

   return 1;
}
