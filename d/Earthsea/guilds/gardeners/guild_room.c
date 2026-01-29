#pragma strict_types
#pragma no_clone

#define TYPE_ABBR ([ \
   "occupational" : "occ", \
   "layman" : "lay", \
   "racial" : "race", \
   "craft"  : "craft", \
])

private string _guild_name;
private string *_guild_style = ({ });
private string *_guild_type = ({ });
private string *_guild_soul = ({ });
private string *_guild_shadow = ({ });
private string *_remove_func = ({ });
private string *_join_func = ({ });
private string *_switch_func = ({ });

private string *_join_cmds = ({ });
private string *_join_args = ({ });
private string *_leave_cmds = ({ });
private string *_leave_args = ({ });
private string *_switch_cmds = ({ });
private string *_switch_args = ({ });

public string query_guild_name() { return _guild_name; }

public nomask varargs void
add_config_guild_room(string name, string soul, string shadow,
    string style = "fighter", string type = "occupational",
    string join_func = 0,
    string remove_func = "remove_guild_" + TYPE_ABBR[type],
    string switch_func = 0,
    string *joincmds = ({ "join" }),
    string *leavecmds = ({ "leave" }),
    string *switchcmds = ({ "switch" }),
    string joinargs = "guild",
    string leaveargs = "guild",
    string switchargs = "guild")
{
    _guild_name = name;
    _guild_soul = _guild_soul + ({soul});
    _guild_shadow = _guild_shadow + ({shadow});
    _guild_style = _guild_style + ({style});
    _guild_type = _guild_type + ({type});
    _join_cmds = _join_cmds + ({joincmds});
    _leave_cmds = _leave_cmds + ({leavecmds});
    _switch_cmds = _switch_cmds + ({switchcmds});
    _join_args = _join_args + ({joinargs});
    _leave_args = _leave_args + ({leaveargs});
    _switch_args = _switch_args + ({switchargs});
    _join_func = _join_func + ({join_func});
    _remove_func = _remove_func + ({remove_func});
    _switch_func = _switch_func + ({switch_func});
}

public void
log_guild_join(object player)
{
}

public void
log_guild_leave(object player)
{
}

public void
log_guild_switch(object player)
{
}

public string
hook_guild_join_syntax(string str)
{
    return "Join layman? Join craft?\n";
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
    return "Leave layman? Leave craft?\n";
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

public string
hook_guild_switch_syntax(string str)
{
    return "Switch layman? Switch craft?\n";
}

public string
hook_guild_switch_succeed(string str, string branch)
{
    return "You switched to the " + branch + " branch of the " +
        _guild_name + ".\n";
}

public string
hook_guild_switch_not_member()
{
    return "But you are not a member!\n";
}

public string
hook_guild_switch_wrong_branch(string branch)
{
    return "You are already a member of the " +
        branch + " branch!\n";
}

public string
hook_guild_cant_switch(string str, string branch)
{
    return "Someone does not want you to switch the " + branch + 
        " branch of the " + _guild_name + ".\n";
}

public string
hook_guild_switch_fail(mixed result)
{
    return "There was a problem switching. Please report bug #" + result + ".\n";
}

public string
hook_guild_switch_shadow_error(string str)
{
    return hook_guild_switch_fail("LOAD_SHADOW");
}

public int
_join(string str)
{
    object shadow, tp = this_player();
    int result;
    int i;
    int x = -1;

    seteuid(getuid(tp));
    x = member_array(str, _join_args);
    if(x == -1)
   	{
        tp->catch_msg(hook_guild_join_syntax(str));
            return 1;
   	}
    for (i = 0; i < sizeof(_guild_type); i++)
    {
	    if(_guild_name == call_other(tp, "query_guild_name_" +
	         TYPE_ABBR[_guild_type[i]]))
	    {
	        tp->catch_msg(hook_join_already_member(str));
	        return 1;
	    }
    }
    shadow = clone_object(_guild_shadow[x]);

    if(!objectp(shadow))
    {
        tp->catch_msg(hook_guild_join_shadow_error(str));
        return 1;
    }

    result = shadow->shadow_me(tp, _guild_type[x], _guild_style[x],
        _guild_name);

    switch(result)
    {
        case 1:
            if(_guild_soul[x] && strlen(_guild_soul[x]) > 0)
            {
                if(tp->query_wiz_level())
                {
                    tp->catch_tell("You will want to add the cmdsoul: " +
                        _guild_soul[x] + " as well as the autoshadow: " +
                        _guild_shadow[x] + ":\n");
                    tp->catch_tell("Example: \n" +
                        "   Call me add_cmdsoul " + _guild_soul[x] + "\n" +
                        "   Call me add_autoshadow " + _guild_shadow[x] + ":\n" +
                        "   newhooks\n");
                }
            }

            tp->add_autoshadow(shadow);
            tp->catch_msg(hook_guild_join_succeed(str));

            if(_join_func[x])
            {
                 call_other(tp, _join_func[x]);
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
    int i;
    int x = -1;

    seteuid(getuid(tp));
    x = member_array(str, _leave_args);
    if(x == -1)
    {
        tp->catch_msg(hook_guild_leave_syntax(str));
        return 1;
    }

    if(_guild_name != call_other(tp, "query_guild_name_" +
        TYPE_ABBR[_guild_type[x]]))
    {
        tp->catch_msg(hook_guild_leave_not_member());
        return 1;
    }

    if(call_other(tp, _remove_func[x]) != 1)
    {
        write("A very strange error occured. You cannot leave!\n");
        return 1;
    }

    tp->remove_autoshadow(_guild_shadow[x]);
    tp->catch_msg(hook_guild_leave_succeed(str));
    log_guild_leave(tp);

    return 1;
}

public int
_switch(string str)
{
    object shadow, tp = this_player();
    int result;
    int i;
    int x = -1;
    int is_member = -1;
    int not_allowed = 0;

    seteuid(getuid(tp));
    if (str == 0)
    {
        tp->catch_msg(hook_guild_switch_syntax(str));
        return 1;
    }

    x = member_array(str, _switch_args);
   
    for (i = 0; i < sizeof(_guild_type); i++)
    {
        if(_guild_name == call_other(tp, "query_guild_name_" +
             TYPE_ABBR[_guild_type[i]]))
        {
            is_member = i;
            break;
        }
    }
    if (is_member == -1)
    {
        tp->catch_msg(hook_guild_switch_not_member());
        return 1;
    }

    if(_guild_name == call_other(tp, "query_guild_name_" +
        TYPE_ABBR[_guild_type[x]]))
    {
        tp->catch_msg(hook_guild_switch_wrong_branch(str + " " + _guild_type[x] + 
            " " + x + " " + TYPE_ABBR[_guild_type[x]]));
        return 1;
    }

    for (i = 0; i < sizeof(_guild_type); i++)
    {
        if (call_other(tp, "query_not_allow_join_" +
            TYPE_ABBR[_guild_type[i]],
            tp, TYPE_ABBR[_guild_type[i]], _guild_name))
        {
            if (_guild_type[i] != str)
            {
                not_allowed = 1;
            }
        }
    }
    if (not_allowed)
    {
        tp->catch_msg(hook_guild_cant_switch(str, str));
    }

    shadow = clone_object(_guild_shadow[x]);

    if(!objectp(shadow))
    {
        tp->catch_msg(hook_guild_join_shadow_error(str));
        return 1;
    }

    tp->remove_autoshadow(_guild_shadow[is_member]);

    result = shadow->shadow_me(tp, _guild_type[x], _guild_style[x],
        _guild_name);

    switch(result)
    {
        case 1:
            if(_guild_soul[x] && strlen(_guild_soul[x]) > 0)
            {
                if(tp->query_wiz_level())
                {
                    tp->catch_tell("You will want to add the cmdsoul: " +
                        _guild_soul[x] + " as well as the autoshadow: " +
                        _guild_shadow[x] + ":\n");
                    tp->catch_tell("Example: \n" +
                        "   Call me add_cmdsoul " + _guild_soul[x] + "\n" +
                        "   Call me add_autoshadow " + _guild_shadow[x] + ":\n" +
                        "   newhooks\n");
                }
            }

            tp->add_autoshadow(shadow);
            tp->catch_msg(hook_guild_switch_succeed(str, str));

            if(_join_func[x])
            {
                 call_other(tp, _switch_func[x]);
                 log_guild_switch(tp);
            }

            return 1;
        break;
        case 0:
            tp->catch_msg(hook_guild_switch_wrong_branch(str));
            return 1;
        default:
            tp->catch_msg(hook_guild_switch_shadow_error(str));
            return 1;
    }
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
    if(_switch_cmds && pointerp(_switch_cmds))
    {
       for(i=0; i < sizeof(_switch_cmds); i++)
       {
          add_action(_switch, _switch_cmds[i]);
       }
    }
}
