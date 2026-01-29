inherit "/std/monster";

public void
create_monster()
{
    set_name("test");
    trig_new("%s jumps.", "blah");
}
public void
blah(string str)
{
    find_player("shiva")->catch_tell(str + "\n");
}

public mixed trig_check(string str, string pat, string func)
{
  mixed val = ::trig_check(str, pat, func);
  
  find_player("shiva")->catch_tell(str + "\n");  
  find_player("shiva")->catch_tell(pat + "\n");  
  find_player("shiva")->catch_tell(val + "\n");
  return val;
}
