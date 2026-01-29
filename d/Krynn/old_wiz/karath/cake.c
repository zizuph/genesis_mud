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
    add_adj( ({"gooey", "chocolate"}) );
    set_short("slice of gooey chocolate cake");
    set_pshort("slices of gooey chocolate cake");
    set_long("This is a delicious huge slice of chocolate cake. It's still "+
	"warm from Karath's oven and drizzled with chocolate frosting on the "+
	"top, and between it's layers. It's a special treat for Cizada's "+
	"100th birthday!\n");
}

public void
consume_text(object *arr, string vb)
{
    string str;
    if(this_player()->query_real_name() == "cizada")
      {
    write("You " + vb + " " + (str=COMPOSITE_DEAD(arr)) +
    ", greedily inhaling it and licking bits of frosting from "+
	"your fingers. You are so pleased that you feel like celebrating.\n"+
	"You sing Happy Birthday to yourself!\n");
    say(QCTNAME(this_player()) + " " + vb + "s " + str +
	", greedily inhaling " + this_player()->query_possessive() +
	" cake, licking bits of frosting from " +
	this_player()->query_possessive() + " fingers. "+
	capitalize(this_player()->query_pronoun()) + " looks happy and "+
	"starts to sing Happy Birthday to herself!\n");
      }
else
  {
    write("You " + vb + " " + (str=COMPOSITE_DEAD(arr)) +
    ", greedily inhaling it and licking bits of frosting from "+
	"your fingers. You are so pleased that you feel like celebrating.\n"+
	"You sing Happy Birthday to Cizada!\n");
    say(QCTNAME(this_player()) + " " + vb + "s " + str +
	" greedily inhaling " + this_player()->query_possessive() +
	" cake, licking bits of frosting from " +
	this_player()->query_possessive() + " fingers. "+
	capitalize(this_player()->query_pronoun()) + " looks happy and "+
	"starts to sing Happy Birthday to Cizada!\n");
  }
}
