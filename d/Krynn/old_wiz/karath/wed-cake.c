#pragma save_binary
#pragma strict_types

inherit "/std/food.c";
#include <macros.h>
#include <composite.h>

public void
create_food()
{
    set_amount(10);
    set_name("slice");
    add_name("cake");
    set_pname("slices");
    add_adj( ({"gooey", "chocolate", "wedding"}) );
    set_short("slice of gooey chocolate wedding cake");
    set_pshort("slices of gooey chocolate wedding cake");
    set_long("This is a delicious huge slice of chocolate wedding cake. It's still "+
	"warm from Karath's oven and drizzled with chocolate frosting on the "+
    "top, and between it's layers. This piece still has the "+
    "bride and groom standing on the top of the cake. It's a special treat for Tianar "+
    "and Thyrus!\n");
}

public void
consume_text(object *arr, string vb)
{
    string str;
    if(this_player()->query_real_name() == "tianar")
      {
    write("You " + vb + " " + (str=COMPOSITE_DEAD(arr)) +
	", greedily inhaling your yummy cake, licking bits of frosting from "+
	"your fingers. You are so pleased that you feel like celebrating.\n"+
	"You sing \"Here Comes the Bride\" to yourself!\n");
    say(QCTNAME(this_player()) + " " + vb + "s " + str +
	", greedily inhaling " + this_player()->query_possessive() +
	" cake, licking bits of frosting from " +
	this_player()->query_pronoun() + " fingers. "+
	capitalize(this_player()->query_pronoun()) + " looks happy and "+
	"starts to sing \"Here Comes the Bride\" to herself!\n");
      }
else
  {
    write("You " + vb + " " + (str=COMPOSITE_DEAD(arr)) +
	", greedily inhaling the yummy cake, licking bits of frosting from "+
	"your fingers. You are so pleased that you feel like celebrating.\n"+
    "You dance a happy little wedding jig!\n");
    say(QCTNAME(this_player()) + " " + vb + "s " + str +
	" greedily inhaling " + this_player()->query_possessive() +
	" cake, licking bits of frosting from " +
	this_player()->query_pronoun() + " fingers. "+
	capitalize(this_player()->query_pronoun()) + " looks happy and "+
     "You dance a happy little wedding jig!\n");
  }
}
