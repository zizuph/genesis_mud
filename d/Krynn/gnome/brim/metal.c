/* created by Aridor, 06/15/94 */

inherit "/std/object";

int looked_at = 0;

void
create_object()
{
    set_short("iron piece");
    set_pshort("iron pieces");
    set_name("metal");
    set_adj("iron");
    add_name("piece");
    add_name("iron");
    set_long("@@my_long");
}

string
my_long()
{
    if (looked_at < 1)
      {
	  looked_at++;
	  return "It is a bulk of metal, but you need to look at it some " +
	    "more before you can make something from the form of it.\n";
      }
    else if (looked_at < 2)
      {
	  looked_at++;
	  return "It is a bulk of metal, looking again you think " +
	    "you may be able to make something from the form of " +
	    "it, but you are not sure yet.\n";
      }
    else
      {
	  if (!id("muffin_solution"))
	    add_name("muffin_solution");
	  return "It is a bulk of metal, but you think the form of it " +
	    "resembles the number 24. This sounds like a reasonable number " +
	    "for just about anything.\n";
      }
}

void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
    if (!dest->id("brimsch_gnome"))
      remove_name("muffin_solution");
    looked_at = 0;
}
