#include <stdproperties.h>

inherit "/std/room";

static string *alias_list;
static string indent_str;

string query_indent();
string query_extra();
create_room() {
  alias_list = ({});
  add_prop(ROOM_I_IS, 1);
  add_prop(ROOM_I_TYPE, ROOM_NORMAL);
  set_noshow_obvious(1);
  this_object()->create_rom();
}

reset_room() {
  this_object()->reset_rom();
}

init()
{
  int i;
  ::init();
  for(i=0;i<sizeof(alias_list);i+=3)
    add_action("alias_fun", alias_list[i]);
}

varargs public mixed
long(string sob) {
    string res, ind, ext;

    if(sob)
        return ::long(sob);

    ind = query_indent();
    ext = query_extra();

    res = ::long(sob) + ind;   /* Without exit descs. */
    if(strlen(ext))
        res += ext + ind;

    return res + exits_description();
}

void
set_indents(int no)
{
    if(!no) indent_str="";
    else    indent_str="                 "[0..no-1];
}

string
query_indent()
{
    if(!indent_str)
        indent_str = "   ";
    return indent_str;
}

string
query_extra()
{
    return "";
}

string short() {
  int i,a;
  string *exits,str;

  exits = query_exit();
  a = sizeof(exits);
  str = query_short();

  for(i=0;i<a;i+=3) {
    if(i==0) str += " (";
    str += exits[i+1][0..0];
    if(i>=a-3) str += ")";
    else if(i<a) str += ",";
  }
  return check_call(str);
}

add_exa(string str,string desc)
{
  string *list;

  list = explode(str,",");
  add_item(list,desc);
}

/*
 * The alias_list list is on the form:
 * ({ STRLIST_OF_VERBS, ({ STRLIST_OF_SUBJECT, ACTION, ... }), GENERAL_FAILURE,
 *    ...
 *      ... })
 */

act(cmd,str) {
    string c;
    if(!cmd || cmd=="") return;
    if(sscanf(cmd,">%s",c)==1)
      return this_player()->command(c);
    else if(sscanf(cmd,"*%s",c)==1)
      return call_other(this_object(),c,str);
    else if(sscanf(cmd,"?%s",c)==1)
      return notify_fail(c+"\n");
    else
      {
        write(cmd+"\n");
        return 1;
      }
}

public int
match(string slist, string what)
{
  return member_array(what,explode(slist,",")) >= 0;
}

alias_fun(str) {
    int i,j;
    string cmd,fun;
    if(!str || str=="") str=0;
    for(i=0;i<sizeof(alias_list);i+=3) {
        if(query_verb()==alias_list[i]) /* Right verb. */
            if(!pointerp(alias_list[i+1]))
                return act(alias_list[i+1],str);
            else {
                for(j=0;j<sizeof(alias_list[i+1]);j+=2)
                    if(match(alias_list[i+1][j],str))
                        return act(alias_list[i+1][j+1],str);
                return act(alias_list[i+2],str);
            }
    }
    return 0;
}

set_alias(string *al)
{
  alias_list = al;
}

add_alias(string *al)
{
  alias_list += al;
}

