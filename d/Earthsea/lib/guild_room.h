public void log_guild_join(object player);
public void log_guild_leave(object player);

public string hook_guild_join_syntax(string str);
public string hook_guild_join_succeed(string str);
public string hook_join_already_member(string str);
public string hook_guild_cant_join(string str);
public string hook_guild_join_fail(mixed result);
public string hook_guild_join_shadow_error(string str);
public string hook_guild_leave_syntax(string str);
public string hook_guild_leave_not_member();
public string hook_guild_leave_succeed(string str);

public int _join(string str);
public int _leave(string str);
