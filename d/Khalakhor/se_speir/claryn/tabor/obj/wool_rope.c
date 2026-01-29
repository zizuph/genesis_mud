//
// A hand-made wool rope - spun by the spinning wheel
//
// Zima  May 20, 1998
//
inherit "/std/rope";
 
string color;
 
string query_color()   { return color; }
void set_color(string c)
{
   if (stringp(color)) remove_adj(color);
   color=c;
   set_short(color+" wool rope");
   set_long("It is a standard rope, homespun of "+color+" wool.\n");
   add_adj(color);
}
 
public void create_rope()
{
   set_name("rope");
   add_adj(({"wool","homespun"}));
   set_color("white");
}
