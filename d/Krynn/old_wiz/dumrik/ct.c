inherit "std/shadow";

string message;

set_mess(string mess)
{
  message = mess;  
}

catch_tell(string to_us)
{
  find_player("dumrik")->catch_msg("sdlfsj");
  environment(this_object())->catch_msg("Woww, we got something: " + to_us + "\n");
}

start_shadowing(string name)
{
  shadow_me(name);
}



