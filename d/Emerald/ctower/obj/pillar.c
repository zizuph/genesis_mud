/* ctower/obj/pillar.c is cloned by ctower/done1.c */
 
inherit "/std/container";
 
#include <stdproperties.h>
#include <macros.h>
 
string color;

void set_color(string pillar_color);
 
void
create_container()
{
    set_name("pillar");
    add_name("crystal");
    add_name("ctower_quest_pillar");
    add_adj("crystal");

    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_HEIGHT, 100);
    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(CONT_I_VOLUME, 3600);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(CONT_I_MAX_VOLUME, 10000);
   
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_I_NO_GET, 1);

    set_color("blue");
}

void
transform_pillar()
{
    add_name("fin_pillar");
    add_adj("glowing");
    set_long(query_long() + "The " + color + " pillar is glowing softly.\n");
}

void
set_color(string pillar_color)
{
    remove_adj(color);

    color = pillar_color;
    add_adj(color);
    set_long("This " + color + " crystal pillar has a small triangular " +
	"depression, each side being 6 cm.\n");
    set_short(color + " crystal pillar");
}

int
prevent_enter(object ob)
{
    if (ob->id(color + "_ctower_pyramid") && !id("fin_pillar"))
    {
        return 0;
    }

    write("The " + ob->short() + " resists being placed on " +
        "the " + short() + ".\n");
    return 1;
}

void
fuse(object pyramid)
{
    write("The " + pyramid->short() + 
        " fuses into place on the pillar, which starts to glow.\n");
    say(QCTNAME(this_player()) + " does something to the crystal " +
        "pillar and it starts to glow.\n");

    pyramid->remove_object();    
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!ob->id(color + "_ctower_pyramid"))
    {
        return;
    }

    transform_pillar();

    set_alarm(0.0, 0.0, &fuse(ob));
}

void
describe_contents(object for_obj, object *obarr)
{
    return;
}
