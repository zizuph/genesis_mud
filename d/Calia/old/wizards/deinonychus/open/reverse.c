inherit "/std/object";

#include <stdproperties.h>

create_object()
{
  set_name("reverse");
  set_short("reverse");
  set_long("This is a nice tool to reverse all you say. Just type reverse " +
           "<cmd> <text>. There has to be a blank between <cmd> and <text>.\n");
}

init()
{
  add_action("do_reverse","reverse");
}

string
reverse(string s)
{
    string *orig, *dest;
    int siz,i;

    orig = explode(s,"");
    siz = sizeof(orig);
    dest = allocate(siz);
    for (i=0; i<siz; i++)
	dest[i] = orig[siz-i-1];
    return implode(dest,"");
}

 
int
do_reverse(string str)
{
  string cmd;
  string *commandline;
  string text;

  commandline = explode(str," ");
  cmd = commandline[0];
  commandline[0] = "";
  text = implode(commandline," ");
  text = reverse(text);
  this_player()->command(implode(({cmd, text})," "));
  return 1;
}

