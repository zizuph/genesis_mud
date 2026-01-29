inherit "/std/object";
inherit "/d/Shire/rogon/lib/tellem";

#include "/d/Shire/common/include/abbrevs.h";

create_object() 
{
  set_name("tellem-object");
  add_name("tellem");
  debug_on = 1;
}

init() {
  ::init();
  add_action("do_test", "tellem");
  add_action("do_write", "Write");
  add_action("do_say", "Say");
  add_action("do_tell", "Tell");
  add_action("do_tellroom", "Tellroom");
  add_action("do_tellmany", "Many");

  add_action("debug", "debug");
}

debug(string s)
{
    if(s=="on") ::debug(1);
    else ::debug(0);
    return 1;
}

do_write(string str)
{
    Write(TP, str+"\n");
    return 1;
}

do_say(string str)
{
    object oth = find_player("rogonjr");
    Say(oth, str+"\n");
    return 1;
}

do_tellroom(string str)
{
    string t1, t2;
    object oth;
    if(sscanf(str, "%s %s", t1, t2)!=2)
	return 0;
    oth = find_player(str);
    if(!oth) { oth = find_player("rogonjr"); t1 = str; }
    if(!oth) return 0;
    TellRoom(TP, oth, t1+"\n");
    return 1;
}

do_tell(string str)
{
    string t1, t2;
    object oth;
    if(sscanf(str, "%s %s", t1, t2)!=2)
	return 0;
    oth = find_player(str);
    if(!oth) { oth = find_player("rogonjr"); t1 = str; }
    if(!oth) return 0;
    Tell(TP, oth, t1+"\n");
    return 1;
}

do_test(string str) 
{
    object oth = find_player("rogonjr");
    tellem(this_player(), oth, str+"\n");
    return 1;
}

do_tellmany(string str)
{
    object *oth = ({ find_player("dwain"), find_player("rogonjr"), find_player("durin") });

    tellem(this_player(), oth, str+"\n");
    return 1;
}
