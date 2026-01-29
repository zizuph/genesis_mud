inherit "/std/scroll";
inherit "/w/kessie/icewall/local.h";
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>

void
create_scroll()
{
    set_name("scroll");
    set_adj("protection from fire");
    set_long("Some readable text is written on this scroll.\n");

    add_prop(OBJ_I_VALUE, 678);
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 254);

    add_prop(OBJ_S_WIZINFO, "Protection from fire scroll.\n");
    add_prop(MAGIC_AM_MAGIC, ({55, "enchantment"}) );

    set_file(OBJKESSIE + "fire_prot_txt");
}

void
init()
{
    ::init();

    add_action(recite, "recite");
}

int
recite(string str)
{
    object ob, *obj;

    notify_fail("Recite which scroll? Or recite which scroll on what?\n");

    if(str != "protection from fire scroll")
    return 0;

    say(QCTNAME(this_player()) + " recites a scroll.\n");
    write("You recite the protection from fire scroll.\n");

    clone_object(OBJKESSIE + "prot_fire_obj")->move(this_player());

    call_out("remove_object", 1);
    write("\nYour scroll of protection from fire crumbles to dust.\n");
    say("The scroll held by " + QTNAME(ob) + " crumbles into dust.\n");
    return 1;
}

int
dispel_magic(int num)
{
    object ob; 

    if (num > 55)
    {
  	ob = environment(this_object());
	if (ob && living(ob))
	{
	    tell_object(ob, "Your scroll glows black and crumbles to dust.\n");
	    say("The scroll " + QTNAME(ob) + " is holding glows black " +
		"and crumbles to dust.\n", ob);
        } else
	    say("The scroll glows black and crumbles to dust.\n");

	call_out("remove_object", 1);
	return 1;
    }

    return 0;
}
